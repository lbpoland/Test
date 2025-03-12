inherit "/std/effect_shadow";
int trap_lock(string type) {
  if(type != "pick")
    return 0;
  tell_object(this_player(), "Trap triggered.\n");
  return 0;
}