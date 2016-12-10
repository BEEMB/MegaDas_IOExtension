/************************************************************************************************************************************************************************                                              
 * - Author               : BELKHIR Mohamed              *                                               
 * - Profession           : (Developer) MEGA DAS owner   *                                                                                              
 * - Main purpose         : Industrial Application       *                                                                                 
 * - Copyright (c) holder : All rights reserved          *
 * - License              : BSD 2-Clause License         * 
 * - Date                 : 06/10/2016                   *
 * ***********************************************************************************************************************************************************************/
 
 /********************** NOTE **************************************/
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED
 
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
|       IN_P         |    Digital INPUT        |         IN_P         | Use a simple digital Pin to read the inputs                                                        |
|--------------------|-------------------------|----------------------|----------------------------------------------------------------------------------------------------|*/

// IOExtension cpp file (.cpp)
//------------------------------------------------------------------------- INCLUDES -----------------------------------------------------------------------------------

#include"MegaDAS_IOExtension.h"                // include the MegaDAS_IOExtension header file 

//------------------------------------------------------------------------- METHODES -----------------------------------------------------------------------------------

  /** The constructor used to create the instance of the IOExtension class that allows us to use the APIs 
  -----------------------------------------------------------------------------------------------------------------------------------*/
//------------------------------------------------------------------ STARTING THE CONSTRUCTOR FUNCTION -----------------------------------------------------------------
IOExtension::IOExtension(int SH_CP,int DS,int ST_CP,int IN_P)
{	
				//************************************* PRIVATE VARIABLES INITIALIZATION **************************************************
	shift_clock=SH_CP;
	data=DS;
	store_clock=ST_CP;
	this->IN_P=IN_P;
	commandePinOM=0x00;
	commandePinOL=0x00;
	commandePinI=0x00;
	
				//******************************************* I/O pins configuration *******************************************************
	pinMode(shift_clock,OUTPUT);
	pinMode(data,OUTPUT);
	pinMode(store_clock,OUTPUT);
	pinMode(IN_P,INPUT);
	
				//**************************************** SPI SETUP AND CONFIGURATION *****************************************************
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	SPI.begin();
}
//------------------------------------------------------------------- ENDING THE SETUP FUNCTION ------------------------------------------------------------------------

IOExtension::~IOExtension()
{
	
}
  /** The first function is similar to Arduino API digitalWrite function! it takes two parameters ( the pin to use and the state )
          - The pin is a number from 1 to 16 (depends on the Extension module that you use "8 I/O or 16 I/O or other")
		  - The state is a boolean level which can be false or true // HIGH or LOW // 0 or an integer number different than 0 to refer to 1 logic
  -----------------------------------------------------------------------------------------------------------------------------------*/
  //------------------------------------------------------------------ STARTING THE DigitalWrite FUNCTION -----------------------------------------------------------------
void IOExtension::DigitalWrite(int pin,bool state)
{
	if(pin<9)                               // If the user will use the first 8-bit outputs so we modify the Outputs of the first register
  {
	  if(state!=0)                          // Test the logic level to write if it's different of 0 that means HIGH
	  {
		bitWrite(commandePinOL,pin-1,1);    // Then we need to set only the specified bit which is the 'pin' argument to HIGH
	  }
	  else                                  // Now if the state argument is equal to 0 or LOW or false
	  {
		bitWrite(commandePinOL,pin-1,0);    // That means we need to switch the specified bit (output pin) tow LOW
	  }
  }
  else                                      // If the user is using the second 8-bit outputs so we modify the Outputs of the second register
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
	                                        // Every time we call this function we need to modify the Outputs of all registers
	SPI.transfer(commandePinOM);            // Update the Second Output register
	SPI.transfer(commandePinOL);            // Update the First Output register
	SPI.transfer(commandePinI);             // Update the First Input register
	SPI.transfer(commandePinI);             // Update the Second Input register
	digitalWrite(store_clock,HIGH);         // Toggle the store pin of all I/O
	digitalWrite(store_clock,LOW);
}
//------------------------------------------------------------------- ENDING THE DigitalWrite FUNCTION --------------------------------------------------------------------

 /** The second function is similar to Arduino API digitalRead function! it takes only one parameter ( the pin to read)
          - The pin is a number from 1 to 16 (depends on the Extension module that you use "8 I/O or 16 I/O or other")
	 The function return a boolean data refer the the pin logic level (TOR)
  -----------------------------------------------------------------------------------------------------------------------------------*/
  //------------------------------------------------------------------ STARTING THE DigitalRead FUNCTION -----------------------------------------------------------------
bool IOExtension::DigitalRead(int pin)
{
											// Every time we call this function we need to modify the Outputs of all registers
	SPI.transfer(commandePinOM);            // Update the Second Output register    
	SPI.transfer(commandePinOL);            // Update the First Output register
	digitalWrite(store_clock,HIGH);         // Toggle the store pin of all I/O
	digitalWrite(store_clock,LOW);
	
	if(pin<9)                               // If the user will use the first 8-bit inputs so we modify the input of the first register
  {
    SPI.transfer(commandePinI);             // Send zero over all input registers
    digitalWrite(store_clock,HIGH);         // Toggle the store pin of all I/O
    digitalWrite(store_clock,LOW);
    bitWrite(commandePinI,pin-1,1);
    SPI.transfer(commandePinI);             // Send the HIGH logic level over the specified pin
    digitalWrite(store_clock,HIGH);         // Toggle the store pin of all I/O
    digitalWrite(store_clock,LOW);
  }
  else                                      // If the user is using the second 8-bit inputs so we modify the inputs of the second register
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
  commandePinI=0x00;                        // Reset the inputs registers command
  delayMicroseconds(500);                   // Delay to make sure that the level is HIGH over the specified pin
  if(digitalRead(IN_P))                     // Read the Input pin configured in your Board to verify if we have a HIGH logic level coming from the input pin register 
    return true;                            // Return true if the input is HIGH
  else
    return false;                           // Else return false
}
//------------------------------------------------------------------- ENDING THE DigitalRead FUNCTION --------------------------------------------------------------------