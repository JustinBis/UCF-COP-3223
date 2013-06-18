/* ****************** */
/* P7-A  Track        */
/* Justin Bisignano   */
/* COP 3223 Section 4 */
/* 10/22/2012         */
/* ****************** */

#include <stdio.h>

#define PI 3.1415926535898

int main(void){
    // Initilize Variables
    int run, num_tracks, length, inner_mack_radius, outer_zack_radius, mack_laps, zack_laps;
    double inner_circle_distance, outer_circle_distance, mack_distance, zack_distance;

    // Open File
    FILE *ifp;
    ifp = fopen("track.in", "r");
    fscanf(ifp, "%d", &num_tracks);

    for(run=1; run<=num_tracks; run++){
        fscanf(ifp, "%d%d%d%d%d", &length, &inner_mack_radius, &outer_zack_radius, &mack_laps, &zack_laps); // Scan all 5 intergers on the line into the correct variables

        // Do some math
        inner_circle_distance = PI*inner_mack_radius*2; // Calculates the additional distance (circumference) the semi-circles on the ends of the track adds to each lap.
        outer_circle_distance = PI*outer_zack_radius*2;

        mack_distance = (inner_circle_distance + 2*length)*mack_laps;
        zack_distance = (outer_circle_distance + 2*length)*zack_laps;

        //Print Outputs
        printf("Track #%d: ", run);
        if(zack_distance>mack_distance)
            printf("I've run %.0lf more meters than Mack!!!\n", zack_distance-mack_distance);
        else
            printf("Drats!\n");
    }

    // Program Completed, so return 0.
    return 0;
}
