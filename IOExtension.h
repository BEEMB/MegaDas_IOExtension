#ifndef IO_Extension_H
#define IO_Extension_H
#include "Arduino.h"    // for digitalRead, digitalWrite, pinMode, delayMicroseconds
#include<SPI.h>
class IOExtension
{
	private :
	int shift_clock;
	int store_clock;
	int data;
	int IN_P;
	byte commandePinOM;
	byte commandePinOL;
	byte commandePinI;
	
	public:
	IOExtension(int,int,int,int);
	~IOExtension();
	void DigitalWrite(int,bool);
	bool DigitalRead(int);
};
#endif