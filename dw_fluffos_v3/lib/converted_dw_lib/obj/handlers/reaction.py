# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/reaction.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):
            mapping merge_effects(mapping effects_a, mapping effects_m, int q_a, int q_m) {
            int q_t, strength
            string key
            mapping ret = ([ ])
            if(!mapp(effects_a) || !mapp(effects_m))
            return 0
            q_t = q_a + q_m
            if ( !q_t ) {
            return 0


    def merge_cont_medium(self, a: MudObject, medium_alias: str) -> MudObject:
            object medium
            int no_join, q_a, q_m
            mapping effects_a, effects_m, eff
            string key
            a.remove_alias(medium_alias)
            no_join = a.query_no_join()
            if ((medium = present(medium_alias, environment(a))) && !no_join) {
            a.set_no_join()
            a.move("/room/void")
            q_a = a.query_amount()
            q_m = medium.query_amount()
            medium.adjust_amount(q_a)
            effects_a = copy(a.query_eat_effects())
            effects_m = copy(medium.query_eat_effects())
            eff = merge_effects(effects_a, effects_m, q_a, q_m)
            if (mapp(eff)) {
            foreach (key in keys(eff)) {
            medium.add_eat_effect(key, eff[key])


    def check_reaction(self, a: MudObject) -> None:
            int amt_a, need_amt_a, amt_b, need_amt_b
            string name_a, name_b, i_a, i_b, msg, fcn
            mixed *fcns
            int i, j, amt_result
            object x, *bs, ob_a, ob_b
            float ratio
            class reaction rcn
            if (objectp(this_player()))
            debug_rh = this_player()->query_property("debug_rh")
            else
            debug_rh = 0
            write_dbg("Entering reaction_handler.\n")
            name_a = a.query_medium_alias()
            if (!name_a || !a.query_continuous()) {
            write_dbg("Leaving reaction_handler because there is no A or it is not "
            "continous.\n")
            return


    def move_substance(self, ob: MudObject) -> None:
            int vol, vol_left, cont, closed, i, mv_stat
            object *contents
            if (!ob[0] || !ob[1]) return
            vol_left = (int)ob[1]->query_max_volume() - (int)ob[1]->query_volume()
            if (cont = ob[0]->query_continuous()) {
            vol = ob[0]->query_amount()
            } else {
            vol = (int)ob[0]->query_weight()*200


    def dest_substance(self, ob: MudObject) -> None:
            if (ob) {
            ob.dest_me()


    def restore_from_files(self, ) -> None:
            string *files
            int i
            files = ["base.hdr"]
            files += get_dir(REACTIONS + "*.rcn")
            for (i = 0; i < sizeof(files); i++) {
            files[i] = REACTIONS + files[i]


    def update_from_files(self, fn: str) -> None:
            mapping new_substance
            string a, b
            new_substance = "/obj/handlers/data"->compile_data( [fn] )
            foreach (a in keys(new_substance)) {
            if (undefinedp(substance[a])) {
            substance[a] = ([ ])



class Reaction(MudObject):
