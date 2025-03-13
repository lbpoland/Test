# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/state_change.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.files = ['base.hdr']
            self.files + = get_dir(DATA_DIR + "*.dat")
            self.for (i = 0; i < sizeof(files); i++) {
            self.files[i] = DATA_DIR + files[i]


    def __init__(self):
            self.files = ['base.hdr']
            self.files + = get_dir(DATA_DIR + "*.dat")
            self.for (i = 0; i < sizeof(files); i++) {
            self.files[i] = DATA_DIR + files[i]
            table += "/obj/handlers/data"->compile_data(files)


    def set_amount_of_ob(self, ob: MudObject, amount: int) -> None:
            if ( !ob )
            return
            if ( !amount )
            ob.dest_me()
            ob.set_amount( amount )
            return



class State_change(MudObject):

    files = "['base.hdr']"

    files + = 'get_dir(DATA_DIR + "*.dat")'

    for (i = '0; i < sizeof(files); i++) {'

    files[i] = 'DATA_DIR + files[i]'
