#define REACTION_HANDLER ("/obj/handlers/reaction")
#define TASTE_AMT 200
#include <tasks.h>
#include <move_failures.h>
#include <volumes.h>
inherit "/obj/baggage";
private int leak_rate;
private int hb_count;
private int sub_query_contents;
private int volume;
private int max_volume;
private int cont_volume;
private int is_liquid;
private nosave int* _fraction;
private nosave object* _liquids;
int drink_amount(int drinking, object player);
private int query_fighting(object player);
void set_leak_rate(int i) { leak_rate = i; }
int query_leak_rate() { return leak_rate; }
void set_max_volume(int v) { max_volume = v; }
int query_max_volume() { return max_volume; }
string *leak_verb = ({ " drips slowly",
                       " drips",
                       " dribbles",
                       " trickles slowly",
                       " trickles",
                       " trickles rapidly",
                       " pours sluggishly",
                       " pours",
                       " streams",
                       " gushes",
                       " fountains"
                     });
string *drink_pat = ({ "[from] <direct:object>",
                       "<fraction> {of|from} <direct:object>"
                   });
string *splash_pat = ({ "[from] <direct:object> {on|to|onto} <indirect:living>",
                       "<fraction> {of|from} <direct:object> {on|to|onto} "
                       "<indirect:living>"
                   });
string *apply_pat = ({ "[from] <direct:object> {on|to} <indirect:living>",
                       "<fraction> {of|from} <direct:object> {on|to} "
                       "<indirect:living>"
                   });
string *pour_pat = ({ "<direct:object> {from|into} <indirect:object>",
                      "<fraction> of <direct:object> {from|into} <indirect:object>"
                  });
string *fill_pat = ({ "<indirect:object> <fraction> full {from|into} <direct:object>",
                      "<indirect:object> <fraction> up {from|into} <direct:object>",
                      "<indirect:object> {from|into} <direct:object>"
                  });
