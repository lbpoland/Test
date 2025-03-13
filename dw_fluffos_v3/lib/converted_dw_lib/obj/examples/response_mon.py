# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/examples/response_mon.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("guard")
            add_adjective(["big", "gate"])
            set_short("Big gate guard")
            set_long("This is one of the common guards of Amber.  "+
            "He looks quite big, maybe you shouldn't upset him...\n")
            set_race("human")
            set_class("fighter")
            set_level(45)
            set_al(250)
            set_gender(1)
            tale = ["There once was a frog with 5 legs.\n",
            "This frog was very very unhappy.\n",
            "All other frogs made fun of him.\n",
            "And no lady frog wanted to marry him.\n",
            "One day, a womble appeared, and bit one of his legs off.\n",
            "Since then the frog had 4 legs, and lived happily ever after.\n"
            })
            set_respond_to_with(([ ["help", "me"] : "'I can't help you." ,
            [["hi","hello","greetings"]] :
            ["'Hello $hcname$.",
            "emote salutes you."],
            [["remove","unwield","unhold"],
            ["axe","weapon"]] :
            "#remov",
            [["wield","hold"],
            ["axe","weapon"]] :
            "#wiel",
            ["tell" , "story"] :
            "#story" ]))
            weapc = clone_object("/obj/weapons/axe.wep")
            weapc.move(self)
            do_equip()


    def remov(self, ) -> int:
            init_command("unhold axe")


    def wiel(self, ) -> int:
            init_command("hold axe")


    def story(self, tpl: MudObject) -> None:
            command("'Very well, "+tpl.query_cap_name()+ " I will tell you a story.\n")
            set_stop_responding(1)
            asyncio.create_task(self."tell_story",2,0)


    def tell_story(self, arg: int) -> None:
            remove_asyncio.create_task(self."tell_story")
            if (arg == sizeof(tale)) {
            set_stop_responding(0)
            return



class Response_mon(MudObject):
