# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/virtual/compiler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def create(self, ) -> None:
            {
            seteuid("Root")
            initialize_methods()
            o_funcs = O_FUN
            r_funcs = O_FUN + R_FUN
            arm_funcs = ARM_FUN + O_FUN
            clo_funcs = CLO_FUN + O_FUN
            sca_funcs = SCA_FUN + O_FUN
            wep_funcs = WEP_FUN + O_FUN
            mon_funcs = MON_FUN + O_FUN
            cont_funcs = CONT_FUN + O_FUN
            food_funcs = FOOD_FUN + CONT_FUN + O_FUN
            clotrans_funcs = O_FUN + CLO_FUN + CLOTRANS_FUN


    def query_return_ob(self, ) -> MudObject:
            {
            return return_ob


    def set_return_ob(self, ob: MudObject) -> None:
            {
            return_ob = ob


    def initialize_methods(self, ) -> None:
            {
            SERVER.add_method( "r", file_name( self ), "compile_r",
            CLONE|LOAD )
            SERVER.add_method( "ro", file_name( self ), "compile_r",
            CLONE|LOAD )
            SERVER.add_method( "ob", file_name( self ), "compile_ob" )
            SERVER.add_method( "arm", file_name( self ), "compile_arm" )
            SERVER.add_method( "clo", file_name( self ), "compile_clo" )
            SERVER.add_method( "trans", file_name( self ), "compile_clotrans" )
            SERVER.add_method( "sca", file_name( self ), "compile_sca" )
            SERVER.add_method( "wep", file_name( self ), "compile_wep" )
            SERVER.add_method( "mon", file_name( self ), "compile_mon" )
            SERVER.add_method( "food", file_name( self ), "compile_food" )
            SERVER.add_method( "cont", file_name( self ), "compile_cont" )
            SERVER.add_method( "imp", file_name( self ), "compile_imp" )


    def do_clone(self, dest: MudObject, str: str) -> None:
            {
            object  ob
            ob = clone_object( str )
            if( ob )
            ob.move( dest )


    def __init__(self):
            self.data = read_file( file )


    def strip_string(self, str: str) -> str:
            {
            int     i, j
            j = strlen( str ) - 1
            for( ; WHITESPACE( str[ i ] ) && i < j; i++ )
            for( ; WHITESPACE( str[ j ] ) && j > i; j-- )
            return str[ i..j ]


    def str_to_var(self, str: str) -> Any:
            {
            int     i
            str = strip_string( str )
            switch( str[ 0 ] )
            {
            case '{':
            {
            str = str[ 1..strlen( str ) - 2 ]
            return map_array( explode( str, "," ), "str_to_var",
            self )


    def compile_r(self, name: str, clone: int) -> MudObject:
            object r
            r = prop_to_fun( name, r_funcs, "\"/obj/virtual_room.c\"",
            "virtual_room.h", 1 )
            r.reset()
            return r


    def compile_ob(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, o_funcs, "\"/std/object.c\"",
            "virtual.h", clone )


    def compile_arm(self, name: str, clone: int) -> MudObject:
            if (name[0 .. 19] == "/obj/armours/shield/")
            return prop_to_fun(name, arm_funcs, "\"/obj/shield.c\"",
            "virtual.h", clone )
            return prop_to_fun( name, arm_funcs, "\"/obj/armour.c\"",
            "virtual.h", clone )


    def compile_clo(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, clo_funcs, "\"/obj/clothing.c\"",
            "virtual.h", clone )


    def compile_sca(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, sca_funcs, "\"/obj/scabbard.c\"",
            "virtual.h", clone )


    def compile_wep(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, wep_funcs, "\"/obj/weapon.c\"",
            "virtual.h", clone )


    def compile_mon(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, mon_funcs, "\"/obj/monster.c\"",
            "virtual.h", clone )


    def compile_food(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, food_funcs, "\"/obj/food.c\"",
            "virtual.h", clone )


    def compile_cont(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, cont_funcs, "\"/obj/cont_medium.c\"",
            "virtual.h", clone )


    def compile_clotrans(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, clotrans_funcs, "\"/obj/clothing_transport.c\"",
            "virtual.h", clone )


    def compile_imp(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, o_funcs, "\"/obj/implement.c\"",
            "virtual.h", clone )


    def set_debug_status(self, d_stat: int) -> int:
            debug_file=d_stat
            return debug_file



class Compiler(MudObject):

    data = 'read_file( file )'
