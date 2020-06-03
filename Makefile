######## CONFIGURATION ########

# Board
avrType=atmega32u4

# CPU clock speed
avrFreq=8000000 # 16 Mhz

# Linux port
programmerDev=/dev/ttyACM*

# Other
baud=57600
commsBaud=9600
programmerType=avr109
CXX=avr-g++

###### END CONFIGURATION ######

CPPFLAGS=-DF_CPU=$(avrFreq) -mmcu=$(avrType) -Iinclude -std=c++11
# -Wall -Werror -Wextra 
objects=$(patsubst %.cc,%.o,$(wildcard *.cc)) stdavr/**/*.cc

.PHONY: flash clean

all: build/main.hex

%.o: %.c
	$(CXX) $(CPPFLAGS) -c $< -o $@

build/main.elf: $(objects)
	$(CXX) $(CPPFLAGS) -o $@ $^ 

build/main.hex: build/main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@

flash: build/main.hex
	sudo systemctl stop ModemManager.service

	python2 bootloader.py $(programmerDev)
	
	# sudo stty -F $(programmerDev) speed 1200
	# sudo stty -F $(programmerDev) speed $(baud)

	sleep 2
	sudo avrdude -p$(avrType) -c$(programmerType) -P $(programmerDev) -b$(baud) -v -D -U flash:w:$<:i

clean:
	rm -f build/*

connect:
	screen $(programmerDev) $(commsBaud)

finddevices:
	ls /dev/ttyACM*