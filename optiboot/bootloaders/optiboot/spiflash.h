#ifndef _SPIFLASH_H_
#define _SPIFLASH_H_

#include <inttypes.h>

// SPI register, port and SS pin config
#define SPI_DDR           DDRB
#define SPI_PORT          PORTB
#define SPI_SS            PINB2

// FLASH register, port and SS pin config
#define FLASHSS_DDR       DDRD
#define FLASHSS_PORT      PORTD
#define FLASHSS           PIND2

// SPI and flash commands
#define SPI_INIT          { SPI_DDR |= _BV(SPI_SS) | _BV(PORTB3) | _BV(PORTB5); } // OUTPUTS for SS, MOSI, SCK
#define SPI_ENABLE        { SPCR |= _BV(MSTR) | _BV(SPE); } //enable SPI and set SPI to MASTER mode
#define SPI_DISABLE       { SPCR &= ~_BV(SPE); }
#define FLASH_SELECT      { FLASHSS_PORT &= ~(_BV(FLASHSS)); }
#define FLASH_UNSELECT    { FLASHSS_PORT |= _BV(FLASHSS); }

// SPI flash commands
#define SPIFLASH_JEDECID            0x9F  // read JEDEC ID
#define SPIFLASH_CHIPERASE          0x60  // erase entire chip
#define SPIFLASH_ARRAYREADLOWFREQ   0x03  // read array (low frequency)
#define SPIFLASH_WRITEENABLE        0x06  // write enable
#define SPIFLASH_STATUSWRITE        0x01  // write status register
#define SPIFLASH_STATUSREAD         0x05  // read status register
//#define SPIFLASH_BLOCKERASE_32K   0x52   // erase one 32K block of flash memory
#define SPIFLASH_BLOCKERASE_64K     0xD8     // erase one 64K block of flash memory
// #define SPIFLASH_BLOCKERASE      0x52   // erase one block of flash memory (size depends on model)

// Function prototypes
uint8_t SPI_transfer(uint8_t _data);
uint8_t FLASH_busy();
void    FLASH_command(uint8_t cmd, uint8_t isWrite);
uint8_t FLASH_readByte(uint32_t addr);

#endif