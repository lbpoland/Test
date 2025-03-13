# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/chars/npc_example.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "ralph" )
            set_short( "Ralph the spotted giraffe" )
            add_property( "determinate", "" )
            add_adjective( "spotted" )
            set_main_plural("Ralph the spotted giraffes")
            add_plural(( { "ralphs", "giraffes" } ))
            add_alias(( { "giraffe", "Ralph" } ))
            set_long( "This is Ralph the spotted giraffe.  He is just an example in "
            "this file so I won't describe him although I should.  Well, "
            "okay then... He's like any normal giraffe except for his cool "
            "black specs and mop fringe.  He is coolnes personified.\n" )
            add_property( "unique", 1 )
            set_race( "horse" )
            set_class("wizard")
            set_height( 300 )
            set_weight( 1600 )
            set_gender( 1 )
            set_al( -500 )
            set_level( 15 )
            set_con(18)
            set_dex(18)
            set_str(16)
            set_wis(15)
            set_int(15)
            add_move_zone( "Short" )
            add_move_zone( "Filigree" )
            set_move_after( 50, 60 )
            set_virtual_move(1)
            load_chat( 90, ({
            3, "@grin",
            3, "@high5 $lname$",
            2, "@bless $lname$",
            1, "@moonwalk",
            1, "'Far out man.",
            1, ({
            "'Hey, if it isn't $lname$!",
            "'You're looking cool as usual!"
            }),
            1, ":tells you: Hey my man!  Watcha up to?",
            1, "'That's cool.",
            1, "'Chillin' out here, are we?",
            1, "@ruffle $lname$",
            1, "@wink $lname$",
            2, ":does a really complicated tap dance manoeuvre.",
            1, "'Let's do something wild and crazy...",
            1, ({
            "'Yoho, how's it hangin'?",
            "'I'm in a darn good mood today!"
            }),
            1, ":tells you: Ouch man, where the heck did you find those clothes?"
            }) )
            load_a_chat( 100, ({
            1, "'Wait till Hobbes hears about this!",
            1, "'It's SO uncool to fight!",
            1, "@scream",
            1, "You can't believe you're fighting such a nice creature as Ralph.",
            1, ":seems to wish he was somewhere else."
            }) )
            ARMOURY.request_weapon("meat cleaver", 80+random(20))->move(self)
            ARMOURY.request_armour("gigantic dog collar", 100)->move(self)
            ARMOURY.request_armour("straw hat", 80)->move(self)
            comb=clone_object("/d/am/items/comb")
            comb.move( self )
            init_equip()



class Npc_example(MudObject):
