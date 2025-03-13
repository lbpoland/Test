# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/npc/basilisk_stare.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_passed_out_message(self, ) -> str:
            {
            string *msgs = ({
            "The eyes!  They're burning!  Can't think!\n",
            "Your concentration is too fragmented.\n",
            "Why do that when you can just sit here and fall into those eyes?\n",
            "Arrrrgghhhh!  Too much pain!\n"
            })
            return msgs[random(sizeof(msgs))]


    def move_with_look(self, dest: MudObject, messin: str, messout: str) -> int:
            {
            tell_object(player, "Your mind is not here to help you control "+
            "your movement.\n")
            return MOVE_NO_DROP


    def attack_by(self, obj: MudObject) -> int:
            {
            if( !obj || ( !obj.one_short() ) ) {
            tell_room( environment( player ), player.one_short() + " is totally "
            "helpless.\n", player )



class Basilisk_stare(MudObject):
