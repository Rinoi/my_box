#include "my_box.h"

int               my_box(int fd)
{
  t_world         *world;
  sfRenderWindow  *window;

  (void)(fd);
  window = sfRenderWindow_create((sfVideoMode){1200, 900, 32},
                                       "My Box", sfResize | sfClose, NULL);
  sfRenderWindow_setFramerateLimit(window, 60);
  //world = world_from_file(fd);
  world = world_from_test();
  while (sfRenderWindow_isOpen(window))
    if (my_update(world, window) != 0)
      return (0);
  return (1);
}

void               my_draw(t_world *world, sfRenderWindow  *window)
{
  t_body_list *list = world_get_bodys(world);
  sfRectangleShape *rect = sfRectangleShape_create();

  vec2d size;

  sfRectangleShape_setOutlineThickness(rect, 1);
  sfRectangleShape_setFillColor(rect, (sfColor){0, 0, 0, 0});
  for (int i = list->min; i < list->max; i += 1)
  {
    if (list->use[i] == true)
      {
        switch (list->bodys[i].shape.type)
        {
          case TYPE_RECT:

            size = list->bodys[i].shape.rect.size;
            sfRectangleShape_setPosition(rect, (sfVector2f){list->bodys[i].pos.x - size.x/2, list->bodys[i].pos.y - size.y/2});
            sfRectangleShape_setSize(rect, (sfVector2f){size.x,
                                                        size.y});
            sfRenderWindow_drawRectangleShape(window, rect, NULL);
            break;
          default:
            break;
        }
    }
  }
  sfRectangleShape_destroy(rect);
}

int               my_update(t_world *world, sfRenderWindow  *window)
{
  static bool OK = true;
  sfEvent         event;

  if (OK == true)
  {
    update_world(world);
    OK = false;

    t_body *body = new_body(world);
    if (body != NULL)
    {
      body->pos.x = rnd() * 800.;
      body->pos.y = rnd() * 50;
      body->fix = false;
      body->v.y = 0;
      //body->v.x = 0;
      body->v.x = (rnd() - 0.5) * 10;
      body->restitution = 0.10;
      body->mass = 1;
      fix_rect(body, (vec2d){10 + rnd() * 20., 10 + rnd() * 20.});
    }

  }
  for (int i = world->body_list.min; i < world->body_list.max; i += 1)
    if (world->body_list.use[i] == true && world->body_list.bodys[i].fix == false)
      if (world->body_list.bodys[i].pos.y > 800)
      {
        world->body_list.use[i] = false;
      }
  while (sfRenderWindow_pollEvent(window, &event))
    {
      if (event.type == sfEvtClosed)
        {
          sfRenderWindow_close(window);
          return (1);
        }
      if (event.key.code == sfKeyA)
        OK = true;
    }
  sfRenderWindow_clear(window, sfBlack);
  my_draw(world, window);
  sfRenderWindow_display(window);
  return (0);
}
