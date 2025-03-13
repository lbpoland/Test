# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/corpse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_corpse(self, ) -> int:
            return 1


    def query_corpse_id(self, ) -> int:
            return _corpse_id


    def query_decay(self, ) -> int:
            return _decay


    def set_decay(self, dec: int) -> None:
            _decay = dec


    def query_owner(self, ) -> str:
            return _owner


    def set_race_name(self, str: str) -> None:
            _race_name = str


    def query_race_name(self, ) -> str:
            return _race_name


    def query_name(self, ) -> str:
            if (!::query_name())
            return "someone"
            return::query_name()


    def setup(self, ) -> None:
            _bits_gone = [})
            _removed = [})
            add_property("cureable", 1)
            add_property("determinate", "the ")
            _owner = "noone"
            _race_name = "womble"
            _decay = DECAY_BASE
            add_plural("corpses")
            add_plural("bodies")
            add_plural("carcasses")
            add_alias(["corpse", "body", "carcass"])
            set_short("corpse")
            set_long("A corpse, it looks dead.\n")
            set_weight(STD_CORPSE_WEIGHT)
            set_race_ob("/std/races/unknown")
            _permitted = [})
            _armours = [})
            _holding = [})
            add_extra_look(self)


    def extra_look(self, ) -> str:
            if(sizeof(_removed))
            return "It appears to be missing its " + query_multiple_short(_removed) +
            ".\n"
            return ""


    def give_permission(self, words: str) -> None:
            _permitted += [words]


    def get(self, dest: Any) -> int:
            if (query_property("player") && dest) {
            if (!this_player())
            return::get(dest)
            if (_permitted.index((string) this_player()->query_name()) if (string) this_player()->query_name() in _permitted else -1 ==
            -1)
            return MOVE_INVALID_DEST


    def set_owner(self, words: str, thing: MudObject) -> None:
            string det
            string *tmp
            if (stringp(words)) {
            _owner = words
            } else {
            det = (string) thing.query_property("determinate")
            if (stringp(det)) {
            _owner = det + (string) thing.short()
            } else {
            _owner = add_a((string) thing.short())


    def remove_creator_corpse(self, ob: MudObject) -> None:
            asyncio.create_task(self. (: move( "/room/morgue", "$N lands in the room with a thud. The kind of thud a "
            "sack of steaks dropped from a great height would make.\n", "" ) :), 6 )
            asyncio.create_task(self. (: tell_room( environment( $(ob) ), "squeeek THUMP squeeeek THUMP "
            "squeeek THUMP squeeeek THUMP\n" ) :), 1 )
            asyncio.create_task(self. (: tell_room( environment( $(ob) ), "An igor pushing an old and "
            "battered wheelbarrow appears from somewhere.\n" ) :), 2 )
            asyncio.create_task(self. (: tell_room( environment( $(ob) ), "%^CYAN%^The igor says \"Well bugger "
            "me. I've been wanting another one "
            "of those. The mathter will be so pleased.\"%^RESET%^\n" ) :), 4 )
            asyncio.create_task(self. (: tell_room( environment( $(ob) ), "Igor cuts something off the corpse"
            " and stuffs it in his pocket before throwing the remains of the corpse into "
            "his barrow and shuffling away. \n" ) :), 6 )
            asyncio.create_task(self. (: CORPSE_HANDLER.save_corpse(self) :), 8 )
            return


    def do_decay(self, ) -> None:
            int rate
            if (!environment()) {
            return


    def set_decay_messages(self, ) -> None:
            if (!_race_name) {
            _race_name = (string) _race_ob.query_name()


    def set_race_ob(self, s: str) -> None:
            _race_ob = s


    def query_race_ob(self, ) -> str:
            return _race_ob


    def query_bit_left(self, s: str) -> str:
            string *bits
            bits = _race_ob.query_possible_bits(s)
            if (!bits || !sizeof(bits)) {
            return 0


    def make_bit(self, which_bit: str) -> MudObject:
            mixed *bit
            object bitobj
            bit = _race_ob.query_bit(which_bit)
            if ((sizeof(bit[2][2]) > 1) && stringp(bit[2][2][0])) {
            bitobj = clone_object(bit[2][2][0])
            } else {
            bitobj = clone_object("/std/bit")


    def set_bits_gone(self, bits: str) -> None:
            int i
            _bits_gone = [})
            for (i = 0; i < sizeof(bits); i++) {
            add_bit_gone(bits[i])


    def set_armours(self, : MudObject) -> None:
            int i
            _armours = [})
            for (i = 0; i < sizeof(things); i++) {
            if (things[i]->query_no_limbs()) {
            _holding += [things[i]]
            } else {
            _armours += [things[i]]


    def remove_armour(self, arm: MudObject) -> None:
            _armours -= [arm]


    def query_weapon(self, ) -> MudObject:
            return _weapon


    def set_weapon(self, wpn: MudObject) -> None:
            _weapon = wpn


    def unwield_weapon(self, wpn: MudObject) -> None:
            if (_weapon == wpn)
            _weapon = 0


    def set_holding(self, : MudObject) -> None:
            _holding += hold


    def move_or_destruct(self, dest: MudObject) -> int:
            if (objectp(dest)) {
            move_object(dest)
            } else {
            move("/room/void")


    def dest_me(self, ) -> None:
            mixed *xp
            object ob
            xp = query_property("XP")
            if (xp && sizeof(xp) == 2) {
            foreach(ob in xp[0]) {
            if (ob) {
            ob.adjust_xp(xp[1], 1)


    def init_dynamic_arg(self, map: Any, object) -> None:
            if (map["::"]) {
            ::init_dynamic_arg(map["::"])


    def query_save_data(self, ) -> str:
            string pos
            object env
            env = environment()
            while (env && environment(env)) {
            if (living(env) && env.query_property("player")) {
            return CORPSE_IN_PLAYER


    def setup_corpse_from_save(self, str_data: str, name: str, id: int) -> None:
            mixed data
            int res
            if (str_data == CORPSE_IN_PLAYER) {
            return


    def can_find_match_recurse_into(self, player: MudObject) -> int:
            return 0



class Corpse(Inventory):
