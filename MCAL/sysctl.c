#include "STD_TYPES.h"
#include "sysctl.h"

#define SYSCTL_BASEADDRESS 0x400FE000

#define SYSCTL_RCC *((volatile u32*) (SYSCTL_BASEADDRESS + 0x060))
#define SYSCTL_RCGGPIO *((volatile u32*)(SYSCTL_BASEADDRESS + 0x608))


/* Masks used by SYSCTL_setSystemClock */
#define SYSCTL_OSCSRC_MOSC 0xFFFFFFCF
#define SYSCTL_BYPASS_OSC  0xFFFFFFFF
#define SYSCTL_USESYSDIV 0xFFBFFFFF

/* API used to initialize (select) system clock to Clock argument */
errStat SYSCTL_setSystemClock (u32 Clock)
{
  if (Clock == SYSCTL_MAIN_OSCILLATOR_CLOCK)
  {
    SYSCTL_RCC &= SYSCTL_BYPASS_OSC;
    SYSCTL_RCC &= Clock & SYSCTL_OSCSRC_MOSC &  SYSCTL_USESYSDIV;
    return ERR_STAT_OK;
  }
  return ERR_STAT_NOK;
}


/* API used to enable/disable GPIO peripheral */
errStat SYSCTL_controlGPIO(u32 GPIO_Num, u8 status)
{
  if (
      (
        (GPIO_Num == SYSCTL_GPIO_A) || 
        (GPIO_Num == SYSCTL_GPIO_B) || 
        (GPIO_Num == SYSCTL_GPIO_C) || 
        (GPIO_Num == SYSCTL_GPIO_D) || 
        (GPIO_Num == SYSCTL_GPIO_E) || 
        (GPIO_Num == SYSCTL_GPIO_F)
      ) && 
      (
        (status == SYSCTL_GPIO_ENABLE) || 
        (status == SYSCTL_GPIO_DISABLE)
      )
     )
  {
    switch(status)
    {
      case SYSCTL_GPIO_DISABLE:
        SYSCTL_RCGGPIO &= ~GPIO_Num;
      break;
      
      case SYSCTL_GPIO_ENABLE:
        SYSCTL_RCGGPIO |= GPIO_Num;
      break;
    }
    return ERR_STAT_OK;
  }
  return ERR_STAT_NOK;
}
