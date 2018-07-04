#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <FileSystem.h>
#include <MCP23017.h>
#include <LiquidCrystal_I2C.h>
#include <PiGPIO.h>
#include <Net.h>
#include <Timer.h>

using namespace pi;

// * * * * * * * * * * * * * * //

FileSystem			fs;
LiquidCrystal_I2C	lcd(0x3f, 16, 2);
MCP23017			bus(0x20);
PiGPIO				gpio;

// * * * * * * * * * * * * * * //


void showLoading(unsigned ms)
{
	lcd.clear();
	if (ms > 0)
	{
		lcd.print("Loading...");
		lcd.setPos(0, 1);
		for (int i = 0; i < 16; i++)
		{
			lcd.print((char)255);
			delay(ms);
		}
		delay(500);
		lcd.clear();
	}
}

void netTest()
{
	lcd.clear();
	const char* e0 = Net::getAddr("eth0");
	lcd.printf("e0 %s", (e0 ? e0 : "Offline"));

	lcd.setPos(0, 1);
	const char* w0 = Net::getAddr("wlan0");
	lcd.printf("w0 %s", (w0 ? w0 : "Offline"));
}

// * * * * * * * * * * * * * * //

int setup()
{
	if (wiringPiSetup() == -1)
	{
		std::cerr << "Wiring Pi Setup Failed" << std::endl;
		return EXIT_FAILURE;
	}

	if (!lcd.setup())
	{
		std::cerr << "LiquidCrystal_I2C Setup Failed" << std::endl;
		return EXIT_FAILURE;
	}

	if (!bus.setup())
	{
		std::cerr << "MCP23017 Setup Failed" << std::endl;
		return EXIT_FAILURE;
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

	// Setup LCD
	lcd.clear().home().blink(true);
	delay(1000);
	lcd.blink(false);

	showLoading(50);

	netTest();

	return EXIT_SUCCESS;
}

// * * * * * * * * * * * * * * //
