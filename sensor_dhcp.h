/*
* INFINITAG - open source laser tag
* Authors: Jani Taxidis, Tobias Stewen & Florian Kleene
* Website: www.infinitag.io
*
* All files are published under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
* License: https://creativecommons.org/licenses/by-nc-sa/4.0/
*/

#ifndef INFINITAG_SENSOR_DHCP_H
#define INFINITAG_SENSOR_DHCP_H

#include "EEPROMManager.h"
#include <Wire.h>
#include <Arduino.h>

#define ArrayCount(Array) (sizeof(Array)/sizeof(Array[0]))

#define IIC_DHCP_ADDRESS_RANGE 6

#define DHCP_MASTER_ADDRESS 0x08
#define DHCP_DEFAULT_SLAVE_ADDRESS 0x09

#define DHCP_FIRST_FREE_ADDRESS 0x22
#define DHCP_LAST_FREE_ADDRESS 0x26

//30 Minutes lease time
#define DHCP_LEASE_TIME 1800000 
#define DHCP_LEASE_HALF_TIME (DHCP_LEASE_TIME / 2)

#define SENSOR_DHCP_MAJOR_VERSION 0x00
#define SENSOR_DHCP_MINOR_VERSION 0x01
#define SENSOR_DHCP_PATCH_VERSION 0x00


enum dhcp_client_type
{
  DHCP_NO_CLIENT,
  DHCP_RESERVED_ADDRESS,
  DHCP_SENSOR_CLIENT,
};


inline bool checkEEPROMVersion()
{
  byte majorVersion = EEPROM.read(0);
  byte minorVersion = EEPROM.read(1);
  byte patchVersion = EEPROM.read(2);
  
  if((majorVersion != SENSOR_DHCP_MAJOR_VERSION) ||
    (minorVersion != SENSOR_DHCP_MINOR_VERSION) ||
    (patchVersion != SENSOR_DHCP_PATCH_VERSION))
  {
    for (int i = 0; i < EEPROM.length(); i++) 
    {
      EEPROM.write(i, 0xFF);
    }
    return false;
  }
  else
  {
    return true;
  }
}


#endif //INFINITAG_SENSOR_DHCP_H