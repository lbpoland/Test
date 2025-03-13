# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/gchat.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str) -> Any:
            string word, cur_lang, party
            object ob, *members, *earmuffed
            return notify_fail( "This command is no longer used.  Please "
            "use \"party say\" instead.\n" )
            if( TP.check_earmuffs( "gchat" ) )
            return notify_fail( "You have gchat ear muffed.\n" )
            party = TEAM_HANDLER.query_party(this_player())
            if(!party)
            return notify_fail("You are not a member of any party.\n")
            if(!arg)
            return notify_fail("Syntax: gchat <message>\n")
            cur_lang = TP.query_current_language()
            if (!LANGUAGE_HAND.query_language_spoken(cur_lang))
            return notify_fail(capitalize(cur_lang)+" is not a spoken language.\n")
            if (!LANGUAGE_HAND.query_language_distance(cur_lang))
            return notify_fail(capitalize(cur_lang)+" is not able to spoken at a "
            "distance.\n")
            word = query_word_type(arg, "")
            if (word != "")
            word = word + "ing"
            if (TP.query_volume(D_ALCOHOL))
            arg = drunk_speech(arg)
            if(function_exists("mangle_tell", environment(TP)))
            arg = environment(TP)->mangle_tell(arg, ob, 0)
            members = TEAM_HANDLER.query_members(party)
            members -= [this_player()]
            if ( !members ) {
            TEAM_HANDLER.leave_party( party, this_player() )
            TEAM_HANDLER.end_party( party )
            write( "Somehow your party has no members.  "
            "Your party has been ended.  "
            "I hope this is okay.\n" )
            return 1



class Gchat(MudObject):
