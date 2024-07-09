ARDUINO_BINDIR=~/.local/bin
INO := $(shell command -v arduino-cli 2> /dev/null)

WSSID = ${WIFI_SSID}
WPASS = ${WIFI_PASS}

FASTLED_FLAGS:=-Wno-register -Wno-deprecated-declarations -Wno-misleading-indentation \
	-DWIFI_SSID=$(WSSID) \
	-DWIFI_PASS=$(WPASS)

COMPILE_FLAGS=\
	--export-binaries \
	--warnings more \
	--build-property compiler.cpp.extra_flags='$(FASTLED_FLAGS)' \
	--build-property build.extra_flags='-I$(CURDIR)/../include' \


ELF=build/esp8266.esp8266.generic/remote.ino.elf

$(ELF): install_arduino $(SRC) $(LIBS)
	$(INO) compile $(COMPILE_FLAGS) .

.PHONY: upload
upload: $(ELF)
	# rsync -auv build/esp8266.esp8266.generic/* usbpi.local:/tmp/esp8266_remote_build
	# ssh usbpi.local -- "cd midi2serial2esp/remote && ~/.local/bin/arduino-cli upload --verify --input-dir /tmp/esp8266_remote_build"
	$(INO) upload --verify # --input-file $(ELF)

ota: $(ELF)
	$(INO) upload --verify --protocol network --port "$(PORT)"

.PHONY: install_arduino
install_arduino:
ifndef INO
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=$(ARDUINO_BINDIR) sh -s nightly-latest
	arduino-cli lib update-index
	@echo "arduino-cli has been installed to $(ARDUINO_BINDIR). Add it to your path or edit \`ARDUINO_BINDIR\`."
endif

