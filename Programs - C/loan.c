/* ****************** */
/* P6-B House Payments*/
/* Justin Bisignano   */
/* COP 3223 Section 4 */
/* 10/11/2012         */
/* ****************** */

#include <stdio.h>

int main(void){
    // Initilize Variables
    int month, spaces, i;
    double value, interest, payment;

    //Get Inputs
    printf("What is the value left on the mortgage?\n");
    scanf("%lf", &value);

    printf("What is the annual interest rate of the loan, in percent?\n");
    scanf("%lf", &interest);

    printf("What is the monthly payment?\n");
    scanf("%lf", &payment);

    interest = interest/12.0; // Convert to monthly interest
    interest = interest/100.0; // Convert from a percent to a real number muliplier

    // Check that the mortgage can be paid off with the monthly payment
    if ((value*interest)>=payment) // If the first increase in value from intrest is higher than the given payment, it will never be paid off.
        printf("Sorry, but you can't pay off the mortgage with a payment that low.\n");

    else{
        // Print Chart Header
        printf("Month\tPayment\tAmount Owed\n");

        // Loop through printing the chart
        for (month=1; value>0; month++){
            // Print Month Section
            printf("%d\t", month);

            // Print Payment Section
            if (value<payment)
                payment = value*(1+interest);
            printf("%.2lf\t", payment);

            // Print Amount Owed Section
            value = value * (1+interest);
            value = value - payment; // Amount owed after payment
            printf("%.2lf\n", value);

        }
    }

    // Program Completed, so return 0.
    return 0;
}
