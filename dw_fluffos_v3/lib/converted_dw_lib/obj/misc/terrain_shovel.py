# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/terrain_shovel.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "shovel" )
            set_short( "ceremonial shovel" )
            add_adjective( "ceremonial" )
            set_long( "This is a small ceremonial shovel, carried by those "+
            "responsible for the care, upkeep and expansion of "+
            "dungeons.\n" )


    def init(self, ) -> None:
            if ( this_player()->query_creator() ) {
            add_action( "do_add", "add" )
            add_action( "do_remove", "remove" )
            add_action( "do_visit", "visit" )


    def do_add(self, words: str) -> int:
            int i, distance, level, *new_co_ord, *old_co_ord, *vector
            string direc, file, terrain, type
            object room, *things
            if ( !words )
            return notify_fail( "Add what?\n" )
            if ( sscanf( words, "%s %s %s", type, file, direc ) != 3 )
            return notify_fail( "Syntax: add fixed|floating <file> <direction>\n" )
            i = STD_ORDERS .index( direc) if  direc in STD_ORDERS  else -1
            if ( i == -1 )
            return notify_fail( capitalize( direc ) +" is not a valid "+
            "direction.\n" )
            room = environment( this_player() )
            if ( room.query_exit( direc ) )
            return notify_fail( "There is already an exit to the "+
            direc +".\n" )
            vector = STD_ORDERS[ i + 1 ]
            if ( file_size( file +".c" ) < 0 )
            return notify_fail( capitalize( file ) +" does not exist.\n" )
            file.force_load()
            if ( !find_object( file ) )
            return notify_fail( capitalize( file ) +" will not load.\n" )
            distance = (int)file.query_room_size() +
            (int)room.query_room_size()
            old_co_ord = (int *)room.query_co_ord()
            if ( sizeof( old_co_ord ) != 3 )
            return notify_fail( "Environment does not have coordinates.\n" )
            new_co_ord = allocate( 3 )
            for ( i = 0; i < 3; i++ )
            new_co_ord[ i ] = old_co_ord[ i ] - distance * vector[ i ]
            terrain = (string)room.query_property( "terrain name" )
            if ( !terrain )
            return notify_fail( "Environment is not in the terrain "+
            "handling system.\n" )
            switch( type ) {
            case "fixed" :
            i = (int)TERRAIN_MAP->add_fixed_location( terrain,
            file, new_co_ord )
            break
            case "floating" :
            i = (int)TERRAIN_MAP->add_floating_location( terrain,
            file, new_co_ord, level )
            break
            default :
            return notify_fail( "Type must be fixed or floating.\n" )


    def do_remove(self, ) -> int:
            write( "This function has not been written yet.\n" )
            return 1


    def do_visit(self, words: str) -> int:
            int x, y, z
            string terrain
            object room
            if ( !words )
            return notify_fail( "Visit where?\n" )
            if ( sscanf( words, "%s %d %d %d", terrain, x, y, z ) != 4 )
            return notify_fail( "Syntax: visit <terrain> <x co-ord> "+
            "<y co-ord> <z co-ord>\n" )
            room = (object)TERRAIN_MAP.find_location( terrain, [x, y, z] )
            if ( !objectp( room ) )
            return notify_fail( "There is no location at ("+ x +","+ y +","+ z +
            ") in \""+ terrain +"\".\n" )
            this_player()->move_with_look( room, "There is a strange smell, like "+
            "freshly broken earth, and $N appear$s.", "With a squelch, "+
            "$N vanish$s." )
            return 1



class Terrain_shovel(MudObject):
