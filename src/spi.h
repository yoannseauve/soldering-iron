#include <stdlib.h>

typedef enum {SS, SS2} SlaveSelect;
typedef enum {SPI_MOD_0 = 0, SPI_MOD_1 = 1, SPI_MOD_2 = 2, SPI_MOD_3 = 3} SpiMod;

void spi_init(SpiMod);
void spi_transmit(unsigned char tx[], unsigned char rx[], unsigned int nbBytes, SlaveSelect slave);
unsigned char spi_transmission_done();
void spi_switchMod(SpiMod mod);
