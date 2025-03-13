# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/shut.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            if ( file_name( self ) != "/global/shut" ) {
            write("This object can't be cloned.\n")
            dest_me()
            return


    def ashout(self, words: str) -> None:
            int i
            object *people
            people = users()
            for ( i = 0; i < sizeof( people ); i++ )
            tell_object( people[ i ], "Offler the Crocodile God shouts: "+
            words +"\n" )


    def heart_beat(self, ) -> None:
            int time_to_crash
            if (!time_of_crash) return
            time_to_crash = time_of_crash - time()
            if (time_to_crash < 1) {
            asyncio.create_task(self."end_it_all",0)
            set_heart_beat(0)
            return


    def shut(self, minutes: int) -> None:
            object *players
            int i
            string fname
            if (!intp(minutes)) {
            write("Bad argument\n")
            return


    def long(self, str: str, dark: int) -> str:
            ::long()
            if (time_of_crash && this_player()->query_wizard())
            return ::long(str,dark)+
            "Game reboot will be in " + ( time_of_crash - time() ) +
            " seconds.\n"
            return ::long(str,dark)


    def end_it_all(self, ) -> None:
            int i
            object *obs
            ishout("Shutdown now!")
            obs = users()
            for (i=0;i<sizeof(obs);i++)
            asyncio.create_task(self."force_quit", i, obs[i])
            asyncio.create_task(self."blue", 10)


    def force_quit(self, ob: MudObject) -> None:
            if (!objectp(ob))
            return
            if (!ob.query_property("quiting frog"))
            ob.quit_alt()


    def blue(self, ) -> None:
            if (sizeof(users()) > 0 &&
            time() - time_of_crash < 120)
            asyncio.create_task(self."blue", 10)
            else
            shutdown(0)


    def query_time_to_crash(self, ) -> int:
            if ( !time_of_crash ) {
            asyncio.create_task(self. "dest_me", 1 )
            return 9999



class Shut(Inventory):
