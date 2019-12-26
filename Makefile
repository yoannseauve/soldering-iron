AVR_LOCATION = /usr/bin
AVRDUDE_LOCATION = /usr/bin
//ARD_RESET_SCRIPT = /home/galileo/arduino/Arduino-Makefile/bin/ard-reset-arduino

include configuration


SRC = $(wildcard src/*.c)
OBJ_wrong_dir = $(SRC:.c=.o)
OBJ = $(foreach f,$(OBJ_wrong_dir),obj/$(notdir $(f)))
BUILD_LOCATION = build_$(BOARD_TAG)

.PHONY: clean upload

ALL:make_folders $(PROJECT_NAME)


obj/%.o: src/%.c
	#$(AVR_LOCATION)/avr-gcc -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DARDUINO=$(ARDUINO_VERSION) -D__PROG_TYPES_COMPAT -Wall -ffunction-sections -fdata-sections -Os -std=gnu11 -flto -fno-fat-lto-objects -c $< -o $@ -MD -I src/
	#$(AVR_LOCATION)/avr-gcc -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DARDUINO=$(ARDUINO_VERSION) -D__PROG_TYPES_COMPAT -Wall -ffunction-sections -fdata-sections -Os -std=gnu11 -flto -c $< -o $@ -MD -I src/
	$(AVR_LOCATION)/avr-gcc -mmcu=$(MCU) -DF_CPU=$(F_CPU) -D__PROG_TYPES_COMPAT -Wall -ffunction-sections -fdata-sections -Os -std=gnu11 -flto -c $< -o $@ -MD -I src/

$(PROJECT_NAME): ${OBJ}
	#$(AVR_LOCATION)/avr-gcc -mmcu=$(MCU) -Wl,--gc-sections -Os -flto -fuse-linker-plugin -o $(BUILD_LOCATION)/$@.elf $(OBJ)
	$(AVR_LOCATION)/avr-gcc -mmcu=$(MCU) -Wl,--gc-sections -Os -flto -o $(BUILD_LOCATION)/$@.elf $(OBJ)
	$(AVR_LOCATION)/avr-objcopy -O ihex -R .eeprom $(BUILD_LOCATION)/$@.elf $(BUILD_LOCATION)/$@.hex
	$(AVR_LOCATION)/avr-size --mcu=$(MCU) -C --format=avr $(BUILD_LOCATION)/$(PROJECT_NAME).elf

make_folders:
	mkdir -p obj 
	mkdir -p $(BUILD_LOCATION) 

clean:
	@ rm -rf obj
	@ rm -rf $(BUILD_LOCATION)


-include obj/*.d

upload:
ifeq ($(wildcard $(ARDUINO_PORT)),)
	$(error Impossible to find the arduino port $(ARDUINO_PORT))
endif
	#$(MAKE) reset
	$(AVRDUDE_LOCATION)/avrdude -C /etc/avrdude.conf -p $(MCU) -carduino -P $(ARDUINO_PORT) -b $(AVRDUDE_ARD_BAUDRATE) -U flash:w:$(BUILD_LOCATION)/$(PROJECT_NAME).hex:i

upload_asp:
	$(AVRDUDE_LOCATION)/avrdude -c usbasp -p $(MCU) -U flash:w:$(BUILD_LOCATION)/$(PROJECT_NAME).hex


reset:
	#$(ARD_RESET_SCRIPT) $(ARDUINO_PORT)
	echo -a "a" > $(ARDUINO_PORT)
