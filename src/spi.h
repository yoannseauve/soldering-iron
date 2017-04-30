typedef enum {SS, SS2} SlaveSelect;

void spi_init();
void spi_transmit(unsigned char tx[], unsigned char rx[], unsigned int nbBytes, SlaveSelect slave);
unsigned char spi_transmission_done();
