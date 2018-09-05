#include <MCP23017.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>

#define WRITE_DELAY 1

namespace pi
{
	MCP23017::MCP23017()
		: m_addr(-1)
		, m_handle(-1)
		, m_ioa(0)
		, m_iob(0)
	{
	}

	MCP23017::MCP23017(int addr)
		: m_addr(addr)
		, m_handle(-1)
		, m_ioa(0)
		, m_iob(0)
	{
	}

	MCP23017::MCP23017(const MCP23017 & copy)
		: m_addr(copy.m_addr)
		, m_handle(copy.m_handle)
		, m_ioa(copy.m_ioa)
		, m_iob(copy.m_iob)
	{
	}

	MCP23017::~MCP23017()
	{
	}


	bool MCP23017::setup()
	{
		if ((m_handle = wiringPiI2CSetup(m_addr)) >= 0)
		{
			return true;
		}
		return false;
	}


	MCP23017 & MCP23017::clearA()
	{
		return writeA(0);
	}

	MCP23017 & MCP23017::clearB()
	{
		return writeB(0);
	}

	MCP23017 & MCP23017::clearAB()
	{
		return clearA().clearB();
	}


	MCP23017 & MCP23017::setPin(unsigned pin, bool value)
	{
		return (pin < 8) ? setPinA(pin, value) : setPinB(pin - 8, value);
	}

	MCP23017 & MCP23017::setPinA(unsigned pin, bool value)
	{
		if (pin < 8)
		{
			if (value)
			{
				m_ioa |= 1UL << pin;
			}
			else
			{
				m_ioa &= ~(1UL << pin);
			}
			return writeA(m_ioa);
		}
		return (*this);
	}

	MCP23017 & MCP23017::setPinB(unsigned pin, bool value)
	{
		if (pin < 8)
		{
			if (value)
			{
				m_iob |= 1UL << pin;
			}
			else
			{
				m_iob &= ~(1UL << pin);
			}
			return writeB(m_iob);
		}
		return (*this);
	}


	MCP23017 & MCP23017::writeA(int value)
	{
		return writeReg8(MCP23017::GPIOA, value);
	}

	MCP23017 & MCP23017::writeB(int value)
	{
		return writeReg8(MCP23017::GPIOB, value);
	}

	MCP23017 & MCP23017::writeAB(int i)
	{
		return writeA((char)(i & 0xFF)).writeB((char)(((i >> 8) & 0xFF)));
	}

	MCP23017 & MCP23017::writeReg8(int reg, int value)
	{
		switch (reg)
		{
		case MCP23017::GPIOA:
		case MCP23017::OLATA:
			m_ioa = value;
			break;
		case MCP23017::GPIOB:
		case MCP23017::OLATB:
			m_iob = value;
			break;
		}

		wiringPiI2CWriteReg8(handle(), reg, static_cast<char>(value));
		delayMicroseconds(WRITE_DELAY);
		return (*this);
	}


	bool MCP23017::getPin(unsigned pin) const
	{
		return (pin < 8) ? getPinA(pin) : getPinB(pin - 8);
	}

	bool MCP23017::getPinA(unsigned pin) const
	{
		return (pin < 8) ? ((readA() >> pin) & 1UL) : false;
	}

	bool MCP23017::getPinB(unsigned pin) const
	{
		return (pin < 8) ? ((readB() >> pin) & 1UL) : false;
	}


	int MCP23017::readA() const
	{
		return (m_ioa = wiringPiI2CReadReg8(handle(), MCP23017::GPIOA));
	}

	int MCP23017::readB() const
	{
		return (m_iob = wiringPiI2CReadReg8(handle(), MCP23017::GPIOB));
	}
}
