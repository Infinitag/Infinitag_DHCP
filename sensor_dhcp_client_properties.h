/*
* INFINITAG - open source laser tag
* Authors: Jani Taxidis, Tobias Stewen & Florian Kleene
* Website: www.infinitag.io
*
* All files are published under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
* License: https://creativecommons.org/licenses/by-nc-sa/4.0/
*/

#ifndef INFINITAG_SENSOR_DHCP_CLIENT_PROPERTIES_H
#define INFINITAG_SENSOR_DHCP_CLIENT_PROPERTIES_H

#include "sensor_dhcp.h"


class SensorDHCPClientProperties
{
public:
	SensorDHCPClientProperties();
	SensorDHCPClientProperties(uint8_t Address, dhcp_client_type Type = DHCP_NO_CLIENT);
	
	static SensorDHCPClientProperties retrievePropertiesFromEEPROM(int BaseAddress);
	static void writePropertiesToEEPROM(int BaseAddress, const SensorDHCPClientProperties& properties);
	
	void initializeClient();
	dhcp_client_type getClientType() const { return clientType; }
private:
	uint8_t clientAddress;
	dhcp_client_type clientType;
	bool initialized;
	bool connected;
};

#endif //INFINITAG_SENSOR_DHCP_CLIENT_PROPERTIES_H