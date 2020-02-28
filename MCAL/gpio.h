#ifndef GPIO_H
#define GPIO_H



//*****************************************************************************
//
// The following values define the bit field for the ui32Port argument to
// several of the APIs.
//
//*****************************************************************************

#define GPIO_PORTA_BASE         0x40004000  // GPIO Port A
#define GPIO_PORTB_BASE         0x40005000  // GPIO Port B
#define GPIO_PORTC_BASE         0x40006000  // GPIO Port C
#define GPIO_PORTD_BASE         0x40007000  // GPIO Port D
#define GPIO_PORTE_BASE         0x40024000  // GPIO Port E
#define GPIO_PORTF_BASE         0x40025000  // GPIO Port F
#define GPIO_PORTG_BASE         0x40026000  // GPIO Port G
#define GPIO_PORTH_BASE         0x40027000  // GPIO Port H
#define GPIO_PORTA_AHB_BASE     0x40058000  // GPIO Port A (high speed)
#define GPIO_PORTB_AHB_BASE     0x40059000  // GPIO Port B (high speed)
#define GPIO_PORTC_AHB_BASE     0x4005A000  // GPIO Port C (high speed)
#define GPIO_PORTD_AHB_BASE     0x4005B000  // GPIO Port D (high speed)
#define GPIO_PORTE_AHB_BASE     0x4005C000  // GPIO Port E (high speed)
#define GPIO_PORTF_AHB_BASE     0x4005D000  // GPIO Port F (high speed)
#define GPIO_PORTG_AHB_BASE     0x4005E000  // GPIO Port G (high speed)
#define GPIO_PORTH_AHB_BASE     0x4005F000  // GPIO Port H (high speed)
#define GPIO_PORTJ_AHB_BASE     0x40060000  // GPIO Port J (high speed)


//*****************************************************************************
//
// The following values define the bit field for the ui8Pins argument to
// several of the APIs.
//
//*****************************************************************************
#define GPIO_PIN_0              0x00000001  // GPIO pin 0
#define GPIO_PIN_1              0x00000002  // GPIO pin 1
#define GPIO_PIN_2              0x00000004  // GPIO pin 2
#define GPIO_PIN_3              0x00000008  // GPIO pin 3
#define GPIO_PIN_4              0x00000010  // GPIO pin 4
#define GPIO_PIN_5              0x00000020  // GPIO pin 5
#define GPIO_PIN_6              0x00000040  // GPIO pin 6
#define GPIO_PIN_7              0x00000080  // GPIO pin 7

//*****************************************************************************
//
// Values that can be passed to GPIODirModeSet as the ui32PinIO parameter, and
// returned from GPIODirModeGet.
//
//*****************************************************************************
#define GPIO_DIR_MODE_IN        0x00000000  // Pin is a GPIO input
#define GPIO_DIR_MODE_OUT       0x00000001  // Pin is a GPIO output
#define GPIO_DIR_MODE_HW        0x00000002  // Pin is a peripheral function

//*****************************************************************************
//
// Values that can be passed to GPIOIntTypeSet as the ui32IntType parameter,
// and returned from GPIOIntTypeGet.
//
//*****************************************************************************
#define GPIO_FALLING_EDGE       0x00000000  // Interrupt on falling edge
#define GPIO_RISING_EDGE        0x00000004  // Interrupt on rising edge
#define GPIO_BOTH_EDGES         0x00000001  // Interrupt on both edges
#define GPIO_LOW_LEVEL          0x00000002  // Interrupt on low level
#define GPIO_HIGH_LEVEL         0x00000006  // Interrupt on high level
#define GPIO_DISCRETE_INT       0x00010000  // Interrupt for individual pins

//*****************************************************************************
//
// Values that can be passed to GPIOPadConfigSet as the ui32Strength parameter,
// and returned by GPIOPadConfigGet in the *pui32Strength parameter.
//
//*****************************************************************************
#define GPIO_STRENGTH_2MA       0x00000001  // 2mA drive strength
#define GPIO_STRENGTH_4MA       0x00000002  // 4mA drive strength
#define GPIO_STRENGTH_6MA       0x00000065  // 6mA drive strength
#define GPIO_STRENGTH_8MA       0x00000066  // 8mA drive strength
#define GPIO_STRENGTH_8MA_SC    0x0000006E  // 8mA drive with slew rate control
#define GPIO_STRENGTH_10MA      0x00000075  // 10mA drive strength
#define GPIO_STRENGTH_12MA      0x00000077  // 12mA drive strength

//*****************************************************************************
//
// Values that can be passed to GPIOPadConfigSet as the ui32PadType parameter,
// and returned by GPIOPadConfigGet in the *pui32PadType parameter.
//
//*****************************************************************************
#define GPIO_PIN_TYPE_STD       0x00000008  // Push-pull
#define GPIO_PIN_TYPE_STD_WPU   0x0000000A  // Push-pull with weak pull-up
#define GPIO_PIN_TYPE_STD_WPD   0x0000000C  // Push-pull with weak pull-down
#define GPIO_PIN_TYPE_OD        0x00000009  // Open-drain
#define GPIO_PIN_TYPE_ANALOG    0x00000000  // Analog comparator
#define GPIO_PIN_TYPE_WAKE_HIGH 0x00000208  // Hibernate wake, high
#define GPIO_PIN_TYPE_WAKE_LOW  0x00000108  // Hibernate wake, low

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern errStat GPIO_DirModeSet(u32 ui32Port, u8 ui8Pins, u32 ui32PinIO);
extern errStat GPIO_PinRead(u32 ui32Port, u8 ui8Pins, u8* ui8Val);
extern errStat GPIO_PinWrite(u32 ui32Port, u8 ui8Pins, u8 ui8Val);
extern errStat GPIO_PadConfigSet(u32 ui32Port, u8 ui8Pins,u32 ui32Strength, u32 ui32PinType);

#endif
