#include <Pin.h>
#include <wiringPi.h>

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
		, m_dir(IOD::In)
		, m_pud(PUD::Off)
		, m_bit(false)
	{
	}

	Pin::Pin(int adr, int dir, int pud)
		: m_adr(adr)
		, m_dir((IOD)dir)
		, m_pud((PUD)pud)
		, m_bit(0)
	{
	}

	Pin::Pin(int adr, bool bit, IOD dir, PUD pud)
		: m_adr(adr)
		, m_dir(dir)
		, m_pud(pud)
		, m_bit(bit)
	{
	}

	Pin::Pin(const Pin & copy)
		: m_adr(copy.m_adr)
		, m_dir(copy.m_dir)
		, m_pud(copy.m_pud)
		, m_bit(copy.m_bit)
	{
	}

	Pin::~Pin()
	{
	}

	void Pin::write() const
	{
		digitalWrite(getAdr(), getBit());
	}

	void Pin::read()
	{
		setBit(digitalRead(getAdr()));
	}

	
	Pin & Pin::setAdr(int value)
	{
		m_adr = value;
		return (*this);
	}

	Pin & Pin::setBit(bool value)
	{
		m_bit = value;
		return (*this);
	}
	
	Pin & Pin::setDir(int value)
	{
		pinMode(getAdr(), (m_dir = (IOD)value));
		return (*this);
	}

	Pin & Pin::setPud(int value)
	{
		pullUpDnControl(getAdr(), (m_pud = (PUD)value));
		return (*this);
	}


	const int &			Pin::getAdr() const
	{
		return m_adr;
	}

	const bool &		Pin::getBit() const
	{
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

	Pin &	Pin::operator=(const Pin & copy)
	{
		return setBit(copy.getBit());
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
