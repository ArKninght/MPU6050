#include "msp.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <mpu6050.h>
#include <my_uart.h>
#include <inv_mpu.h>
#include <inv_mpu_dmp_motion_driver.h>
#include <delay.h>
#include <stdint.h>
#include <stdbool.h>
#define TIMER_PERIOD    2000

int16_t rawAccX, rawAccY, rawAccZ,rawGyroX, rawGyroY, rawGyroZ;
float gyroXoffset, gyroYoffset, gyroZoffset;
float temp, accX, accY, accZ, gyroX, gyroY, gyroZ;
float angleGyroX, angleGyroY, angleGyroZ,angleAccX, angleAccY, angleAccZ;
float angleX, angleY, angleZ;
float pitch,roll,yaw;
uint32_t timer;
uint32_t timer1;

double P[2][2] = {{ 1, 0 },{ 0, 1 }};
double Pdot[4] ={ 0,0,0,0};
static const double Q_angle=0.001, Q_gyro=0.003, R_angle=0.5,dtt=0.005,C_0 = 1;
double q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;

const Timer_A_UpModeConfig upConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_6,          // SMCLK/1 = 3MHz
        TIMER_PERIOD,                           // 5000 tick period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
};

void Kalman_Filter(double angle_m,double gyro_m)
{
    angleX+=(gyro_m-q_bias) * dtt;
    Pdot[0]=Q_angle - P[0][1] - P[1][0];
    Pdot[1]=- P[1][1];
    Pdot[2]=- P[1][1];
    Pdot[3]=Q_gyro;
    P[0][0] += Pdot[0] * dtt;
    P[0][1] += Pdot[1] * dtt;
    P[1][0] += Pdot[2] * dtt;
    P[1][1] += Pdot[3] * dtt;
    angle_err = angle_m - angleX;
    PCt_0 = C_0 * P[0][0];
    PCt_1 = C_0 * P[1][0];
    E = R_angle + C_0 * PCt_0;
    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;
    t_0 = PCt_0;
    t_1 = C_0 * P[0][1];
    P[0][0] -= K_0 * t_0;
    P[0][1] -= K_0 * t_1;
    P[1][0] -= K_1 * t_0;
    P[1][1] -= K_1 * t_1;
    angleX+= K_0 * angle_err;
    q_bias += K_1 * angle_err;
}

void Timer_init(void){

    MAP_Timer_A_configureUpMode(TIMER_A1_BASE, &upConfig);
    MAP_Interrupt_enableInterrupt(INT_TA1_0);
    MAP_Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
    Interrupt_enableMaster();
}

void LED_init(void){
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}



void main(void)
{

    MAP_WDT_A_holdTimer();
    MAP_FPU_enableModule();
    MAP_FPU_enableLazyStacking();
    usart_init();
    MPU_Init();
    mpu_dmp_init();
    Timer_init();
    LED_init();
    calcGyroOffsets();
    while(1){
      //mpu_update();
      mpu_dmp_get_data(&pitch, &roll, &yaw);
      printf("%f %f %f \r\n  ", pitch, roll, yaw);
      }
}

void TA1_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0);
    timer++;
    timer1++;
    if(timer1 == 1000){
        timer1 = 0;
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
}

