#include <avr/io.h>
#include <util/delay.h>


/* 8 io pins used (not contiguous since leds on d<0:1>):
   portb<0:1>
   portd<2:7>
 */


static void wait_for_long(void)
{
  unsigned char counter;
  for (counter = 0; counter != 2; ++counter) _delay_loop_2(30000);
}


static void set_pins(unsigned char pins)
{
  PORTB = (PORTB & ~0x3) | (pins & 0x3);
  PORTD = (PORTD & 0x3) | (pins & ~0x3);
}


static const unsigned char doremi_map[] =
{ 1, 0, 7, 6, 5, 4, 3, 2 };


enum doremi_key
{
  DO = 0,
  RE,
  MI,
  FA,
  SOL,
  LA,
  SI,
  DO_DIESE
};
 

#if 0 /* simple main */
 
int main (void)
{
  /* digital output mode */
  DDRB = 0xff;
  DDRD = 0xff;

  PORTB = 0x00;
  PORTD = 0x00;

  while (1)
  {
    set_pins(0xff);
    wait_for_long();
    set_pins(0x00);
    wait_for_long();
  }
 
  return 0;
}

#elif 1

int main (void)
{
  unsigned char note = 0;

  /* digital output mode */
  DDRB = 0xff;
  DDRD = 0xff;

  PORTB = 0x00;
  PORTD = 0x00;

  while (1)
  {
    set_pins(1 << doremi_map[(note++) & (0x8 - 1)]);
    wait_for_long();
    set_pins(0x00);
    wait_for_long();
  }
 
  return 0;
}

#endif
