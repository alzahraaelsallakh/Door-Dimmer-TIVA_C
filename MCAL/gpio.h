#ifndef GPIO_H
#define GPIO_H


/*****************************************************************************
 Macros for hardware access.
*****************************************************************************/
#define HWREG(x)                                                              \
        (*((volatile u32 *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile u16 *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile u8 *)(x)))


/******************************************************************************

 The following are defines for the GPIO register offsets.

/*******************************************************************************/
#define GPIO_O_DATA             0x00000000  /* GPIO Data                       */
#define GPIO_O_DIR              0x00000400  /* GPIO Direction                  */
#define GPIO_O_IS               0x00000404  /* GPIO Interrupt Sense            */
#define GPIO_O_IBE              0x00000408  /* GPIO Interrupt Both Edges       */
#define GPIO_O_IEV              0x0000040C  /* GPIO Interrupt Event            */
#define GPIO_O_IM               0x00000410  /* GPIO Interrupt Mask             */
#define GPIO_O_RIS              0x00000414  /* GPIO Raw Interrupt Status       */
#define GPIO_O_MIS              0x00000418  /* GPIO Masked Interrupt Status    */
#define GPIO_O_ICR              0x0000041C  /* GPIO Interrupt Clear            */
#define GPIO_O_AFSEL            0x00000420  /* GPIO Alternate Function Select  */
#define GPIO_O_DR2R             0x00000500  /* GPIO 2-mA Drive Select          */
#define GPIO_O_DR4R             0x00000504  /* GPIO 4-mA Drive Select          */
#define GPIO_O_DR8R             0x00000508  /* GPIO 8-mA Drive Select          */
#define GPIO_O_ODR              0x0000050C  /* GPIO Open Drain Select          */
#define GPIO_O_PUR              0x00000510  /* GPIO Pull-Up Select             */
#define GPIO_O_PDR              0x00000514  /* GPIO Pull-Down Select           */
#define GPIO_O_SLR              0x00000518  /* GPIO Slew Rate Control Select   */
#define GPIO_O_DEN              0x0000051C  /* GPIO Digital Enable             */
#define GPIO_O_LOCK             0x00000520  /* GPIO Lock                       */
#define GPIO_O_CR               0x00000524  /* GPIO Commit                     */
#define GPIO_O_AMSEL            0x00000528  /* GPIO Analog Mode Select         */
#define GPIO_O_PCTL             0x0000052C  /* GPIO Port Control               */
#define GPIO_O_ADCCTL           0x00000530  /* GPIO ADC Control                */
#define GPIO_O_DMACTL           0x00000534  /* GPIO DMA Control                */
#define GPIO_O_SI               0x00000538  /* GPIO Select Interrupt           */
#define GPIO_O_DR12R            0x0000053C  /* GPIO 12-mA Drive Select         */
#define GPIO_O_WAKEPEN          0x00000540  /* GPIO Wake Pin Enable            */
#define GPIO_O_WAKELVL          0x00000544  /* GPIO Wake Level                 */
#define GPIO_O_WAKESTAT         0x00000548  /* GPIO Wake Status                */
#define GPIO_O_PP               0x00000FC0  /* GPIO Peripheral Property        */
#define GPIO_O_PC               0x00000FC4  /* GPIO Peripheral Configuration   */
                                                                        

/******************************************************************************
  
  The following are defines for the bit fields in the GPIO_O_LOCK register.
  
******************************************************************************/
#define GPIO_LOCK_M             0xFFFFFFFF  /* GPIO Lock                      */
#define GPIO_LOCK_UNLOCKED      0x00000000  /* The GPIOCR register is unlocked*/
                                            /* and may be modified            */
#define GPIO_LOCK_LOCKED        0x00000001  /* The GPIOCR register is locked  */
                                            /* and may not be modified        */
#define GPIO_LOCK_KEY           0x4C4F434B  /* Unlocks the GPIO_CR register   */

/******************************************************************************
 The following are defines for the bit fields in the GPIO_O_WAKESTAT
 register.
/******************************************************************************/

#define GPIO_WAKESTAT_STAT4     0x00000010  /* P[4] Wake Status     */


/*****************************************************************************
 The following values define the bit field for the ui32Port argument to
 several of the APIs.
*****************************************************************************/

#define GPIO_PORTA_BASE         0x40004000  /* GPIO Port A                  */ 
#define GPIO_PORTB_BASE         0x40005000  /* GPIO Port B                  */
#define GPIO_PORTC_BASE         0x40006000  /* GPIO Port C                  */
#define GPIO_PORTD_BASE         0x40007000  /* GPIO Port D                  */
#define GPIO_PORTE_BASE         0x40024000  /* GPIO Port E                  */
#define GPIO_PORTF_BASE         0x40025000  /* GPIO Port F                  */
#define GPIO_PORTG_BASE         0x40026000  /* GPIO Port G                  */
#define GPIO_PORTH_BASE         0x40027000  /* GPIO Port H                  */


