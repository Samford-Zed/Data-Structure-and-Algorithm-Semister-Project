package com.Loanmanagement.Loan.LMS.repository;

import com.Loanmanagement.Loan.LMS.model.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

@Repository
public interface UserRepository extends JpaRepository<User, Long> {

    // Find user by email (for authentication)
    Optional<User> findByEmail(String email);

    // Check if email exists (for registration)
    boolean existsByEmail(String email);
    boolean existsByPhoneNumber(String phoneNumber);  // Added phone number check


    // Update user password
    @Transactional
    @Modifying
    @Query("UPDATE User u SET u.password = ?2 WHERE u.email = ?1")
    void updatePassword(String email, String newPassword);

    // Update user details (excluding password)
    @Transactional
    @Modifying
    @Query("UPDATE User u SET u.fullName = ?2 WHERE u.id = ?1")
    void updateUserDetails(Long id, String fullName);

    // Find all users with a specific role (for admin)
    @Query("SELECT u FROM User u JOIN u.roles r WHERE r = ?1")
    List<User> findAllByRole(String role);

    // Enable/disable user account
    @Transactional
    @Modifying
    @Query("UPDATE User u SET u.enabled = ?2 WHERE u.id = ?1")
    void setUserEnabledStatus(Long id, boolean enabled);

    // Find all active/inactive users
    List<User> findAllByEnabled(boolean enabled);
}