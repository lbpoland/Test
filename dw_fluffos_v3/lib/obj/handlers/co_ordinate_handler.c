#include <dirs.h>
class room_data {
   string other;
   string direction;
   int* coords;
   int last_update;
}
private mapping _rooms = ([ ]);
private nosave mapping _dirs;
int setup_room(string path);
void create() {
   mixed* bits;
   int i;
   bits = STD_ORDERS;
   _dirs = ([ ]);
   for (i = 0; i < sizeof(bits); i += 2) {
      _dirs[bits[i]] = bits[i + 1];
   }
}
private void setup_specific_room(string path, string new_path, string dir) {
   int* delta;
   int* co_ord;
   int k;
   class room_data data;
   delta = new_path->query_room_size_array() + path->query_room_size_array();
   co_ord = copy( _rooms[new_path]->coords);
   for ( k = 0; k < 3; k++ ) {
     co_ord[ k ] += _dirs[dir][ k ] *
                    ( delta[ k ] + delta[ k + 3 ] );
   }
   data = new(class room_data);
   data->other = new_path;
   data->coords = co_ord;
   data->direction = dir;
   data->last_update = _rooms[new_path]->last_update;
   _rooms[path] = data;
}
int* query_room_co_ords(string path) {
   class room_data data;
   data = _rooms[path];
   if (data) {
      if (!_rooms[data->other]) {
         map_delete(_rooms, path);
      } else {
         if (data->last_update != _rooms[data->other]->last_update) {
            setup_specific_room(path, data->other, data->direction);
         }
         return data->coords;
      }
   }
   if (setup_room(path)) {
      data = _rooms[path];
      return data->coords;
   }
   return 0;
}
int setup_room(string path) {
   string* bits;
   int i;
   string new_path;
   if (path->query_property("location") != "outside" ||
       !path->query_terrain_handler()) {
      return 0;
   }
   bits = path->query_dest_dir();
   for (i = 0; i < sizeof(bits); i += 2) {
      if (find_object(bits[i+1])) {
         new_path = file_name(find_object(bits[i+1]));
      } else {
         new_path = bits[i+1];
      }
      if (_rooms[new_path]) {
         setup_specific_room(path, new_path, bits[i]);
         return 1;
      }
   }
   return 0;
}
void setup_fixed_room(string path, int* coords) {
   class room_data data;
tell_creator("pinkfish", "%O %O %O\n", path, path->query_property("location"),
               path->query_terrain_handler());
   if (path->query_property("location") != "outside" ||
       !path->query_terrain_handler()) {
      return 0;
   }
   if (_rooms[path]) {
      data = _rooms[path];
      if (data->coords[0] == coords[0] &&
          data->coords[1] == coords[1] &&
          data->coords[2] == coords[2]) {
         return ;
      }
   } else {
      data = new(class room_data);
   }
   data->coords = coords;
   data->last_update = time();
   _rooms[path] = data;
}
mapping query_rooms() {
   return _rooms;
}