ARDUINO_BINDIR=~/.local/bin
INO := $(shell command -v arduino-cli 2> /dev/null)

FASTLED_FLAGS=-Wno-register -Wno-deprecated-declarations -Wno-misleading-indentation

COMPILE_FLAGS=--profile esp8266 \
	--export-binaries \
	--warnings more \
	--build-property "compiler.cpp.extra_flags=\"$(FASTLED_FLAGS)\"" \
	--build-property "build.extra_flags=\"-I$(CURDIR)/../include\""


ELF=build/esp8266.esp8266.generic/remote.ino.elf

$(ELF): install_arduino $(SRC) $(LIBS)
	$(INO) compile $(COMPILE_FLAGS) .

.PHONY: upload
upload: install_arduino $(ELF)
	scp -R build/esp8266.esp8266.generic/* usbpi.local:/tmp/esp8266_remote_build
	ssh usbpi.local -- "cd midi2serial2esp && sudo ./bin/arduino-cli --config-file arduino-cli.yaml upload -b esp8266:esp8266:generic --verify --port /dev/ttyUSB0 --input-file /tmp/esp8266_remote_build/remote.ino.elf"

.PHONY: serial-monitor
serial-monitor:
	ssh usbpi.local -- "cd midi2serial2esp && sudo ./bin/arduino-cli --config-file arduino-cli.yaml monitor -c baudrate=115200 --port /dev/ttyUSB0 --fqbn esp8266:esp8266:generic"


.PHONY: install_arduino
install_arduino:
ifndef INO
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=$(ARDUINO_BINDIR) sh
	@echo "arduino-cli has been installed to $(ARDUINO_BINDIR). Add it to your path or edit \`ARDUINO_BINDIR\`."
endif

