/*
 * delay.c
 *
 *  Created on: 2023年7月3日
 *      Author: 15976
 */

#include "delay.h"
//必须是11.0592Mhz晶振频率，记得选择
void delay_us(unsigned int tus)//@11.0592MHz
{
    unsigned char i;
    i = tus;
    while (--i);
}

void delay_ms(unsigned int tms)
{
    unsigned char i, j;
    unsigned int ttt;
  for(ttt=tms;ttt>0;ttt--)
    {
      i = 15;
        j = 90;
        do
        {
            while (--j);
        } while (--i);
    }
}



