# Railway Crossing

The railway model in Zusebau room 2045 should be extended by a Crossing Gate. The gate will be operated by a servo motor, a train has to be detected by sensors before and after the crossing. The gate should be open when no train is in the area, the gate should be closed as soon as a train is on or near the crossing. Under no circumstances can the gate be open while a train is passing. Think about the right set of sensors to assure this requirement. During this task, modifications to the railway model are not allowed or needed.

## Requirements
Requirements | Functional
------------ | ----------
Must-have | <ul><li>The crossing gate is open when no train is coming near the gate.</li><li>The crossing gate is closed when a train is about to cross and during crossing the gate.</li><li>The crossing gate is open again when the train passes the gate.</li><li>Train can stop between the sensors.</li></ul>
Nice-to-have | <ul><li>A signaling light: Light is on when the gate is closed, i.e a train is approaching, and vice versa</li></ul>
Constraints | <ul><li>Distance between left-sided sensor and right-sided sensor is longer than the train</li><li>Use Arduino-family microcontroller</li></ul>

## Schematics (Fritzing)

> schematics/[schematics.fzz](https://github.com/TuanANg/railway-crossing/blob/master/Railway_Crossing.fzz)

![Railway Crossing Schematics](media/schematics.png)

## List of Components

Name | Type | Quantity
---- | ---- | --------
Arduino UNO | Microcontroller board | 1
Servo motor | Servo motor | 1
TCRT5000 | Infra-red sensor pair | 4
Red light | LED Red | 1
220Ohm resistor | Resistor | 5
10KOhm resistor | Resistor | 4
Wires | -- | --

## Setup
4 TRCT5000 sensors are placed at position LO (left out), LI (left in), RI (right in) & RO (right out) <br/>

![Railway Crossing Setup](media/setup.png)

## State machine

![Railway Crossing Behavior](media/state-machine.png)

## Firmware (Arduino)

> /firmware/[firmware.ino](https://github.com/TuanANg/railway-crossing/blob/master/firmWare/firmWare.ino)
