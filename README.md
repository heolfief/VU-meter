# VU-meter

## Table of contents

- [Description](#description)
- [Hardware](#hardware)
- [Software](#software)
- [Copyright and license](#copyright-and-license)


## Description
This project is an AVR based LED VU-meter. It's display consists of 80 LEDs per audio channel. Each PCB holds all the LEDs, the analog and digital segments of the circuit and only handle one audio channel. That way you can build a stereo VU-meter just by using two instances of this circuit (which can be mechanically stacked together). Each audio channel will be completely separated and computed separately by the AVR microcontroller on each PCB.

### Video demo

[![](https://github.com/heolfief/VU-meter/blob/master/docs/vid_thumbnail.jpg)](http://www.youtube.com/watch?v=NpEaa2P7qZI "VU-meter in action")

## Hardware
The hardware is based on 3 main components:
- ATmega328p AVR microcontroller
- MCP6004 quad op-amp
- 74HC595 shift-registers for extended MCU outputs

This board runs on 5V DC power and should not exceed 500mA of current draw (All LEDs lit up).
A stabilized power supply is needed in order to provide clean power to the analog circuit.

### Documents available

- <a target="_blank" href="https://github.com/heolfief/VU-meter/blob/master/Hardware/Schematics.pdf">Schematics (PDF)</a>
- <a target="_blank" href="https://github.com/heolfief/VU-meter/blob/master/Hardware/BOM.pdf">Bill of materials (PDF)</a>
- <a target="_blank" href="https://github.com/heolfief/VU-meter/blob/master/Hardware/CAD/Eagle%20files">Autodesk Eagle CAD files</a>
- <a href="https://github.com/heolfief/VU-meter/tree/master/Hardware/CAD/GerberFiles">Gerber files</a>


## Software
The Firmware for the AVR microcontroller is written in C.

- IDE : Atmel Studio 7.0 (can be opened in MPLAB X)
- Compiler : avr-gcc

### Documents available

- <a target="_blank" href="https://heolfief.github.io/VU-meter/">Code documentation (doxygen)</a>

## Copyright and license
heolfief/VU-meter is licensed under the GNU General Public License v3.0.

See the <a target="_blank" href="https://github.com/heolfief/VU-meter/blob/master/LICENSE">LICENSE file</a> for more information.
