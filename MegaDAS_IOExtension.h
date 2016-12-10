/************************************************************************************************************************************************************************                                              
 * - Author               : BELKHIR Mohamed              *                                               
 * - Profession           : (Developer) MEGA DAS owner   *                                                                                              
 * - Main purpose         : Industrial Application       *                                                                                 
 * - Copyright (c) holder : All rights reserved          *
 * - License              : BSD 2-Clause License         * 
 * - Date                 : 06/10/2016                   *
 * ***********************************************************************************************************************************************************************/
 
 /*********************************** NOTE **************************************/
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
 
 // Headers file (.h)

#ifndef IO_Extension_H
#define IO_Extension_H
//------------------------------------------------------------------------- INCLUDES -----------------------------------------------------------------------------------

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
	IOExtension(int,int,int,int);   // Constructor header
	~IOExtension();                 // Destructor header
	void DigitalWrite(int,bool);    // DigitalWrite header
	bool DigitalRead(int);          // DigitalRead header
};
#endif