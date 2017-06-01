#define LCD_CONTRAST 54

#define LCD_X     84
#define LCD_Y     48

typedef enum{LCD_C, LCD_D} LCDMOD;

void screen_init();
void lcd_write(LCDMOD mod, unsigned int nbBytes, unsigned char bytes[]);
void lcd_clear();
