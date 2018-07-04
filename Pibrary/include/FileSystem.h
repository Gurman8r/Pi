#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_

#include <Export.h>
#include <string>

namespace pi
{
	class PI_API FileSystem
	{
	public:
		FileSystem();
		~FileSystem();

		std::string getCwd() const;
		std::string	getRoot() const;
		bool		setCwd(const std::string& value);

	private:
	};
}

#endif // !_FILE_SYSTEM_H_
