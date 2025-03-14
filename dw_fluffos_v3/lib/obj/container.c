#include "move_failures.h"
#include "parse_command.h"
#include "potion_attrs.h"
inherit "/std/container";
inherit "/std/basic/close_lock_container";
#define MAX_INVENT 40
nosave int full_weight, leak_rate, hb_count;
mixed *misc_attrs;
nosave mixed *all_attrs;
nosave mixed *active_attrs;
int volume, max_volume;
int water;
int *ps_coord;
int ps_quantity;
nosave mixed *potion_id, *potion_adjective;
nosave int volume_to_womble;
void set_volume_to_womble(int n) { volume_to_womble = n; }
int query_volume_to_womble() { return volume_to_womble; }
void set_full_weight(int i) { full_weight = i; }
void set_leak_rate(int i) { leak_rate = i; }
int query_full_weight() { return full_weight; }
int query_leak_rate() { return leak_rate; }
int query_volume() { return volume; }
void set_volume(int i) {
   volume = i;
   if (leak_rate) {
      set_heart_beat(1);
   }
}
int query_max_volume() { return max_volume; }
int *query_ps_coord() { return ps_coord; }
int query_ps_quantity() { return ps_quantity; }
void set_ps_quantity(int n) { ps_quantity = n; }
int *query_all_attrs() { return all_attrs; }
int *query_misc_attrs() { return misc_attrs; }
int *query_active_attrs() { return active_attrs; }
void set_water_volume(int n) { water = n; if (leak_rate) set_heart_beat(1); }
int query_water_volume() { return water; }
void set_max_weight(int i) {
  if (!max_volume && i) {
    max_volume = i*10;
  }
  ::set_max_weight(i);
}
void set_max_volume(int i) {
  if (!query_max_weight() && i) {
    ::set_max_weight(i/10);
  }
  max_volume = i;
}
int empty_formula() {
   int vol_lost;
   vol_lost = 2 + volume * 95 / 100;
   if (vol_lost > volume) vol_lost = volume;
   return vol_lost;
}
int cull_neutral_obs( mixed ob ) {
   if ( ob->query_vect() ) {
     return 1;
   }
   return 0;
}
int *contents_vect() {
   object *inv;
   int *v;
   int ang, str, tot, i;
   inv = all_inventory(this_object());
   inv = filter_array(inv, "cull_neutral_obs", this_object());
   if (sizeof(inv) == 0) return ({ 0, 0, 0 });
   tot = ang = str = 0;
   for (i = 0; i < sizeof(inv); i++) {
      v = inv[i]->query_vect();
      tot += v[0];
      ang += v[1] * v[0];
      str += v[2] * v[0];
   }
   return ({ ang / tot, str / tot, tot });
}
int dest_active_contents() {
   object *inv;
   int i;
   inv = all_inventory(this_object());
   inv = filter_array(inv, "cull_neutral_obs", this_object());
   for (i = 0; i < sizeof(inv); i++) {
      inv[i]->dest_me();
   }
   return sizeof(inv);
}
int *squidge_vector(int *v, int meth_ang, int meth_mult) {
   int ca, cb;
   int da, cx, cy;
   object trig;
   "/obj/handlers/trig"->wibble_wobble();
   trig = find_object("/obj/handlers/trig");
   da = meth_ang - v[0];
   ca = v[1] * trig->cos(da);
   cb = v[1] * trig->sin(da);
   ca = ca * meth_mult;
   cb /= meth_mult;
   ca /= 1000000;
   cb /= 1000000;
   cx = ca * trig->cos(meth_ang) + cb * trig->sin(meth_ang);
   cy = ca * trig->sin(meth_ang) - cb * trig->cos(meth_ang);
   return ({ cx / 1000000, cy / 1000000 });
}
void set_ps_coord_quantity(int *coord, int quantity);
void add_ps_vect(int *v, int quant) {
   object trig;
   int ca, cb;
   if (quant <= 0) return;
   trig = find_object("/obj/handlers/trig");
   ca = v[0];  cb = v[1];
    ca = (int)trig->pow1_5(ps_coord[0] * 10 * ps_quantity /(ca * quant)) * ca / 1000000;
   cb = (int)trig->pow1_5(ps_coord[1] * 10 * ps_quantity /(cb * quant)) * cb / 1000000;
   set_ps_coord_quantity( ({ ps_coord[0] + ca, ps_coord[1] + cb }),
                          quant + ps_quantity);
   return;
}
string transparency_string(int trans)
{
   switch (trans) {
   case -10..9: return "opaque";
   case 10..24: return "milky";
   case 25..39: return "murky";
   case 40..59: return "cloudy";
   case 60..74: return "misty";
   case 75..89: return "slightly misty";
   case 90..110: return "clear";
   default: return "paisley";
   }
}
string consistency_string(int cons)
{
   switch (cons) {
   case -10..9: return "watery liquid";
   case 10..24: return "slightly viscous watery liquid";
   case 25..39: return "runny syrup";
   case 40..59: return "syrup";
   case 60..74: return "jelly";
   case 75..89: return "paste";
   case 90..110: return "solid";
   default: return "non-Newtonian fluid";
   }
}
void update_potion_parse()
{
   int i;
   string *exploded;
   potion_adjective = query_adjectives() +
                  ({ transparency_string(all_attrs[POTION_TRANSPARENCY]) });
   potion_id = ({ query_name() }) + query_alias() +
                  ({ consistency_string(all_attrs[POTION_CONSISTENCY]) });
   for (i = 0; i < sizeof(all_attrs[POTION_NAMES]); i++) {
      exploded = explode(all_attrs[POTION_NAMES][i][0], " ");
      potion_id += ({ exploded[sizeof(exploded) - 1] });
      if (sizeof(exploded) > 1) {
         potion_adjective += exploded[0..sizeof(exploded) - 2];
      }
   }
   for (i = 0; i < sizeof(all_attrs[POTION_COLOURS]); i++)
      potion_adjective += explode(all_attrs[POTION_COLOURS][i][0], " ");
}
void void_liquid()
{
   volume = 0;
   water = 0;
   misc_attrs = allocate(POTION_ATTRS_SIZE);
   misc_attrs[POTION_CONSISTENCY] = 0;
   misc_attrs[POTION_TRANSPARENCY] = 100;
   misc_attrs[POTION_NAMES] = ({ });
   misc_attrs[POTION_COLOURS] = ({ });
   misc_attrs[POTION_SMELLS] = ({ });
   misc_attrs[POTION_FLAVOURS] = ({ });
   ps_coord = (int *)POTION_SPACE_HANDLER->neutral_coordinate();
   ps_quantity = 0;
   active_attrs = all_attrs = misc_attrs;
   update_potion_parse();
}
void create() {
  do_setup++;
  container::create();
  close_lock_container::create();
  set_can_export_inventory();
  do_setup--;
  void_liquid();
  add_property("liquid", 1);
  add_property("watertight", 1);
  leak_rate = 1000;
  if ( !do_setup )
    this_object()->setup();
}
void init() {
  (void)this_player()->add_command("drink", this_object());
  (void)this_player()->add_command("splash", this_object(), "<direct:object> <preposition> <indirect:object>");
  (void)this_player()->add_command("rub", this_object(), "<direct:object> <preposition> <indirect:object>");
  (void)this_player()->add_command("apply", this_object(), "<direct:object> <preposition> <indirect:object>");
  (void)this_player()->add_command("pour", this_object(), "<direct:object> <preposition> <indirect:object>");
  (void)this_player()->add_command("taste", this_object());
  (void)this_player()->add_command("smell", this_object());
  this_player()->add_command("fill", this_object(), "<indirect:object> <preposition> <direct:object>");
  this_player()->add_command("fill", this_object(), "<indirect:object> <fraction> up <preposition> <direct:object>");
  this_player()->add_command("fill", this_object(), "<indirect:object> <fraction> full <preposition> <direct:object>");
  (void)this_player()->add_command("empty", this_object());
  close_lock_container::init();
}
int query_complete_weight() {
  return ::query_complete_weight() + ( query_max_weight() * volume ) /
      ( max_volume + 1 );
}
int query_weight_left() {
  if (!max_volume)
    return query_max_weight() - query_loc_weight();
  return query_max_weight() - query_loc_weight() - (query_max_weight()*volume)/max_volume;
}
int query_volume_left() {
  if (!query_max_weight())
    return max_volume - volume;
  return max_volume - volume - (max_volume*query_loc_weight())/query_max_weight();
}
int add_weight( int n ) {
  if ( query_weight_left() < n ) return 0;
  if ( !( ::add_weight( n ) ) ) return 0;
  if ( n >= 0 ) {
    remove_call_out( "check_breakages" );
    call_out( "check_breakages", 5 + random( 16 ) );
  }
  return 1;
#ifdef BREAK_NOW
  obs = all_inventory();
  for (i=0;i<sizeof(obs);i++)
    if ((amt = obs[i]->query_property("fragile"))) {
      if (query_loc_weight() <= amt || ((query_loc_weight() - amt)*100)/amt <= random(100))
          obs[i] = 0;
    } else
      obs[i] = 0;
  obs = obs - ({ 0 });
  if (sizeof(obs)) {
    say(this_player()->one_short()+" breaks "+
          (sizeof(obs)>1?"some things":"one thing")+" in "+
          query_multiple_short(({ this_object() }))+".\n");
    write("You break "+query_multiple_short(obs)+" in "+
          query_multiple_short(({ this_object() }))+".\n");
    obs->dest_me();
  }
  return 1;
#endif
}
void check_breakages() {
  object *obs, carrier;
  int i, amt, wt;
  carrier = environment(this_object());
  while (carrier && (!living(carrier))) {
    carrier = environment(carrier);
  }
  if (!carrier)
    return;
  obs = all_inventory();
  wt = query_loc_weight() - (int)query_property("padded");
  for (i=0;i<sizeof(obs);i++) {
    if ((amt = obs[i]->query_property("fragile"))) {
      if (wt <= amt || ((wt - amt)*100)/amt <= random(100)) {
          obs[i] = 0;
      }
    } else {
      obs[i] = 0;
    }
  }
  obs = obs - ({ 0 });
  if (sizeof(obs) && environment(carrier)) {
    tell_room(environment(carrier), carrier->the_short()+" breaks "+
          (sizeof(obs)>1?"some things":"one thing")+" in "+
          query_multiple_short(({ this_object() }))+".\n", ({ carrier }));
    tell_object(carrier, "You break "+query_multiple_short(obs)+" in "+
          query_multiple_short(({ this_object() }))+".\n");
    obs->dest_me();
  }
}
varargs string pretty_short( object thing ) {
   return short_status() + ::pretty_short( thing );
}
varargs string pretty_plural( object thing ) {
   return short_status() + ::pretty_plural( thing );
}
string liquid_name()
{
   string liq_name;
   mixed *names, *colours;
   string *med, *lo;
   int no_names, no_colours, i;
   names = all_attrs[POTION_NAMES];
   colours = all_attrs[POTION_COLOURS];
   no_names = (sizeof(names) < 1 || names[0][1] < VERY_SMALL_AMOUNT);
   no_colours = (sizeof(colours) < 1 || colours[0][1] < VERY_SMALL_AMOUNT);
   if (no_names && no_colours) {
      liq_name = "a colourless " +
         transparency_string(all_attrs[POTION_TRANSPARENCY]) + " " +
         consistency_string(all_attrs[POTION_CONSISTENCY]);
   } else if (no_names) {
      if (colours[0][1] < SMALL_AMOUNT) {
         liq_name = "a faint " + colours[0][0];
      } else {
         liq_name = add_a(colours[0][0]);
      }
      liq_name += " " + transparency_string(all_attrs[POTION_TRANSPARENCY]) +
                     " " + consistency_string(all_attrs[POTION_CONSISTENCY]);
      med = ({ });
      i = 1;
      while (i < sizeof(colours) && colours[i][1] >= SMALL_AMOUNT)
         med += ({ colours[i++][0] });
      lo = ({ });
      while (i < sizeof(colours) && colours[i][1] >= VERY_SMALL_AMOUNT)
         lo += ({ colours[i++][0] });
      if (sizeof(med)) {
         liq_name += " with swirls of " + query_multiple_short(med);
      }
      if (sizeof(lo)) {
         if (sizeof(med)) liq_name += " and faint streaks of " + query_multiple_short(lo);
         else liq_name += " with faint streaks of " + query_multiple_short(lo);
      }
   } else if (no_colours) {
      i = 0;
      med = ({ });
      lo = ({ });
      while (i < sizeof(names) && names[i][1] >= SMALL_AMOUNT)
         med += ({ names[i++][0] });
      while (i < sizeof(names) && names[i][1] >= VERY_SMALL_AMOUNT)
         lo += ({ names[i++][0] });
      if (sizeof(med) > 1) liq_name = "a mixture of " + query_multiple_short(med);
      else if (sizeof(med) == 1) liq_name = med[0];
      if (!sizeof(med) && sizeof(lo) > 1)
         liq_name = "a diluted mixture of " + query_multiple_short(lo);
      else if (!sizeof(med) && sizeof(lo) == 1)
         liq_name = "diluted " + lo[0];
      else if (sizeof(med) && sizeof(lo))
         liq_name += "and small quantities of " + query_multiple_short(lo);
   } else {
      if (names[0][1] > colours[0][1] / 2)
      {
         i = 0;
         med = ({ });
         lo = ({ });
         while (i < sizeof(names) && names[i][1] >= SMALL_AMOUNT)
            med += ({ names[i++][0] });
         while (i < sizeof(names) && names[i][1] >= VERY_SMALL_AMOUNT)
            lo += ({ names[i++][0] });
         if (sizeof(med) > 1) liq_name = "a mixture of " + query_multiple_short(med);
         else if (sizeof(med) == 1) liq_name = med[0];
         if (!sizeof(med) && sizeof(lo) > 1)
            liq_name = "a diluted mixture of " + query_multiple_short(lo);
         else if (!sizeof(med) && sizeof(lo) == 1)
            liq_name = "diluted " + lo[0];
         else if (sizeof(med) && sizeof(lo))
            liq_name += "and small quantities of " + query_multiple_short(lo);
         if (colours[0][1] < SMALL_AMOUNT) liq_name += " (a faint " + colours[0][0];
         else liq_name += " (" + add_a(colours[0][0]);
         liq_name += " " + transparency_string(all_attrs[POTION_TRANSPARENCY]) +
                        " " + consistency_string(all_attrs[POTION_CONSISTENCY]);
         med = ({ });
         i = 1;
         while (i < sizeof(colours) && colours[i][1] >= SMALL_AMOUNT)
            med += ({ colours[i++][0] });
         lo = ({ });
         while (i < sizeof(colours) && colours[i][1] >= VERY_SMALL_AMOUNT)
            lo += ({ colours[i++][0] });
         if (sizeof(med)) {
            liq_name += " with swirls of " + query_multiple_short(med);
         }
         if (sizeof(lo)) {
            if (sizeof(med)) liq_name += " and faint streaks of " + query_multiple_short(lo);
            else liq_name += " with faint streaks of " + query_multiple_short(lo);
         }
         liq_name += ")";
      } else {
         if (colours[0][1] < SMALL_AMOUNT) liq_name = "a faint " + colours[0][0];
         else liq_name = add_a(colours[0][0]);
         liq_name += " " + transparency_string(all_attrs[POTION_TRANSPARENCY]) +
                        " " + consistency_string(all_attrs[POTION_CONSISTENCY]);
         med = ({ });
         i = 0;
         while (i < sizeof(names) && names[i][1] >= VERY_SMALL_AMOUNT)
            med += ({ names[i++][0] });
         liq_name += " containing " + query_multiple_short(med);
         med = ({ });
         i = 1;
         while (i < sizeof(colours) && colours[i][1] >= SMALL_AMOUNT)
            med += ({ colours[i++][0] });
         lo = ({ });
         while (i < sizeof(colours) && colours[i][1] >= VERY_SMALL_AMOUNT)
            lo += ({ colours[i++][0] });
         if (sizeof(med)) {
            liq_name += " with swirls of " + query_multiple_short(med);
         }
         if (sizeof(lo)) {
            if (sizeof(med)) liq_name += " and faint streaks of " + query_multiple_short(lo);
            else liq_name += " with faint streaks of " + query_multiple_short(lo);
         }
      }
   }
   return liq_name;
}
string query_liquid_short()
{
   if (sizeof(all_attrs[POTION_NAMES]) && sizeof(all_attrs[POTION_COLOURS])) {
      if (all_attrs[POTION_NAMES][0][1] > all_attrs[POTION_COLOURS][0][1] / 2) {
         return all_attrs[POTION_NAMES][0][0];
      }
   }
   return (sizeof(all_attrs[POTION_COLOURS]) ?
           all_attrs[POTION_COLOURS][0][0] : "colourless") + " " +
             transparency_string(all_attrs[POTION_TRANSPARENCY]) + " " +
             consistency_string(all_attrs[POTION_CONSISTENCY]);
}
string long(string str, int dark) {
  string ret;
  int bing;
  ret = ::long(str, dark);
  if (query_transparent() ||
      !query_closed()) {
    if ( ( dark == 2 ) || ( dark == -2 ) ) {
       if (query_contents() != "") {
          ret += "The "+ short( dark ) +" contains some items you cannot "
                 "make out.\n";
       }
    } else {
       ret += query_contents( "The "+ short( dark ) +" contains:\n" );
    }
  }
  ret += long_status();
  if ((query_transparent() || !query_closed()) && volume) {
    if ( ( dark == 2 ) || ( dark == -2 ) ) {
      ret += "It has some liquid of some sort in it.\n";
    } else {
      bing = (volume*8 + max_volume/16)/max_volume;
      if (bing <= 0) {
        ret += "It is slightly wet from "+liquid_name()+".\n";
      } else if (bing >= 8) {
        ret += "It is full to the brim with " + liquid_name()+".\n";
      } else {
        ret += "It is " + ({ "an eighth", "a quarter",
                "three eighths", "half", "five eighths", "three quarters",
                "seven eighths" })[bing-1]+" full of "+liquid_name()+".\n";
      }
    }
  }
  return ret;
}
string *fullness_adjectives()
{
   if (!max_volume) {
      return ({ "totally", "empty" });
   }
   switch (100 * volume / max_volume) {
   case 0..4: return ({ "totally", "empty" });
   case 5..13: return ({ "empty" });
   case 65..94: return ({ "full" });
   case 95..100: return ({ "totally", "full" });
   default: return ({ });
   }
}
string *parse_command_id_list() {
  return potion_id + ::parse_command_id_list();
}
string *parse_command_adjectiv_id_list() {
  return  fullness_adjectives() + potion_adjective + ::parse_command_adjectiv_id_list();
}
int sort_func(int *x, int *y)
{
   if (x[1] < y[1]) return 1;
   else return 0;
}
mixed *mix_liq(mixed *arr1, mixed *arr2, int vol1, int vol2, int tot_vol)
{
   int i, j;
   mixed *arr3;
   arr3 = allocate(sizeof(arr1));
   for (i = 0; i < sizeof(arr1); i++) {
      arr3[i] = ({ arr1[i][0], arr1[i][1] * vol1 / tot_vol });
      for (j = 0; j < sizeof(arr2); j++) {
         if (arr2[j][0] == arr1[i][0]) {
            arr3[i][1] += arr2[j][1] * vol2 / tot_vol;
            arr2[j][1] += 100000;
            break;
         }
      }
   }
   for (i = 0; i < sizeof(arr2); i++) {
      if (arr2[i][1] >= 100000) {
         arr2[i][1] -= 100000;
      } else {
         arr3 += ({ ({ arr2[i][0], arr2[i][1] * vol2 / tot_vol }) });
      }
   }
   arr3 = sort_array(arr3, "sort_func", this_object());
   for (i = sizeof(arr3) - 1; i >= 0; i--) {
      if (arr3[i][1] > 0) break;
   }
   if (i < 0) arr3 = ({ });
   else arr3 = arr3[0..i];
   return arr3;
}
mixed *merge_potions(mixed *potion1, mixed *potion2, int vol1, int vol2, int tot_vol)
{
   mixed *result;
   result = allocate(POTION_ATTRS_SIZE);
   result[POTION_CONSISTENCY] =
      (potion1[POTION_CONSISTENCY] * vol1 +
       potion2[POTION_CONSISTENCY] * vol2) / tot_vol;
   result[POTION_TRANSPARENCY] =
      (potion1[POTION_TRANSPARENCY] * vol1 +
       potion2[POTION_TRANSPARENCY] * vol2) / tot_vol;
   result[POTION_NAMES] = mix_liq(potion1[POTION_NAMES], potion2[POTION_NAMES],
                                  vol1, vol2, tot_vol);
   result[POTION_COLOURS] = mix_liq(potion1[POTION_COLOURS], potion2[POTION_COLOURS],
                                  vol1, vol2, tot_vol);
   result[POTION_FLAVOURS] = mix_liq(potion1[POTION_FLAVOURS], potion2[POTION_FLAVOURS],
                                  vol1, vol2, tot_vol);
   result[POTION_SMELLS] = mix_liq(potion1[POTION_SMELLS], potion2[POTION_SMELLS],
                                  vol1, vol2, tot_vol);
   return result;
}
void set_misc_attrs(mixed *new_misc_attrs, int misc_vol)
{
   misc_attrs = new_misc_attrs + ({ });
   volume = water + misc_vol;
   all_attrs = merge_potions(active_attrs, misc_attrs, water, volume - water, volume);
   update_potion_parse();
   if (leak_rate) set_heart_beat(1);
}
mixed *change_concentration(mixed *potion, int new_conc)
{
   mixed *newpotion;
   int i;
   newpotion = potion + ({ });
   newpotion[POTION_CONSISTENCY] = newpotion[POTION_CONSISTENCY] * new_conc / 100;
   newpotion[POTION_TRANSPARENCY] =
      (100 - (100 - newpotion[POTION_TRANSPARENCY]) * new_conc / 100);
   for (i = 0; i < sizeof(newpotion[POTION_NAMES]); i++) {
      newpotion[POTION_NAMES][i][1] = newpotion[POTION_NAMES][i][1] * new_conc / 100;
   }
   for (i = 0; i < sizeof(newpotion[POTION_COLOURS]); i++) {
      newpotion[POTION_COLOURS][i][1] = newpotion[POTION_COLOURS][i][1] * new_conc / 100;
   }
   for (i = 0; i < sizeof(newpotion[POTION_SMELLS]); i++) {
      newpotion[POTION_SMELLS][i][1] = newpotion[POTION_SMELLS][i][1] * new_conc / 100;
   }
   for (i = 0; i < sizeof(newpotion[POTION_FLAVOURS]); i++) {
      newpotion[POTION_FLAVOURS][i][1] = newpotion[POTION_FLAVOURS][i][1] * new_conc / 100;
   }
   return newpotion;
}
void set_ps_coord_quantity(int *new_coord, int new_quantity)
{
   mixed *ps_attrs;
   ps_attrs = (mixed *)POTION_SPACE_HANDLER->query_attrs_at(new_coord);
   active_attrs = change_concentration(ps_attrs, new_quantity * 100 / water);
   ps_quantity = new_quantity;
   ps_coord = new_coord;
   all_attrs = merge_potions(active_attrs, misc_attrs, water, volume - water, volume);
   update_potion_parse();
   (void)POTION_SPACE_HANDLER->potion_create(this_object(), new_coord, new_quantity);
}
void begin_config()
{
   potion_id = allocate(9);
   ps_coord = allocate(9);
}
void config(int vari, mixed cont)
{
   potion_id[vari] = cont;
   ps_coord[vari] = 1;
}
void end_config()
{
   mixed *ps_attrs;
   if (ps_coord[OC_VOL]) {
      volume = potion_id[OC_VOL];
      if (ps_coord[OC_MVOL]) water = volume - potion_id[OC_MVOL];
      else water = potion_id[OC_WVOL];
   } else {
      water = potion_id[OC_WVOL];
      volume = water + potion_id[OC_MVOL];
   }
   leak_rate = potion_id[OC_LEAKRATE];
   if (leak_rate && volume) set_heart_beat(1);
   if (ps_coord[OC_MAXVOL]) max_volume = potion_id[OC_MAXVOL];
   else max_volume = volume;
   ps_quantity = potion_id[OC_PSQUANT];
   if (ps_coord[OC_MISCATTRS]) misc_attrs = potion_id[OC_MISCATTRS];
   else misc_attrs = ({ 0, 100, ({ }), ({ }), ({ }), ({ }) });
   if (ps_coord[OC_PSCOORD]) ps_coord = potion_id[OC_PSCOORD];
   else ps_coord = ({ 0, 0 });
   ps_attrs = (mixed *)POTION_SPACE_HANDLER->query_attrs_at(ps_coord);
   active_attrs = change_concentration(ps_attrs, ps_quantity * 100 / water);
   all_attrs = merge_potions(active_attrs, misc_attrs, water, volume - water, volume);
   update_potion_parse();
   (void)POTION_SPACE_HANDLER->potion_create(this_object(), ps_coord, ps_quantity);
}
mixed stats() {
  return container::stats() + close_lock_container::stats() + ({
    ({ "ps_quantity", query_ps_quantity() }),
   ({ "ps_coord", (pointerp(ps_coord) && sizeof(ps_coord) == 2) ?
      "({ " + ps_coord[0] + ", " + ps_coord[1] + " })" :
      sprintf("%O", ps_coord) }),
    ({ "volume", query_volume() + "" }),
    ({ "max volume", query_max_volume() }),
    ({ "water vol", query_water_volume() }),
    ({ "volume left", query_volume_left() }),
    ({ "weight left", query_weight_left() }),
    ({ "full_weight", query_full_weight(), }),
    ({ "leak_rate", query_leak_rate() + "" }),
  });
}
object query_parse_id(mixed *arr) {
  volume_to_womble = 0;
  return ::query_parse_id(arr);
}
object query_frac_parse_id(mixed *arr) {
  int i;
  volume_to_womble = 0;
  if (arr[P_THING] < 0) {
    arr[P_THING]++;
    if (arr[P_THING] != 0)
      return 0;
    volume_to_womble = volume*arr[P_TOP]/arr[P_BOT];
    call_out("set_volume_to_womble", 0, 0);
    arr[P_THING] = -1784628;
    return this_object();
  }
  if (arr[P_THING] == 0)
    if ((i=(arr[P_MAX_NUM]*arr[P_TOP])/arr[P_BOT]) > arr[P_CUR_NUM]++)
      return this_object();
    else
      if (i+1 == arr[P_CUR_NUM]) {
        volume_to_womble = volume*arr[P_TOP]/arr[P_BOT];
        call_out("set_volume_to_womble", 0, 0);
        return this_object();
      }
  else
    return 0;
  if ((i=(arr[P_THING]*arr[P_TOP])/arr[P_BOT]) > arr[P_CUR_NUM]++)
    return this_object();
  else
    if (i+1 == arr[P_CUR_NUM]) {
      volume_to_womble = volume*arr[P_TOP]/arr[P_BOT];
      call_out("set_volume_to_womble", 0, 0);
      return this_object();
    }
  return 0;
}
int remove_volume(int vol_lost)
{
   int q_lost;
   if (!volume) {
      q_lost = ps_quantity;
      water = 0;
      ps_quantity = 0;
      return q_lost;
   }
   q_lost = ps_quantity * vol_lost / volume;
   water -= water * vol_lost / volume;
   volume -= vol_lost;
   ps_quantity -= q_lost;
   return q_lost;
}
void heart_beat() {
  int lost, off;
   if (leak_rate == 0 || volume <= 0) {
      set_heart_beat(0);
      return;
   }
  if (hb_count--) return ;
  hb_count = 10;
  lost = leak_rate;
  if (lost > volume)
    lost = volume;
  off = lost/100;
  if (off > 10)
    off = 10;
  tell_room(environment(),
            capitalize(query_liquid_short())+({ " drips slowly",
                               " drips",
                               " dribbles",
                               " trickles slowly",
                               " trickles",
                               " trickles rapidly",
                               " pours sluggishly",
                               " pours",
                               " streams",
                               " gushes",
                               " fountains", })[off]+" out of the "+
                                                          short(1)+".\n");
  (void)remove_volume(lost);
  if (!volume) {
    set_heart_beat(0);
    void_liquid();
  }
}
void transfer_liquid_to(object dest, int vol_misc, mixed *misc,
                                     int vol_water, int *coord, int quantity)
{
   mixed *their_attrs;
   int their_vol, their_water, their_quantity, new_quantity, new_misc_vol;
   int *new_coord, *old_coord;
   their_attrs = (mixed *)dest->query_misc_attrs();
   their_vol = (int)dest->query_volume();
   their_water = (int)dest->query_water_volume();
   their_quantity = (int)dest->query_ps_quantity();
   new_quantity = quantity + their_quantity;
   if (!their_attrs)
      return ;
   new_misc_vol = vol_misc + their_vol - their_water;
   (void)dest->set_water_volume(their_water + vol_water);
   if (new_misc_vol) {
      their_attrs = merge_potions(misc_attrs, their_attrs,
                               vol_misc, their_vol - their_water,
                               new_misc_vol);
      (void)dest->set_misc_attrs(their_attrs, new_misc_vol);
   } else
      (void)dest->set_volume(their_water + vol_water);
   old_coord = (int *)dest->query_ps_coord();
   new_coord = allocate(2);
   if (pointerp(ps_coord) && new_quantity) {
      new_coord[0] = (ps_coord[0] * quantity + old_coord[0] * their_quantity) /
                     new_quantity;
      new_coord[1] = (ps_coord[1] * quantity + old_coord[1] * their_quantity) /
                     new_quantity;
      dest->set_ps_coord_quantity(new_coord, new_quantity);
   }
}
int ensure_open()
{
   if (query_locked()) {
      write("The " + short(1) + " is locked.\n");
      return 0;
   }
   if (query_closed())
      if (do_open()) {
         write("You open the "+short(1)+".\n");
         return 1;
      } else {
         write("You can't open the " + short(1) + ".\n");
         return 0;
      }
   return 1;
}
int do_pour(object *dest, string me, string him, string prep)
{
   int amount_poured, volume_transferred, old_water, old_volume;
   string liquid_desc;
   if (sizeof(dest) > 1) {
      write("Currently you can only pour into one object\n");
      return 0;
   }
   if (!ensure_open()) return 0;
   if (volume <= 0) {
      write("The " + short(0) + " you are trying to pour out of is empty.\n");
      return 0;
   }
   old_water = water;
   old_volume = volume;
   liquid_desc = query_liquid_short();
   if (volume_to_womble && volume_to_womble <= empty_formula())
      volume_transferred = volume_to_womble;
   else
      volume_transferred = empty_formula();
   amount_poured = remove_volume(volume_transferred);
   if (volume_transferred > dest[0]->query_volume_left()) {
      say(this_player()->short(0) + " attempts to pour from " + add_a(short(0))
         + " into " + add_a(dest[0]->short(0)) + " but ends up spilling "
         + liquid_desc + " all over the ground.\n");
      write(capitalize(liquid_desc) + " spills on the floor as you try to pour "
         + "from the " + short(0) + " into the " + dest[0]->short(0) + ".\n");
      amount_poured = (amount_poured * ((int)dest[0]->query_volume_left())) /
                         volume_transferred;
      volume_transferred = (int)dest[0]->query_volume_left();
   }
   transfer_liquid_to(dest[0], volume_transferred * (old_volume - old_water) / old_volume,
      misc_attrs, volume_transferred * old_water / old_volume, ps_coord, amount_poured);
   this_player()->add_succeeded(dest[0]);
   return 1;
}
int do_fill(object *to, mixed *args_b, mixed *args_a, mixed *args) {
   int m, n, i, run_out, volume_needed, their_volume, their_max,
       amount_poured, ok;
   if (intp(args[1]) && intp(args[2])) {
      m = args[0];
      n = args[1];
      if (m > n || m < 0 || n <= 0) {
         notify_fail("Interesting fraction you have there!\n");
         return 0;
      }
   } else {
      m = 1;
      n = 1;
   }
   if (query_locked()) {
      notify_fail("The " + short(0) + " is locked!\n");
      return 0;
   }
   if (query_closed()) {
      if (do_open()) {
         write("You open the " + short(0) + ".\n");
      } else {
         write("You cannot open the " + short(0) + ".\n");
         return 0;
      }
   }
   if (volume <= 0) {
      write("The " + short(0) + " is bone dry!\n");
      return 0;
   }
   run_out = 0;
   for (i = 0; i < sizeof(to) && !run_out; i++) {
      their_volume = (int)to[i]->query_volume();
      their_max = (int)to[i]->query_max_volume();
      if (their_max <= 0) {
         write("The " + to[i]->short(0) +
               " doesn't look like it can be filled!\n");
         continue;
      }
      if (their_volume >= their_max) {
         write("The " + to[i]->short(0) + " is full to the brim already.\n");
         continue;
      }
      volume_needed = their_max * m / n;
      if (their_volume >= volume_needed) {
         write("The " + to[i]->short(0) + " is more than " + m + "/" + n +
           " full already.\n");
         continue;
      }
      ok++;
      volume_needed -= their_volume;
      if (volume_needed > empty_formula()) {
         write("You drain the " + short(0) + " into the " + to[i]->short(0) +
            " but it is not enough.\n");
         volume_needed = empty_formula();
         run_out = 1;
         this_player()->add_succeeded(to[i]);
      } else {
         this_player()->add_succeeded(to[i]);
      }
      amount_poured = volume_needed * ps_quantity / volume;
      transfer_liquid_to(to[i], volume_needed * (volume - water) / volume,
         misc_attrs, volume_needed * water / volume, ps_coord, amount_poured);
      amount_poured = remove_volume(volume_needed);
   }
   return ok;
}
int do_drink(object *dest, string me, string him, string prep)
{
   int amount_drunk, amount_can_be_drunk;
   if (sizeof(dest)) {
      write("Drinking is a very simple operation - please don't complicate matters.\n");
      return 0;
   }
   if (!ensure_open()) return 0;
   if (volume <= 0) {
      write("The " + short(0) + " is bone dry!\n");
      return 0;
   }
   amount_can_be_drunk = (2000 - (int)this_player()->query_volume(2)) *
      (int)this_player()->query_con() / 12;
   if (!volume_to_womble) volume_to_womble = empty_formula();
   if (volume_to_womble > empty_formula()) volume_to_womble = empty_formula();
   if (volume_to_womble > amount_can_be_drunk) {
      write("You drink some of the liquid, but simply cannot fit it all in.\n");
      volume_to_womble = amount_can_be_drunk;
   }
   amount_drunk = remove_volume(volume_to_womble);
   (void)POTION_SPACE_HANDLER->potion_drunk(this_player(), ps_coord, amount_drunk);
   this_player()->adjust_volume(2, volume_to_womble * 12 /
      (int)this_player()->query_con());
   switch ((this_player()->query_volume(2) + 100) / 200) {
   case 5:
      write("You feel mildly full of liquid.\n");
      break;
   case 6:
      write("You feel very full of liquid.\n");
      break;
   case 7:
      write("You feel pissed.\n");
      break;
   case 8:
      write("You are awash with liquid.\n");
      break;
   case 9:
      write("You are full to the brim with liquid.\n");
      break;
   case 10:
      write("You feel you would burst if you drank any more.\n");
      break;
   }
   return 1;
}
int do_empty(object *dest, string me, string him, string prep)
{
   if (sizeof(dest)) {
      write("Passing on to pour ... bad move.\n");
      return do_pour(dest, me, him, prep);
   }
   if (!ensure_open()) { write("It aint open!\n"); return 0; }
   if (volume == 0) {
      write("The " + short(0) + " is already empty.\n");
      return 0;
   }
   if (volume_to_womble && volume_to_womble <= empty_formula())
      (void)remove_volume(volume_to_womble);
   else
      (void)remove_volume(empty_formula());
   return 1;
}
int do_splash(object *dest, string me, string him, string prep) {
   int amount_splashed;
   if (sizeof(dest) > 1) {
      write("You can only splash one object at a time.\n");
      return 0;
   }
   if (!sizeof(dest))
     return 0;
   if (!ensure_open()) return 0;
   if (volume_to_womble && volume_to_womble <= empty_formula())
      amount_splashed = remove_volume(volume_to_womble);
   else
      amount_splashed = remove_volume(empty_formula());
   (void)POTION_SPACE_HANDLER->potion_touch(dest[0], ps_coord, amount_splashed);
   (void)this_player()->add_succeeded(dest[0]);
   return 1;
}
int do_rub(object *dest, string me, string him, string prep) {
   int amount_rubbed;
   if (sizeof(dest) > 1) {
      write("You can only "+query_verb()+" on to one object at a time.\n");
      return 0;
   }
   if (!sizeof(dest))
     return 0;
   if (environment(dest[0]) != this_player()) {
      write("You can only "+query_verb()+" on to an object in your inventory.\n");
      return 0;
   }
   if (!ensure_open()) return 0;
   if (volume_to_womble && volume_to_womble <= empty_formula())
      amount_rubbed = remove_volume(volume_to_womble);
   else
      amount_rubbed = remove_volume(empty_formula());
   (void)POTION_SPACE_HANDLER->potion_touch(dest[0], ps_coord, amount_rubbed);
   (void)this_player()->add_succeeded(dest[0]);
   return 1;
}
void do_apply(object *dest, string me, string him, string prep ) {
   do_rub( dest, me, him, prep );
}
#define TASTE_AMOUNT 5
int do_taste() {
   int amount_tasted;
   string desc;
   mixed *group;
   int i;
   if (!ensure_open()) return 0;
   if (volume < TASTE_AMOUNT) {
      write("There is no liquid to taste.\n");
      return 0;
   }
   desc = "The " + query_liquid_short();
   if (!sizeof(all_attrs[POTION_FLAVOURS]) ||
     all_attrs[POTION_FLAVOURS][0][1] < VERY_SMALL_AMOUNT)
      desc += " has no discernible flavour";
   else {
      group = ({ });
      for (i = 0; i < sizeof(all_attrs[POTION_FLAVOURS]) &&
           all_attrs[POTION_FLAVOURS][i][1] >= SMALL_AMOUNT; i++)
         group += all_attrs[POTION_FLAVOURS][i][0..0];
      if (sizeof(group)) {
         desc += " tastes of " + query_multiple_short(group);
         if (i < sizeof(all_attrs[POTION_FLAVOURS]) &&
             all_attrs[POTION_FLAVOURS][i][1] >= VERY_SMALL_AMOUNT)
            desc += " with a faint hint of ";
      } else desc += " tastes faintly of ";
      group = ({ });
      for (; i < sizeof(all_attrs[POTION_FLAVOURS]) &&
           all_attrs[POTION_FLAVOURS][i][1] >= VERY_SMALL_AMOUNT; i++)
         group += all_attrs[POTION_FLAVOURS][i][0..0];
      if (sizeof(group)) desc += query_multiple_short(group);
   }
   write(desc + ".\n");
   say(this_player()->one_short() + " takes a small sip from the " +
       short(0) + ".\n");
   amount_tasted = remove_volume(TASTE_AMOUNT);
   (void)POTION_SPACE_HANDLER->potion_drunk(this_player(), ps_coord, TASTE_AMOUNT);
   return 1;
}
int do_smell()
{
   string desc;
   string *group;
   int i;
   if (!ensure_open()) return 0;
   if (volume < 1) {
      write("There is no liquid to smell.\n");
      return 0;
   }
   desc = "The " + query_liquid_short();
   if (!sizeof(all_attrs[POTION_SMELLS]) ||
     all_attrs[POTION_SMELLS][0][1] < VERY_SMALL_AMOUNT)
      desc += " has no distinct aroma";
   else {
      group = ({ });
      for (i = 0; i < sizeof(all_attrs[POTION_SMELLS]) &&
           all_attrs[POTION_SMELLS][i][1] >= SMALL_AMOUNT; i++)
         group += all_attrs[POTION_SMELLS][i][0..0];
      if (sizeof(group)) {
         desc += " smells of " + query_multiple_short(group);
         if (i < sizeof(all_attrs[POTION_SMELLS]) &&
             all_attrs[POTION_SMELLS][i][1] >= VERY_SMALL_AMOUNT)
            desc += " with a faint hint of ";
      } else desc += " smells faintly of ";
      group = ({ });
      for (; i < sizeof(all_attrs[POTION_SMELLS]) &&
           all_attrs[POTION_SMELLS][i][1] >= VERY_SMALL_AMOUNT; i++)
         group += all_attrs[POTION_SMELLS][i][0..0];
      if (sizeof(group)) desc += query_multiple_short(group);
   }
   write(desc + ".\n");
   say(this_player()->one_short() + " takes a whiff of the " +
       short(0) + ".\n");
   (void)POTION_SPACE_HANDLER->potion_smell(this_player(), ps_coord, ps_quantity * 100 / volume);
   return 1;
}
mapping int_query_static_auto_load() {
  mapping tmp;
  tmp = ::int_query_static_auto_load();
  return ([ "::" : tmp,
            "leak rate" : leak_rate,
            "full weight" : full_weight,
            "trans" : query_transparent(),
            "difficulty" : query_difficulty(),
            "key" : query_key(),
            "trap open func" : query_open_trap_func(),
            "trap lock func" : query_lock_trap_func(),
            "trap open ob" : query_open_trap_ob(),
            "trap lock ob" : query_lock_trap_ob(),
            "max volume" : max_volume,
          ]);
}
mapping query_dynamic_auto_load() {
  if (!query_name() || query_name() == "object") {
    return 0;
  }
  return ([
           "::" : ::query_dynamic_auto_load(),
           "locked" : query_locked(),
           "stuck" : query_stuck(),
           "closed" : query_closed(),
           "volume" : volume,
           "water" : water,
           "misc attrs" : misc_attrs,
           "ps coord" : ps_coord,
           "ps quantity" : ps_quantity,
          ]);
}
void init_dynamic_arg(mapping map) {
  mixed *ps_attrs;
  object money;
  if (map["::"])
    ::init_dynamic_arg(map["::"]);
  if (sizeof(map["money"])) {
     money = clone_object("/obj/money");
     money->set_money_array(map["money"]);
     money->move(this_object());
  }
  if (map["locked"]) {
     set_locked();
  } else {
     set_unlocked();
  }
  set_stuck(map["stuck"]);
  if (map["closed"]) {
     set_closed();
  } else {
     set_open();
  }
  volume = map["volume"];
  set_water_volume(map["water"]);
  if (volume == 0) {
    void_liquid();
    update_potion_parse();
    return;
  }
  misc_attrs = map["misc attrs"];
  ps_quantity = map["ps quantity"];
  ps_coord = map["ps coord"];
  ps_attrs = (mixed *)POTION_SPACE_HANDLER->query_attrs_at(ps_coord);
  if(!water) water = 1;
  active_attrs = change_concentration(ps_attrs, ps_quantity * 100 / water);
  all_attrs = merge_potions(active_attrs, misc_attrs, water, volume - water, volume);
  update_potion_parse();
}
void init_static_arg(mapping args) {
  if (args["::"]) {
    ::init_static_arg(args["::"]);
  }
  if (!undefinedp(args["leak rate"])) {
    leak_rate = args["leak rate"];
  }
  if (!undefinedp(args["full weight"])) {
    full_weight = args["full weight"];
  }
  if (!undefinedp(args["trans"])) {
    if (args["trans"]) {
       set_transparent();
    } else {
       set_opaque();
    }
  }
  if (!undefinedp(args["difficulty"])) {
    set_difficulty(args["difficulty"]);
  }
  if (!undefinedp(args["key"])) {
    set_key(args["key"]);
  }
  if (!undefinedp(args["trap open func"])) {
    set_open_trap(args["trap open ob"], args["trap open func"]);
  }
  if (!undefinedp(args["trap lock func"])) {
    set_lock_trap(args["trap lock ob"], args["trap lock func"]);
  }
  if (!undefinedp(args["max volume"])) {
    max_volume = args["max volume"];
  }
}
mixed query_static_auto_load() {
  if (!query_name() || query_name() == "object") return 0;
  if (file_name(this_object())[0..13] == "/obj/container")
    return int_query_static_auto_load();
  return ([ ]);
}
int test_add(object ob, int flag) {
  return !query_closed() && !flag;
}
int can_find_match_recurse_into(object looker) {
   if (query_closed()) {
      return 0;
   }
   return ::can_find_match_recurse_into(looker);
}
int test_remove(object ob, int flag) { return !query_closed(); }
varargs int move(mixed dest, string messin, string messout) {
   int result;
   object from;
   object to;
   from = environment();
   result = ::move(dest, messin, messout);
   if (result == MOVE_OK) {
      to = environment();
      we_moved(from, to);
   }
   return result;
}
void dest_me() {
   close_lock_container::dest_me();
   container::dest_me();
}