NAME=midi2serial2esp
MAIN=$(NAME).ino
SRC=$(MAIN) $(wildcard ./src/*)

DEPS_DIR=./bin
ARDUINO_DIR=./.arduino
BUILD_DIR=./build
CACHE_DIR=$(BUILD_DIR)/cache

BIN=$(BUILD_DIR)/$(MAIN).bin

INO=$(DEPS_DIR)/arduino-cli
INOFLAGS=--board arduino:avr:uno --port /dev/ttyACM0 --pref build.path=./build

BOARD_PACKAGE=esp8266:esp8266
BOARD=$(BOARD_PACKAGE):nodemcuv2
BOARDS_TARGET=$(ARDUINO_DIR)/data/package_esp8266com_index.json

LIBS_TARGET=$(ARDUINO_DIR)/data/library_index.json

FASTLED_TARGET=$(ARDUINO_DIR)/user/libraries/FastLED/src/FastLED.h

# If uploading from WSL, follow this tutorial:
# https://docs.microsoft.com/en-us/windows/wsl/connect-usb
PORT=/dev/ttyUSB0


$(BIN): deps $(SRC)
	$(INO) compile -b $(BOARD) --build-cache-path $(CACHE_DIR) --build-path $(BUILD_DIR) --warnings more .

upload: deps $(BIN)
	$(INO) upload -v -b $(BOARD) --input-dir $(BUILD_DIR) -t -p $(PORT)

$(INO):
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

$(BOARDS_TARGET): $(INO)
	$(INO) core update-index 
	$(INO) core install $(BOARD_PACKAGE) -v


$(LIBS_TARGET): $(INO) arduino-cli.yaml
	$(INO) lib update-index

$(FASTLED_TARGET): $(INO) $(LIBS_TARGET)
	$(INO) lib install FastLED -v

deps: $(INO) $(BOARDS_TARGET) $(LIBS_TARGET) $(FASTLED_TARGET)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(DEPS_DIR)
	rm -rf $(ARDUINO_DIR)
