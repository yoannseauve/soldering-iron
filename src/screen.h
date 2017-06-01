#define LCD_CONTRAST 54

#define LCD_X     84
#define LCD_Y     48

typedef enum{LCD_C, LCD_D} LCDMOD;

void screen_init();
void lcd_send(LCDMOD mod, unsigned int nbBytes, const unsigned char bytes[]);
void lcd_clear();
void lcd_write(const char string[]);
void lcd_gotoXY(unsigned int x, unsigned int y);
