#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <SFML/Graphics.h>
#include <SFML/Window.h>

#include "utils.h"
#include "stdbool.h"

//
//      SHAPE
//

#define TYPE_NAN  0
#define TYPE_RECT 1

#define using(X, CODE) { typeof(&(X)) _ = &(X); CODE }
#define usingBy(X, Y, CODE) { typeof(&(X)) Y = &(X); CODE }
#define usingBy2(X, Y, A, B, CODE) { typeof(&(X)) Y = &(X); typeof(&(A)) B = &(A); CODE }

typedef struct  s_shape_AABB
{
  vec2d         pos;
  vec2d         half_s;
} t_shape_AABB;

typedef struct  s_shape_rect
{
  vec2d         size;
} t_shape_rect;

typedef struct  s_shape
{
  uchar         type;
  union
  {
    t_shape_rect rect;
  };
} t_shape;

//END

typedef struct  s_body
{
  vec2d         pos;
  vec2d         v;
  double        mass;
  t_shape       shape;
  double        restitution;
  bool          fix;
  char          *name;
} t_body;

typedef struct  s_body_list
{
  t_body        *bodys;
  bool          *use;
  int           max;
  int           min;
  int           nb;
} t_body_list;

typedef struct  s_contact
{
  t_body        *A;
  t_body        *B;
  double        penetration;
  vec2d         normal;
} t_contact;

typedef struct  s_contact_list
{
  t_contact     *contacts;
  int           max;
  int           nb;
} t_contact_list;

typedef struct s_world
{
  t_body_list body_list;
  t_contact_list  contact_list;
} t_world;

int   my_box(int fd);
void  update_world(t_world *w);
int   my_update(t_world *world, sfRenderWindow  *window);

bool world_detector(t_world *, t_body *);
t_world  *world_from_test();
t_body_list *world_get_bodys(t_world *world);
t_body      *new_body(t_world *w);
t_shape *fix_rect(t_body *body, vec2d size);
