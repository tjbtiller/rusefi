
BOARDCPPSRC = $(BOARD_DIR)/board_configuration.cpp

DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::C11

# No USB
DDEFS += -DEFI_USB_SERIAL=FALSE

# We're running on TDG PDM hardware!
DDEFS += -DHW_TDG_PDM8=1

DDEFS += -DSTATIC_BOARD_ID=STATIC_BOARD_ID_TDG_PDM8
DDEFS += -DFIRMWARE_ID=\"tdg-pdm8\"
DDEFS += -DDEFAULT_ENGINE_TYPE=engine_type_e::MINIMAL_PINS
