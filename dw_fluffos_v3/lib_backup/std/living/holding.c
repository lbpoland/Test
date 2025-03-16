nosave mixed *_using;
nosave mixed *_weapons;
#define START_VALUE "1"
int *set_hold(object ob, int location, int limbs);
int *set_unhold(object ob);
private int sub_hold(object ob, int pos, int first);
void create()
{
   _weapons = ({ });
}
string *query_limbs()
{
   string race_ob;
   string *limbs;
   race_ob = this_object()->query_race_ob();
   if (!race_ob) {
      _using = ({ });
      return ({ });
   }
   limbs = race_ob->query_limbs();
   if (!_using) {
      _using = allocate(sizeof(limbs));
   }
   return limbs;
}
string* query_using_array() {
   return copy(_using);
}
object *query_holding()
{
   if (!arrayp(_using)) {
      query_limbs();
   }
   _using =
      map(_using, (: $1 ? (environment($1) == this_object()? $1 : 0) : 0 :));
   return copy(_using);
}
string* query_holding_limbs(object ob) {
   string* ret;
   int i;
   object* holding;
   string* limbs;
   ret = ({ });
   holding = query_holding();
   limbs = query_limbs();
   for (i = 0; i < sizeof(holding); i++) {
      if (holding[i] == ob) {
         ret += ({ limbs[i] });
      }
   }
   return ret;
}
int query_free_limbs()
{
   if (!arrayp(_using)) {
      query_limbs();
   }
   return
      sizeof(filter(_using, (: !$1 || environment($1) != this_object() :)));
}
object *query_weapons()
{
   return filter(_weapons, (: $1 :));
}
int *set_unhold(object ob)
{
   int *pos;
   if (!objectp(ob)) {
      return ({ });
   }
   if (member_array(ob, _using) == -1) {
      return ({ });
   }
   if (!ob->set_holder(0)) {
      return ({ });
   }
   pos = find_member(ob, _using);
   if (ob->query_weapon()) {
      _weapons = filter(_weapons, (: $1 != $(ob) :));
   }
   if (ob->query_armour()) {
      this_object()->remove_armour(ob);
   }
   _using = map(_using, (: $1 == $(ob) ? 0 : $1 :));
   this_object()->do_burden_call();
   return pos;
}
int *set_hold(object ob, int pos, int limbs)
{
   int limb_count;
   int *free = ({ });
   int *used = ({ });
   int total = 0;
   int temp = 0;
   int ok;
   int failed;
   if (environment(ob) != this_object()) {
      debug_printf("Bad environment");
      return ({ });
   }
   limb_count = sizeof(this_player()->query_limbs());
   if (!arrayp(_using)) {
      query_limbs();
   }
   if (pos == -1) {
      total = ob->query_no_limbs();
      if (total > this_object()->query_free_limbs()) {
         debug_printf("Too many limbs");
         return ({ });
      }
      free = find_member(0, _using);
      if (!sizeof (free)) {
        return ({ });
      }
      pos = free[0];
   }
   if (objectp(_using[pos]) && environment(_using[pos]) == this_object()) {
      return ({ });
   }
   ok = sub_hold(ob, pos, 1);
   if (ok) {
      used += ({ pos });
   } else {
      return ({ });
   }
   if(limbs)
     total = limbs - 1;
   else
     total = ob->query_no_limbs() - 1;
   free = find_member(0, _using);
   temp = 0;
   while (temp < total && temp < sizeof(free)) {
      if (temp > limb_count) {
         set_unhold(ob);
         return ({ });
      }
      sub_hold(ob, free[temp], 0);
      if (ok) {
         used += ({ free[temp] });
         temp++;
      } else {
         failed = 1;
      }
   }
   if (failed) {
      set_unhold(ob);
      return ({ });
   } else {
     this_object()->do_burden_call();
      return used;
   }
}
private int sub_hold(object ob,
                     int pos,
                     int first)
{
   int success;
   if (environment(ob) != this_object()) {
      return 0;
   }
   if (first) {
      success = ob->set_holder(this_object(), pos);
      if (!success) {
         return 0;
      }
   }
   _using[pos] = ob;
   if (ob->query_weapon()) {
      if (member_array(ob, _weapons) == -1) {
         _weapons += ({ ob });
      }
   }
   return 1;
}