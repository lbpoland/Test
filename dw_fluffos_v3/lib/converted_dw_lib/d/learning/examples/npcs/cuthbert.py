# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/examples/npcs/cuthbert.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "cuthbert" )
            set_short( "Cuthbert" )
            add_property("determinate", "")
            add_alias( ({"npc", "warrior", "man"}) )
            set_long("Cuthbert is a fashion victim.  Not content with off the peg "
            "stuff, he wants clothing unique to him.  Fair enough, let's give him"
            " some.\n")
            basic_setup ("human", "warrior", 50)
            set_gender( 1 )
            add_language( "common" )
            set_language( "common" )
            load_chat( 50, ({
            1, ":checks his equipment.",
            1, ":feels all snuggly and warm in his new clothes."
            }) )
            load_a_chat( 150, ({
            1, "'Oof!",
            1, ":is happy to die so you can learn.",
            1, "You feel Someone is waiting in the wings."}) )
            ARMOURY->request_item( "short sword",
            70+random(30))->move( TO )
            ARMOURY->request_item( "baggy leather loincloth",
            70+random(30))->move( TO )
            ARMOURY->request_item( "metal helmet",
            70+random(30))->move( TO )
            trousers = clone_object( "/obj/clothing" )
            trousers.set_name( "britches" )
            trousers.add_adjective(({"pair", "of"}))
            trousers.set_short( "pair of britches" )
            trousers.add_alias("trousers")
            trousers->set_long( "These are funky purple flaired britches, made of camel"
            "skin with beaver fur lining.\n" )
            trousers.set_value( 100 )
            trousers.set_weight( 7 )
            trousers.set_type( "trousers" )
            trousers.add_pocket( "side", 100 )
            trousers.add_pocket( "side", 100 )
            trousers.set_damage_chance( 10 )
            trousers.set_max_cond( 800 )
            trousers.set_cond( 600 + random( 200 ) )
            trousers.move( TO )
            cape = clone_object( "/obj/clothing" )
            cape.set_name( "cape" )
            cape.set_short( "orange cape" )
            cape.add_adjective("orange")
            cape->set_long( "Orange velvet has been made into a large cape.  It is bright "
            "and garish.\n" )
            cape.set_value( 100 )
            cape.set_weight( 7 )
            cape.set_type( "cape" )
            cape.set_damage_chance( 10 )
            cape.set_max_cond( 800 )
            cape.set_cond( 600 + random( 200 ) )
            cape.move( TO )
            init_equip()
            give_money( 10, 30, "Waterdeep pence" )



class Cuthbert(MudObject):
