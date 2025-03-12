#include <npc/goals.h>
#include "goal_inherit.h"
class goal_information {
   mixed data;
   int priority;
   string *events;
}
class plan_info {
   int priority;
   mixed data;
}
private nosave mapping _goals;
private nosave mapping _events;
private nosave mapping _emotions;
private nosave mixed* _plans;
private nosave string  _current_plan;
private class goal_information query_goal_information(string goal);
void remove_goal_event(string goal, string event);
void add_goal_event(string goal, string event);
int query_goal_priority(string goal);
int check_current_plan_finished();
void create() {
   _goals = ([ ]);
   _events = ([ ]);
   _plans = ({ });
}
mapping query_goals() {
   return _goals;
}
mapping query_events() {
   return _events;
}
void add_goal(string goal, mixed data) {
   class goal_information frog;
   if (!goal->invarient(this_object())) {
      return ;
   }
   if (!_goals[goal]) {
      frog = new(class goal_information);
      frog->data = data;
      frog->priority = goal->query_priority(this_object(), data);
      frog->events = ({ });
      _goals[goal] = frog;
      goal->initialise(this_object(), goal, data);
   } else {
      goal->add_again(this_object(), query_goal_information(goal)->data, data);
   }
}
void remove_goal(string goal) {
   class goal_information frog;
   string event;
   frog = query_goal_information(goal);
   if (frog) {
      goal->finalise(this_object(), frog->data);
      foreach (event in frog->events) {
         remove_goal_event(goal, event);
      }
      map_delete(_goals, goal);
   }
}
private class goal_information query_goal_information(string goal) {
   class goal_information frog;
   frog = _goals[goal];
   return frog;
}
mixed query_goal_data(string goal) {
   class goal_information frog;
   frog = query_goal_information(goal);
   if (frog) {
      return frog->data;
   }
   return 0;
}
int set_goal_data(string goal, mixed data) {
   class goal_information frog;
   frog = query_goal_information(goal);
   if (frog) {
      frog->data = data;
      return 1;
   }
   return 0;
}
int query_goal_priority(string goal) {
   class goal_information frog;
   frog = query_goal_information(goal);
   if (frog) {
      return frog->priority;
   }
   return GOAL_INVALID_PRIORITY;
}
void change_goal_priority(string goal) {
   class goal_information frog;
   int new_priority;
   string evt;
   frog = query_goal_information(goal);
   if (frog) {
      new_priority = goal->query_priority(this_object(), frog->data);
      if (new_priority != frog->priority) {
         frog->priority = new_priority;
      }
      foreach (evt in frog->events) {
         remove_goal_event(goal, evt);
         add_goal_event(goal, evt);
      }
   }
}
void add_goal_event(string goal, string event) {
   class goal_information frog;
   string test_goal;
   int i;
   int priority;
   int found;
   frog = query_goal_information(goal);
   if (frog) {
      if (!_events[event]) {
         _events[event] = ({ goal });
      } else if (member_array(goal, _events[event]) == -1) {
         priority = query_goal_priority(goal);
         while (i < sizeof(_events[event])) {
            test_goal = _events[event][i];
            if (query_goal_priority(_events[event][i]) < priority) {
               _events[event] = _events[event][0..i-1] + ({ goal }) +
                                _events[event][i..];
               found = 1;
               break;
            }
            i++;
         }
         if (!found) {
            _events[event] += ({ goal });
         }
      }
      frog->events += ({ event });
   }
}
void remove_goal_event(string goal, string event) {
   class goal_information frog;
   frog = query_goal_information(goal);
   if (frog && _events[event]) {
      _events[event] -= ({ goal });
      if (!sizeof(_events[event])) {
         map_delete(_events, event);
      }
      frog->events -= ({ event });
   }
}
varargs void notify_npc_event(string event, mixed *information ...) {
   string goal;
tell_creator("pinkfish", "%s %O\n", event, _events[event]);
   if (_events[event]) {
      foreach (goal in _events[event]) {
         if (goal->notify_of_event(this_object(),
                                   query_goal_information(goal)->data,
                                   event,
                                   information)) {
            return ;
         }
      }
   }
   if (sizeof(_plans)) {
      if (_plans[PLAN_PLAN]->notify_of_event(this_object(),
                                      ((class plan_info)_plans[PLAN_INFO])->data,
                                      event,
				      information)) {
         check_current_plan_finished();
      }
   }
}
void activate_plan(string plan,
                   string goal,
                   mixed data) {
   int priority;
   int pos;
   int i;
   int old;
   mixed *tmp;
   class plan_info info;
   priority = query_goal_priority(goal);
   pos = member_array(plan, _plans);
   if (pos != -1) {
      info = _plans[pos + PLAN_INFO];
      info->data = plan->combine_plans(info->data, data);
      if (info->priority != priority) {
         old = -1;
         for (i = pos - PLAN_ARRAY_SIZE; i >= 0; i -= PLAN_ARRAY_SIZE) {
            if (priority > ((class plan_info)_plans[i + PLAN_INFO])->priority) {
               old = i;
            } else {
               break;
            }
         }
         if (old != -1) {
            tmp = _plans[pos..pos + PLAN_ARRAY_SIZE];
            _plans = _plans[0..pos - 1] + _plans[pos + PLAN_ARRAY_SIZE..];
            _plans = _plans[0..old - 1] + tmp + _plans[old..];
         } else {
            for (i = pos + PLAN_ARRAY_SIZE; i < sizeof(_plans);
                 i += PLAN_ARRAY_SIZE) {
               if (priority < ((class plan_info)_plans[i + PLAN_INFO])->priority) {
                  old = i;
               } else {
                  break;
               }
            }
            if (old != -1) {
               tmp = _plans[old..old + PLAN_ARRAY_SIZE];
               _plans = _plans[0..old - 1] + _plans[old + PLAN_ARRAY_SIZE..];
               _plans = _plans[0..pos - 1] + tmp + _plans[pos..];
            }
         }
      }
   } else {
      old = -1;
      info = new(class plan_info);
      info->data = data;
      info->priority = priority;
      for (i = 0; i < sizeof(_plans); i += PLAN_ARRAY_SIZE) {
         if (priority > ((class plan_info)_plans[i + PLAN_INFO])->priority) {
            _plans = _plans[0..i - 1] + ({ plan, info }) +
                     _plans[i..];
            old = i + PLAN_ARRAY_SIZE;
            break;
         }
      }
      if (i >= sizeof(_plans)) {
         _plans += ({ plan, info });
      }
   }
tell_creator("pinkfish", "Activating %O, %O, %O\n", _current_plan, _plans[PLAN_PLAN], _plans[PLAN_INFO]);
   if (_plans[PLAN_PLAN] != _current_plan) {
      if (_current_plan) {
         pos = member_array(_current_plan, _plans);
         if (pos != -1) {
            _plans[pos + PLAN_PLAN]->suspend_plan(this_object(),
                                                  ((class plan_info)_plans[pos + PLAN_INFO])->data);
         }
      }
      _plans[PLAN_PLAN]->activate_plan(this_object(),
                                       ((class plan_info)_plans[PLAN_INFO])->data);
      while (check_current_plan_finished());
   }
}
int check_current_plan_finished() {
   if (sizeof(_plans)) {
      if (_plans[PLAN_PLAN]->finished(this_object(),
                                      ((class plan_info)_plans[PLAN_INFO])->data)) {
         _plans = _plans[PLAN_ARRAY_SIZE..];
         if (sizeof(_plans)) {
            _plans[PLAN_PLAN]->activate_plan(this_object(),
                                             ((class plan_info)_plans[PLAN_INFO])->data);
         }
         return 1;
      }
   }
   return 0;
}
void set_plan_data(string plan, mixed data) {
   int pos;
   pos = member_array(plan, _plans);
   if (pos != -1) {
      ((class plan_info)_plans[pos + PLAN_INFO])->data = data;
   }
}
mixed *stats() {
   mixed *ret;
   string goal;
   class goal_information frog;
   int goal_num;
   int i;
   goal_num = 0;
   ret = ({ });
   foreach (goal in keys(_goals)) {
      frog = query_goal_information(goal);
      ret += ({ ({ "Goal " + goal_num + ") name", goal }) });
      ret += ({ ({ "Goal " + goal_num + ") events",
                   query_multiple_short(frog->events) }) });
      ret += ({ ({ "Goal " + goal_num + ") priority",  frog->priority }) });
      goal_num++;
   }
   for (i = 0; i < sizeof(_plans); i += PLAN_ARRAY_SIZE) {
      ret += ({ ({ "Plan " + goal_num + ") name", _plans[i + PLAN_PLAN] }) });
      ret += ({ ({ "Plan " + goal_num + ") priority",
                   ((class plan_info)_plans[i + PLAN_INFO])->priority }) });
   }
   return ret;
}
void set_goal_plan_data(string goal, string plan, mixed data) {
   mixed goal_data;
   goal_data = query_goal_data(goal);
   goal->set_plan_data(this_object(), goal_data, plan, data);
}
mixed query_goal_plan_data(string goal, string plan) {
   mixed goal_data;
   goal_data = query_goal_data(goal);
   return goal->query_plan_data(this_object(), goal_data, plan);
}