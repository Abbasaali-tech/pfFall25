#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets){
    
    if (fuel == 0 || planet > totalPlanets)
    {
        return fuel;
    }

    int newfuel = fuel - consumption;

    if (planet % 2 == 0)
    {
        newfuel += recharge;
    }
    
    if (planet % 4 == 0)
    {
        newfuel += solarBonus;
    }
    
    if (newfuel < 0)
    {
        newfuel = 0;
    }
    
    printf("Planet %d: Fuel Remaining = %d\n",planet,newfuel);

    return calculateFuel(newfuel,consumption,recharge,solarBonus,planet+1,totalPlanets);
}

int main(){

    int finalFuel = calculateFuel(1000,180,50,100,1,7);

    if (finalFuel > 0)
    {
        printf("Mission Completed\n");
    }
    else
    {
        printf("Mission not completed\n");
    }
}