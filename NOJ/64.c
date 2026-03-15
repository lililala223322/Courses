#include<stdio.h>

struct PIDData{
    double Kp , Ki , Kd,
           preError , integral;
};

double PIDCalculate(struct PIDData PID1,double setpoint,double measuredValue)
{
    double error = setpoint - measuredValue,     //本次误差
           diffrential = error - PID1.preError; //微分
    PID1.integral += error;                     //积分
    double output = PID1.Kp * error + PID1.Ki * PID1.integral + PID1.Kd * diffrential;//PID公式
    PID1.preError = error;
    return output;

}

int main()
{
    double setPoint, measuredValue;
	int time; 
    struct PIDData PID1 = {0,0,0,0,0};

    scanf("%lf %lf %lf", &PID1.Kp, &PID1.Ki, &PID1.Kd);
	scanf("%lf %lf %d", &setPoint, &measuredValue, &time);

	for (int i = 1; i <= time; ++i) {
		double output = PIDCalculate(PID1, setPoint, measuredValue);
		measuredValue += output;
		printf("%d %.6lf\n", i, measuredValue);
	}

	return 0;
}

/*
    n=1:
    sp=100 mV=0
    error=100
    int=100
    diff=100
    output = 0.1x100 + 0.01x100 + 0.05x100 = 100x0.16 = 16
    pre = 116

    n=2:
    sp=100 mV=0
    error=100
    int=200
    diff=-16
    output = 10 + 0.01x200 -16x0.05
*/
