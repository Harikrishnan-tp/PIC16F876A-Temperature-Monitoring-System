# PIC16F876A Temperature Monitoring System

## Project Overview
This project is a temperature monitoring system developed using the PIC16F876A microcontroller and LM35 temperature sensor. The system measures the surrounding temperature and displays the temperature value on a 16×2 LCD.

An LED alert is activated when the temperature reaches the predefined threshold of 35°C.

## Components Used
- PIC16F876A microcontroller
- LM35 temperature sensor
- 16×2 LCD (LM016L)
- LED indicator
- 4 MHz crystal oscillator
- 22 pF capacitors
- Resistors
- Connecting wires and power supply

## Software and Tools
- MPLAB X IDE
- XC8 Compiler
- Proteus Design Suite

## Working Principle
1. The LM35 senses the surrounding temperature.
2. The sensor generates an analog voltage proportional to the temperature.
3. The PIC16F876A reads the sensor voltage through its ADC.
4. The microcontroller converts the ADC reading into a temperature value.
5. The temperature is displayed on the 16×2 LCD.
6. When the temperature reaches 35°C, the LED alert activates.

## Features
- Real-time temperature monitoring
- LCD-based temperature display
- LED alert at a predefined temperature threshold
- Microcontroller-based embedded system design
- Circuit simulation using Proteus

## Applications
- Basic temperature monitoring
- Electronic equipment temperature indication
- Embedded systems learning and experimentation

## Project Files
- `temperaturemonitoringsystem.c` — XC8 source code
- Proteus schematic — circuit design and simulation

## Learning Outcomes
- Interfacing an LM35 sensor with a PIC microcontroller
- Using the ADC to measure analog signals
- Interfacing a 16×2 LCD in embedded C
- Implementing threshold-based LED control
- Simulating microcontroller circuits in Proteus

## Future Improvements
- Add a buzzer for an audible temperature warning
- Display temperature readings in Celsius with improved formatting
- Add additional temperature thresholds

## Author
Harikrishnan TP

## Note
This project is intended for educational purposes and embedded systems practice.

