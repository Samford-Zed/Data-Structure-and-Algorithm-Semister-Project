package com.Loanmanagement.Loan.LMS.service;

import com.Loanmanagement.Loan.LMS.client.BmsClient;
import com.Loanmanagement.Loan.LMS.dto.RepaymentRequest;
import com.Loanmanagement.Loan.LMS.model.Loan;
import com.Loanmanagement.Loan.LMS.model.Repayment;
import com.Loanmanagement.Loan.LMS.repository.BankAccountRepository;
import com.Loanmanagement.Loan.LMS.repository.LoanRepository;
import com.Loanmanagement.Loan.LMS.repository.RepaymentRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.List;

@Service
public class RepaymentService {

    @Autowired
    private RepaymentRepository repaymentRepository;
    @Autowired
    private LoanRepository loanRepository;
    @Autowired
    private BankAccountRepository bankAccountRepository;
    @Autowired
    private BmsClient bmsClient;

    public List<Repayment> getAllRepayments() {
        return repaymentRepository.findAll();
    }

    @Transactional // Ensures all database operations succeed or fail together
    public Repayment makeRepayment(RepaymentRequest request) {
        Loan loan = loanRepository.findById(request.getLoanId()).orElseThrow(() -> new RuntimeException("Loan not found"));
        var paymentAccount = bankAccountRepository.findById(request.getPaymentAccountId()).orElseThrow(() -> new RuntimeException("Payment account not found"));

        Repayment repayment = new Repayment();
        repayment.setLoan(loan);
        repayment.setUser(loan.getUser());
        repayment.setPaymentAccount(paymentAccount);
        repayment.setAmount(request.getAmount());
        repayment.setRepaymentDate(LocalDateTime.now());
        repayment.setStatus(Repayment.RepaymentStatus.PENDING);

        Repayment savedRepayment = repaymentRepository.save(repayment);

        // Call the BMS to process the payment
        boolean paymentSuccess = bmsClient.processRepayment(savedRepayment);

        if (paymentSuccess) {
            savedRepayment.setStatus(Repayment.RepaymentStatus.COMPLETED);

            // Update the loan's outstanding balance
            BigDecimal newBalance = loan.getOutstandingBalance().subtract(request.getAmount());
            loan.setOutstandingBalance(newBalance);

            if (newBalance.compareTo(BigDecimal.ZERO) <= 0) {
                loan.setStatus(Loan.LoanStatus.PAID_OFF);
            }
            loanRepository.save(loan);
        } else {
            savedRepayment.setStatus(Repayment.RepaymentStatus.FAILED);
        }

        return repaymentRepository.save(savedRepayment);
    }
}