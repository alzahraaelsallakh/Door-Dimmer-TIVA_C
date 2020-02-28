#include "STD_TYPES.h"
#include "sysctl.h"
#include "gpio.h"
#include "SWITCH.h"
#include "SWITCH_config.h"
#include "rightDoor.h"

extern errStat RightDoor_ReadStatus (u8* rightDoorStatus)
{
  errStat status = ERR_STAT_OK;
  
  status = Switch_GetSwitchState (SWITCH_RIGHTDOOR,rightDoorStatus);
  
  return status;
}