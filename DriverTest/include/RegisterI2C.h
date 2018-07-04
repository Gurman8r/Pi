#ifndef _REGISTER_I2C_H_
#define _REGISTER_I2C_H_

#include <Register.h>

namespace pi
{
	template <unsigned N>
	class RegisterI2C
	{
	public:
		RegisterI2C(int port, int addr);
		RegisterI2C(const RegisterI2C<N>& copy);
		~RegisterI2C();

		RegisterI2C<N>&	setData(unsigned value) override;
		unsigned		getData() const override;

	private:
		int m_port;
		int m_addr;
	};

	// * Constructors * * * * * * * //
	template <unsigned N>
	inline RegisterI2C<N>::RegisterI2C(int port, int addr)
		: Register<N>()
		, m_port(port)
		, m_addr(addr)
	{
	}

	template<unsigned N>
	inline RegisterI2C<N>::RegisterI2C(const RegisterI2C<N>& copy)
		: Register<N>(copy)
		, m_port(copy.m_port)
		, m_addr(copy.m_addr)
	{
	}

	template <unsigned N>
	inline RegisterI2C<N>::~RegisterI2C()
	{
	}


	// * Functions* * * * * * * * * //
	template<unsigned N>
	inline RegisterI2C<N>& RegisterI2C<N>::setData(unsigned value)
	{
		return (*this);
	}

	template<unsigned N>
	inline unsigned RegisterI2C<N>::getData() const
	{
		return 0;
	}


	// * Usings * * * * * * * * * * //
	using RegI2C8 = RegisterI2C<8>;
}

#endif // !_REGISTER_I2C_H_
