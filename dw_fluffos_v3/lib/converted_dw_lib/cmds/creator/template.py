# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/template.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, size: int) -> int:
            mixed* data
            int x
            int y
            string line
            data = TERRAIN_MAP_WORLD_MAP.query_map_template(size)
            line = ""
            for (y = 0; y < sizeof(data); y++) {
            for (x = 0; x < sizeof(data[y]); x++) {
            if (data[x][y]) {
            line += "*"
            } else {
            line += " "



class Template(MudObject):
