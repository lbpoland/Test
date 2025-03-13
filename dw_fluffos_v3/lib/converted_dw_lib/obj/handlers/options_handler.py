# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/options_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._options = ([ ])
            self._cache_input = ([ ])
            self._colours = []
            self.(: $1->set_mangle_accent($3 = = "mangle"), 1 :),


    def is_option(self, player: MudObject, name: str) -> int:
            mixed stuff
            string *path
            path = explode(name, " ")
            stuff = query_bottom_sub_option(player, path)
            if (!classp(stuff)) {
            return 0


    def is_option_group(self, player: MudObject, name: str) -> int:
            mixed stuff
            string *path
            path = explode(name, " ")
            stuff = query_bottom_sub_option(player, path)
            if (!mapp(stuff)) {
            return 0


    def query_option_value(self, player: MudObject, path: str) -> str:
            string* bits
            mixed value
            class option stuff
            bits = explode(path, " ")
            stuff = query_bottom_sub_option(player, bits)
            if (classp(stuff)) {
            value = evaluate(stuff->query, player, bits)
            if (intp(stuff->type)) {
            switch (stuff->type) {
            case OPTIONS_TYPE_BRIEF:
            if (value) {
            value = "verbose"
            } else {
            value = "brief"


    def query_option_help(self, player: MudObject, path: str) -> str:
            string *bits
            mixed stuff
            bits = explode(path, " ")
            stuff = query_bottom_sub_option(player, bits)
            if (classp(stuff)) {
            return copy(stuff->help)


    def set_option_value(self, player: MudObject, path: str, value: str) -> int:
            string* bits
            string* bad
            mixed set_value
            class option stuff
            bits = explode(path, " ")
            stuff = query_bottom_sub_option(player, bits)
            if (classp(stuff)) {
            if (pointerp(stuff->type)) {
            if (stuff->type.index(value) if value in stuff->type else -1 == -1) {
            add_failed_mess("You must set your type to one of " +
            query_multiple_short(stuff->type) + ".\n")
            return 0


    def convert_birthday(self, str: str) -> str:
            #undef MONTHS
            #define MONTHS ["January", "February", "March", "April", "May", "June", \
            "July", "August", "September", "October", "November", "December"]
            int day, month, tot
            string retval
            sscanf(str, "%d", tot)
            day = tot / 100
            month = tot % 100
            switch(day) {
            case 11:
            retval = "11th"; break
            case 12:
            retval = "12th"; break
            case 13:
            retval = "13th"; break
            default:
            switch(day%10) {
            case 1:
            retval = day+"st"; break
            case 2:
            retval = day+"nd"; break
            case 3:
            retval = day+"rd"; break
            default:
            retval = day+"th"



class Options_handler(MudObject):

    _options = '([ ])'

    _cache_input = '([ ])'

    _colours = '[]'

    (: $1->set_mangle_accent($3 = '= "mangle"), 1 :),'
