# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/add_item/args_char.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("add_item room #12, Getting character arguments ")
            set_light(100)
            set_long("add_item room #12, Getting character arguments\n"
            +"There is a large stone in the middle of the room.  It looks as "
            +"if you can engrave your name onto it.\nSource code.\n")
            add_item("large stone", ({
            "long",
            "It can be engraved."
            ,"engrave",
            [self, "do_engrave",
            "'into' %D 'the' text' %s" ]
            }))
            add_item("source code", ["long",
            "It looks like some source code."
            ,"read",
            "The source code:\n"
            +"\n"
            +"   add_item(\"large stone\", ({\n"
            +"	        \"long\",\n"
            +"	                   \"It can be engraved.\"\n"
            +"		,\"engrave\",\n"
            +"			   [self, \"do_engrave\",\n"
            +"				\"'into' %D 'the' text' %s\" ]\n"
            +"	}));\n"
            +"\n\nRead also:  do_engrave\n"])
            add_item("do_engrave", ["long",
            "It looks like some source code."
            ,"read",
            "The source code:\n"
            +"int do_engrave(mixed a1,mixed a2,mixed a3,mixed a4, mixed a5, mixed a6)\n"
            +"{\n"
            +"     string mess;\n"
            +"        mess =  \"$N $V \"+a5[1]+\" into \"+a3+\".\\n\";\n"
            +"        this_player()->add_succeeded_mess(previous_object(),\n"
            +"					        mess,\n"
            +"					        ({}));\n"
            +"        return 1;\n"
            +"}\n"
            +"\n"])
            add_exit("east",ROOM+"args_object","door")
            add_exit("west",ROOM+"args_integer","door")
            add_exit("north",MAIN,"door" )


    def do_engrave(self, a1: Any, a2: Any, a3: Any, a4: Any, a5: Any, a6: Any) -> int:
            {
            string mess
            mess =  "$N $V "+a5[1]+" into "+a3+".\n"
            this_player()->add_succeeded_mess(previous_object(),
            mess,
            ({}))
            return 1



class Args_char(Room):
