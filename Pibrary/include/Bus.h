#ifndef _BUS_H_
#define _BUS_H_

#include <Pin.h>
#include <iostream>
#include <vector>

namespace pi
{
	class PI_API Bus
	{
	public:
		using array_type			= std::vector<Pin>;
		using iterator				= array_type::iterator;
		using const_iterator		= array_type::const_iterator;
		using reverse_iterator		= array_type::reverse_iterator;
		using const_reverse_iterator= array_type::const_reverse_iterator;

	public:
		Bus();
		Bus(unsigned size);
		Bus(const Bus& copy);
		virtual ~Bus();

	public:
		virtual int			getData() const;
		virtual Bus&		setData(int value);

		virtual const Pin&	getPin(unsigned i) const;
		virtual Pin&		getPin(unsigned i);

		virtual void		writeAll() const;
		virtual void		readAll();

	public:
		const Pin&	operator[](unsigned i) const;
		Pin&		operator[](unsigned i);

		Bus&	operator=(int value);
		Bus&	operator=(const Bus& copy);

		int		operator|(int value) const;
		int		operator&(int value) const;
		int		operator^(int value) const;
		int		operator<<(int value) const;
		int		operator>>(int value) const;

		Bus&	operator|=(int value);
		Bus&	operator&=(int value);
		Bus&	operator^=(int value);
		Bus&	operator<<=(int value);
		Bus&	operator>>=(int value);

	public:
		inline iterator					begin()			{ return m_pins.begin();	}
		inline iterator					end()			{ return m_pins.end();		}
		inline const_iterator			cbegin() const	{ return m_pins.cbegin();	}
		inline const_iterator			cend()	 const	{ return m_pins.cend();		}
		inline reverse_iterator			rbegin()		{ return m_pins.rbegin();	}
		inline reverse_iterator			rend()			{ return m_pins.rend();		}
		inline const_reverse_iterator	crbegin()const	{ return m_pins.crbegin();	}
		inline const_reverse_iterator	crend()	 const	{ return m_pins.crend();	}

	public:
		inline unsigned	size() const { return m_pins.size(); }

	protected:
		array_type	m_pins;
		mutable int m_data;
	};
}

#endif // !_BUS_H_

