/* ****************** */
/* P4-Menchies        */
/* Justin Bisignano   */
/* COP 3223 Section 4 */
/* 9/28/2012          */
/* ****************** */

#include <stdio.h>

#define PRICE 0.49
#define SALES_TAX 0.065

int main(void){
    // Initilize Variables
    double cash, ratio;
    double priceaftertax, arupamount, childamount;

    // Ask for Inputs
    printf("How many dollars do you have for frozen yogurt?\n");
    scanf("%lf", &cash);
    printf("What is the ratio of yougurt that you'll get to your child?\n");
    scanf("%lf", &ratio);

    // Do some math
    priceaftertax = (PRICE*(1+SALES_TAX));
    childamount = (cash/priceaftertax)/(ratio+1);
    arupamount = childamount*ratio;

    // Print Final Results
    printf("You will get %.2lf ounces of yogurt.\n", arupamount);
    printf("Your child will get %.2lf ounces of yogurt.\n", childamount);
    return 0;
}
