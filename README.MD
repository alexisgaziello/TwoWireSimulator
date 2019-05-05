

# TwoWire Simulator

I have been working on a project in which I worked with several I2C sensors that gave me information. However, for testing purposes I wrote this extension of the library “Wire.h” to let me simulate with an Arduino the behaviour of several I2C devices.

## Use

See *example.ino* file for an implementation in an arduino that will act as multiple I2C slave devices. The implementation in the master device is the same as it would be in normal use.
There are two ways to configure the class object WireSim:
- By giving the addresses (the mask will be calculated accordingly).
  - Be careful!! When submitting addresses make sure that most bits are common. If not the mask calculated will be big and lots of addresses will be disabled. 

- By directly providing the mask and one address (there is no importance in which address is given).

The mask may disable more addresses than you need. Make sure these addresses are not used by other devices.

## Requirements

- *Wire.h* library (from arduino's official repository)
  
 
## How does it work?

If you want to understand the code I wrote you will have to learn a little about the Arduino’s hardware architecture.
A micro controller has several registers, that usually consist of a small amount of fast storage quickly accessible location available to a computer's central processing unit (CPU). We are going to focus on the Two Wire registers (TW).

The micro controller used by the Arduino Uno is called ATMega 328. There will be much more information in the section 22 - 2 wire Serial Interface - of the controller datasheet, if you are interested. This document is attached at the end of the article.

I will keep things simple. Here are the most important registers we need to understand. They are all 8 bits registers.

- **TWAR**:The TWI Address Register checks if the seven bits received are the slave address. In the affirmative case it triggers an interrupt routine. Here is where the “Wire.h” sets our address.

- **TWDR**: The Data and Address Shift Register. Contains the address or data bytes to be transmitted, or the address or data bytes received. Here is where we will check which address is called by the master. 

- **TWAMR**: The TWI Address Mask can be set to mask (disable) the corresponding address bits in the TWI Address Register (TWAR). If the mask bit is set to one then the address match logic ignores the compare between the incoming address bit and the corresponding bit in TWAR.

Here is a diagram of what is happening (even if it is not in the order, this is the idea):

![Diagram](https://github.com/alexisgaziello/TwoWireSimulator/blob/master/imgs/diagram.png)

**Idea**

By putting one bit to the value 1 in the TWAMR address we are allowing two addresses to be read.
(Letters represent 1 or 0, however they must be the same on all addresses)

<pre>
Mask:     	0	0	0	1	0	0	0
Address 1:	A	B	C	0	D	E	F
Address 2:	A	B	C	1	D	E	F
</pre>

If we mask 2 bits then we have 4 addresses:

<pre>
Mask:     	0	0	0	1	1	0	0
Address 1:	A	B	C	0	0	E	F
Address 2:	A	B	C	1	0	E	F
Address 3:	A	B	C	0	1	E	F
Address 4:	A	B	C	1	1	E	F
</pre>

For 3 bits 8 addresses, etc. You get the idea. 2<sup>(bits masked)</sup> = number of addresses we can use.

However, be careful, some addresses are not allowed to be used because the I2C protocol needs them to work properly. You should only use addresses between 8 and 119. The first and last 8 are reserved.
