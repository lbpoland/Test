# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/sh_out.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            string s1, s2, s
            object g
            string cur_lang
            object lag
            int tim, cost
            if(!str || str == "")
            return notify_fail("Syntax : shout <text>\n")
            if (!environment(this_player()))
            return notify_fail( "You appear to be in limbo...\n" )
            if(TP.query_property("dead") == 1)
            return notify_fail("You don't have any lungs, how can you shout?\n")
            if (TP.check_earmuffs("shout"))
            return notify_fail("Why shout when you can't hear people "
            "shout back?\n")
            cur_lang = TP.query_current_language()
            if (!LANGUAGE_HAND.query_language_spoken(cur_lang))
            return notify_fail(capitalize(cur_lang)+" is not a spoken language.\n")
            if (!LANGUAGE_HAND.query_language_distance(cur_lang))
            return notify_fail(capitalize(cur_lang)+" is not able to spoken "
            "at a distance.\n")
            if (TP.query_invis())
            return notify_fail("Invisible people cannot shout, they cannot "
            "see their arm in front of their face.  Shouting is "
            "out of the question.\n")
            if (TP.query_property("gagged"))
            return notify_fail("You have been gagged!  You will not be able "
            "to shout again until the gag is removed.  Perhaps "
            "you should talk to a creator about this.\n")
            if (TP.query_property("recently shouted")) {
            return notify_fail("You have shouted very recently, perhaps you "
            "should give your lungs a small break and try again "
            "in a couple seconds.\n")


    def query_shout_word_type(self, str: str) -> str:
            switch (str[<1]) {
            case '!':
            return "yell"
            case '?':
            return " asking"
            default:
            return ""


    def my_mess(self, fish: str, erk: str) -> None:
            if(!interactive(TP))
            return
            printf("%s%-=*s\n", fish, TP.query_cols() - strlen(fish),
            TP.fix_string(erk))


    def summon_bel_shamharoth(self, who: MudObject, lag_shout: int) -> None:
            object env
            if (!who || !objectp(who))
            return
            if (!random(3))
            who.adjust_tmp_con(-2)
            if (!random(3))
            who.adjust_tmp_int(-2)
            if (!random(3))
            who.adjust_tmp_wis(-2)
            if (!random(3))
            who.adjust_tmp_dex(-2)
            env = environment(who)
            if ("/secure/master"->query_lord(geteuid(who))) {
            BROADCASTER.broadcast_event(users(),
            (int *)env.query_co_ord(),
            "The heavens shake with a hideous roar and just as suddenly "
            "all is quiet.\n$C$"+ who.query_name() + " chuckles in the "
            "distance.\n",
            ( 100 * ( (int)who.query_con() +
            (int)who.query_str() ) ) / 3,
            1, 0)
            tell_object(who, "Your lordliness saves you from a grizzly "
            "encounter with the Sender of Eight.\n")
            } else {
            BROADCASTER.broadcast_event(users(),
            (int *)env.query_co_ord(),
            "a sudden chill passes through the land as $C$" +
            who.query_name() + " is carried off screaming "
            "to the land of shades.\n",
            ( 100 * ( (int)who.query_con() +
            (int)who.query_str() ) ) / 3,
            1, 0)
            tell_object( who, "You think you'd best be careful what you "
            "shout in the future as shadowy tentacles drag you "
            "into the ground...\n" )
            if(lag_shout)
            BROADCASTER.broadcast_event(users(),
            (int *)env.query_co_ord(),
            ( 100 * ( (int)who.query_con() +
            "The heavens shake with a hideous chuckle and in the "
            "distance a booming yet apologetic voice says: Oops.\n",
            (int)who.query_str() ) ) / 3,
            1, 0)
            if(base_name(env) != "/room/departures")
            who.quit()


    def query_no_quit(self, ) -> int:
            if (TP.query_save_inhibit() || TP.query_auto_loading()) {
            return NO_QUIT_INVENTORY



class Sh_out(MudObject):
