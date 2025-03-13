# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/baggage.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            close_lock_container::init()


    def add_weight(self, n: int) -> int:
            if ( !( ::add_weight( n ) ) ) return 0
            if ( n >= 0 ) {
            remove_asyncio.create_task(self. "check_breakages" )
            asyncio.create_task(self. "check_breakages", 5 + random( 16 ) )


    def check_breakages(self, ) -> None:
            object *obs, carrier
            int i, amt, wt
            carrier = environment(self)
            while (carrier && (!living(carrier)))
            carrier = environment(carrier)
            if (!carrier)
            return
            obs = all_inventory()
            wt = query_loc_weight() - (int)query_property("padded")
            for (i=0;i<sizeof(obs);i++)
            if ((amt = obs[i]->query_property("fragile"))) {
            if (wt <= amt || ((wt - amt)*100)/amt <= random(100))
            obs[i] = 0
            } else
            obs[i] = 0
            obs = obs - [0]
            if (sizeof(obs) && environment(carrier)) {
            tell_room(environment(carrier), carrier.the_short()+" breaks "+
            (sizeof(obs)>1?"some things":"one thing")+" in "+
            query_multiple_short([self])+".\n", [carrier])
            await carrier.send("You break "+query_multiple_short(obs)+" in "+
            query_multiple_short([self])+".\n")
            obs.dest_me()


    def long(self, word: str, dark: int) -> str:
            string ret
            ret = ::long( word, dark )
            ret += cond_string()
            if ( query_transparent() || !query_closed() ) {
            if (dark == 2 ||
            dark == -2) {
            if (query_contents() != "") {
            ret += "$C$$the_short:" + file_name(self) + "$ contains "
            "some items you cannot make out.\n"


    def ensure_open(self, ) -> int:
            if ( query_locked() ) {
            write( "The "+ short( 0 ) +" is locked.\n" )
            return 0


    def stats(self, ) -> Any:
            return container::stats() + close_lock_container::stats()


    def init_dynamic_arg(self, map: Any, object) -> None:
            object money
            if (map["::"]) {
            container::init_dynamic_arg(map["::"])


    def init_static_arg(self, args: Any) -> None:
            if (args["::"]) {
            ::init_static_arg(args["::"])


    def query_static_auto_load(self, ) -> Any:
            if ( !query_name() || ( query_name() == "object" ) ) {
            return 0


    def can_find_match_recurse_into(self, looker: MudObject) -> int:
            if (query_closed()) {
            return 0


    def test_add(self, ob: MudObject, flag: int) -> int:
            if(flag)
            return 0
            return ::test_add(ob, flag)


    def break_me(self, ) -> None:
            all_inventory()->move( environment(), "$N fall$s out of " + a_short() +"." )
            ::break_me()


    def dest_me(self, ) -> None:
            close_lock_container::dest_me()
            container::dest_me()



class Baggage(Inventory):
