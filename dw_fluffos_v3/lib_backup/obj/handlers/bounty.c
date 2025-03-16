#include <money.h>
#define SAVE_FILE "/save/bounty"
#define EXPIRY 60 * 60 * 8 * 60
#define BASE 40000
#define TAXES 60
#define LOGIN "/secure/login"
class bounty {
   string short;
   string *victims;
   int value;
   int active;
   int time;
}
mapping bounty, collect;
void create() {
   bounty  = ([ ]);
   collect = ([ ]);
   seteuid( "Room" );
   if ( file_size( SAVE_FILE +".o" ) > 0 )
      unguarded( (: restore_object, SAVE_FILE :) );
   call_out( "tidy_bounties", 120 );
}
void save_file() { unguarded( (: save_object, SAVE_FILE :) ); }
void delete_bounty( string word ) {
   map_delete( bounty, word );
   save_file();
}
void tidy_bounties() {
   int now = time();
   string word;
   object thing;
   class bounty record;
   foreach ( word, record in bounty ) {
      if ( LOGIN->test_creator( word ) ) {
         log_file( "BOUNTY", "%s: bounty removed from %s (creator)\n",
               ctime( now ), word );
         map_delete( bounty, word );
         continue;
      }
      if (record && record->time + EXPIRY < now ) {
         if (record->active )
            log_file( "BOUNTY", "%s: bounty on %s of %d expired\n",
                  ctime( now ), word, record->value );
         else
            log_file( "BOUNTY", "%s: inactive bounty on %s cancelled\n",
                  ctime( now ), word );
         thing = find_player( word );
         if ( objectp( thing ) )
            tell_object( thing, "You feel that there is no longer "
                  "a price on your head.\n" );
         map_delete( bounty, word );
         continue;
      }
   }
   foreach ( word, record in collect )
      if ( !LOGIN->test_user( word ) ) {
         map_delete( collect, word );
         continue;
      }
      if (record && record->time + EXPIRY < now ) {
         log_file( "BOUNTY", "%s: bounty of %d owed to %s expired\n",
               ctime( now ), record->value, word );
         thing = find_player( word );
         if ( objectp( thing ) )
            tell_object( thing, "You have the funniest feeling that "
                  "you just let a lot of money get away.\n" );
         map_delete( collect, word );
      }
   save_file();
}
void clear_bounties() {
   if ( !master()->high_programmer( geteuid( this_player( 1 ) ) ) )
      return 0;
   bounty  = ([ ]);
   collect = ([ ]);
   save_file();
}
void dest_me() { destruct( this_object() ); }
void register_kill( object victim, object *attackers ) {
   int now, reward;
   string killed, killer, *killers;
   object thing;
   class bounty record;
   if ( member_array( victim, attackers ) != -1 )
      return;
   if ( victim->query_creator() || victim->query_property( "no bounties" ) )
      return;
   if ( !environment( victim ) )
      return;
   if ( environment( victim )->query_property( "bar brawling" ) )
      return;
   now = time();
   killed = (string)victim->query_short();
   if ( undefinedp( bounty[ lower_case( killed ) ] ) ) {
      return;
      foreach ( thing in attackers ) {
         if ( !objectp( thing ) )
            continue;
         if ( thing->query_creator() )
            continue;
         if ( !userp( thing ) && !thing->query_property( "unique" ) )
            continue;
         if ( ( (object)thing->query_property( "inhumer" ) == victim ) &&
               ( (object)victim->query_property( "inhumee" ) == thing ) )
            continue;
         killer = (string)thing->query_short();
         if ( undefinedp( bounty[ lower_case( killer ) ] ) ) {
            record = new( class bounty );
            bounty[ lower_case( killer ) ] = record;
            record->short = killer;
            record->victims = ({ killed });
         } else {
            record = (class bounty)bounty[ lower_case( killer ) ];
            if ( strsrch( lower_case( killed ),
                  lower_case( implode( record->victims, ", " ) ) ) == -1 )
               record->victims += ({ killed });
         }
         record->time = now;
         if ( record->active ) {
            record->value = sizeof( record->victims ) * BASE;
            if ( sizeof( record->victims ) > 1 )
               call_out( "inform_bounty", 30, thing );
         }
      }
      save_file();
      return;
   }
   if ( !( ( (class bounty)bounty[ lower_case( killed ) ] )->active ) )
      return;
   killers = ({ });
   foreach ( thing in attackers ) {
      if ( !objectp( thing ) )
         continue;
      if ( thing->query_creator() )
         continue;
      if ( !userp( thing ) && !thing->query_property( "unique" ) &&
            !thing->query_property( "bounty hunter" ) )
         continue;
      killer = (string)thing->query_short();
      killers += ({ killer });
      call_out( "well_done", 30, thing, (string)victim->query_gender() );
   }
   if ( sizeof( killers ) ) {
      reward = ( (class bounty)bounty[ lower_case( killed ) ] )->value /
            sizeof( killers );
      foreach ( killer in killers ) {
         if ( !undefinedp( bounty[ lower_case( killer ) ] ) )
            continue;
         if ( undefinedp( collect[ lower_case( killer ) ] ) ) {
            record = new( class bounty );
            collect[ lower_case( killer ) ] = record;
            record->short = killer;
            record->victims = ({ killed });
         } else {
            record = (class bounty)collect[ lower_case( killer ) ];
            record->victims += ({ killed });
         }
         record->time = now;
         record->value += reward;
      }
      log_file( "BOUNTY", "%s: bounty on %s fulfilled by %s\n",
            ctime( now ), lower_case( killed ),
            query_multiple_short( map_array( killers,
            (: lower_case( $1 ) :) ) ) );
      map_delete( bounty, lower_case( killed ) );
   }
   save_file();
}
void inform_bounty( object thing ) {
   if ( !thing )
      return;
   if ( !userp( thing ) )
      return;
   tell_object( thing, "You feel the price on your head rise.\n" );
}
void well_done( object thing, int gender ) {
   if ( !thing )
      return;
   if ( !userp( thing ) )
      return;
   tell_object( thing, "You feel good about killing a wanted "+
         ({ "creature", "man", "woman" })[gender] +".\n" );
}
string report_murder( string killer ) {
   string place;
   class bounty record;
   if ( undefinedp( bounty[ lower_case( killer ) ] ) )
      return "According to the records, \""+ killer +
            "\" has never killed anyone.";
   killer = lower_case( killer );
   record = (class bounty)bounty[ killer ];
   if ( record->active ) {
      place = (string)environment( this_player() )->query_property( "place" );
      if ( !place || ( place == "" ) )
         place = "default";
      return "There is already a bounty of "+
            (string)MONEY_HAND->money_value_string( record->value, place ) +
            " offered for the death of "+ record->short +".";
   }
   record->active = 1;
   record->value = sizeof( record->victims ) * BASE;
   call_out( "issue_warrant", 30, killer );
   save_file();
   if ( strsrch( lower_case( (string)this_player()->query_short() ),
         lower_case( implode( record->victims, ", " ) ) ) == -1 )
      return "Ah, a concerned citizen reporting a murder.  I'll issue "
            "a bounty notice for "+ record->short +" right away.";
   return "I'm sorry to hear that "+ record->short +" caused you "
         "harm.  I'll issue a bounty notice right away.";
}
void issue_warrant( string killer ) {
   object thing;
   thing = find_player( killer );
   if ( !thing )
      return;
   if ( !userp( thing ) )
      return;
   thing->remove_hide_invis( "hide" );
   tell_room( environment( thing ), "There is a small unspectacular flash "
         "of light and a small orange imp appears.  It promptly informs "+
         (string)thing->the_short() +" that a bounty has been placed on "+
         (string)thing->query_possessive() +" head.  The imp bows deeply, "
         " smiles evilly, and vanishes in an equally unspectacular flash "
         "of light.\n", thing );
   tell_object( thing, "There is a small unspectacular flash of light and "
         "a small orange imp appears.  It promptly informs you that a bounty "
         "has been placed on your head.  The imp bows deeply, smiles evilly, "
         "and vanishes in an equally unspectacular flash of light.\n" );
}
string collect_bounty() {
   int money;
   string collector, place;
   class bounty record;
   collector = lower_case( (string)this_player()->query_short() );
   if ( undefinedp( collect[ collector ] ) )
      return "According to the records, you've done nothing "
            "to deserve a bounty.";
   record = (class bounty)collect[ collector ];
   money = ( record->value * ( 100 - TAXES ) ) / 100;
   place = (string)environment( this_player() )->query_property( "place" );
   if ( !place || ( place == "" ) )
      place = "default";
   this_player()->adjust_money( (mixed *)MONEY_HAND->create_money_array( money,
         place ) );
   this_player()->set_title( "bounty", "Bounty Hunter" );
   map_delete( collect, collector );
   save_file();
   return "Ah yes, let's see.  Monies owed to you total "+
         (string)MONEY_HAND->money_value_string( record->value, place ) +
         ", minus death tax, inheritance tax, income tax, pension fund "
         "contribution, union dues, VAT, Save the Womble donations and "
         "administrative charges, which leaves you with the grand sum of "+
         (string)MONEY_HAND->money_value_string( money, place ) +
         ".  Nice doing business with you.";
}
int query_bounty( string word ) { return !undefinedp( bounty[ word ] ); }
int query_bounty_value( string word ) {
   if ( undefinedp( bounty[ word ] ) )
      return 0;
   return ( (class bounty)bounty[ word ] )->value;
}
string query_all_bounties() {
   int cre;
   string list, word, place;
   class bounty record;
   cre = (int)this_player( 1 )->query_creator();
   if ( !sizeof( bounty ) )
      return "There are no bounties currently offered.\n";
   place = (string)environment( this_player() )->query_property( "place" );
   if ( !place || ( place == "" ) )
      place = "default";
   list = "";
   foreach ( word, record in bounty )
      if ( record->active ) {
         list += sprintf( " -   %-15s for %s\n", record->short,
               (string)MONEY_HAND->money_value_string( record->value,
               place ) );
         if ( cre )
            list += sprintf( "               %-#60s\n               %s\n",
                  implode( record->victims, "\n" ),
                  ctime( record->time + EXPIRY ) );
      } else
         if ( cre )
            list += sprintf( " -   %-15s (inactive)\n"
                  "               %-#60s\n               %s\n",
                  record->short, implode( record->victims, "\n" ),
                  ctime( record->time + EXPIRY ) );
   if ( list == "" )
      return "There are no bounties currently offered.\n";
   return "The following bounters are currently offered:\n"+ list;
}
string query_all_collectors() {
   string list, word, place;
   class bounty record;
   if ( !sizeof( collect ) )
      return "There are no bounties awaiting collection.\n";
   place = (string)environment( this_player() )->query_property( "place" );
   if ( !place || ( place == "" ) )
      place = "default";
   list = "";
   foreach ( word, record in collect )
         list += sprintf( " -   %-15s owed %s\n               %s\n",
               record->short,
               (string)MONEY_HAND->money_value_string( record->value, place ),
               ctime( record->time + EXPIRY ) );
   return "The following bounties are awaiting collection:\n"+ list;
}
string query_bounty_info( string word ) {
   string place;
   class bounty record;
   place = (string)environment( this_player() )->query_property( "place" );
   if ( !place || ( place == "" ) )
      place = "default";
   if ( undefinedp( bounty[ word ] ) )
      return 0;
   record = (class bounty)bounty[ word ];
   if ( !record->active )
      return 0;
   return "A bounty of "+
         (string)MONEY_HAND->money_value_string( record->value, place ) +
         " is offered for the death of "+ record->short +" for the murder of "+
         query_multiple_short( record->victims ) +".\n";
}