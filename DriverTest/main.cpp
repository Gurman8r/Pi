#include <wiringPi.h>
#include <iostream>
#include <MCP23017.h>

using namespace pi;

// * * * * * * * * * * * * * * //

Reg16		gpio;
MCP23017	bus(0x20);

// * * * * * * * * * * * * * * //

int setup()
{
	if (wiringPiSetup() < 0)
	{
		std::cerr << "WiringPi setup failed" << std::endl;
		return EXIT_SUCCESS;
	}

	if (!bus.setup())
	{
		std::cerr << "Bus setup failed" << std::endl;
		return EXIT_FAILURE;
	}

	for (unsigned i = 0; i < 16; i++)
	{
		// pins 0-7, 21-28
		int addr = ((i < 8) ? (i) : (i + 13));

		gpio[i].setAdr(addr).setDir(Pin::Output).setBit(0);
	}

	return EXIT_SUCCESS;
}

// * * * * * * * * * * * * * * //

int main(int argc, char** argv)
{
	if (setup())
	{
		return EXIT_FAILURE;
	}
	
	std::cout << (gpio = 0x0000) << std::endl; delay(500);
	std::cout << (gpio = 0x000F) << std::endl; delay(500);
	std::cout << (gpio = 0x00F0) << std::endl; delay(500);	
	std::cout << (gpio = 0x0F00) << std::endl; delay(500);
	std::cout << (gpio = 0xF000) << std::endl; delay(500);

	return EXIT_SUCCESS;
}

// * * * * * * * * * * * * * * //
