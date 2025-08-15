package com.Loanmanagement.Loan.LMS.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.EnumType;
import jakarta.persistence.Enumerated;
import java.math.BigDecimal;
import java.time.LocalDateTime;

@Entity
public class Repayment {

    public enum RepaymentStatus {
        PENDING,
        COMPLETED,
        FAILED
    }

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne
    private Loan loan;

    @ManyToOne
    private User user;

    @ManyToOne
    private BankAccount paymentAccount;

    private BigDecimal amount;

    private LocalDateTime repaymentDate;

    @Enumerated(EnumType.STRING)
    private RepaymentStatus status;

    // Getters and setters

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Loan getLoan() {
        return loan;
    }

    public void setLoan(Loan loan) {
        this.loan = loan;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public BankAccount getPaymentAccount() {
        return paymentAccount;
    }

    public void setPaymentAccount(BankAccount paymentAccount) {
        this.paymentAccount = paymentAccount;
    }

    public BigDecimal getAmount() {
        return amount;
    }

    public void setAmount(BigDecimal amount) {
        this.amount = amount;
    }

    public LocalDateTime getRepaymentDate() {
        return repaymentDate;
    }

    public void setRepaymentDate(LocalDateTime repaymentDate) {
        this.repaymentDate = repaymentDate;
    }

    public RepaymentStatus getStatus() {
        return status;
    }

    public void setStatus(RepaymentStatus status) {
        this.status = status;
    }
}