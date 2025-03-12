#include <weather.h>
#include <clothing.h>
#include <playtesters.h>
#define COMFORTABLE 20
int temperature;
string temperature_str;
int query_wetness()
{
   return 0;
}
void add_wetness(int arg)
{
}
void dry_out()
{
}
void set_personal_temp(int i)
{
   temperature = i;
}
void adjust_personal_temp(int i)
{
   temperature += i;
}
int query_personal_temp()
{
   return temperature;
}
string query_temp_str()
{
   if (!temperature_str || temperature_str == "") {
      return "quite comfortable";
   }
   return temperature_str;
}
int calc_personal_temp()
{
   mixed tmp;
   object where,
    *clothes;
   string item,
     zone,
     type,
    *types,
    *zones;
   int adjustment,
     room_temp,
     correction,
    *enums;
   if (this_object()->query_property("dead")) {
      temperature = 0;
      return 0;
   }
   where = environment(this_object());
   if (!where->query_property("location") &&
       environment(where) && environment(where)->query_property("location"))
      where = environment(where);
   switch (where->query_property("location")) {
   case "outside":
      room_temp = (WEATHER->query_temperature(where) - COMFORTABLE);
      break;
   default:
      room_temp = 0;
   }
   room_temp += where->query_property("warmth");
   room_temp -= where->query_property("cooling");
   adjustment = room_temp;
   adjustment += this_object()->query_property("warmth");
   adjustment -= this_object()->query_property("cooling");
   clothes = filter_array(this_object()->query_wearing(),
                          (: !$1->id("scabbard") &&
                             !$1->id("belt") &&
                             !$1->id("backpack") &&
                             !$1->id("glasses") && !$1->id("jewellery") :));
   zones = ({ });
   foreach(item in clothes) {
      tmp = item->query_type();
      if (arrayp(tmp))  types = tmp;
      else types = ({ tmp });
      foreach(type in types) {
         if (CLOTHING_HANDLER->query_equivilant_type(type))
            type = CLOTHING_HANDLER->query_equivilant_type(type);
         foreach(zone in CLOTHING_HANDLER->query_zone_names(type)) {
            if (member_array(zone, zones) == -1) {
               zones += ({ zone });
            }
            tmp = item->query_property("warmth");
            if (!tmp) {
               adjustment++;
            } else if (intp(tmp) && tmp) {
               adjustment += tmp;
            }
            if (room_temp > 0 && item->query_property("cooling")) {
               adjustment -= item->query_property("cooling");
            }
         }
      }
   }
   if (room_temp < 0) {
      adjustment += sizeof(zones);
      if (room_temp + sizeof(zones) > 5) {
         adjustment -= (room_temp + sizeof(zones) - 5);
      }
   } else {
      adjustment -= sizeof(zones);
      if (room_temp - sizeof(zones) < -5) {
         adjustment -= (room_temp - sizeof(zones) + 5);
      }
   }
   enums = (int *) this_object()->effects_matching("body.wetness");
   if (sizeof(enums)) {
      adjustment -= sqrt(sqrt((int) this_object()->arg_of(enums[0]))) * 2;
   }
   if (temperature > room_temp && room_temp >= 0 || temperature > 5) {
      correction -= (temperature / 5) + 5;
   }
   if (temperature < room_temp && room_temp <= 0 || temperature < -5) {
      correction -= (temperature / 5) - 5;
   }
#ifdef 0
   if ((room_temp < 10 && temperature >= 0) ||
       (room_temp > 10 && temperature <= 0)) {
      factor = (ABS(room_temp - temperature) / 10.0);
      if (factor > 1.0 || factor < 0.0)
         factor = 1.0;
   } else {
      factor = 1.0;
   }
   temperature += to_int((adjustment + correction) * factor);
#endif
   temperature += (adjustment + correction);
   temperature_str = (this_object()->query_race_ob())->
      temperature_effects(this_object(), temperature);
   return temperature;
}
string weather_extra_look()
{
   if (stringp(temperature_str) && strlen(temperature_str)) {
      return capitalize((string) this_object()->query_pronoun()) + " looks " +
         temperature_str + ".\n";
   }
   return "";
}