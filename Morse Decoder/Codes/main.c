#include <msp430.h>
#include <string.h>
#include "lcd.h"

#define TICK_MS         5
#define DOT_MS         100
#define DASH_MS        300
#define LETTER_PAUSE   400
#define WORD_PAUSE    1000
#define MORSE_THRESHOLD 800
#define LCD_W           16

typedef struct { char symbol; const char *morse; } MorseTable;
const MorseTable morseTable[] = {
  {'A',".-"}, {'B',"-..."},{'C',"-.-."},{'D',"-.."}, {'E',"."},
  {'F',"..-."},{'G',"--."},{'H',"...."},{'I',".."}, {'J',".---"},
  {'K',"-.-"},{'L',".-.."},{'M',"--"},{'N',"-."},{'O',"---"},
  {'P',".--."},{'Q',"--.-"},{'R',".-."},{'S',"..."},{'T',"-"},
  {'U',"..-"},{'V',"...-"},{'W',".--"},{'X',"-..-"},{'Y',"-.--"},
  {'Z',"--.."}, {'1',".----"},{'2',"..---"},{'3',"...--"},
  {'4',"....-"},{'5',"....."},{'6',"-...."},{'7',"--..."},
  {'8',"---.."},{'9',"----."},{'0',"-----"},{'-',"-....-"}
};

char morse_to_char(const char *code){
  unsigned int i;
  for(i=0; i<sizeof(morseTable)/sizeof(morseTable[0]); i++){
    if(strcmp(morseTable[i].morse, code)==0)
      return morseTable[i].symbol;
  }
  return '?';
}

void adc_init(void){
  ADC10CTL1 = INCH_0;
  ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON;
}
unsigned int adc_read(void){
  ADC10CTL0 |= ENC|ADC10SC;
  while (ADC10CTL1 & ADC10BUSY);
  return ADC10MEM;
}

int main(void){
  WDTCTL = WDTPW|WDTHOLD;
  BCSCTL1 = CALBC1_1MHZ; DCOCTL = CALDCO_1MHZ;
  adc_init(); lcd_init(); lcd_clear();

  // Başlangıç mesajı
  lcd_set_cursor(1,0);
  lcd_print("MORSE DECODER");
  __delay_cycles(1000000);
  lcd_clear();

  char morseBuf[8] = {0};
  unsigned int mi = 0;
  unsigned long dur = 0, sil = 0;
  int sig = 0;

  while(1){
    unsigned int v = adc_read();

    // Sinyal geldi mi?
    if(v > MORSE_THRESHOLD){
      if(!sig) dur = 0;
      sig = 1;
      dur += TICK_MS;
      sil = 0;
    } else {
      if(sig){
        // Darbe bitti; nokta mı çizgi mi?
        if(dur >= DASH_MS)       morseBuf[mi++] = '-';
        else if(dur >= DOT_MS)   morseBuf[mi++] = '.';
        // gürültü darbesi silinir
        morseBuf[mi] = '\0';
        dur = 0; sig = 0;
      }
      sil += TICK_MS;

      // Harf tamamlandı mı?
      if(mi>0 && sil > LETTER_PAUSE){
        // 1. satır: ham morse kodu
        lcd_clear();
        lcd_set_cursor(1,0);
        lcd_print(morseBuf);

        // 2. satır: çözülen karakter
        char decoded = morse_to_char(morseBuf);
        lcd_set_cursor(2,0);
        lcd_putc(decoded);

        // 2 s bekle, sonra hazır ol
        __delay_cycles(2000000);

        // Temizle, sıfırla
        lcd_clear();
        mi = 0;
        morseBuf[0] = '\0';
        sil = 0;
      }
    }
    __delay_cycles((unsigned long)TICK_MS * 1000);
  }
}
