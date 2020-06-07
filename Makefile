######## CONFIGURATION ########

# Board
avrType=atmega32u4
clibtype=__AVR_ATmega32U4__

# CPU clock speed
avrFreq=16000000

# Linux ports
programmerDev=/dev/ttyACM*
serialDev=/dev/ttyUSB*

# Other
baud=57600
commsBaud=9600
programmerType=avr109
CXX=avr-g++

###### END CONFIGURATION ######

common_flags=-DMILLIS_TIMER=1 -mmcu=$(avrType) -Iinclude -Iapplication/include -std=c++11  -DF_CPU=$(avrFreq) -w -Os -g -flto -DBAUD=$(commsBaud)
CPPFLAGS=-D $(clibtype)   -std=c++11 -lang-c++  -fdata-sections -MMD $(common_flags)
ASMFLAGS=-x assembler-with-cpp
LINKFLAGS= -fuse-linker-plugin -Wl,--gc-sections  $(common_flags)
# -Wall -Werror -Wextra 
objects=$(patsubst %.cc,%.o,$(wildcard *.cc)) os32u4/**/*.cc application/*.cc vendor/**/*.cc
sobjects= os32u4/**/*.s

.PHONY: flash clean

all: build/main.hex

%.o: %.cc
	$(CXX) $(CPPFLAGS) -c $< -o $@

%.o: %.s
	$(CXX) $(CPPFLAGS) $(ASMFLAGS) -c $< -o $@

build/main.elf: $(objects)
	$(CXX) $(LINKFLAGS) -o $@ $^ 

build/main.hex: build/main.elf
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $^ $@.eep
	avr-objcopy -O ihex -R .eeprom $^ $@

flash: build/main.hex

	@echo "Requesting sudo access"
	@sudo echo "Done"
	
	@echo "Please reset your chip"
	until  ls $(programmerDev) 2> /dev/null; do sleep 0.5; done

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
	until  ls $(serialDev) 2> /dev/null; do sleep 0.5; done

	sudo screen $(serialDev) $(commsBaud)

finddevices:
	ls /dev/ttyACM*