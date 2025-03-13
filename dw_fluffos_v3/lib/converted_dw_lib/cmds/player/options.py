# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/options.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd_display(self, option: str) -> int:
            string *bits
            string *partys
            string bing
            if (sscanf(option, "%s=%s", option, bing) == 2) {
            return cmd_set(option, bing)


    def cmd_set_all(self, option: str, value: str) -> int:
            string* stuff
            string* ok
            string* bad
            string opt
            if (!OPTION_HANDLER.is_option_party(this_player(), option)) {
            add_failed_mess("The option must be an option party to use the 'all' "
            "keywork.\n")
            return 0


    def cmd_set(self, option: str, value: str) -> int:
            string *bits
            if (!option  ||  option == "")
            return 0
            bits = explode(option, " ")
            if(!sizeof(bits))
            return 0
            if (bits[<1] == "all") {
            if (sizeof(bits) > 1) {
            return cmd_set_all(implode(bits[0..<2], " "), value)


    def cmd_edit(self, option: str) -> int:
            string value
            if (OPTION_HANDLER.is_option(this_player(), option)) {
            value = OPTION_HANDLER.query_option_value(this_player(), option)
            write("Editing the option " + option + ".\n")
            this_player()->do_edit(value, "finish_edit", self,
            0, option)
            return 1
            } else {
            add_failed_mess("There is no option " + option + ".\n")
            return 0


    def finish_edit(self, value: str, option: str) -> None:
            if (!value) {
            write("Aborting.\n")
            return



class Options(MudObject):