/******************************************************************************
/*
/* The following values define the bit field for the ui8Pins argument to
/* several of the APIs.
/*
/*******************************************************************************/
#define GPIO_PIN_0              0x00000001  /* GPIO pin 0                      */
#define GPIO_PIN_1              0x00000002  /* GPIO pin 1                      */
#define GPIO_PIN_2              0x00000004  /* GPIO pin 2                      */
#define GPIO_PIN_3              0x00000008  /* GPIO pin 3                      */
#define GPIO_PIN_4              0x00000010  /* GPIO pin 4                      */
#define GPIO_PIN_5              0x00000020  /* GPIO pin 5                      */
#define GPIO_PIN_6              0x00000040  /* GPIO pin 6                      */
#define GPIO_PIN_7              0x00000080  /* GPIO pin 7                      */
                                                                               
/*******************************************************************************/
/*
/* Values that can be passed to GPIODirModeSet as the ui32PinIO parameter, and
/* returned from GPIODirModeGet.
/*
/*******************************************************************************/
#define GPIO_DIR_MODE_IN        0x00000000  /* Pin is a GPIO input             */
#define GPIO_DIR_MODE_OUT       0x00000001  /* Pin is a GPIO output            */
#define GPIO_DIR_MODE_HW        0x00000002  /* Pin is a peripheral function    */

/******************************************************************************
/*
/* Values that can be passed to GPIOIntTypeSet as the ui32IntType parameter,
/* and returned from GPIOIntTypeGet.
/*
/*******************************************************************************/
#define GPIO_FALLING_EDGE       0x00000000  /* Interrupt on falling edge       */
#define GPIO_RISING_EDGE        0x00000004  /* Interrupt on rising edge        */
#define GPIO_BOTH_EDGES         0x00000001  /* Interrupt on both edges         */
#define GPIO_LOW_LEVEL          0x00000002  /* Interrupt on low level          */
#define GPIO_HIGH_LEVEL         0x00000006  /* Interrupt on high level         */
#define GPIO_DISCRETE_INT       0x00010000  /* Interrupt for individual pins   */
                                                                                
/*******************************************************************************/
/*
/* Values that can be passed to GPIOPadConfigSet as the ui32Strength parameter,
/* and returned by GPIOPadConfigGet in the *pui32Strength parameter.
/*
/******************************************************************************/
#define GPIO_STRENGTH_2MA       0x00000001  /* 2mA drive strength              */
#define GPIO_STRENGTH_4MA       0x00000002  /* 4mA drive strength              */
#define GPIO_STRENGTH_6MA       0x00000065  /* 6mA drive strength              */
#define GPIO_STRENGTH_8MA       0x00000066  /* 8mA drive strength              */
#define GPIO_STRENGTH_8MA_SC    0x0000006E  /* 8mA drive with slew rate control*/
#define GPIO_STRENGTH_10MA      0x00000075  /* 10mA drive strength             */
#define GPIO_STRENGTH_12MA      0x00000077  /* 12mA drive strength             */
                                                                              
/******************************************************************************/
/*
/* Values that can be passed to GPIOPadConfigSet as the ui32PadType parameter,
/* and returned by GPIOPadConfigGet in the *pui32PadType parameter.
/*
/*******************************************************************************/
#define GPIO_PIN_TYPE_STD       0x00000008  /* Push-pull                       */
#define GPIO_PIN_TYPE_STD_WPU   0x0000000A  /* Push-pull with weak pull-up     */
#define GPIO_PIN_TYPE_STD_WPD   0x0000000C  /* Push-pull with weak pull-down   */
#define GPIO_PIN_TYPE_OD        0x00000009  /* Open-drain                      */
#define GPIO_PIN_TYPE_ANALOG    0x00000000  /* Analog comparator               */
#define GPIO_PIN_TYPE_WAKE_HIGH 0x00000208  /* Hibernate wake, high            */
#define GPIO_PIN_TYPE_WAKE_LOW  0x00000108  /* Hibernate wake, low             */

/******************************************************************************/
/*
/* Prototypes for the APIs.
/*
/******************************************************************************/
extern errStat GPIO_DirModeSet(u32 ui32Port, u8 ui8Pins, u32 ui32PinIO);
extern errStat GPIO_PinRead(u32 ui32Port, u8 ui8Pins, u8* ui8Val);
extern errStat GPIO_PinWrite(u32 ui32Port, u8 ui8Pins, u8 ui8Val);
extern errStat GPIO_PadConfigSet(u32 ui32Port, u8 ui8Pins,u32 ui32Strength, u32 ui32PinType);

#endif