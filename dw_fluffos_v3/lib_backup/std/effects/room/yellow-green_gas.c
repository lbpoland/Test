#include <effect.h>
#define DAMAGE 1 + random(300)
#define CHOKE_TIME 20
string query_classification()
{
  return "gas.poisonous";
}
void beginning(object room, int time, int)
{
  tell_room(room,
    "A billowing yellow-green gas fills the area!\n");
  room->submit_ee("choke", CHOKE_TIME, EE_CONTINUOUS);
  room->submit_ee("clear", time, EE_REMOVE);
  room->add_extra_look(this_object());
  room->add_item("billowing yellow-green gas",
    "A thick, yellow-green gas swirls around the area.");
}
int merge_effect(object, int new_time, int old_time, int)
{
  int time_left;
  time_left = new_time + old_time;
  return time_left;
}
void clear(object room, int, int)
{
  tell_room(room, "The yellow-green gas clears.\n");
  room->remove_item("gas");
}
void choke(object room, int, int)
{
  int damage;
  object ob, *obs;
  obs = filter(all_inventory(room), (: living($1) :));
  foreach(ob in obs)
  {
    damage = DAMAGE;
    damage -= ob->query_ac("gas", damage, "head");
    if(damage > 0)
    {
      tell_object(ob,
        "You choke as you inhale the noxious gas!\n");
      tell_room(room,
        "$C$"+ob->one_short()+" chokes as "+ob->query_pronoun()+
        " inhales the noxious gas!\n", ob);
      ob->adjust_hp(-damage);
      if(ob->query_monitor())
      {
        ob->monitor_points();
      }
    }
  }
}
void end(object room, int time, int id)
{
  room->remove_extra_look(this_object());
}
string extra_look(object thing)
{
  return "A billowing yellow-green gas swirls around here.\n";
}