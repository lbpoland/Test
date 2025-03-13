# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/misc/marry_shadow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.yes_response = ([ "say":({ "yes", "yep", "sure", "ok",
            self.no_response = ([ "say":({ "no", "nope", ({ "won't", "i" }),
            self.local_prop = ([ MARRYPROP : 1, ])


    def add_marry_shadow(self, p: MudObject, m1: MudObject, m2: MudObject) -> MudObject:
            player = p
            marry1 = m1
            marry2 = m2
            askingwho = (string)marry1.query_name()
            asking = ASKFIRST
            tell_object( player, "Now you should ask " +
            (string) marry1.query_short() + " whether " +
            (string) marry1.query_pronoun() + " will marry " +
            (string) marry2.query_short() + "\n")
            return shadow( p, 1 )


    def remove_read_marks(self, str: str) -> str:
            int index, size
            string result
            string temp
            index = 0
            size = strlen(str)
            result = ""
            while (index < size) {
            temp = str[index..index]
            if (((temp >= "a") && (temp <= "z")) ||
            (temp == " ") || (temp == "'")) result += temp
            else result += " "
            index++


    def check_response(self, resptype: str, mess: str) -> None:
            if ( mess && strlen( mess ) ) {
            mess = lower_case( mess )
            mess = remove_read_marks(mess)
            words = explode( mess, " " )
            yes_array = yes_response[ resptype ]
            no_array = no_response[ resptype ]
            response_index = sizeof( yes_array )
            while ( response_index-- ) {
            if ( !stringp( yes_array[ response_index ] ) ) {
            if ( ( member_array( yes_array[ response_index ][ 0 ],
            words ) != -1 ) &&
            ( member_array( yes_array[ response_index ][ 1 ],
            words ) != -1 ) ) {
            do_accept()
            return


    def event_person_say(self, ob: MudObject, start: str, mess: str, lang: str) -> None:
            if ( ob.query_name() == askingwho ) {
            check_response("say", mess)


    def event_person_tell(self, ob: MudObject, start: str, mess: str, lang: str) -> None:
            if ( ob.query_name() == askingwho ) {
            check_response("say", mess)


    def do_accept(self, ) -> None:
            if ( asking == ASKFIRST ) {
            asking = ASKSECOND
            askingwho = (string) marry2.query_name()
            await  player.send((string) marry1.query_pronoun() +
            " accepted. Now you should ask " +
            (string) marry2.query_short() + " whether " +
            (string) marry2.query_pronoun() + " will marry " +
            (string) marry1.query_short() + "\n" )
            await  marry1.send("You accepted.\n" )
            } else if ( asking == ASKSECOND ) {
            asking = DONEASK
            askingwho = "*NoOne*"
            await  player.send((string) marry2.query_pronoun() +
            " accepted. Now you can ask if there are any objections or" +
            " you can finalize the wedding with 'marry them'.\n" )
            await  marry2.send("You accepted.\n" )
            } else {
            tell_object( player, "Something is wrong here, please tell Olorin " +
            "what you where doing.\n" )
            #ifdef LOG
            unguarded((: write_file, LOG ,
            "marry_error "+
            "in accept:" + asking + ";" + askingwho + "(" +
            (string) marry1.query_short() + " to " +
            (string) marry2.query_short() + ")" :))
            #endif
            asyncio.create_task(self. "remove_propose_shadow", 0 )


    def do_refuse(self, ) -> None:
            if ( asking == ASKFIRST ) {
            await  player.send((string) marry1.query_pronoun() +
            " wimpied out.\n" )
            await  marry1.send("You refused, the marriage is off.\n" )
            } else if ( asking == ASKSECOND ) {
            await  player .send((string) marry2.query_pronoun() +
            " wimpied out.\nYou'd better try to console " +
            (string) marry1.query_short() + "\n" )
            tell_object( marry2, "You refused, how will you explain that to "+
            (string) marry1.query_short() + ".\n" )
            } else {
            tell_object( player, "Something is wrong here, please tell Olorin " +
            "what you where doing.\n" )
            #ifdef LOG
            unguarded((: write_file, LOG ,
            "marry_error"+
            "in refuse:" + asking + ";" + askingwho + "(" +
            (string) marry1.query_short() + " to " +
            (string) marry2.query_short() + ")" :))
            #endif


    def query_property(self, str: str) -> Any:
            if ( str == MARRYPROP ) {
            return 1
            } else {
            return player.query_property( str )


    def do_wedding(self, ) -> int:
            if ( environment( player ) == environment( marry1 ) ) {
            if ( environment( player ) == environment( marry2 ) ) {
            marry1.add_property( "spouse", marry2->query_name() )
            marry2.add_property( "spouse", marry1->query_name() )
            ring1 = clone_object( RING )
            ring1.set_owner( marry1->query_short() )
            ring1.set_giver( marry2->query_short() )
            ring1.move( marry1 )
            ring2 = clone_object( RING )
            ring2.set_owner( marry2->query_short() )
            ring2.set_giver( marry1->query_short() )
            ring2.move( marry2 )
            await  player.send("They are now married, you'd better tell them.\n" )
            asyncio.create_task(self. "remove_marry_shadow", 0 )
            return 1
            } else {
            await  player.send(marry2.query_short() +
            " seems to have wandered off.\n" +
            "Perhaps you should try to console " +
            (string) marry1.query_short() + "\n" )


    def abort_wedding(self, ) -> int:
            asyncio.create_task(self. "remove_marry_shadow", 0 )
            return 0


    def remove_marry_shadow(self, ) -> None:
            destruct( self )
            return



class Marry_shadow(MudObject):

    yes_response = '([ "say":({ "yes", "yep", "sure", "ok",'

    no_response = '([ "say":({ "no", "nope", ({ "won\'t", "i" }),'

    local_prop = '([ MARRYPROP : 1, ])'
