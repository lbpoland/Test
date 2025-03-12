#include <npc/plan.h>
private nosave int _sutability;
private nosave mapping _hooked_events;
void setup() {
}
void create() {
   _sutability = PLAN_INVALID_SUTABILITY;
   _hooked_events = ([ ]);
   setup();
}
int pre_condition(object npc,
		  string goal,
                  mixed goal_info,
		  string event,
		  mixed *data) {
   return 0;
}
int finished(object npc,
             mixed *data) {
   return 1;
}
int query_sutability(object npc,
		     string goal,
                     mixed goal_info,
		     string event,
		     mixed *data) {
   return _sutability;
}
void set_sutability(int sutability) {
   _sutability = sutability;
}
int query_data(object npc,
	       string goal,
               mixed goal_info,
	       string event,
	       mixed *data) {
   return 0;
}
mixed create_plan_data() {
   return 0;
}
void add_hooked_event(string event, function func) {
   _hooked_events[event] = func;
}
void remove_hooked_event(string event) {
   map_delete(_hooked_events, event);
}
int notify_event(object npc,
                 mixed plan_data,
                 string event,
                 mixed *data) {
   if (_hooked_events[event]) {
      return evaluate(_hooked_events[event], npc, plan_data, event, data);
   }
   return 0;
}