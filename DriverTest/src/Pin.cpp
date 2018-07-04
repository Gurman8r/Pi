#include <Pin.h>
#include <wiringPi.h>
#include <iomanip>

namespace pi
{
	const char Pin::IODIR_IDs[Pin::MAX_IODIR] =
	{
		'I','O'
	};

	const char Pin::PUDC_IDs[Pin::MAX_PUDC] = 
	{ 
		'-','D','U'
	};

	Pin::Pin()
		: m_adr(0)
		, m_bit(false)
		, m_dir(IOD::Input)
		, m_pud(PUD::Off)
	{
	}

	Pin::Pin(int adr, bool bit, IOD dir, PUD pud)
		: m_adr(adr)
		, m_bit(bit)
		, m_dir(dir)
		, m_pud(pud)
	{
	}

	Pin::Pin(const Pin & copy)
		: m_adr(copy.m_adr)
		, m_bit(copy.m_bit)
		, m_dir(copy.m_dir)
		, m_pud(copy.m_pud)
	{
	}

	Pin::~Pin()
	{
	}

	
	Pin & Pin::setAdr(int value)
	{
		m_adr = value;
		return (*this);
	}

	Pin & Pin::setBit(bool value)
	{
		if (getDir() == Pin::Output)
		{
			digitalWrite(getAdr(), (m_bit = value));
			return (*this);
		}
		m_bit = value;
		return (*this);
	}
	
	Pin & Pin::setDir(int value)
	{
		//m_dir = (IODIR)value;
		pinMode(getAdr(), (m_dir = (IOD)value));
		return (*this);
	}

	Pin & Pin::setPud(int value)
	{
		//m_pud = (PUDC)value;
		pullUpDnControl(getAdr(), (m_pud = (PUD)value));
		return (*this);
	}


	const int &			Pin::getAdr() const
	{
		return m_adr;
	}

	const bool &		Pin::getBit() const
	{
		if (getDir() == Pin::Input)
		{
			return (m_bit = digitalRead(getAdr()));
		}
		return m_bit;
	}

	const Pin::IOD &	Pin::getDir() const
	{
		return m_dir;
	}

	const Pin::PUD &	Pin::getPud() const
	{
		return m_pud;
	}


	Pin &	Pin::operator=(bool value)
	{
		return setBit(value);
	}

	bool	Pin::operator*() const
	{
		return getBit();
	}


	std::ostream & operator<<(std::ostream & out, const Pin & pin)
	{
		return out
			<< " adr:" << pin.getAdr()
			<< " val:" << pin.getBit()
			<< " dir:" << pin.getDir()
			<< " pud:" << pin.getPud();
	}

	std::istream & operator>>(std::istream & in, Pin & pin)
	{
		if (in.good())
		{
			bool bit;
			in >> bit;
			pin = bit;
		}
		return in;
	}
}
