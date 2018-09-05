#include "Config.h"
#include <algorithm>
#include <wiringPi.h>
#include <iostream>
#include <Bus.h>
#include <LCD_I2C.h>
#include <FileSystem.h>
#include <INIReader.h>
#include <MCP23017.h>
#include <Net.h>
#include <Timer.h>
#include <OLED.h>
#include <wiringPiI2C.h>

using namespace pi;

// * * * * * * * * * * * * * * //

#define PIN_CLR 8
#define PIN_CLK 10
#define PIN_DIR 11

#define AMT 25
#define SER	0
#define OEN	1
#define LAT	2
#define CLK	3
#define CLR	4
#define CRY	5

#define RDIR 8
#define RCLK 9
#define RCLR 10

#define CRES 0
#define CCLK 1
#define CCEN 2
#define CCAR 3

// * * * * * * * * * * * * * * //

FileSystem	fs;
Bus			gpio(8);
Pin			dir, clk, clr;
MCP23017	bus(0x20);
LCD_I2C		lcd(0x3F, 16, 2);
OLED		oled(OLED_VCC_SWITCHCAP, 0x3C, 128, 64);

// * * * * * * * * * * * * * * //

void showLoading(unsigned spd, unsigned msg = 500)
{
	lcd.clear().blink(1);
	
	delay(msg);

	lcd.blink(0).print("Loading...");

	for (int i = 0; i < lcd.getW(); i++)
	{
		lcd.setPos(i, 1).print((char)255);

		delay(spd);
	}

	delay(msg);	
	
	lcd.clear();
}

void showIP()
{
	lcd.clear();
	const char* e0 = Net::getAddr("eth0");
	lcd.printf("e0 %s", (e0 ? e0 : "Offline"));

	lcd.setPos(0, 1);
	const char* w0 = Net::getAddr("wlan0");
	lcd.printf("w0 %s", (w0 ? w0 : "Offline"));
}

void shiftOut(Pin& ser, Pin& lat, Pin& clk, unsigned value, unsigned n = 8, unsigned usec = 10)
{
	// clear
	ser = lat = clk = 0;
	for (unsigned i = 0; i <= n; i++)
	{
		// latch data
		ser = (value & (1UL << i));
		lat = 1;
		// pulse clock
		clk = 1;
		delayMicroseconds(usec);
		// clear
		ser = lat = clk = 0;
	}
}

// * * * * * * * * * * * * * * //

void printScroll(const std::string& str, unsigned spd)
{
	const unsigned size = str.size();

	if (size == 0)
	{
		lcd.clear();
	}
	else if (size <= 16)
	{
		lcd.clear().print(str);
	}
	else
	{
		lcd.clear().print(str.substr(0, 16));
		delay(spd);

		for (unsigned i = 0; i <= size; i++)
		{
			std::string sub;

			unsigned len = 16;

			if ((i + len) >= size)
			{
				len = (size - i);

				sub = str.substr(i, len);

				sub += std::string((16 - len), ' ');
			}
			else
			{
				sub = str.substr(i, len);
			}

			for (unsigned c = 0, cmax = sub.size(); c < cmax; c++)
			{
				lcd.setPos(c, 0).print(sub.at(c));
			}

			delay(spd);
		}
	}
}

void testScroll()
{
	lcd.clear() << "Test Scroll";
	delay(1000);

	const unsigned spd = 250;

	printScroll("0123456789ABCDEF", spd);
	delay(1000);

	printScroll("FEDCBA9876543210", spd);
	delay(1000);

	printScroll("ABCDEFGHIJKLMNOPQRSTUVWXYZ", spd);
	delay(1000);
}

void testRotary()
{
	lcd.clear() << "Test Rotary";
	delay(1000);

	Pin &btn = gpio[0].setAdr(0).setDir(INPUT).setPud(PUD_DOWN),
		&lhs = gpio[1].setAdr(1).setDir(INPUT).setPud(PUD_DOWN),
		&rhs = gpio[2].setAdr(2).setDir(INPUT).setPud(PUD_DOWN);

	bool bOld = 0, aOld = 0;

	Timer timer;
	int64_t ms;
	timer.start();
	while ((ms = timer.elapsed().millis()) < 15000)
	{
		gpio.readAll();

		if ((*lhs) != aOld)
		{
			if ((*rhs) != (*lhs))
			{
				std::cout << "Left" << std::endl;
			}
			else
			{
				std::cout << "Right" << std::endl;
			}

			aOld = (*lhs);
		}

		bool bNew = !(*btn);
		if (bNew && !bOld)
		{
			std::cout << "Press" << std::endl;
		}
		bOld = bNew;
	}
}

void testBus()
{
	lcd.clear() << "Test Bus";
	delay(1000);

	bus.writeReg8(MCP23017::IODIRA, 0).writeReg8(MCP23017::IODIRB, 0);
	bus.clearAB();

	bus.writeA(0b10101010);
	bus.writeB(0b11001100);
	delay(2500);

	//bus.clearAB();
}

// * * * * * * * * * * * * * * //

void shiftClock()
{
	bus.setPinA(CLK, 0);
	delayMicroseconds(1);
	bus.setPinA(CLK, 1);
	delayMicroseconds(1);
	bus.setPinA(CLK, 0);
}

void shiftBit(bool bit)
{
	bus.setPinA(SER, bit);
	bus.setPinA(LAT, 1);
	shiftClock();
	bus.setPinA(SER, 0);
	bus.setPinA(LAT, 0);
}

void shiftFill(bool bit)
{
	for (unsigned i = 0; i < AMT; i++)
	{
		shiftBit(bit);
	}
}

