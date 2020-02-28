#ifndef SYSCTL_H
#define SYSCTL_H

/*Parameter: Clock
API : void SYSCTL_setSystemClock (uint32_t Clock)
*/

#define SYSCTL_MAIN_OSCILLATOR_CLOCK 0xFFFFFFFE


/* 
Parameter: status
API: void SYSCTL_controlGPIO(u32 GPIO_Num, u8 status)
*/

#define SYSCTL_GPIO_ENABLE 0
#define SYSCTL_GPIO_DISABLE 1

/* 
Parameter: GPIO_Num
API: void SYSCTL_controlGPIO(u32 GPIO_Num, u8 status) 
*/
#define SYSCTL_GPIO_A 0x00000001
#define SYSCTL_GPIO_B 0x00000002
#define SYSCTL_GPIO_C 0x00000004
#define SYSCTL_GPIO_D 0x00000008
#define SYSCTL_GPIO_E 0x00000010
#define SYSCTL_GPIO_F 0x00000020

errStat SYSCTL_setSystemClock (u32 Clock);
errStat SYSCTL_controlGPIO(u32 GPIO_Num, u8 status);

#endif