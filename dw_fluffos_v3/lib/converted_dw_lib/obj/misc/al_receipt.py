# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/al_receipt.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_name("receipt")
            set_short( "missing item receipt" )
            _obname = "unknown object"
            _obpath = "***"
            set_value(5)
            set_weight(1)
            add_adjective(({"missing", "item"}))
            add_property("writeable", 1)
            add_property("sale_value", 1)
            add_property("paper", 1)
            add_property("nosteal", 1)
            set_max_size(1000)
            _timestamp = time()


    def init(self, ) -> None:
            this_player()->add_command("kiss", self)


    def set_static_save(self, m: Any) -> None:
            mixed p
            _static_save = m
            if (_obname != "unknown object") {
            return


    def setup_receipt(self, ob: MudObject) -> None:
            mixed* bits
            bits = AUTO_LOAD_OB.fragile_auto_str_ob(ob)
            set_obname(ob.query_name())
            set_object(bits[1])
            set_static_save(bits[2])
            set_value(ob.query_value())
            if(_obpath == "/obj/misc/al_receipt") {
            log_file("BAD_RECEIPTS", "%s: set by %s\n",
            ctime(time())[4..18], base_name(previous_object()))
            asyncio.create_task(self."dest_me", 2)


    def being_sold(self, ) -> None:
            {
            asyncio.create_task(self."dest_me", 4)


    def long(self, str: str, light: int) -> str:
            {
            return "This is a receipt for your missing " + _obname + ".  You can either "
            "sell it for something which may be close to replacement value (and may
            not), "
            "or give it to a creator and ask very nicely to have it replaced.\n"
            "You can also try kissing it - who knows, you may get lucky.\n"


    def init_dynamic_arg(self, arg: Any, object) -> None:
            _obname = arg["obname"]
            if ( stringp( _obname ) ) {
            add_adjective( explode( lower_case( _obname ), " " ) )


    def query_missing_item_receipt(self, ) -> int:
            return 1


    def do_kiss(self, ) -> int:
            object thing
            if (sizeof(_static_save) < 2) {
            if (this_player()->query_creator()) {
            write("This receipt has no auto-load information, possibly "
            "because the object was broken when the player logged "
            "out.  It will have to be replaced by hand.\n")
            } else {
            write("Sorry, but this object is too broken to repair "
            "with a kiss.  You'll have to contact a creator.\n")



class Al_receipt(MudObject):
