# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/virtual/setup_compiler/SetupCompiler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def initialize_methods(self, ) -> None:
            SERVER.add_method("vrm",  file_name(self), "compile_vrm")
            SERVER.add_method("vro",  file_name(self), "compile_vro")
            SERVER.add_method("vrw",  file_name(self), "compile_vrw")
            SERVER.add_method("vra",  file_name(self), "compile_vra")
            SERVER.add_method("vrc",  file_name(self), "compile_vrc")


    def prop_to_fun(self, file: str, clone: int, incfile: str) -> MudObject:
            string  data, data2, s1, *ind, dir, tmp_name
            int      i
            tmp_name = file+"-"+(tmp_file_no++)+".c"
            if (find_object(tmp_name))
            tmp_name.dest_me()
            ind = explode(file, "/")
            dir = implode(ind[0..sizeof(ind)-2], "/")
            unguarded((: rm, tmp_name :))
            unguarded((: write_file, tmp_name,
            "object MyRoom;\n"
            "#include \""+incfile+"\"\n\n"
            "object this_room() { return MyRoom; }\n" :))
            data = read_file(file)
            if (!data) {
            Error("prop_to_fun() : file " + file + " not found\n")


    def __init__(self):
            self."  MyRoom = (object)\""+SERVER+


    def compile_vrc(self, name: str, clone: int) -> MudObject:
            return prop_to_fun(name, clone, PATH+ROOMFUNCS )


    def compile_vmc(self, name: str, clone: int) -> MudObject:
            return prop_to_fun(name, clone, PATH+MON_FUNCS )


    def compile_vac(self, name: str, clone: int) -> MudObject:
            return prop_to_fun(name, clone, PATH+ARM_FUNCS )


    def compile_vwc(self, name: str, clone: int) -> MudObject:
            return prop_to_fun(name, clone, PATH+WEP_FUNCS )


    def compile_voc(self, name: str, clone: int) -> MudObject:
            return prop_to_fun(name, clone, PATH+OBJ_FUNCS )



class Setupcompiler(MudObject):

    "  MyRoom = '(object)\\""+SERVER+'
