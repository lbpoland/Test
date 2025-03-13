# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/expression_util.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_expression_type(self, type: str) -> None:
            _type = type


    def query_expression_type(self, ) -> str:
            return _type


    def do_user_function_add(self, def: str, expr: str) -> int:
            string name
            if (this_player()->query_name() != "presto")
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add functions to this store.\n")
            return 0


    def do_user_function_remove(self, name: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to remove functions from this store.\n")
            return 0


    def do_approve_status_internal_functions(self, ) -> int:
            string* names
            string name
            string ret
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to see the status of this store.\n")
            return 0


    def do_function_help(self, name: str) -> int:
            string nroff_fn
            string str
            string fname
            fname = CRAFT_SHOP_EXPRESSION_HELP_DIR + name
            if (file_size(fname) <= 0) {
            add_failed_mess("There is no help for the function '" + name + "'.\n")
            return 0


    def do_function_help_list(self, ) -> int:
            string *names
            names = get_dir(CRAFT_SHOP_EXPRESSION_HELP_DIR)
            if (!sizeof(names)) {
            add_failed_mess("There is no help on any functions.\n")
            return 0


    def do_approve_status_functions(self, hints: int) -> int:
            string* names
            string name
            string ret
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to see the status of this store.\n")
            return 0


    def init(self, ) -> None:
            if (!is_allowed(this_player()->query_name())) {
            return



class Expression_util(MudObject):
