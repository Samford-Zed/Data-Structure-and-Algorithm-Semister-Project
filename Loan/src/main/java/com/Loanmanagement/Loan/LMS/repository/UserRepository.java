package com.Loanmanagement.Loan.LMS.repository;

import com.Loanmanagement.Loan.LMS.model.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface UserRepository extends JpaRepository<User, Long> {
}