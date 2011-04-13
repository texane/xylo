#include <stdio.h>
#include <math.h>

#if 0
static inline double compute_length
(double n, double v, double d, double f)
{
  /* n an integer (passed as double)
     v the speed of sound in air
     d the tube diameter
     f the frequency
     returns l the tube length
   */

  return ((n * v) / (2 * f)) - 0.8 * d;
}
#else
static inline double compute_length(double f)
{
  /* . v speed of sound in copper: 3700 meter per second
     . k the radius of gyration. for a pipe, it is given
     by: 1/2 * sqrt(inner_radius^2 + outter_radius^2);
     . 
   */

  const double v = 3700;
  const double k = sqrt(0.004 * 0.004 + 0.0045 * 0.0045) / 2.f;
/*   const double k = sqrt(0.008 * 0.008 + 0.007 * 0.007) / 2.f; */
  const double m[] = { 3.0112, 5, 7, 9, 11, 13, 15, 17 };
  const double mm = m[0] * m[0];
  return sqrt((M_PI * v * k * mm) / (8.f * f));
}
#endif

static inline double compute_freq
(double f0, unsigned int n)
{
  return f0 * pow(2.f, (double)n / 12.f);
}

static void compute_frequencies
(unsigned int scale, double* freqs)
{
  static const double scales[] =
  { 16.35, 32.70, 65.41, 130.81, 261.63, 523.25, 1046.50, 2093, 4186.01 };

  unsigned int i;
  for (i = 0; i < 12; ++i)
    freqs[i] = compute_freq(scales[scale], i);
}

static void compute_antinodes
(double l, double* a, double* b)
{
  *a = 0.224 * l;
  *b = 0.776 * l;
}

int main(int ac, char** av)
{
  /* freqs in hertz */
  double freqs[12];
  unsigned int notes[] = { 0, 2, 4, 5, 7, 9, 11 };
  unsigned int i;
  double nodes[2];

  compute_frequencies(8, freqs);

  for (i = 0; i < sizeof(notes) / sizeof(notes[0]); ++i)
  {
    const double l = compute_length
#if 0
    (1.0, 344.0, 0.008, freqs[notes[i]]);
#else
    (freqs[notes[i]]);
#endif

    compute_antinodes(l, &nodes[0], &nodes[1]);

    printf("%lf %lf %lf %lf\n", freqs[notes[i]], l, nodes[0], nodes[1]);
  }

  return 0;
}
