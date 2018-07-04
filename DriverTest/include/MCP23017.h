#ifndef _MCP23017_H_
#define _MCP23017_H_

#include <DriverI2C.h>

namespace pi
{
	class MCP23017 : public DriverI2C
	{
	public:
		MCP23017(int port);
		~MCP23017();

		bool setup() override;

	private:

	};

	
}

#endif // !_MCP23017_H_
