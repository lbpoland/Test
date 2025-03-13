# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/surface.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def make_shadow(self, thing: MudObject) -> None:
            object shadow
            shadow = clone_object( SURFACE_SHADOW )
            shadow.setup_shadow( thing, self )
            if ( !surface_shadows ) surface_shadows = [})
            surface_shadows += [shadow]


    def check_shadows(self, ) -> None:
            int i
            for ( i = 0; i < sizeof( surface_shadows ); i++ ) {
            if ( surface_shadows[ i ] ) {
            if ( environment() == (object)surface_shadows[ i ]->
            query_shadowed( surface_shadows[ i ] ) ) {
            surface_shadows[ i ]->destruct_shadow( surface_shadows[ i ] )
            surface_shadows = surface_shadows[0..i-1] + surface_shadows[i + 1..]
            i--


    def check_environment(self, ) -> None:
            if ( environment() ) {
            make_shadow( environment() )


    def dest_me(self, ) -> None:
            int i
            for ( i = 0; i < sizeof( surface_shadows ); i++ )
            if ( surface_shadows[ i ] )
            surface_shadows[ i ]->destruct_shadow( surface_shadows[ i ] )



class Surface(MudObject):
