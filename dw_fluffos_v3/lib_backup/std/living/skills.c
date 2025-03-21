#include <skills.h>
#include <tasks.h>
#include <tune.h>
#undef LOGGING
varargs int calc_bonus( int lvl, string skill, int use_base_stats );
varargs int stat_modify( int bonus, string skill, int use_base_stats );
mixed recursive_skill_add(mixed skil, string *path, int avr, int lvl, int exp,
                           mixed standard);
private void convert_skills(mixed *skills, string path);
int query_skill(string skill);
mapping new_skills;
nosave mapping _bonus_cache,
               _stat_cache,
               _teach_offer;
mapping _last_info;
mapping query_skills() { return copy( new_skills ); }
void set_skills( mapping map ) { new_skills = map; }
int calc_level(string *path);
void create() {
  _bonus_cache = ([ ]);
  _teach_offer = ([ ]);
  _stat_cache = ([ ]);
  new_skills = ([ ]);
  if(!_last_info)
    _last_info = ([ "time" : time() ]);
}
int not_there( string skill ) {
   return undefinedp(new_skills[skill]);
}
mapping query_bonus_cache() { return copy(_bonus_cache); }
mapping query_stat_cache() { return copy(_stat_cache); }
void zap_stat_cache() {
   int i;
   string word, *list, stat;
   stat = this_object()->stats_to_zap();
   if ( !stat ) {
      return;
   }
   if ( find_call_out( "reset_all2" ) == -1 ) {
      call_out( "reset_all2", 1 );
   }
   foreach( i in stat ) {
      list = _stat_cache[ i ];
      if ( !list )
         continue;
      foreach( word in list ) {
         map_delete( _stat_cache, word );
      }
   }
   word = (string)this_object()->query_race_ob();
   if ( word ) {
      word->set_unarmed_attacks( this_object() );
   }
}
void totaly_zap_bonus_cache() {
   _bonus_cache = ([ ]);
}
protected void totaly_zap_stat_cache() {
   _stat_cache = ([ ]);
}
varargs int query_skill_bonus( string skill, int use_base_stats ) {
#ifdef 0
   int tmp, lvl;
   string *path;
   object guild, race;
#endif
  if (!stringp(skill) || !strlen(skill)) {
    return 0;
  }
  if (!new_skills) {
    new_skills = ([ ]);
  }
  if (skill[0] == '.') {
    skill = skill[1..];
  }
  TASKER->set_control( ({ this_object(), skill }) );
  if ( _bonus_cache[ skill ] )
     return stat_modify( _bonus_cache[ skill ], skill, use_base_stats );
  return calc_bonus( query_skill(skill), skill, use_base_stats );
#ifdef 0
  lvl = query_skill(skill);
  guild = (object)this_object()->query_guild_ob();
  race = (object)this_object()->query_race_ob();
  if (race) {
    tmp = (int)race->query_skill_bonus(lvl, skill);
  }
  if (guild) {
    tmp += (int)guild->query_skill_bonus(lvl, skill);
  }
  return calc_bonus( lvl + tmp, skill, use_base_stats );
#endif
}
int query_skill(string skill) {
   string *path;
   if (!new_skills) {
      new_skills = ([ ]);
   }
   if (!stringp(skill)) {
      return 0;
   }
   if (skill[0] == '.') {
      skill = skill[1..];
   }
   TASKER->set_control( ({ this_object(), skill }) );
   if ( not_there( skill ) ) {
      int i;
      path = (string *)SKILL_OB->query_skill_tree(skill);
      if (path) {
         for (i=0;i<sizeof(path);i++) {
            if ( !not_there( path[ i ] ) ) {
               return new_skills[path[i]];
            }
         }
      }
   } else {
      return new_skills[skill];
   }
   return 0;
}
mapping query_complete_skill_branch( string branch ) {
  string *skills = SKILL_OB->query_all_children( branch );
  if ( !arrayp( skills ) || !sizeof( skills ) )
    return ([ ]);
  return allocate_mapping( skills, (: query_skill( $1 ) :) );
}
protected void flatten_it(string skill) {
   int value;
   int i;
   string *same;
   reset_eval_cost();
   value = new_skills[skill];
   same = (mixed *)SKILL_OB->query_immediate_children(skill);
   for (i=0;i<sizeof(same);i++) {
      if ( not_there( same[ i ] ) ) {
         new_skills[same[i]] = value;
      }
      flatten_it(same[i]);
   }
   if (sizeof(same)) {
      map_delete(new_skills, skill);
   }
}
int tm_check_ok(string skill, object exp) {
  string *history, *bits, *abits;
  int i, j, last, delay;
  if ( !_last_info ) {
    _last_info = ([ "time" : time() ]);
  }
#ifdef LOGGING
  if(base_name(previous_object()) != "/obj/handlers/taskmaster" &&
     base_name(previous_object()) != "/std/effects/fighting/combat" &&
     base_name(previous_object()) != "/std/shadows/misc/team" &&
     base_name(previous_object()) != "/std/shadows/other/group" &&
     base_name(previous_object()) != "/global/player" &&
     base_name(previous_object())[0..2] != "/w/") {
     log_file("ATTEMPT_TASK", "Object %s gave skill increase without using "
              "the taskmaster.\n", base_name(previous_object()));
   }
#endif
  history = this_object()->get_history();
  if(sizeof(history)) {
    for(i=0; i<sizeof(history) && history[i]; i++)
      ;
    last = i - 1;
    if(!this_object()->is_alias(history[last]))
      last -= this_object()->query_queued_commands();
    if(last > 0 && sizeof(history[last]) > 1 && skill[<7..] != ".points") {
      for(i=0; i<sizeof(history) && history[i]; i++) {
        if(history[last] == history[i]) {
          j++;
        }
      }
      if(j > 5 || j * 100 / i > 30) {
#ifdef BAD_TM
        log_file(BAD_TM, "%s %s in %s by %O too many attempts at %s [%s]\n",
                 ctime(time())[4..18], this_object()->query_name(), skill,
                 exp, history[last], history[i-1]);
#endif
        if(!_last_info["skill"] || _last_info["skill"][0] != skill)
          _last_info["skill"] = ({ skill, 2 });
        else
          _last_info["skill"][1] += 1;
        _last_info["time"] = time();
        if(!_last_info["object"] || _last_info["object"][0] != base_name(exp))
          _last_info["object"] = ({ base_name(exp), 2 });
        else
          _last_info["object"][1] += 1;
        if(!_last_info["env"] || _last_info["env"][0] != environment())
          _last_info["env"] = ({ environment(), 2 });
        else
          _last_info["env"][1] += 1;
        return 0;
      }
    }
  }
  delay = 30 + random(this_object()->query_level()) +
    random(this_object()->query_skill(skill));
  if(_last_info["object"] && base_name(exp) == _last_info["object"][0])
    delay *= _last_info["object"][1];
  if(this_object()->query_level() * 2 < this_object()->query_skill(skill))
    delay *= 2;
  if(_last_info["env"] && environment(this_object()) == _last_info["env"][0]) {
    delay *= _last_info["env"][1];
  }
  bits = explode(skill, ".");
  if(_last_info["skill"])
    abits = explode(_last_info["skill"][0], ".");
  else
    abits = ({ });
  for(i=0; i<sizeof(bits) && i<sizeof(abits) && bits[i] == abits[i]; i++)
    ;
  if(i && _last_info["skill"])
    delay *= (i * _last_info["skill"][1]);
  else
    delay = 60;
  if(_last_info["time"] > (time() - delay)) {
#ifdef BAD_TM
    log_file(BAD_TM, "%s %s in %s by %O last %d secs ago, delay %d.\n",
             ctime(time())[4..18], this_object()->query_name(), skill,
             exp, (time() - _last_info["time"]), delay);
#endif
    if(!_last_info["skill"] || _last_info["skill"][0] != skill)
      _last_info["skill"] = ({ skill, 2 });
    else
      _last_info["skill"][1] += 1;
    _last_info["time"] = time();
    if(!_last_info["object"] || _last_info["object"][0] != base_name(exp))
      _last_info["object"] = ({ base_name(exp), 2 });
    else
      _last_info["object"][1] += 1;
    if(!_last_info["env"] || _last_info["env"][0] != environment())
      _last_info["env"] = ({ environment(), 2 });
    else
      _last_info["env"][1] += 1;
    return 0;
  }
  if(!_last_info["skill"] || _last_info["skill"][0] != skill)
    _last_info["skill"] = ({ skill, 2 });
  else
    _last_info["skill"][1] += 1;
  _last_info["time"] = time();
  if(!_last_info["object"] || _last_info["object"][0] != base_name(exp))
    _last_info["object"] = ({ base_name(exp), 2 });
  else
    _last_info["object"][1] += 1;
  if(!_last_info["env"] || _last_info["env"][0] != environment())
    _last_info["env"] = ({ environment(), 2 });
  else
    _last_info["env"][1] += 1;
  return 1;
}
varargs int add_skill_level( string skill, int lvl, mixed exp ) {
   string guild, *recursive_skills, *same_level, *bits, *tree;
   int i;
   reset_eval_cost();
   if (!stringp(skill) || !intp(lvl) || lvl > 1000) {
      return 0;
   }
   if (!new_skills || (!mapp(new_skills))) {
      new_skills = ([ ]);
   }
   if (skill[0] == '.') {
      skill = skill[1..];
   }
   recursive_skills = (string *)SKILL_OB->query_related_skills(skill);
   if (!recursive_skills) {
      return 0;
   }
   bits = explode(skill, ".");
   if ( not_there( skill ) && !SKILL_OB->query_only_leaf(skill)) {
      int tmp_lvl, j;
      if (sizeof(bits) > 1) {
         tmp_lvl = 0;
         for (i=sizeof(bits)-1;!tmp_lvl && i>=0;i--) {
            if ( !not_there( implode( bits[ 0 .. i ], "." ) ) ) {
               tmp_lvl = new_skills[implode(bits[0..i], ".")];
               break;
            }
         }
         if (i>=0) {
            for (;i<sizeof(bits);i++) {
               same_level = (string *)
                 SKILL_OB->query_immediate_children(implode(bits[0..i], "."));
               for ( j = 0; j < sizeof( same_level ); j++ ) {
                  new_skills[ same_level[ j ] ] = tmp_lvl;
                  map_delete( _bonus_cache, same_level[ j ] );
               }
            }
         } else {
            tmp_lvl = 0;
         }
      }
   }
   for (i=0;i<sizeof(recursive_skills);i++) {
      if ( !not_there( recursive_skills[ i ] ) ) {
         new_skills[recursive_skills[i]] += lvl;
         if (new_skills[recursive_skills[i]] < 0) {
            new_skills[recursive_skills[i]] = 0;
         }
      }
      map_delete(_bonus_cache, recursive_skills[i]);
   }
   if ( not_there( skill ) ) {
      new_skills[skill] = lvl;
   }
   tree = (string *)SKILL_OB->query_skill_tree(skill);
   for (i=1;i<sizeof(tree);i++) {
      int total, j;
      same_level = (string *)SKILL_OB->query_immediate_children(tree[i]);
      if (sizeof(same_level)) {
         total = 0;
         for (j=0;j<sizeof(same_level);j++) {
            if ( not_there( same_level[ j ] ) ) {
               new_skills[ same_level[ j ] ] = new_skills[ tree[ i ] ];
               map_delete( _bonus_cache, same_level[ j ] );
            }
            total += new_skills[same_level[j]];
         }
         new_skills[tree[i]] = total/sizeof(same_level);
         map_delete( _bonus_cache, tree[ i ] );
      }
   }
   if ( interactive( this_object() ) &&
         ( guild = (string)this_object()->query_guild_ob() ) ) {
      if ( stringp( guild ) ) {
         guild->skills_advanced( this_object(), skill, new_skills[ skill ] );
      }
  }
  if((lvl == 1) && userp(this_object()) && (!exp || objectp(exp))) {
    if(!exp)
      exp = previous_object();
    if(!tm_check_ok(skill, exp)) {
      new_skills[skill] -= 1;
      return 0;
    } else {
      TASKER->award_made( (string)this_object()->query_name(),
                          base_name( exp ), skill, new_skills[ skill ] );
    }
  }
  if ( find_call_out( "reset_all" ) == -1 ) {
    call_out( "reset_all", 1 );
  }
  if(interactive(this_object()) && !this_object()->query_auto_loading())
     this_object()->save();
  return 1;
}
varargs int stat_modify( int lvl, string skill, int use_base_stats ) {
   int i, stat;
   string stat_bonus;
   float bonus;
   bonus = 0.0;
   if ( !_stat_cache[ skill ] || use_base_stats ) {
      stat_bonus = (string)SKILL_OB->query_skill_stat(skill);
      foreach ( i in stat_bonus ) {
         switch( i ) {
            case 'C' :
               if ( use_base_stats )
                  stat = (int)this_object()->query_real_con();
               else
                  stat = (int)this_object()->query_con();
               break;
            case 'D' :
               if ( use_base_stats )
                  stat = (int)this_object()->query_real_dex();
               else
                  stat = (int)this_object()->query_dex();
               break;
            case 'I' :
               if ( use_base_stats )
                  stat = (int)this_object()->query_real_int();
               else
                  stat = (int)this_object()->query_int();
               break;
            case 'S' :
               if ( use_base_stats )
                  stat = (int)this_object()->query_real_str();
               else
                  stat = (int)this_object()->query_str();
               break;
            case 'W' :
            default :
               if ( use_base_stats )
                  stat = (int)this_object()->query_real_wis();
               else
                  stat = (int)this_object()->query_wis();
         }
         if (stat > 0) {
            bonus += (log(stat) / 9.8) - 0.25;
         } else if (stat < 0) {
            bonus -= (log(-stat) / 9.8) + 0.25;
         } else {
            bonus -= 0.25;
         }
         if ( !_stat_cache[ i ] ) {
            _stat_cache[ i ] = ({ skill });
         } else {
            _stat_cache[ i ] |= ({ skill });
         }
      }
      if ( !use_base_stats ) {
         _stat_cache[ skill ] = ({ bonus, stat_bonus });
      }
   } else {
      bonus = _stat_cache[ skill ][ 0 ];
      stat_bonus = _stat_cache[ skill ][ 1 ];
   }
   i = strlen( stat_bonus );
   if ( i ) {
      stat = to_int(lvl + ( lvl * bonus ));
      if (stat < 0) {
         return 0;
      }
      return stat;
   }
   return lvl;
}
varargs int calc_bonus( int lvl, string skill, int use_base_stats ) {
   if (lvl > 60) {
      lvl = 170 + ((lvl-60) >> 1);
   } else if (lvl > 40) {
      lvl = 150 + (lvl-40);
   } else if (lvl > 20) {
      lvl = 100 + ( ((lvl-20)*5) >> 1);
   } else {
      lvl = lvl * 5;
   }
   if ( !use_base_stats ) {
      _bonus_cache[ skill ] = lvl;
   }
   return stat_modify( lvl, skill, use_base_stats );
}
int query_skill_successful(string str, int mod) {
  return (query_skill_bonus(str, 0) + mod >= random(200));
}
void add_teach_offer(object ob, string skill, int num, int lvl, int xp) {
  _teach_offer[ob] = ({ skill, num, lvl, xp });
}
mapping query_teach_offer() { return copy(_teach_offer); }
void stop_teaching_skills(int left, mixed bing) {
   object ob;
   if (left > 0) {
      if (bing[O_OTHER_PER] == this_object()) {
         say(this_object()->short() + " stops teaching themselves some "
             "skills.\n");
      } else if (previous_object() == this_object()) {
         ob = bing[O_OTHER_PER];
         tell_object(ob, this_object()->short() + " interupts your "
                         "training.\n");
      } else {
         ob = this_object();
         tell_object(ob, bing[O_OTHER_PER]->short() + " interupts your "
                         "training.\n");
      }
      say(bing[O_OTHER_PER]->short() + " stops teaching some skills to " +
          this_object()->short() + ".\n",
          ({ this_object(), bing[O_OTHER_PER] }));
      this_object()->adjust_time_left(-((int)this_object()->query_time_left()));
      this_object()->set_interupt_command(0);
      return ;
   }
   if (previous_object() != this_object()) {
      return ;
   }
   if(this_object()->query_xp() < bing[O_XP]) {
      write("Something has gone wrong. :(\n");
      return;
   }
   if (this_object() != bing[O_OTHER_PER]) {
      bing[O_OTHER_PER]->adjust_xp(bing[O_XP]/10);
   }
   this_object()->adjust_xp(-bing[O_XP]);
   add_skill_level(bing[O_SKILL], bing[O_NUM], bing[O_XP]);
   if (this_object() != bing[O_OTHER_PER]) {
      tell_object(this_object(), "You finish learning " + bing[O_NUM] +
                  " levels of "
                  + bing[O_SKILL] + " from " + bing[O_OTHER_PER]->short() +
                  ".\n");
      tell_object(bing[O_OTHER_PER], this_object()->short() + " finishes " +
                  "learning " + bing[O_NUM] + " levels of "
                  +bing[O_SKILL] + " from you.\n");
      say(this_object()->short() + " finishes learning some skills "+
          "from "+bing[O_OTHER_PER]->short()+".\n",
          ({ this_object(), bing[O_OTHER_PER] }));
   } else {
      tell_object(this_object(), "You finish teaching yourself " + bing[O_NUM] +
                  " levels of " + bing[O_SKILL] + ".\n");
      say(this_object()->short() + " finishes learning some skills "
          "from " + this_object()->query_objective() + "self.\n",
          ({ this_object(), bing[O_OTHER_PER] }));
   }
}