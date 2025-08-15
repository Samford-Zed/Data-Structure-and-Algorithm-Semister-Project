package com.Loanmanagement.Loan.LMS.repository;

import com.Loanmanagement.Loan.LMS.model.Repayment;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface RepaymentRepository extends JpaRepository<Repayment, Long> {
    // You can add custom query methods here if needed
}