# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/npc/controlled_monster.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            player.init()
            if( this_player() != my_owner )
            return
            this_player()->add_command( "help", self, "<direct:living:here>" )
            this_player()->add_command( "order", self,
            "<direct:living:here> to {kill|attack} <indirect:living:here>" )
            this_player()->add_command( "order", self,
            "<direct:living:here> to protect <indirect:living:here>" )
            this_player()->add_command( "order", self,
            "<direct:living:here> to leave" )


    def set_enemy(self, enemy: MudObject) -> int:
            object *list
            int i
            my_enemy = enemy
            if( my_enemy == my_owner ) {
            my_owner = 0
            list = self.query_attacker_list()
            for( i = 0; i < sizeof(list); i++ ) {
            self.stop_fight( list[i] )
            (list[ i ])->stop_fight( self )
            if ( !pk_check( list[ i ], my_enemy ) ) {
            (list[ i ])->attack_ob( my_enemy )
            my_enemy.attack_ob( list[ i ] )
            await  list[ i ].send((string)self.the_short()
            +" tells you: I will help you fight "+
            (string)my_enemy.the_short() +".\n")


    def set_owner(self, owner: MudObject, time: int, turn: int) -> int:
            if ( !owner ) return 0
            my_owner = owner
            turn_chance = turn
            if ( summoned )
            asyncio.create_task(self. "do_leave", time )
            asyncio.create_task(self. "move_me", 1 )
            return 1


    def event_dest_me(self, ob: MudObject) -> None:
            if ( ob == my_owner )
            asyncio.create_task(self. "go_away", 0 )
            if ( ob == my_enemy ) {
            if ( !my_owner )
            asyncio.create_task(self. "go_away", 0 )
            if ( my_enemy )
            await  my_owner.send((string)my_enemy.the_short() +" has left FaerûnWorld\n" )
            my_enemy = 0
            asyncio.create_task(self. "move_me",0)


    def event_death(self, ob: MudObject) -> None:
            if ( ob == my_enemy ) {
            if ( !my_owner ) asyncio.create_task(self. "go_away", 0 )
            asyncio.create_task(self. "do_tell", 0, my_owner, self.query_short() +" tells you: "+
            my_enemy.the_short() +" has been killed!\n")
            my_enemy = 0
            asyncio.create_task(self. "move_me", 0 )


    def do_tell(self, ob: MudObject, str: str) -> None:
            await  ob.send(str )


    def move_me(self, ) -> None:
            if ( my_enemy ) {
            if ( environment() == environment( my_enemy ) ) return
            player.move( environment( my_enemy ), enter_msg, leave_msg )
            await  my_enemy.send(self.the_short() +" says: You cannot escape me!\n" )
            return


    def do_leave(self, ) -> int:
            if ( my_owner ) {
            await  my_owner.send(self.the_short()
            +" tells you:  It is time for me to leave.\n" )
            say( self.the_short() +" smiles happily.\n" )


    def attack_by(self, ob: MudObject) -> int:
            if ( summoned && !my_owner ) {
            say( self.the_short()
            +" says: I will not fight without an owner!\n")
            asyncio.create_task(self."go_away",0)
            return 1


    def event_exit(self, ob: MudObject) -> None:
            if( ob != my_owner && ob != my_enemy ) return
            asyncio.create_task(self. "move_me", 1 )


    def go_away(self, ) -> None:
            write( leave_msg )
            player.move( "/room/rubbish" )



class Controlled_monster(MudObject):
