# MIDI 2 SERIAL 2 ESP

## Dependancies
 - curl
 - make

## Compilation

 > This is currently setup to compile to an esp8266 nodemcu board from Expressif system.
    If you plan on using this board you can skip this step.

To configure the board edit the Makefile variable `BOARD_PACKAGE` `BOARD` and `BOARD_TARGET` (any file from the board package).
Add any required board manager url in `arduino-cli.yaml`.

```bash
make
```

*Note*: The build system, libraries and any dependancies are fetch automatically.

## Flash board
Configuure the destination COM port in the Makefile. `PORT=/dev/ttyUSB0`

```bash
make upload
```
*Note*: You might want to prefix this with `sudo` on some systems

