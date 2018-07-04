#ifndef _PIN_H_
#define _PIN_H_

#include <Export.h>
#include <iostream>

namespace pi
{
	class Bus;

	class PI_API Pin
	{
	public:
		Pin();
		Pin(Bus* bus, int addr, int mode, int pud);
		Pin(const Pin& copy);
		~Pin();

		const int&	addr() const;
		const Bus*	bus()  const;
		const bool&	get()  const;
		const int&	mode() const;
		const int&	pud()  const;

		Pin& addr(int value);
		Pin& bus(Bus* value);
		Pin& set(bool value);
		Pin& mode(int value);
		Pin& pud(int value);

		inline Pin& operator=(bool value)
		{
			return set(value);
		}
		inline bool operator*() const
		{
			return get();
		}

		inline friend std::ostream& operator<<(std::ostream& out, const Pin& pin)
		{
			return (out << pin.get());
		}
		inline friend bool operator==(const Pin& lhs, const Pin& rhs)
		{
			return lhs.get() == rhs.get();
		}
		inline friend bool operator!=(const Pin& lhs, const Pin& rhs)
		{
			return !(lhs == rhs);
		}
		inline friend bool operator==(const Pin& lhs, bool rhs)
		{
			return lhs.get() == rhs;
		}
		inline friend bool operator!=(const Pin& lhs, bool rhs)
		{
			return !(lhs == rhs);
		}

	private:
		mutable Bus*	m_bus;	// master device
		mutable int		m_addr;	// pin number
		mutable int		m_mode;	// pin mode
		mutable int		m_pud;	// pull up/down control		
		mutable bool	m_bool; // value of pin
	};
}

#endif // !_PIN_H_
