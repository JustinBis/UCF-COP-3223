/* ****************** */
/* P4-Ichiban Buffet  */
/* Justin Bisignano   */
/* COP 3223 Section 4 */
/* 9/28/2012          */
/* ****************** */

#include <stdio.h>

#define BUFFET_PRICE 9.05
#define SALMON_VALUE 0.75
#define VOLCANO_VALUE 1.25

int main(void){
    // Initilize Variables
    int numsalmon, numvolvano;
    double saved;

    // Ask for Inputs
    printf("How many salmon roll pieces did you eat?\n");
    scanf("%d", &numsalmon);
    printf("How many volcano roll pieces did you eat?\n");
    scanf("%d", &numvolvano);

    // Do some math
    saved = (numsalmon*SALMON_VALUE + numvolvano*VOLCANO_VALUE) - BUFFET_PRICE;

    // Print Final Results
    printf("You saved $%.2lf.\n", saved);
    return 0;
}
