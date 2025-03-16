#include "spells.h"
nosave mixed *_spell_effects;
void create() {
  _spell_effects = ({ });
}
mixed query_effects() { return _spell_effects; }
int queue_commands() { return sizeof( _spell_effects ); }
int add_spell_effect(int no_rnds, string type, string name, object callee,
                     string func, mixed params) {
  int i,j;
   if (strsrch(file_name(this_object()),"global")==-1)
      tell_object(find_living("olorin"),
                  sprintf("add_spell_effect in %s\n",
                          file_name(this_object())));
  if ((i=member_array(type, _spell_effects)) != -1)
    if ((j=member_array(name, _spell_effects[i+1])) == -1)
      _spell_effects[i+1] += ({ name, ({ no_rnds, callee, func, params }) });
    else
      _spell_effects[i+1][j+1] = ({ no_rnds, callee, func, params });
  else
    _spell_effects += ({ type, ({ name, ({ no_rnds, callee, func, params }) }) });
}
int remove_spell_effect(string name) {
  int i, j;
   if (strsrch(file_name(this_object()),"global")==-1)
      tell_object(find_living("olorin"),
                  sprintf("remove_spell_effect in %s\n",
                          file_name(this_object())));
  for (i=0;i<sizeof(_spell_effects);i+=2)
    if ((j=member_array(name, _spell_effects[i+1])) != -1) {
      _spell_effects[i+1] = delete(_spell_effects[i+1], j, 2);
      if (!sizeof(_spell_effects[i+1])) {
        _spell_effects = delete(_spell_effects, i, 2);
        i -= 2;
      }
    }
  return 1;
}
mixed query_spell_effect(string name) {
   int i;
   if (strsrch(file_name(this_object()),"global")==-1)
      tell_object(find_living("olorin"),
                  sprintf("query_spell_effect in %s\n",
                          file_name(this_object())));
  if ((i=member_array(name, _spell_effects)) == -1)
    return 0;
  if (sizeof(_spell_effects[i+1]))
    return _spell_effects[i..i]+_spell_effects[0..1];
  return 0;
}
mixed *query_spell_effects_type(string type) {
  int i, j;
  mixed *ret;
  if ((i=member_array(type, _spell_effects)) == -1)
    return ({ });
  ret = ({ });
  for (j=0;j<sizeof(_spell_effects);j+=2)
    ret += ({ _spell_effects[i], _spell_effects[i+1][j..j+1] });
  return ret;
}
int do_spell_effects(object attacker) {
  int i, j;
  this_object()->remove_property("casting");
  for (i=0;i<sizeof(_spell_effects);i+=2)
    for (j=0;j<sizeof(_spell_effects[i+1]);j+=2) {
      call_out("do_call_out_effect", 1, ({ _spell_effects[i+1][j+1], attacker }));
      _spell_effects[i+1][j+1][SP_NO_RNDS]--;
      if ( !_spell_effects[i+1][j+1][SP_NO_RNDS] || !_spell_effects[i+1][j+1][SP_OBJECT]) {
        _spell_effects[i+1] = delete(_spell_effects[i+1], j, 2);
        j -= 2;
        if (!sizeof(_spell_effects[i+1])) {
          _spell_effects = delete(_spell_effects, i, 2);
          i -= 2;
          break;
        }
      }
    }
    return 0;
}
void do_call_out_effect(mixed *params) {
  if (params[0][SP_OBJECT])
    call_other(params[0][SP_OBJECT],
             params[0][SP_FUNC],
             params[1],
             params[0][SP_PARAM],
             params[0][SP_NO_RNDS]);
}