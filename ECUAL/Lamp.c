#include "STD_TYPES.h"
#include "sysctl.h"
#include "gpio.h"

#include "Lamp.h"
#include "Lamp_config.h"


/* 
  Description: This function shall initiate the specified lamp num by setting its
  pin, port, mode and configuration in a GPIO object and passing it to GPIO module
  
  Input: lampNum which holds the index of the lamp in the lamp array 
  
  Output: errStat

 */
extern errStat Lamp_init(u8 lampNum)
{
  errStat status = ERR_STAT_OK;
  if (lampNum >= Lamps_NUM)
  {
    status = ERR_STAT_NOK;
  }
  /* Creating Lamp element */
  lampmap_t * lampMapElement; 
  
  /* Enabling peripheral clock on PORTF */
  SYSCTL_controlGPIO(SYSCTL_GPIO_F,SYSCTL_GPIO_ENABLE);
  
  /* Getting required lamp configurations */
  lampMapElement = getLampMap(lampNum);

  /* Initiating GPIO element */
  GPIO_DirModeSet(lampMapElement->port,lampMapElement->pin,GPIO_DIR_MODE_OUT);
  
  return status;
}

/* 
  Description: This function shall turn on the specified lamp 
  
  Input: lampNum which holds the index of the lamp in the lamp array 
  
  Output: errStat

 */
extern errStat Lamp_SwitchOn(u8 lampNum)
{
  errStat status = ERR_STAT_OK;
  if (lampNum >= Lamps_NUM)
  {
    status = ERR_STAT_NOK;
  }
  
  /* Creating lamp element */
  lampmap_t * lampMapElement; 
  /* Getting required lamp configurations */
  lampMapElement = getLampMap(lampNum);

  /* Setting the lamp on */
  GPIO_PinWrite(lampMapElement->port,lampMapElement->pin,lampMapElement->ON);
  
  return status;
}

/* 
  Description: This function shall turn off the specified lamp 
  
  Input: lampNum which holds the index of the lamp in the lamp array 
  
  Output: errStat

 */
extern errStat Lamp_SwitchOff(u8 lampNum)
{
  
  errStat status = ERR_STAT_OK;
  if (lampNum >= Lamps_NUM)
  {
    status = ERR_STAT_NOK;
  }
  
  /* Creating lamp element */
  lampmap_t * lampMapElement; 
  /* Getting required lamp configurations */
  lampMapElement = getLampMap(lampNum);
 
  
  /* Setting the lamp off */
  GPIO_PinWrite(lampMapElement->port,lampMapElement->pin,lampMapElement->OFF);
  
  return status;
}
