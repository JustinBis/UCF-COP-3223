/* ****************** */
/* P7-A  Refinancing  */
/* Justin Bisignano   */
/* COP 3223 Section 4 */
/* 10/22/2012         */
/* ****************** */

#include <stdio.h>

int main(void){
    // Initilize Variables
    int month, spaces, i;
    double orig_value, value, interest, orig_payment, payment, closing_cost;
    double firstpayment = 0, secondpayment = 0;

    //Get Inputs
    printf("What is the value left on the mortgage?\n");
    scanf("%lf", &orig_value);
    value = orig_value; // Copy value into a new variable we can use for calculations without loosing the number later.

    printf("What is the annual interest rate of the loan, in percent?\n");
    scanf("%lf", &interest);

    printf("What is the monthly payment?\n");
    scanf("%lf", &orig_payment);
    payment = orig_payment; // Again, save the value for later

    interest = interest/12.0; // Convert to monthly interest
    interest = interest/100.0; // Convert from a percent to a real number muliplier

    // Check that the mortgage can be paid off with the monthly payment. If not, return 1 and exit.
    if ((value*interest)>=payment){ // If the first increase in value from intrest is higher than the given payment, it will never be paid off.
        printf("Sorry, but you can't pay off the mortgage with a payment that low.\n");
        return 1;
        }

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
            firstpayment = firstpayment + payment;

            // Print Amount Owed Section
            value = value * (1+interest);
            value = value - payment; // Amount owed after payment
            printf("%.2lf\n", value);

        }

    // Ask user for new interest rate and closing cost
    printf("\nWhat is the new annual interest rate of the loan after refinancing, in percent?\n");
    scanf("%lf", &interest);

    printf("What was the closing cost for the refinancing?\n");
    scanf("%lf", &closing_cost);

    interest = interest/12.0; // Convert to monthly interest
    interest = interest/100.0; // Convert from a percent to a real number muliplier

    value = orig_value; // Restore the original value
    value = value + closing_cost; // Add the cost of closing to the principle

    payment = orig_payment; // Restore the original payment

        // Print Header for the Second Chart
        printf("Month\tPayment\tAmount Owed\n");

        // Loop through printing the chart
        for (month=1; value>0; month++){
            // Print Month Section
            printf("%d\t", month);

            // Print Payment Section
            if (value<payment)
                payment = value*(1+interest);
            printf("%.2lf\t", payment);
            secondpayment = secondpayment + payment;

            // Print Amount Owed Section
            value = value * (1+interest);
            value = value - payment; // Amount owed after payment
            printf("%.2lf\n", value);

        }

    if(secondpayment<firstpayment)
        printf("You should refinance. You will save $%.2lf.", firstpayment-secondpayment);
    else
        printf("You shouldn't refinance. You will not save any money.");

    // Program Completed, so return 0.
    return 0;
}
