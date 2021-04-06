#include<stdio.h>
#include "head.h"

void main()
{
    int tot_time, maxarr, maxdep;
    float arrrate, deprate;
    int proceed = 1;

    printf("This program will simulate the working of an airport\n");
    printf("Runway 1: Landing\n");
    printf("Runway 2: Takeoff\n");
    printf("Runway 3: Landing or Takeoff\n");
    do
    {
        printf("Enter the units of time this simulation should work for: ");
        scanf("%d", &tot_time);
        printf("Enter maximum number of planes that can be queued for landing: ");
        scanf("%d", &maxarr);
        printf("Enter maximum number of planes that can be queued for takeoff: ");
        scanf("%d", &maxdep);
        printf("Enter approximate landing rate: ");
        scanf("%f", &arrrate);
        printf("Enter approximate takeoff rate: ");
        scanf("%f", &deprate);

        if (tot_time<0 || maxarr<0 || maxdep<0 || arrrate<0 || arrrate>2 || deprate<0 || deprate>2)
        {
            proceed = 0;
            if (arrrate>2 || deprate>2)
                printf("\nHigh activity rates!\n");
            printf("Entered data unacceptable, please re-enter:\n\n");
        }
        else
            proceed = 1;

    }while (proceed == 0);

    if (arrrate+deprate>3)
        printf("WARNING: High rates of activity, airport might be saturated.\n\n");

    sim(tot_time, maxarr, maxdep, arrrate, deprate); //function where simulation occurs

}

