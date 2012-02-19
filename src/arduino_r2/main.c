#include <avr/io.h>
#include <util/delay.h>


/* 8 io pins used (not contiguous since leds on d<0:1>):
   portb<0:1>
   portd<2:7>
 */


static void wait_for_long(void)
{
  unsigned char counter;
  for (counter = 0; counter != 15; ++counter) _delay_loop_2(30000);
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
  DO2
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

#elif 0 /* doremi */

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

#elif 1 /* partitions */

#if 0 /* au clair de la lune */
static const enum doremi_key part[] =
{
  DO, DO, DO, RE, MI, RE, DO, MI, RE, RE, DO,
  DO, DO, DO, RE, MI, RE, DO, MI, RE, RE, DO,
  RE, RE, RE, RE, LA, LA, RE, DO, SI, LA, SOL,
  DO, DO, DO, RE, MI, RE, DO, MI, RE, RE, DO
};
#elif 1 /* les cowboys fringants */
static const enum doremi_key part[] =
{
  SI, DO, SI, DO, SI, DO, SI,
  SI, DO, SI, DO, SI, DO, LA,
  /* refrain */
  FA, FA, FA, FA, MI, FA, MI, RE, DO, SI, SOL, SOL, SI, FA,
  MI, MI, MI, MI, RE, MI, RE, DO, SI, LA, FA, FA, LA, MI, RE,
  RE, DO, 
  SI, DO, SI, DO, LA,
  /* couplet */
  FA, FA, FA, FA, MI, FA, MI, RE, DO, SI, 
  RE, RE, RE, RE, DO, RE, MI, RE, MI, RE, DO, SI, LA, 
  DO, DO, DO, DO, SI, DO, RE, DO, 
  SI, DO, SI, DO, LA,
  SI, DO, SI, DO, LA,
  /* refrain */
  FA, FA, FA, FA, MI, FA, MI, RE, DO, SI, SOL, SOL, SI, FA,
  MI, MI, MI, MI, RE, MI, RE, DO, SI, LA, FA, FA, LA, MI, RE,
  RE, DO,
  SI, DO, SI, DO, LA,
  /* couplet */
  FA, FA, FA, FA, MI, FA, MI, RE, DO, SI,
  RE, RE, RE, RE, DO, RE, MI, RE, MI, RE, DO, SI, LA,
  DO, DO, DO, DO, SI, DO, RE, DO,
  SI, DO, SI, DO, LA,
  SI, DO, SI, DO, LA,
  /* refrain */
  FA, FA, FA, FA, MI, FA, MI, RE, DO, SI, SOL, SOL, SI, FA,
  MI, MI, MI, MI, RE, MI, RE, DO, SI, LA, FA, FA, LA, MI, RE,
  RE, DO, 
  SI, DO, SI, DO, LA,
  /* solo */
  MI, MI, MI, MI, RE, MI, FA, MI, FA, MI, RE, DO, SI, 
  RE, RE, RE, RE, DO, RE, MI, RE, MI, RE, DO, SI, LA, 
  DO, DO, DO, DO, SI, DO, 
  RE, DO,
  SI, DO, SI, DO, LA,
  /* couplet */
  FA, FA, FA, FA, MI, FA, MI, RE, DO, SI,
  RE, RE, RE, RE, DO, RE, MI, RE, MI, RE, DO, SI, LA,
  DO, DO, DO, DO, SI, DO, RE, DO,
  SI, DO, SI, DO, LA,
  SI, DO, SI, DO, LA,
  /* refrain */
  FA, FA, FA, FA, MI, FA, MI, RE, DO, SI, SOL, SOL, SI, FA,
  MI, MI, MI, MI, RE, MI, RE, DO, SI, LA, FA, FA, LA, MI, RE,
  RE, DO, 
  SI, DO, SI, DO, LA,

  FA, FA, FA, FA, MI, FA, MI, RE, DO, SI, SOL, SOL, SI, FA,
  MI, MI, MI, MI, RE, MI, RE, DO, SI, LA, FA, FA, LA, MI, RE,
  RE, DO,
  SI, DO, SI, DO, SI, DO, SI,
  SI, DO, SI, DO, SI, DO, LA
};
#elif 0
static const enum doremi_key part[] =
{
  DO, DO, RE, MI, DO, SOL, SOL, SOL, RE, SOL,
  SOL, FA, MI, FA, SOL,
  SOL, RE, MI, FA, FA,
  SOL, FA, MI, RE, DO,
  DO, RE, MI, FA, SOL, MI, FA, SOL, MI, RE, DO 
};
#endif

int main(void)
{
  const unsigned int count = sizeof(part) / sizeof(part[0]);
  unsigned int note = 0;

  /* digital output mode */
  DDRB = 0xff;
  DDRD = 0xff;

  PORTB = 0x00;
  PORTD = 0x00;

 redo_part:
  for (note = 0; note < count; ++note)
  {
    set_pins(1 << doremi_map[part[note]]);
    wait_for_long();
    set_pins(0x00);
    wait_for_long();
  }
  goto redo_part;

  return 0;
}

#endif
