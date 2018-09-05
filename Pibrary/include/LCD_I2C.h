#ifndef _LiquidCrystal_I2C_H_
#define _LiquidCrystal_I2C_H_

#include <Export.h>
#include <string>

namespace pi
{
	class PI_API LCD_I2C
	{
	public:
		LCD_I2C();
		LCD_I2C(int address, int width, int height);
		LCD_I2C(const LCD_I2C& copy);
		~LCD_I2C();

		bool setup();

		LCD_I2C& blink(bool value);
		LCD_I2C& clear();
		LCD_I2C& cursor(bool value);
		LCD_I2C& display(int value);
		LCD_I2C& home();
		LCD_I2C& modPos(int dx, int dy);
		LCD_I2C& setPos(int x, int y);
		LCD_I2C& setX(int value);
		LCD_I2C& setY(int value);

		LCD_I2C& print(int value);
		LCD_I2C& print(double value);
		LCD_I2C& print(float value);
		LCD_I2C& print(char value);
		LCD_I2C& print(const char* value);
		LCD_I2C& print(const std::string& value);
		LCD_I2C& printf(const char* fmt, ...);
		LCD_I2C& print8(int value);
		LCD_I2C& print16(int value);

		LCD_I2C& sendByte(int value, int mode);
		LCD_I2C& sendCommand(int value);
		LCD_I2C& sendData(int value);

		inline int	address()	const { return m_address; }
		inline int	handle()	const { return m_handle; }
		inline int	getW()		const { return m_w; }
		inline int	getH()		const { return m_h; }
		inline int	getX()		const { return m_x; }
		inline int	getY()		const { return m_y; }

		inline LCD_I2C& operator<<(int value) { return print(value); }
		inline LCD_I2C& operator<<(double value) { return print(value); }
		inline LCD_I2C& operator<<(float value) { return print(value); }
		inline LCD_I2C& operator<<(char value) { return print(value); }
		inline LCD_I2C& operator<<(const char* value) { return print(value); }
		inline LCD_I2C& operator<<(const std::string& value) { return print(value); }

	private:
		int	m_address;
		int	m_handle;
		int	m_w, m_h;
		int	m_x, m_y;

		mutable std::string m_str;
	};
}

#endif // !_LiquidCrystal_I2C_H_
