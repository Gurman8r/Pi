#include <wiringPi.h>
#include <Pin.h>
#include <Bus.h>

namespace pi
{
	Pin::Pin()
		: m_bool(false)
		, m_bus(0)
		, m_addr(0)
		, m_mode(INPUT)
		, m_pud(PUD_OFF)
	{
	}

	Pin::Pin(Bus * bus, int addr, int mode, int pud)
		: m_bool(false)
		, m_bus(bus)
		, m_addr(addr)
		, m_mode(mode)
		, m_pud(pud)
	{
	}

	Pin::Pin(const Pin & copy)
		: m_bool(copy.m_bool)
		, m_bus(copy.m_bus)
		, m_addr(copy.m_addr)
		, m_mode(copy.m_mode)
		, m_pud(copy.m_pud)
	{
	}

	Pin::~Pin()
	{
	}


	const int&	Pin::addr() const
	{
		return m_addr;
	}
	const Bus*	Pin::bus()  const
	{
		return m_bus;
	}
	const bool&	Pin::get()  const
	{
		if (m_bus)
		{
			return (m_bool = m_bus->getPin(m_addr));
		}
		return m_bool;
	}
	const int&	Pin::mode() const
	{
		return m_mode;
	}
	const int&	Pin::pud()  const
	{
		if (m_bus)
		{
			return (m_pud = m_bus->getPud(m_addr));
		}
		return m_pud;
	}

	Pin& Pin::addr(int value)
	{
		m_addr = value;
		return (*this);
	}
	Pin& Pin::bus(Bus* value)
	{
		m_bus = value;
		return (*this);
	}
	Pin& Pin::set(bool value)
	{
		if (m_bus)
		{
			m_bus->setPin(m_addr, m_bool = value);
			return (*this);
		}
		return (*this);
	}
	Pin& Pin::mode(int value)
	{
		m_mode = value;
		return (*this);
	}
	Pin& Pin::pud(int value)
	{
		if (m_bus)
		{
			m_bus->setPud(m_addr, m_pud = value);
			return (*this);
		}
		return (*this);
	}
}
