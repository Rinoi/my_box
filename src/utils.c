#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "utils.h"

int   usage(char *path)
{
  printf("%s : Usage\n", path);
  return (1);
}

int   my_open(char *name)
{
  int fd = open(name, O_RDONLY);
  if (fd < 0)
    dprintf(2, "Can't open filename : %s\n", name);
  return (fd);
}

double dot_product(vec2d *v1, vec2d *v2)
{
  return ((v1->x * v2->x) + (v1->y * v2->y));
}

double min_d(double a, double b)
{
  return (a < b ? a : b);
}

float rnd()
{
  float i = random() % 10000;

  i /= 10000;
  return (i);
}
