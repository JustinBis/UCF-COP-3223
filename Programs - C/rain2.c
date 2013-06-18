/* ****************** */
/* P5-B Random Weather*/
/* Justin Bisignano   */
/* COP 3223 Section 4 */
/* 10/6/2012          */
/* ****************** */

#include <stdio.h>
#include <math.h>
#include <time.h>

int main(void){
    // Initilize Variables
    int temp, compare;
    double probability, upper, percentage;

    // Seed random for later
    srand(time(0));

    // Get Temperature
    printf("What is the temperature in Fahrenheit?\n");
    scanf("%d", &temp);

    // Set Probability
    if(temp<32){ // If the temp is less than 32, probability is 0
        probability = 0;
    }
    else if(temp>=32 && temp<=80){ // If temp is between 32 and 80 inclusive, use this formula.
        upper = fabs(65-temp); // Uses the fabs() function in the cmath library to get the absolute value of a double.
        probability = upper/100.0;
    }
    else if(temp>80){ // Last resort, temp is above 80
        probability = 2*(temp-50)/120.0;
    }

    // Output Probability to 2 decimal places.
    percentage = 100*probability;
    printf("The proability of rain is %.2lf%%\n", percentage);

    // Run a simulation to see if it rains
    compare = rand()%1000 + 1; // Generates a random value between 1 and 1000 (as opposed to 1 to 100) to accommodate for one decimal place of extra accuracy.

    // We have to multiply percentage below by 10 because percent is on a 100 basis and we need it to be on a 1000 basis to compare to the random number to get that extra accuracy.
    if(compare<=percentage*10) // compare could equally likely be any number from 1 to 1000. If there was a 25.0% chance of rain, and we chose a number of 250 or below (a 25.0% chance), then it rained.
        printf("In our simulation, it rained!\n");

    else
        printf("In our simulation, it did not rain!\n");

    // Return 0 unpon completion.
    return 0;
}

