# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/wiz_channels.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def wiz_commands(self, ) -> None:
            string channel
            foreach(channel in channel_list()) {
            add_command(channel, "<string'mess'>", (: channel_cmd($4[0]) :))
            add_command(channel+"@", "<string'mess'>", (: channel_cmd("@"+$4[0]) :))
            add_command(channel+"?", "", (: channel_cmd("?") :))
            if(!INTERMUD_MAP[channel]) {
            add_command(channel+"!", "", (: channel_cmd("!") :))
            add_command("h"+channel, "", (: channel_hist() :))



class Wiz_channels(MudObject):
