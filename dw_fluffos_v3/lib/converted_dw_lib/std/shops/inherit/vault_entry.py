# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/vault_entry.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_vault_exit(self, direc: str, dest: Any, type: str) -> None:
            vault_room = dest
            add_exit(direc, dest, type)
            modify_exit( direc, ["function", "check_customer"] )
            modify_exit( direc, ["closed", 1}))


    def apply_for_account(self, ) -> int:
            string owner
            object container
            if(!proprietor || environment(proprietor) != self)
            return notify_fail("The vault is closed since the proprietor is "
            "missing.\n")
            this_player()->add_succeeded_mess( self, "", [}) )
            write("You ask for an account.\n")
            say((string)this_player()->one_short() +" asks for an account.\n")
            owner = (string)this_player()->query_name()
            if ( master()->file_exists( VAULT_SAVE +vault_name+ "/"+ owner +".o" ) ||
            query_property( owner ) )
            {
            if ( this_player()->query_property( "vault warned" ) ) {
            proprietor.do_command( "glare "+ this_player()->query_name() )
            proprietor->do_command( "say I just said, you already have an "
            "account." )
            return notify_fail("")


    def init(self, ) -> None:
            add_command( "apply", "for [an] account", (: apply_for_account :) )


    def check_customer(self, verb: str, thing: MudObject, special: str) -> int:
            string owner
            object vroom
            if(!proprietor || environment(proprietor) != self)
            return notify_fail("The vault is closed since the proprietor is "
            "missing.\n")
            if( !interactive(thing) )
            return 0
            owner = (string)thing.query_name()
            if ( !master()->file_exists( VAULT_SAVE +vault_name+ "/" + owner +".o" ) &&
            !query_property( owner ) )
            {
            tell_object( thing, PTS+
            " intercepts you.\n" )
            tell_room( self, PTS+" intercepts "+
            (string)thing.the_short() +".\n",
            thing )
            if ( thing.query_property( "vault warned" ) ) {
            proprietor.do_command( "glare "+ thing->query_name() )
            proprietor->do_command( "say I just said, you don't have an account "
            "so I won't let you in!" )
            return notify_fail("")


    def check_idler(self, who: MudObject) -> None:
            if(who && base_name(environment(who)) == vault_room) {
            tell_object(who, "You've been in here too long so " + PTS + " comes and "
            "drags you out.\n")
            who->move_with_look(self,
            "$N is dragged out of the vault by the hair.",
            "$N is dragged out of the vault by the hair.")


    def player_quitting(self, who: MudObject, env: MudObject) -> None:



class Vault_entry(MudObject):
