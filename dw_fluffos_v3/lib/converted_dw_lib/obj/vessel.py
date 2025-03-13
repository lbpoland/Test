# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/vessel.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):
            add_help_file("vessel")


    def init(self, ) -> None:
            ::init()
            add_command("drink", drink_pat)
            add_command("quaff", drink_pat)
            add_command("splash", splash_pat)
            add_command("rub", apply_pat)
            add_command("apply", apply_pat)
            add_command("pour", pour_pat)
            add_command("taste", "<direct:object>")
            add_command("sip", "<direct:object>")
            add_command("fill", fill_pat)
            add_command("empty", "<direct:object>")


    def stats(self, ) -> Any:
            return ::stats() + ({
            ["leak_rate", leak_rate],
            ["volume", volume],
            ["cont_volume", cont_volume],
            ["liquid", is_liquid],
            ["max_volume", max_volume]
            })


    def cmp_amount_r(self, a: MudObject, b: MudObject) -> int:
            return ((int)b.query_amount() - (int)a.query_amount())


    def cmp_weight_r(self, a: MudObject, b: MudObject) -> int:
            if (a.query_weight() || b.query_weight())
            return ((int)b.query_weight() - (int)a.query_weight())
            return cmp_amount_r(a, b)


    def query_liquid_desc(self, ) -> str:
            object *contents, *solids = ({})
            int i
            string desc, *shorts
            mixed *others
            contents = all_inventory(self)
            if( !sizeof( contents ) ) {
            return (string) 0


    def query_fullness_desc(self, ) -> str:
            int full
            full = (100 * volume) / max_volume
            if( full < 1 && query_liquid_desc() ) {
            full = 1


    def short(self, dark: int) -> str:
            object *inv
            if(query_opaque())
            return ::short(dark)
            inv = all_inventory(self)
            if(!sizeof(inv))
            return ::short(dark)
            return ::short(dark) + " of " +
            "/global/events"->convert_message(query_multiple_short(map(inv,
            (: $1.query_short() :))))


    def long(self, str: str, dark: int) -> str:
            string ret
            sub_query_contents = 1
            ret = ::long(str, dark)
            sub_query_contents = 0
            return ret


    def calc_liquid(self, ) -> None:
            if (sizeof(filter(all_inventory(), (: $1.query_liquid() :)))) {
            is_liquid = 1
            } else {
            is_liquid = 0


    def query_volume_left(self, ) -> int:
            if (!query_max_weight()) {
            return max_volume - volume


    def add_volume(self, vol: int) -> int:
            if ((vol <= 0) || !max_volume || (vol + volume <= max_volume)) {
            volume += vol
            if (previous_object()->query_continuous()) {
            cont_volume += vol


    def add_weight(self, n: int) -> int:
            int v
            if (this_player() && (this_player()->query_name() == "pinkfish")) {
            tell_creator("pinkfish", "vessel::add_weight(%O)\n", n)


    def remove_volume(self, vol_lost: int) -> int:
            {
            int amt_lost, i, orig_cv
            object *contents
            if (!cont_volume) {
            return 0


    def xfer_volume(self, vol_xferred: int, dest: MudObject) -> int:
            int vol_to_go
            int i
            int amt_xferred
            int tmp
            int orig_cv
            object *contents
            object copy
            string file_path
            mapping map
            vol_to_go = vol_xferred
            if (!cont_volume) {
            return 0


    def heart_beat(self, ) -> None:
            int lost, off
            if (leak_rate == 0 || !is_liquid) {
            set_heart_beat(0)
            return


    def do_pour(self, to: MudObject, args_b: Any, args_a: Any, args: Any) -> int:
            int m, n, volume_needed, their_volume, their_max, ovf, xfer_result
            if (query_fighting(this_player())) {
            add_failed_mess("You cannot attempt to do this while in combat.\n")
            return 0


    def do_fill(self, to: MudObject, args_b: Any, args_a: Any, args: Any) -> int:
            int m
            int n
            int i
            int run_out
            int volume_needed
            int their_volume
            int their_max
            int amount_not_poured
            int ok
            if (query_fighting(this_player())) {
            add_failed_mess("You cannot attempt to do this while in combat.\n")
            return 0


    def do_drink(self, dest: MudObject, me: Any, him: Any, args: Any, pattern: str) -> int:
            {
            int amt_to_drink
            int m
            int n
            if (sizeof(dest)) {
            add_failed_mess("Drinking is a very simple operation "
            "- please don't complicate matters.\n")
            return 0


    def do_quaff(self, dest: MudObject, me: Any, him: Any, args: Any, pattern: str) -> int:
            return do_drink(dest, me, him, args, pattern)


    def do_empty(self, dest: MudObject, me: str, him: str, prep: str) -> int:
            {
            if (environment(self) != this_player()) {
            add_failed_mess("You are not carrying $D.\n")
            return 0


    def check_splashable(self, ob: MudObject, splasher: MudObject, splashee: MudObject) -> int:
            return ob.query_splashable(splasher, splashee)


    def do_splash(self, dest: MudObject, me: Any, him: Any, args: Any, pattern: str) -> int:
            int amt_to_splash, i, m, n, orig_cv
            object *contents
            if (!sizeof(dest)) {
            add_failed_mess("Splash it on who?\n")
            return 0


    def check_applicable(self, ob: MudObject, applier: MudObject, appliee: MudObject) -> int:
            return ob.query_applicable(applier, appliee)


    def do_rub(self, dest: MudObject, me: Any, him: Any, args: Any, pattern: str) -> int:
            int amt_to_apply, i, m, n, orig_cv
            object *contents
            if (!sizeof(dest)) {
            add_failed_mess("Rub it on who?\n")
            return 0


    def do_apply(self, dest: MudObject, me: Any, him: Any, args: Any, pattern: str) -> int:
            return do_rub(dest, me, him, args, pattern)


    def do_taste(self, ) -> int:
            int amount_tasted
            if (environment(self) != this_player()) {
            write("You aren't carrying the " + short(0) + ".\n")
            return 0


    def do_sip(self, ) -> int:
            int amount_tasted
            if (environment(self) != this_player()) {
            write("You aren't carrying the " + short(0) + ".\n")
            return 0


    def do_smell(self, ) -> int:
            if (!ensure_open()) {
            return 0


    def init_static_arg(self, args: Any) -> None:
            if (args["::"])
            ::init_static_arg(args["::"])
            if (!undefinedp(args["leak rate"]))
            leak_rate = args["leak rate"]
            if (!undefinedp(args["max volume"]))
            max_volume = args["max volume"]


    def test_add(self, ob: MudObject, flag: int) -> int:
            int new_vol
            if ( !::test_add( ob, flag ) ) {
            return 0


    def event_enter(self, ob: MudObject, message: str, from: MudObject) -> None:
            int ob_vol, ob_cont
            if (environment(ob) == self) {
            if (ob.query_continuous() ) {
            ob_vol = ob.query_amount()
            ob_cont = 1
            } else if (ob.query_property("density")) {
            ob_vol = (int)ob.query_weight()*
            (int)ob.query_property("density")
            } else {
            ob_vol = 0


    def event_exit(self, ob: MudObject, mess: str, to: MudObject) -> None:
            int ob_vol, ob_cont
            if (environment(ob) == self) {
            if (ob.query_continuous()) {
            ob_vol = ob.query_amount()
            ob_cont = 1
            } else if (ob.query_property("density")) {
            ob_vol = (int)ob.query_weight()*
            (int)ob.query_property("density")
            } else {
            ob_vol = 0


    def break_me(self, ) -> None:
            object *liquid
            liquid = filter(all_inventory(), (: $1.query_liquid() :))
            if (sizeof(liquid)) {
            tell_room(environment(),
            query_multiple_short(liquid) + " splashes all over the place "
            "as " + the_short() + " breaks.\n")
            liquid.move("/room/rubbish")



class Vessel(MudObject):
