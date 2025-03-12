#include "path.h"
#include <effect.h>
string query_classification()
{
  return "object.heat";
}
string query_shadow_ob()
{
  return SHADOWS+"heat_shadow";
}
int beginning(object ob, int heat, int id)
{
  ob->submit_ee("change_temperature", ({ 45, 15 }), EE_CONTINUOUS);
  ob->add_extra_look(this_object());
  return heat;
}
void restart(object ob)
{
  ob->add_extra_look(this_object());
}
int merge_effect(object ob, int new_heat, int old_heat, int id)
{
  int heat;
  heat = new_heat + old_heat;
  if(heat < 21)
  {
    ob->submit_ee(0, 0, EE_REMOVE);
  }
  return heat;
}
void end(object ob, int heat, int id)
{
  ob->remove_extra_look(this_object());
}
void change_temperature(object ob, int heat, int id)
{
  int shift;
  int env_temp;
  int new_heat;
  env_temp = environment(ob)->query_heat();
  if(!env_temp)
  {
    env_temp = 20;
  }
  if(env_temp > heat)
  {
    shift = 100 + ((env_temp - heat) / 10);
    if((heat + shift) > env_temp)
    {
      shift = env_temp - heat;
    }
  }
  else
  {
    shift = -100 - ((heat - env_temp) / 10);
    if((heat + shift) < env_temp)
    {
      shift = env_temp - heat;
    }
  }
  tell_creator(find_living("gototh"), "Heat shift: %O\n", shift);
  new_heat = heat + shift;
  if(heat > ob->query_property("red hot at") &&
    new_heat < (ob->query_property("red hot at") + 1))
  {
    tell_room(environment(ob),
      "$C$" + ob->one_short() + " stops glowing red hot.\n");
  }
  if((heat > 80) && (new_heat < 81))
  {
    tell_room(environment(ob),
      "$C$" + ob->one_short() + " seems to have cooled down.\n");
  }
  if(new_heat < 21)
  {
    ob->submit_ee(0, 0, EE_REMOVE);
  }
  else
  {
    ob->set_arg_of(ob->sid_to_enum(id), new_heat);
  }
}
string extra_look(object ob)
{
  int heat;
  int *enums;
  int red_hot;
  enums = ob->effects_matching("object.heat");
  if(!sizeof(enums))
  {
    return "";
  }
  heat = ob->arg_of(enums[0]);
  red_hot = ob->query_property("red hot at");
  if(red_hot)
  {
    if(heat > red_hot)
    {
      return "It is red hot.\n";
    }
    if(heat > 80)
    {
      return "It looks hot.\n";
    }
  }
  return "";
}