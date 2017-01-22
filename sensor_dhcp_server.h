/*
* INFINITAG - open source laser tag
* Authors: Jani Taxidis, Tobias Stewen & Florian Kleene
* Website: www.infinitag.io
*
* All files are published under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
* License: https://creativecommons.org/licenses/by-nc-sa/4.0/
*/

#ifndef INFINITAG_SENSOR_DHCP_SERVER_H
#define INFINITAG_SENSOR_DHCP_SERVER_H


#include "sensor_dhcp.h"
#include "sensor_dhcp_client_properties.h"

class SensorDHCPServer
{
public:
	SensorDHCPServer(uint8_t ServerAddress, uint16_t scanInterval);
	~SensorDHCPServer();
	
	void initialize();
	
	uint8_t getNextFreeSlot() const;
	
	void scanIfNecessary(bool forceScan = false);
	void registerNewClient();
	
private:
	uint8_t serverAddress;
	uint16_t scanInterval;
	uint16_t callsSinceLastScan;
	SensorDHCPClientProperties clients[IIC_DHCP_ADDRESS_RANGE];
	
	EEPROMEntry<SensorDHCPServer> Memory;
};

#endif