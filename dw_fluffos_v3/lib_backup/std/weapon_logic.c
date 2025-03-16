#include <weapon.h>
nosave string *attack_names;
nosave string *attack_types;
nosave mixed *attack_data;
nosave mapping special_messages;
void create() {
   attack_names = ({ });
   attack_types = ({ });
   attack_data = ({ });
   special_messages = ([ ]);
}
string *query_attack_names() { return copy( attack_names ); }
string *query_attack_types() { return uniq_array( attack_types ); }
mixed *query_attack_data() { return copy( attack_data ); }
mapping query_special_messages() { return copy( special_messages ); }
void add_attack_message(string name, string type, string *data) {
   string nam;
   nam = type;
   if (name) {
      nam += "-" + name;
   }
   special_messages[nam] = data;
}
mixed *query_attack_message(string name, string type) {
   if (special_messages[type + "-" + name]) {
      return special_messages[type + "-" + name];
   }
   if (special_messages[type]) {
     return special_messages[type];
   }
   return 0;
}
varargs int add_attack( string a_name, int chance, int *damage, string type,
      string skill, mixed func, mixed bogus_1, mixed bogus_2 ) {
   if ( stringp( bogus_1 ) ) {
      write( file_name( this_object() ) +" is using the obselete syntax "+
            "of add_attack.\n" );
      return 0;
   }
   if ( member_array( a_name, attack_names ) != -1 )
      return 0;
   attack_names += ({ a_name });
   attack_types += ({ type });
   attack_data += ({ chance, damage, type, skill, func });
   return 1;
}
void remove_attack( string a_name ) {
   int i;
   i = member_array( a_name, attack_names );
   if ( i == -1 )
      return;
   attack_names = delete(attack_names, i, 1);
   attack_types = delete(attack_types, i, 1);
   attack_data = delete( attack_data, i * W_ARRAY_SIZE, W_ARRAY_SIZE );
}
int modify_damage( int damage, string attack_name ) { return damage; }
int calc_attack( int number, int percent ) {
   int damage, *data;
   data = attack_data[ number * W_ARRAY_SIZE + W_DAMAGE ];
   damage = data[ F_FIXED ] + roll_MdN( data[ F_NUM ], data[ F_DIE ] );
   damage = (int)this_object()->modify_damage( damage,
         attack_names[ number ] );
   damage = ( damage * percent ) / 100;
   return damage;
}
mixed *weapon_attacks(int percent, object target ) {
   int i, *order;
   mixed *attacks;
   if ( !percent )
      percent = 100;
   order = ({ });
   for ( i = 0; i < sizeof( attack_names ); i++ )
      order += ({ i });
   order = shuffle( order );
   attacks = ({ });
   for ( i = 0; i < sizeof( order ); i++ ) {
      if ( random( percent ) <
            attack_data[ order[ i ] * W_ARRAY_SIZE + W_CHANCE ] ) {
         attacks += ({ calc_attack( order[ i ], percent ),
               attack_data[ order[ i ] * W_ARRAY_SIZE + W_SKILL ],
               attack_data[ order[ i ] * W_ARRAY_SIZE + W_TYPE ],
               attack_names[ order[ i ] ] });
      }
   }
   return attacks;
}
void attack_function( string a_name, int damage, object attack_ob,
      object attack_by ) {
   int i;
   i = member_array( a_name, attack_names );
   if ( i == -1 ) {
      return;
   }
   i *= W_ARRAY_SIZE;
   if ( !attack_data[ i + W_FUNCTION ] ) {
      return;
   }
   if ( stringp( attack_data[ i + W_FUNCTION ] ) ) {
      call_other( this_object(), attack_data[ i + W_FUNCTION ],
            damage, attack_ob, attack_by, attack_data[ i + W_TYPE ], a_name );
   } else {
      call_other( attack_data[ i + W_FUNCTION ][ 1 ],
            attack_data[ i + W_FUNCTION ][ 0 ], damage, attack_ob, attack_by,
            attack_data[ i + W_TYPE ], a_name );
   }
}
string query_weapon_type() {
   int i;
   string type;
   for ( i = 0; i < sizeof( attack_data ); i += W_ARRAY_SIZE ) {
      if ( !type ) {
         type = attack_data[ i + W_SKILL ];
         continue;
      }
      if ( type != attack_data[ i + W_SKILL ] )
         return "mixed";
   }
   return type;
}
mixed weapon_stats() {
   int i, j;
   string bit;
   mixed *ret;
   ret = ({ });
   for ( i = 0; i < sizeof( attack_data ); i += W_ARRAY_SIZE, j++ ) {
      ret += ({
         ({ "attack #"+ j, attack_names[ j ] }),
         ({ "   chance", attack_data[ i + W_CHANCE ] })
      });
      if ( attack_data[ i + W_DAMAGE ][ F_FIXED ] )
         bit = attack_data[ i + W_DAMAGE ][ F_FIXED ] +"+";
      else
         bit = "";
      if ( attack_data[ i + W_DAMAGE ][ F_NUM ] )
         bit += attack_data[ i + W_DAMAGE ][ F_NUM ] +"d"+
               attack_data[ i + W_DAMAGE ][ F_DIE ];
      else
         if ( attack_data[ i + W_DAMAGE ][ F_DIE ] )
            bit += "1d"+ attack_data[ i + W_DAMAGE ][ F_DIE ];
      ret += ({
         ({ "   damage", bit }),
         ({ "     type", attack_data[ i + W_TYPE ] }),
         ({ "    skill", attack_data[ i + W_SKILL ] })
      });
      if ( stringp( attack_data[ i + W_FUNCTION ] ) )
         ret += ({ ({ " function", attack_data[ i + W_FUNCTION ] }) });
      else
         if ( pointerp( attack_data[ i + W_FUNCTION ] ) )
            ret += ({
               ({ " function", attack_data[ i + W_FUNCTION ][ 0 ] }),
               ({ "called on", attack_data[ i + W_FUNCTION ][ 1 ] })
            });
   }
   return ret;
}
mixed stats() { return weapon_stats(); }