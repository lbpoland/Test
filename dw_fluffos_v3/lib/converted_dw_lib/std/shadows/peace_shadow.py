# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/peace_shadow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup_shadow(self, person: MudObject, thing: MudObject) -> None:
            shadow( person, 1 )
            peacenpc=thing


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            if (ob==peacenpc)
            dest_peace_shadow()


    def event_move_object(self, from: Any, to: Any) -> None:
            dest_peace_shadow()


    def command_shadowed(self, verb: str, args: str) -> int:
            switch(verb) {
            case "attack":
            case "behead":
            case "berserk":
            case "bob":
            case "crush":
            case "disarm":
            case "fire":
            case "guard":
            case "hack":
            case "hurl":
            case "iai":
            case "impale":
            case "kill":
            case "punch":
            case "riposte":
            case "slash":
            case "throw":
            case "warcry":
            await TP.send(GFR)
            return 1
            case "cast":
            case "circle":
            case "educe":
            case "forget":
            case "invoke":
            case "remember":
            case "scribe":
            case "scry":
            case "spellcheck":
            case "twist":
            case "use":
            case "zap":
            await TP.send(GMR)
            return 1
            case "bodyguard":
            case "bury":
            case "drag":
            case "eye":
            case "fuel":
            case "hedgehog":
            case "judge":
            case "leatherwork":
            case "mock":
            case "tempt":
            case "scathe":
            case "vurdere":
            await TP.send(GOR)
            return 1
            case "conflagrate":
            case "consecrate":
            case "decompose":
            case "ensumpf":
            case "envalise":
            case "imbue":
            case "perform":
            case "pray":
            case "pyroscipate":
            case "shroud":
            case "suffuse":
            case "ventisepelate":
            await TP.send(GRR)
            return 1
            case "abscond":
            case "ambush":
            case "case":
            case "conceal":
            case "crack":
            case "disable":
            case "filch":
            case "hide":
            case "inhume":
            case "lpick":
            case "palm":
            case "peek":
            case "plant":
            case "probe":
            case "scope":
            case "shoplift":
            case "slip":
            case "snatch":
            case "sneak":
            case "steal":
            case "unhide":
            await TP.send(GSR)
            return 1
            default:
            return 0


    def run_away(self, ) -> int:
            await TO.send(GER)



class Peace_shadow(MudObject):
