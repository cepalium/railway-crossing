# Railway Crossing by 2 Ultrasonic Sensors
The railway model in Zusebau room 2045 should be extended by a Crossing Gate. The gate will be operated by a servo motor, a train has to be detected by sensors before and after the crossing. The gate should be open when no train is in the area, the gate should be closed as soon as a train is on or near the crossing. Under no circumstances can the gate be open while a train is passing. Think about the right set of sensors to assure this requirement. During this task, modifications to the railway model are not allowed or needed.


## Requirements
Requirements | Functional | Non-functional
------------ | ---------- | --------------
Must-have | <ul><li>The crossing gate is open when no train is coming near the gate.</li><li>The crossing gate is closed when there is a train coming to the gate.</li><li>The crossing gate is open again when the train passes the gate.</li></ul> | <ul><li>Train can stop between the sensors.</li></ul>
Constraints | <ul><li>Micro-controller to control the whole system</li><li>Servo motor to open/close the gate</li><li>2 sensors: 1 on left, 1 on right of the gate</li><li>LED for signal</li></ul> | <ul><li>Distance between sensors is longer than the train.</li></ul>


## Schematics
![Railway Crossing Schematics](media/schematics.png)


## List of Components
Name | Type | Quantity
---- | ---- | --------
Arduino UNO | Microcontroller board | 1
Servo motor | Servo motor | 1
HC-SR04 | Ultrasonic sensor | 2
Red light | LED Red | 1
220Ohm resistor | Resistor | 1
Male-male wires | Cables | 20
Male-female wires | Cables | 3


## State machine
![State machine](media/state-machine.png)


## Arduino Firmware
See [Railway-Crossing-2-Sensor Arduino program](https://github.com/TuanANg/railway-crossing/blob/2-sensor/firmware/railwayCrossing_firmWare.ino)