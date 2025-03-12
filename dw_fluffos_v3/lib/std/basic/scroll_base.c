#include <tasks.h>
inherit "/std/basic/scroll_book_react";
#define SKILL "magic.items.scroll"
#define CONTROL_SKILL "magic.spells.special"
private string _spell;
string long( string word, int dark ) {
   int i;
   int j;
   int chance;
   int level;
   int width;
   string spell_name;
   level = 2 * (int)_spell->query_power_level();
   width = sqrt( level );
   chance = (int)this_player()->query_skill_bonus( SKILL ) - ( level - width );
   chance = ( 100 * chance ) / ( 2 * width + 1 );
   spell_name = "$"+ (string)_spell->query_name() +"$";
   j = strlen( spell_name ) - 1;
   for ( i = 1; i < j; i++ ) {
      if ( random( 100 ) > chance ) {
         switch ( spell_name[ i ] ) {
            case 32 :
               break;
            case 65 .. 90 :
               spell_name = spell_name[ 0 .. i - 1 ] +
                     sprintf( "%c", 65 + random( 26 ) ) +
                     spell_name[ i + 1 .. j ];
               break;
            case 97 .. 122 :
               spell_name = spell_name[ 0 .. i - 1 ] +
                     sprintf( "%c", 97 + random( 26 ) ) +
                     spell_name[ i + 1 .. j ];
               break;
            default :
               spell_name = spell_name[ 0 .. i - 1 ] +
                     spell_name[ i + 1 .. j ];
               j--;
         }
      }
   }
   spell_name = spell_name[ 1 .. j - 1 ];
   return spell_name;
}
int query_magic_scroll() { return 1; }
int query_binding_force() { return 5; }
string query_spell() { return _spell; }
int query_spell_power_level() {
   if (_spell) {
      return _spell->query_power_level();
   }
}
void set_spell( string word ) { _spell = word; }
string query_spell_name() { return (string)_spell->query_name(); }
int test_skill() {
   int level;
   level = 2 * (int)( _spell->query_power_level() ) + 1;
   return (int)TASKER->perform_task(this_player(), SKILL, level, TM_FREE);
}
void clear_spell( int award ) {
   if ( award ) {
     write( "%^YELLOW%^"+ ({ "A piece of lore concerning scrolls becomes "
             "clearer for you", "You manage to grasp one of the principles "
             "of magic scrolls more firmly", "A sudden flash of insight "
             "allows you to understand process of casting a spell from a "
             "scroll a little better" })[ random( 3 ) ] +".%^RESET%^\n" );
   }
}
int cast_spell( string words ) {
   int outcome;
   if ( !words ) {
      words = "";
   }
   outcome = test_skill();
   if ( outcome == FAIL ) {
      return notify_fail( "You can't figure out how to use the scroll.\n" );
   }
   if ( !( _spell->cast_spell( words, 1 ) ) ) {
      return 0;
   }
   clear_spell( outcome == AWARD );
   return 1;
}
int cast_spell_new( string words , object* targets, object* using ) {
   int outcome;
   if ( !words ) {
      words = "";
   }
   outcome = test_skill();
   if ( outcome == FAIL ) {
      return notify_fail( "You can't figure out how to use the scroll.\n" );
   }
   if ( !( _spell->cast_spell_new( words, 1, targets, using ) ) ) {
      return 0;
   }
   clear_spell( outcome == AWARD );
   return 1;
}
string query_death_reason() {
   return " a spell going wild and getting out of control.";
}