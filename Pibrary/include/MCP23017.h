#ifndef _MCP23017_H_
#define _MCP23017_H_

#include <array>
#include <Bus.h>
#include <Pin.h>

namespace pi
{
	class PI_API MCP23017 : public Bus
	{
	public:
		enum
		{
			MAX_PIN = 16,
			A_MIN = 0,
			B_MIN = 8,
			A_MAX = B_MIN,
			B_MAX = MAX_PIN,
		};

	public:
		using array_type			= std::array<Pin, MAX_PIN>;
		using iterator				= array_type::iterator;
		using const_iterator		= array_type::const_iterator;
		using reverse_iterator		= array_type::reverse_iterator;
		using const_reverse_iterator= array_type::const_reverse_iterator;

	public:
		enum Register
		{
			IODIRA		= 0x00, //	A | I/O Direction
			IODIRB		= 0x01, //	B | I/O Direction
			IPOLA		= 0x02, //	A | Pin Inversion
			IPOLB		= 0x03, //	B | Pin Inversion
			GPINTENA	= 0x04, //	A | 
			GPINTENB	= 0x05, //	B | 
			DEFVALA		= 0x06, //	A | Default Value
			DEFVALB		= 0x07, //	B | Default Value
			INTCONA		= 0x08, //	A | Interrupt Condition
			INTCONB		= 0x09, //	B | Interrupt Condition
			IOCONA		= 0x0A, //	A | 
			IOCONB		= 0x0B, //	B | 
			GPPUA		= 0x0C, //	A | Pullup Control
			GPPUB		= 0x0D, //	B | Pullup Control
			INTFA		= 0x0E, //	A | Interrupt Flag
			INTFB		= 0x0F, //	B | Interrupt Flag
			INTCAPA		= 0x10, //	A | Interrupt Data Capture
			INTCAPB		= 0x11, //	B | Interrupt Data Capture
			GPIOA		= 0x12, //	A | I/O Registers
			GPIOB		= 0x13, //	B | I/O Registers
			OLATA		= 0x14, //	A | Output Latch
			OLATB		= 0x15, //	B | Output Latch
			MAX_REGISTER
		};
	public:
		MCP23017();
		MCP23017(int addr);
		MCP23017(const MCP23017& copy);
		~MCP23017();
				
		bool		getPin(unsigned pin) const override;
		int			getPud(unsigned pin) const override;
		MCP23017&	setPin(unsigned pin, bool value) override;
		MCP23017&	setPud(unsigned pin, int value) override;
		
		bool setup();
		
		MCP23017& clearA();
		MCP23017& clearB();
		MCP23017& clearAB();
		
		MCP23017& setA(int value);
		MCP23017& setB(int value);
		MCP23017& setAB(int value);
		MCP23017& setReg(int reg, int value);

		int getA() const;
		int getB() const;
		int getReg(int reg) const;

		inline const int& addr()   const { return m_addr;   };
		inline const int& handle() const { return m_handle; };

	public:
		const Pin&	operator[](unsigned index) const;
		Pin&		operator[](unsigned index);

		MCP23017::iterator					begin();
		MCP23017::iterator					end();
		MCP23017::const_iterator			begin() const;
		MCP23017::const_iterator			end()	const;
		MCP23017::const_iterator			cbegin()const;
		MCP23017::const_iterator			cend()	const;
		MCP23017::reverse_iterator			rbegin();
		MCP23017::reverse_iterator			rend();
		MCP23017::const_reverse_iterator	crbegin() const;
		MCP23017::const_reverse_iterator	crend() const;

	private:
		int m_addr;
		int m_handle;
		std::array<Pin, MAX_PIN> m_pins;
		
		mutable int m_reg[MAX_REGISTER];
	};
}

#endif // !_MCP23017_H_
