#include <MCP23017.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>

namespace pi
{
	MCP23017::MCP23017()
		: m_addr(-1)
		, m_handle(-1)
	{
	}

	MCP23017::MCP23017(int addr)
		: m_addr(addr)
		, m_handle(-1)
	{
	}

	MCP23017::MCP23017(const MCP23017 & copy)
		: m_addr(copy.m_addr)
		, m_handle(copy.m_handle)
	{
	}

	MCP23017::~MCP23017()
	{
	}


	bool MCP23017::getPin(unsigned pin) const
	{
		if (pin < MCP23017::A_MAX)
		{
			int bit = (1 << (pin & 7));

			return getA() & bit;
		}
		else if (pin < MCP23017::B_MAX)
		{
			int bit = (1 << ((pin - 8) & 7));

			return getA() & bit;
		}
		return -1;
	}

	int MCP23017::getPud(unsigned pin) const
	{
		if (pin < MCP23017::A_MAX)
		{
			int bit = (1 << (pin & 7));

			return getReg(MCP23017::GPPUA) & bit;
		}
		else if (pin < MCP23017::B_MAX)
		{
			int bit = (1 << ((pin - 8) & 7));

			return getReg(MCP23017::GPPUB) & bit;
		}
		return -1;
	}

	MCP23017 & MCP23017::setPin(unsigned pin, bool value)
	{
		if (pin < MCP23017::A_MAX)
		{
			int bit = (1 << (pin & 7));
			if (value)
			{
				return setA(m_reg[MCP23017::OLATA] | bit);
			}
			else
			{
				return setA(m_reg[MCP23017::OLATA] & (~bit));
			}
		}
		else if (pin < MCP23017::B_MAX)
		{
			int bit = (1 << ((pin - 8) & 7));
			if (value)
			{
				return setB(m_reg[MCP23017::OLATB] | bit);
			}
			else
			{
				return setB(m_reg[MCP23017::OLATB] & (~bit));
			}
		}
		return (*this);
	}

	MCP23017 & MCP23017::setPud(unsigned pin, int value)
	{
		if (pin < MCP23017::A_MAX)
		{
			int bit = (1 << (pin & 7));
			if (value)
			{
				return setReg(MCP23017::GPPUA, m_reg[MCP23017::GPPUA] | bit);
			}
			else
			{
				return setReg(MCP23017::GPPUA, m_reg[MCP23017::GPPUA] & (~bit));
			}
		}
		else if(pin < MCP23017::B_MAX)
		{
			int bit = (1 << ((pin - 8) & 7));
			if (value)
			{
				return setReg(MCP23017::GPPUB, m_reg[MCP23017::GPPUB] | bit);
			}
			else
			{
				return setReg(MCP23017::GPPUB, m_reg[MCP23017::GPPUB] & (~bit));
			}
		}
		return (*this);
	}
	
	
	bool MCP23017::setup()
	{
		if ((m_handle = wiringPiI2CSetup(m_addr)) >= 0)
		{
			for (int i = 0; i < MCP23017::MAX_PIN; i++)
			{
				m_pins[i].bus(this).addr(i).mode(OUTPUT).pud(PUD_OFF);
			}

			return true;
		}
		return false;
	}


	MCP23017 & MCP23017::clearA()
	{
		return setReg(MCP23017::OLATA, 0);
	}

	MCP23017 & MCP23017::clearB()
	{
		return setReg(MCP23017::OLATB, 0);
	}

	MCP23017 & MCP23017::clearAB()
	{
		return clearA().clearB();
	}


	MCP23017 & MCP23017::setA(int value)
	{
		return setReg(MCP23017::OLATA, value);
	}
	
	MCP23017 & MCP23017::setB(int value)
	{
		return setReg(MCP23017::OLATB, value);
	}
	
	MCP23017 & MCP23017::setAB(int i)
	{
		return setA((char)(i & 0xFF)).setB((char)(((i >> 8) & 0xFF)));
	}
				 
	MCP23017 & MCP23017::setReg(int reg, int value)
	{
		m_reg[reg] = value;
		wiringPiI2CWriteReg8(handle(), reg, value);
		return (*this);
	}
	
	
	int MCP23017::getA() const
	{
		return getReg(MCP23017::GPIOA);
	}
	
	int MCP23017::getB() const
	{
		return getReg(MCP23017::GPIOB);
	}

	int MCP23017::getReg(int reg) const
	{
		return (m_reg[reg] = wiringPiI2CReadReg8(handle(), reg));
	}


	// * Pins * * * * * * * * * * * * //

	const Pin & MCP23017::operator[](unsigned index) const
	{
		return m_pins.at(index);
	}

	Pin & MCP23017::operator[](unsigned index)
	{
		return m_pins[index];
	}

		
	MCP23017::iterator MCP23017::begin()
	{
		return m_pins.begin();
	}
	
	MCP23017::iterator MCP23017::end()
	{
		return m_pins.end();
	}
	
	MCP23017::const_iterator MCP23017::begin() const
	{
		return m_pins.begin();
	}
	
	MCP23017::const_iterator MCP23017::end() const
	{
		return m_pins.end();
	}
	
	MCP23017::const_iterator MCP23017::cbegin() const
	{
		return m_pins.cbegin();
	}
	
	MCP23017::const_iterator MCP23017::cend() const
	{
		return m_pins.cend();
	}
	
	MCP23017::reverse_iterator MCP23017::rbegin()
	{
		return m_pins.rbegin();
	}
	
	MCP23017::reverse_iterator MCP23017::rend()
	{
		return m_pins.rend();
	}
	
	MCP23017::const_reverse_iterator MCP23017::crbegin() const
	{
		return m_pins.crbegin();
	}
	
	MCP23017::const_reverse_iterator MCP23017::crend() const
	{
		return m_pins.crend();
	}
}
