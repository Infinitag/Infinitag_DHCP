#include "sensor_dhcp_server.h"

SensorDHCPServer::SensorDHCPServer(uint8_t ServerAddress, uint16_t ScanInterval)
	: serverAddress(ServerAddress)
	, scanInterval(ScanInterval)
	, callsSinceLastScan(0)
{
	Memory = EEPROMManager::the()->allocateEntry<SensorDHCPServer>();
	Memory.setData(this);
	
	uint8_t address = 0;
	/*for(; address < DHCP_FIRST_FREE_ADDRESS; address++)
	{
		clients[address] = SensorDHCPClientProperties(address, DHCP_RESERVED_ADDRESS);
	}*/
	for(address = DHCP_FIRST_FREE_ADDRESS; address < DHCP_FIRST_FREE_ADDRESS + IIC_DHCP_ADDRESS_RANGE; address++)
	{
		clients[address - DHCP_FIRST_FREE_ADDRESS] = SensorDHCPClientProperties(address, DHCP_NO_CLIENT);
	}
	/*for(; address < IIC_DHCP_ADDRESS_RANGE; address++)
	{
		clients[address] = SensorDHCPClientProperties(address, DHCP_RESERVED_ADDRESS);
	}*/
}

SensorDHCPServer::~SensorDHCPServer()
{
	
}
	
void SensorDHCPServer::initialize()
{
	Wire.begin(serverAddress);
}

uint8_t SensorDHCPServer::getNextFreeSlot() const
{
	for(uint8_t address = DHCP_FIRST_FREE_ADDRESS; address <= DHCP_LAST_FREE_ADDRESS; address++)
	{
		if(clients[address - DHCP_FIRST_FREE_ADDRESS].getClientType() == DHCP_NO_CLIENT)
		{
			return address;
		}
	}	
	return IIC_DHCP_ADDRESS_RANGE;
}

void SensorDHCPServer::scanIfNecessary(bool forceScan)
{
	if((callsSinceLastScan >= scanInterval) || forceScan)
	{ 
		Serial.println("Scanning...");
		for(uint8_t address = DHCP_FIRST_FREE_ADDRESS; address <= DHCP_LAST_FREE_ADDRESS; address++)
		{      
			Wire.beginTransmission(address);
			uint8_t error = Wire.endTransmission();
 
			//I2C device found at address      
			if (error == 0)
			{	
				Serial.print("I2C device found at address 0x");
				if (address<16)
					Serial.print("0");
				Serial.print(address,HEX);
				Serial.println("  !");
				//TODO determine type! but for now assume its a sensor
				//if(clients[address])
				//clients[address] = SensorDHCPClientProperties(address, DHCP_SENSOR_CLIENT);
			}
			else if (error==4)
			{
				//Error occured
			}   
			else
			{
				clients[address] = SensorDHCPClientProperties(address, DHCP_NO_CLIENT);
			}	 
		}

		callsSinceLastScan = 0;
		//Serial.println("done\n");
	}
	else
	{
		callsSinceLastScan++;
	}
}
	
void SensorDHCPServer::registerNewClient()
{
	uint8_t nextFreeClient = getNextFreeSlot();
	if((nextFreeClient >= DHCP_FIRST_FREE_ADDRESS) && (nextFreeClient <= DHCP_LAST_FREE_ADDRESS))
	{
		clients[nextFreeClient - DHCP_FIRST_FREE_ADDRESS] = SensorDHCPClientProperties(nextFreeClient, DHCP_SENSOR_CLIENT);
		Wire.write(nextFreeClient);
	}
	else
	{
		Wire.write(nextFreeClient);
	}
}