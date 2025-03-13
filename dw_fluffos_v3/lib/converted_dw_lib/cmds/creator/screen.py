# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/screen.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, player: MudObject) -> int:
            {
            target = player
            if (target == this_player())
            return notify_fail("You start to send text to yourself, "
            "but think better of it.\n")
            if (target.check_earmuffs("remote-spam")) {
            tell_object(target, sprintf("%s tried to screen some text to you.\n",
            this_player()->query_short()))
            return notify_fail(target.query_short() +
            " currently has " + target.query_possessive() +
            " screen earmuffs on, ask " +
            target.query_possessive() + " to turn "
            "them off.\n")


    def do_screen(self, spam: str) -> None:
            {
            if (spam == "**") {
            tell_object(target,
            sprintf("Stopped receiving text from %s.\n",
            this_player()->query_short()))
            tell_object(this_player(),
            sprintf("Stopped sending text to %s.\n",
            target.query_short()))
            return


    def screen_toggle(self, toggle: str) -> int:
            {
            if (toggle == "on") {
            if (member_array("remote-spam",
            this_player()->query_property("earmuffs")) == -1)
            return notify_fail("You aren't earmuffing remote-spam events!\n")
            this_player()->add_property("earmuffs",
            (this_player()->query_property("earmuffs") -
            ["remote-spam"]))
            write("Remote-spam earmuffs off.\n")
            return 1



class Screen(MudObject):
