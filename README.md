# deadflesh-usb

*Spectrum Membrane to USB adapter*

This code in its current iteration will allow the cheap and cheerful Arduino Promicro to correctly read a spectrum 48k/128k/plus 2 key presses and return the correct keypresses as a USB keyboard. Please read below to get started.

## How to deploy the code to the arduino

### Install The arduino IDE 

### Load the Ino file

### attach your promicro

### verify the code

### deploy the code



## How to build the shield

### Buy a PCB

This can be used with the 'deadflesh-usb' as a shield to make usage easy, as seen here -> http://www.mrbackus.co.uk 

![Speccy Membrane USB](/img/speccy-membrane-usb.png)

Want one ? Please buy one on ebay here or search for Speccy Membrane USB

### Roll your own
Alternatively you can use it directly using the pinouts below, and roll your own: 

Pins represent generic physical pin positions not assigned arduinio pins (counter clock wise from top left) Wire up according to this diagram..

5 pin connector
```
 [5 6 7 8 9]
   ________
  | Ribbon |
```
8 pin connector
```
[13 17 14 15 16 12 11 10 ]
  ______________________
 |        Ribbon        |
```
You must pull down all lines to ground ( Pin 3,4,23 ) with 10K resistor

![Pinouts for arduino ](/img/pinout.webp)



If you want to send me some appreciation : https://www.buymeacoffee.com/nadoom
