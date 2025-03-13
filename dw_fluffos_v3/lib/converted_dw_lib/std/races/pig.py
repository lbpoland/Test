# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/pig.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "pig" )
            set_long( "A domesticated mammal, of the swine family.\n" )
            set_desc( "a domesticated mammal, of the swine family" )
            set_weight( 1200 )
            set_height( 50 )
            remove_bit( "nose" )
            remove_bit( "head" )
            remove_bit( "left front leg" )
            remove_bit( "right front leg" )
            remove_bit( "left rear leg" )
            remove_bit( "right rear leg" )
            add_bit( "head", "head", [0, 135, 0,
            "left eye", "right eye", "snout", "skull", "tongue", "left ear",
            "right ear"] )
            add_bit( "snout", "snout", ["head", 12, 0] )
            add_bit( "left front trotter", "trotter", [0, 180, 0, "left front hoof"] )
            add_bit( "right front trotter", "trotter", [0, 180, 0, "right front hoof"] )
            add_bit( "left rear trotter", "trotter", [0, 180, 0, "left rear hoof"] )
            add_bit( "right rear trotter", "trotter", [0, 180, 0, "right rear hoof"] )
            add_bit( "chop", "chop", [0, 1, 0] )
            add_bit( "tail", "tail", [0, 1, 0] )
            inedible += ["left front trotter", "right front trotter",
            "left rear trotter", "right rear trotter"]
            unrottable += ["left front trotter", "right front trotter",
            "left rear trotter", "right rear trotter"]
            set_stats( [2, 0, -2, 4, -4] )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "standard" )
            thing.remove_attack( "hoof" )
            thing.add_attack( "hoof", 60, [32, 10, 11],
            "blunt", "unarmed", 0 )
            thing.tactics( "response dodge" )



class Pig(MudObject):
