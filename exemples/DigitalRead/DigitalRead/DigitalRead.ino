/************************************************************************************************************************************************************************                                              
 * - Author               : BELKHIR Mohamed              *                                               
 * - Profession           : (Developer) MEGA DAS owner   *                                                                                              
 * - Main purpose         : Industrial Application       *                                                                                 
 * - Copyright (c) holder : All rights reserved          *
 * - License              : BSD 2-Clause License         * 
 * - Date                 : 06/10/2016                   *
 * ***********************************************************************************************************************************************************************/
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

/*   ----- The circuit:                                            
 *                                                ARDUINO BOARD         EXTENSION MODULE
 *                                                |---------|          |-------------|
 *                                                |      13 | -------> | SH_CP       |
 *                                                |      11 | -------> | DS          |
 *                                                |    ST_CP| -------> | ST_CP       |
 *                                                |     IN_P| -------> | IN_P        |
 *                                                |---------|          |-------------|
 *                                                
 *   ----- Wiring:
 *   You gonna need only 4 pins to get 16 digital Inputs and 16 digital Outputs
 *   you can use the extension module using the SPI pins! so follow the instructions bellow
 *   - Connect pin 13 to SH_CP
 *   - Connect pin 11 to DS 
 *   - Connect any (unused) pin to ST_CP (in this exemple we used Digital pin 3
 *   - Connect any (unused) pin to IN_P (in this exemple we used Digital pin 4
 *   All pins will be automatically configured through the instance
 */   
#include <MegaDAS_IOExtension.h>              // Include the MegaDAS_IOExtension header file 

const int SH_CP=13;                             // 13 or ICSP-3 (for Arduino Uno, Nano, Leonardo and 101)  52 or ICSP-3 (for Arduino Mega2560 and Mega1280)
const int DS=11;                                // 11 or ICSP-4 (for Arduino Uno, Nano, Leonardo and 101)  51 or ICSP-4 (for Arduino Mega2560 and Mega1280)
const int ST_CP=3;                        
const int IN_P=4;
const int LED=2;

IOExtension myExt(SH_CP, DS, ST_CP, IN_P);         // Make instance and named anything you want (in this example the instance is myExt)

void setup()
{
  pinMode(LED,OUTPUT);                          // Configure LED pin as output pin 
}

void loop()
{
  if(myExt.DigitalRead(1)==HIGH)                // Read the first input pin of the Extension module
    digitalWrite(LED,HIGH);                     // Set LED output to HIGH if the Extension input is HIGH
    
  else
    digitalWrite(LED,LOW);                      // Set LED output to LOW if the Extension input is LOW
}
