# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/mag_eff_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def block(self, thing: MudObject) -> int:
            if ( !thing.query_closed() )
            return 0
            return (int)thing.query_property( "enchantment block" )


    def ambient_enchantment(self, thing: MudObject) -> int:
            int i, total
            object *tops
            tops = [thing]
            while ( environment( tops[ 0 ] ) ) {
            tops = [environment( tops[ 0 ] )] + tops


    def do_effect(self, number: int, name: str, place: MudObject) -> None:
            int i
            string word
            object thing, *things
            switch( number ) {
            case 0:
            tell_room( place, "How curious.\n" )
            break
            case 1:
            tell_room( place, name +" spins slowly in mid-air, then "+
            "vanishes with a small \"pop!\"\n" )
            break
            case 2:
            i = random( 4 )
            tell_room( place, name +" sparkles and turns into a small "+
            ["yellow", "green", "hairy", "spotted"][ i ] +" caterpillar.\n" )
            thing = clone_object( "/obj/monster" )
            thing.set_name( "caterpillar" )
            thing.set_short( ["yellow", "green", "hairy", "spotted"][ i ]
            +" caterpillar" )
            thing.add_adjective( ["yellow", "green", "hairy", "spotted"][ i ] )
            thing.set_main_plural( ["yellow", "green", "hairy", "spotted"][ i ]
            +" caterpillars" )
            thing.add_plural( "caterpillars" )
            thing.set_long( "This is a small, common or garden caterpillar.\n" )
            thing.set_race( "caterpillar" )
            thing.set_level( 1 )
            thing.move( place )
            break
            case 3:
            tell_room( place, name +" vanishes with a sharp \"spang!\"\n"+
            "A moment later, you hear a small thunderclap.\n" )
            break
            case 4:
            tell_room( place, "Balefire blossoms, and "+ name +" turns into "+
            "a bunch of flowers.\n" )
            thing = clone_object( "/std/object" )
            thing.set_name( "flowers" )
            thing.set_short( "bunch of flowers" )
            thing.set_main_plural( "bunches of flowers" )
            thing.add_adjective( ["bunch", "bunches", "of"] )
            thing.add_plural( "bunches" )
            thing.set_long( "A nice bunch of flowers.\n" )
            thing.set_weight( 10 )
            thing.set_value( 100 )
            thing.move( place )
            break
            case 5:
            tell_room( place, "With a small gout of flame, "+ name +" begins "+
            "to accelerate.\n" )
            switch( (string)place.query_property( "location" ) ) {
            case "outside":
            tell_room( place, name +" vanishes into the distance.\n" )
            break
            default:
            tell_room( place, "There is a small puff of burning dust as "+
            name +" passes through a wall.\n" )


    def add_octonite_crystal(self, crystal: MudObject) -> None:
            int i, when
            when = time() + roll_MdN( 5, 60 )
            if ( !sizeof( _octonite ) ) {
            _octonite = [crystal, when]
            schedule_next()
            } else {
            for ( i = 0; i < sizeof( _octonite ); i += 2 ) {
            if ( when < _octonite[ i + 1 ] ) {
            break


    def extra_look(self, thing: MudObject) -> str:
            if ( explode( file_name( thing ), "#" )[ 0 ] != "/obj/magic/octonite" ) {
            return ""



class Mag_eff_handler(MudObject):
