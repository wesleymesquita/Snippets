#include<stdio.h>

int
main ()
{

  int k, m, n, x, y;

  for (;;)
    {
      scanf ("%d", &k);
      if (k == 0)
	break;
      scanf ("%d %d", &n, &m);
      for (; k-- > 0;)
	{
	  scanf ("%d %d", &x, &y);
	  if (x == n || y == m)
	    printf ("divisa\n");
	  else if (x > n && y > m)
	    printf ("NE\n");
	  else if (x > n && y < m)
	    printf ("SE\n");
	  else if (x < n && y < m)
	    printf ("SO\n");
	  else if (x < n && y > m)
	    printf ("NO\n");
	}
    }
  return 0;
}