void create() {
    do_setup++;
    ::create();
    do_setup--;
    if ( !do_setup ) {
      this_object()->setup();
    }
    add_help_file("vessel");
}
void init() {
    ::init();
    add_command("drink", drink_pat);
    add_command("quaff", drink_pat);
    add_command("splash", splash_pat);
    add_command("rub", apply_pat);
    add_command("apply", apply_pat);
    add_command("pour", pour_pat);
    add_command("taste", "<direct:object>");
    add_command("sip", "<direct:object>");
    add_command("fill", fill_pat);
    add_command("empty", "<direct:object>");
}
string *fullness_adjectives() {
   if (!max_volume) return ({ "totally", "empty" });
   switch (100 * volume / max_volume) {
   case 0..4: return ({ "totally", "empty" });
   case 5..13: return ({ "empty" });
   case 65..94: return ({ "full" });
   case 95..100: return ({ "totally", "full" });
   default: return ({ });
   }
}
mixed stats() {
  return ::stats() + ({
      ({ "leak_rate", leak_rate }),
      ({ "volume", volume }),
      ({ "cont_volume", cont_volume }),
      ({ "liquid", is_liquid }),
      ({ "max_volume", max_volume })
    });
}
int cmp_amount_r(object a, object b) {
    return ((int)b->query_amount() - (int)a->query_amount());
}
int cmp_weight_r(object a, object b) {
    if (a->query_weight() || b->query_weight())
      return ((int)b->query_weight() - (int)a->query_weight());
    return cmp_amount_r(a, b);
}
private void figure_out_liquids() {
   _liquids = filter(all_inventory(this_object()), (: $1->query_liquid() :));
   _liquids = sort_array(_liquids, "cmp_amount_r", this_object());
}
string query_liquid_desc() {
    object *contents, *solids = ({});
    int i;
    string desc, *shorts;
    mixed *others;
    contents = all_inventory(this_object());
    if( !sizeof( contents ) ) {
       return (string) 0;
    }
    figure_out_liquids();
    solids = contents - _liquids;
    if (sizeof(_liquids)) {
       _liquids = sort_array(_liquids, "cmp_amount_r", this_object());
       others = unique_array(_liquids->a_short(),
                          (: "/global/events"->convert_message($1) :));
       shorts = ({ });
       for (i = 0; i < sizeof(others); i++) {
          shorts += ({ others[i][0] });
       }
       desc = shorts[0];
       if (sizeof(shorts) > 1) {
          desc += ", mixed with ";
          if (sizeof(shorts) > 4) {
             desc += "other liquids";
          } else {
             desc += query_multiple_short(shorts[1..]);
          }
       }
    } else {
       desc = "";
    }
    if (!sizeof(solids)) {
        return desc;
    }
    solids = sort_array(solids, "cmp_weight_r", this_object());
    others = unique_array(solids,
                          (: $1->query_continuous()?
                           this_player()->convert_message($1->a_short()) :
                           $1 :) );
    for (i = 0; i < sizeof(others); i++) {
       if( arrayp( others ) ) {
          others[i] = others[i][0];
       } else {
          tell_creator( "gruper", "others is %O.\n", others );
       }
    }
    if (sizeof(_liquids)) {
       desc += ", with ";
    }
    if (sizeof(others) > 10) {
        desc += "various undissolved substances";
    } else {
        desc += query_multiple_short(others);
    }
    if (sizeof(_liquids)) {
       desc += " floating in it";
    }
    return desc;
}
string query_fullness_desc() {
   int full;
   full = (100 * volume) / max_volume;
   if( full < 1 && query_liquid_desc() ) {
      full = 1;
   }
   switch (full) {
      case 0:       return "";
      case 1..12:   return "It is almost empty.";
      case 13..37:  return "It is about one-quarter full.";
      case 38..62:  return "It is about half full.";
      case 63..87:  return "It is about three-quarters full.";
      case 88..95:  return "It is almost full.";
      case 96..100: return "It is completely full.";
      default:      return "Its capacity defies the laws of physics.  "
                           "Please submit a bug report.";
    }
}
varargs string query_contents(string str, object *obs ) {
    string s, c;
    if ( query_liquid_desc() ) {
        c = "\n"+ query_fullness_desc() +"\n";
    } else {
        c = "";
    }
    s = query_liquid_desc();
    if (sub_query_contents) {
        if (s) {
            return str + capitalize(s) + "." + c;
        }
        return ::query_contents(str, obs) + c;
    }
    return ::query_contents(str, obs);
}
string short(int dark) {
  object *inv;
  if(query_opaque())
    return ::short(dark);
  inv = all_inventory(this_object());
  if(!sizeof(inv))
    return ::short(dark);
  return ::short(dark) + " of " +
    "/global/events"->convert_message(query_multiple_short(map(inv,
    (: $1->query_short() :))));
}
string long(string str, int dark) {
    string ret;
    sub_query_contents = 1;
    ret = ::long(str, dark);
    sub_query_contents = 0;
    return ret;
}
int query_cont_volume() { return cont_volume; }
int query_liquid() { return is_liquid; }
void calc_liquid() {
    if (sizeof(filter(all_inventory(), (: $1->query_liquid() :)))) {
      is_liquid = 1;
    } else {
      is_liquid = 0;
    }
}
int query_volume() { return volume; }
int query_volume_left() {
  if (!query_max_weight()) {
    return max_volume - volume;
  }
  return max_volume - volume - (max_volume*query_loc_weight())/query_max_weight();
}
int add_volume(int vol) {
   if ((vol <= 0) || !max_volume || (vol + volume <= max_volume)) {
      volume += vol;
      if (previous_object()->query_continuous()) {
          cont_volume += vol;
      }
      return 1;
    }
    return 0;
}
int add_weight(int n) {
    int v;
    if (this_player() && (this_player()->query_name() == "pinkfish")) {
      tell_creator("pinkfish", "vessel::add_weight(%O)\n", n);
    }
    if (previous_object()->query_continuous()) {
       return (::add_weight(n));
    }
      v = n*200;
    if (max_volume && (v + volume > max_volume)) {
       return 0;
    }
    if (::add_weight(n)) {
        volume += v;
        return 1;
    }
    return 0;
}
int remove_volume(int vol_lost)
{
    int amt_lost, i, orig_cv;
    object *contents;
    if (!cont_volume) {
        return 0;
    }
    orig_cv = cont_volume;
    contents = all_inventory(this_object());
    for (i = 0; i < sizeof(contents); i++) {
        if (contents[i]->query_continuous()) {
            amt_lost = -to_int((int)contents[i]->query_amount()
                               * (to_float(vol_lost) / orig_cv));
            if (!amt_lost) {
                amt_lost++;
            }
            contents[i]->adjust_amount(amt_lost);
        }
    }
    return vol_lost;
}
int xfer_volume(int vol_xferred, object dest) {
    int vol_to_go;
    int i;
    int amt_xferred;
    int tmp;
    int orig_cv;
    object *contents;
    object copy;
    string file_path;
    mapping map;
    vol_to_go = vol_xferred;
    if (!cont_volume) {
        return 0;
    }
    orig_cv = cont_volume;
    contents = filter(all_inventory(this_object()),
                      (: $1->query_continuous() :));
    for (i = 0; i < sizeof(contents) && vol_to_go > 0; i++) {
        if (i == sizeof(contents) - 1) {
            amt_xferred = vol_to_go;
        } else {
            amt_xferred = to_int((int)contents[i]->query_amount()
                                 * (to_float(vol_xferred) / orig_cv));
        }
        if (!amt_xferred) {
            amt_xferred++;
        }
        file_path = explode( file_name(contents[i]), "#" )[ 0 ];
        copy = clone_object(file_path);
        map = (mapping)contents[i]->query_dynamic_auto_load();
        copy->init_dynamic_arg( map );
        map = (mapping)contents[i]->query_static_auto_load();
        if (map) {
            copy->init_static_arg( map );
        }
        copy->set_amount(amt_xferred);
        tmp = copy->move(dest);
        if (tmp == MOVE_OK) {
            vol_to_go -= amt_xferred;
            contents[i]->adjust_amount(-amt_xferred);
        } else {
            copy->dest_me();
        }
    }
    return vol_to_go;
}
void heart_beat() {
    int lost, off;
    if (leak_rate == 0 || !is_liquid) {
        set_heart_beat(0);
        return;
    }
    if (hb_count--) return ;
    hb_count = 10;
    lost = leak_rate;
    if (lost > cont_volume)
      lost = cont_volume;
    off = lost/100;
    if (off > 10)
        off = 10;
    if ( interactive( environment() ) )
        tell_object( environment(), "$C$Some " + query_multiple_short( map( all_inventory(),
        (: $1->query_short() :) ) ) + leak_verb[off] + " out of the "+ short(1) + ".\n" );
    else
      tell_room( environment(), "$C$Some " + query_multiple_short( map( all_inventory(),
        (: $1->query_short() :) ) ) + leak_verb[off] + " out of the "+ short(1) + ".\n" );
  (void)remove_volume(lost);
  if (!cont_volume) {
    set_heart_beat(0);
  }
}
int do_pour(object *to, mixed *args_b, mixed *args_a, mixed *args) {
    int m, n, volume_needed, their_volume, their_max, ovf, xfer_result;
    if (query_fighting(this_player())) {
       add_failed_mess("You cannot attempt to do this while in combat.\n");
       return 0;
    }
    if (environment(this_object()) != this_player()) {
        add_failed_mess("You aren't carrying $D.\n");
        return 0;
    }
    if (sizeof(args) == 5) {
        sscanf(args[0] + " " + args[1], "%d %d", m, n);
        if ((m > n) || (m < 0) || (n <= 0)) {
            add_failed_mess("Interesting fraction you have there!\n");
            return 0;
        }
    } else {
        m = 1;
        n = 1;
    }
    if (query_locked()) {
        add_failed_mess("$C$$D $V$0=is,are$V$ locked!\n");
        return 0;
    }
    if (query_closed()) {
        if (do_open()) {
            write("You open the " + short(0) + ".\n");
        } else {
            add_failed_mess("You cannot open $D.\n");
            return 0;
        }
    }
    if (cont_volume <= 0) {
        add_failed_mess("$C$$D has nothing to pour!\n");
        return 0;
    }
    if (sizeof(to) > 1) {
        add_failed_mess("You can only pour into one object at a time.\n");
        return 0;
    }
    their_volume = (int)to[0]->query_volume();
    their_max = (int)to[0]->query_max_volume();
    if (their_max <= 0) {
        add_failed_mess("$C$" + to[0]->the_short(0) +
            " doesn't look like it can be filled!\n");
        return 0;
    }
    if (their_volume >= their_max) {
        add_failed_mess("The " + to[0]->short(0)
              + " $V$0=is,are$V$ full to the brim already.\n");
        their_volume = their_max;
    }
    if ((m == 1) && (n == 1)) {
        volume_needed = volume;
    } else {
        volume_needed = max_volume * m / n;
    }
    if (volume < volume_needed) {
        add_failed_mess("$C$$D $V$0=is,are$V$ less than " + m + "/" + n +
              " full.\n");
        return 0;
    }
    if (volume_needed > 120) {
        volume_needed += random(240) - 120;
    }
    if (volume_needed > (their_max - their_volume)) {
        volume_needed = their_max - their_volume;
        ovf = 1;
    }
    if (volume_needed > cont_volume) {
        add_failed_mess("You drain the " + short(0) + " into the "
              + to[0]->short(0) + " but it $V$0=is,are$V$ not enough.\n");
        volume_needed = cont_volume;
        this_player()->add_succeeded(to[0]);
    } else {
        this_player()->add_succeeded(to[0]);
    }
    xfer_result = xfer_volume( volume_needed, to[0] );
    if (xfer_result < volume_needed) {
        this_player()->add_succeeded_mess(this_object(), "$N $V $D into $I.\n", ({to[0]}));
    }
    else {
        add_failed_mess( "You were unable to $V $D into $I.\n", ({to[0]}));
        return 0;
    }
    if (ovf) {
        this_player()->add_succeeded_mess(this_object(), "$N $V $D into $I, " +
            "spilling some in the process.\n", ({to[0]}));
    }
    return 1;
}
int do_fill(object *to, mixed *args_b, mixed *args_a, mixed *args) {
    int m;
    int n;
    int i;
    int run_out;
    int volume_needed;
    int their_volume;
    int their_max;
    int amount_not_poured;
    int ok;
    if (query_fighting(this_player())) {
       add_failed_mess("You cannot attempt to do this while in combat.\n");
       return 0;
    }
    if (sizeof(args) == 4) {
        sscanf(args[1] + " " + args[2], "%d %d", m, n);
        if ((m > n) || (m < 0) || (n <= 0)) {
            add_failed_mess("Interesting fraction you have there!\n");
            return 0;
        }
    } else {
        m = 1;
        n = 1;
    }
    if (query_closed() &&
        query_locked()) {
        add_failed_mess("$C$$D $V$0=is,are$V$ locked!\n");
        return 0;
    }
    if (query_closed()) {
        if (do_open()) {
            write("You open the " + short(0) + ".\n");
        } else {
            add_failed_mess("You cannot open $D.\n");
            return 0;
        }
    }
    if (cont_volume <= 0) {
        add_failed_mess("$C$$D has nothing to pour!\n");
        return 0;
    }
    run_out = 0;
    for (i = 0; i < sizeof(to) && !run_out; i++) {
        if ((environment(this_object()) != this_player()) &&
            (environment(to[i]) != this_player())) {
            write("You're not carrying " + the_short() + " or " +
                  to[i]->the_short() + ".\n");
            continue;
        }
        if (to[i]->query_closed()) {
            add_failed_mess("$I $V$0=is,are$V$ closed.\n", to[i..i]);
            continue;
        }
        their_volume = (int)to[i]->query_volume();
        their_max = (int)to[i]->query_max_volume();
        if (their_max <= 0) {
            add_failed_mess("$I doesn't look like it can be filled!\n",
                            to[i..i]);
            continue;
        }
        if (their_volume >= their_max) {
            add_failed_mess("$I $V$0=is,are$V$ full to the brim already.\n", to[i..i]);
            continue;
        }
        volume_needed = their_max * m / n;
        if (their_volume >= volume_needed) {
            add_failed_mess("$I $V$0=is,are$V$ more than " + m + "/" + n +
                  " full already.\n", to[i..i]);
            continue;
        }
        if (volume_needed > 120) {
            volume_needed += random(240) - 120;
        }
        if (volume_needed > their_max) {
            volume_needed = their_max;
        }
        ok++;
        volume_needed -= their_volume;
        if (volume_needed > cont_volume) {
            add_failed_mess("You drain " + the_short() + " into "
                  + to[i]->the_short() + " but it $V$0=is,are$V$ not enough.\n");
            volume_needed = cont_volume;
            run_out = 1;
            this_player()->add_succeeded(to[i]);
        } else {
            this_player()->add_succeeded(to[i]);
        }
        amount_not_poured = xfer_volume(volume_needed, to[i]);
        if (amount_not_poured) {
           ok--;
        }
    }
    if (!ok) {
       add_failed_mess("You cannot seem to do anything useful with this "
                       "container, it seems unwilling to accept what you "
                       "offer.\n");
    }
    return ok;
}
private int query_fighting(object player) {
   object ob;
   if (!player || !environment(player)) {
      return 0;
   }
   if (player->query_fighting()) {
      return 1;
   }
   foreach (ob in all_inventory(environment(player))) {
      if (living(ob)) {
         if (ob->query_attacker_list() &&
             member_array(this_player(), ob->query_attacker_list()) != -1) {
            return 1;
         }
      }
   }
   if (environment(ob)->query_mirror_room()) {
      foreach (ob in all_inventory(environment(player)->query_mirror_room())) {
         if (living(ob)) {
            if (member_array(this_player(), ob->query_attacker_list()) != -1) {
               return 1;
            }
         }
      }
   }
}
int is_fighting_bottle_smashed(object player,
                               object me) {
   object* fighting;
   object ob;
   object weapon;
   string skill;
   string my_skill;
   int bonus;
   int stopped;
   stopped = 0;
   if (query_fighting(player)) {
      fighting = filter(player->query_attacker_list(),
                        (: environment($1) == $2 :), environment(player));
      if (query_holder()) {
         bonus = 0;
         bonus += -10 * player->query_free_limbs();
      } else {
         bonus = 20;
      }
      if (sizeof(fighting)) {
         bonus += (sizeof(fighting) - 1) * 20;
      }
      if (player->query_free_limbs() < 2 &&
          !query_holder()) {
         bonus += 50 - player->query_free_limbs() * 25;
      }
      foreach (ob in fighting) {
         if (sizeof(ob->query_holding() - ({ 0 }))) {
            weapon = (ob->query_holding() - ({ 0 }))[0];
            skill = weapon->query_weapon_type();
            if (skill == "mixed" ||
                (skill != "sharp" && skill != "blunt" && skill != "pierce")) {
               skill = ({ "sharp", "blunt", "pierce" })[random(3)];
            }
            skill = "fighting.combat.melee." + skill;
         } else {
            skill = "fighting.combat.melee.unarmed";
         }
         my_skill = "fighting.combat.special.unarmed";
         switch (player->query_combat_response()) {
         case "parry" :
            my_skill = "fighting.combat.parry.melee";
            break;
         case "dodge" :
            my_skill = "fighting.combat.dodging.melee";
            break;
         case "neutral" :
            my_skill = "fighting.combat." +
            (({ "parry", "dodging" })[random(2)]) + ".melee";
         }
         switch (TASKER->compare_skills(player,
                                       my_skill,
                                       ob,
                                       skill,
                                       -bonus,
                                       TM_FREE,
                                       TM_FREE)) {
         case OFFAWARD :
            if (player->query_combat_response() == "dodge") {
               tell_object(player,
                           "%^YELLOW%^You nimbly dodge an attack to avoid "
                           "getting " +
                           me->poss_short() +
                           " smashed out of your hand and feel better about "
                           "attempting it next time.\n%^RESET%^");
            } else {
               tell_object(player,
                           "%^YELLOW%^You nimbly parry an attack to avoid "
                           " getting " +
                           me->poss_short() +
                           " smashed out of your hand and feel better about "
                           "attempting it next time.\n%^RESET%^");
            }
         case OFFWIN :
            tell_room(environment(player),
                      player->the_short() + " avoids getting " +
                      me->poss_short() + " smashed by " +
                      query_multiple_short(({ ob })) + ".\n",
                               ({ player }));
            tell_object(player,
                        "You avoid getting " + me->poss_short() +
                        " smashed by " + query_multiple_short(({ ob })) +
                        ".\n");
            do_damage("crush", 20 + random(50));
            break;
         case DEFAWARD :
            tell_object(ob,
                        "%^YELLOW%^You feel much more able to smash "
                        "bottles out of peoples hands than "
                        "before.\n%^RESET%^");
         case DEFWIN :
            if (!query_holder() &&
                me->move(environment(player)) == MOVE_OK) {
               tell_room(environment(player),
                   ob->the_short() + " smashes " + the_short() + " out of " +
                   player->the_short() + "'s hands onto the ground "
                   "causing some of the liquid to splash out.\n",
                   ({ player, me }));
               tell_object(player,
                   ob->the_short() + " smashes " + the_short() + " out of " +
                   "your hands onto the ground "
                   "causing some of the liquid to splash out.\n");
               tell_object(me,
                   ob->the_short() + " smash " + the_short() + " out of " +
                   player->the_short() + "'s hands onto the ground "
                   "causing some of the liquid to splash out.\n");
            } else {
               tell_room(environment(player),
                   ob->the_short() + " smashes " + the_short() + " away "
                   "from " + player->the_short() + "'s mouth causing "
                   "some of the liquid to splash out.\n", ({ player, me }));
               tell_object(player,
                   ob->the_short() + " smashes " + the_short() + " away "
                   "from " + "your mouth causing some of the liquid to "
                   "splash out.\n");
               tell_object(me,
                   ob->the_short() + " smash " + the_short() + " out of " +
                   player->the_short() + "'s hands onto the ground "
                   "causing some of the liquid to splash out.\n");
            }
            stopped = 1;
            break;
         }
         if (stopped) {
            break;
         }
      }
   }
   return stopped;
}
private string consumed_desc( int consumed_amount ) {
   string amount_desc;
   object* contents;
   string* contents_descs = ({ });
   string contents_desc;
   contents = all_inventory( this_object() );
   if( !consumed_amount || !sizeof( contents ) )
      return "nothing much";
   switch( consumed_amount ) {
   case 1..30:
      amount_desc = "a teaspoon";
      break;
   case 31..80:
      amount_desc = "a tablespoon";
      break;
   case 81..140:
      amount_desc = "an ounce";
      break;
   case 141..800:
      amount_desc = "a few ounces";
      break;
   case 801..1200:
      amount_desc = "a cup";
      break;
   case 1201..2000:
      amount_desc = "a couple of cups";
      break;
   case 2001..3500:
      amount_desc = "a pint";
      break;
   case 3501..7000:
      amount_desc = "a couple of pints";
      break;
   case 7001..15000:
      amount_desc = "several pints";
      break;
   case 15001..25000:
      amount_desc = "about a gallon";
      break;
   default:
      amount_desc = "several gallons";
   }
   contents = filter( contents, (: $1->query_liquid() :) );
   foreach( string* frog in unique_array( contents->short(), (: $1 :) ) ) {
      if( sizeof( frog ) > 1 ) {
         contents_descs += ({ pluralize( frog[0] ) });
      } else {
         contents_descs += ({ frog[0] });
      }
   }
   contents_desc = query_multiple_short( contents_descs );
   return amount_desc +" of "+ contents_desc;
}
int drink_amount(int drinking,
                 object player) {
   int cap_amount;
   int amt_to_drink;
   int amount_can_be_drunk;
   object* contents;
   object ob;
   int orig_cv;
   amt_to_drink = drinking;
   if (amt_to_drink > cont_volume) {
      amt_to_drink = cont_volume;
   }
   if (max_volume / 20 > VOLUME_WINE) {
      cap_amount = max_volume / 20;
   } else {
      cap_amount = VOLUME_WINE;
   }
   if (amt_to_drink < cap_amount) {
      if (query_fighting(player)) {
         amt_to_drink += random(2 * (cap_amount - amt_to_drink)) -
                         cap_amount - amt_to_drink;
         if (amt_to_drink < VOLUME_MINIMUM_DRINKABLE * 2) {
            amt_to_drink = VOLUME_MINIMUM_DRINKABLE * 2;
         }
      } else {
         amt_to_drink += random((cap_amount - amt_to_drink) / 6) -
                         (cap_amount - amt_to_drink) / 12;
      }
   }
   if (amt_to_drink < VOLUME_MINIMUM_DRINKABLE) {
      amt_to_drink = VOLUME_MINIMUM_DRINKABLE;
   }
   if (amt_to_drink < (max_volume / 100)) {
      amt_to_drink = max_volume / 100;
   }
   if( amt_to_drink > cont_volume ) {
      amt_to_drink = cont_volume;
   }
   amount_can_be_drunk = (8000 - (int)this_player()->query_volume(2)) *
     (int)this_player()->query_con() / 12;
   if (amt_to_drink > amount_can_be_drunk) {
       write("You drink some of the liquid, "
             "but simply cannot fit it all in.\n");
       amt_to_drink = amount_can_be_drunk;
   }
   if (is_fighting_bottle_smashed(this_player(), this_object())) {
      amt_to_drink *= (1 + random(15));
      if (amt_to_drink > volume) {
         amt_to_drink = volume;
      }
      orig_cv = cont_volume;
      foreach (ob in all_inventory(this_object())) {
         if (ob->query_continuous()) {
            if (amt_to_drink == cont_volume) {
               ob->adjust_amount(-ob->query_amount());
            } else {
               ob->adjust_amount(-(ob->query_amount() * amt_to_drink / orig_cv));
            }
         }
      }
      add_succeeded_mess("");
      do_damage("crush", 50 + random(300));
      return 1;
   }
   contents = all_inventory(this_object());
   if( sizeof( contents[0]->query_eat_mess() ) ) {
      add_succeeded_mess( contents[0]->query_eat_mess() );
   } else {
      add_succeeded_mess("$N $V "+ consumed_desc( amt_to_drink ) +
                         " from $D.\n");
   }
   if (amt_to_drink - drinking > (max_volume / 40) &&
       amt_to_drink - drinking > VOLUME_MINIMUM_DRINKABLE) {
      add_succeeded_mess(({ "Whoops!  You seemed to have gulped "
                            "too much down.\n",
                            "" }));
   }
   orig_cv = cont_volume;
   foreach (ob in contents) {
       if (ob->query_continuous()) {
           if (amt_to_drink == orig_cv) {
               ob->consume(this_player(), ob->query_amount());
           } else {
               ob->consume(this_player(),
                           ob->query_amount() * amt_to_drink / orig_cv);
           }
       }
   }
   return 1;
}
int do_drink(object *dest, mixed me, mixed him, mixed args, string pattern)
{
    int amt_to_drink;
    int m;
    int n;
    if (sizeof(dest)) {
        add_failed_mess("Drinking is a very simple operation "
              "- please don't complicate matters.\n");
        return 0;
    }
    if (environment(this_object()) != this_player()) {
        add_failed_mess("You aren't carrying $D.\n");
        return 0;
    }
    if (!ensure_open()) {
       return 0;
    }
    if (!is_liquid) {
        add_failed_mess("$C$$D $V$0=is,are$V$ bone dry!\n");
        return 0;
    }
    if (pattern == drink_pat[1]) {
        m = to_int(args[0]);
        n = to_int(args[1]);
        if ( n > 100 ) {
          add_failed_mess( "You can't drink with that much precision!\n" );
          return 0;
        }
        if ((m > n) || (m < 0) || (n <= 0)) {
            add_failed_mess("Interesting fraction you have there!\n");
            return 0;
        }
    } else {
        m = 1;
        n = 1;
    }
    if (_fraction) {
        m = _fraction[0];
        n = _fraction[1];
    }
    if ((m == 1) && (n == 1)) {
        amt_to_drink = cont_volume;
    } else {
        amt_to_drink = (max_volume*m)/n;
        if (amt_to_drink > volume) {
            add_failed_mess("$C$$D $V$0=is,are$V$ less than " + m + "/" + n +
                  " full.\n");
            return 0;
        }
        if (amt_to_drink > cont_volume) {
            amt_to_drink = cont_volume;
        }
    }
    if (!drink_amount(amt_to_drink, this_player())) {
       return 0;
    }
    switch ((this_player()->query_volume(2) + 100) / 200) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
        break;
      case 5:
        write("You feel mildly full of liquid.\n");
        break;
      case 6:
        write("You feel very full of liquid.\n");
        break;
      case 7:
        write("You feel all the liquid sloshing around inside you.\n");
        break;
      case 8:
        write("You are awash with liquid.\n");
        break;
      case 9:
        write("You are full to the brim with liquid.\n");
        break;
      default:
        write("You feel you would burst if you drank any more.\n");
        break;
    }
    return 1;
}
int do_quaff(object *dest, mixed me, mixed him, mixed args, string pattern) {
   return do_drink(dest, me, him, args, pattern);
}
int do_empty(object *dest, string me, string him, string prep)
{
   if (environment(this_object()) != this_player()) {
       add_failed_mess("You are not carrying $D.\n");
       return 0;
   }
   if (sizeof(dest)) {
       write("Passing on to pour ... bad move.\n");
   }
   if (!ensure_open()) {
      add_failed_mess("$C$$D $V$0=is,are$V$ not open.\n");
      return 0;
   }
   if (cont_volume == 0 &&
       !sizeof(all_inventory())) {
       add_failed_mess("$C$$D $V$0=is,are$V$ already empty.\n");
       return 0;
   }
   (void)remove_volume(cont_volume);
   all_inventory()->move(environment(this_player()));
   return 1;
}
int check_splashable(object ob, object splasher, object splashee){
  return ob->query_splashable(splasher, splashee);
}
int do_splash(object *dest, mixed me, mixed him, mixed args, string pattern) {
    int amt_to_splash, i, m, n, orig_cv;
    object *contents;
    if (!sizeof(dest)) {
        add_failed_mess("Splash it on who?\n");
        return 0;
    }
    if(sizeof(dest) >1){
        add_failed_mess("You may only splash one person at a time.\n");
        return 0;
    }
    if (environment(this_object()) != this_player()) {
        write("You aren't carrying the " + short(0) + ".\n");
        return 0;
    }
    if (!ensure_open()) return 0;
    if (!is_liquid) {
        add_failed_mess("The " + short(0) + " $V$0=is,are$V$ bone dry!\n");
        return 0;
    }
    if (pattern == splash_pat[1]) {
        m = to_int(args[0]);
        n = to_int(args[1]);
        if ((m > n) || (m < 0) || (n <= 0)) {
            notify_fail("Interesting fraction you have there!\n");
            return 0;
        }
    } else {
        m = 1;
        n = 1;
    }
    contents = filter( all_inventory(this_object()), (:check_splashable:),
          this_player(), dest[0]);
    if( !sizeof(contents) ){
       add_failed_mess("You can't splash anything in $D.\n");
       return 0;
    }
    orig_cv = cont_volume;
    if ( m == n ){
        amt_to_splash = cont_volume;
    } else {
        amt_to_splash = (max_volume*m)/n;
        if (amt_to_splash > volume) {
            add_failed_mess("The " + short(0) + " $V$0=is,are$V$ less than "
               + m + "/" + n + " full.\n");
            return 0;
        }
        if (amt_to_splash > cont_volume) {
            amt_to_splash = cont_volume;
        }
    }
    if(this_player() == dest[0]){
       this_player()->add_succeeded_mess(this_object(),
                     "$N $V " + query_multiple_short(contents) +
                     " from $D onto "+this_player()->query_objective() +
                     "self.\n", ({}));
    }else{
       this_player()->add_succeeded_mess(this_object(),
                     "$N $V " + query_multiple_short(contents) +
                     " from $D onto $I.\n", dest);
    }
    for (i = 0; i < sizeof(contents); i++) {
        if (amt_to_splash == cont_volume) {
           contents[i]->consume(dest[0],
           contents[i]->query_amount(), "splash");
        } else {
           contents[i]->consume(dest[0],
              (int)contents[i]->query_amount()
              * amt_to_splash / orig_cv, "splash");
        }
    }
    return 1;
}
int check_applicable(object ob, object applier, object appliee){
  return ob->query_applicable(applier, appliee);
}
int do_rub(object *dest, mixed me, mixed him, mixed args, string pattern) {
    int amt_to_apply, i, m, n, orig_cv;
    object *contents;
    if (!sizeof(dest)) {
        add_failed_mess("Rub it on who?\n");
        return 0;
    }
    if(sizeof(dest) >1){
        add_failed_mess("You may only rub stuff on one person at a time.\n");
        return 0;
    }
    if (environment(this_object()) != this_player()) {
        write("You aren't carrying the " + short(0) + ".\n");
        return 0;
    }
    if (!ensure_open()) return 0;
    if (!is_liquid) {
        add_failed_mess("The " + short(0) + " $V$0=is,are$V$ bone dry!\n");
        return 0;
    }
    if (pattern == apply_pat[1]) {
        m = to_int(args[0]);
        n = to_int(args[1]);
        if ((m > n) || (m < 0) || (n <= 0)) {
            notify_fail("Interesting fraction you have there!\n");
            return 0;
        }
    } else {
        m = 1;
        n = 1;
    }
    contents = filter( all_inventory(this_object()), (:check_applicable:),
        this_player(), dest[0]);
    if( !sizeof(contents) ){
       add_failed_mess("You can't rub anything in $D on $I.\n",dest);
    }
    orig_cv = cont_volume;
    if ( m == n ){
        amt_to_apply = cont_volume;
    } else {
        amt_to_apply = (max_volume*m)/n;
        if (amt_to_apply > volume) {
            add_failed_mess("The " + short(0) + " $V$0=is,are$V$ less than "
               + m + "/" + n + " full.\n");
            return 0;
        }
        if (amt_to_apply > cont_volume) {
            amt_to_apply = cont_volume;
        }
    }
    if (this_player() == dest[0]){
       this_player()->add_succeeded_mess(this_object(),
                     "$N $V " + query_multiple_short(contents) +
                     " from $D onto "+this_player()->query_objective()+"self.\n", ({}));
    } else {
       this_player()->add_succeeded_mess(this_object(),
                     "$N $V " + query_multiple_short(contents) +
                     " from $D onto $I.\n", dest);
    }
    for (i = 0; i < sizeof(contents); i++) {
        if (amt_to_apply == cont_volume) {
           contents[i]->consume(dest[0],
                          contents[i]->query_amount(),"apply");
        } else {
           contents[i]->consume(dest[0],
              (int)contents[i]->query_amount()
              * amt_to_apply / orig_cv, "apply");
        }
    }
    return 1;
}
int do_apply(object *dest, mixed me, mixed him, mixed args, string pattern){
   return do_rub(dest, me, him, args, pattern);
}
int do_taste() {
    int amount_tasted;
    if (environment(this_object()) != this_player()) {
        write("You aren't carrying the " + short(0) + ".\n");
        return 0;
    }
    if (!ensure_open()) {
       return 0;
    }
    if (!cont_volume || !is_liquid) {
        add_failed_mess("The " + short(0) + " $V$0=is,are$V$ bone dry!\n");
        return 0;
    }
    amount_tasted = VOLUME_SHOT;
    if (cont_volume < amount_tasted) {
        amount_tasted = cont_volume;
    }
    if (amount_tasted < max_volume / 100) {
       amount_tasted = max_volume / 100;
    }
    return drink_amount(amount_tasted, this_player());
}
int do_sip() {
   int amount_tasted;
   if (environment(this_object()) != this_player()) {
      write("You aren't carrying the " + short(0) + ".\n");
      return 0;
   }
   if (!ensure_open()) {
      return 0;
   }
   if (!cont_volume || !is_liquid) {
      add_failed_mess("The " + short(0) + " $V$0=is,are$V$ bone dry!\n");
      return 0;
   }
   amount_tasted = VOLUME_SHOT * 2;
   if (cont_volume < amount_tasted) {
      amount_tasted = cont_volume;
   }
   if (amount_tasted < max_volume / 70) {
      amount_tasted = max_volume / 70;
   }
   return drink_amount(amount_tasted, this_player());
}
int do_smell() {
   if (!ensure_open()) {
      return 0;
   }
   write("Smelling isn't implemented yet.  Sorry.\n");
   return 1;
}
protected int handle_restore_inventory(object ob) {
   int ret;
   ret = ::handle_restore_inventory(ob);
   if (ret == MOVE_OK) {
      return MOVE_OK;
   }
   if (ob->query_liquid()) {
      ob->set_amount( query_max_volume() - query_volume() );
      ret = ::handle_restore_inventory(ob);
      if (ret == MOVE_OK) {
         return MOVE_OK;
      }
   }
   return ret;
}
mapping int_query_static_auto_load() {
  mapping tmp;
  tmp = ::int_query_static_auto_load();
  return ([ "::" : tmp, "leak rate" : leak_rate,
           "max volume" : max_volume,
          ]);
}
mapping query_static_auto_load() {
  if ( !query_name() || ( query_name() == "object" ) ) {
    return 0;
  }
  if ( explode( file_name( this_object() ), "#" )[ 0 ] == "/obj/vessel" ) {
    return int_query_static_auto_load();
  }
  return ([ ]);
}
void init_static_arg(mapping args) {
  if (args["::"])
    ::init_static_arg(args["::"]);
  if (!undefinedp(args["leak rate"]))
    leak_rate = args["leak rate"];
  if (!undefinedp(args["max volume"]))
    max_volume = args["max volume"];
}
int test_add(object ob, int flag) {
    int new_vol;
    if ( !::test_add( ob, flag ) ) {
        return 0;
    }
    if (ob->query_continuous()) {
        new_vol = ob->query_amount();
    } else if (ob->query_property("density")) {
        new_vol = (int)ob->query_weight()*(int)ob->query_property("density");
    } else {
        new_vol = 0;
    }
    if ((new_vol + volume) > max_volume) {
        return 0;
    }
    return 1;
}
void event_enter(object ob, string message, object from) {
    int ob_vol, ob_cont;
    if (environment(ob) == this_object()) {
        if (ob->query_continuous() ) {
            ob_vol = ob->query_amount();
            ob_cont = 1;
        } else if (ob->query_property("density")) {
            ob_vol = (int)ob->query_weight()*
              (int)ob->query_property("density");
        } else {
            ob_vol = 0;
        }
        if (ob->query_liquid()) {
           is_liquid = 1;
           _liquids = ({ });
        }
#ifdef DEBUG
        debug_printf("Increasing volume by " + ob_vol + ".\n");
#endif
        volume += ob_vol;
        if (ob_cont) cont_volume += ob_vol;
        REACTION_HANDLER->check_reaction(ob);
        if (leak_rate > 0) {
            set_heart_beat(1);
        }
    }
}
void event_exit(object ob, string mess, object to) {
    int ob_vol, ob_cont;
    if (environment(ob) == this_object()) {
        if (ob->query_continuous()) {
            ob_vol = ob->query_amount();
            ob_cont = 1;
        } else if (ob->query_property("density")) {
            ob_vol = (int)ob->query_weight()*
              (int)ob->query_property("density");
        } else {
            ob_vol = 0;
        }
#ifdef DEBUG
        debug_printf("Decreasing volume by " + ob_vol + ".\n");
#endif
        volume -= ob_vol;
        if (ob_cont) cont_volume -= ob_vol;
        if (volume <= 0) is_liquid = 0;
    }
}
void break_me() {
  object *liquid;
   liquid = filter(all_inventory(), (: $1->query_liquid() :));
   if (sizeof(liquid)) {
      tell_room(environment(),
         query_multiple_short(liquid) + " splashes all over the place "
         "as " + the_short() + " breaks.\n");
       liquid->move("/room/rubbish");
   }
   ::break_me();
}
mixed* parse_match_object(string* input, object player,
                          class obj_match_context context) {
   int result;
   result = ::is_matching_object(input, player, context);
   if (result) {
      _fraction = context->fraction;
      if (update_parse_match_context(context, 1, result)) {
         return ({ result, ({ this_object() }) });
      }
   }
   return 0;
}
string *parse_command_adjectiv_id_list() {
   string *ret;
   ret =  fullness_adjectives() + ::parse_command_adjectiv_id_list();
   if (is_liquid && !query_opaque()) {
      object liquid;
      if (!sizeof(_liquids)) {
         figure_out_liquids();
      }
      _liquids -= ({ 0 });
      foreach (liquid in _liquids) {
         ret += liquid->parse_command_adjectiv_id_list();
      }
      return ret;
   }
   return ret;
}
string* parse_command_id_list() {
   if (is_liquid && !query_opaque()) {
      string* ret;
      object liquid;
      if (!sizeof(_liquids)) {
         figure_out_liquids();
      }
      _liquids -= ({ 0 });
      ret = ::parse_command_id_list();
      foreach (liquid in _liquids) {
         ret += liquid->parse_command_id_list();
      }
      return ret;
   }
   return ::parse_command_id_list();
}
string* parse_command_plural_id_list() {
   if (is_liquid && !query_opaque()) {
      string* ret;
      object liquid;
      if (!sizeof(_liquids)) {
         figure_out_liquids();
      }
      _liquids -= ({ 0 });
      ret = ::parse_command_plural_id_list();
      foreach (liquid in _liquids) {
         ret += liquid->parse_command_plural_id_list();
      }
      return ret;
   }
   return ::parse_command_plural_id_list();
}
int query_vessel() { return 1; }