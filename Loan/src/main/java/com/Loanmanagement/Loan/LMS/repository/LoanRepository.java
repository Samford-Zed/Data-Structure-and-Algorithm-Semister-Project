package com.Loanmanagement.Loan.LMS.repository;

import com.Loanmanagement.Loan.LMS.model.Loan;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface LoanRepository extends JpaRepository<Loan, Long> {
}