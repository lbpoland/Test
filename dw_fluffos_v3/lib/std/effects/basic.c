#include "potion_attrs.h"
int x1, x2, y1, y2;
void set_boundaries(int *min, int *max)
{
   x1 = min[0];
   x2 = max[0];
   y1 = min[1];
   y2 = max[1];
}
int *query_coordinate()
{
   return ({ (x1 + x2) / 2, (y1 + y2) / 2 });
}
#pragma no_warnings
mixed *query_attrs(int *coord)
{
   return ({ 0, 100, ({ }), ({ }), ({ }), ({ }) });
}
int query_pass_through(int *coord)
{
   return 100;
}
void install_effect()
{
   (void)POTION_SPACE_HANDLER->remove_effect(file_name(this_object()));
   (void)POTION_SPACE_HANDLER->add_effect(file_name(this_object()), x1, x2, y1, y2);
}
int sqrt(int p)
{
   int i;
   for (i = 1; i < 500; i++) if (i * i > p) return i-1;
}
int distance_within_region(int *coord)
{
   int dx, dy;
   if (x1 < 0) {
      if (x2 > 0)
         dx = (coord[0] < 0) ? -coord[0] : coord[0];
      else
         dx = (x2 - coord[0]);
   } else
      dx = coord[0] - x1;
   if (y1 < 0) {
      if (y2 > 0)
         dy = (coord[1] < 0) ? -coord[1] : coord[1];
      else
         dy = (y2 - coord[1]);
   } else
      dy = coord[1] - y1;
   return sqrt(dx * dx + dy * dy);
}
int distance_from_origin(int *coord)
{
   return sqrt(coord[0] * coord[0] + coord[1] * coord[1]);
}