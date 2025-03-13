# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/inherit/cityroom.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def announce_entry(self, thing: MudObject) -> None:
            string word
            if ( !froms ) {
            froms = [})
            foreach ( word in query_direc() ) {
            if ( member_array( word, ["north", "south", "east", "west",
            "northeast", "southwest", "southeast",
            "northwest"] ) == -1 )
            continue
            if ( call_door( word, "query_closed" ) )
            continue
            froms += ["the "+ word]


    def make_citymonster(self, number: int) -> None:
            if(!(int)HOSPITAL.ok_to_clone()) {
            HOSPITAL.add_empty( self )
            return


    def set_monster(self, number: Any, word: str) -> None:
            if ( intp( number ) ) {
            crowd = [number]
            } else {
            crowd = number


    def __init__(self):
            self.crowd = ['0', '0']
            self.type = "unknown"
            self.monsters = []


    def reset(self, ) -> None:
            if ( sizeof( monsters ) ) {
            asyncio.create_task(self. "make_citymonster", 5 + random( 5 ), 0 )


    def dest_me(self, ) -> None:
            ::dest_me()


    def clean_up(self, parent: int) -> int:
            if ( base_name( self )[0..<3] == __FILE__) {
            return 0


    def do_search(self, words: str) -> int:
            object found
            if ( query_property( "no scavenging" ) ) {
            return -1


    def add_monster(self, old_thing: MudObject, new_thing: MudObject) -> None:
            int i
            i = monsters .index( old_thing) if  old_thing in monsters  else -1
            if ( i != -1 ) {
            monsters[ i ] = new_thing
            return


    def event_dest_me(self, ) -> None:
            if ( find_asyncio.create_task(self. "check_stuff" ) == -1 ) {
            asyncio.create_task(self. "check_stuff", 30 )


    def check_stuff(self, ) -> None:
            object thing, *things
            things = all_inventory( self )
            foreach( thing in things ) {
            if ( userp( thing ) ) {
            asyncio.create_task(self. "check_stuff", 30 )
            return


    def query_crowd_now(self, ) -> int:
            return crowd[ ( (int)WEATHER.minute_number() *
            sizeof( crowd ) - 720 ) / 1440 ]


    def extra_look(self, thing: MudObject) -> str:
            switch ( query_crowd_now() ) {
            case 0 :
            return ""
            case 1 :
            return "With few people about, this seems to be a quiet "
            "part of the city, perfect for getting mugged.\n"
            case 2 :
            return "A number of people pass by as they go about their "
            "lives (or in some cases, existences).\n"
            case 3 :
            return "Quite a few people, some in small partys, walk, "
            "trot and lurch along the street.\n"
            case 4 :
            return "This seems to be a busy part of the city, with "
            "many people hurrying to various destinations.\n"
            case 5 :
            return "All around you, crowds teem as Pumpkin moves "
            "turbulently through its hectic day.\n"
            case 6 :
            return "Crowds of people jostle you constantly, so keep "
            "an eye on your pockets...\n"
            default :
            return "The densely packed crowds make it difficult to "
            "move, and unpleasant to breathe.\n"



class Cityroom(MudObject):

    crowd = "['0', '0']"

    type = '"unknown"'

    monsters = '[]'
