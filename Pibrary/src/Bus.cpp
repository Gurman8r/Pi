#include <Bus.h>
#include <wiringPi.h>
#include <cassert>

namespace pi
{
	Bus::Bus()
		: m_pins(0)
	{
	}

	Bus::Bus(unsigned size)
		: m_pins(size)
	{
	}

	Bus::Bus(const Bus& copy)
		: m_pins(copy.m_pins)
	{
	}

	Bus::~Bus()
	{
	}



	int Bus::getData() const
	{
		m_data = 0;
		for (unsigned i = 0, imax = size(); i++ < imax;)
		{
			m_data |= (*getPin(i)) << 1UL;
		}
		return m_data;
	}

	Bus & Bus::setData(int value)
	{
		m_data = value;
		for (unsigned i = 0, imax = size(); i++ < imax;)
		{
			getPin(i) = (m_data & (1UL << i));
		}
		return (*this);
	}


	const Pin & Bus::getPin(unsigned i) const
	{
		assert(i < m_pins.size());
		return m_pins.at(i);
	}

	Pin & Bus::getPin(unsigned i)
	{
		assert(i < m_pins.size());
		return m_pins[i];
	}


	void Bus::writeAll() const
	{
		for (Bus::const_iterator it = cbegin(); it != cend(); it++)
		{
			//digitalWrite(it->getAdr(), it->getBit());

			it->write();
		}
	}

	void Bus::readAll()
	{
		for (Bus::iterator it = begin(); it != end(); it++)
		{
			//it->setBit(digitalRead(it->getAdr()));

			it->read();
		}
	}



	const Pin & Bus::operator[](unsigned i) const
	{
		return getPin(i);
	}

	Pin & Bus::operator[](unsigned i)
	{
		return getPin(i);
	}

	
	Bus & Bus::operator=(int value)
	{
		return setData(value);
	}

	Bus & Bus::operator=(const Bus & copy)
	{
		return setData(copy.getData());
	}


	int Bus::operator|(int value) const
	{
		return getData() | value;
	}

	int Bus::operator&(int value) const
	{
		return getData() & value;
	}

	int Bus::operator^(int value) const
	{
		return getData() ^ value;
	}

	int Bus::operator<<(int value) const
	{
		return getData() << value;
	}

	int Bus::operator>>(int value) const
	{
		return getData() >> value;
	}


	Bus & Bus::operator|=(int value)
	{
		return (*this);
	}
	
	Bus & Bus::operator&=(int value)
	{
		return (*this);
	}
	
	Bus & Bus::operator^=(int value)
	{
		return (*this);
	}
	
	Bus & Bus::operator<<=(int value)
	{
		return (*this);
	}
	
	Bus & Bus::operator>>=(int value)
	{
		return (*this);
	}
}
