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
{ 1, 0, 7, 6, 5, 4, 3, 2, 8 };


enum doremi_key
{
  DO = 0,
  RE,
  MI,
  FA,
  SOL,
  LA,
  SI,
  DO2,
  SILENCE,

  /* missing notes */
  LA_DIESE = LA,
  FA_DIESE = FA,
  SOL_DIESE = SOL,
  RE_DIESE = RE,
  MIB = MI,
  SIB = SI,
  DO_MINOR = DO,
  FA_MINOR = FA,
  LA_MINOR = LA,
  SOL_MINOR = SOL,
  RE_MINOR = RE
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

#if 1
#include "part_elise.h"
#elif 0
#include "part_bach2.h"
#elif 0
#include "part_tetris.h"
#elif 0
#include "part_auclairdelalune.h"
#elif 0
#include "part_leconpiano.h"
#elif 0
#include "part_couleurcafe.h"
#elif 0
#include "part_odejoie.h"
#elif 0
#include "part_foretlointaine.h"
#elif 0
#include "part_terriblejungle.h"
#elif 0
#include "part_marseillaise.h"
#elif 0
#include "part_bach.h"
#elif 0
#include "part_papanoel.h"
#elif 0
#include "part_frerejacques.h"
#elif 0
#include "part_zelda.h"
#elif 0
#include "part_berceusezelda.h"
#elif 0
#include "part_monbeausapin.h"
#elif 0
#include "part_choux.h"
#elif 0
#include "part_jinglebells.h"
#elif 0
#include "part_mario.h"
#elif 0
#include "part_cowboys.h"
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
