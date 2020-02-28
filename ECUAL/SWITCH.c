#include "STD_TYPES.h"
#include "sysctl.h"
#include "gpio.h"
#include "SWITCH.h"
#include "SWITCH_config.h"


/* 
  Description: This function shall initiate the specified switch num by setting its
  pin, port, mode and configuration in a GPIO object and passing it to GPIO module
  
  Input: switchNum which holds the index of the switch in the switch array 
  
  Output: errStat

 */
extern errStat Switch_Init(u8 switchNum)
{
  errStat status = ERR_STAT_OK;
  if (switchNum >= SWITCH_NUM)
  {
    status = ERR_STAT_NOK;
  }
  /* Creating switch element */
  switchmap_t * switchMapElement; 
  
  /* Enabling peripheral clock on PORTA */
  SYSCTL_controlGPIO(SYSCTL_GPIO_F,SYSCTL_GPIO_ENABLE);
  
  /* Getting required switch configurations */
  switchMapElement = getSwitchMap(switchNum);

  /* Initiating GPIO element */
  GPIO_DirModeSet(switchMapElement->port,switchMapElement->pin,GPIO_DIR_MODE_IN);
  GPIO_PadConfigSet(switchMapElement->port,switchMapElement->pin,GPIO_STRENGTH_2MA,switchMapElement->pullState);
  
  /* Setting bit in ODR in case of pull up switch and reseting it in case of pull down switch */
  if (GPIO_PIN_TYPE_STD_WPU == switchMapElement->pullState)
  {
    GPIO_PinWrite(switchMapElement->port,switchMapElement->pin,pinSet);
  }
  else if (GPIO_PIN_TYPE_STD_WPD == switchMapElement->pullState)
  {
    GPIO_PinWrite(switchMapElement->port,switchMapElement->pin,pinReset);
  }
  
  return status;
}


/* 
  Description: This function shall return the specified switch state which can be 
  PRESSED or RELEASED
  
  Input: switchNum which holds the index of the switch in the switch array 
  
  Output: errStat

 */
extern errStat Switch_GetSwitchState(u8 switchNum, switchState* switchValue)
{
  errStat status = ERR_STAT_OK;
  if (switchNum >= SWITCH_NUM)
  {
    status = ERR_STAT_NOK;
  }
  /* Creating switch element */
  switchmap_t * switchMapElement;  
  /* Getting required switch configurations */
  switchMapElement = getSwitchMap(switchNum);

  /* Reading GPIO value */
  GPIO_PinRead(switchMapElement->port,switchMapElement->pin,switchValue);
  
  /* The switchValue holds the pin mask which won't equal fixed number all time
     if not zero, then it has a value equals to the pin mask
  */
  if (*switchValue != RELEASED)
  {
	  *switchValue = PRESSED;
  }
  
  /* Toggling switchValue in case of pull up switch */
  if (GPIO_PIN_TYPE_STD_WPU == switchMapElement->pullState)
  {
    *switchValue = *switchValue ^ 0x01;
  }

  return status;
  
}

