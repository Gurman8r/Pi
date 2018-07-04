#include <Register.h>

namespace pi
{
	// * Constructors * * * * * * * //
	template<unsigned N>
	inline Register<N>::Register()
		: m_pins(N)
		, m_value(0)
	{
	}

	template<unsigned N>
	inline Register<N>::Register(const Register<N>& copy)
		: m_pins(copy.m_pins)
		, m_value(copy.m_value)
	{
	}

	template<unsigned N>
	inline Register<N>::~Register()
	{
	}


	// * Functions* * * * * * * * * //
	template<unsigned N>
	inline Register<N>& Register<N>::setData(unsigned value)
	{
		m_value = value;
		for (unsigned i = 0; i < N; i++)
		{
			(*this)[i] = ((m_value) & (1UL << (i)));
		}
		return (*this);
	}

	template<unsigned N>
	inline unsigned Register<N>::getData() const
	{
		m_value = 0;
		for (unsigned i = 0; i < N; i++)
		{
			m_value |= (*(*this)[i]) << 1UL;
		}
		return m_value;
	}


	// * Operators* * * * * * * * * //
	template<unsigned N>
	inline const Pin & Register<N>::operator[](unsigned i) const
	{
		assert(i < N);
		return m_pins.at(i);
	}

	template<unsigned N>
	inline Pin & Register<N>::operator[](unsigned i)
	{
		assert(i < N);
		return m_pins[i];
	}


	template<unsigned N>
	inline Register<N>& Register<N>::operator=(unsigned value)
	{
		return setData(value);
	}

	template<unsigned N>
	inline unsigned Register<N>::operator*() const
	{
		return getData();
	}

	template<unsigned N>
	inline unsigned Register<N>::operator~() const
	{
		return ~(getData());
	}

	
	template<unsigned N>
	inline unsigned Register<N>::operator+(unsigned value) const
	{
		return getData() + value;
	}

	template<unsigned N>
	inline unsigned Register<N>::operator-(unsigned value) const
	{
		return getData() - value;
	}
		
	template<unsigned N>
	inline unsigned Register<N>::operator|(unsigned value) const
	{
		return getData() | value;
	}

	template<unsigned N>
	inline unsigned Register<N>::operator&(unsigned value) const
	{
		return getData() & value;
	}

	template<unsigned N>
	inline unsigned Register<N>::operator^(unsigned value) const
	{
		return getData() ^ value;
	}

	template<unsigned N>
	inline unsigned Register<N>::operator<<(unsigned value) const
	{
		return getData() << value;
	}

	template<unsigned N>
	inline unsigned Register<N>::operator>>(unsigned value) const
	{
		return getData() >> value;
	}


	template<unsigned N>
	inline Register<N>& Register<N>::operator+=(unsigned value)
	{
		return setData((*this) + value);
	}

	template<unsigned N>
	inline Register<N>& Register<N>::operator-=(unsigned value)
	{
		return setData((*this) - value);
	}

	template<unsigned N>
	inline Register<N>& Register<N>::operator|=(unsigned value)
	{
		return setData((*this) | value);
	}
	
	template<unsigned N>
	inline Register<N>& Register<N>::operator&=(unsigned value)
	{
		return setData((*this) & value);
	}
	
	template<unsigned N>
	inline Register<N>& Register<N>::operator^=(unsigned value)
	{
		return setData((*this) ^ value);
	}
	
	template<unsigned N>
	inline Register<N>& Register<N>::operator<<=(unsigned value)
	{
		return setData((*this) << value);
	}
	
	template<unsigned N>
	inline Register<N>& Register<N>::operator>>=(unsigned value)
	{
		return setData((*this) >> value);
	}
	
	
	template<unsigned N>
	inline Register<N>& Register<N>::operator++()
	{
		return setData((*this) + 1);
	}

	template<unsigned N>
	inline Register<N>& Register<N>::operator--()
	{
		return setData((*this) - 1);
	}
}
