# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/pawn_receipt.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "receipt" )
            set_short( "pawned item receipt" )
            add_adjective( ["pawned", "item"] )
            set_long( "This is a small slip of paper, with a black border.\n" )
            set_main_plural( "pawned item receipts" )
            add_plural( "receipts" )
            add_adjective( "pawned" )
            set_value( 0 )
            set_weight( 1 )
            _obname = "unknown object"
            _obpath = "***"
            _timestamp = time()


    def init(self, ) -> None:
            add_command( "reclaim", "<direct:object:me'receipt'>" )


    def reset(self, ) -> None:
            object item
            if ( ( ! _expired ) && time() > _expiry_time ) {
            _expired = 1
            set_short( "expired pawned item receipt" )
            add_adjective( "expired" )
            if ( ! _expired_sold ) {
            _expired_sold = 1
            item = do_kiss()
            if ( item ) {
            item.move( _shop_path->query_store_room() )


    def set_obshort(self, s: str) -> None:
            _obshort = s


    def query_obshort(self, ) -> str:
            return _obshort


    def set_expiry_time(self, time: int) -> None:
            _expiry_time = time


    def query_expiry_time(self, ) -> int:
            return _expiry_time


    def set_item_value(self, value: int) -> None:
            _item_value = value


    def query_item_value(self, ) -> int:
            return _item_value


    def set_shop_path(self, shop: Any) -> None:
            if ( objectp( shop ) ) {
            _shop_path = base_name( shop )
            return


    def query_shop_path(self, ) -> str:
            return _shop_path


    def set_obname(self, name: str) -> None:
            _obname = name


    def set_object(self, path: str) -> None:
            _obpath = path


    def set_virtobname(self, name: str) -> None:
            _virt_name = name


    def query_obname(self, ) -> str:
            return _obname


    def query_obpath(self, ) -> str:
            return _obpath


    def query_timestamp(self, ) -> int:
            return _timestamp


    def query_virt_obname(self, ) -> str:
            return _virt_name


    def query_static_save(self, ) -> Any:
            return _static_save


    def query_pawned_item_receipt(self, ) -> int:
            return 1


    def set_static_save(self, args: Any) -> None:
            mixed p
            _static_save = args
            if (_obname != "unknown object") {
            return


    def set_object_plural(self, ob: MudObject) -> None:
            if ( ob.query_collective() && ob.query_amount() > 1 ) {
            _obplural = 1
            } else {
            _obplural = 0


    def query_object_plural(self, ) -> int:
            return _obplural


    def query_correct_short(self, ob: MudObject) -> str:
            if ( ! ob ) {
            return 0


    def setup_receipt(self, ob: MudObject) -> None:
            mixed* bits
            bits = AUTO_LOAD_OB.fragile_auto_str_ob(ob)
            set_obname(ob.query_name())
            set_obshort( query_correct_short( ob ) )
            set_object(bits[1])
            set_static_save(bits[2])


    def pluralize_sentence(self, text: str, plural: int) -> str:
            if ( plural ) {
            return replace( text, ({
            "$o", "them",
            "$r", "they",
            "$ve", "ve"
            }) )


    def query_details(self, ) -> str:
            if ( _expired ) {
            return pluralize_sentence(
            "This is a receipt for your pawned " + query_obshort() + ".\n"
            "Sadly, you have left it too long to collect $o and $r ha$ve "
            "expired, so the shop will put $o up for sale.  Better hurry to "
            + _shop_path.the_short() + " sharpish and try to buy $o back!",
            _obplural )


    def init_dynamic_arg(self, arg: Any, object) -> None:
            _obname = arg["obname"]
            if ( stringp( _obname ) ) {
            add_adjective( explode( lower_case( _obname ), " " ) )


    def do_kiss(self, ) -> MudObject:
            object thing
            if (sizeof(_static_save) < 2) {
            if (this_player()->query_creator()) {
            write("This receipt has no auto-load information, possibly "
            "because the object was broken when the player logged "
            "out.  It will have to be replaced by hand.\n")
            } else {
            write("Sorry, but this object is too broken to repair "
            "with a kiss.  You'll have to contact a creator.\n")


    def do_reclaim(self, ) -> int:
            int cost, i
            object change, item
            string change_str, place
            if ( ! query_pawned_item_receipt() ) {
            add_failed_mess( "$D is not a pawned item receipt.\n" )
            return 0



class Pawn_receipt(MudObject):
