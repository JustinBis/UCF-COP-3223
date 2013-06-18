/* ****************** */
/* P5-A Rain and Temp */
/* Justin Bisignano   */
/* COP 3223 Section 4 */
/* 10/6/2012          */
/* ****************** */

#include <stdio.h>

int main(void){
    // Initilize Variables
    int temp, time_mins, time_hours;

    //Get Temperature
    printf("What is the temperature in Fahrenheit?\n");
    scanf("%d", &temp);

    if(temp>=90){ // If the temp is greater than or equal to 90 degrees, calculate when it will rain

        // Serious math time
        // This will convert the hours and fraction of an hour given by the formula into just minutes as an integer.
        time_mins = 60*((5 - (temp-90)/5.0)); // All integers devided by 5 will have 1 decimal place, so this only will work for integer values of temperature. Good thing its guarenteed!

        time_hours = time_mins/60; // Integer devivde here to get just hours, no minutes, as an integer

        time_mins = time_mins - time_hours*60; // Reverse the integer devision and subtract it from the total minutes leaving just the remainder, which is just the leftover minutes.

        // A lot of work to get around using fmod from the math library, but it allows me to work with just integers, no seperate data types.

        // Print the result, finally
        printf("It will rain at approximately %d hours and %d minutes after noon", time_hours, time_mins);
    }
    else{
        // If it isn't above 90 degrees, tell the user that it won't rain
        printf("It will not rain today.\n");
    }

    // Program Completed, so return 0.
    return 0;
}
