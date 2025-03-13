# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/teddy.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("bear")
            set_short("teddy bear")
            add_alias("teddy")
            add_adjective("teddy")
            set_long("This is a cute and cuddly teddy bear.  Just the sort to give "
            +"someone you love to remind them of you.  It looks very soft and "
            +"huggable.\n")
            set_weight(10)
            set_value(25)
            set_main_plural("teddy bears")
            add_plural(({"bears", "teddys"}))


    def init(self, ) -> None:
            TP.add_command("hug", TO)
            TP.add_command("cuddle", TO)


    def do_hug(self, ) -> int:
            write("You hug the teddy bear close to you and feel all warm and fuzzy "
            "inside.\n")
            say(TP.one_short()+ " hugs the teddy bear close and smiles happily.\n")
            TP.add_succeeded_mess(TO, "", [}) )
            return 1


    def do_cuddle(self, ) -> int:
            do_hug()
            TP.add_succeeded_mess(TO, "", [}) )
            return 1



class Teddy(MudObject):
