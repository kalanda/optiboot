#include <avr/io.h>
#include "spiflash.h"

/**
 * SPI Flash functions
 */
uint8_t SPI_transfer(uint8_t _data) {

  SPDR = _data;
  while (!(SPSR & _BV(SPIF)));

  return SPDR;
}
/**
 * Check if flash is busy
 *
 * @return 1 if is busy or 0 if ready
 */
uint8_t FLASH_busy() {

  FLASH_SELECT;
  SPI_transfer(SPIFLASH_STATUSREAD);
  uint8_t status = SPI_transfer(0);
  FLASH_UNSELECT;

  return status & 1;
}

/**
 * Sends a FLASH command to SPI
 *
 * @param cmd     Command code
 * @param isWrite true if is write command
 */
void FLASH_command(uint8_t cmd, uint8_t isWrite) {

  if (isWrite) {
    FLASH_command(SPIFLASH_WRITEENABLE, 0); // Write Enable
    FLASH_UNSELECT;
  }
  while(FLASH_busy()); //wait for chip to become available
  FLASH_SELECT;
  SPI_transfer(cmd);
}

/**
 * Reads a byte at specific address of flash memory
 *
 * @param  addr Address of the byte to read
 *
 * @return      The reading byte
 */
uint8_t FLASH_readByte(uint32_t addr) {

  FLASH_command(SPIFLASH_ARRAYREADLOWFREQ, 0);
  SPI_transfer(addr >> 16);
  SPI_transfer(addr >> 8);
  SPI_transfer(addr);

  uint8_t result = SPI_transfer(0);
  FLASH_UNSELECT;

  return result;
}