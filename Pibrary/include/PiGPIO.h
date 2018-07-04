#ifndef _PI_GPIO_H_
#define _PI_GPIO_H_

#include <Export.h>

namespace pi
{
	class PI_API PiGPIO
	{
	public:
		enum
		{
			Pin0,
			Pin1,
			Pin2,
			Pin3,
			Pin4,
			Pin5,
			Pin6,
			Pin7,
			MAX_PIN
		};
	public:
		PiGPIO();
		~PiGPIO();

		int setAB(int index, int mode, int pud);

		PiGPIO& beginStep();
		PiGPIO& endStep();

		bool getPin(int index) const;
		bool getPinOff(int index) const;
		bool getPinOn(int index) const;

		inline const int& getNew() const { return m_new; };
		inline const int& getOld() const { return m_old; };

	private:
		int m_new, m_old;
	};
}

#endif // !_PI_GPIO_H_
