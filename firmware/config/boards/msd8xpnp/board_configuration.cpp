/**
 * @file boards/msd8xpnp/board_configuration.cpp
 *
 * @brief Configuration defaults for the msd8xpnp board
 *
 * @author Tyler Browning, (c) 2024
 */

#include "pch.h"
#include "msd8xpnp_meta.h"

static const brain_pin_e injPins[] = {
  Gpio::msd8xpnp_LS_1,
	Gpio::msd8xpnp_LS_2,
	Gpio::msd8xpnp_LS_3,
	Gpio::msd8xpnp_LS_4,
	Gpio::msd8xpnp_LS_5,
	Gpio::msd8xpnp_LS_6,
	Gpio::msd8xpnp_LS_7,
	Gpio::msd8xpnp_LS_8,
	Gpio::msd8xpnp_LS_9,
	Gpio::msd8xpnp_LS_10,
	Gpio::msd8xpnp_LS_11,
	Gpio::msd8xpnp_LS_12
};

static const brain_pin_e ignPins[] = {
	Gpio::msd8xpnp_IGN_1,
	Gpio::msd8xpnp_IGN_2,
	Gpio::msd8xpnp_IGN_3,
	Gpio::msd8xpnp_IGN_4,
	Gpio::msd8xpnp_IGN_5,
	Gpio::msd8xpnp_IGN_6,
	Gpio::msd8xpnp_IGN_7,
	Gpio::msd8xpnp_IGN_8,
	Gpio::msd8xpnp_IGN_9,
	Gpio::msd8xpnp_IGN_10,
	Gpio::msd8xpnp_IGN_11,
	Gpio::msd8xpnp_IGN_12,
};

static void setInjectorPins() {
	copyArray(engineConfiguration->injectionPins, injPins);
}

static void setIgnitionPins() {
	copyArray(engineConfiguration->ignitionPins, ignPins);
}

// PE3 is error LED, configured in board.mk
Gpio getCommsLedPin() {
	return Gpio::E4;
}

Gpio getRunningLedPin() {
	return Gpio::E5;
}

Gpio getWarningLedPin() {
	return Gpio::E6;
}

static void setupVbatt() {
	// 5.6k high side/10k low side = 1.56 ratio divider
	engineConfiguration->analogInputDividerCoefficient = 1.56f;

	// 82k high side/10k low side = 9.2
	engineConfiguration->vbattDividerCoeff = (92.0f / 10.0f);

	// Battery sense on PA7
	engineConfiguration->vbattAdcChannel = EFI_ADC_7;

	engineConfiguration->adcVcc = 3.3f;
}

static void setupEtb() {
	// TLE9201 driver
	// This chip has three control pins:
	// DIR - sets direction of the motor
	// PWM - pwm control (enable high, coast low)
	// DIS - disables motor (enable low)

	// Throttle #1
	// PWM pin
	engineConfiguration->etbIo[0].controlPin = Gpio::D12;
	// DIR pin
	engineConfiguration->etbIo[0].directionPin1 = Gpio::D10;
	// Disable pin
	engineConfiguration->etbIo[0].disablePin = Gpio::D11;

	// Throttle #2
	// PWM pin
	engineConfiguration->etbIo[1].controlPin = Gpio::D13;
	// DIR pin
	engineConfiguration->etbIo[1].directionPin1 = Gpio::D9;
	// Disable pin
	engineConfiguration->etbIo[1].disablePin = Gpio::D8;

	// we only have pwm/dir, no dira/dirb
	engineConfiguration->etb_use_two_wires = false;
}

static void setupDefaultSensorInputs() {
	// trigger inputs
	// Digital channel 1 as default - others not set
	engineConfiguration->triggerInputPins[0] = msd8xpnp_DIGITAL_1;
	engineConfiguration->camInputs[0] = Gpio::Unassigned;

	engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;


	engineConfiguration->clt.adcChannel = msd8xpnp_IN_CLT;
	engineConfiguration->iat.adcChannel = msd8xpnp_IN_IAT;
	engineConfiguration->tps1_1AdcChannel = msd8xpnp_IN_TPS;
	engineConfiguration->map.sensor.hwChannel = msd8xpnp_IN_MAP;

    // see also enableAemXSeries
	// pin #28 WBO AFR "Analog Volt 10"
	engineConfiguration->afr.hwChannel = msd8xpnp_IN_ANALOG_VOLT_10;
}

static void setupSdCard() {
	engineConfiguration->sdCardSpiDevice = SPI_DEVICE_3;
	engineConfiguration->sdCardCsPin = Gpio::D2;

	engineConfiguration->is_enabled_spi_3 = true;
	engineConfiguration->spi3sckPin = Gpio::C10;
	engineConfiguration->spi3misoPin = Gpio::C11;
	engineConfiguration->spi3mosiPin = Gpio::C12;

	engineConfiguration->is_enabled_spi_5 = true;
	engineConfiguration->spi5sckPin = Gpio::F7;
	engineConfiguration->spi5misoPin = Gpio::F8;
	engineConfiguration->spi5mosiPin = Gpio::F9;
}

void setBoardConfigOverrides() {
	setupSdCard();
	setupVbatt();

	engineConfiguration->clt.config.bias_resistor = msd8xpnp_DEFAULT_AT_PULLUP;
	engineConfiguration->iat.config.bias_resistor = msd8xpnp_DEFAULT_AT_PULLUP;

	engineConfiguration->canTxPin = Gpio::D1;
	engineConfiguration->canRxPin = Gpio::D0;

#if defined(STM32F4) || defined(STM32F7)
	engineConfiguration->can2RxPin = Gpio::B12;
	engineConfiguration->can2TxPin = Gpio::B13;
#endif

	engineConfiguration->lps25BaroSensorScl = Gpio::B10;
	engineConfiguration->lps25BaroSensorSda = Gpio::B11;
}

