/*
* INFINITAG - open source laser tag
* Authors: Jani Taxidis, Tobias Stewen & Florian Kleene
* Website: www.infinitag.io
*
* All files are published under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
* License: https://creativecommons.org/licenses/by-nc-sa/4.0/
*/

#ifndef INFINITAG_SENSOR_DHCP_CLIENT_H
#define INFINITAG_SENSOR_DHCP_CLIENT_H


#include "sensor_dhcp.h"
#include "sensor_dhcp_client_properties.h"

class SensorDHCPClient
{
public:
	SensorDHCPClient(uint8_t ServerAddress);
	~SensorDHCPClient();
	
	void initialize();	
private:
	SensorDHCPClientProperties properties;
	int bootsSinceLease;
	uint8_t serverAddress;	
	uint8_t clientAddress;
};

#endif