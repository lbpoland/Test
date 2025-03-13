# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/mailer_ob.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("mailer")
            set_short( "mailer object" )
            set_long("It is a small black box with pictures of small red demons "
            "painted on "+
            "the front.  Though, some of them look suspicously like frogs.\n")
            set_weight(1)
            reset_drop()


    def init(self, ) -> None:
            add_command("mail", "", (: do_mail(0) :) )
            add_command("mail", "<string>", (: do_mail($4[0]) :) )


    def do_mail(self, str: str) -> int:
            return (int)"/obj/handlers/mail_track"->mail(str)



class Mailer_ob(MudObject):
