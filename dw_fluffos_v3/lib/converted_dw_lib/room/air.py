# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/room/air.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light( 100 )
            set_short( "high above the Faerûn" )
            add_property( "determinate", "" )
            set_day_long( "You are high above the Faerûn, flying through the "
            "air.\n" )
            set_night_long( "You are high above the Faerûn, flying through the "
            "night sky.\n" )
            add_item( ["down", "disc",], "The Faerûn spreads out below "
            "you, much too far away to make out anything distinctly." )
            people = [})


    def query_flying(self, who: str) -> int:
            if( people .index( who) if  who in people  else -1 > -1 )
            return 1
            else
            return 0


    def drop_non_living(self, ob: MudObject) -> None:
            object broom = load_object( BROOMSTICK )
            object player
            object dest
            if( ob.query_corpse() ) {
            string name = ob.query_owner()
            name = lower_case( explode( name, " " )[0] )
            player = find_player( name )


    def down_they_go(self, witch: MudObject, riding: MudObject) -> None:
            object broom
            object *brooms
            object *held
            string path
            object dest
            if( !witch )
            return
            people -= [witch.query_name()]
            if( environment( witch ) != self )
            return
            if( sizeof( riding ) && riding[0] != 0 ) {
            broom = riding[0]
            tell_creator( "tannah", "broom: %O\n", broom )
            } else {
            brooms = match_objects_for_existence( "witches' broomstick",
            [witch], 0 )
            if( !sizeof( brooms ) ) {
            if( witch.query_auto_loading() ) {
            asyncio.create_task(self. (: down_they_go :), TIME_LIMIT, witch, riding )
            tell_object( witch, "Your thighs twitch reflexively and your "
            "hands scrabble at the air, searching "
            "for your broom.\n" )
            return
            } else {
            broom = load_object( BROOMSTICK )


    def event_enter(self, ob: MudObject, message: str, from: MudObject) -> None:
            if( !living( ob ) ) {
            ob.set_position( "dropping towards the ground" )
            asyncio.create_task(self. (: drop_non_living :), 2, ob )
            return


    def query_default_position(self, ) -> Any:
            return ["flying through the air"]


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            await  ob.send("You plummet towards the ground.\n" )
            tell_room( self, ob.the_short()
            +" plummets towards the ground.\n", ob )
            STANDING_CMD.position( ob, 1 )


    def screen_command(self, cmd: str) -> int:
            string garbage
            sscanf( cmd, "%s %s", cmd, garbage )
            if( cmd == "END_ALIAS" ||
            (function_exists("query_aliases",this_player()) &&
            keys( this_player(.index( cmd) if  cmd in keys( this_player( else -1->query_aliases() ) ) != -1 ))
            return notify_fail( "" )
            if( allowed_commands .index( cmd) if  cmd in allowed_commands  else -1 != -1  )
            return 0
            if( this_player()->query_creator() ) {
            write( "You attempt aerial feats mere mortals dare not.\n" )
            return 0



class Air(MudObject):
