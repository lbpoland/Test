inherit "/std/room/inherit/terrain_map/distance_str";
private int _max_range;
private int _max_day_range;
private int _max_night_range;
private int _min_range = -1;
private int _range_offset;
private int _blocking;
private object _region;
class feature_pos {
   int xstart;
   int ystart;
   int width;
   int height;
}
void set_region(mixed region) {
   if (_region) {
      _region->dest_me();
   }
   if (stringp(region)) {
      _region = clone_object(region);
   } else if (objectp(region)) {
      _region = region;
   }
}
object query_region_ob() {
   return _region;
}
void set_range_offset(int offset) {
   _range_offset = offset;
}
int query_range_offset() {
   return _range_offset;
}
void set_max_day_range(int range) {
  _max_day_range = range;
   if (_max_day_range > _max_range) {
      _max_range = _max_day_range;
   }
}
int query_max_day_range() {
   return _max_day_range;
}
void set_max_night_range(int range) {
   _max_night_range = range;
   if (_max_night_range > _max_range) {
      _max_range = _max_night_range;
   }
}
int query_max_night_range() {
   return _max_night_range;
}
void set_min_range(int range) {
  _min_range = range;
}
int query_min_range() {
   return _min_range;
}
int query_max_range() {
   return _max_range;
}
int set_blocking(int blocking) {
   _blocking = blocking;
}
int query_blocking() {
   return _blocking;
}
string calc_feature_desc(mapping direc, int night, int visibility) {
   return "This needs to be set.";
}
mapping filter_distances(mapping direcs) {
   return filter(direcs, (: $2 <= _max_range :));
}
mapping query_feature_desc_from(int x, int y, int z, int no_filter) {
   mapping bits;
   if (_region) {
      bits = _region->query_feature_desc_from(x, y, z);
      if (bits) {
        if(no_filter)
          return bits;
        else
          return filter_distances(bits);
      }
   }
   return ([ ]);
}
int is_inside_region(int x1, int y1, int x2, int y2) {
   return _region->is_inside_region(x1, y1, x2, y2, query_max_range());
}
void dest_me() {
   if (_region) {
      _region->dest_me();
   }
   destruct(this_object());
}