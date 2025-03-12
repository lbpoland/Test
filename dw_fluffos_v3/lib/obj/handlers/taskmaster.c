#include <tasks.h>
#define TIME_PER_USER 1800
#define SAVE_FILES "/save/tasks/"
#define LOG_STATS 2
#undef LOGGING
mapping stats;
nosave int last_save;
nosave int last;
nosave string skill;
nosave mixed *control;
nosave int * critical_chances;
varargs mixed perform_task( object person, string skill, int difficulty,
                         int tm_type, int degree );
varargs mixed attempt_task( int difficulty, int bonus, int upper,
                            mixed extra, int degree );
varargs mixed attempt_task_e( int difficulty, int bonus, int upper,
                              int half, int degree );
int is_critical( int margin );
void create() {
   float a, b;
   seteuid( "Root" );
   critical_chances = allocate(100);
   a = 0.93260;
   b = 0.06978;
   for( int i = 0; i < 100; i++ ) {
      critical_chances[i] = a * exp( b * ( i + 1 ) );
   }
}
mapping query_stats( string s_name ) {
  if ( skill != s_name ) {
    skill = s_name;
    if ( file_size( SAVE_FILES + skill +".o" ) > 0 )
      unguarded( (: restore_object, SAVE_FILES + skill :) );
    else
      stats = 0;
  }
  if ( !stats )
    stats = ([ ]);
  return copy( stats );
}
int query_last() { return last; }
mixed *query_control() { return control; }
void set_control( mixed *args ) { control = args; }
void reset_control() { control = 0; }
void award_made( string p_name, string o_name, string s_name, int level ) {
  user_event( "inform", p_name +" gains a level in "+ s_name +" from "+
              o_name + " at level " + level, "skill" );
#ifdef LOG_STATS
#if LOG_STATS == 1
  query_stats( s_name );
  if ( !stats[ level ] )
    stats[ level ] = ([ ]);
  stats[ level ][ explode( o_name, "#" )[ 0 ] ]++;
#else
  query_stats("summary");
  if(s_name[<7..] == ".points" || s_name[0..13] == "other.language")
    return;
  s_name = explode(s_name, ".")[0];
  if(!stats[s_name])
    stats[s_name] = ({ ({ 0 , 0 }),  ({ 0, 0 }),  ({ 0, 0 }) , ({0,0})});
  switch(level) {
  case 0..149:
    stats[s_name][0] = ({ stats[s_name][0][0], stats[s_name][0][1]+1 });
    break;
  case 150..299:
    stats[s_name][1] = ({ stats[s_name][1][0], stats[s_name][1][1]+1 });
    break;
  case 300..599:
    stats[s_name][2] = ({ stats[s_name][2][0], stats[s_name][2][1]+1 });
    break;
  default:
    stats[s_name][3] = ({ stats[s_name][3][0], stats[s_name][3][1]+1 });
    break;
  }
  if(last_save < time() - 300) {
    unguarded( (: save_object, SAVE_FILES + "summary" :) );
    last_save = time();
  }
#endif
#endif
}
#if LOG_STATS == 2
void skill_checked(string s_name, int level) {
  query_stats("summary");
  if(s_name[<7..] == ".points" || s_name[0..13] == "other.language")
    return;
  s_name = explode(s_name, ".")[0];
  if(!stats[s_name])
    stats[s_name] = ({ ({0,0}), ({0,0}), ({0,0}), ({0,0}), ({0,0}) });
  switch(level) {
  case 0..49:
    stats[s_name][0] = ({ stats[s_name][0][0]+1, stats[s_name][0][1] });
    break;
  case 50..149:
    stats[s_name][1] = ({ stats[s_name][1][0]+1, stats[s_name][1][1] });
    break;
  case 150..299:
    stats[s_name][2] = ({ stats[s_name][2][0]+1, stats[s_name][2][1] });
    break;
  case 300..599:
    stats[s_name][3] = ({ stats[s_name][3][0]+1, stats[s_name][3][1] });
    break;
  default:
    stats[s_name][4] = ({ stats[s_name][4][0]+1, stats[s_name][4][1] });
    break;
  }
  if(last_save < time() - 300) {
    unguarded( (: save_object, SAVE_FILES + "summary" :) );
    last_save = time();
  }
}
#endif
string *query_skill_files() {
  return unguarded( (: get_dir, SAVE_FILES +"*.o" :) );
}
void clear_skill_files() {
  string word;
  foreach ( word in unguarded( (: get_dir, SAVE_FILES +"*.o" :) ) )
    unguarded( (: rm, SAVE_FILES + word :) );
  skill = 0;
}
varargs mixed compare_skills( object offob, string offskill,
                              object defob, string defskill,
                              int modifier, int off_tm_type,
                              int def_tm_type, int degree )
{
  int offbonus, defbonus;
  int perc, chance;
  int success_margin, res, deg;
  if( !offob || !defob || !offskill || !defskill )
    return BARF;
  offbonus = offob->query_skill_bonus(offskill);
  defbonus = defob->query_skill_bonus(defskill);
  if( !defbonus ) {
    defbonus = 1;
  }
  if( !offbonus ) {
    offbonus = 1;
  }
  (offbonus > defbonus) ?
    perc = (50 * offbonus * offbonus) / (offbonus * defbonus) :
    perc = 100 - (50 * defbonus * defbonus) / (offbonus * defbonus);
  perc += modifier;
  if(perc > 99)
    perc = 99;
  if(perc < 1)
    perc = 1;
  chance = random(100);
  success_margin = perc - chance;
  if( success_margin > 0 ) {
    switch( perform_task( offob, offskill, defbonus-modifier,
                          off_tm_type, 0 ) )
    {
    case AWARD:
      res = OFFAWARD;
      break;
    default:
      res = OFFWIN;
    }
    if( degree ) {
      if( is_critical(success_margin) ) {
        deg = TASKER_CRITICAL;
      } else {
         if( success_margin < TASKER_MARGINAL_UPPER ) {
           deg = TASKER_MARGINAL;
         } else if( success_margin < TASKER_NORMAL_UPPER ) {
           deg = TASKER_NORMAL;
         } else {
           deg = TASKER_EXCEPTIONAL;
         }
      }
      return new( class tasker_result,
                  result : res,
                  degree : deg,
                  raw    : success_margin );
    } else {
      return res;
    }
  } else {
    switch( perform_task( defob, defskill, offbonus-modifier,
                          def_tm_type, 0 ) ) {
    case AWARD:
      res = DEFAWARD;
      break;
    default:
      res = DEFWIN;
    }
    if( degree ) {
      if( is_critical(success_margin) ) {
        deg = TASKER_CRITICAL;
      } else {
         if( -success_margin < TASKER_MARGINAL_UPPER ) {
           deg = TASKER_MARGINAL;
         } else if( -success_margin < TASKER_NORMAL_UPPER ) {
           deg = TASKER_NORMAL;
         } else {
           deg = TASKER_EXCEPTIONAL;
         }
      }
      return new( class tasker_result,
                  result : res,
                  degree : deg,
                  raw    : success_margin );
    } else {
      return res;
    }
  }
}
varargs mixed perform_task( object person, string skill, int difficulty,
                            int tm_type, int degree ) {
  mixed result;
  int bonus, upper;
  if( !person || !skill )
    return BARF;
  bonus = person->query_skill_bonus( skill );
  switch(tm_type) {
  case TM_FIXED:
    result = attempt_task( difficulty, bonus, 100, 0, degree );
    break;
  case TM_FREE:
    result = attempt_task( difficulty, bonus, 25, 0, degree );
    break;
  case TM_CONTINUOUS:
    result = attempt_task( difficulty, bonus, 50, 0, degree );
    break;
  case TM_COMMAND:
    if( explode( skill, "." )[0] == "covert" )
      result = attempt_task_e
  ( difficulty, bonus, 60, 40, degree );
    else
      result = attempt_task( difficulty, bonus, 100, 0, degree );
    break;
  case TM_RITUAL:
    result = attempt_task_e( difficulty, bonus, 50, 25, degree );
    break;
  case TM_SPELL:
    result = attempt_task_e( difficulty, bonus, 60, 40, degree );
    break;
  case TM_NONE:
    result = attempt_task_e(difficulty, bonus, 1, 0, degree);
    if(classp(result) && ( (class tasker_result)result )->result == AWARD) {
      result->result = SUCCEED;
    } else if( result == AWARD ) {
      result = SUCCEED;
    }
    break;
  default:
#ifdef LOGGING
    if(file_name(previous_object())[0..2] != "/w/")
      log_file("ATTEMPT_TASK",
               "%s Object %s using old perform_task [%d, %d]\n",
               ctime(time()), base_name(previous_object()), tm_type, degree );
#endif
    upper = tm_type;
    if ( !upper )
      upper = 100;
    result = attempt_task( difficulty, bonus, upper, 0, degree );
  }
  if(classp(result) && ( (class tasker_result)result )->result == AWARD ||
     result == AWARD) {
    if(person->advancement_restriction() ||
       !person->add_skill_level(skill, 1, previous_object())) {
      if(classp(result))
        result->result = SUCCEED;
      else
        result = SUCCEED;
    }
  }
  return result;
}
varargs mixed attempt_task( int difficulty, int bonus, int upper,
                            mixed extra, int degree )
{
   int margin, success_margin, deg, res;
   float tmp;
#ifdef LOGGING
   if( call_stack(2)[1] != "perform_task" &&
       base_name( previous_object() ) != "/std/effects/fighting/combat" &&
       file_name( previous_object() )[0..2] != "/w/" )
   {
     log_file("ATTEMPT_TASK", "%s Object %s is using old attempt_task "
              "[%O]\n",
              ctime( time() ), base_name( previous_object() ), call_stack(2) );
   }
#endif
#if LOG_STATS == 2
   if(pointerp(control) && control[1]) {
      skill_checked(control[1], control[0]->query_skill(control[1]));
   }
#endif
   if ( bonus < difficulty ) {
#ifdef DEBUG
      if(pointerp(control) && control[0]->query_name() == WATCH_PLAYER &&
         find_player(DEBUG))
      {
         tell_creator( DEBUG, "%^RED%^"
           + sprintf( "TM: %s Skill: %s [%d] [%d] Failed\n",
                      control[0]->query_name(), control[1], bonus, difficulty )
           + "%^RESET%^" );
      }
#endif
      if( degree ) {
         return new( class tasker_result,
                     result : FAIL,
                     degree : ( is_critical( -100 ) ?
                                TASKER_CRITICAL :
                                TASKER_EXCEPTIONAL ),
                     raw    : -100 );
      } else {
         return FAIL;
      }
   }
   if ( !extra )
      margin = 3 * sqrt( difficulty );
   else {
      if ( intp( extra ) )
         margin = extra;
      if ( pointerp( extra ) )
         margin = extra[ 0 ] + extra[ 1 ] * sqrt( difficulty );
   }
   if ( !margin )
      return BARF;
   if ( bonus > difficulty + margin ) {
#ifdef DEBUG
     if(pointerp(control) &&
        WATCH_PLAYER || control[0]->query_name() == WATCH_PLAYER &&
        find_player(DEBUG))
       tell_object(find_player(DEBUG), "%^RED%^" + sprintf("TM: %s Skill: %s [%d] [%d] [%d] Succeeded\n", control[0]->query_name(), control[1], bonus, difficulty, margin) + "%^RESET%^");
#endif
      if( degree ) {
         return new( class tasker_result,
                     result : SUCCEED,
                     degree : ( is_critical(100) ?
                                TASKER_CRITICAL :
                                TASKER_EXCEPTIONAL ),
                     raw    : 100 );
      } else {
         return SUCCEED;
      }
   }
   if(!margin)
     margin = 1;
   success_margin = ( ( 100 * ( bonus - difficulty ) ) / margin ) - random(100);
   if ( success_margin <= 0 ) {
#ifdef DEBUG
     if(pointerp(control) &&
        control[0]->query_name() == WATCH_PLAYER &&
        find_player(DEBUG))
       tell_object(find_player(DEBUG), "%^RED%^" + sprintf("TM: %s Skill: %s [%d] [%d] Failed (2)\n", control[0]->query_name(), control[1], bonus, difficulty) + "%^RESET%^");
#endif
      if( degree ) {
         if( is_critical(success_margin) ) {
            deg = TASKER_CRITICAL;
         } else {
            if( -success_margin < TASKER_MARGINAL_UPPER ) {
               deg = TASKER_MARGINAL;
            } else if( -success_margin < TASKER_NORMAL_UPPER ) {
               deg = TASKER_NORMAL;
            } else {
               deg = TASKER_EXCEPTIONAL;
            }
         }
         return new( class tasker_result,
                     result : FAIL,
                     degree : deg,
                     raw    : success_margin );
      } else {
         return FAIL;
      }
   }
   if ( pointerp( control ) ) {
#ifdef DEBUG
     if(find_player(DEBUG) && bonus >= MIN_LEVEL)
       tell_object(find_player(DEBUG), "%^RED%^" +
                   sprintf("TM: %s Skill: %s [%d,%d] OU: %d ",
                           control[0]->query_name(),
                           control[1], bonus,
                           control[0]->query_skill(control[1]),
                           upper));
#endif
     upper = (int)control[ 0 ]->stat_modify(upper, control[ 1 ] );
#ifdef DEBUG
     if(find_player(DEBUG) && bonus >= MIN_LEVEL)
       tell_object(find_player(DEBUG),
                   sprintf("SU: %d ", upper));
#endif
     tmp = exp((control[0]->query_skill(control[1])-BASE) / DECAY);
     upper = to_int(upper / tmp) - MODIFIER;
#ifdef DEBUG
     if(find_player(DEBUG) && bonus >= MIN_LEVEL)
       tell_object(find_player(DEBUG), sprintf("LU: %d ", upper));
#endif
     if(upper < 0)
       upper = 0;
#ifdef DEBUG
      if(find_player(DEBUG) && bonus >= MIN_LEVEL)
       tell_object(find_player(DEBUG), sprintf("FU: %d\n",
                                                 upper) + "%^RESET%^");
#endif
   }
#ifdef DEBUG
   else
     if(find_player(DEBUG))
       tell_object(find_player(DEBUG), sprintf("No control: %O\n",
                                                 previous_object(-1)));
#endif
     if(!margin)
        margin = 1;
   if( random(100) < ( upper * ( difficulty + margin - bonus ) ) / margin )
      res = AWARD;
   else
      res = SUCCEED;
   if( degree ) {
      if( is_critical(success_margin) ) {
         deg = TASKER_CRITICAL;
      } else {
         if( success_margin < TASKER_MARGINAL_UPPER ) {
            deg = TASKER_MARGINAL;
         } else if( success_margin < TASKER_NORMAL_UPPER ) {
            deg = TASKER_NORMAL;
         } else {
            deg = TASKER_EXCEPTIONAL;
         }
      }
      return new( class tasker_result,
                  result : res,
                  degree : deg,
                  raw    : success_margin );
   } else {
      return res;
   }
}
varargs mixed attempt_task_e( int difficulty, int bonus, int upper,
                              int half, int degree )
{
   float fail_chance;
   float tmp;
   int success_margin, deg, res;
#ifdef LOGGING
   if(call_stack(2)[1] != "perform_task" &&
      base_name(previous_object()) != "/std/effects/fighting/combat" &&
      file_name(previous_object())[0..2] != "/w/") {
     log_file("ATTEMPT_TASK", "%s Object %s is using old attempt_task "
              "[%O]\n",
              ctime(time()), base_name(previous_object()), call_stack(2));
   }
#endif
#if LOG_STATS == 2
   if(pointerp(control) && control[1]) {
     skill_checked(control[1], control[0]->query_skill(control[1]));
   }
#endif
   if ( bonus < difficulty ) {
      if( degree ) {
         return new( class tasker_result,
                     result : FAIL,
                     degree : ( is_critical( -100 ) ?
                                TASKER_CRITICAL :
                                TASKER_EXCEPTIONAL ),
                     raw    : -100 );
      } else {
         return FAIL;
      }
   }
   if( !half )
      half = 6 * sqrt( difficulty );
   if( !half )
      half = 1;
   fail_chance = exp( ( -0.693 * ( bonus - difficulty ) ) / half );
   success_margin = ( random( 1000 ) - ( 1000 * fail_chance ) ) / 10;
   if ( success_margin < 0 ) {
      if( degree ) {
         if( is_critical(success_margin) ) {
            deg = TASKER_CRITICAL;
         } else {
            if( -success_margin < TASKER_MARGINAL_UPPER ) {
               deg = TASKER_MARGINAL;
            } else if( -success_margin < TASKER_NORMAL_UPPER ) {
               deg = TASKER_NORMAL;
            } else {
               deg = TASKER_EXCEPTIONAL;
            }
         }
         return new( class tasker_result,
                     result : FAIL,
                     degree : deg,
                     raw    : success_margin );
      } else {
         return FAIL;
      }
   }
   if ( pointerp( control ) ) {
#ifdef DEBUG
     if(find_player(DEBUG) && bonus >= MIN_LEVEL)
       tell_object(find_player(DEBUG), "%^RED%^" +
                   sprintf("TM: %s Skill: %s [%d,%d] OU: %d ",
                           control[0]->query_name(),
                           control[1], bonus,
                           control[0]->query_skill(control[1]),
                           upper));
#endif
     upper = (int)control[ 0 ]->stat_modify( upper, control[ 1 ] );
#ifdef DEBUG
     if(find_player(DEBUG) && bonus >= MIN_LEVEL)
       tell_object(find_player(DEBUG),
                   sprintf("SU: %d ", upper));
#endif
     tmp = exp((control[0]->query_skill(control[1])-BASE) / DECAY);
     upper = to_int(upper / tmp) - E_MODIFIER;
#ifdef DEBUG
     if(find_player(DEBUG) && bonus >= MIN_LEVEL)
       tell_object(find_player(DEBUG), sprintf("LU: %d ", upper));
#endif
     if(upper < 0)
       upper = 0;
#ifdef DEBUG
      if(find_player(DEBUG) && bonus >= MIN_LEVEL)
       tell_object(find_player(DEBUG), sprintf("FU: %d\n",
                                                 upper) + "%^RESET%^");
#endif
   }
   if ( random(1000) < ( upper * fail_chance * 10 )
    &&  bonus < difficulty + ( half * 5 ) ) {
      res = AWARD;
   } else {
      res = SUCCEED;
   }
   if( degree ) {
      if( is_critical(success_margin) ) {
         deg = TASKER_CRITICAL;
      } else {
         if( success_margin < TASKER_MARGINAL_UPPER ) {
            deg = TASKER_MARGINAL;
         } else if( success_margin < TASKER_NORMAL_UPPER ) {
            deg = TASKER_NORMAL;
         } else {
            deg = TASKER_EXCEPTIONAL;
         }
      }
      return new( class tasker_result,
                  result : res,
                  degree : deg,
                  raw    : success_margin );
   } else {
      return res;
   }
}
int is_critical( int margin ) {
   if ( margin < 0 ) {
      margin *= -1;
   }
   if ( margin > 100 ) {
      margin = 100;
   }
   if ( margin == 0 ) {
      return 0;
   }
   return random(10000) < critical_chances[ margin - 1 ];
}