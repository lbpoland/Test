#include <terrain_map.h>
class region {
   mixed* terrains;
   string* features;
   int last_touched;
}
#define SAVE_DIR "/save/world_map/"
#define BOUNDARY TERRAIN_MAP_WORLD_BOUNDARY
#define REGION_SIZE TERRAIN_MAP_WORLD_REGION_SIZE
#define REGION_BOUNDARY TERRAIN_MAP_WORLD_REGION_BOUNDARY
#define OFFSET TERRAIN_MAP_WORLD_OFFSET
#define REGION_WIDTH TERRAIN_MAP_WORLD_REGION_WIDTH
void load_me();
private void generate_main_templates();
private void generate_blocking_templates();
private nosave mixed* _regions;
private nosave mixed* _templates;
private nosave mixed* _blocking_templates;
void create() {
   _regions = allocate(REGION_WIDTH, (: allocate(REGION_WIDTH) :));
   seteuid(getuid());
   generate_main_templates();
   generate_blocking_templates();
}
private void generate_main_templates() {
   int size;
   mixed* last;
   int x;
   int y;
   int u;
   int v;
   int e;
   int i;
   _templates = allocate(12);
   last = ({ ({ 1 }) });
   for (size = 0; size < sizeof(_templates); size++) {
      for (i = 0; i < sizeof(last); i++) {
         last[i] = ({ 0 }) + last[i] + ({ 0 });
      }
      _templates[size] = ({ allocate((size + 1) * 2 + 1) }) + last +
                         ({ allocate((size + 1) * 2 + 1) });
      x = 0;
      y = size + 1;
      u = 1;
      v = 2 * (size + 1) - 1;
      e = 0;
      while (x <= y) {
         _templates[size][size + 1 + x][size + 1 + y] = 1;
         _templates[size][size + 1 + x][size + 1 - y] = 1;
         _templates[size][size + 1 - x][size + 1 + y] = 1;
         _templates[size][size + 1 - x][size + 1 - y] = 1;
         _templates[size][size + 1 + y][size + 1 + x] = 1;
         _templates[size][size + 1 + y][size + 1 - x] = 1;
         _templates[size][size + 1 - y][size + 1 + x] = 1;
         _templates[size][size + 1 - y][size + 1 - x] = 1;
         if (size > 0) {
            _templates[size][size + 1 + x - 1][size + 1 + y] = 1;
            _templates[size][size + 1 + x - 1][size + 1 - y] = 1;
            _templates[size][size + 1 - x + 1][size + 1 + y] = 1;
            _templates[size][size + 1 - x + 1][size + 1 - y] = 1;
            _templates[size][size + 1 + y - 1][size + 1 + x] = 1;
            _templates[size][size + 1 + y - 1][size + 1 - x] = 1;
            _templates[size][size + 1 - y + 1][size + 1 + x] = 1;
            _templates[size][size + 1 - y + 1][size + 1 - x] = 1;
         }
         x++;
         e += u;
         u += 2;
         if (v < 2 * e) {
            y--;
            e -= v;
            v -= 2;
         }
         if (x > y) {
            break;
         }
      }
      last = copy(_templates[size]);
   }
}
mixed* generate_blocking(int x, int y, string* start,
                          string* straight, string* diagonal) {
   int i;
   int dx;
   int ex;
   int dy;
   int balance;
   int sx;
   int sy;
   int blocked;
   int blocked_straight;
   int blocked_diagonal;
   int first_block;
   first_block = -1;
   for (i = 0; i <= sizeof(start); i++) {
      sx = 0;
      sy = 0;
      ex = sizeof(start);
      dx = sizeof(start);
      dy = i;
      dy <<= 1;
      balance = dy - dx;
      dx <<= 1;
      blocked_straight = blocked_diagonal = blocked = 0;
      while (sx != ex) {
         if (blocked) {
            if (first_block == -1) {
               first_block = i;
            }
            start[sy] = start[sy][0..sx-1] + "*" + start[sy][sx+1..];
         } else {
            start[sy] = start[sy][0..sx-1] + " " + start[sy][sx+1..];
         }
         if (blocked_straight) {
            straight[sy] = straight[sy][0..sx-1] + "*" + straight[sy][sx+1..];
         } else {
            straight[sy] = straight[sy][0..sx-1] + " " + straight[sy][sx+1..];
         }
         if (blocked_diagonal) {
            diagonal[sy] = diagonal[sy][0..sx-1] + "*" + diagonal[sy][sx+1..];
         } else {
            diagonal[sy] = diagonal[sy][0..sx-1] + " " + diagonal[sy][sx+1..];
         }
         if (sx == x && sy == y) {
            blocked_diagonal = blocked_straight = blocked = 1;
            diagonal[sy] = diagonal[sy][0..sx-1] + "@" + diagonal[sy][sx+1..];
            start[sy] = start[sy][0..sx-1] + "@" + start[sy][sx+1..];
            straight[sy] = straight[sy][0..sx-1] + "@" + straight[sy][sx+1..];
         }
         if (sx == x && sy == y + 1) {
            blocked_straight = 1;
            straight[sy] = straight[sy][0..sx-1] + "|" + straight[sy][sx+1..];
         }
         if (sx == x + 1 && sy == y + 1) {
            blocked_diagonal = 1;
            diagonal[sy] = diagonal[sy][0..sx-1] + "\\" + diagonal[sy][sx+1..];
         }
         if (balance >= 0) {
            sy++;
            balance -= dx;
         }
         balance += dy;
         sx++;
      }
   }
   if (first_block >= (sizeof(start) / 2)) {
      for (i = sizeof(start); i >= 6; i--) {
         sx = 0;
         sy = 0;
         ex = sizeof(start);
         dx = sizeof(start);
         dy = i;
         dy <<= 1;
         balance = dy - dx;
         dx <<= 1;
         blocked = 0;
         while (sx != ex) {
            start[sy] = start[sy][0..sx-1] + " " + start[sy][sx+1..];
            if (sx == x && sy == y) {
               break;
            }
            if (balance >= 0) {
               sy++;
               balance -= dx;
            }
            balance += dy;
            sx++;
         }
      }
   }
   return ({ start, straight, diagonal });
}
private void generate_blocking_templates() {
   int x;
   int y;
   int size;
   mixed* basic;
   string* start;
   string line;
   basic = _templates[<1];
   size = sizeof(_templates);
   line = "";
   for (x = 0; x < size + 1; x++) {
      line += " ";
   }
   start = allocate(size + 1, line);
   _blocking_templates = allocate(size + 1, ({ }));
   for (x = 0; x < size + 1; x++) {
      _blocking_templates[x] = allocate(size + 1);
   }
   for (x = 0; x < size + 1; x++) {
      for (y = x; y < size + 1; y++) {
         if (basic[x + size][y + size] && (x != 0 || y != 0)) {
            _blocking_templates[x][y] = generate_blocking(y, x, copy(start), copy(start), copy(start));
         }
      }
   }
}
string *query_blocking_template(int x, int y, int type) {
   if (arrayp(_blocking_templates[x][y])) {
      return copy(_blocking_templates[x][y][type]);
   }
   return 0;
}
mixed* query_map_template(int size) {
   return copy(_templates[size - 1]);
}
void load_region(int x, int y) {
   class region region;
   string fname;
   if (_regions[x][y]) {
      _regions[x][y]->last_touched = time();
      return ;
   }
   fname = SAVE_DIR + "region_" + x + "_" + y;
   if (unguarded((: file_size($(fname)) :)) > 0) {
      region = unguarded( (: restore_variable(read_file($(fname), 1)) :));
   } else {
      region = new(class region,
                   terrains : allocate(REGION_SIZE, (: allocate(REGION_SIZE) :)),
                   features : ({ }));
   }
   _regions[x][y] = region;
   _regions[x][y]->last_touched = time();
}
void save_region(int x, int y) {
   string fname;
   class region region;
   if (_regions[x][y]) {
      region = _regions[x][y];
      fname = SAVE_DIR + "region_" + x + "_" + y;
      unguarded( (: write_file($(fname), save_variable($(region)), 1) :));
   }
}
int add_terrain(string path, int x1, int y1, int x2, int y2) {
   int tmp;
   int region_x;
   int region_y;
   if (x1 > x2) {
      tmp = x1;
      x1 = x2;
      x2 = tmp;
   }
   if (y1 > y2) {
      tmp = y1;
      y1 = y2;
      y2 = tmp;
   }
   if (x2 - x1 != BOUNDARY ||
       y2 - y1 != BOUNDARY) {
      debug_printf("Incorrect terrain size (%d x %d): %s\n",
                  x2 - x1, y2 - y1, path);
      return 0;
   }
   if (x1 % BOUNDARY ||
       y1 % BOUNDARY) {
      debug_printf("Incorrect boundary (%d - %d): %s\n",
                  x1 % BOUNDARY, y1 % BOUNDARY, path);
      return 0;
   }
   x1 = ((x1 + OFFSET) / BOUNDARY);
   y1 = ((y1 + OFFSET) / BOUNDARY);
   region_x = x1 / REGION_SIZE;
   region_y = y1 / REGION_SIZE;
   load_region(region_x, region_y);
   x2 = x1 % REGION_SIZE;
   y2 = y1 % REGION_SIZE;
   _regions[region_x][region_y]->terrains[x2][y2] = path;
   save_region(region_x, region_y);
   debug_printf("Added terrain (%d {%d}, %d {%d}) [%d,  %d]: %s\n",
                 x1, x2, y1, y2, region_x, region_y, path);
   return 1;
}
string find_terrain_at(int x, int y) {
   int region_x;
   int region_y;
   x = ((x + OFFSET) / BOUNDARY);
   y = ((y + OFFSET) / BOUNDARY);
   region_x = x / REGION_SIZE;
   region_y = y / REGION_SIZE;
   load_region(region_x, region_y);
   return _regions[region_x][region_y]->terrains[x % REGION_SIZE][y % REGION_SIZE];
}
string find_room_at(int x, int y) {
   string path;
   path = find_terrain_at(x, y);
   if (path) {
      return path->find_room_at_real_coord(x, y);
   }
   return 0;
}
void add_feature(string feature) {
   int x;
   int y;
   for (x = 0; x < REGION_WIDTH; x++) {
      for (y = 0; y < REGION_WIDTH; y++) {
         if (feature->is_inside_region(
                                (x * REGION_WIDTH) * BOUNDARY - OFFSET,
                                (y * REGION_WIDTH) * BOUNDARY - OFFSET,
                                ((x + 1) * REGION_WIDTH) * BOUNDARY - OFFSET,
                                ((y + 1) * REGION_WIDTH) * BOUNDARY - OFFSET)) {
            load_region(x, y);
            _regions[x][y]->features |= ({ feature });
            save_region(x, y);
            debug_printf("Added feature to region %d, %d\n", x, y);
         }
      }
   }
}
void remove_feature(string feature) {
   int x;
   int y;
   for (x = 0; x < REGION_WIDTH; x++) {
      for (y = 0; y < REGION_WIDTH; y++) {
         load_region(x, y);
         if (member_array(feature, _regions[x][y]->features) != -1) {
            _regions[x][y]->features -= ({ feature });
            save_region(x, y);
         }
      }
   }
}
string* query_features_at(int x, int y) {
   int region_x;
   int region_y;
   x = ((x + OFFSET) / BOUNDARY);
   y = ((y + OFFSET) / BOUNDARY);
   region_x = x / REGION_WIDTH;
   region_y = y / REGION_WIDTH;
   load_region(region_x, region_y);
   return _regions[region_x][region_y]->features;
}
string* query_features_in_region(int x1_orig, int y1_orig, int x2_orig, int y2_orig) {
   int region_x;
   int region_y;
   int x1;
   int y1;
   int x2;
   int y2;
   int tmp;
   string* features;
   string feat;
   x1 = ((x1_orig + OFFSET) / BOUNDARY) / REGION_WIDTH;
   y1 = ((y1_orig + OFFSET) / BOUNDARY) / REGION_WIDTH;
   x2 = ((x2_orig + OFFSET) / BOUNDARY) / REGION_WIDTH;
   y2 = ((y2_orig + OFFSET) / BOUNDARY) / REGION_WIDTH;
   if (x1 > x2) {
      tmp = x1;
      x1 = x2;
      x2 = tmp;
   }
   if (y1 > y2) {
      tmp = y1;
      y1 = y2;
      y2 = tmp;
   }
   features = ({ });
   if (x1 < 0) {
      x1 = 0;
   }
   if (y1 < 0) {
      y1 = 0;
   }
   if (x2 >= REGION_WIDTH) {
      x2 = REGION_WIDTH - 1;
   }
   if (y2 >= REGION_WIDTH) {
      y2 = REGION_WIDTH - 1;
   }
   for (region_x = x1; region_x <= x2; region_x++) {
      for (region_y = y1; region_y <= y2; region_y++) {
         load_region(region_x, region_y);
         foreach (feat in _regions[region_x][region_y]->features) {
            if (feat->is_inside_region(x1_orig, y1_orig, x2_orig, y2_orig)) {
               features |= ({ feat });
            }
         }
      }
   }
   return features;
}