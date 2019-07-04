#pragma once

typedef unsigned char uchar;

typedef struct s_vec2d
{
  double x;
  double y;
} vec2d;

int   usage(char *path);
int   my_open(char *name);

double dot_product(vec2d *v1, vec2d *v2);
double min_d(double a, double b);

float rnd();
