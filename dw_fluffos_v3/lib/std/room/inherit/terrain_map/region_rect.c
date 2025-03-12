inherit "/std/room/inherit/terrain_map/geometry";
class feature_pos {
   int xstart;
   int ystart;
   int width;
   int height;
}
private mixed    *_feature_direcs = ({ ({ "southwest", "south", "southeast" }),
                               ({ "west", "Oops", "east" }),
                               ({ "northwest", "north", "northeast" }) });
private class feature_pos* _positions = ({ });
void add_feature_position(int x, int y, int width, int height) {
   class feature_pos pos;
   pos = new(class feature_pos, xstart : x, ystart : y,
                                width : width, height : height);
   _positions += ({ pos });
}
mapping query_feature_desc_from(int x, int y, int z) {
   int h;
   int v;
   int width;
   int height;
   float distance;
   float min_distance;
   string direc;
   class feature_pos pos;
   float xmod;
   float ymod;
   int xd;
   int yd;
   foreach (pos in _positions) {
      h = pos->xstart;
      v = pos->ystart;
      width = pos->width;
      height = pos->height;
      if (x >= (h + width)) {
         h = h + width - 1;
      } else if (x >= h) {
         h = x;
      }
      if (y >= (v + height)) {
         v = v + height - 1;
      } else if (y >= v) {
         v = y;
      }
      distance = sqrt(pow(x - h, 2) + pow(y - v, 2));
      if (distance > 0.0000001 && (distance < min_distance || !min_distance)) {
         xmod = ((h - x) < 0) ? -0.5 : 0.5;
         ymod = ((v - y) < 0) ? -0.5 : 0.5;
         xd = to_int(xmod + to_float(h - x) / distance) + 1;
         yd = to_int(ymod + to_float(v - y) / distance) + 1;
         direc = _feature_direcs[yd][xd];
         min_distance = distance;
      }
   }
   if (!direc) {
      return ([ ]);
   }
   return ([ direc : to_int(min_distance) ]);
}
void dest_me() {
   destruct(this_object());
}
int is_inside_region(int x1, int y1, int x2, int y2, int range) {
   class feature_pos position;
   int height;
   int width;
   foreach (position in _positions) {
      height = position->height;
      width = position->width;
      if (position->xstart >= x1 && position->xstart <= x2 &&
          position->ystart >= y1 && position->ystart <= y2) {
         return 1;
      }
      if (position->xstart >= x1 && position->xstart <= x2 &&
          position->ystart + height >= y1 && position->ystart + height <= y2) {
         return 1;
      }
      if (position->xstart +width >= x1 && position->xstart +width <= x2 &&
          position->ystart + height >= y1 && position->ystart + height <= y2) {
         return 1;
      }
      if (position->xstart +width >= x1 && position->xstart +width <= x2 &&
          position->ystart >= y1 && position->ystart <= y2) {
         return 1;
      }
   }
   return 0;
}