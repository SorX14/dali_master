#pragma once

/* dali_master library by Steve Parker
 */

// This will load the definition for common Particle variable types
#include "Particle.h"
#include "application.h"

#ifndef bitRead
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#endif

#define ON_C                0b00000101 // Alias for RECALLMAXLEVEL_C
#define RECALLMAXLEVEL_C    0b00000101 
#define RECALLMINLEVEL_C    0b00000110
#define OFF_C               0x00 // OFF
#define QUERY_MAX_LEVEL_C   0xA1 // Ask for maximum output level

#define BLANK_C             0x00 // Easier to type

#define BROADCAST_C         0xFF
#define BROADCAST_DP        0xFE

// Specifically related to initialisation
#define RESET_C             0b00100000 // 0x20
#define TERMINATE_C         0b10100001 // 0xA1
#define INITIALISE_C        0b10100101 // 0xA5
#define RANDOMISE_C         0b10100111 // 0xA7
#define COMPARE_C           0b10101001 // 0xA9
#define SEARCHADDRH_C       0b10110001 // 0xB1
#define SEARCHADDRM_C       0b10110011 // 0xB3
#define SEARCHADDRL_C       0b10110101 // 0xB5
#define PROGRAMSHORT_C      0b10110111 // 0xB7
#define WITHDRAW_C          0b10101011 // 0xAB

// Led Warrior I2C bits
#define BUSERROR_S 7
#define BUSY_S 6
#define OVERRUN_S 5
#define FRAMEERROR_S 4
#define VALIDREPLY_S 3
#define REPLYTIMEFRAME_S 2
#define REPLY2_S 1
#define REPLY1_S 0

// This is your main class that users will import into their application
class Dali_master
{
public:
  /**
   * Constructor
   */
  Dali_master();

  /**
   * Begin; set the address of the LED Warrior
   */
  void begin(uint8_t _address);

  /**
   * Transmit a command and optionally wait for a reply
   */
  byte transmitCommand(byte cmd1, byte cmd2, bool &reply, byte &reply1, byte &reply2);
  byte transmitCommand(byte cmd1, byte cmd2);

  /**
   * Get command status
   */
  byte getStatus();

  /**
   * Get command register
   */
  void getCommandRegister(uint8_t &byte1, uint8_t &byte2);

  /**
   * Split 24 bit long into three bytes
   */
  void splitAdd(long input, uint8_t &highbyte, uint8_t &middlebyte, uint8_t &lowbyte);

  /**
   * Flash a device
   */
  void flashDevice(byte deviceId);

private:
  uint8_t address;

  /**
   * Clear status register
   */
  void clearStatusRegister();

  /**
   * Get status register. Returns true when valid data is available
   */
  bool getStatusRaw();

  /**
   * Get command register. Returns true when valid data is available
   */
  bool getCommandRegisterRaw();  
};
