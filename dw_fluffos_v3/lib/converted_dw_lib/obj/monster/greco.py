# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/monster/greco.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            seteuid("Root")
            if (!grecos_day_off) {
            set_name("greco")
            set_short("Greco the Departure Gecko")
            set_long("A small mottled grey gecko whose job it is to record all of "
            "the baggage of players so they can be restocked when they "
            "come back.  Greco is currently scribbling in "
            + query_possessive() + " notebook furiously.\n")
            } else {
            set_name("gumboot")
            set_short("Gumboot")
            set_long("A big black lizard who looks rather confused about what "
            + query_pronoun() + " is supposed to be doing.  Nevertheless, "
            + query_pronoun() + " is trying to look busy, scrawling "
            "something into a huge log book.\n")


    def set_grecos_day_off(self, day_off: int) -> None:
            grecos_day_off = day_off
            setup()


    def query_grecos_day_off(self, ) -> int:
            return grecos_day_off


    def get_rid_of(self, player: MudObject, verbose: int) -> None:
            int i
            catch(set_grecos_day_off("/obj/monster/greco"->query_grecos_day_off()))
            if (verbose) {
            if (!grecos_day_off) {
            tell_object(player, "Greco the Departure Gecko starts inspecting "
            "all your items and scribbling on a "
            "notepad.\n")
            } else {
            tell_object(player, "This is Greco's day off.\nGumboot, Greco's "
            "distant relative, is here to take your "
            "information.  Gumboot looks very confused "
            "and sticks the pencil in "+
            query_possessive()+" ear.\n")


    def get_ob_al(self, ob: MudObject, verbose: int) -> None:
            {
            mixed *als
            unhandled_obs -= [ob]
            als = my_player.fragile_auto_str_ob(ob)
            done_obs += [ob]
            if (sizeof(als) == 0) return
            total_als += als


    def handle_dead_ob(self, ob: MudObject) -> None:
            int value
            mixed *als
            string obname
            catch(ob.move("/room/broken"))
            value = 1000
            catch(value = ob.query_value())
            obname = "unknown object"
            catch(obname = ob.short(1))
            catch("/obj/misc/al_receipt"->set_object(file_name(ob)))
            "/obj/misc/al_receipt"->set_obname(obname)
            "/obj/misc/al_receipt"->set_value(value)
            als = "/global/auto_load"->
            fragile_auto_str_ob(find_object("/obj/misc/al_receipt"))
            als[0] = 1
            if (!undefinedp(als[2][1]["::"]["cloned by"])) {
            als[2][1]["::"]["cloned by"] = "greco"


    def finish_player(self, verbose: int) -> None:
            int i, one_more
            object *missing_obs
            if (find_asyncio.create_task(self."get_ob_al") != -1) {
            asyncio.create_task(self."finish_player", 2, verbose)
            return



class Greco(MudObject):
