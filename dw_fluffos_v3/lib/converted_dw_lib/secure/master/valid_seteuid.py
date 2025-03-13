# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/valid_seteuid.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def valid_euid(self, str: str) -> int:
            string *domains
            switch (str) {
            case "all":
            case "Handlers":
            case "Mailer":
            case "Network":
            case "Room":
            case "Spell":
            case "WWW":
            return 1
            default:
            domains = unguarded((: get_dir, "/d/" :))
            domains -= ["lost+found"]
            domains = map(domains, (: capitalize($1) :))
            if (domains.index(str) if str in domains else -1 != -1) {
            return 1


    def valid_seteuid(self, ob: MudObject, euid: str) -> int:
            string crea
            if (euid == "tmp") {
            return 1



class Valid_seteuid(MudObject):
