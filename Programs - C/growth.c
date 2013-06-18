/* ****************** */
/* P6-A Pop. Growth   */
/* Justin Bisignano   */
/* COP 3223 Section 4 */
/* 10/11/2012         */
/* ****************** */

#include <stdio.h>

int main(void){
    // Initilize Variables
    int doubletime, currentpop, periods, i;
    int year = 2012;

    //Get Inputs
    printf("How long (in years) does the population take to double?\n");
    scanf("%d", &doubletime);

    printf("What is the current population?\n");
    scanf("%d", &currentpop);

    printf("How many doubling periods do you want the chart to be?\n");
    scanf("%d", &periods);

    // Print Chart Header
    printf("Year\tPopulation\n");

    // Loop through printing the chart
    for (i=0; i<=periods; i++){ // Will run [Periods]+1 times because [i] starts at 0.
        printf("%d\t%d\n", year, currentpop); // Prints "[Year] -tab- [Current Pop]"
        currentpop = currentpop*2;
        year = year+doubletime;
    }


    // Program Completed, so return 0.
    return 0;
}
