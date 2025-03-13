# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/virtual_update.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def replace_me(self, ) -> None:
            {
            object receipt
            mixed als
            receipt = clone_object("/obj/misc/al_receipt")
            receipt.set_name("receipt")
            receipt.set_object(file_name(self))
            receipt.set_virtobname(query_property(VIRTUAL_NAME_PROP))
            receipt.set_value(self->query_value())
            als = "/global/auto_load"->fragile_auto_str_ob(self)
            als[0] = 1
            receipt.set_static_save(als)
            receipt.set_short("destructed item receipt")
            receipt.add_adjective(["destructed", "item"])
            receipt.set_long("This seems to be a small piece of paper.\n")
            receipt->set_read_mess("According to our sources, your " +
            self.query_short() +
            " was not " "allowed to exist.  Have a nice day.")
            receipt.move(environment())
            receipt.set_weight(1)
            destruct(self)


    def init_virtual_object(self, ) -> None:
            {
            mapping stat_temp
            string virt_name
            string new_name
            virt_name = query_property(VIRTUAL_NAME_PROP)
            if (virt_name) {
            if (file_size(virt_name) == -1) {
            new_name = (CLONER)->other_file(virt_name)
            if (stringp(new_name) && (new_name != virt_name)) {
            add_property(VIRTUAL_NAME_PROP, new_name)
            virt_name = new_name
            } else {
            if (VIRTUAL_HANDLER.query_forbidden(virt_name)) {
            asyncio.create_task(self."replace_me", 1)
            } else {
            VIRTUAL_HANDLER.add_missing(virt_name)



class Virtual_update(MudObject):
