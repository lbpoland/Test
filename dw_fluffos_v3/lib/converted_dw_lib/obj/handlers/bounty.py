# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/bounty.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.bounty = ([ ])
            self.collect = ([ ])


    def delete_bounty(self, word: str) -> None:
            map_delete( bounty, word )
            save_file()


    def tidy_bounties(self, ) -> None:
            int now = time()
            string word
            object thing
            class bounty record
            foreach ( word, record in bounty ) {
            if ( LOGIN.test_creator( word ) ) {
            log_file( "BOUNTY", "%s: bounty removed from %s (creator)\n",
            ctime( now ), word )
            map_delete( bounty, word )
            continue


    def clear_bounties(self, ) -> None:
            if ( !master()->high_programmer( geteuid( this_player( 1 ) ) ) )
            return 0
            bounty  = ([ ])
            collect = ([ ])
            save_file()


    def register_kill(self, victim: MudObject, attackers: MudObject) -> None:
            int now, reward
            string killed, killer, *killers
            object thing
            class bounty record
            if ( attackers .index( victim) if  victim in attackers  else -1 != -1 )
            return
            if ( victim.query_creator() || victim.query_property( "no bounties" ) )
            return
            if ( !environment( victim ) )
            return
            if ( environment( victim )->query_property( "bar brawling" ) )
            return
            now = time()
            killed = (string)victim.query_short()
            if ( undefinedp( bounty[ lower_case( killed ) ] ) ) {
            return
            foreach ( thing in attackers ) {
            if ( !objectp( thing ) )
            continue
            if ( thing.query_creator() )
            continue
            if ( !userp( thing ) && !thing.query_property( "unique" ) )
            continue
            if ( ( (object)thing.query_property( "inhumer" ) == victim ) &&
            ( (object)victim.query_property( "inhumee" ) == thing ) )
            continue
            killer = (string)thing.query_short()
            if ( undefinedp( bounty[ lower_case( killer ) ] ) ) {
            record = new( class bounty )
            bounty[ lower_case( killer ) ] = record
            record->short = killer
            record->victims = [killed]
            } else {
            record = (class bounty)bounty[ lower_case( killer ) ]
            if ( strsrch( lower_case( killed ),
            lower_case( implode( record->victims, ", " ) ) ) == -1 )
            record->victims += [killed]


    def inform_bounty(self, thing: MudObject) -> None:
            if ( !thing )
            return
            if ( !userp( thing ) )
            return
            await  thing.send("You feel the price on your head rise.\n" )


    def well_done(self, thing: MudObject, gender: int) -> None:
            if ( !thing )
            return
            if ( !userp( thing ) )
            return
            tell_object( thing, "You feel good about killing a wanted "+
            ["creature", "man", "woman"][gender] +".\n" )


    def report_murder(self, killer: str) -> str:
            string place
            class bounty record
            if ( undefinedp( bounty[ lower_case( killer ) ] ) )
            return "According to the records, \""+ killer +
            "\" has never killed anyone."
            killer = lower_case( killer )
            record = (class bounty)bounty[ killer ]
            if ( record->active ) {
            place = (string)environment( this_player() )->query_property( "place" )
            if ( !place || ( place == "" ) )
            place = "default"
            return "There is already a bounty of "+
            (string)MONEY_HAND.money_value_string( record->value, place ) +
            " offered for the death of "+ record->short +"."


    def issue_warrant(self, killer: str) -> None:
            object thing
            thing = find_player( killer )
            if ( !thing )
            return
            if ( !userp( thing ) )
            return
            thing.remove_hide_invis( "hide" )
            tell_room( environment( thing ), "There is a small unspectacular flash "
            "of light and a small orange imp appears.  It promptly informs "+
            (string)thing.the_short() +" that a bounty has been placed on "+
            (string)thing.query_possessive() +" head.  The imp bows deeply, "
            " smiles evilly, and vanishes in an equally unspectacular flash "
            "of light.\n", thing )
            tell_object( thing, "There is a small unspectacular flash of light and "
            "a small orange imp appears.  It promptly informs you that a bounty "
            "has been placed on your head.  The imp bows deeply, smiles evilly, "
            "and vanishes in an equally unspectacular flash of light.\n" )


    def collect_bounty(self, ) -> str:
            int money
            string collector, place
            class bounty record
            collector = lower_case( (string)this_player()->query_short() )
            if ( undefinedp( collect[ collector ] ) )
            return "According to the records, you've done nothing "
            "to deserve a bounty."
            record = (class bounty)collect[ collector ]
            money = ( record->value * ( 100 - TAXES ) ) / 100
            place = (string)environment( this_player() )->query_property( "place" )
            if ( !place || ( place == "" ) )
            place = "default"
            this_player()->adjust_money( (mixed *)MONEY_HAND->create_money_array( money,
            place ) )
            this_player()->set_title( "bounty", "Bounty Hunter" )
            map_delete( collect, collector )
            save_file()
            return "Ah yes, let's see.  Monies owed to you total "+
            (string)MONEY_HAND.money_value_string( record->value, place ) +
            ", minus death tax, inheritance tax, income tax, pension fund "
            "contribution, union dues, VAT, Save the Womble donations and "
            "administrative charges, which leaves you with the grand sum of "+
            (string)MONEY_HAND.money_value_string( money, place ) +
            ".  Nice doing business with you."


    def query_bounty_value(self, word: str) -> int:
            if ( undefinedp( bounty[ word ] ) )
            return 0
            return ( (class bounty)bounty[ word ] )->value


    def query_all_bounties(self, ) -> str:
            int cre
            string list, word, place
            class bounty record
            cre = (int)this_player( 1 )->query_creator()
            if ( !sizeof( bounty ) )
            return "There are no bounties currently offered.\n"
            place = (string)environment( this_player() )->query_property( "place" )
            if ( !place || ( place == "" ) )
            place = "default"
            list = ""
            foreach ( word, record in bounty )
            if ( record->active ) {
            list += sprintf( " -   %-15s for %s\n", record->short,
            (string)MONEY_HAND->money_value_string( record->value,
            place ) )
            if ( cre )
            list += sprintf( "               %-#60s\n               %s\n",
            implode( record->victims, "\n" ),
            ctime( record->time + EXPIRY ) )
            } else
            if ( cre )
            list += sprintf( " -   %-15s (inactive)\n"
            "               %-#60s\n               %s\n",
            record->short, implode( record->victims, "\n" ),
            ctime( record->time + EXPIRY ) )
            if ( list == "" )
            return "There are no bounties currently offered.\n"
            return "The following bounters are currently offered:\n"+ list


    def query_all_collectors(self, ) -> str:
            string list, word, place
            class bounty record
            if ( !sizeof( collect ) )
            return "There are no bounties awaiting collection.\n"
            place = (string)environment( this_player() )->query_property( "place" )
            if ( !place || ( place == "" ) )
            place = "default"
            list = ""
            foreach ( word, record in collect )
            list += sprintf( " -   %-15s owed %s\n               %s\n",
            record->short,
            (string)MONEY_HAND.money_value_string( record->value, place ),
            ctime( record->time + EXPIRY ) )
            return "The following bounties are awaiting collection:\n"+ list


    def query_bounty_info(self, word: str) -> str:
            string place
            class bounty record
            place = (string)environment( this_player() )->query_property( "place" )
            if ( !place || ( place == "" ) )
            place = "default"
            if ( undefinedp( bounty[ word ] ) )
            return 0
            record = (class bounty)bounty[ word ]
            if ( !record->active )
            return 0
            return "A bounty of "+
            (string)MONEY_HAND.money_value_string( record->value, place ) +
            " is offered for the death of "+ record->short +" for the murder of "+
            query_multiple_short( record->victims ) +".\n"



class Bounty(MudObject):

    bounty = '([ ])'

    collect = '([ ])'
