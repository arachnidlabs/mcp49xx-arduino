#ifndef __ARDUINO_MCP49XX_H
#define __ARDUINO_MCP49XX_H

#include <Arduino.h>
#include <SPI.h>

extern "C" {
	#include <mcp49xx/mcp49xx.h>
}

class MCP49XX {
	public:
		MCP49XX(byte select_pin = SS);

		void begin();

		void setIsBuffered(uint8_t idx, uint8_t is_buffered) {
			mcp49xx_set_is_buffered(&dac, idx, is_buffered);
		}

		void setGain(uint8_t idx, mcp49xx_gain_t gain) {
			mcp49xx_set_gain(&dac, idx, gain);
		}

		void setIsShutdown(uint8_t idx, uint8_t is_shutdown) {
			mcp49xx_set_is_shutdown(&dac, idx, is_shutdown);
		}

		void write(uint8_t idx, uint16_t data) {
			mcp49xx_write(&dac, idx, data);
		}

		void spi_transfer(char data[], int len);
		byte m_select_pin;
	private:
		mcp49xx_t dac;
};

#endif
