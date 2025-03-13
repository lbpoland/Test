# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/sink_inherit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def extra_look(self, ) -> str:
            object *stuff
            string answer = ""
            stuff = all_inventory( self )
            if (water) {
            if (dirt >= sizeof(dirt_messages)) {
            dirt = sizeof(dirt_messages) - 1


    def long_status(self, ) -> str:
            return ""


    def init(self, ) -> None:
            ::init()
            add_command( "fill", "<direct:object>")
            add_command( "empty", "<direct:object>")
            add_command( "splash", "<indirect:living:here>")
            add_command( "wash", "<indirect:living:here>")


    def wet_everyone_in(self, ) -> None:
            object *victims
            if (!water) {
            return


    def reset(self, ) -> None:
            wet_everyone_in()


    def do_fill(self, ) -> int:
            object player
            player=this_player()
            if (water) {
            player.add_failed_mess(self, "The " + self->short() + " is "
            "already full of water.\n")
            return 0


    def do_empty(self, ) -> int:
            object player
            player=this_player()
            if (!water) {
            player.add_failed_mess(self, "The " + self->short() + " is "
            "already as empty as it gets.\n")
            return 0


    def do_splash(self, indirect_obs: MudObject) -> int:
            if (!water) {
            this_player()->add_failed_mess(self, "It's not a bad idea,  "
            "but maybe you'd need some water in the " + self.short() +
            "before you can splash.\n")
            return 0


    def do_wash(self, indirect_obs: MudObject) -> int:
            if (!water) {
            this_player()->add_failed_mess(self, "It's not a bad idea,  "
            "but maybe you'd need some water in the " + self.short() +
            "before you can wash.\n")
            return 0


    def zap_bad_effects(self, who: MudObject) -> None:
            int i, flag, *enums
            class effect *effs
            dirt++
            effs = (class effect *)who.query_effs()
            enums = (int *)who.effects_matching( "body.smell" )
            i = sizeof( enums )
            if ( !random(dirt) && i ) {
            i = random( i )
            flag = 1
            write( "The antiseptic power of the soap defeats "+
            (string)effs[ enums[ i ] ]->ob_name->smell_string( who,
            effs[ enums[ i ] ]->arg ) +".\n" )
            who.delete_effect( enums[ i ] )
            dirt ++



class Sink_inherit(MudObject):
