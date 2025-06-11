#ifndef LCD_H_
#define LCD_H_

void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(unsigned char row, unsigned char col);
void lcd_putc(char c);
void lcd_print(const char *str);

#endif /* LCD_H_ */

