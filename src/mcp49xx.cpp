#include "mcp49xx.h"

static void _transfer_func(void *ctx, char data[], int len) {
	MCP49XX *mcp = (MCP49XX*)ctx;
	mcp->spi_transfer(data, len);
}

void MCP49XX::spi_transfer(char data[], int len) {
	// Set up transfer options
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV128);

	// Assert CS
	digitalWrite(m_select_pin, LOW);

	// Transfer data
	for(int i = 0; i < len; i++)
		data[i] = SPI.transfer(data[i]);

	// Deassert CS
	digitalWrite(m_select_pin, HIGH);

}

MCP49XX::MCP49XX(byte select_pin) : m_select_pin(select_pin) {
}

void MCP49XX::begin() {
	pinMode(m_select_pin, OUTPUT);
	digitalWrite(m_select_pin, HIGH);
	SPI.begin();
	mcp49xx_init(&dac, &_transfer_func, this);
}
