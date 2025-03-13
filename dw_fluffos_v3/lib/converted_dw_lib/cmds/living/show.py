# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/show.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def notify_fail(self, str: str) -> int:
            tell_object(find_player("tape"), "%^YELLOW%^"+
            this_player()->query_short()+" "+str+"%^RESET%^\n")
            return efun::notify_fail(str)


    def cmd(self, item: MudObject, target: MudObject) -> int:
            {
            return do_show_object( this_player(), item, this_player(), target, 0 )


    def do_show_object(self, shower: MudObject, item: MudObject, owner: MudObject, target: MudObject, nomess: int) -> int:
            {
            tell_creator( shower, "%O\n%O\n", item, target )
            if( target == shower ) {
            add_failed_mess( "Why not just look at it?\n")
            return 0


    def accept_show(self, target: MudObject, read: int) -> int:
            mixed *stuff
            object from
            object owner
            object item
            string message
            if( target == this_player() ) {
            add_failed_mess( "You cannot show stuff to yourself.\n")
            return 0



class Show(MudObject):
