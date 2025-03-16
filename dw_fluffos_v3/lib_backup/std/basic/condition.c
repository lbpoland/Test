#include <armoury.h>
#include <move_failures.h>
#define DAMAGE_NORM 200
private nosave int cond, max_cond, lowest_cond, damage_chance, hide_cond;
void create() {
   max_cond = 1;
}
void break_me() {
  if(environment(this_object())) {
    if(living(environment(this_object())))
      tell_object(environment(this_object()),
                  capitalize(this_object()->the_short()) + " breaks!\n");
    else
      tell_room(environment(this_object()),
                capitalize(this_object()->the_short()) + " breaks!\n");
  }
  if((int)this_object()->move("/room/rubbish") != MOVE_OK)
    move_object("/room/rubbish");
}
string cond_string() {
   string pronoun;
   string verb;
   if ( cond > max_cond ) {
      cond = max_cond;
   }
   if ( hide_cond )
      return "";
   pronoun = capitalize(this_object()->query_pronoun());
   verb = this_object()->query_is_pair() ? " are" : " is";
   switch ( ( 100 * cond ) / max_cond ) {
      case 91 .. 100 :
         return pronoun + verb + " in excellent condition.\n";
      case 81 .. 90 :
         return pronoun + verb + " in very good condition.\n";
      case 71 .. 80 :
         return pronoun + verb + " in good condition.\n";
      case 61 .. 70 :
         return pronoun + verb + " in decent condition.\n";
      case 51 .. 60 :
         return pronoun + verb + " in fairly good condition.\n";
      case 41 .. 50 :
         return pronoun + verb + " in fairly poor condition.\n";
      case 31 .. 40 :
         return pronoun + verb + " in poor condition.\n";
      case 21 .. 30 :
         return pronoun + verb + " in really poor condition.\n";
      case 11 .. 20 :
         return pronoun + verb + " in very poor condition.\n";
      case 1 .. 10 :
         return pronoun + verb + " in atrocious condition.\n";
      default :
         return pronoun + verb + " a complete wreck.\n";
   }
}
void set_max_cond(int i) { max_cond = i; }
void set_cond(int i) {
   cond = i;
   if (cond < 0) {
      cond = 0;
   }
   if (cond < lowest_cond) {
      lowest_cond = cond;
   }
   if ( cond <= 0 ) {
      if ( environment( this_object() ) &&
          !environment( this_object() )->query_property("don't break contents")) {
         this_object()->break_me();
      }
      return 0;
   }
}
int adjust_cond( int i ) {
   cond += i;
   if (cond < 0)
      cond = 0;
   if ( cond < lowest_cond )
      lowest_cond = cond;
   if ( cond > max_cond )
      cond = max_cond;
   if ( cond <= 0 ) {
      if ( !environment()->query_property( "don't break contents" ) )
         this_object()->break_me();
      return 0;
   }
   return cond;
}
void set_lowest_cond(int i) { lowest_cond = i; }
void set_hide_cond(int i) { hide_cond = i; }
int query_cond() {
  if ( cond > max_cond ) {
    cond = max_cond;
  }
  return cond;
}
int query_max_cond() { return max_cond; }
int query_lowest_cond() { return lowest_cond; }
int query_hide_cond() { return hide_cond; }
void set_percentage(int i) {
   if (i > 100) {
      i = 100;
   }
   set_cond((query_max_cond() * i) / 100);
   set_lowest_cond((query_cond()*(random(30) + 70)) / 100);
}
int query_damage_chance() { return damage_chance; }
void set_damage_chance( int number ) { damage_chance = number; }
void do_damage( string type, int amount ) {
   int wholes, parts;
   wholes = amount * ( 1 + random( damage_chance ) + random( damage_chance ) );
   parts = wholes % DAMAGE_NORM;
   wholes /= DAMAGE_NORM;
   if ( random( DAMAGE_NORM ) < parts )
      wholes++;
   adjust_cond( -wholes );
}
mixed *stats() {
   return
      ({
         ({ "condition", cond }),
         ({ "max cond", max_cond }),
         ({ "lowest cond", lowest_cond }),
         ({ "damage chance", damage_chance }),
         ({ "hide cond", hide_cond }),
      });
}
mapping query_static_auto_load() {
   return ([
      "max cond" : max_cond,
      "damage chance" : damage_chance,
      "hide cond" : hide_cond
   ]);
}
void init_static_arg( mapping map ) {
   if ( !undefinedp( map[ "max cond" ] ) )
      max_cond = map[ "max cond" ];
   if ( !undefinedp( map[ "damage chance" ] ) )
      damage_chance = map[ "damage chance" ];
   if ( !undefinedp( map[ "hide cond" ] ) )
      hide_cond = map[ "hide cond" ];
}
mapping query_dynamic_auto_load() {
   if ( cond > max_cond ) {
      cond = max_cond;
   }
   if ( lowest_cond > cond ) {
      lowest_cond = cond;
   }
   return ([
      "cond" : cond,
      "lowest cond" : lowest_cond
   ]);
}
void init_dynamic_arg( mapping map, object ) {
   if ( !undefinedp( map[ "cond" ] ) )
      cond = map[ "cond" ];
   if ( !undefinedp( map[ "lowest cond" ] ) )
      lowest_cond = map[ "lowest cond" ];
}