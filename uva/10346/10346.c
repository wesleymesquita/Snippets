#include <stdio.h>

int
main ()
{

  int n, k, s, b;

  for (; scanf ("%d %d", &n, &k) > 0;)
    {
      s = n;
      b = n;
      for (; n > 0;)
	{
	  n = (int) b / k;
	  b = b % k;
	  b += n;
	  s += n;
	}
      printf ("%d\n", s);

    }

  return 0;
}
