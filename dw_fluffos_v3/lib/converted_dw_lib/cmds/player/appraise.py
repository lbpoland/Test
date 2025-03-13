# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/appraise.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_length_mess(self, number: int) -> str:
            int half_feet
            switch(number) {
            case 0:
            return "not very"
            case 1:
            return "an inch"
            case 2:
            return "a couple of inches"
            case 3:
            return "three inches"
            case 4:
            return "four inches"
            case 5..7:
            return "about six inches"
            case 8..10:
            return "about nine inches"
            case 11..14:
            return "about a foot"
            case 15..21:
            return "about a foot and a half"
            case 22..27:
            return "about two feet"
            case 28..33:
            return "about two and a half feet"
            default:
            half_feet = (number + 3)/6
            if( half_feet%2 ) {
            return "about " + query_num(half_feet/2) + " and a half feet"


    def query_dimensions_mess(self, thing: MudObject) -> str:
            return "is " + query_length_mess(thing.query_length()) + " long and " +
            query_length_mess(thing.query_width()) + " wide."


    def query_appearance_mess(self, thing: MudObject) -> str:
            string material_mess
            if( !sizeof(thing.query_materials()) ) {
            material_mess = "some unidentifiable material"


    def query_type_mess(self, thing: MudObject) -> str:
            if( thing.query_plant() ) {
            return "appears to be some sort of plant"


    def query_container_mess(self, thing: MudObject) -> str:
            int volume
            int size
            string str
            volume = thing.query_max_volume()
            if (thing.query_container()) {
            size = thing.query_max_size()


    def cmd(self, things: MudObject) -> int:
            object thing
            string mess
            string tmp
            if(!sizeof(things)) {
            add_failed_mess("For some reason, you "
            "have nothing to appraise.  Please bugrep this.\n", [}) )
            return 0



class Appraise(MudObject):
