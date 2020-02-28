#include "STD_TYPES.h"

#include "sysctl.h"
#include "gpio.h"

#include "SWITCH.h"
#include "SWITCH_config.h"
#include "Lamp.h"
#include "Lamp_config.h"

#include "leftDoor.h"
#include "rightDoor.h"

void main ()
{
  u8 rightDoor, leftDoor;
  
  SYSCTL_setSystemClock(SYSCTL_MAIN_OSCILLATOR_CLOCK);
  
  Switch_Init(SWITCH_LEFTDOOR);
  Switch_Init(SWITCH_RIGHTDOOR);
  
  Lamp_init(Lamp_DIMMER);
  
  while (1)
  {
      LeftDoor_ReadStatus(&leftDoor);
      RightDoor_ReadStatus(&rightDoor);
      
      if (leftDoor == DOOR_CLOSED && rightDoor == DOOR_CLOSED)
      {
        Lamp_SwitchOff(Lamp_DIMMER);
          //GPIO_PinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
      }
      else
      {
        Lamp_SwitchOn(Lamp_DIMMER);
          //GPIO_PinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0xff);
      }
  }
  
  
  
  
}
