#include <tasks.h>
#define SKILL "covert.lockpick.traps"
private nosave int _trap_difficulty;
private nosave string _trap_trigger;
private nosave string _trap_description;
private nosave mixed _trap_message;
private nosave mixed _trap_effect;
private nosave mixed _trap_armed;
void setup_trap(int difficulty, string trigger, string description,
                     mixed message, mixed effect) {
  if(!trigger)
    return;
  if(trigger == "open")
    this_object()->set_open_trap(this_object(), "basic_trap");
  else
    this_object()->set_lock_trap(this_object(), "basic_trap");
  _trap_difficulty = difficulty;
  _trap_trigger = trigger;
  _trap_description = description;
  _trap_message = message;
  _trap_effect = effect;
}
mixed *query_trap_data() {
  return ({ _trap_difficulty, _trap_trigger, _trap_description,
              _trap_message, _trap_effect, _trap_armed });
}
int query_trap_difficulty() { return _trap_difficulty; }
string query_trap_trigger() { return _trap_trigger; }
string query_trap_description() { return _trap_description; }
mixed query_trap_message() { return _trap_message; }
mixed query_trap_effect() { return _trap_effect; }
void set_trap_armed(int i) { _trap_armed = i; }
int query_trap_armed() { return _trap_armed; }
int basic_trap(string action) {
  if(!_trap_armed || action != _trap_trigger)
    return 1;
  switch(TASKER->perform_task(this_player(), SKILL, _trap_difficulty,
                              TM_FREE)) {
  case AWARD:
    write("%^YELLOW%^You feel you have learned something about avoiding "
          "traps.%^RESET%^\n");
  case SUCCEED:
    return 1;
  default:
    if(arrayp(_trap_message)) {
      write(_trap_message[0]);
      say(_trap_message[1], this_player());
    } else
      write(_trap_message);
    if(intp(_trap_effect)) {
      if(_trap_effect > this_player()->query_hp())
        this_player()->do_death();
      else
        this_player()->adjust_hp(-(_trap_effect));
    } else if(arrayp(_trap_effect)) {
      if(sizeof(_trap_effect) == 2)
        this_player()->add_effect(_trap_effect[0], _trap_effect[1]);
      else
        this_player()->add_effect(_trap_effect[0], _trap_effect[1..]);
    } else
      this_player()->add_effect(_trap_effect);
    return 0;
  }
}