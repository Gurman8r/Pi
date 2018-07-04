#ifndef _DRIVER_I2C_H_
#define _DRIVER_I2C_H_

#include <Driver.h>
#include <RegisterI2C.h>

namespace pi
{
	class DriverI2C : public Driver
	{
	public:
		DriverI2C(int port);
		virtual ~DriverI2C();

		virtual bool setup();
		
		inline const bool&	good()	const { return m_good;   };
		inline const int&	addr()	const { return m_addr;   };
		inline const int&	handle()const { return m_handle; };

	private:
		bool	m_good;
		int		m_addr;
		int		m_handle;
	};
}

#endif // !_DRIVER_I2C_H_
