# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/findc_orpse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str) -> int:
            object *cs, c
            string r
            r = "player corpse objects\n"
            cs = filter( children( "/obj/corpse" ), (: $1 && $1->query_property(
            "player" ) :) )
            if( !arg ) {
            foreach( c in cs ) r += file_name( c ) + " - " + c.query_owner() +
            " - " + ( environment( c ) ? file_name( environment( c ) ) :
            "In void" ) + "\n"
            await  this_player().send(r )
            await  this_player().send(sizeof( cs ) + " player corpses.\n" )
            } else {
            cs = filter( cs, (: $1 && $1.query_ownership() == $( arg ) :) )
            if( sizeof( cs ) ) {
            r = "Corpse objects of " + arg + ": \n"
            foreach( c in cs ) r += file_name( c ) + " in " + (
            environment( c ) ? file_name( environment( c ) ) : "void" ) + "\n"
            await  this_player().send(r )
            } else {
            await  this_player().send(arg + " has no corpses loaded.\n" )


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Findc_orpse(MudObject):
