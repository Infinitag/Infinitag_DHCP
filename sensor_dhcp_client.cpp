#include "sensor_dhcp_client.h"

SensorDHCPClient::SensorDHCPClient(uint8_t ServerAddress)
	: serverAddress(ServerAddress)
	, clientAddress(DHCP_DEFAULT_SLAVE_ADDRESS)
{	
}

SensorDHCPClient::~SensorDHCPClient()
{
}

void SensorDHCPClient::initialize()
{
	if(clientAddress != DHCP_DEFAULT_SLAVE_ADDRESS)
	{
		Wire.begin(clientAddress);

		while(Wire.requestFrom((uint8_t)serverAddress, (uint8_t)1) != 1)
		{
			//don't block i2c bus
			delay(50);
		}
		clientAddress = Wire.read();
	}
	
	Wire.begin(clientAddress);
}