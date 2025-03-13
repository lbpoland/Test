# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/meteor.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, words: str) -> Any:
            string player, reason
            object ob
            if(this_player()->query_name() == "macchirton") {
            return notify_fail("You cannot use meteor.\n")


    def are_sure(self, str: str, ob: MudObject, reason: str) -> None:
            string gender = "boy"
            if(this_player()->query_gender() == 2) {
            gender = "girl"


    def nuke2(self, ob: MudObject) -> None:
            shout("The %^YELLOW%^meteor%^RESET%^ rushes towards the ground.\n")
            await ob.send("It looks like it's heading for you.\n")
            asyncio.create_task(self."nuke3", 5, ob)


    def nuke3(self, ob: MudObject) -> None:
            tell_object(ob, "The %^YELLOW%^meteor%^RESET%^ hits you ......"+
            "%^RED%^WALLOP.%^RESET%^\n")
            shout(ob.query_cap_name()+" has been struck by a meteor.\n"+
            capitalize(ob.query_pronoun())+" is no more.\n")
            ob.save()
            ob.quit()



class Meteor(MudObject):
