# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/salve.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.apply_effects = ([ ])


    def init(self, ) -> None:
            this_player()->add_command( "apply", self, "<direct:object> to <indirect:object>")


    def add_apply_effect(self, word: str, number: int) -> int:
            if ( apply_effects[ word ] )
            apply_effects[ word ] += number
            else
            apply_effects[ word ] = number
            return apply_effects[ word ]


    def remove_apply_effect(self, word: str) -> None:
            if ( !undefinedp( apply_effects[ word ] ) )
            apply_effects = m_delete( apply_effects, word )


    def being_joined_by(self, thing: MudObject) -> None:
            int i, that, this
            string *words
            mapping new_effects
            that = (int)thing.query_amount()
            this = query_amount()
            if ( !( this + that ) )
            return
            new_effects = (mapping)thing.query_apply_effects()
            words = m_indices( apply_effects )
            for ( i = 0; i < sizeof( words ); i++ )
            if ( new_effects[ words[ i ] ] ) {
            new_effects[ words[ i ] ] *= that
            new_effects[ words[ i ] ] += this * apply_effects[ words[ i ] ]
            } else
            new_effects[ words[ i ] ] = this * apply_effects[ words[ i ] ]
            words = m_indices( new_effects )
            for ( i = 0; i < sizeof( words ); i++ )
            new_effects[ words[ i ] ] /= this + that
            apply_effects = new_effects


    def do_apply(self, indir: MudObject, dir_s: str, indir_s: str, args: Any) -> int:
            string *words
            int i
            if (environment(self) != this_player()) {
            write("You aren't holding the " + dir_s + ".\n")
            return 0


    def init_dynamic_arg(self, map: Any) -> None:
            if ( map[ "::" ] )
            ::init_dynamic_arg( map[ "::" ] )
            apply_effects = map[ "apply_effects" ]



class Salve(MudObject):

    apply_effects = '([ ])'
