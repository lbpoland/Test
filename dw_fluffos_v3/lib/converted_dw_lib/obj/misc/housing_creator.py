# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/housing_creator.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("ball")
            set_short("small jade ball")
            add_adjective(({"small", "jade"}))
            set_long("This non-descript jade ball can be used to make player houses.\n")
            set_read_mess((: list_plans() :))
            set_weight(1)
            set_value(0)
            seteuid("Room")


    def init(self, ) -> None:
            this_player()->add_command("make", self,
            "<word'floor plan'> <word'orientation'> "
            "<word'location'> <word'outside'> <word'region'> <string:quoted'address'>",
            (: do_create($4[0], $4[1], $4[2], $4[3], $4[4], $4[5], 0, 1) :) )
            this_player()->add_command("makereal", self,
            "<word'floor plan'> <word'orientation'> "
            "<word'location'> <word'outside'> <word'region'> <string:quoted'address'>",
            (: do_create($4[0], $4[1], $4[2], $4[3], $4[4], $4[5], 0, 0) :) )
            this_player()->add_command("maketest", self,
            "<word'floor plan'> <word'orientation'> "
            "<word'location'> <word'outside'> <word'region'> <string:quoted'address'>",
            (: do_create($4[0], $4[1], $4[2], $4[3], $4[4], $4[5], 1, 1) :) )


    def list_plans(self, ) -> str:
            string ret, str
            string plan
            ret = "To create a house use:\n"
            "  'make <floor plan> <orientation> <location> <outside> <region>\n"
            "        <address>' where:\n"
            "  'makereal <floor plan> <orientation> <location> <outside> <region>\n"
            "        <address>' where:\n"
            "  'makeforce <floor plan> <orientation> <location> <outside> <region>\n"
            "        <address>' where:\n"
            "  floor plan is one of the standard floor plans\n"
            "  orientation is its orientation (ie. the direction you enter it to)\n"
            "  location is the directory to write the houses files into\n"
            "  address is a the unique address for the house\n"
            "  region is the region of the house\n"
            "The 'makereal' command will add the house into the housing handler, "
            "the 'make' command will do a normal test make and the 'makeforce' "
            "will overwrite any existing housing files.\n\n"
            "Example:\n"
            "$I$5=   makereal twobedhouse south /d/am/fluff/housing OUT+room1 am \"12 Fluff Street\"\n\n$I$0="
            "The following floorplans are available:\n"
            str = ""
            foreach(plan in get_dir(PATH + "*")) {
            if(plan != "." && plan != ".." && file_size(PATH + plan) == -2 )
            str += plan + "\n"



class Housing_creator(MudObject):
