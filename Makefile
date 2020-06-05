######## CONFIGURATION ########

# Board
avrType=atmega32u4
clibtype=__AVR_ATmega32U4__

# CPU clock speed
avrFreq=16000000

# Linux port
programmerDev=/dev/ttyACM*

# Other
baud=57600
commsBaud=9600
programmerType=avr109
CXX=avr-g++

###### END CONFIGURATION ######

CPPFLAGS=-DF_CPU=$(avrFreq) -D $(clibtype) -mmcu=$(avrType) -Iinclude -DBAUD=$(commsBaud) -std=c++11  -g -Os -w  -fdata-sections -MMD -flto
LINKFLAGS=-w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=$(avrType) -Iinclude -std=c++11 -DF_CPU=$(avrFreq)
# -Wall -Werror -Wextra 
objects=$(patsubst %.cc,%.o,$(wildcard *.cc)) stdavr/**/*.cc

.PHONY: flash clean

all: build/main.hex

%.o: %.c
	$(CXX) $(CPPFLAGS) -c $< -o $@

build/main.elf: $(objects)
	$(CXX) $(LINKFLAGS) -o $@ $^ 

build/main.hex: build/main.elf
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $^ $@.eep
	avr-objcopy -O ihex -R .eeprom $^ $@

flash: build/main.hex

	@echo "Requesting sudo access"
	@sudo echo "Done"
	
	@echo "Please reset your chip"
	until  ls /dev/tty* | grep ACM ; do sleep 0.5; done

	# sleep 2
	# sudo python2 bootloader.py $(programmerDev)
	
	# sudo stty -F $(programmerDev) speed 1200
	# sudo stty -F $(programmerDev) speed $(baud)

	sleep 2
	avr-size -A build/main.elf
	sudo avrdude -p$(avrType) -c$(programmerType) -P $(programmerDev) -b$(baud) -v -U flash:w:$<:i -U eeprom:w:$<.eep

clean:
	rm -f build/*

connect:
	@echo "Requesting sudo access"
	@sudo echo "Done"
	
	@echo "Please reset your chip"
	until  ls /dev/tty* | grep ACM ; do sleep 0.5; done

	sudo screen $(programmerDev) $(commsBaud)

finddevices:
	ls /dev/ttyACM*