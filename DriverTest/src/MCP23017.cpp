#include <MCP23017.h>
#include <wiringPiI2C.h>

namespace pi
{
	MCP23017::MCP23017(int port)
		: DriverI2C(port)
	{
	}

	MCP23017::~MCP23017()
	{
	}

	bool MCP23017::setup()
	{
		if (DriverI2C::setup())
		{
			return true;
		}
		return false;
	}
}
