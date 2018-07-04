#include <PiGPIO.h>
#include <wiringPi.h>

namespace pi
{
	PiGPIO::PiGPIO()
		: m_new(0)
		, m_old(0)
	{
	}

	PiGPIO::~PiGPIO()
	{
	}


	int PiGPIO::setAB(int index, int mode, int pud)
	{
		pinMode(index, mode);
		pullUpDnControl(index, pud);
		return index;
	}


	PiGPIO & PiGPIO::beginStep()
	{
		m_new = 0;
		for (int i = 0; i < MAX_PIN; i++)
		{
			m_new |= digitalRead(i) << i;
		}
		return (*this);
	}
	
	PiGPIO & PiGPIO::endStep()
	{
		m_old = m_new;
		return (*this);
	}
	
	
	bool PiGPIO::getPin(int index) const
	{
		return (m_new & (1 << index));
	}
	
	bool PiGPIO::getPinOff(int index) const
	{
		return (m_new & (1 << index)) && !(m_old & (1 << index));
	}
	
	bool PiGPIO::getPinOn(int index) const
	{
		return !(m_new & (1 << index)) && (m_old & (1 << index));
	}
}
