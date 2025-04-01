/*
 * msd8xpnp_meta.h
 *
 * @date Oct 2, 2021
 * @author Andrey Belomutskiy, (c) 2012-2021
 */

#pragma once

// not directly related but often used together
#include "defaults.h"

#define msd8xpnp_DEFAULT_AT_PULLUP 2700

#define msd8xpnp_LS_1 D7
// pin 15/black35
#define msd8xpnp_LS_2 G9

// pin 4/black35
#define msd8xpnp_LS_3 G10

// pin 16/black35
#define msd8xpnp_LS_4 G11

// pin 5/black35
#define msd8xpnp_LS_5 G12

// pin 6/black35
#define msd8xpnp_LS_6 G13

// pin 7/black35
#define msd8xpnp_LS_7 G14
#define msd8xpnp_LS_8 B4
#define msd8xpnp_LS_9 B5

// pin 20/black35
#define msd8xpnp_LS_10 B6
#define msd8xpnp_LS_11 B7
#define msd8xpnp_LS_12 B8

// pin 10/black35
#define msd8xpnp_LS_13 B9
// pin 11/black35
#define msd8xpnp_LS_14 E0
// pin 12/black35
#define msd8xpnp_LS_15 E1
// pin 23/black35
#define msd8xpnp_LS_16 E2


// pin 2/black35
#define msd8xpnp_HS_1 A9

// pin 1/black35
#define msd8xpnp_HS_2 A8

#define msd8xpnp_HS_3 D15

#define msd8xpnp_HS_4 D14

// pin 35/black35
#define msd8xpnp_IGN_1 D4

// pin 34/black35
#define msd8xpnp_IGN_2 D3

// pin 22/black35
#define msd8xpnp_IGN_3 C9
#define msd8xpnp_IGN_4 C8
#define msd8xpnp_IGN_5 C7
#define msd8xpnp_IGN_6 G8
#define msd8xpnp_IGN_7 G7
#define msd8xpnp_IGN_8 G6
#define msd8xpnp_IGN_9 G5
#define msd8xpnp_IGN_10 G4
#define msd8xpnp_IGN_11 G3
#define msd8xpnp_IGN_12 G2

// Analog Temp 1 = PC4
#define msd8xpnp_IN_ANALOG_TEMP_1 EFI_ADC_14

// IAT = Analog Temp 2 = PC5
#define msd8xpnp_IN_ANALOG_TEMP_2 EFI_ADC_15
#define msd8xpnp_IN_IAT msd8xpnp_IN_ANALOG_TEMP_2

// CLT = Analog Temp 3 = PB0
#define msd8xpnp_IN_ANALOG_TEMP_3 EFI_ADC_8
#define msd8xpnp_IN_CLT msd8xpnp_IN_ANALOG_TEMP_3

// Analog Temp 4 = PB1
#define msd8xpnp_IN_ANALOG_TEMP_4 EFI_ADC_9

// MAP = Analog volt 1 = PC0
#define msd8xpnp_IN_ANALOG_VOLT_1 EFI_ADC_10
#define msd8xpnp_IN_MAP msd8xpnp_IN_ANALOG_VOLT_1

// TPS = Analog volt 2 = PC1
#define msd8xpnp_IN_ANALOG_VOLT_2 EFI_ADC_11
#define msd8xpnp_IN_TPS msd8xpnp_IN_ANALOG_VOLT_2

// PC2
#define msd8xpnp_IN_ANALOG_VOLT_3 EFI_ADC_12
#define msd8xpnp_IN_TPS1_2 msd8xpnp_IN_ANALOG_VOLT_3

// PC3
#define msd8xpnp_IN_ANALOG_VOLT_4 EFI_ADC_13
#define msd8xpnp_IN_TPS2_1 msd8xpnp_IN_ANALOG_VOLT_4

// PA0
#define msd8xpnp_IN_ANALOG_VOLT_5 EFI_ADC_0

// PA1
#define msd8xpnp_IN_ANALOG_VOLT_6 EFI_ADC_1
#define msd8xpnp_IN_AV_6_DIGITAL Gpio::A1

// PA2
#define msd8xpnp_IN_ANALOG_VOLT_7 EFI_ADC_2
#define msd8xpnp_IN_PPS2 msd8xpnp_IN_ANALOG_VOLT_7

// PA3
#define msd8xpnp_IN_ANALOG_VOLT_8 EFI_ADC_3
#define msd8xpnp_IN_AV_8_DIGITAL Gpio::A3

// PA4
#define msd8xpnp_IN_ANALOG_VOLT_9 EFI_ADC_4
#define msd8xpnp_IN_PPS msd8xpnp_IN_ANALOG_VOLT_9

// PA5
#define msd8xpnp_IN_ANALOG_VOLT_10 EFI_ADC_5
#define msd8xpnp_IN_AV_10_DIGITAL Gpio::A5

// PA6
#define msd8xpnp_IN_ANALOG_VOLT_11 EFI_ADC_6
#define msd8xpnp_IN_AV_11_DIGITAL Gpio::A6

#define msd8xpnp_VR_1 Gpio::E7
#define msd8xpnp_VR_2 Gpio::E8

#define msd8xpnp_DIGITAL_1 Gpio::C6
#define msd8xpnp_DIGITAL_2 Gpio::E11
#define msd8xpnp_DIGITAL_3 Gpio::E12
#define msd8xpnp_DIGITAL_4 Gpio::E14
#define msd8xpnp_DIGITAL_5 Gpio::E13
#define msd8xpnp_DIGITAL_6 Gpio::E15

void setmsd8xpnpEtbIO();
