#ifndef _PIBRARY_EXPORT_H_
#define _PIBRARY_EXPORT_H_

#if __GNUC__ >= 4
	// GCC 4 has special keywords for showing/hidding symbols,
	// the same keyword is used for both importing and exporting
	#define PI_API_EXPORT __attribute__ ((__visibility__ ("default")))
	#define PI_API_IMPORT __attribute__ ((__visibility__ ("default")))
#else
	// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
	#define PI_API_EXPORT
	#define PI_API_IMPORT
#endif

#if defined(PI_API_EXPORTS)
	#define PI_API PI_API_EXPORT
#else
	#define PI_API PI_API_IMPORT
#endif

namespace pi
{
	using byte = unsigned short;
}

#endif // !_PIBRARY_EXPORT_H_
