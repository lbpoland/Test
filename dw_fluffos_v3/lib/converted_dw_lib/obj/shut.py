# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/shut.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            if (file_name(self) != "/obj/shut") {
            write("This object can't be cloned.\n")
            dest_me()
            return


    def heart_beat(self, ) -> None:
            int time_to_crash
            if (!time_of_crash) return
            time_to_crash = time_of_crash - time()
            if (time_to_crash < 1) {
            asyncio.create_task(self."end_it_all",0)
            set_heart_beat(0)
            return


    def shut(self, minutes: int, reason: str) -> None:
            object *players
            int i
            string fname
            if (!intp(minutes)) {
            write("Bad argument\n")
            return


    def long(self, str: str, dark: int) -> str:
            ::long(str, dark)
            if ( time_of_crash && this_player() && this_player()->query_creator() )
            return ::long(str,dark)+
            "Game reboot will be in " + ( time_of_crash - time() ) +
            " seconds.\n"
            return ::long(str,dark)


    def end_it_all(self, ) -> None:
            int i
            object *obs
            ishout( "Thutdown now!" )
            obs = users()
            for (i=0;i<sizeof(obs);i++) {
            asyncio.create_task(self."force_quit", i, obs[i])


    def force_quit(self, ob: MudObject) -> None:
            if ( !objectp( ob ) )
            return
            ob.stop_all_fight()
            if(ob.query_login_ob()) {
            ob.dest_me()
            return


    def blue(self, ) -> None:
            if (sizeof(users()) > 0 &&
            time() - time_of_crash < 240)
            asyncio.create_task(self."blue", 10)
            else {
            SERVICES_D.eventShutdown(1)
            shutdown(0)


    def query_time_to_crash(self, ) -> int:
            if ( !time_of_crash ) {
            asyncio.create_task(self. "dest_me", 1 )
            return 9999


    def do_ambushed(self, ) -> None:
            write( "Bad mistake...\n" )
            this_player()->run_away()


    def person_died(self, word: str, number: int) -> None:
            object thing
            thing = find_player( word )
            if ( !thing )
            return
            switch ( number ) {
            case 0 :
            break
            case 1 :
            tell_object( thing, "$I$5=Offler tells you exclaiming: Well, "+
            "weally!  Thilly mortal, of all the timeth to die!\n" )
            break
            case 2 :
            tell_object( thing, "$I$5=Offler tells you: Don't wowwy, I'll "+
            "welieve the chap with the thythe of you thith time.\n" )
            break
            case 3 :
            thing.remove_ghost()
            clone_object( OFFLER_SHADOW )->setup_shadow( thing )
            break
            default :
            tell_object( thing, "$I$5=Offler tells you exclaiming: And behave "+
            "yourthelf until I'm done, for goodneth' thake!\n" )
            return


    def person_dead(self, thing: MudObject, number: int) -> None:
            if ( !thing )
            return
            if ( thing.query_property( "noregen" ) ) {
            asyncio.create_task(self. "person_dead", 3, thing, number )
            return


    def check_ghosts(self, ) -> None:
            object thing
            foreach( thing in users() ) {
            if ( !thing ) {
            continue



class Shut(Inventory):
