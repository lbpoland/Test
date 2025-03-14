#define CREATOR "Ceres"
#include <am_time.h>
inherit "std/object";
#define HOURS ({"twelve", "one", "two", "three", "four", "five", "six", \
                "seven", "seven plus one", "nine", "ten", "eleven" })
#define CHIME_HANDLER "/obj/handlers/chime_handler"
int show_date;
void create() {
  do_setup++;
  object::create();
  do_setup--;
  if(!do_setup)
    this_object()->setup();
  add_extra_look(this_object());
}
string query_time_string() {
  string mess;
  int minute, hour, *arr;
  minute = (AM_TIME_HANDLER->query_am_minute(time()) % 60);
  hour = AM_TIME_HANDLER->query_am_hour(time());
  if(minute > 30 )
    hour = hour + 1;
  hour = hour % 12;
  mess = "";
  switch(minute) {
  case 53..57:
    mess += "five to " + HOURS[hour]; break;
  case 48..52:
    mess += "ten to " + HOURS[hour]; break;
  case 43..47:
    mess += "quarter to " + HOURS[hour]; break;
  case 38..42:
      mess += "twenty to " + HOURS[hour]; break;
  case 33..37:
    mess += "twenty-five to " + HOURS[hour]; break;
  case 28..32:
    mess += "half past " + HOURS[hour]; break;
  case 23..27:
    mess += "twenty-five past " + HOURS[hour]; break;
  case 18..22:
    mess += "twenty past " + HOURS[hour]; break;
  case 13..17:
    mess += "a quarter past " + HOURS[hour]; break;
  case 8..12:
    mess += "ten past " + HOURS[hour]; break;
  case 3..7:
    mess += "five past " + HOURS[hour]; break;
  default:
    mess += HOURS[hour] + " o'clock";
  }
  if(show_date) {
    arr = AM_TIME_HANDLER->query_am_time_array(time());
    mess += " on " +
      AM_TIME_HANDLER->query_day_of_week(arr[AM_TIME_DAY_OF_WEEK]) + " the " +
      ordinal(arr[AM_TIME_DAY_OF_MONTH]) + " of " +
      AM_TIME_HANDLER->query_month(arr[AM_TIME_MONTH]);
  }
  return mess;
}
string extra_look(object thing) {
  return query_time_string() + ".\n";
}
void set_show_date() { show_date = 1; }
void set_chimes(int num, string mess) {
  CHIME_HANDLER->register_for_chimes(this_object(), num, mess);
}
void chime(string chime_message, int type) {
  say(chime_message);
}