/**
 * @brief   Board-specific configuration defaults.
 *
 * See also setDefaultEngineConfiguration
 *

 */
void setBoardDefaultConfiguration() {
	setInjectorPins();
	setIgnitionPins();
	setupEtb();

	engineConfiguration->isSdCardEnabled = true;

	// "required" hardware is done - set some reasonable defaults
	setupDefaultSensorInputs();

	engineConfiguration->enableSoftwareKnock = true;

#if HW_msd8xpnp & EFI_PROD_CODE
	engineConfiguration->mainRelayPin = Gpio::msd8xpnp_LS_12;
	engineConfiguration->fanPin = Gpio::msd8xpnp_LS_11;
	engineConfiguration->fuelPumpPin = Gpio::msd8xpnp_LS_10;
#endif // HW_msd8xpnp

	// If we're running as hardware CI, borrow a few extra pins for that
#ifdef HARDWARE_CI
	engineConfiguration->triggerSimulatorPins[0] = Gpio::G3;
	engineConfiguration->triggerSimulatorPins[1] = Gpio::G2;
#endif
}

void boardPrepareForStop() {
	// Wake on the CAN RX pin
	palEnableLineEvent(PAL_LINE(GPIOD, 0), PAL_EVENT_MODE_RISING_EDGE);
}

#if HW_msd8xpnp
static Gpio msd8xpnp_N54_OUTPUTS[] = {
  Gpio::msd8xpnp_LS_1, // inj 1
  Gpio::msd8xpnp_LS_2, // inj 2
  Gpio::msd8xpnp_LS_3, // inj 3
  Gpio::msd8xpnp_LS_4, // inj 4
  Gpio::msd8xpnp_LS_5, // inj 5
  Gpio::msd8xpnp_LS_6, // inj 6
  Gpio::msd8xpnp_LS_14, // starter control or aux output
  Gpio::msd8xpnp_LS_15, // radiator fan relay output white

  Gpio::msd8xpnp_IGN_1, // ign 1
	Gpio::msd8xpnp_IGN_2, // ign 2
  Gpio::msd8xpnp_IGN_3, // ign 3
  Gpio::msd8xpnp_IGN_4, // ign 4
  Gpio::msd8xpnp_IGN_5, // ign 5
  Gpio::msd8xpnp_IGN_6, // ign 6

  //Gpio::msd8xpnp_LS_13, // main relay
  //Gpio::msd8xpnp_LS_16, // main relay
};

int getBoardMetaLowSideOutputsCount() {
    if (engineConfiguration->engineType == engine_type_e::msd8xpnp_BMW_N54) {
        return getBoardMetaOutputsCount();
    }
    return 16;
}

static Gpio msd8xpnp_OUTPUTS[] = {
Gpio::msd8xpnp_LS_1,
Gpio::msd8xpnp_LS_2,
Gpio::msd8xpnp_LS_3,
Gpio::msd8xpnp_LS_4,
Gpio::msd8xpnp_LS_5,
Gpio::msd8xpnp_LS_6,
Gpio::msd8xpnp_LS_7,
Gpio::msd8xpnp_LS_8,
Gpio::msd8xpnp_LS_9,
Gpio::msd8xpnp_LS_10,
Gpio::msd8xpnp_LS_11,
Gpio::msd8xpnp_LS_12,
Gpio::msd8xpnp_LS_13,
Gpio::msd8xpnp_LS_14,
Gpio::msd8xpnp_LS_15,
Gpio::msd8xpnp_LS_16,
	Gpio::msd8xpnp_IGN_1,
	Gpio::msd8xpnp_IGN_2,
	Gpio::msd8xpnp_IGN_3,
	Gpio::msd8xpnp_IGN_4,
	Gpio::msd8xpnp_IGN_5,
	Gpio::msd8xpnp_IGN_6,
	Gpio::msd8xpnp_IGN_7,
	Gpio::msd8xpnp_IGN_8,
	Gpio::msd8xpnp_IGN_9,
	Gpio::msd8xpnp_IGN_10,
	Gpio::msd8xpnp_IGN_11,
	Gpio::msd8xpnp_IGN_12,
	Gpio::msd8xpnp_HS_1,
	Gpio::msd8xpnp_HS_2,
	Gpio::msd8xpnp_HS_3,
	Gpio::msd8xpnp_HS_4
};

int getBoardMetaOutputsCount() {
    if (engineConfiguration->engineType == engine_type_e::msd8xpnp_BMW_N54) {
      return efi::size(msd8xpnp_N54_OUTPUTS);
  }
    return efi::size(msd8xpnp_OUTPUTS);
}

int getBoardMetaDcOutputsCount() {
    if (engineConfiguration->engineType == engine_type_e::msd8xpnp_BMW_N54) {
        return 1;
/*    return 2; msd8xpnp has two h-bridges but stim board is short on channels to test :( */
}

Gpio* getBoardMetaOutputs() {
    if (engineConfiguration->engineType == engine_type_e::msd8xpnp_BMW_N54) {
        return msd8xpnp_N54_OUTPUTS;
    }
    return msd8xpnp_OUTPUTS;
}
#endif // HW_msd8xpnp