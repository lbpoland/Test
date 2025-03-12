#include <npc/goals.h>
private mapping _default_plans;
private int _default_priority;
#define GOAL_PLAN_ARRAY_SIZE 1
#define GOAL_PLAN_PLAN 0
void setup() {
}
void create() {
   _default_plans = ([ ]);
   _default_priority = GOAL_INVALID_PRIORITY;
   setup();
}
void initialise_plans(object npc,
                      string goal_name,
                      mixed data) {
}
void initialise(object npc,
                string goal_name,
                class goal_control control) {
   string name;
   foreach (name in keys(_default_plans)) {
tell_creator("pinkfish", "Adding event hook for %O\n", name);
      npc->add_goal_event(base_name(this_object()), name);
   }
   foreach (name in keys(control->extra_plans)) {
      npc->add_goal_event(base_name(this_object()), name);
   }
   initialise_plans(npc, goal_name, control->data);
}
string query_current_plan(object npc,
                          class goal_control control) {
   return control->current_plan;
}
mixed create_goal_data(object npc,
                       string goal_name,
                       mixed stuff) {
   return stuff;
}
void add_goal_to_npc(object npc,
                     mapping extra_plans,
		     mixed stuff) {
   class goal_control frog;
   mixed value;
   string goal_name;
tell_creator("pinkfish", "Adding goal %O to npc(%O).\n", base_name(this_object()), stuff);
   if (!mapp(extra_plans)) {
      extra_plans = ([ ]);
   }
   goal_name = base_name(this_object());
   frog = new(class goal_control);
   frog->extra_plans = extra_plans;
   frog->current_plan = 0;
   frog->priority = GOAL_DEFAULT_PRIORITY;
   frog->data = create_goal_data(npc, goal_name, stuff);
   frog->plan_info = ([ ]);
   npc->add_goal(goal_name, frog);
}
int query_priority(object npc,
                   class goal_control control) {
   if (control->priority != GOAL_DEFAULT_PRIORITY) {
      return control->priority;
   }
   return _default_priority;
}
int query_default_priority() {
   return _default_priority;
}
protected void set_default_priority(int priority) {
   _default_priority = priority;
}
int notify_of_event(object npc,
                    class goal_control control,
                    string event,
                    mixed *data) {
   int value;
   string plan;
   int max_value;
   string max_plan;
   mixed max_data;
   int i;
   mixed info;
   if (control->extra_plans[event]) {
      for (i = 0; i < sizeof(control->extra_plans[event]);
           i += GOAL_PLAN_ARRAY_SIZE) {
         plan = control->extra_plans[event][i + GOAL_PLAN_PLAN];
         info = control->plan_info[plan];
         if (plan->pre_condition(npc,
                                 base_name(this_object()),
                                 info,
                                 event,
                                 data)) {
            value = plan->query_sutability(npc,
                                           base_name(this_object()),
                                           info,
                                           event,
                                           data);
            if (value > max_value) {
               max_value = value;
               max_plan = plan;
               max_data = plan->query_data(npc,
                                           base_name(this_object()),
                                           info,
                                           event,
                                           data);
            }
         }
      }
   }
   if (_default_plans[event]) {
      for (i = 0;
           i < sizeof(_default_plans[event]);
           i += GOAL_PLAN_ARRAY_SIZE) {
         plan = _default_plans[event][i + GOAL_PLAN_PLAN];
         info = control->plan_info[plan];
         if (plan->pre_condition(npc,
                                 base_name(this_object()),
                                 info,
                                 event,
                                 data)) {
            value = plan->query_sutability(npc,
                                           base_name(this_object()),
                                           info,
                                           event,
                                           data);
            if (value > max_value) {
               max_value = value;
               max_plan = plan;
               max_data = plan->query_data(npc,
                                           base_name(this_object()),
                                           info,
                                           event,
                                           data);
            }
         }
      }
   }
   if (max_plan) {
      return npc->activate_plan(max_plan,
                                base_name(this_object()),
                                query_priority(npc, control) +
                                   max_plan->query_priority_offset(),
                                max_data);
   }
   return GOAL_EVENT_NOT_HANDLED;
}
mapping query_default_plans() {
   return _default_plans;
}
protected void add_default_plan(string event_name,
                                string plan) {
   if (!_default_plans[event_name]) {
      _default_plans[event_name] = ({ plan });
   } else if (member_array(plan, _default_plans[event_name]) == -1) {
      _default_plans[event_name] += ({ plan });
   }
}
void set_plan_data(object npc,
                   class goal_control control,
                   string plan,
                   mixed plan_data) {
   control->plan_info[plan] = plan_data;
}
mixed query_plan_data(object npc,
                      class goal_control control,
                      string plan) {
   return control->plan_info[plan];
}