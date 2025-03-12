#include "monster.h"
#undef DEBUG
mixed *mon_actions;
void create() {
  mon_actions = ({ });
}
void do_shadow() {
  int i;
  object ob;
  string fname;
  this_object()->shadow_death();
  fname = (string)MONSTER_HAND->query_shadow_name();
  rm(fname+".c");
  for (i=0;i<sizeof(mon_actions);i+=2)
    write_file(fname+".c",
               "inherit \"/std/trigger/"+mon_actions[i]+"\";\n");
  write_file(fname+".c", read_file("/std/living/mon-shadow.c"));
  ob = clone_object(fname);
  ob->setup_shadow(this_object());
  rm(fname+".c");
}
int add_triggered_action(string name, string trigger, mixed ob,
                         string func) {
  int i, j;
#ifdef DEBUG
  log_file("TRIGGERED", ctime(time())+": "+
           file_name(this_object())+"  prev: "+
      implode( map_array( previous_object( -1 ), (: file_name( $1 ) :) ),
      ", " ) +"\n" );
#endif
  if ((i=member_array(trigger, mon_actions)) == -1) {
    mon_actions += ({ trigger, ({ name, ({ ob, func }) }) });
    do_shadow();
  } else if ((j=member_array(name, mon_actions[i+1])) == -1)
    mon_actions[i+1] += ({ name, ({ ob, func }) });
  else
    mon_actions[i+1][j+1] = ({ ob, func });
}
int remove_trigger(string name) {
  int i;
  if ((i=member_array(name, mon_actions)) == -1)
    return 0;
  mon_actions = delete(mon_actions, i, 2);
  if (!sizeof(mon_actions))
    this_object()->shadow_death();
  else
    do_shadow();
  return 1;
}
int remove_triggered_action(string trigger, string name) {
  int i, j;
  if ((i=member_array(trigger, mon_actions)) == -1)
    return 0;
  if ((j=member_array(name, mon_actions[i+1])) == -1)
    return 0;
  mon_actions[i+1] = delete(mon_actions[i+1], i, 2);
  if (!sizeof(mon_actions[i+1]))
    remove_trigger(trigger);
  return 1;
}
mixed *query_actions(string trigger) {
  int i;
  if ((i=member_array(trigger, mon_actions)) == -1)
    return ({ });
  return mon_actions[i+1];
}
mixed *query_mon_actions() { return mon_actions; }