# deadflesh-usb

*Spectrum Membrane to USB adapter*

Code is licenced under the MIT liscence see [HERE](/LICENSE.txt)

This code in its current iteration will allow the cheap and cheerful Arduino Promicro to read a spectrum 48k/128k/plus 2 key presses and return the correct keypresses as a USB keyboard. Use it conjunction with the Deadflesh usb PCB.

Please read below to get started. Code more or less works it is being improved all the time.


### Buy a PCB
from me Nadoom aka *backus-cheese-emporium* on ebay search for deadflesh usb

Here is the link: https://www.ebay.co.uk/itm/375260941327

![Deadflesh USB](/img/speccy-membrane-usb.png)



## How to deploy the code to the arduino
*todo*
### Install The arduino IDE 
*todo*
### Load the Ino file
*todo*
### attach your promicro
*todo*
### verify the code
*todo*
### deploy the code
*todo*


## How to build the board

### Get the parts

| # | Reference        | Qty | Value           | Footprint                                                                                         |
|---|------------------|-----|-----------------|---------------------------------------------------------------------------------------------------|
| 1 | ArduinoProMicro1 | 1   | ProMicro        | promicro:ProMicro Castillated one if you want less work, but they are a bit more expensive.       |
| 2 | Power1           | 1   | Conn_01x02      | 1x2 pin header, can be ignored if you are just using a membrane kb                                |
| 3 | RN1              | 1   | Pull down       | Resistor_THT:R_Array_SIP9 a 9 pin resistor array 10K (Bourns, 4600X 10kΩ) RS: 522-4071            |
| 4 | RN2              | 1   | Pull down       | Resistor_THT:R_Array_SIP6 a 6 pin resistor array 10K (Bourns, 4600X 10kΩ) RS: 522-3488            |
| 5 | SpectrumKB5      | 1   | Conn_01x05_Male | Different options:<br>JST FDZ series 2.54mm FPC Connectors RS search: 6387268 (Bit too tight tbh) |
| 6 | SpectrumKB8      | 1   | Conn_01x08_Male | Different options:<br>JST FDZ series 2.54mm FPC Connectors RS search: 6387280 (Bit too tight tbh) |

### Roll your own
Alternatively you can use it directly using the pinouts below, and roll your own: 

Pins represent generic physical pin positions not assigned arduino pins (counter clock wise from top left) Wire up according to this diagram..

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

My email is nadeem.backus@gmail.com
