# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/outsides/woodland.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def extra_look(self, ) -> str:
            string extra
            extra = ::extra_look()
            switch((string)WEATHER.query_season()) {
            case "spring":
            return extra + "Spring flowers are everywhere you look.\n"
            case "autumn":
            return extra + "The ground is littered with fallen leaves.\n"
            break
            default:
            return extra


    def do_get_rock(self, verb: str, dest: MudObject) -> Any:
            int rock_size
            string rock_type
            object rock
            if ( query_property( "rock object" ) )
            return ( rock = clone_object( (string)query_property( "rock object" ) ) )
            if ( undefinedp( rock_size = (int)query_property( "rock size" ) ) )
            rock_size = 3
            if ( !rock_size ) return 0
            rock = clone_object( "/obj/mineral" )
            if ( undefinedp( rock_type = (string)query_property( "rock type" ) ) )
            rock_type = ["cinnabar", "coal", "rosy-quartz", "chalk", "flint",
            "slate"][ random( 6 ) ]
            rock.make_mineral( rock_type, 1 + random( rock_size ) )
            if ( !( rock.move( this_player() ) ) ) return 1
            rock.dest_me()
            return 0


    def do_get_flower(self, verb: str, dest: MudObject) -> Any:
            string flower_type
            object flower
            if ( query_property( "flower object" ) )
            return (flower = clone_object((string)query_property("flower object")))
            if ((int)query_property("noflowers"))
            return 0
            flower = clone_object("/std/plant")
            if(undefinedp(flower_type = (string)query_property("flower type")))
            flower_type = ({"forgetmenot", "violet"})[ random(2) ]
            flower.set_plant(flower_type)
            flower.set_plant_type(flower_type)
            flower->set_plant_desc("A beautiful "+flower_type+" picked before its "+
            "time.\n")
            flower.set_main_plural(flower_type + "s")
            if (!(flower.move(this_player()))) return 1
            flower.dest_me()
            return 0


    def do_get_berry(self, verb: str, dest: MudObject) -> Any:
            object berry
            string berry_type
            if ((int)query_property("noflowers"))
            return 0
            berry_type = ({"blackberry", "raspberry", "blueberry", "strawberry",
            "blackcurrant"})[random(5)]
            berry = clone_object( "/obj/food" )
            berry.set_name(berry_type)
            berry.set_short(berry_type)
            berry->set_long("This is a lovely, plump "+berry_type+" it looks good "+
            "enough to eat.\n")
            berry.add_alias("berry")
            if (!(berry.move(this_player()))) return 1
            berry.dest_me()
            return 0


    def do_get_leaf(self, verb: str, dest: MudObject) -> Any:
            object leaf
            string leaf_type
            if ((int)query_property("noflowers"))
            return 0
            leaf_type = ({"maple", "oak", "sycamore", "ash", "silver birch"})[random(5)]
            leaf = clone_object("/std/object")
            leaf.set_name("leaf")
            leaf.set_short(leaf_type+" leaf")
            leaf->set_long("This is a dead "+leaf_type+" leaf.  Its natural green "+
            "has turned to shades of gold, red and brown.\n")
            leaf.add_adjective(leaf_type)
            if (!(leaf.move(this_player()))) return 1
            leaf.dest_me()
            return 0



class Woodland(MudObject):
