# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/describe.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .utilities import CLOTHING_HANDLER
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._zone_str = "face|hair"
            self._zone_str + = "|" + zone


    def cmd(self, str: str) -> int:
            string desc
            string zone
            desc = TP.query_desc()
            if (!str) {
            if (desc) {
            write("Description reads:\n" + TP.query_cap_name() + " " +
            desc + "\n")
            } else {
            write("No description set.\n")


    def finish_desc_edit(self, str: str) -> None:
            string cname
            --use_count
            if (!str) {
            write("Description unchanged.\n")
            return


    def cmd_zone(self, zone: str, desc: str) -> int:
            this_player()->set_zone_desc(zone, desc)
            write("Set the description for the zone " + zone + " as \"" + desc + "\".\n")
            return 1


    def cmd_zone_clear(self, zone: str) -> int:
            this_player()->set_zone_desc(zone, 0)
            write("Cleared the description for the zone " + zone + ".\n")
            return 1



class Describe(MudObject):

    _zone_str = '"face|hair"'

    _zone_str + = '"|" + zone'
