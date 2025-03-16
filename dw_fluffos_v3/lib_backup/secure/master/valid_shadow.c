int valid_shadow(object ob) {
  if (previous_object() == ob)
    return 0;
  return (!ob->query_prevent_shadow(previous_object()) &&
          !sscanf(file_name(ob), "/secure/%*s") &&
          !sscanf(file_name(ob), "/obj/handlers/%*s") &&
          !function_exists("heart_beat" , previous_object(), 1) &&
          !sscanf(file_name(ob), "/cmds/%*s"));
}