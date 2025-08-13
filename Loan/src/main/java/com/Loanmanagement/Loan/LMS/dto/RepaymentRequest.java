package com.Loanmanagement.Loan.LMS.dto;

import lombok.Data;
import java.math.BigDecimal;

@Data
public class RepaymentRequest {
    private Long loanId;
    private BigDecimal amount;
    private Long paymentAccountId;
}