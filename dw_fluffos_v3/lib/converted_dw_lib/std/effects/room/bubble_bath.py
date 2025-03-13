# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/room/bubble_bath.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_surface_water(self, room: MudObject) -> int:
            return room.query_surface() ||
            sizeof(filter(all_inventory(room), (: $1.query_baths() :)))


    def beginning(self, room: MudObject, args: Any) -> None:
            object uproom
            tell_room( room, "As the liquid enters the water it diffuses into "
            "a "+ args[1][0] +" coloured cloud.\n" )
            if(query_surface_water(room))
            tell_room( room, "A gentle fragrance of " + args[1][1] +
            " fills the room.\n")
            else if(uproom = find_object(room.query_destination(room->query_up_dir())))
            uproom.add_effect(PATH + "bubble_bath", args)
            room.submit_ee( "bubblebubble", ({10,30}), EE_CONTINUOUS )
            room.submit_ee( 0, args[0], EE_REMOVE )
            room.add_extra_look( self )
            room->add_item(args[1][0] + " bubbles", "These " + args[1][0] + " coloured "
            "bubbles fill the room.")


    def end(self, room: MudObject, args: Any, id: int) -> None:
            int index, count
            string type =(room.query_surface()?"fragrant":"colourful")
            tell_room( room, "The last of the bubbles disappear with a " + type +
            " *pop*.\n" )
            room.remove_extra_look( self )
            count = sizeof(args)
            for (index = 1; index < count; index++ )
            room.remove_item( args[index][0] + " bubbles" )


    def extra_look(self, room: MudObject) -> str:
            int *enums
            int count, size
            mixed  shades=({})
            string bubblez
            string type
            enums = room.effects_matching( query_classification() )
            type = (room.query_surface()?"smelling":"looking")
            if ( !sizeof ( enums )) return ""
            shades = room.arg_of( enums[0] )
            if ( !sizeof ( shades )) return ""
            if ( sizeof ( shades ) == 1 )
            bubblez = "A multitude of " + shades[1][0] +" coloured bubbles fill the "
            "room, " + type +  " delicately of " + shades[1][1] + ".\n"
            if ( sizeof ( shades ) > 1 ) {
            size = sizeof ( shades )
            bubblez = "The room is filled with " + shades[1][0]
            for ( count = 2; count < size; count++ ) {
            if ( count != size-1 ) {
            bubblez += ", "


    def bubblebubble(self, room: MudObject, args: Any) -> None:
            int index = 0
            string type = (query_surface_water(room)?"fragrance":"colours")
            string where= (query_surface_water(room)?"air":"water")
            while (!index) index = random(sizeof(args))
            tell_room( room, "The gentle " + type + " of " + args[index][1] + " floats "
            "through the " + where + " as some of the " + args[index][0] + " bubbles "
            "pop.\n")



class Bubble_bath(MudObject):
