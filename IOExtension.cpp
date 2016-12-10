/************************************************************************************************************************************************************************                                              
 * - Author               : BELKHIR Mohamed              *                                               
 * - Profession           : (Developer) MEGA DAS owner   *                                                                                              
 * - Main purpose         : Industrial Application       *                                                                                 
 * - Copyright (c) holder : No copyrights                *                                  
 * - Date                 : 06/10/2016                   *
 * ***********************************************************************************************************************************************************************/
 
 /********************** NOTE **************************************/
//  This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
 
/**                                                           --------------------------------------------------------------
                                                                     MASTER ARRAY FOR SOFTWARE AND HARDWARE REFERENCES
                                                              --------------------------------------------------------------
|--------------------|-------------------------|----------------------|----------------------------------------------------------------------------------------------------|
|    I/O Label       |         Type            |     HARDWARE PIN     |                                              Description                                           |
|--------------------|-------------------------|----------------------|----------------------------------------------------------------------------------------------------|
|    shift_clock     |    Digital INPUT        |         SH_CP        | Shift Register Clock Input. A low– to–high transition onthis input causes the data at the Serial   |
|                    |                         |                      | Input pin to be shiftedinto the 8–bit shift register.                                              |
|--------------------|-------------------------|----------------------|----------------------------------------------------------------------------------------------------|
|       data         |    Digital INPUT        |          DS          | Serial Data Input. The data on this pin is shifted into the 8–bit serial shift register.           |                           
|--------------------|-------------------------|----------------------|----------------------------------------------------------------------------------------------------|
|    store_clock     |    Digital INPUT        |         ST_CP        | Storage Latch Clock Input. A low–to–high transition on this input latches the shift register data. |                                             |
|--------------------|-------------------------|----------------------|----------------------------------------------------------------------------------------------------|
|       IN_P         |    Digital INPUT        |         IN_P         | Use a simple digital Pin to read the inputs                    |
|--------------------|-------------------------|----------------------|----------------------------------------------------------------------------------------------------|*/


#include"IOExtension.h"                // include the IOExten

IOExtension::IOExtension(int SH_CP,int DS,int ST_CP,int IN_P)
{	
	shift_clock=SH_CP;
	data=DS;
	store_clock=ST_CP;
	this->IN_P=IN_P;
	commandePinOM=0x00;
	commandePinOL=0x00;
	commandePinI=0x00;
	
	pinMode(shift_clock,OUTPUT);
	pinMode(data,OUTPUT);
	pinMode(store_clock,OUTPUT);
	pinMode(IN_P,INPUT);
	
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	SPI.begin();
}

IOExtension::~IOExtension()
{
	
}

void IOExtension::DigitalWrite(int pin,bool state)
{
	if(pin<9)
  {
	  if(state!=0)
	  {
		bitWrite(commandePinOL,pin-1,1);
	  }
	  else
	  {
		bitWrite(commandePinOL,pin-1,0);
	  }
  }
  else
  {
	if(state!=0)
	{
		bitWrite(commandePinOM,pin-9,1);
	}
	else
	{
		bitWrite(commandePinOM,pin-9,0);
	}  
  }
  /**THIS portion of code(commented) can be used in case you don't want to use the SPI functions 
  ----------------------------------------------------------------------------------------------------*/
	/* digitalWrite(store_clock,LOW);
	for(int i=0;i<8;i++)
	{
		digitalWrite(shift_clock,LOW);
		digitalWrite(data,commandePinM & 0x80 >> i);
		digitalWrite(shift_clock,HIGH);
	}
	digitalWrite(store_clock,HIGH);
	digitalWrite(store_clock,LOW);
	for(int i=0;i<8;i++)
	{
		digitalWrite(shift_clock,LOW);
		digitalWrite(data,commandePinL & 0x80 >> i);
		digitalWrite(shift_clock,HIGH);
	} */
/**  ----------------------------------------------------------------------------------------------------*/
	SPI.transfer(commandePinOM);
	SPI.transfer(commandePinOL);
	SPI.transfer(commandePinI);
	SPI.transfer(commandePinI);
	digitalWrite(store_clock,HIGH);
	digitalWrite(store_clock,LOW);
}

bool IOExtension::DigitalRead(int pin)
{
	SPI.transfer(commandePinOM);
	SPI.transfer(commandePinOL);
	digitalWrite(store_clock,HIGH);
	digitalWrite(store_clock,LOW);
	if(pin<9)
  {
    SPI.transfer(commandePinI);
    digitalWrite(store_clock,HIGH);
    digitalWrite(store_clock,LOW);
    bitWrite(commandePinI,pin-1,1);
    SPI.transfer(commandePinI);
    digitalWrite(store_clock,HIGH);
    digitalWrite(store_clock,LOW);
  }
  else
  {
    bitWrite(commandePinI,pin-9,1);
    SPI.transfer(commandePinI);
    digitalWrite(store_clock,HIGH);
    digitalWrite(store_clock,LOW);
	commandePinI=0x00;
    SPI.transfer(commandePinI);
    digitalWrite(store_clock,HIGH);
    digitalWrite(store_clock,LOW);
  }
  commandePinI=0x00;
  delayMicroseconds(500);
  if(digitalRead(IN_P))
    return true;
  else
    return false;
}