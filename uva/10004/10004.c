#include <stdio.h>

struct node
{
  int color;
  int visited;
};


int
visit (int n, int prev_color, int nnodes, int g[][200],
       struct node nodes[][200])
{
  int i;
  if (!(*nodes)[n].visited)
    {
      (*nodes)[n].visited = 1;
      (*nodes)[n].color = !prev_color;
      for (i = 0; i < nnodes; i++)
	{
	  if (g[n][i] == 1 && (*nodes)[i].visited
	      && (*nodes)[i].color == !prev_color)
	    {
	      return 0;
	    }
	}
      for (i = 0; i < nnodes; i++)
	{

	  if (g[n][i] == 1 && !(*nodes)[i].visited)
	    {
	      if (visit (i, !prev_color, nnodes, g, nodes) == 0)
		{
		  return 0;
		}
	    }
	}
    }

  return 1;
}


int
main ()
{
  int n, i, j, e, v, w;
  int g[200][200];
  struct node nodes[200];

  for (;;)
    {
      scanf ("%d", &n);
      if (n == 0)
	break;
      for (i = 0; i < n; i++)
	{
	  nodes[i].color = 0;
	  nodes[i].visited = 0;
	  for (j = 0; j < n; j++)
	    {
	      g[i][j] = 0;
	    }
	}
      scanf ("%d", &e);
      for (i = 0; i < e; i++)
	{
	  scanf ("%d %d", &v, &w);
	  g[v][w] = 1;
	  g[w][v] = 1;
	}

      v = 0;
      v = visit (0, nodes[0].color, n, g, &nodes);
      v ? printf ("BICOLORABLE.\n") : printf ("NOT BICOLORABLE.\n");

    }

  return 0;
}
