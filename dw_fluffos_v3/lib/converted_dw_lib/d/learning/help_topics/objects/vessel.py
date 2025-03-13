# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/objects/vessel.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("room of vessel and liquid examples")
            add_property( "determinate", "the " )
            set_long( "This room gives some simple examples of using vessels.  "
            "There should be a wine bottle, a wine glass, and a "
            "coffee cup in here.  There are also a few usage notes "
            "on the wall (\"read note1\", \"read note2\", etc).\n" )
            set_light( 100 )
            add_item( "note1",
            ["long", "This note describes how to use the vessels.",
            "read", "The vessels all have the following commands: "
            "pour, fill, drink, empty.  There are a few others, "
            "but they're mainly carry-overs from the old "
            "container code, and probably don't work correctly.  "
            "Try pouring from one object to another, drinking, etc.  "
            "Try mixing equal parts of wine and Klatchian coffee.  "
            "Use the \"stat\" command to check on the volumes (eg, "
            "\"stat bottle\", \"stat all in cup\").  If you want "
            "to start over with a fresh vessel, dest it and "
            "\"call reset() here\".\n"
            }) )
            add_item( "note2",
            ["long", "This is a little note on liquid units of measure.",
            "read", "The base unit for a liquid is the drop.  Four "
            "drops is roughly 1 cc, and 200 drops of water weighs "
            "one Faerûnworld weight unit.  Here are some common "
            "amounts (I believe these are all British measures, "
            "but I could have made an error):\n"
            "    1 teaspoon =      20 drops\n"
            "    1 tablespoon =    60 drops\n"
            "    1 ounce =        120 drops\n"
            "    1 cup =          960 drops\n"
            "    1 pint =        2400 drops\n"
            "    1 quart =       4800 drops\n"
            "    1 gallon =     19200 drops\n"
            }) )
            add_item( "note3",
            ["long", "This is a note on adding effects to food, "
            "especially liquids.",
            "read", "To add an effect to food so that it will be "
            "applied to the player when consumed, use "
            "add_eat_effect(<effect>, <arg>).  <arg> (which "
            "should be an integer) is multiplied by the weight "
            "of the amount consumed; for liquids, this is generally "
            "200 drops per weight unit.\n\n"
            "For example, the wine in the wine bottle adds the "
            "drunk effect; a final <arg> of 3900 for this effect "
            "will last 10 minutes on a player with constitution 13 "
            "(trust me on this).  If we want one pint (2400 drops) "
            "of wine to have this effect, the <arg> to "
            "add_eat_effect() should be 3900/(2400/200), or "
            "325.\n"
            }) )
            add_item( "note4",
            ["long", "This is a note on using continuous objects.",
            "read", "Continuous objects (those derived from "
            "/obj/cont_medium, such as /obj/food) are a way "
            "to have multiple identical instances of an item "
            "without having to have a clone for each one.  Each "
            "unique continuous object is identified by its "
            "\"medium alias\".  The medium alias must be a single "
            "word without embedded spaces; by convention, it is "
            "made by concatenating a series of capitalized words "
            "that describe it, such as \"RedWine\" or "
            "\"GroundPurpleMushroom\".  All objects with a common "
            "medium alias in the same environment are combined "
            "into a single object.  Also, the reaction handler "
            "uses the medium alias to identify objects that "
            "react with one another.\n"
            }) )
            add_exit( "back", LEARNING +"search", "path" )
            add_exit( "exit", ENTRANCE, "path" )
            add_property( "commented functions",
            ["make_bottle", "add_eat_effect", "set_medium_alias",
            "set_max_weight", "set_max_volume"] )
            add_property( "keywords",
            ["bottle", "vessel", "liquid"] )


    def reset(self, ) -> None:
            asyncio.create_task(self. "check_vessels", 3 )


    def check_vessels(self, ) -> None:
            object wine, coffee
            if ( !wine_bottle || ( environment( wine_bottle ) != self ) ) {
            wine_bottle = clone_object( "/obj/bottle" )
            wine_bottle.make_bottle( "green", 600 )
            wine_bottle->move( self, "Jeremy walks into the room and "
            "leaves $N before walking out again." )
            wine = clone_object( "/obj/reagents/generic_liquid.ob" )
            wine.set_name( "wine" )
            wine.set_short( "red wine" )
            wine.set_long( "This is a deep red wine, $amount_size$.\n")
            wine.set_medium_alias( "RedWine" )
            wine.add_adjective( "red" )
            wine.add_eat_effect( "/std/effects/ingested/drunk", 325 )
            wine.set_amount( 2400 )
            wine.move( wine_bottle )



class Vessel(Room):
