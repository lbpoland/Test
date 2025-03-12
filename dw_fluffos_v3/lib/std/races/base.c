#define QUEST_AVE 140
#define QUEST_MAX 570
#define BASE 50
#define SCALE 10
#define NORM 15
#define EXPERT 20
#define A_TYPES ([ \
      "claws" : "sharp", \
      "chew" : "sharp", \
      "beak" : "pierce", \
      "bite" : "pierce", \
      "horn" : "pierce", \
      "hands" : "blunt", \
      "feet" : "blunt", \
      "tail" : "blunt", \
      "hoof" : "blunt", \
      "wrestle" : "blunt", \
   ])
inherit "/std/object";
private int height;
private int *sight;
private int *stats;
private string desc;
private string skin;
string *inedible;
string *unrottable;
string *pluckable;
private string *limbs;
private mixed *acs;
private mixed *attacks;
private mapping _fixed_bits;
mixed *bits;
void create() {
   do_setup++;
   ::create();
   do_setup--;
   sight = ({ 5, 20, 200, 300 });
   stats = allocate( 5 );
   desc = "a small non-descript thing";
   inedible = ({  });
   unrottable = ({  });
   pluckable = ({  });
   acs = ({ });
   attacks = ({ });
   bits = ({ });
   if ( !do_setup )
      this_object()->setup();
}
int query_height() { return height; }
void set_height( int number ) { height = number; }
int *query_sight() { return copy(sight); }
void set_sight( int *numbers ) { sight = numbers; }
int query_dark( int light ) {
   if ( light < sight[ 0 ] ) {
      return -2;
   }
   if ( light < sight[ 1 ] ) {
      return -1;
   }
   if ( light > sight[ 3 ] ) {
      return 2;
   }
   if ( light > sight[ 2 ] ) {
      return 1;
   }
   return 0;
}
int *query_stats() { return copy(stats); }
void set_stats( int *numbers ) { stats = numbers; }
string query_skin() { return skin; }
void set_skin( string word ) { skin = word; }
string query_desc( object thing ) {
   return capitalize( (string)thing->query_pronoun() ) +" is "+ desc +".\n";
}
void set_desc( string words ) { desc = words; }
string *query_limbs() {
   if ( !limbs ) {
      this_object()->find_limbs();
   }
   return copy(limbs);
}
void find_limbs() {
   int i;
   string limb;
   limbs = ({ });
   for ( i = 0; i < sizeof( bits ); i += 3 ) {
     if ( sscanf( bits[ i ], "%s hand", limb ) == 1 ) {
       limbs += ({ bits[ i ] });
     }
   }
}
mixed *query_acs() { return copy(acs); }
void add_ac( string ac_name, string ac_type, mixed ac_amount ) {
   acs += ({ ac_name, ac_type, ac_amount });
}
mixed *query_attacks() { return copy(attacks); }
void add_attack( string attack_name, int attack_chance, int *attack_data ) {
   attacks += ({ attack_name, attack_chance, attack_data });
}
mixed *query_bits() { return bits; }
mixed *query_bit( string word ) {
   int i;
   i = member_array( word, bits );
   if ( ( i == -1 ) || ( i % 3 ) ) {
      return ({ });
   }
   return bits[ i .. i + 2 ];
}
private void fixup_bits() {
   string* str_bits;
   string pl;
   int i;
   if (_fixed_bits) {
      return ;
   }
   _fixed_bits = ([ ]);
   for ( i = sizeof( bits ) - 3; i > -1; i -= 3 ) {
      str_bits = explode(bits[i], " ");
      pl = pluralize(str_bits[<1]);
      if (!_fixed_bits[str_bits[<1]]) {
         _fixed_bits[str_bits[<1]] = ({ });
      }
      _fixed_bits[str_bits[<1]] += ({ ({ str_bits[0..<2], i, 0 }) });
      if (!_fixed_bits[pl]) {
         _fixed_bits[pl] = ({ });
      }
      _fixed_bits[pl] += ({ ({ str_bits[0..<2], i, 1 }) });
   }
}
private string *query_old_possible_bits( string word ) {
   int i;
  int j;
  string *possibles;
  possibles = ({ });
  for ( i = sizeof( bits ) - 3; i > -1; i -= 3 ) {
    if ( ( bits[ i ] == word ) ||
          ( bits[ i + 1 ] == word ) ||
          !word) {
       if (arrayp( bits[i+2][2] )) {
         for ( j = 0; j < bits[i + 2][2][1]; j++) {
           possibles += ({ bits[ i ] });
         }
       } else {
         possibles += ({ bits[ i ] });
       }
     }
   }
   return possibles;
}
string *query_possible_bits( string word ) {
  string* str_bits;
  string* adj;
  string *possibles;
  mixed* bing;
  if(!word) {
    return query_old_possible_bits( word );
  }
  fixup_bits();
  str_bits = explode(word, " ");
  possibles = ({ });
  if (_fixed_bits[str_bits[<1]]) {
     adj = str_bits[0..<2];
     foreach (bing in _fixed_bits[str_bits[<1]]) {
        if (!bing[2] &&
            sizeof(adj) == sizeof(adj & bing[0])) {
           possibles += ({ bits[bing[1]] });
        }
     }
  }
  return possibles;
}
string *query_possible_plural_bits( string word ) {
  string* str_bits;
  string* adj;
  string *possibles;
  mixed* bing;
  fixup_bits();
  str_bits = explode(word, " ");
  possibles = ({ });
  if (_fixed_bits[str_bits[<1]]) {
     adj = str_bits[0..<2];
     foreach (bing in _fixed_bits[str_bits[<1]]) {
        if (bing[2] &&
            sizeof(adj) == sizeof(adj & bing[0])) {
           possibles += ({ bits[bing[1]] });
        }
     }
  }
  return possibles;
}
void add_bit( string bit_short, string bit_name, mixed *bit_array ) {
   int i;
   i = member_array( bit_short, bits );
   if ( !( i % 3 ) ) {
      bits[ i ] = bit_short;
      bits[ i + 1 ] = bit_name;
      bits[ i + 2 ] = bit_array;
      return;
   }
   bits += ({ bit_short, bit_name, bit_array });
}
void remove_bit( string word ) {
   int i;
   i = member_array( word, bits );
   if ( ( i == -1 ) || ( i % 3 ) ) {
      return;
   }
   bits = delete( bits, i, 3 );
}
int modifier( int number ) {
   return ( number * ( roll_MdN( 20, 21 ) - 220 ) ) / 2000;
}
void start_player( object thing ) {
   if ( !thing->query_base_weight() ) {
      thing->set_base_weight( 1 + weight + modifier( weight ) );
   }
   if ( !thing->query_height() ) {
      thing->set_height( 1 + height + modifier( height ) );
   }
   thing->adjust_bonus_con( stats[ 0 ] );
   thing->adjust_bonus_dex( stats[ 1 ] );
   thing->adjust_bonus_int( stats[ 2 ] );
   thing->adjust_bonus_str( stats[ 3 ] );
   thing->adjust_bonus_wis( stats[ 4 ] );
   thing->reset_all();
   if ( skin ) {
      thing->set_skin( skin );
   }
}
int query_number_worn( string type ) {
   switch ( type ) {
      case "armband" :
         return 2;
      case "badge" :
         return 15;
      case "bracelet" :
         return 4;
      case "earring" :
        return 2;
      case "garter" :
         return 2;
      case "shoulder" :
         return 2;
      case "necklace" :
         return 5;
      case "ring" :
         return 8;
      case "sash" :
         return 2;
      case "shirt" :
         return 2;
      case "belt scabbard" :
         return 2;
      case "small scabbard" :
         return 2;
      case "bandaid" :
         return 5;
      default :
         return 1;
   }
}
int query_number_wielded( string type ) { return 1; }
int query_skill_bonus( int number, string word ) { return 0; }
int player_start( object thing ) { return 1; }
int player_quit( object thing ) { return 1; }
void set_level( object thing, int level ) {
   int i;
   if ( !thing ) {
      return;
   }
   for ( i = sizeof( acs ) - 3; i > -1; i -= 3 ) {
      thing->add_ac( acs[ i ], acs[ i + 1 ], acs[ i + 2 ] );
   }
}
int *calc_attack( int *data, int number ) {
   int base;
   int num;
   int rand;
   int rating;
   int scale;
   base =  data[ 0 ] * ( BASE + SCALE * number );
   num = data[ 1 ];
   rand = data[ 2 ] * ( BASE + SCALE * number );
   rating = QUEST_AVE * ( base + num * rand ) +
         QUEST_MAX * ( base + ( num * ( 1 + rand ) ) / 2 );
   scale = BASE + SCALE * NORM;
   rating /= scale;
   rating = ( ( BASE + SCALE * EXPERT ) * rating + QUEST_AVE * QUEST_MAX ) /
         ( 2 * QUEST_AVE * QUEST_MAX );
   if ( rating > scale ) {
      scale = ( rating + scale ) / 2;
   }
   return ({ base / scale, num, rand / scale });
}
void set_unarmed_attacks( object thing ) {
   int i, number;
   number = (int)thing->query_skill_bonus( "fighting.combat.melee.unarmed" );
   number = sqrt( number );
   for ( i = sizeof( attacks ) - 3; i > -1; i -= 3 ) {
      thing->remove_attack( attacks[ i ] );
      thing->add_attack( attacks[ i ], attacks[ i + 1 ],
            calc_attack( attacks[ i + 2 ], number ), A_TYPES[ attacks[ i ] ],
            "unarmed", "unarmed_"+ attacks[ i ] );
   }
}
int query_eat( string bit ) {
  if (member_array( bit, inedible) == -1) {
    return 1;
  }
  return 0;
}
int query_unrottable( string bit ) {
  if (member_array( bit, unrottable) == -1) {
    return 0;
  }
  return 1;
}
int query_pluckable( string bit ) {
  if (member_array( bit, pluckable) == -1) {
    return 0;
  }
  return 1;
}
string *query_all_inedible() {
   return inedible;
}
string *query_all_unrottable() {
   return unrottable;
}
string *query_all_pluckable() {
   return pluckable;
}
string *query_target_zones() {
  return ({ "head", "head", "neck",
              "chest", "back", "back", "back", "lower back",
              "left front leg", "left front leg",
              "stomach", "stomach",
              "right front leg", "right front leg",
              "left rear leg", "left rear leg",
              "right rear leg", "right rear leg",});
}
string map_target_zone(string zone) {
  switch(zone) {
  case "abdomen":
    return "stomach";
  case "hands":
  case "arms":
    return (random(2) ? "left " : "right ") + "front leg";
  case "feet":
  case "legs":
    return (random(2) ? "left " : "right ") + "rear leg";
  default:
    return zone;
  }
}
string map_armour_zone(string zone) {
  switch(zone) {
  case "thorax":
  case "body":
  case "breast":
  case "trunk":
    return "chest";
  case "tail":
    return "back";
  case "stomach":
    return "abdomen";
  case "left arm":
  case "right arm":
  case "left front leg":
  case "right front leg":
  case "left petral fin":
  case "right petral fin":
  case "left wing":
  case "right wing":
  case "branches":
    return "arms";
  case "left hand":
  case "right hand":
  case "left middle leg":
  case "right middle leg":
  case "left front paw":
  case "right front paw":
    return "hands";
  case "left leg":
  case "right leg":
  case "left back leg":
  case "right back leg":
  case "left rear leg":
  case "right rear leg":
  case "dorsal fin":
    return "legs";
  case "left foot":
  case "right foot":
  case "left rear paw":
  case "left rear paw":
  case "left rear foot":
  case "left rear foot":
  case "left claw":
  case "right claw":
  case "root":
    return "feet";
  default:
    return zone;
  }
}