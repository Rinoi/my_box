#include "my_box.h"

t_world *world_from_test()
{
  t_world *world = malloc(sizeof(t_world));

  if (world == NULL)
    return (NULL);

  const int NB = 300;

  world->body_list.bodys = malloc(sizeof(t_body) * (NB + 1));
  world->body_list.use = malloc(sizeof(bool) * (NB + 1));
  world->body_list.nb = NB + 1;
  world->body_list.max = 0;
  world->body_list.min = 0;

  world->contact_list.contacts = malloc(sizeof(t_contact) * (NB));
  world->contact_list.max = 0;
  world->contact_list.nb = NB;


  t_body *body;

  // for (int i = 0; i < 10; i += 1)
  // {
  //   body = new_body(world);
  //   body->pos.x = rnd() * 800.;
  //   body->pos.y = rnd() * 50;
  //   body->fix = false;
  //   body->v.y = 1 + rnd() * 10;
  //   body->v.x = 1;
  //   body->restitution = 0.90;
  //   body->mass = 1;
  //   fix_rect(body, (vec2d){20, 20});
  // }
  //

  //TEST X Y
  // {
    // for (int i = 0; i < 2; i += 1)
    // {
    //   body = new_body(world);
    //   body->pos.x = 100 + rnd() * 200.;
    //   body->pos.y = 450;
    //   body->fix = false;
    //   body->v.y = 0;
    //   body->v.x = 5;
    //   body->restitution = 0.90;
    //   body->mass = 1;
    //   fix_rect(body, (vec2d){20, 20});
    // }
    // body = new_body(world);
    // body->pos.x = 200;
    // body->pos.y = 450;
    // body->fix = false;
    // body->v.y = 0;
    // body->v.x = 5;
    // body->restitution = 0.20;
    // body->mass = 1;
    // body->name = "CUBE A";
    // fix_rect(body, (vec2d){20, 20});

    // body = new_body(world);
    // body->pos.x = 300;
    // body->pos.y = 450;
    // body->fix = false;
    // body->v.y = 0;
    // body->v.x = 5;
    // body->restitution = 0.20;
    // body->mass = 1;
    // body->name = "CUBE B";
    // fix_rect(body, (vec2d){20, 20});
    // for (int i = 0; i < 10; i += 1)
    // {
    //   body = new_body(world);
    //   body->pos.x = 700 - rnd() * 200.;
    //   body->pos.y = 500;
    //   body->fix = false;
    //   body->v.y = 0;
    //   body->v.x = -1;
    //   body->restitution = 0.90;
    //   body->mass = 1;
    //   fix_rect(body, (vec2d){20, 20});
    // }
    //
    // body = new_body(world);
    // body->pos.x = 700 + 10;
    // body->pos.y = 500 - 10;
    // body->fix = true;
    // body->v.y = 0;
    // body->v.x = -1;
    // body->restitution = 0.90;
    // body->mass = 1;
    // body->name = "BLOCK";
    // fix_rect(body, (vec2d){10, 60});

  //}


  body = new_body(world);
  body->pos.x = 600;
  body->pos.y = 800;
  body->fix = true;
  body->restitution = 0.50;
  body->mass = 10000;
  fix_rect(body, (vec2d){600, 100});

  return (world);
}

t_shape *fix_rect(t_body *body, vec2d size)
{
  body->shape.type = TYPE_RECT;
  body->shape.rect.size = size;
  return (&body->shape);
}

t_body      *new_body(t_world *w) usingBy(w->body_list, list,
{
  //NO BODY IN LIST
  if (list->max == 0)
  {
    list->max = 1;
    list->use[0] = true;
    printf("body CREATE\n");
    return (&list->bodys[0]);
  }

  //SEARCH BETWEEN MIN AND MAX
  int i;

  for (i = list->min; i < list->max; i += 1)
    if (list->use[i] == false)
    {
      list->use[i] = true;
      return (&list->bodys[i]);
    }

  //NEW IF YOU CAN
  if (i < list->nb)
    {
      list->max = i + 1;
      list->use[i] = true;
      return (&list->bodys[i]);
    }
  //LIST FULL
  return (NULL);
});

static int getMinInTab(double *tab)
{
  double min = tab[0];
  int idx = 0;

  for (int i = 1; i < 4; i += 1)
    if (tab[i] < min)
     {
         idx = i;
         min = tab[i];
     }
  return (idx);
}

