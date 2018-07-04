#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <Pin.h>
#include <vector>

namespace pi
{
	// A collection of pins
	template <unsigned N>
	class Register
	{
	public:
		enum { MAX_PIN = N };

	public:
		using array_type			= std::vector<Pin>;
		using iterator				= array_type::iterator;
		using const_iterator		= array_type::const_iterator;
		using reverse_iterator		= array_type::reverse_iterator;
		using const_reverse_iterator= array_type::reverse_iterator;

	public:
		Register();
		Register(const Register<N>& copy);
		virtual ~Register();

		virtual Register<N>&	setData(unsigned value);
		virtual unsigned		getData() const;

		const Pin&	operator[](unsigned i) const;
		Pin&		operator[](unsigned i);

		Register<N>&	operator=(unsigned value);
		unsigned		operator*() const;
		unsigned		operator~() const;
		
		unsigned		operator+(unsigned value) const;
		unsigned		operator-(unsigned value) const;
		unsigned		operator|(unsigned value) const;
		unsigned		operator&(unsigned value) const;
		unsigned		operator^(unsigned value) const;
		unsigned		operator<<(unsigned value) const;
		unsigned		operator>>(unsigned value) const;
		
		Register<N>&	operator+=(unsigned value);
		Register<N>&	operator-=(unsigned value);
		Register<N>&	operator|=(unsigned value);
		Register<N>&	operator&=(unsigned value);
		Register<N>&	operator^=(unsigned value);
		Register<N>&	operator<<=(unsigned value);
		Register<N>&	operator>>=(unsigned value);

		Register<N>&	operator++();
		Register<N>&	operator--();

	public:
		inline iterator					begin()	 { return m_pins.begin();   }
		inline iterator					end()	 { return m_pins.end();		}
		inline const_iterator			cbegin() { return m_pins.cbegin();  }
		inline const_iterator			cend()	 { return m_pins.cend();	}
		inline reverse_iterator			rbegin() { return m_pins.rbegin();  }
		inline reverse_iterator			rend()	 { return m_pins.rend();	}
		inline const_reverse_iterator	crbegin(){ return m_pins.crbegin(); }
		inline const_reverse_iterator	crend()	 { return m_pins.crend();   }

	private:
		array_type		 m_pins;
		mutable unsigned m_value;
	};

	template <unsigned N>
	inline std::ostream& operator<<(std::ostream& out, const Register<N>& reg)
	{
		for (unsigned i = 0; i < N; i++)
		{
			out << reg[i] << std::endl;
		}
		return out;
	}

	template <unsigned N>
	inline std::istream& operator>>(std::istream& in, Register<N>& reg)
	{
		for (unsigned i = 0; i < N; i++)
		{
			if (in.good())
			{
				in << reg[i];
			}
			else
			{
				break;
			}
		}
		return in;
	}


	template <unsigned N>
	inline bool operator==(const Register<N>& lhs, unsigned rhs)
	{
		return (*lhs) == rhs;
	}

	template <unsigned N>
	inline bool operator!=(const Register<N>& lhs, unsigned rhs)
	{
		return (*lhs) != rhs;
	}

	template <unsigned N>
	inline bool operator<(const Register<N>& lhs, unsigned rhs)
	{
		return (*lhs) < rhs;
	}

	template <unsigned N>
	inline bool operator>(const Register<N>& lhs, unsigned rhs)
	{
		return (*lhs) > rhs;
	}

	template <unsigned N>
	inline bool operator<=(const Register<N>& lhs, unsigned rhs)
	{
		return (*lhs) <= rhs;
	}

	template <unsigned N>
	inline bool operator>=(const Register<N>& lhs, unsigned rhs)
	{
		return (*lhs) >= rhs;
	}


	template <unsigned N>
	inline bool operator==(const Register<N>& lhs, const Register<N>& rhs)
	{
		return lhs == (*rhs);
	}

	template <unsigned N>
	inline bool operator!=(const Register<N>& lhs, const Register<N>& rhs)
	{
		return !(lhs == rhs);
	}

	template <unsigned N>
	inline bool operator<(const Register<N>& lhs, const Register<N>& rhs)
	{
		return lhs < (*rhs);
	}

	template <unsigned N>
	inline bool operator>(const Register<N>& lhs, const Register<N>& rhs)
	{
		return lhs > (*rhs);
	}

	template <unsigned N>
	inline bool operator<=(const Register<N>& lhs, const Register<N>& rhs)
	{
		return lhs <= (*rhs);
	}

	template <unsigned N>
	inline bool operator>=(const Register<N>& lhs, const Register<N>& rhs)
	{
		return lhs >= (*rhs);
	}


	// * Usings * * * * * * * * * * //
	using Reg8	= Register<8>;
	using Reg16 = Register<16>;
}

#include <Register.inl>

#endif // !_REGISTER_H_
