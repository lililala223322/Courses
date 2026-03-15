//火箭模拟

#include <stdio.h>
#define timeStep 0.1

int main()
{
    double totalMass , rocketMass , burnTime , cE , g ;
    scanf("%lf %lf %lf %lf %lf",&totalMass,&rocketMass,&burnTime,&cE,&g);

    double propellantMass = totalMass - rocketMass;
    double massFlow = propellantMass / burnTime;
    double T = massFlow * cE;
    double altitude = 0, V = 0;
    double timeLeft = burnTime + timeStep;

    while (timeLeft >= 0)
    {
        double a = T / totalMass;
        double deltaV = a * timeStep;
        double deltaAltitude = V * timeStep;
        double deltaM = massFlow * timeStep;
        V += deltaV;
        altitude += deltaAltitude;
        totalMass -= deltaM;
        timeLeft -= timeStep;
    }

    altitude/=1000;

    printf("%.3lfkm",altitude);
        
}