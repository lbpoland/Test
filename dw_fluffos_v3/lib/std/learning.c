#include <money.h>
#include <tasks.h>
class step {
  string *blurbs;
  string skill;
  int difficulty;
  string *responses;
  string *params;
  string award_mess;
  string succeed_mess;
  string fail_mess;
}
class lesson {
  mapping minimum_skills;
  mapping maximum_skills;
  string *materials;
  int cost;
  string currency;
  string *lesson_ending;
  object teacher;
  class step *plan;
}
private nosave mapping _lessons;
private nosave int current_step;
private nosave int attempt;
int lesson_response(string, object, int, string);
int register_lesson(string name, mapping minimum_skills,
                    mapping maximum_skills, string *materials, int cost,
                    string currency, string *lesson_ending, object teacher ) {
  if(!_lessons)
    _lessons = ([ ]);
  if(_lessons[name])
    return 0;
  _lessons[name] = new(class lesson,
                       minimum_skills : minimum_skills,
                       maximum_skills : maximum_skills,
                       materials : materials,
                       cost : cost,
                       currency : currency,
                       lesson_ending : lesson_ending,
                       teacher : teacher
                       );
  return 1;
}
int add_step( string lesson_name, string *blurbs, string skill, int diff,
        string *responses, string *params, string award_mess, string succeed_mess,
        string fail_mess) {
  if(!_lessons)
    _lessons = ([ ]);
  if( !_lessons[lesson_name] ){
    return 0;
  }
  if( !_lessons[lesson_name]->plan ){
    _lessons[lesson_name]->plan = ({ });
  }
  _lessons[lesson_name]->plan += ({ new(class step,
          blurbs : blurbs,
          skill : skill,
          difficulty : diff,
          responses : responses,
          params : params,
          award_mess : award_mess,
          succeed_mess : succeed_mess,
          fail_mess : fail_mess
          ) });
  return 1;
}
int has_required_skills( string name, object player ) {
  string skill;
  int p_level;
  foreach( skill in (keys(_lessons[name]->minimum_skills)) ){
    p_level = player->query_skill(skill);
    if( p_level < _lessons[name]->minimum_skills[skill] ){
      return 0;
    }
  }
  foreach( skill in (keys(_lessons[name]->maximum_skills)) ){
    p_level = player->query_skill(skill);
    if( p_level > _lessons[name]->maximum_skills[skill] ){
      return 0;
    }
  }
  return 1;
}
int has_required_materials( string name, object player ) {
  string mat;
  foreach( mat in _lessons[name]->materials ) {
    if( sizeof( filter_array(deep_inventory(player),
           (: ($1)->query_short() :) ) ) ){
      return 1;
    }
  }
  return 0;
}
int has_required_cash( string name, object player ) {
  if(player->query_value_in(_lessons[name]->currency) < _lessons[name]->cost) {
    return 0;
  } else {
    return 1;
  }
}
int start_lesson(string name, object player) {
  string *needed;
  if(!_lessons[name])
    return notify_fail(player, "Sorry, it's not clear what you want to learn "
                "here.\n");
  needed = ({ });
  if(!has_required_skills(name, player))
    needed += ({ "skills" });
  if(!has_required_materials( name, player ))
    needed += ({ "materials" });
  if(!has_required_cash( name, player ))
    needed += ({ "cash" });
  if(sizeof(needed)) {
    debug_printf( "Player doesn't have the correct %s\n",
                  query_multiple_short(needed) );
    return add_failed_mess("Sorry, You don't have the correct " +
                  query_multiple_short(needed) + " to learn today.\n");
  }
  call_out("lesson_step", 1, name, player, 0);
  return 1;
}
string *query_lessons() { return keys(_lessons); }
protected void lesson_step(string name, object student, int lessonstep) {
  string str;
  class step current;
  object teacher = _lessons[name]->teacher;
  int i;
  current = _lessons[name]->plan[lessonstep];
  str = "";
  for(i=0; i<sizeof(current->responses); i++) {
    if(current->params && sizeof(current->params) > i) {
      str = " <string:'" + current->params[i] + "'>";
      student->add_command(current->responses[i], this_object(), str,
                           (: lesson_response($(name), $(student),
                                              $(lessonstep), $4) :));
    } else {
      str = "";
      student->add_command(current->responses[i], this_object(), str,
                           (: lesson_response($(name), $(student),
                                              $(lessonstep), "") :));
    }
  }
  foreach( str in (current->blurbs) ) {
   if( teacher )
      teacher->queue_command(str);
    else
      tell_object(student, str);
  }
}
int lesson_response(string name, object student, int lessonstep, string args) {
  class step current;
  if(this_player() != student)
    return 0;
  current = _lessons[name]->plan[lessonstep];
  if(sizeof(current->params) &&
     member_array(args[0], current->params) == -1)
    return student->add_failed_mess(this_object(), "Invalid response.\n",
            ({ }));
  switch(TASKER->perform_task(student, current->skill, current->difficulty,
                              TM_FIXED)) {
  case AWARD:
    tell_object(student, "%^YELLOW%^"+current->award_mess+"%^RESET%^\n");
  case SUCCEED:
    tell_object( student, current->succeed_mess + "\n");
    student->remove_object(this_object(), 1);
    if( (sizeof(_lessons[name]->plan)-1) == lessonstep ) {
      tell_creator("belle", "Lesson is on its last step: %d\n", lessonstep );
      call_out( "lesson_end", 1, name, student );
      return 1;
    } else {
      call_out("lesson_step", 1, name, student, ++lessonstep);
    }
    break;
  default:
    tell_object(student, current->fail_mess + "\n" );
    break;
  }
  return 1;
}
int lesson_end ( string name, object student ) {
  string str;
  object teacher = _lessons[name]->teacher;
  foreach( str in (_lessons[name]->lesson_ending) ) {
    if( teacher )
      teacher->queue_command(str);
    else
      tell_object(student, str);
  }
  return 1;
}