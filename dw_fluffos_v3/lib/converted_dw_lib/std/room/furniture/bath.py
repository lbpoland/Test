# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/bath.c (2003 FluffOS v3) for Forgotten Realms MUD
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
            add_command( "lie", "in <direct:object>")
            add_command( "sit", "in <direct:object>")
            add_command( "kneel", "in <direct:object>")
            add_command( "stand", "in <direct:object>")
            add_command( "leave", "<direct:object>")
            add_command( "fill", "<direct:object>")
            add_command( "empty", "<direct:object>")
            add_command( "splash", "<indirect:living:here>")
            add_command( "wash", "<indirect:living:here>")


    def can_player_get_in_it(self, ) -> int:
            if (environment(self)!=environment(this_player())) {
            this_player()->add_failed_mess(self, "The " + self.short() + " needs to "
            "be on the floor for you to get in it.\n")
            return 0


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


    def do_lie(self, ) -> int:
            object player
            if (!can_player_get_in_it()) {
            return 0


    def do_sit(self, ) -> int:
            object player
            if (!can_player_get_in_it()) {
            return 0


    def do_kneel(self, ) -> int:
            object player
            if (!can_player_get_in_it()) {
            return 0


    def do_stand(self, ) -> int:
            object player
            if (!can_player_get_in_it()) {
            return 0


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            if (ob==this_player() && this_player()->query_position_on() == self) {
            this_player()->return_to_default_position(1)


    def do_leave(self, ) -> int:
            if (this_player()->query_position_on() == "the "+self.short()) {
            this_player()->return_to_default_position(1)
            await this_player().send("You clamber out of the " + self.short() + ".\n" )
            tell_room(environment(self), this_player()->short()+" clambers "
            "out of the " + self.short() + ".\n", this_player() )


    def do_splash(self, indirect_obs: MudObject) -> int:
            if (environment(self)!=environment(this_player())) {
            this_player()->add_failed_mess(self, "The " + self.short() + " needs to "
            "be on the floor for you to splash with it.\n")
            return 0


    def do_wash(self, indirect_obs: MudObject) -> int:
            if (!can_player_get_in_it()) {
            return 0


    def query_baths(self, ) -> int:
            return 1


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



class Bath(MudObject):
