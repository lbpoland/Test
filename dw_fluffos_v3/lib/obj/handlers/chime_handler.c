#define CREATOR "Ceres"
#include <am_time.h>
#include <chime.h>
#define FIFTEEN_MINS (AM_SECONDS_PER_MINUTE * 15)
class chime {
  object ob;
  int type;
  string mess;
}
void do_chime(class chime record, int type);
class chime *chime_list;
int last_strike;
void create() {
  int next_chime;
  chime_list = ({ });
  next_chime = 301 - (time() % 300);
  remove_call_out("check_time");
  call_out("check_time", next_chime);
}
int register_for_chimes(object ob, int num, string mess) {
  class chime record;
  foreach(record in chime_list) {
    if(record->ob == ob && record->type == num && record->mess == mess) {
      record->type = num;
      record->mess = mess;
      return 1;
    }
  }
  record = new(class chime);
  record->ob = ob;
  record->type = num;
  record->mess = mess;
  chime_list += ({ record });
  return 1;
}
void check_time() {
  int next_chime, minute;
  class chime record;
  minute = AM_TIME_HANDLER->query_am_minute(time());
  foreach(record in chime_list) {
    catch{
      if(minute % 60 < 5)
        do_chime(record, CHIME_HOUR);
      else if(minute % 30 < 5 && record->type > CHIME_HOUR)
        do_chime(record, CHIME_HALF_HOUR);
      else if(minute % 15 < 5 && record->type == CHIME_QUARTER_HOUR)
        do_chime(record, CHIME_QUARTER_HOUR);
    };
  }
  next_chime = (FIFTEEN_MINS + 1) - (time() % FIFTEEN_MINS);
  remove_call_out("check_time");
  call_out("check_time", next_chime);
}
void do_chime(class chime record, int type) {
  if(!record || !record->ob)
    return;
  (record->ob)->chime(record->mess, type);
}
void reset() {
  int next_chime;
  class chime record;
  next_chime = (FIFTEEN_MINS + 1) - (time() % FIFTEEN_MINS);
  remove_call_out("check_time");
  call_out("check_time", next_chime);
  foreach(record in chime_list) {
    if(!record->ob)
      chime_list -= ({ record });
  }
}
mapping query_dynamic_auto_load() {
   mapping tmp;
   tmp = ([ "chime_list" : chime_list ]);
   return tmp;
}
void init_dynamic_arg(mapping maps) {
   if (maps["chime_list"])
      chime_list = maps["chime_list"];
}
mixed stats() {
  return ({ ({ "chime count", sizeof(chime_list) }) });
}