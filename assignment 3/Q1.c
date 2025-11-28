#include <stdio.h>

float calculateRepayment(float loan, int interest, int years) {
    if (loan <= 0 || years == 0) {
        return 0;
    }

    float loanWithInterest = loan + loan * (interest / 100.0);
    float newLoan = loanWithInterest - 40000;

    float paymentThisYear;
    if (newLoan < 0) {
        paymentThisYear = loanWithInterest;
    } else {
        paymentThisYear = loanWithInterest - newLoan;
    }

    if (newLoan < 0) {
        newLoan = 0;
    }

    printf("Year %d: Remaining loan = %.2f\n", years, newLoan);

    return paymentThisYear + calculateRepayment(newLoan, interest, years - 1);
}

int main() {
    float totalRepayment = calculateRepayment(100000, 5, 3);
    printf("Total repayment: %.2f\n", totalRepayment);
    return 0;
}
