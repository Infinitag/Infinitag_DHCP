#include "sensor_dhcp_client_properties.h"

SensorDHCPClientProperties::SensorDHCPClientProperties()
	: clientAddress(0)
	, clientType(DHCP_NO_CLIENT)
	, initialized(false)
	, connected(false)
{
	
}


SensorDHCPClientProperties SensorDHCPClientProperties::retrievePropertiesFromEEPROM(int BaseAddress)
{
	int ee = BaseAddress;
	SensorDHCPClientProperties properties;
	
	byte* p = (byte*)(void*)&properties;
    unsigned int i;
    for (i = 0; i < sizeof(SensorDHCPClientProperties); i++)
	{
          *p++ = EEPROM.read(ee++);
	}
    return properties;	
}

void SensorDHCPClientProperties::writePropertiesToEEPROM(int BaseAddress, const SensorDHCPClientProperties& properties)
{
	int ee = BaseAddress;
    const byte* p = (const byte*)(const void*)&properties;
    unsigned int i;
    for (i = 0; i < sizeof(SensorDHCPClientProperties); i++)
	{
          EEPROM.write(ee++, *p++);  
	}
}

SensorDHCPClientProperties::SensorDHCPClientProperties(uint8_t Address, dhcp_client_type Type)
	: clientAddress(Address)
	, clientType(Type)
{
	switch(clientType)
	{
	case DHCP_RESERVED_ADDRESS:
	{
		initialized = true;
		connected = false;
	}break;
	case DHCP_SENSOR_CLIENT:
	{
		initialized = true;
		connected = true;
	}break;
	case DHCP_NO_CLIENT:
	default:
	{
		initialized = false;
		connected = false;
	}break;
	}
}