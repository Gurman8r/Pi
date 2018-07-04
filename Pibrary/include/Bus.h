#ifndef _BUS_H_
#define _BUS_H_

#include <Export.h>

namespace pi
{
	class PI_API Bus
	{
	public:
		Bus() {};
		virtual ~Bus() {};

		virtual bool	getPin(unsigned pin) const = 0;
		virtual int		getPud(unsigned) const = 0;

		virtual Bus&	setPin(unsigned pin, bool value) = 0;
		virtual Bus&	setPud(unsigned pin, int value) = 0;

	private:

	};
}

#endif // !_BUS_H_