bool rect_rect(t_body *A, t_body *B, t_contact *c)
{
  t_shape_rect *a = &A->shape.rect;
  t_shape_rect *b = &B->shape.rect;

  vec2d pA = {A->pos.x - a->size.x/2, A->pos.y - a->size.y/2};
  vec2d pB = {B->pos.x - b->size.x/2, B->pos.y - b->size.y/2};
  double tab[4] = {(pB.x + b->size.x) - pA.x,
                  (pA.x + a->size.x) - pB.x,
                  (pB.y + b->size.y) - pA.y,
                  (pA.y + a->size.y) - pB.y};

  if (tab[0] > 0 && tab[1] > 0 && tab[2] > 0 && tab[3] > 0)
     {
       int min = getMinInTab(tab);
       c->penetration = tab[min];
       switch (min)
       {
         case 0: //gauche
          c->normal = (vec2d){1, 0};
          break;
         case 1: //droite
          c->normal = (vec2d){-1, 0};
          //printf("IMPOSIBLE DROITE\n");
          break;
         case 2: //bas
          c->normal = (vec2d){0, 1};
          printf("IMPOSIBLE BAS\n");
          break;
         case 3: //haut
          c->normal = (vec2d){0, -1};
          break;
         default:
          break;
       }
       return (true);
     }

  return (false);
}

bool world_detector(t_world *w, t_body *A)
{
  for (int i = w->body_list.min; i < w->body_list.max; i += 1)
  {
    if (w->body_list.use[i] == true) usingBy (w->body_list.bodys[i], B,
      {
        if (B == A)
          continue;
        if (A->shape.type == TYPE_RECT && B->shape.type == TYPE_RECT && w->contact_list.max < w->contact_list.nb)
          if (rect_rect(A, B, &w->contact_list.contacts[w->contact_list.max]) == true)
          {
            w->contact_list.contacts[w->contact_list.max].A = A;
            w->contact_list.contacts[w->contact_list.max].B = B;
            w->contact_list.max += 1;
          }
      });
  }
  return (w->contact_list.max > 0);
}

void  update_body(t_body *body)
{
  if (body->fix == true)
    return;

  // printf("%s %f %f %f %f\n", body->name, body->v.x, body->v.y, body->pos.x, body->pos.y);
  body->v.x += 0;
  body->v.y += 0.3;
  body->pos.y += body->v.y;
  body->pos.x += body->v.x;
}

void  resolve(t_contact *c)
{
  vec2d rv = {c->B->v.x - c->A->v.x, c->B->v.y - c->A->v.y};

  c->A->pos.x += c->normal.x * c->penetration;
  c->A->pos.y += c->normal.y * c->penetration;

  double velA = dot_product(&rv, &c->normal);
  if (velA < 0)
  {
    // printf("NO! %p\n", c->A);
    // printf("penetration %f\n", c->penetration);
    //return;
  }

  //printf("VEL A = %f\n", velA);

  double e = min_d( c->A->restitution, c->B->restitution);
  // Calculate impulse scalar
  float j = -(1 + e) * velA;
  j /= 1 / c->A->mass + 1 / c->B->mass;
  // Apply impulse
  vec2d impulse = {c->normal.x * j, c->normal.y * j};
  c->A->v.x -= 1 / c->A->mass * impulse.x;
  c->A->v.y -= 1 / c->A->mass * impulse.y;

  c->B->v.x += 1 / c->B->mass * impulse.x;
  c->B->v.y += 1 / c->B->mass * impulse.y;
  //printf("pen %f\n", c->penetration);
}

void  update_world(t_world *w)
{
  for (int ii = 0; ii < 6; ii += 1)
    for (int i = w->body_list.min; i < w->body_list.max; i += 1)
    {
      if (w->body_list.use[i] == true && w->body_list.bodys[i].fix == false)
      {
        if (ii == 0)
          update_body(&w->body_list.bodys[i]);
        w->contact_list.max = 0;
        if (world_detector(w, &w->body_list.bodys[i]) == true)
          for (int i = 0; i < w->contact_list.max; i += 1)
          {
            resolve(&w->contact_list.contacts[i]);
            w->contact_list.contacts[i].A->v.x *= 0.90;
          }
      }
    }
}

t_body_list *world_get_bodys(t_world *world)
{
  return (&world->body_list);
}
