#include <move_failures.h>
#include <skills.h>
#include <living.h>
#include <config.h>
#define BASE 20
#define ORD1T 1
#define ORD1B 1
#define ORD2T 1
#define ORD2B 5
#define SCALING_DATA ({ 650, 150, 10, 5 })
#define DIVISOR 700
#define DEATH_WAIT_TIME 5
#define INIT_GP_INC -20
int Con, Dex, Int, Str, Wis,
    contmp, dextmp, inttmp, strtmp, wistmp,
    height, base_weight;
nosave int conbon, dexbon, intbon, strbon, wisbon, no_check;
nosave string to_zap;
nosave int gp_inc = INIT_GP_INC, hp_inc;
mixed query_property(string name);
string stats_to_zap() {
   string temp;
   temp = to_zap;
   to_zap = 0;
   return temp;
}
void zap_stat( string word ) {
   string dummy;
   if ( !to_zap ) {
      to_zap = word;
      if ( find_call_out( "zap_stat_cache" ) == -1 )
         call_out( "zap_stat_cache", 1 );
   }
   if ( sscanf( to_zap, "%s"+ word +"%s", dummy, dummy ) != 2 )
      to_zap += word;
}
int query_no_check() { return no_check; }
void set_no_check( int i ) { no_check = i; }
int hp_base() {
  int base;
  base = 150 + 10 * (int)this_object()->query_con();
  if ( base < 5 ) base = 5;
  return base;
}
int hp_gradient() { return 4; }
int scaled_weight() {
  int i, actual, scaled;
  actual = (int)this_object()->query_weight(1);
  if ( actual < SCALING_DATA[ 0 ] )
    return actual;
  scaled += SCALING_DATA[ 0 ];
  actual -= SCALING_DATA[ 0 ];
  i = 1;
  while ( actual && ( ( i * SCALING_DATA[ 2 ] ) < 100 ) ) {
    if ( actual >= SCALING_DATA[ 1 ] ) {
      scaled += ( ( 100 - SCALING_DATA[ 2 ] * i ) * SCALING_DATA[ 1 ] )
          / 100;
      scaled += ( SCALING_DATA[ 3 ] * SCALING_DATA[ 1 ] ) / 1000;
      actual -= SCALING_DATA[ 1 ];
    } else {
      scaled += ( ( 100 - SCALING_DATA[ 2 ] * i ) * actual ) / 100;
      scaled += ( SCALING_DATA[ 3 ] * actual ) / 1000;
      actual = 0;
    }
    i += 1;
  }
  if ( actual )
    scaled += ( SCALING_DATA[ 3 ] * actual ) / 1000;
  return scaled;
}
void reset_hp() {
  int new_max, skill_bon;
  string report;
  if ( no_check )
    return;
  skill_bon = (int)this_object()->query_skill_bonus( "other.health" );
  new_max = hp_base() + skill_bon * hp_gradient();
  if ( !base_weight ) {
    if ( (string)this_object()->query_name() == "object" )
      return;
    report = file_name( this_object() ) +" ("+
        (string)this_object()->query_name() +"): race object is "+
        (string)this_object()->query_race_ob();
    if ( environment() ) {
      if ( file_name( environment() ) == "/room/void" )
        return;
      report += "; in "+ file_name( environment() );
      this_object()->move( "/room/void", "$N gets booted into the void for "+
          "being a bad NPC." );
    }
    report += ".\n";
    log_file( "BAD_NPC", ctime(time()) + " " + report );
    return;
  }
   new_max = ( new_max * scaled_weight() ) / DIVISOR;
   if ( new_max < 1 )
      this_object()->set_max_hp( 1 );
   else
      this_object()->set_max_hp( new_max );
}
void reset_gp() {
   string guild_ob;
   if ( no_check )
      return;
   guild_ob = (string)this_object()->query_guild_ob();
   if (!guild_ob) {
      guild_ob = query_property("backup guild");
   }
   if ( !guild_ob ) {
      this_object()->set_max_gp( 50 +
            (int)this_object()->query_skill_bonus( "other.points" ) );
   } else {
      guild_ob->set_gp( this_object() );
   }
}
void calc_inc_rates() {
   string guild_ob;
   hp_inc = sqrt((int)this_object()->stat_modify(100, "other.health")) - 7;
   guild_ob = (string)this_object()->query_guild_ob();
   if ( !guild_ob ) {
     guild_ob = query_property("backup guild");
     if (!guild_ob) {
       guild_ob = CONFIG_DEFAULT_GUILD;
     }
   }
   gp_inc = sqrt((int)this_object()->stat_modify(100,
         (string)guild_ob->query_gp_skill())) - 7;
   if(hp_inc < 0) {
     hp_inc = 0;
   }
   if(gp_inc < 0) {
     gp_inc = 0;
   }
}
int *query_inc_rates() { return ({ gp_inc, hp_inc }); }
void heart_beat() {
   int hp;
   int calling_death;
   hp = this_object()->query_hp();
   if ( hp < 0 ) {
       calling_death = this_object()->query_callingdeath();
        if ( calling_death ) {
           if ( time() > calling_death + DEATH_WAIT_TIME ) {
                this_object()->do_death();
            }
        } else {
            this_object()->do_death();
        }
   }
   else {
      if ( gp_inc == INIT_GP_INC ) {
         calc_inc_rates();
      }
      this_object()->adjust_gp( gp_inc );
      this_object()->adjust_hp( hp_inc );
   }
}
void reset_carry_cap() {
   int i, hst_num, hst_wei, new_cap, old_loc, tot_str;
   object *contents, *dropped;
   if ( no_check ) return;
   old_loc = (int)this_object()->query_loc_weight();
   tot_str = Str + strtmp + strbon;
   new_cap = BASE;
   new_cap += ( ORD1T * tot_str ) / ORD1B;
   new_cap += ( ORD2T * tot_str * tot_str ) / ORD2B;
   new_cap = ( new_cap * (int)this_object()->query_weight(1) ) / 100;
   if ( !new_cap )
      new_cap = 1;
   this_object()->set_max_weight( new_cap );
   if ( new_cap >= old_loc ) return;
   this_object()->dest_hide_shadow();
   contents = all_inventory( this_object() ) -
      (object *)this_object()->query_armours();
   dropped = ({ });
   while ( ( old_loc > new_cap ) && sizeof( contents ) ) {
      hst_num = 0;
      hst_wei = 0;
      for ( i = 0; i < sizeof( contents ); i++ )
         if ( (int)contents[ i ]->query_complete_weight() > hst_wei ) {
            hst_wei = (int)contents[ i ]->query_complete_weight();
            hst_num = i;
         }
      if ( (int)contents[ hst_num ]->move( environment() ) == MOVE_OK ) {
         dropped += ({ contents[ hst_num ] });
         old_loc -= hst_wei;
      }
      contents = delete( contents, hst_num, 1 );
   }
   if ( sizeof( dropped ) ) {
      tell_room( environment(), capitalize( (string)this_object()->short() ) +
                " drops "+ query_multiple_short( dropped ) +" under strain.\n",
                this_object() );
      tell_object( this_object(), "Your fading strength makes you drop "+
                  query_multiple_short( dropped ) +".\n" );
   }
   this_object()->update_loc_weight();
   this_object()->calc_burden();
   if ( new_cap >= old_loc ) return;
   return;
}
void check_stats_zero() {
   if ( Int + inttmp + intbon <= 0 ||
        Wis + wistmp + wisbon <= 0 ) {
      this_object()->add_property( PASSED_OUT, 1, 500 );
      tell_object( this_object(), "You fall asleep.\n" );
   }
}
void reset_all() { zap_stat( "CDISW" ); }
void reset_all2() {
   no_check = 0;
   reset_hp();
   reset_gp();
   reset_carry_cap();
   calc_inc_rates();
   check_stats_zero();
   this_object()->do_burden_call();
}
int query_con() { return Con + contmp + conbon; }
int query_dex() { return Dex + dextmp + dexbon; }
int query_int() { return Int + inttmp + intbon; }
int query_str() { return Str + strtmp + strbon; }
int query_wis() { return Wis + wistmp + wisbon; }
int query_real_con() { return Con; }
int query_real_dex() { return Dex; }
int query_real_int() { return Int; }
int query_real_str() { return Str; }
int query_real_wis() { return Wis; }
int check( int number ) { return ( number <= 28 ); }
int set_con( int number ) {
  if ( !check( number ) ) number = 28;
  if ( Con != number )
    zap_stat( "C" );
  Con = number;
  return Con;
}
int set_dex( int number ) {
  if ( !check( number ) ) number = 28;
  if ( Dex != number )
    zap_stat( "D" );
  Dex = number;
  return Dex;
}
int set_int( int number ) {
  if ( !check( number ) ) number = 28;
  if ( Int != number )
    zap_stat( "I" );
  Int = number;
  return Int;
}
int set_str( int number ) {
  if ( !check( number ) ) number = 28;
  if ( Str != number )
    zap_stat( "S" );
  Str = number;
  return Str;
}
int set_wis( int number ) {
  if ( !check( number ) ) number = 28;
  if ( Wis != number )
    zap_stat( "W" );
  Wis = number;
  return Wis;
}
int adjust_con( int number ) {
  if ( check( number + Con ) ) {
    Con += number;
    if ( number )
      zap_stat( "C" );
  }
  return Con;
}
int adjust_dex( int number ) {
  if ( check( number + Dex ) ) {
    Dex += number;
    if ( number )
      zap_stat( "D" );
  }
  return Dex;
}
int adjust_int( int number ) {
  if ( check( number + Int ) ) {
    Int += number;
    if ( number )
      zap_stat( "I" );
  }
  return Int;
}
int adjust_str( int number ) {
  if ( check( number + Str ) ) {
    Str += number;
    if ( number )
      zap_stat( "S" );
  }
  return Str;
}
int adjust_wis( int number ) {
  if ( check( number + Wis ) ) {
    Wis += number;
    if ( number )
      zap_stat( "W" );
  }
  return Wis;
}
int query_tmp_con() { return contmp; }
int query_tmp_dex() { return dextmp; }
int query_tmp_int() { return inttmp; }
int query_tmp_str() { return strtmp; }
int query_tmp_wis() { return wistmp; }
int adjust_tmp_con( int number ) {
  contmp += number;
  if ( number )
    zap_stat( "C" );
   if ( contmp && !dextmp && !inttmp && !strtmp && !wistmp )
      call_out( "update_tmps", 900 );
  return contmp;
}
int adjust_tmp_dex( int number ) {
  dextmp += number;
  if ( number )
    zap_stat( "D" );
   if ( !contmp && dextmp && !inttmp && !strtmp && !wistmp )
      call_out( "update_tmps", 900 );
  return dextmp;
}
int adjust_tmp_int( int number ) {
  inttmp += number;
  if ( number )
    zap_stat( "I" );
   if ( !contmp && !dextmp && inttmp && !strtmp && !wistmp )
      call_out( "update_tmps", 900 );
  return inttmp;
}
int adjust_tmp_str( int number ) {
  strtmp += number;
  if ( number )
    zap_stat( "S" );
   if ( !contmp && !dextmp && !inttmp && strtmp && !wistmp )
      call_out( "update_tmps", 900 );
  return strtmp;
}
int adjust_tmp_wis( int number ) {
  wistmp += number;
  if ( number )
    zap_stat( "W" );
   if ( !contmp && !dextmp && !inttmp && !strtmp && wistmp )
      call_out( "update_tmps", 900 );
  return wistmp;
}
int query_bonus_con() { return conbon; }
int query_bonus_dex() { return dexbon; }
int query_bonus_int() { return intbon; }
int query_bonus_str() { return strbon; }
int query_bonus_wis() { return wisbon; }
int adjust_bonus_con( int number ) {
  conbon += number;
  if ( number )
    zap_stat( "C" );
  return conbon;
}
int adjust_bonus_dex( int number ) {
  dexbon += number;
  if ( number )
    zap_stat( "D" );
  return dexbon;
}
int adjust_bonus_int( int number ) {
  intbon += number;
  if ( number )
    zap_stat( "I" );
  return intbon;
}
int adjust_bonus_str( int number ) {
  strbon += number;
  if ( number )
    zap_stat( "S" );
  return strbon;
}
int adjust_bonus_wis( int number ) {
  wisbon += number;
  if ( number )
    zap_stat( "W" );
  return wisbon;
}
void update_tmps() {
  if ( contmp ) {
    zap_stat( "C" );
    contmp = contmp / 2;
  }
  if ( dextmp ) {
    zap_stat( "D" );
    dextmp = dextmp / 2;
  }
  if ( inttmp ) {
    zap_stat( "I" );
    inttmp = inttmp / 2;
  }
  if ( strtmp ) {
    zap_stat( "S" );
    strtmp = strtmp / 2;
  }
  if ( wistmp ) {
    zap_stat( "W" );
    wistmp = wistmp / 2;
  }
   if ( contmp || dextmp || inttmp || strtmp || wistmp )
      call_out( "update_tmps", 900 );
}
int query_height() { return height; }
void set_height( int number ) {
  if ( number > 0 ) height = number;
}
int query_base_weight() { return base_weight; }
void set_base_weight( int number ) {
   if ( number > 0 )
      base_weight = number;
}
int query_weight(int) {
  int adjust_weight;
  adjust_weight = ( ( ( Con + 3 * Str ) / 4 ) - 13 ) * ( base_weight / 30 );
  return base_weight + adjust_weight;
}
mixed *stats() {
  return ({
    ({ "Con", Con + conbon + contmp }),
    ({ "Dex", Dex + dexbon + dextmp }),
    ({ "Int", Int + intbon + inttmp }),
    ({ "Str", Str + strbon + strtmp }),
    ({ "Wis", Wis + wisbon + wistmp }),
    ({ "tmp Con", contmp }),
    ({ "tmp Dex", dextmp }),
    ({ "tmp Int", inttmp }),
    ({ "tmp Str", strtmp }),
    ({ "tmp Wis", wistmp }),
    ({ "bonus Con", conbon }),
    ({ "bonus Dex", dexbon }),
    ({ "bonus Int", intbon }),
    ({ "bonus Str", strbon }),
    ({ "bonus Wis", wisbon }),
    ({ "hp rate", hp_inc }),
    ({ "gp rate", gp_inc }),
    ({ "height", height }),
  });
}