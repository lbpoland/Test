# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/container.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_volume(self, i: int) -> None:
            volume = i
            if (leak_rate) {
            set_heart_beat(1)


    def set_max_weight(self, i: int) -> None:
            if (!max_volume && i) {
            max_volume = i*10


    def set_max_volume(self, i: int) -> None:
            if (!query_max_weight() && i) {
            ::set_max_weight(i/10)


    def empty_formula(self, ) -> int:
            int vol_lost
            vol_lost = 2 + volume * 95 / 100
            if (vol_lost > volume) vol_lost = volume
            return vol_lost


    def cull_neutral_obs(self, ob: Any) -> int:
            if ( ob.query_vect() ) {
            return 1


    def dest_active_contents(self, ) -> int:
            object *inv
            int i
            inv = all_inventory(self)
            inv = filter_array(inv, "cull_neutral_obs", self)
            for (i = 0; i < sizeof(inv); i++) {
            inv[i]->dest_me()


    def add_ps_vect(self, v: int, quant: int) -> None:
            object trig
            int ca, cb
            if (quant <= 0) return
            trig = find_object("/obj/handlers/trig")
            ca = v[0];  cb = v[1]
            ca = (int)trig.pow1_5(ps_coord[0] * 10 * ps_quantity /(ca * quant)) * ca / 1000000
            cb = (int)trig.pow1_5(ps_coord[1] * 10 * ps_quantity /(cb * quant)) * cb / 1000000
            set_ps_coord_quantity( [ps_coord[0] + ca, ps_coord[1] + cb],
            quant + ps_quantity)
            return


    def transparency_string(self, trans: int) -> str:
            {
            switch (trans) {
            case -10..9: return "opaque"
            case 10..24: return "milky"
            case 25..39: return "murky"
            case 40..59: return "cloudy"
            case 60..74: return "misty"
            case 75..89: return "slightly misty"
            case 90..110: return "clear"
            default: return "paisley"


    def consistency_string(self, cons: int) -> str:
            {
            switch (cons) {
            case -10..9: return "watery liquid"
            case 10..24: return "slightly viscous watery liquid"
            case 25..39: return "runny syrup"
            case 40..59: return "syrup"
            case 60..74: return "jelly"
            case 75..89: return "paste"
            case 90..110: return "solid"
            default: return "non-Newtonian fluid"


    def update_potion_parse(self, ) -> None:
            {
            int i
            string *exploded
            potion_adjective = query_adjectives() +
            [transparency_string(all_attrs[POTION_TRANSPARENCY])]
            potion_id = [query_name()] + query_alias() +
            [consistency_string(all_attrs[POTION_CONSISTENCY])]
            for (i = 0; i < sizeof(all_attrs[POTION_NAMES]); i++) {
            exploded = explode(all_attrs[POTION_NAMES][i][0], " ")
            potion_id += [exploded[sizeof(exploded) - 1]]
            if (sizeof(exploded) > 1) {
            potion_adjective += exploded[0..sizeof(exploded) - 2]


    def void_liquid(self, ) -> None:
            {
            volume = 0
            water = 0
            misc_attrs = allocate(POTION_ATTRS_SIZE)
            misc_attrs[POTION_CONSISTENCY] = 0
            misc_attrs[POTION_TRANSPARENCY] = 100
            misc_attrs[POTION_NAMES] = [})
            misc_attrs[POTION_COLOURS] = [})
            misc_attrs[POTION_SMELLS] = [})
            misc_attrs[POTION_FLAVOURS] = [})
            ps_coord = (int *)POTION_SPACE_HANDLER.neutral_coordinate()
            ps_quantity = 0
            active_attrs = all_attrs = misc_attrs
            update_potion_parse()


    def __init__(self):
            self.leak_rate = 1000


    def init(self, ) -> None:
            (void)this_player()->add_command("drink", self)
            (void)this_player()->add_command("splash", self, "<direct:object> <preposition> <indirect:object>")
            (void)this_player()->add_command("rub", self, "<direct:object> <preposition> <indirect:object>")
            (void)this_player()->add_command("apply", self, "<direct:object> <preposition> <indirect:object>")
            (void)this_player()->add_command("pour", self, "<direct:object> <preposition> <indirect:object>")
            (void)this_player()->add_command("taste", self)
            (void)this_player()->add_command("smell", self)
            this_player()->add_command("fill", self, "<indirect:object> <preposition> <direct:object>")
            this_player()->add_command("fill", self, "<indirect:object> <fraction> up <preposition> <direct:object>")
            this_player()->add_command("fill", self, "<indirect:object> <fraction> full <preposition> <direct:object>")
            (void)this_player()->add_command("empty", self)
            close_lock_container::init()


    def query_complete_weight(self, ) -> int:
            return ::query_complete_weight() + ( query_max_weight() * volume ) /
            ( max_volume + 1 )


    def query_weight_left(self, ) -> int:
            if (!max_volume)
            return query_max_weight() - query_loc_weight()
            return query_max_weight() - query_loc_weight() - (query_max_weight()*volume)/max_volume


    def query_volume_left(self, ) -> int:
            if (!query_max_weight())
            return max_volume - volume
            return max_volume - volume - (max_volume*query_loc_weight())/query_max_weight()


    def add_weight(self, n: int) -> int:
            if ( query_weight_left() < n ) return 0
            if ( !( ::add_weight( n ) ) ) return 0
            if ( n >= 0 ) {
            remove_asyncio.create_task(self. "check_breakages" )
            asyncio.create_task(self. "check_breakages", 5 + random( 16 ) )


    def check_breakages(self, ) -> None:
            object *obs, carrier
            int i, amt, wt
            carrier = environment(self)
            while (carrier && (!living(carrier))) {
            carrier = environment(carrier)


    def liquid_name(self, ) -> str:
            {
            string liq_name
            mixed *names, *colours
            string *med, *lo
            int no_names, no_colours, i
            names = all_attrs[POTION_NAMES]
            colours = all_attrs[POTION_COLOURS]
            no_names = (sizeof(names) < 1 || names[0][1] < VERY_SMALL_AMOUNT)
            no_colours = (sizeof(colours) < 1 || colours[0][1] < VERY_SMALL_AMOUNT)
            if (no_names && no_colours) {
            liq_name = "a colourless " +
            transparency_string(all_attrs[POTION_TRANSPARENCY]) + " " +
            consistency_string(all_attrs[POTION_CONSISTENCY])
            } else if (no_names) {
            if (colours[0][1] < SMALL_AMOUNT) {
            liq_name = "a faint " + colours[0][0]
            } else {
            liq_name = add_a(colours[0][0])


    def query_liquid_short(self, ) -> str:
            {
            if (sizeof(all_attrs[POTION_NAMES]) && sizeof(all_attrs[POTION_COLOURS])) {
            if (all_attrs[POTION_NAMES][0][1] > all_attrs[POTION_COLOURS][0][1] / 2) {
            return all_attrs[POTION_NAMES][0][0]


    def long(self, str: str, dark: int) -> str:
            string ret
            int bing
            ret = ::long(str, dark)
            if (query_transparent() ||
            !query_closed()) {
            if ( ( dark == 2 ) || ( dark == -2 ) ) {
            if (query_contents() != "") {
            ret += "The "+ short( dark ) +" contains some items you cannot "
            "make out.\n"


    def sort_func(self, x: int, y: int) -> int:
            {
            if (x[1] < y[1]) return 1
            else return 0


    def set_misc_attrs(self, new_misc_attrs: Any, misc_vol: int) -> None:
            {
            misc_attrs = new_misc_attrs + [})
            volume = water + misc_vol
            all_attrs = merge_potions(active_attrs, misc_attrs, water, volume - water, volume)
            update_potion_parse()
            if (leak_rate) set_heart_beat(1)


    def set_ps_coord_quantity(self, new_coord: int, new_quantity: int) -> None:
            {
            mixed *ps_attrs
            ps_attrs = (mixed *)POTION_SPACE_HANDLER.query_attrs_at(new_coord)
            active_attrs = change_concentration(ps_attrs, new_quantity * 100 / water)
            ps_quantity = new_quantity
            ps_coord = new_coord
            all_attrs = merge_potions(active_attrs, misc_attrs, water, volume - water, volume)
            update_potion_parse()
            (void)POTION_SPACE_HANDLER.potion_create(self, new_coord, new_quantity)


    def begin_config(self, ) -> None:
            {
            potion_id = allocate(9)
            ps_coord = allocate(9)


    def config(self, vari: int, cont: Any) -> None:
            {
            potion_id[vari] = cont
            ps_coord[vari] = 1


    def end_config(self, ) -> None:
            {
            mixed *ps_attrs
            if (ps_coord[OC_VOL]) {
            volume = potion_id[OC_VOL]
            if (ps_coord[OC_MVOL]) water = volume - potion_id[OC_MVOL]
            else water = potion_id[OC_WVOL]
            } else {
            water = potion_id[OC_WVOL]
            volume = water + potion_id[OC_MVOL]


    def stats(self, ) -> Any:
            return container::stats() + close_lock_container::stats() + ({
            ["ps_quantity", query_ps_quantity()],
            ["ps_coord", (pointerp(ps_coord) && sizeof(ps_coord) == 2) ?
            "[" + ps_coord[0] + ", " + ps_coord[1] + "]" :
            sprintf("%O", ps_coord)],
            ["volume", query_volume() + ""],
            ["max volume", query_max_volume()],
            ["water vol", query_water_volume()],
            ["volume left", query_volume_left()],
            ["weight left", query_weight_left()],
            ["full_weight", query_full_weight(),],
            ["leak_rate", query_leak_rate() + ""],
            })


    def query_parse_id(self, arr: Any) -> MudObject:
            volume_to_womble = 0
            return ::query_parse_id(arr)


    def query_frac_parse_id(self, arr: Any) -> MudObject:
            int i
            volume_to_womble = 0
            if (arr[P_THING] < 0) {
            arr[P_THING]++
            if (arr[P_THING] != 0)
            return 0
            volume_to_womble = volume*arr[P_TOP]/arr[P_BOT]
            asyncio.create_task(self."set_volume_to_womble", 0, 0)
            arr[P_THING] = -1784628
            return self


    def remove_volume(self, vol_lost: int) -> int:
            {
            int q_lost
            if (!volume) {
            q_lost = ps_quantity
            water = 0
            ps_quantity = 0
            return q_lost


    def heart_beat(self, ) -> None:
            int lost, off
            if (leak_rate == 0 || volume <= 0) {
            set_heart_beat(0)
            return


    def ensure_open(self, ) -> int:
            {
            if (query_locked()) {
            write("The " + short(1) + " is locked.\n")
            return 0


    def do_pour(self, dest: MudObject, me: str, him: str, prep: str) -> int:
            {
            int amount_poured, volume_transferred, old_water, old_volume
            string liquid_desc
            if (sizeof(dest) > 1) {
            write("Currently you can only pour into one object\n")
            return 0


    def do_fill(self, to: MudObject, args_b: Any, args_a: Any, args: Any) -> int:
            int m, n, i, run_out, volume_needed, their_volume, their_max,
            amount_poured, ok
            if (intp(args[1]) && intp(args[2])) {
            m = args[0]
            n = args[1]
            if (m > n || m < 0 || n <= 0) {
            notify_fail("Interesting fraction you have there!\n")
            return 0


    def do_drink(self, dest: MudObject, me: str, him: str, prep: str) -> int:
            {
            int amount_drunk, amount_can_be_drunk
            if (sizeof(dest)) {
            write("Drinking is a very simple operation - please don't complicate matters.\n")
            return 0


    def do_empty(self, dest: MudObject, me: str, him: str, prep: str) -> int:
            {
            if (sizeof(dest)) {
            write("Passing on to pour ... bad move.\n")
            return do_pour(dest, me, him, prep)


    def do_splash(self, dest: MudObject, me: str, him: str, prep: str) -> int:
            int amount_splashed
            if (sizeof(dest) > 1) {
            write("You can only splash one object at a time.\n")
            return 0


    def do_rub(self, dest: MudObject, me: str, him: str, prep: str) -> int:
            int amount_rubbed
            if (sizeof(dest) > 1) {
            write("You can only "+query_verb()+" on to one object at a time.\n")
            return 0


    def do_apply(self, dest: MudObject, me: str, him: str, prep: str) -> None:
            do_rub( dest, me, him, prep )


    def do_taste(self, ) -> int:
            int amount_tasted
            string desc
            mixed *party
            int i
            if (!ensure_open()) return 0
            if (volume < TASTE_AMOUNT) {
            write("There is no liquid to taste.\n")
            return 0


    def do_smell(self, ) -> int:
            {
            string desc
            string *party
            int i
            if (!ensure_open()) return 0
            if (volume < 1) {
            write("There is no liquid to smell.\n")
            return 0


    def init_dynamic_arg(self, map: Any) -> None:
            mixed *ps_attrs
            object money
            if (map["::"])
            ::init_dynamic_arg(map["::"])
            if (sizeof(map["money"])) {
            money = clone_object("/obj/money")
            money.set_money_array(map["money"])
            money.move(self)


    def init_static_arg(self, args: Any) -> None:
            if (args["::"]) {
            ::init_static_arg(args["::"])


    def query_static_auto_load(self, ) -> Any:
            if (!query_name() || query_name() == "object") return 0
            if (file_name(self)[0..13] == "/obj/container")
            return int_query_static_auto_load()
            return ([ ])


    def test_add(self, ob: MudObject, flag: int) -> int:
            return !query_closed() && !flag


    def can_find_match_recurse_into(self, looker: MudObject) -> int:
            if (query_closed()) {
            return 0


    def test_remove(self, ob: MudObject, flag): int) -> int:
            varargs int move(mixed dest, string messin, string messout) {
            int result
            object from
            object to
            from = environment()
            result = ::move(dest, messin, messout)
            if (result == MOVE_OK) {
            to = environment()
            we_moved(from, to)


    def dest_me(self, ) -> None:
            close_lock_container::dest_me()
            container::dest_me()



class Container(Inventory):

    leak_rate = 1000
