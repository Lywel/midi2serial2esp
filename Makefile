# If uploading from WSL, follow this tutorial:
# https://docs.microsoft.com/en-us/windows/wsl/connect-usb
PORT=/dev/ttyUSB0

SHARED_SRC=$(wildcard src/shared/*)
MASTER_SRC=$(wildcard src/master/*)
SLAVE_SRC=$(wildcard src/slave/*)

CLI_CONFIG=arduino-cli.yaml

DEPS_DIR=bin
ARDUINO_DIR=.arduino
ARDUINO_LIBS_DIR=$(ARDUINO_DIR)/user/libraries
INO=$(DEPS_DIR)/arduino-cli --config-file $(CLI_CONFIG)
BOARDS_TARGET=$(ARDUINO_DIR)/data/package_esp8266com_index.json
LIBS_TARGET=$(ARDUINO_DIR)/data/library_index.json
MIDI_TARGET=$(ARDUINO_LIBS_DIR)/MIDI_Library/CMakeLists.txt
FASTLED_TARGET=$(ARDUINO_LIBS_DIR)/FastLED/library.json

BOARD_PACKAGE=esp8266:esp8266

MASTER_BOARD=$(BOARD_PACKAGE):nodemcuv2
SLAVE_BOARD=$(BOARD_PACKAGE):generic

MASTER_BUILD_PATH=src/master/build
SLAVE_BUILD_PATH=src/slave/build
MASTER_CACHE_DIR=$(MASTER_BUILD_PATH)/cache
SLAVE_CACHE_DIR=$(SLAVE_BUILD_PATH)/cache

FASTLED_FLAGS=-Wno-register \
	-Wno-deprecated-declarations \
	-Wno-misleading-indentation

COMMON_FLAGS=--library src/shared --warnings more

MASTER_FLAGS=$(COMMON_FLAGS) \
	--build-path=$(MASTER_BUILD_PATH) \
	--build-cache-path=$(MASTER_CACHE_DIR) \
	--build-property compiler.cpp.extra_flags='$(FASTLED_FLAGS)'

SLAVE_FLAGS=$(COMMON_FLAGS) \
	--build-path=$(SLAVE_BUILD_PATH) \
	--build-cache-path=$(SLAVE_CACHE_DIR) \
	--build-property compiler.cpp.extra_flags='$(FASTLED_FLAGS)'

MASTER_BUILD_TARGET=$(MASTER_BUILD_PATH)/master.ino.elf
SLAVE_BUILD_TARGET=$(SLAVE_BUILD_PATH)/slave.ino.elf

DEPS_TARGETS=$(BOARDS_TARGET) $(MIDI_TARGET) $(FASTLED_TARGET)



# Compile only
.PHONY: all
all: $(MASTER_BUILD_TARGET) $(SLAVE_BUILD_TARGET)

$(MASTER_BUILD_TARGET): $(MASTER_SRC) $(SHARED_SRC) $(DEPS_TARGETS)
	$(INO) compile -b $(MASTER_BOARD) $(MASTER_FLAGS) src/master

$(SLAVE_BUILD_TARGET): $(SLAVE_SRC) $(SHARED_SRC) $(DEPS_TARGETS)
	$(INO) compile -b $(SLAVE_BOARD) $(SLAVE_FLAGS) src/slave


# Upload
.PHONY: master
master: $(MASTER_BUILD_TARGET)
	$(INO) upload -b $(MASTER_BOARD) --input-dir $(MASTER_BUILD_PATH) -tp $(PORT) src/master

.PHONY: slave
slave: $(SLAVE_BUILD_TARGET)
	$(INO) upload -b $(SLAVE_BOARD) --input-dir $(SLAVE_BUILD_PATH) -tp $(PORT) src/slave


# Build dependancies

$(INO):
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

$(BOARDS_TARGET): $(INO)
	$(INO) core update-index 
	$(INO) core install $(BOARD_PACKAGE)

$(LIBS_TARGET): $(INO) arduino-cli.yaml
	$(INO) lib update-index

$(MIDI_TARGET): $(INO) $(LIBS_TARGET)
	$(INO) lib install "MIDI Library"

$(FASTLED_TARGET): $(INO) $(LIBS_TARGET)
	$(INO) lib install "FastLED"

.PHONY: clean
clean:
	rm -rf $(MASTER_BUILD_PATH)
	rm -rf $(SLAVE_BUILD_PATH)
	rm -rf $(DEPS_DIR)
	rm -rf $(ARDUINO_DIR)
