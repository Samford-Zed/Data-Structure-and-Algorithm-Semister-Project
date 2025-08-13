package com.Loanmanagement.Loan.LMS.client;

import com.Loanmanagement.Loan.LMS.model.BankAccount;
import com.Loanmanagement.Loan.LMS.model.Loan;
import com.Loanmanagement.Loan.LMS.model.Repayment;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

@Component // This makes it a Spring bean that can be injected
public class BmsClientMockImpl implements BmsClient {

    private static final Logger logger = LoggerFactory.getLogger(BmsClientMockImpl.class);

    @Override
    public void startBankAccountVerification(BankAccount bankAccount) {
        logger.info("MOCK BMS CALL: Initiating verification for account {}", bankAccount.getAccountNumber());
        // In a real scenario, this would make an HTTP API call to the BMS.
        // The BMS would then handle the micro-deposit logic.
    }

    @Override
    public void disburseLoan(Loan loan) {
        logger.info("MOCK BMS CALL: Disbursing loan {} of amount {} to account {}",
                loan.getId(), loan.getPrincipalAmount(), loan.getBankAccount().getAccountNumber());
        // This would make an API call to the BMS to transfer the money.
    }

    @Override
    public boolean processRepayment(Repayment repayment) {
        logger.info("MOCK BMS CALL: Processing repayment {} of amount {} from account {}",
                repayment.getId(), repayment.getAmount(), repayment.getPaymentAccount().getAccountNumber());
        // This would make an API call to the BMS to pull funds.
        // We return true to simulate a successful payment.
        return true;
    }
}