void shiftClear()
{
	shiftFill(0);
}

void shiftValue(int value)
{
	for (unsigned i = 0; i < AMT; i++)
	{
		shiftBit(value & (1UL << i));
	}
}

void shiftByte(unsigned char value)
{
	for (unsigned i = 0; i < 8; i++)
	{
		//shiftBit(value & (1 << i));
		shiftBit(value & (1UL << i));
		//shiftBit(value & ((unsigned long)1 << i));
	}


}

void shiftInit()
{
	bus.writeReg8(MCP23017::IODIRA, 0b10000);

	bus.setPinA(SER, 0);
	bus.setPinA(OEN, 0);
	bus.setPinA(LAT, 0);
	bus.setPinA(CLK, 0);
	bus.setPinA(CLR, 1);

	shiftClear();
}

// * * * * * * * * * * * * * * //

void regClock()
{
	bus.setPin(RCLK, 0);
	delayMicroseconds(1);
	bus.setPin(RCLK, 1);
	delayMicroseconds(1);
	bus.setPin(RCLK, 0);
}

void regIn()
{
	bus.setPin(RDIR, 1);
}

void regOut()
{
	bus.setPin(RDIR, 0);
}

// * * * * * * * * * * * * * * //

void counterClock()
{
	bus.setPinA(CCLK, 0);
	delayMicroseconds(1);
	bus.setPinA(CCLK, 1);
	delayMicroseconds(1);
	bus.setPinA(CCLK, 0);
}

// * * * * * * * * * * * * * * //

void testShift()
{
	shiftInit();

	for (unsigned i = 0, imax = 10; i < imax; i++)
	{
		lcd.clear().printf("%d/%d", i, imax);

		shiftByte(0xFF); delay(500);
		shiftByte(0xFF); delay(500);
		shiftByte(0xFF); delay(1000);

		shiftByte(0x55); delay(500);
		shiftByte(0x00); delay(500);
		shiftByte(0x55); delay(1000);

		shiftByte(0x55); delay(500);
		shiftByte(0x00); delay(500);
		shiftByte(0x55); delay(1000);

		shiftByte(0x0F); delay(500);
		shiftByte(0x3C); delay(500);
		shiftByte(0xF0); delay(1000);
	}
}

void busMonitor()
{
	bus.writeReg8(MCP23017::IODIRA, 0xFF).writeReg8(MCP23017::IODIRB, 0xFF);

	int a = bus.readA();
	int b = bus.readB();

	lcd.clear().print8(a).setPos(0, 1).print8(b);

	Timer timer;
	timer.start();
	while (timer.elapsed().millis() < 10000)
	{
		int tmp;

		tmp = bus.readA();
		if (a != tmp)
		{
			a = tmp;
			lcd.setPos(0, 0).print8(a);
		}

		tmp = bus.readB();
		if (b != tmp)
		{
			b = tmp;
			lcd.setPos(0, 1).print8(b);
		}
	}
}

void testRegister()
{
	lcd.clear().print("Test Register");

	bus.writeReg8(MCP23017::IODIRA, 0x00).writeA(0xFF);
	//bus.writeReg8(MCP23017::IODIRA, 0xFF);
	bus.writeReg8(MCP23017::IODIRB, 0x00).setPin(RCLR, 1);
	delay(500);

	regClock();
	delay(500);

	regOut();
	delay(500);

	regIn();
	delay(500);
}

void testCounter()
{
	lcd.clear().print("Test Counter");

	bus.writeReg8(MCP23017::IODIRA, 0x00);

	bus.setPin(CRES, 0);
	bus.setPin(CCEN, 0);

	for (unsigned i = 0; i < 10; i++)
	{
		counterClock();
		delay(100);
	}
}

void testSegment()
{
	bus.writeReg8(MCP23017::IODIRA, 0).writeReg8(MCP23017::IODIRB, 0);

	bus.writeA(0b01111);
	bus.writeB(0b11110);
	delay(500);

	bus.writeA(0b0);
	bus.writeB(0b0);
	delay(500);

	bus.writeA(0b11110);
	bus.writeB(0b1111);
	delay(500);

}

void testTiny()
{
	if (int fd = wiringPiI2CSetup(0x04))
	{
		for (unsigned i = 0; i < 4; i++)
		{
			std::cout << ('A' + i) << wiringPiI2CReadReg8(fd, i) << std::endl;
		}
	}
	else
	{
		lcd.clear().print("ATtiny Error");
	}
}

// * * * * * * * * * * * * * * //

int setup()
{
	const std::string filename = (fs.getRoot() + "../../../config.ini");
	INIReader ini(filename);
	if (ini.ParseError() < 0)
	{
		std::cerr << "Failed loading \'" << filename << "\'" << std::endl;
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "Loaded INI: \'" << filename << "\'" << std::endl;
	}

	if (wiringPiSetup() < 0)
	{
		std::cerr << "WiringPi setup failed" << std::endl;
		return EXIT_FAILURE;
	}

	if (!lcd.setup())
	{
		std::cerr << "LCD setup failed" << std::endl;
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

	showLoading(50, 50);

	if (argc >= 2)
	{
		switch (argv[1][0])
		{
		case 'c':	testCounter();	break;
		case 'b':	busMonitor();	break;
		case 'r':	testRegister();	break;
		case 's':	testShift();	break;
		case '7':	testSegment();  break;
		case 't':	testTiny();		break;
		case 'i':
		default:	showIP();		break;
		}
	}

	auto foo = 0b1100;
	auto bar = 0b11;

	return EXIT_SUCCESS;
}

// * * * * * * * * * * * * * * //
