mapping add_auto_load_value(mapping map,
                            string file_name,
                            string tag,
                            mixed value) {
   map[file_name + "  :  " + tag] = value;
   return map;
}
mixed query_auto_load_value(mapping map,
                            string file_name,
                            string tag) {
   mixed tmp;
   if (tag == "::") {
      return map;
   }
   tmp = map[file_name + "  :  " + tag];
   if (tmp) {
      return tmp;
   }
   return map[tag];
}