#ifndef _PIN_H_
#define _PIN_H_

#include <iostream>
#include <string>
#include <cassert>

namespace pi
{
	// Represents a single bit in a register
	class Pin
	{
	public:
		enum IOD : int // IO Direction
		{
			INVALID_IODIR = -1,
			Input,
			Output,
			MAX_IODIR
		};
		enum PUD : int // Pull Up/Down Control
		{
			INVALID_PUDC = -1,
			Off,
			Down,
			Up,
			MAX_PUDC
		};
		
		static const char IODIR_IDs[MAX_IODIR];
		static const char PUDC_IDs[MAX_PUDC];

		inline friend std::ostream& operator<<(std::ostream& out, const IOD& value)
		{
			return (out << Pin::IODIR_IDs[value]);
		}
		inline friend std::ostream& operator<<(std::ostream& out, const PUD& value)
		{
			return (out << Pin::PUDC_IDs[value]);
		}

	public:
		Pin();
		Pin(int adr, bool bit, IOD dir, PUD pud);
		Pin(const Pin& copy);
		virtual ~Pin();

		virtual Pin& setAdr(int value);
		virtual Pin& setBit(bool value);
		virtual Pin& setDir(int value);
		virtual Pin& setPud(int value);

		virtual const int&		getAdr() const;
		virtual const bool&		getBit() const;
		virtual const IOD&		getDir() const;
		virtual const PUD&		getPud() const;

		virtual Pin& operator=(bool value);
		virtual bool operator*() const;

		friend std::ostream& operator<<(std::ostream& out, const Pin& pin);
		friend std::istream& operator>>(std::istream& in, Pin& pin);

	private:
		mutable int		m_adr;  // Address
		mutable bool	m_bit;  // Pin Value
		mutable IOD		m_dir;  // I/O Direction
		mutable PUD		m_pud;  // Pull Up/Down Control
	};

	
	inline bool operator==(const Pin& lhs, const Pin& rhs)
	{
		return lhs.getBit() == rhs.getBit();
	}

	inline bool operator!=(const Pin& lhs, const Pin& rhs)
	{
		return !(lhs == rhs);
	}

	inline bool operator==(const Pin& lhs, bool rhs)
	{
		return lhs.getBit() == rhs;
	}

	inline bool operator!=(const Pin& lhs, bool rhs)
	{
		return !(lhs == rhs);
	}
	
}

#endif // !_PIN_H_
