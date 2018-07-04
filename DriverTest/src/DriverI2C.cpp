#include <DriverI2C.h>
#include <wiringPiI2C.h>

namespace pi
{
	DriverI2C::DriverI2C(int port)
		: m_good(false)
		, m_addr(port)
	{
	}

	DriverI2C::~DriverI2C()
	{
	}


	bool DriverI2C::setup()
	{
		return (m_good = ((m_handle = wiringPiI2CSetup(m_addr)) >= 0));
	}
}
