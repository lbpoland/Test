#include <terrain_map.h>
inherit TERRAIN_MAP_FEATURE_BASE;
private string _base_desc;
private int _very_close_distance;
private int _distance_multiplier = 1;
void set_very_close_distance(int close) {
   _very_close_distance = close;
}
string query_base_description() {
   return _base_desc;
}
void set_base_description(string desc) {
   _base_desc = desc;
}
void set_distance_multiplier(int mult) {
   _distance_multiplier = mult;
}
string calc_feature_desc(mapping direcs, int night, int visibility) {
   string direc;
   int dist;
   int new_dist;
   string* bits;
   bits = ({ });
   if(visibility < 1 && visibility != -1)
     visibility = 1;
   foreach (direc, dist in direcs) {
      dist += query_range_offset() ;
      new_dist = dist * 100 / visibility;
      if (visibility == -1 ||
          (new_dist < query_max_range() && dist > query_min_range())) {
         if (dist < _very_close_distance) {
            bits += ({ "very close to the " + direc });
         } else {
            bits += ({ query_distance_str(dist * _distance_multiplier) + " to the " + direc });
         }
      }
   }
   if (sizeof(bits) > 1) {
      return implode(bits[0..<2], ", ") + " and " + bits[<1] + " " +_base_desc;
   }
   if (sizeof(bits)) {
      return bits[0] + " " + _base_desc;
   }
   return 0;
}
string calc_map_feature_desc(mapping direcs, int fudge) {
   string direc;
   int dist;
   string* bits;
   bits = ({ });
   foreach (direc, dist in direcs) {
      dist += query_range_offset();
      if (dist < _very_close_distance * 5) {
        bits += ({ "very close to the " + direc });
      } else {
        bits += ({ ({"approximately ", "about ", "roughly "})[random(3)] +
                     query_distance_str(dist * _distance_multiplier) +
                     " to the " + direc });
      }
   }
   if (sizeof(bits) > 1) {
      return implode(bits[0..<2], ", ") + " and " + bits[<1] + " " +_base_desc;
   }
   if (sizeof(bits)) {
      return bits[0] + " " + _base_desc;
   }
   return 0;
}