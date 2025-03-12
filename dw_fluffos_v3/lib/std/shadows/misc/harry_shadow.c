#include <player.h>
int protecting;
string protector;
object player;
void setup_shadow( object thing, string word ) {
   shadow( thing, 1 );
   player = thing;
   protector = word;
   protecting = 1;
   call_out( "dest_harry_shadow", 60 * 20 );
}
string query_harry_protector() { return protector; }
void dest_harry_shadow() { destruct( this_object() ); }
void zap_harry_shadow() {
   protecting = 0;
   tell_object( player, "You lose "+ protector +"'s protection.\n" );
   call_out( "dest_harry_shadow", 1 );
}
int adjust_hp( int number, object thing, object weapon, string attack ) {
   if ( ( number > 0 ) || !protecting ||
       !thing || !pk_check(thing, player ) || player == this_player() )
      return (int)player->adjust_hp( number, thing, weapon, attack );
   return (int)player->query_hp();
}
int set_hp( int number, object thing ) {
   int current;
   current = (int)player->query_hp();
   if ( ( number > current ) || !protecting || !thing || !thing->query_player_killer() )
      return (int)player->set_hp( number, thing );
   return current;
}
int attack_by( object thing ) {
   if ( !protecting || !thing->query_player_killer( ) )
      return (int)player->attack_by( thing );
   tell_object( thing, (string)player->the_short() +
         " are protected from combat by "+ protector +".\n" );
   tell_object( player, "You are protected from combat by "+
         protector +".\n" );
   thing->stop_fight( player );
   return 0;
}
int attack_ob( object thing ) {
   if ( protecting )
      zap_harry_shadow();
   return (int)player->attack_ob( thing );
}
int query_unambushable() { return 1; }
void do_ambushed() {
   write( protector +" stops you from harming "+
         (string)player->the_short() +".\n" );
   tell_object( player, protector +" stops "+
         (string)this_player()->the_short() +" from harming you.\n" );
}
int no_offense() {
   if ( protecting )
      zap_harry_shadow();
   return (int)player->no_offense();
}
int query_player_killer() {
   return 0;
}
int command_shadowed( string verb, string args ) {
   if ( member_array( verb, ({ "cast", "scathe", "perform" }) ) == -1 )
      return (int)player->command_shadowed( verb, args );
   if ( protecting )
      zap_harry_shadow();
   return (int)player->command_shadowed( verb, args );
}
varargs int adjust_xp( int number, int shared ) {
#ifdef DEBUG
  log_file( "PROTECTED", ctime( time() ) +": "+ (string)player->query_name() +
         " gained "+ number +"xp ["+ implode( map_array( previous_object( -1 ),
         (: file_name( $1 ) :) ), ", " ) +"]\n" );
#endif
   return (int)player->adjust_xp( number, shared );
}
varargs int add_skill_level( string skill, int lvl, mixed exp ) {
   string what;
   if ( !exp )
      exp = previous_object();
   if ( objectp( exp ) )
      what = " from "+ file_name( exp );
   else
      what = " for "+ exp +"xp";
#ifdef DEBUG
   log_file( "PROTECTED", ctime( time() ) +": "+ (string)player->query_name() +
         " gained "+ lvl +" in "+ skill + what +" ["+
         implode( map_array( previous_object( -1 ), (: file_name( $1 ) :) ),
         ", " ) +"]\n" );
#endif
   return (int)player->add_skill_level( skill, lvl, exp );
}