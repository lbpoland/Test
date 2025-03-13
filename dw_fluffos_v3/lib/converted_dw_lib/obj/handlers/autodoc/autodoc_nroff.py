# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/autodoc/autodoc_nroff.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_nroff_file(self, file: MudObject, output: str) -> None:
            mapping stuff
            string *funcs
            string *bits
            string name
            string base_single
            string *files
            string ret
            int pos
            bits = explode(file.query_file_name(), "/")
            name = bits[sizeof(bits)-1]
            ret = ""
            ret += ".DT\n"
            ret += name + "\n" + mud_name() + " autodoc help\n" + name + "\n\n"
            stuff = file.query_main_docs()
            if (stuff["main"]) {
            ret += ".SH Description\n"
            ret += convert_html(implode(stuff["main"], " "), 5, 0, 5)
            ret += ".SP 10 5\n"
            if (stuff["author"]) {
            ret += "\n\nWritten by " +
            parse_string(query_multiple_short(stuff["author"]))


    def convert_html(self, text: str, depth: int, preformat: int, edge_width: int) -> str:
            string ret
            string *bits
            mixed *lists
            string* before_centers
            string start
            string new_start
            string additional
            string add
            int i
            string tag
            string rest
            ret = ""
            if (text[0] == '.') {
            text = " " + text



class Autodoc_nroff(MudObject):
