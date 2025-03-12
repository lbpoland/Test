#include <effect.h>
class effect_shadow {
   object shad_ob;
   int idnum;
}
class effect_event {
   int inctime;
   mixed func;
   int eff_ob_num;
   mixed interval;
   int flags;
   mixed eff_ev_args;
}
#undef DEBUG
#ifdef DEBUG
nosave int logging_effects;
void set_logging_effects(int i) { logging_effects = i; }
int query_logging_effects() { return logging_effects; }
#endif
class effect_data {
   int current_enum;
   int next_id;
   int next_event_time;
   class effect_shadow* shadows;
}
void delete_effect(int i);
private nosave class effect_data _data;
private class effect *effs;
private class effect_event *eeq;
protected void create() {
  effs = ({ });
  eeq = ({ });
  _data = new(class effect_data);
  _data->shadows = ({ });
  _data->next_id = 0;
  _data->current_enum = -1;
  _data->next_event_time = 0;
#ifdef DEBUG
  logging_effects = 0;
#endif
}
void reset_effects() {
   effs = ({ });
   eeq = ({ });
   _data->shadows = ({ });
   _data->current_enum = -1;
   _data->next_event_time = 0;
   remove_call_out("effect_timer");
#ifdef DEBUG
   if ( logging_effects )
      log_file( "EFFECT_WOBBLE",
               "%d:%s(%d) reset_effects:remove_call_out( \"effect_timer\" )\n",
               time() % 1000,
               this_object()->query_name(),
               _data->current_enum);
#endif
}
object affected_object() {
   object this, other;
   other = this_object();
   this = other;
   while (objectp(other)) {
      this = other;
      other = query_shadowing(this);
   }
   return this;
}
void effect_freeze() {
   remove_call_out( "effect_timer" );
#ifdef DEBUG
   if ( logging_effects )
      log_file( "EFFECT_WOBBLE",
               "%d:%s(%d) effect_freeze:remove_call_out( \"effect_timer\" )=%d\n",
               time() % 1000,this_object()->query_name(),_data->current_enum,timeleft);
#endif
   if ( sizeof( eeq ) && _data->next_event_time) {
      if (_data->next_event_time <= time()) {
         eeq[ 0 ]->inctime = 1;
      } else {
         eeq[ 0 ]->inctime = _data->next_event_time - time();
      }
   }
}
void effects_saving() {
   int i, neffs;
   string effn;
   mixed arg;
   neffs = sizeof( effs );
   for ( i = 0; i < neffs; i++ ) {
      effn = effs[ i ]->ob_name;
      arg = effs[ i ]->arg;
      if ( pointerp( arg ) && ( sizeof( arg ) == 3 ) &&
          ( arg[ 2 ] == BOGUS_OLD_ARG ) ) {
         arg = arg[ 1 ];
      }
      if ( effn ) {
         catch( (void)effn->saving( affected_object(), arg, i ) );
      }
   }
}
void effects_quiting() {
   int i, neffs;
   string effn;
   mixed arg;
   neffs = sizeof( effs );
   for ( i = 0; i < neffs; i++ ) {
      effn = effs[ i ]->ob_name;
      arg = effs[ i ]->arg;
      if ( pointerp( arg ) && ( sizeof( arg ) == 3 ) &&
          ( arg[ 2 ] == BOGUS_OLD_ARG ) ) {
         arg = arg[ 1 ];
      }
      if ( effn ) {
         catch( (void)effn->quiting( affected_object(), arg, i ) );
      }
   }
}
void effects_desting() {
   int i, neffs;
   string effn;
   mixed arg;
   neffs = sizeof( effs );
   for ( i = 0; i < neffs; i++ ) {
      effn = effs[ i ]->ob_name;
      arg = effs[ i ]->arg;
      if ( pointerp( arg ) && ( sizeof( arg ) == 3 ) &&
          ( arg[ 2 ] == BOGUS_OLD_ARG ) ) {
         arg = arg[ 1 ];
      }
      if ( effn ) {
         catch( (void)effn->desting( affected_object(), arg, i ) );
      }
   }
}
void effect_unfreeze() {
   if ( sizeof( eeq ) ) {
#ifdef DEBUG
      if ( logging_effects )
         log_file( "EFFECT_WOBBLE",
                  "%d:%s(%d) effect_unfreeze:call_out( \"effect_timer\", %d)\n",
                  time() % 1000,this_object()->query_name(),_data->current_enum,eeq[ 0 ]->inctime);
#endif
      remove_call_out( "effect_timer" );
      _data->next_event_time = time() + eeq[ 0 ]->inctime;
      call_out( "effect_timer", eeq[ 0 ]->inctime );
   }
}
protected int int_submit_ee( int eff_ob_num, mixed fun, mixed
      interval, int flags, mixed event_args ) {
   int i, ntime;
#ifdef DEBUG
   if ( logging_effects )
      log_file( "EFFECT_WOBBLE",
               "%d:%s(%d) int_submit_ee:( %d, %O, %O, %s, %O )\n",
               time() % 1000,this_object()->query_name(),_data->current_enum,
               eff_ob_num, fun, interval,
               ({"once","remove","continuous"})[flags], event_args );
#endif
   if (intp(interval))
      ntime = interval;
   else if (pointerp(interval)) {
      switch (sizeof(interval)) {
       case 0:
         return -1;
       case 1:
         ntime = interval[0];
         break;
       case 2:
         ntime = interval[0] + random(interval[1] - interval[0] + 1);
         break;
       case 3:
         ntime = 0;
         for (i = 0; i < interval[2]; i++) {
            ntime += interval[0] + random(interval[1] - interval[0] + 1);
         }
         ntime += (interval[2]/2);
         ntime /= interval[2];
         break;
       default:
         return -1;
      }
   } else return -1;
   if (flags == EE_REMOVE) {
      for(i = 0; i < sizeof(eeq); i++) {
         if ((eeq[i]->eff_ob_num == eff_ob_num) &&
             (eeq[i]->flags == EE_REMOVE)) {
            eeq = eeq[0..i-1] + eeq[i+1..];
            break;
         }
      }
   }
   if ( ntime < 0 ) {
      return 0;
   }
   for (i = 0; i < sizeof(eeq); i++) {
      if (ntime < eeq[i]->inctime) {
         eeq[i]->inctime -= ntime;
         eeq = eeq[0..i-1] +
            ({ new(class effect_event, inctime : ntime, func : fun,
                   eff_ob_num : eff_ob_num, interval : interval,
                   flags : flags, eff_ev_args : event_args ) }) + eeq[i..];
         break;
      }
      ntime -= eeq[i]->inctime;
   }
   if ((i == sizeof(eeq)) && eeq) {
      eeq += ({ new(class effect_event, inctime : ntime, func : fun,
                    eff_ob_num : eff_ob_num, interval : interval,
                    flags : flags, eff_ev_args : event_args ) });
   } else if ( !sizeof(eeq) ) {
      eeq = ({ new(class effect_event, inctime : ntime, func : fun,
                   eff_ob_num : eff_ob_num, interval : interval,
                   flags : flags, eff_ev_args : event_args ) });
   }
   return i;
}
varargs void submit_ee(mixed fun, mixed interval, int flags, mixed
    event_args ) {
  int enumb;
  if( undefinedp( event_args ) )
     event_args = 0;
#ifdef DEBUG
   if ( logging_effects )
      log_file( "EFFECT_WOBBLE",
               "%d:%s(%d) submit_ee:( %O, %O, %s, %O )\n",
               time() % 1000,this_object()->query_name(),_data->current_enum,
               fun, interval, ({"once","remove","continuous"})[flags],
               event_args );
#endif
  enumb = _data->current_enum;
  if (enumb < 0) {
    enumb = member_array(1,
        map(_data->shadows, (: $1 && (((class effect_shadow)$1)->shad_ob == previous_object()) :)));
    if (enumb < 0) {
      error("Can not submit from that object");
    }
  }
  effect_freeze();
  int_submit_ee(enumb, fun, interval, flags, event_args );
  effect_unfreeze();
}
varargs void submit_ee2(int enum, mixed fun, mixed interval, int flags,
    mixed event_args ) {
  if( undefinedp( event_args ) )
    event_args = 0;
#ifdef DEBUG
   if ( logging_effects )
      log_file( "EFFECT_WOBBLE",
               "%d:%s(%d) int_submit_ee:( %d, %O, %O, %s, %O )\n",
               time() % 1000,this_object()->query_name(),_data->current_enum,
               enum, fun, interval, ({"once","remove","continuous"})[flags],
               event_args );
#endif
  if (enum < 0)
    error("Can't submit from that object");
  effect_freeze();
  int_submit_ee(enum, fun, interval, flags, event_args );
  effect_unfreeze();
}
int expected_tt(int flag, int new_enum) {
  int i, timeleft, enum;
  if (flag)
    enum = new_enum;
  else
    enum = _data->current_enum;
  if (enum < 0)
    return -1;
  if (!sizeof(eeq))
    return -1;
  effect_freeze();
  for (i = 0; i < sizeof(eeq); i++) {
    timeleft += eeq[i]->inctime;
    if ((eeq[i]->eff_ob_num == enum) &&
        (eeq[i]->flags == EE_REMOVE)) {
      effect_unfreeze();
      return timeleft;
    }
  }
  effect_unfreeze();
  return -1;
}
varargs int expected_ee( string func_name, int enum ) {
  int timeleft = 0;
  if( undefinedp( enum ) ) {
    enum = _data->current_enum;
  }
  if( !enum ) {
    return -1;
  }
  if( !stringp( func_name ) ) {
    return -1;
  }
  if( !sizeof( eeq ) ) {
    return -1;
  }
  effect_freeze();
  for( int i = 0; i < sizeof( eeq ); i++) {
    timeleft += eeq[i]->inctime;
    if( eeq[i]->eff_ob_num == enum &&
        eeq[i]->func == func_name ) {
      effect_unfreeze();
      return timeleft;
    }
  }
  effect_unfreeze();
  return -1;
}
varargs int *all_expected_ees( string func_name, int *enums ) {
  int timeleft = 0;
  int *alltimesleft = ({});
  if( undefinedp( enums ) ) {
    enums = ({ _data->current_enum });
  }
  if( intp( enums ) ) {
    enums = ({ enums });
  }
  if( !enums ) {
    return ({});
  }
  if( !stringp( func_name ) ) {
    return ({});
  }
  if( !sizeof( eeq ) ) {
    return ({});
  }
  effect_freeze();
  for( int i = 0; i < sizeof( eeq ); i++) {
    timeleft += eeq[i]->inctime;
    if( member_array( eeq[i]->eff_ob_num , enums ) != -1 &&
        eeq[i]->func == func_name ) {
      alltimesleft += ({ timeleft });
    }
  }
  effect_unfreeze();
  return alltimesleft;
}
void add_effect(string eff, mixed arg) {
  string shad;
  object ob, effob;
  mixed hbf, res;
  int i;
  int old_current_enum;
  int enum;
#ifdef DEBUG
   if ( logging_effects )
      log_file( "EFFECT_WOBBLE",
               "%d:%s(%d) add_effect:(%s,%O)\n",
               time() % 1000,this_object()->query_name(),current_enum,eff,arg);
#endif
  hbf = (mixed)eff->query_secs_between_hb();
  if (!hbf) {
    hbf = (mixed) eff->query_heart_beat_frequency();
    if (hbf) {
      if (intp(hbf)) hbf *= 60;
    }
  }
  old_current_enum = _data->current_enum;
  effob = find_object(eff);
  if (!effob)
    error("bad effect object");
  for (i=0; i<sizeof(effs); i++) {
    if (effs[i]->ob_name == eff) {
      if (function_exists("merge_effect", effob)) {
        _data->current_enum = i;
        if (hbf) {
          res = (mixed) effob->merge_effect(affected_object(),
                                            effs[i]->arg[1], arg);
          if (res)
            effs[i]->arg[1] = res;
        } else {
          res = (mixed) effob->merge_effect(affected_object(),
                                            effs[i]->arg, arg);
          if (res)
            effs[i]->arg = res;
        }
        _data->current_enum = old_current_enum;
        return ;
      }
    }
  }
  shad = effob->query_shadow_ob();
  if (shad) {
    ob = clone_object(shad);
    if(!ob) {
      error("Failed to clone shadow object " + shad + ".\n");
      _data->shadows += ({ new(class effect_shadow, shad_ob : 0, idnum : _data->next_id) });
    } else {
      _data->shadows += ({ new(class effect_shadow, shad_ob : ob, idnum : _data->next_id) });
      ob->attach_to_player(affected_object(), _data->next_id);
    }
  } else {
    _data->shadows += ({ new(class effect_shadow, shad_ob : 0, idnum : _data->next_id) });
  }
  _data->current_enum = sizeof(effs);
  enum = _data->current_enum;
  if(!effs)
    effs = ({ });
  effs += ({ new(class effect, ob_name : eff, arg : arg) });
  if (function_exists("beginning", effob)) {
    res = (mixed) effob->beginning(affected_object(), arg, _data->next_id);
    if (res) {
      effs[enum]->arg = res;
    }
  }
  _data->next_id++;
  if (hbf) {
    submit_ee("effect_heart_beat", hbf, EE_CONTINUOUS | EE_OLD);
    effs[enum]->arg = ({ 0, effs[<1]->arg, BOGUS_OLD_ARG });
  }
  _data->current_enum = old_current_enum;
}
#define EFF_OB_NAME 0
#define EFF_ARG 1
#define EEQ_INCTIME 0
#define EEQ_FUNC 1
#define EEQ_EFF_OB 2
#define EEQ_INTERVAL 3
#define EEQ_FLAGS 4
#define EEQ_ARGS 5
#define EFF_SIZE 2
#define EEQ_SIZE 5
protected void convert_arrays() {
  int i, neffs, neeq;
  mixed *old;
  if (sizeof(effs) && !classp(effs[0])) {
    old = effs;
    neffs = sizeof(old) / EFF_SIZE;
    effs = allocate(neffs);
    for (i = 0; i < neffs; i++)
      effs[i] = new(class effect,
                    ob_name : old[i*EFF_SIZE+EFF_OB_NAME],
                    arg : old[i*EFF_SIZE+EFF_ARG]);
  }
  if (sizeof(eeq) && !classp(eeq[0])) {
    old = eeq;
    neeq = sizeof(eeq) / EEQ_SIZE;
    eeq = allocate(neeq);
    for (i = 0; i < neeq; i++)
      eeq[i] = new(class effect_event,
                   inctime : old[ i * EEQ_SIZE + EEQ_INCTIME ],
                   func : old[ i * EEQ_SIZE + EEQ_FUNC ],
                   eff_ob_num : old[ i * EEQ_SIZE + EEQ_EFF_OB ],
                   interval : old[ i * EEQ_SIZE + EEQ_INTERVAL ],
                   flags : old[ i * EEQ_SIZE + EEQ_FLAGS ],
                   eff_ev_args : old[ i * EEQ_SIZE + EEQ_ARGS ] );
  }
}
void init_after_save() {
  int i;
  int neffs;
  string shad;
  string effn;
  object ob;
  mixed arg;
  int *ee_exists;
  convert_arrays();
  for( i = 0; i < sizeof( eeq ); i++ ) {
    if( classp( eeq[i] ) && sizeof( eeq[i] ) < 6 ) {
      eeq[i] = new( class effect_event,
                    inctime : eeq[i]->inctime ,
                    func : eeq[i]->func ,
                    eff_ob_num : eeq[i]->eff_ob_num ,
                    interval : eeq[i]->interval ,
                    flags : eeq[i]->flags ,
                    eff_ev_args : 0 );
    }
  }
  neffs = sizeof(effs);
  _data->shadows = allocate(neffs);
  for (i = 0; i < neffs; i++) {
    effn = effs[i]->ob_name;
    _data->shadows[i] = new(class effect_shadow, idnum : _data->next_id);
    if (catch(shad = (string)
              effn->query_shadow_ob())) {
      continue;
    }
    if (shad) {
      ob = clone_object(shad);
      _data->shadows[i]->shad_ob = ob;
      ob->attach_to_player(affected_object(), _data->next_id);
    }
    _data->current_enum = i;
    arg = effs[i]->arg;
    if (pointerp(arg) && sizeof(arg) == 3 && arg[2] == BOGUS_OLD_ARG) {
      arg = arg[1];
    }
    catch(effn->restart(affected_object(), arg, _data->next_id++));
  }
  ee_exists = allocate(sizeof(effs));
  for (i = 0; i < sizeof(eeq); i++) {
    ee_exists[eeq[i]->eff_ob_num] = 1;
  }
  for (i = sizeof(ee_exists) - 1; i >= 0; i--) {
    if (catch(ob = load_object(effs[i]->ob_name)) || !ob) {
      delete_effect(i);
      continue;
    }
    if (!ee_exists[i] && !ob->query_indefinite()) {
      delete_effect(i);
    }
  }
  _data->current_enum = -1;
  effect_unfreeze();
}
int *effects_matching(string eff) {
  int i, neffs;
  int *match;
  string clas;
  object ob;
  match = ({ });
  neffs = sizeof(effs);
  for (i = 0; i < neffs; i++) {
    if (catch(ob = load_object(effs[i]->ob_name)) || !ob) {
      continue;
    }
    clas = (string)ob->query_classification();
    if (!stringp(clas)) {
      continue;
    }
    if (clas[0..strlen(eff)-1] == eff) {
      match += ({ i });
    }
  }
  return match;
}
void delete_effect(int i) {
   int id, j;
   object effect_object, shadow_object;
   string effect_file;
   mixed arg;
#ifdef DEBUG
   if ( logging_effects )
      log_file( "EFFECT_WOBBLE",
               "%d:%s(%d) delete_effect:(%d) sizeof(eeq)=%d\n",time() % 1000,
               this_object()->query_name(),current_enum,i, sizeof(eeq));
#endif
   if ((i < 0) || (i >= sizeof( effs ))) {
      return;
   }
   id = _data->shadows[i]->idnum;
   arg = effs[i]->arg;
   effect_freeze();
   for (j = 0; j < sizeof(eeq); j++) {
      if (eeq[j]->eff_ob_num == i) {
         if (sizeof(eeq)-1 > j)
            eeq[j+1]->inctime += eeq[j]->inctime;
         eeq = delete(eeq, j--, 1);
      } else {
         if (eeq[j]->eff_ob_num > i)
            eeq[j]->eff_ob_num--;
      }
   }
   effect_file = effs[i]->ob_name;
   effs = delete(effs, i, 1);
   shadow_object = _data->shadows[i]->shad_ob;
   _data->shadows = delete(_data->shadows, i, 1);
   effect_unfreeze();
#ifdef DEBUG
   if ( logging_effects )
      log_file( "EFFECT_WOBBLE",
               "%d:%s(%d) delete_effect: before end\n",time() % 1000,
               this_object()->query_name(),current_enum);
#endif
   effect_object = find_object(effect_file);
   if (!effect_object)
      catch(effect_object = load_object(effect_file));
   if (effect_object)
      if (pointerp(arg) && (sizeof(arg) == 3) &&
          (arg[2] == BOGUS_OLD_ARG))
         effect_object->end(affected_object(), arg[1], id);
   else
      effect_object->end(affected_object(), arg, id);
#ifdef DEBUG
   if ( logging_effects )
      log_file( "EFFECT_WOBBLE",
               "%d:%s(%d) delete_effect: after end\n",time() % 1000,
               this_object()->query_name(),_data->current_enum);
#endif
   if (objectp(shadow_object))
      shadow_object->remove_effect_shadow(id);
}
int sid_to_enum(int sid) {
   return member_array(1,
      map(_data->shadows, (: classp($1) &&
                      ((class effect_shadow)$1)->idnum == $(sid) :)));
}
int enum_to_sid(int enum) {
  return _data->shadows[enum]->idnum;
}
string eff_of(int enum) {
  return effs[enum]->ob_name;
}
mixed arg_of(int enum) {
  mixed arg;
  if (sizeof(effs) <= enum)
    return 0;
  arg = effs[enum]->arg;
  if (arrayp(arg) && sizeof(arg) == 3)
    if (arg[2] == BOGUS_OLD_ARG)
      return copy(arg[1]);
  return copy(arg);
}
void set_arg_of(int enum, mixed newarg) {
  effs[enum]->arg = newarg;
}
class effect *query_effs() { return effs; }
class effect_shadow *query_effect_shadows() { return _data->shadows; }
class effect_event *query_eeq() { return eeq; }
void effect_timer() {
   int enum;
   object effect_object;
   mixed res, last_flags;
   class effect_event thisee;
#ifdef DEBUG
   if ( logging_effects )
      log_file( "EFFECT_WOBBLE",
               "%d:%s(%d) effect_timer:() sizeof(eeq)=%d\n",time() % 1000,
               this_object()->query_name(),current_enum,sizeof(eeq));
#endif
   _data->next_event_time = 0;
   if (!sizeof(eeq)) {
      return;
   }
   thisee = eeq[0];
   eeq = eeq[1..];
   enum = _data->current_enum = thisee->eff_ob_num;
   if (enum >= sizeof(effs)) {
      effect_unfreeze();
      if (this_object()->query_creator()) {
         tell_object(this_object(), "Effect number out of range, "
                     "ignoring.\n");
      }
      return;
   }
   if (thisee->flags & EE_CANCELLED) {
      effect_unfreeze();
      return;
   }
   if (thisee->flags & EE_CONTINUOUS) {
      last_flags = int_submit_ee(enum, thisee->func, thisee->interval,
                                 thisee->flags, thisee->eff_ev_args );
   }
   effect_unfreeze();
   effect_object = find_object(effs[enum]->ob_name);
   if (!effect_object) {
      catch {
         effect_object = load_object(effs[enum]->ob_name);
      };
   }
   if (!effect_object) {
      if (this_object()->query_creator() ) {
         tell_object( this_object(), "Non-existent effect "+
                     effs[enum]->ob_name +", deleting.\n" );
      }
      delete_effect(enum);
      _data->current_enum = -1;
      return;
   }
   if (thisee->flags & EE_OLD) {
      res = (mixed)effect_object->
         effect_heart_beat(this_object(), ++effs[enum]->arg[0],
                           effs[enum]->arg[1], _data->shadows[enum]->idnum);
      if (res == REMOVE_THIS_EFFECT) {
         delete_effect(enum);
      } else {
         effs[enum]->arg[1] = res;
      }
   } else {
      if (stringp(thisee->func)) {
         res = call_other(effect_object, thisee->func, affected_object(),
                          effs[enum]->arg, _data->shadows[enum]->idnum, enum,
                          thisee->eff_ev_args );
         if (res == REMOVE_THIS_EFFECT) {
            delete_effect(enum);
         } else {
            if (res == CANCEL_THIS_EE) {
               eeq[last_flags]->flags |= EE_CANCELLED;
            }
         }
      } else if (functionp(thisee->func)) {
         res = evaluate(thisee->func, affected_object(), effs[enum]->arg,
                     _data->shadows[enum]->idnum, enum, thisee->eff_ev_args );
         if (res == REMOVE_THIS_EFFECT) {
            delete_effect(enum);
         } else if (res == CANCEL_THIS_EE) {
               eeq[last_flags]->flags |= EE_CANCELLED;
         }
      }
   }
   if (thisee->flags & EE_REMOVE)
      delete_effect(enum);
   _data->current_enum = -1;
}
mixed *stats() {
   mixed *sr;
   int i;
   object ob;
   sr = ({ });
   for (i = 0; i < sizeof(effs); i++) {
      if (catch(ob = load_object(effs[i]->ob_name)) || !ob) {
         sr += ({ ({ "effect#" + i, " (buggered)" }) });
         continue;
      }
      if (intp(effs[i]->arg) || stringp(effs[i]->arg)) {
         sr += ({ ({ "effect#" + i,
                       effs[i]->ob_name->query_classification() +
                       " (" + effs[i]->ob_name + ") (" +
                       effs[i]->arg + ")" }) });
      } else {
         sr += ({ ({ "effect#"+i, effs[i]->ob_name->query_classification() +
               " (complex)" }) });
      }
   }
   return sr;
}
void effects_thru_death() {
   int i;
   int id;
   object ob;
   i = sizeof( effs );
   while ( i-- ) {
      id = _data->shadows[i]->idnum;
      if ( catch( ob = load_object(effs[i]->ob_name)) || !ob ||
          !ob->survive_death( affected_object(), effs[i]->arg, id) ) {
         delete_effect(i);
      }
   }
}
int query_current_effect_enum() {
   return _data->current_enum;
}
protected void set_effs( mixed *args ) {
  int i, neffs;
  if ( sizeof( args ) && !classp( args[ 0 ] ) ) {
    neffs = sizeof( args ) / EFF_SIZE;
    effs = allocate( neffs );
    for (i = 0; i < neffs; i++) {
      effs[ i ] = new( class effect,
                       ob_name : args[ i * EFF_SIZE + EFF_OB_NAME ],
                       arg : args[ i * EFF_SIZE + EFF_ARG ] );
    }
  } else {
    effs = args;
  }
}
protected void set_eeq( mixed *args ) {
  int i, neeq;
  if ( sizeof( args ) && !classp( args[ 0 ] ) ) {
    neeq = sizeof( args ) / EEQ_SIZE;
    eeq = allocate( neeq );
    for (i = 0; i < neeq; i++) {
      eeq[ i ] = new( class effect_event,
                      inctime : args[ i * EEQ_SIZE + EEQ_INCTIME ],
                      func : args[ i * EEQ_SIZE + EEQ_FUNC ],
                      eff_ob_num : args[ i * EEQ_SIZE + EEQ_EFF_OB ],
                      interval : args[ i * EEQ_SIZE + EEQ_INTERVAL ],
                      flags : args[ i * EEQ_SIZE + EEQ_FLAGS ],
                      eff_ev_args : args[ i * EEQ_SIZE + EEQ_ARGS ] );
    }
  } else {
    eeq = args;
  }
}