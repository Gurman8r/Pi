#ifndef _MCP23017_H_
#define _MCP23017_H_

#include <Export.h>

namespace pi
{
	class PI_API MCP23017
	{
	public:
		enum
		{
			IODIRA		= 0x00, //	A | IO Direction A
			IODIRB		= 0x01, //	B | IO Direction B
			IPOLA		= 0x02, //	A | Pin Inversion A
			IPOLB		= 0x03, //	B | Pin Inversion B
			GPINTENA	= 0x04, //	A | Interrupt Enable A
			GPINTENB	= 0x05, //	B | Interrupt Enable B
			DEFVALA		= 0x06, //	A | Default Value A
			DEFVALB		= 0x07, //	B | Default Value B
			INTCONA		= 0x08, //	A | Interrupt Condition A
			INTCONB		= 0x09, //	B | Interrupt Condition	B
			IOCONA		= 0x0A, //	A | 
			IOCONB		= 0x0B, //	B | 
			GPPUA		= 0x0C, //	A | Pullup A
			GPPUB		= 0x0D, //	B | Pullup B
			INTFA		= 0x0E, //	A | Interrupt Flag A
			INTFB		= 0x0F, //	B | Interrupt Flag B
			INTCAPA		= 0x10, //	A | Interrupt Data Capture A
			INTCAPB		= 0x11, //	B | Interrupt Data Capture B
			GPIOA		= 0x12, //	A | General Purpose IO A
			GPIOB		= 0x13, //	B | General Purpose IO B
			OLATA		= 0x14, //	A | Output Latch A
			OLATB		= 0x15, //	B | Output Latch B			
			MAX_REGISTER
		};
	public:
		MCP23017();
		MCP23017(int addr);
		MCP23017(const MCP23017& copy);
		~MCP23017();

		bool setup();

		MCP23017& clearA();
		MCP23017& clearB();
		MCP23017& clearAB();

		MCP23017& setPin(unsigned pin, bool value);
		MCP23017& setPinA(unsigned pin, bool value);
		MCP23017& setPinB(unsigned pin, bool value);
		
		MCP23017& writeA(int value);
		MCP23017& writeB(int value);
		MCP23017& writeAB(int value);
		MCP23017& writeReg8(int reg, int value);

		bool getPin(unsigned pin) const;
		bool getPinA(unsigned pin) const;
		bool getPinB(unsigned pin) const;

		int readA() const;
		int readB() const;

		inline int addr()	const { return m_addr; };
		inline int handle() const { return m_handle; };

	private:
		int m_addr;
		int m_handle;

		mutable int m_ioa, m_iob;
	};
}

#endif // !_MCP23017_H_
