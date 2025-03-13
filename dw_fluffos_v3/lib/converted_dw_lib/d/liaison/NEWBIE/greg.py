# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/greg.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            add_property("determinate", "")
            set_name( "greg" )
            set_short("Greg" )
            set_main_plural("Gregs" )
            set_race( "human" )
            set_response_mon_understand_anything(1)
            set_gender( 1 )
            set_al(-500 )
            set_class( "fighter" )
            set_language( "general" )
            set_level( 100 + random( 100 ) )
            set_long( "This is Greg the combat instructor.  He looks pretty mean, but "
            "don't let appearances deceive you, he's a softy at heart.\n" )
            adjust_money( 10 + random( 40 ), "Waterdeep pence" )
            load_chat( 25, ({
            1, ":grunts.",
            1, "'Ug.",
            1, "'I am great.",
            1, "@flex",
            1, "'Look at my cool muscles.",
            }) )
            add_respond_to_with(["yes"], ["#yes"])
            add_respond_to_with(["no"], ["#no"])
            add_respond_to_with([["can", "may"],
            ["practise", "practice", "train"}),
            ["please"]],
            ["#request"] )
            add_respond_to_with([["hello", "hi", "gday",],
            ["womble", "all"]], ["'Hello $hcname$",
            "bow ? $hname$"])
            add_respond_to_with(["fuck", ["off", "you"]], ["'Same to you!",
            "skick $hname$"
            }))
            add_respond_to_with(["fuck"], "waggle $hname$")
            add_respond_to_with(
            ["@smile", "womble"], "smile $hname$")
            add_respond_to_with(
            [["@skick", "@spunch", "@jump", "@pat", "@slap"],
            "womble"], "glare $hname$")
            add_respond_to_with(
            [["@poke", "@glare", "@point"],
            "womble"], "peer sus at $hname$")
            add_respond_to_with(
            ["@grin", "womble"], "grin $hname$")
            add_respond_to_with(
            [["@caress", "@snuggle", "@nestle", "@love", "@throw"],
            "womble"], "waggle $hname$")
            add_respond_to_with(
            [["@kiss", "@french",],
            "womble"], "slap $hname$")
            add_respond_to_with([["@bing", "@womble",],
            "womble"], "smile bri $hname$")
            add_skill_level( "other.health", 50 + random( 50 ) )
            (ARMOURY.request_weapon("long sword", 75))->move(self)
            (ARMOURY.request_armour("ringmail", 80))->move(self)
            (ARMOURY.request_armour("metal clad boots", 80))->move(self)
            (ARMOURY.request_armour("metal gauntlets", 80))->move(self)
            init_equip()
            callouts = ([ ])


    def event_enter(self, ob: MudObject, message: str, from: MudObject) -> None:
            if(environment() == find_object("/room/rubbish")) {
            return ::event_enter(ob, message, from)


    def attack_by(self, thing: MudObject) -> int:
            tell_room(environment(), "Greg lifts a hand and slaps " + thing.one_short()
            + " sending " + thing.query_objective() + " flying across "
            "the room.\n", thing)
            write("Greg lifts a hand, almost as large as your head, and gives you a "
            "slap that sends you flying across the room.\n")
            write("You bash your head against the wall and the world starts "
            "spinning.\n")
            do_command("'Hey, that's not nice!")
            thing.add_effect("/std/effects/ingested/tranquil_sleep", 120)
            self.stop_fight(thing)
            thing.stop_fight(self)
            return 0


    def check_room(self, ) -> None:
            int room
            object ob
            queue = filter_array(queue,
            (: environment($1) == environment(self) :))
            if(sizeof(queue))
            ob = queue[0]
            if(queue.index(ob) if ob in queue else -1 == -1)
            return
            room = in_use.index(0) if 0 in in_use else -1
            if(room == -1) {
            do_command("'Ok " + ob.one_short() + ", unfortunately all the rooms are "
            "busy right now, but "
            "if you don't mind waiting a minute one will become free.")
            return


    def yes(self, ob: MudObject) -> None:
            if(offered.index(ob) if ob in offered else -1 == -1 || queue.index(ob) if ob in queue else -1 != -1)
            return
            queue += [ob]
            check_room()


    def no(self, ob: MudObject) -> None:
            if(offered.index(ob) if ob in offered else -1 == -1)
            return
            offered -= [ob]
            if ( environment(ob) == environment(self) ) {
            do_command("'Okay.  Well, come back if you feel like having a go later.")
            do_command("smile " + ob.query_name())


    def request(self, ob: MudObject) -> None:
            do_command("'Would you like to try out your skills " + ob.one_short() +
            "?")
            if(!sizeof(filter_array(ob.query_holding(), (: $1 && $1.query_weapon()
            :))))
            do_command("'You may want to buy a weapon at the shop before trying out "
            "your skills.")
            if(!offered)
            offered = [})
            offered += [ob]


    def query_using(self, room: int) -> MudObject:
            return in_use[room]


    def throw_out(self, ob: MudObject) -> None:
            int room
            room = in_use.index(ob) if ob in in_use else -1
            if(room != -1) {
            if(base_name(environment(ob)) == RPATHS[room]) {
            do_command(RNAMES[room])
            asyncio.create_task(self."tell_them", 2, ob, room)
            } else {
            in_use[room] = 0


    def tell_them(self, ob: MudObject, room: int) -> None:
            if(!ob) {
            do_command("combat")
            return


    def do_greeting(self, ob: MudObject) -> None:
            int room
            if(!ob || !interactive(ob) || queue.index(ob) if ob in queue else -1 != -1)
            return
            room = in_use.index(ob) if ob in in_use else -1
            if(room == -1) {
            do_command("'Hello " + ob.one_short() + ", welcome to the combat "
            "training area.")
            do_command("'Would you like to try out your skills?")
            if(!sizeof(filter_array(ob.query_holding(), (: $1 && $1.query_weapon()
            :))))
            do_command("'You may want to buy a weapon at the shop before trying out "
            "your skills.")
            } else {
            do_command("'I hope you had a productive time.  Would you like to have "
            "another go?")
            if(room != -1) {
            in_use[room] = 0
            check_room()



class Greg(MudObject):
