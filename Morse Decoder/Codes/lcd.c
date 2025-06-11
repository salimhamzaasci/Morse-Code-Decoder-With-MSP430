#include <msp430.h>
#include "lcd.h"

#define RS BIT0   // P2.0
#define EN BIT1   // P2.1
#define D4 BIT2   // P2.2
#define D5 BIT3   // P2.3
#define D6 BIT4   // P2.4
#define D7 BIT5   // P2.5

#define OUT P2OUT
#define DIR P2DIR

static void pulse(void) {
    OUT |= EN; __delay_cycles(1000);
    OUT &= ~EN; __delay_cycles(1000);
}

static void nibble(unsigned char x) {
    OUT &= ~(D4|D5|D6|D7);
    if (x & 1) OUT |= D4;
    if (x & 2) OUT |= D5;
    if (x & 4) OUT |= D6;
    if (x & 8) OUT |= D7;
    pulse();
}

static void write8(unsigned char b, int data) {
    if (data) OUT |= RS; else OUT &= ~RS;
    nibble(b >> 4);
    nibble(b & 0x0F);
    __delay_cycles(2000);
}

void lcd_init(void) {
    DIR |= RS|EN|D4|D5|D6|D7;
    OUT &= ~(RS|EN|D4|D5|D6|D7);
    __delay_cycles(15000);
    nibble(3); __delay_cycles(5000);
    nibble(3); __delay_cycles(5000);
    nibble(3); __delay_cycles(200);
    nibble(2);
    write8(0x28,0);   // 4-bit, 2 satır
    write8(0x0C,0);   // display ON, cursor OFF
    write8(0x06,0);   // entry mode
    write8(0x01,0);   // clear display
    __delay_cycles(2000);
}

void lcd_clear(void) {
    write8(0x01,0);
    __delay_cycles(2000);
}

void lcd_set_cursor(unsigned char row, unsigned char col) {
    unsigned char addr = (row==2?0x40:0x00) + col;
    write8(0x80|addr,0);
}

void lcd_putc(char c) {
    write8((unsigned char)c,1);
}

void lcd_print(const char *s) {
    while (*s) lcd_putc(*s++);
}