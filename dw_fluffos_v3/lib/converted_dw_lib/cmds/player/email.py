# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/email.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            string email
            email = TP.query_email()
            if (!str) {
            write("Your current email address is "+email+"\n")
            write("To clear use \"email CLEAR\"\n")
            write("For the email address to be only visible by lords prepend a :\n")
            write("eg email :frog@frogcentral.froguni.swamp\n")
            return 1



class Email(MudObject):
