# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/pumpkin/hospital.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_keep_room_loaded(1)
            update = time()
            alignments = allocate( 50 )
            uniques = ([ ])
            if ( file_size( SAVE_FILE +".o" ) > 0 ) {
            unguarded( (: restore_object, SAVE_FILE :) )


    def query_blockage(self, this: str, other: str, number: int) -> int:
            if ( undefinedp( blockages[ this ] ) ) {
            if ( random( 100 ) >= BLOCK )
            number = -1
            blockages[ this ] = blockages[ other ] = number


    def housekeeping(self, ) -> None:
            object thing
            update = time()
            foreach( thing in users() ) {
            if ( thing.query_creator() )
            continue
            alignments[ random( sizeof( alignments ) ) ] =
            (int)thing.query_al()


    def pick_al(self, ) -> int:
            int one, *stats
            if ( !al_data ) {
            al_data = allocate( 3 )
            stats = allocate( 4 )
            foreach( one in alignments ) {
            stats[ 0 ] += one
            stats[ 1 ] += one * one
            if ( one > stats[ 2 ] )
            stats[ 2 ] = one
            if ( one < stats[ 3 ] )
            stats[ 3 ] = one


    def make_unique(self, word: str) -> int:
            if ( uniques[ word ] > time() )
            return 0
            uniques[ word ] = time() + 1 * 60 * 60
            unguarded( (: save_object, SAVE_FILE :) )
            return 1


    def add_mover(self, thing: MudObject) -> None:
            int number
            number = MAX_MOVERS / 2 + random( MAX_MOVERS / 2 )
            if ( !pointerp( movers[ number ] ) )
            movers[ number ] = [thing]
            else
            movers[ number ] += [thing]


    def get_monster(self, type: str) -> MudObject:
            object thing
            object ob
            switch( type ) {
            case "city" :
            case "pumpkin" :
            thing = get_monster( city[ random( sizeof( city ) ) ] )
            thing->add_property( "monster type", type +":"+
            (string)thing.query_property( "monster type" ) )
            thing.add_move_zone( "Pumpkin" )
            add_mover( thing )
            return thing
            case "dog":
            thing = clone_object( CHARS + "dog" )
            if ( random( 4 ) )
            thing.set_type( "small" )
            else
            thing.set_type( "large" )
            thing->add_effect( "/std/effects/npc/i_died",
            [HOSPITAL, "regen_after_death"])
            thing.add_effect( "/std/effects/npc/eat_edible" )
            thing.add_effect( "/std/effects/npc/savage_corpse" )
            thing.add_property( "monster type", type )
            thing.add_property("animal type", type)
            return thing
            case "child":
            thing = clone_object( CHARS + "child_human" )
            return thing
            case "cityguard":
            ob = clone_object(MONSTER)
            ob.add_property("monster type", type)
            ob.set_name("guard")
            ob.add_adjective("city")
            ob.set_main_plural( "city guards" )
            ob.set_short("city guard")
            ob->set_long("This is a city guard. He is supposed to protect the " +
            "city from undesirables. Sadly, Pumpkin isn't very fussy.\n")
            ob.set_race("human")
            ob.set_gender("male")
            ob.set_class("fighter")
            ob.set_level(8)
            ob.set_al( pick_al() / 5 )
            ob.adjust_money( 5 + random( 10 ), "Pumpkin pence" )
            ob->load_chat(10, ({
            3, "@grumble bitterly",
            1, "@daydream",
            1, "@sigh heavily"
            }) )
            ob->load_a_chat(50, ({
            1, "'Ouch!",
            1, "'Come on! I don't need this.",
            1, "'Be on your way!",
            }) )
            ARMOURY.request_weapon("long sword", 40+random(40))->move(ob)
            if(random(2))
            ARMOURY.request_armour("hard leather cap", 70 + random(30))->move(ob)
            ob.init_equip()
            return ob
            case "mercenary":
            ob = clone_object(MONSTER)
            ob.set_name("mercenary")
            ob.set_main_plural( "mercenaries" )
            ob.add_plural( "mercenaries" )
            ob.add_adjective("tough")
            ob.set_race("human")
            ob.set_class("fighter")
            ob.set_level( 50 + roll_MdN( 5, 50 ) )
            ob.set_al( pick_al() )
            ob.set_gender(random(2) + 1)
            ob->set_long("A tough battle scarred mercenary.  There are better "
            "ways of filling in an afternoon than messing with the "
            "likes of "+ob.query_objective()+".\n")
            ob.adjust_money( 5 + random( 50 ), "Waterdeep pence" )
            ob.adjust_money( 1 + random( 5 ), "Waterdeep dollar" )
            ob->load_chat(3, ({
            1, "'Anyone you don't like?",
            1, "'I'll do anything if the price is right?",
            1, "'Don't get me angry.  You won't like me when I'm angry."
            }))
            ob->load_a_chat(30, ({
            1, "'I'll show you who's boss.",
            1, "'You think you're so tough.",
            1, "The crowd runs in terror as the mercenary kills someone by "+
            "accident."
            }))
            get_weapon(ob, ({"bastard sword", "long sword", "morning star",
            "two-handed axe"}))
            get_armour(ob, ({"chainmail", "splintmail", "ringmail"}))
            ob.add_property("monster type", type)
            ob.init_equip()
            return ob
            case "rodent":
            ob = clone_object(MONSTER)
            ob.set_name("rat")
            ob.set_short("rat")
            ob.set_race("rat")
            ob.set_level( random( 1 + random( 3 ) ) )
            ob.add_alias("city rat")
            ob.set_main_plural("rats")
            ob.add_adjective("dirty")
            ob.add_adjective("city")
            ob->set_long("This is a large rat.  It appears to have done well "+
            "living in the city.\n"+
            "The pollution must not affect it too much.\n" )
            ob->load_chat( 5, ({
            1, ":squeaks.",
            1, ":sniffs the air, whiskers twitching.",
            1, ":checks for dwarves."
            }) )
            ob.set_wimpy( 10 )
            ob->load_a_chat( 50, ({
            1, ":squeals in pain.",
            1, ":twitches fearfully."
            }) )
            ob->add_effect("/std/effects/npc/i_died",
            [HOSPITAL, "regen_after_death"])
            ob.add_effect( "/std/effects/npc/eat_edible" )
            ob.add_effect( "/std/effects/npc/savage_corpse" )
            ob.add_property("monster type", type)
            ob.add_property("animal type", type)
            return ob
            case "cockroach":
            ob = clone_object(MONSTER)
            ob.set_name("cockroach")
            ob.set_short("cockroach")
            ob.set_race("cockroach")
            ob.set_level( random( 1 + random( 3 ) ) )
            ob.set_main_plural("cockroaches")
            ob.add_adjective("dirty")
            ob.add_alias("roach")
            ob->set_long( "This is a huge dirty great big cockroach, the size of "
            "your hand at least.  It waves its feelers at you and looks "
            "horrible and black.  Not only can cockroaches survive fires, "
            "plagues, earthquakes and miscellaneous acts of supernatural "
            "beings, they can survive in Waterdeep!\n" )
            ob->load_chat( 5, ({
            10, ":scuttles around a bit.",
            10, ":cleans its feelers.",
            10, ":rushes around in circles.",
            1,  ":jerks off in a strange direction.",
            }) )
            ob.set_wimpy( 30 )
            ob->load_a_chat( 50, ({
            1, ":oozes horrible white stuff.",
            1, ":makes a sort of scraping noise."
            }) )
            ob->add_effect("/std/effects/npc/i_died",
            [HOSPITAL, "regen_after_death"])
            ob.add_property("monster type", type)
            ob.add_property("animal type", type)
            return ob
            default:
            ob = clone_object(MONSTER)
            ob.set_name("failure")
            ob.set_short("failure")
            ob->set_long( "Please inform a creator about this object.\n"+
            "Type is "+ type +" from "+ file_name( previous_object() ) +".\n" )
            ob.add_property( "monster type", "failure:"+ type )
            return ob


    def get_armour(self, ob: MudObject, items: str) -> None:
            ARMOURY.request_armour(items[random(sizeof(items))], 50+random(50))->
            move(ob)


    def get_jewellery(self, ob: MudObject, items: str) -> None:
            ARMOURY.request_armour(items[random(sizeof(items))], 20+random(80))->
            move(ob)


    def get_weapon(self, ob: MudObject, items: str) -> None:
            ARMOURY.request_weapon(items[random(sizeof(items))], 50+random(50))->
            move(ob)


    def regen_after_death(self, player: MudObject) -> None:
            object ob, dest
            string nam
            if (!player)
            return
            nam = (string)player.query_property("monster type")
            dest = (object)player.query_property("start location")
            if ( !nam )
            return
            if ( !dest )
            return
            if(!ok_to_clone())
            return
            ob = get_monster( explode( nam, ":" )[ 0 ] )
            dest.add_monster(player, ob)
            asyncio.create_task(self."do_move", 10, [ob, dest] )


    def do_move(self, junk: Any) -> None:
            junk[0]->move(junk[1])


    def change_to_name(self, ob: MudObject) -> str:
            return implode((string *)ob.query_adjectives(), " ")+
            (string)ob.query_name()


    def do_run(self, ob: MudObject) -> None:
            if (ob)
            ob -> run_away()


    def fight_check(self, ob: MudObject, ob1: MudObject) -> None:
            if (ob.query_property(previous_object()->query_name()))
            previous_object()->attack_ob(ob1)


    def do_grin_laugh(self, ob: MudObject) -> None:
            ob.add_respond_to_with(["@grin", ob->query_name()],
            "laugh man at $hname$")


    def add_empty(self, thing: MudObject) -> None:
            empties -= [0]
            empties += [thing]
            if ( sizeof( empties ) > MAX_EMPTIES )
            empties = shuffle( empties )[ 0 .. MAX_EMPTIES - 1 ]


    def move_monster(self, thing: MudObject) -> None:
            int i
            string dest, direc, zone, *movez, *roomz
            object place
            if ( !thing )
            return
            if ( (int)thing.query_hp() < 0 )
            return
            if ( thing.query_property( PASSED_OUT ) || thing.query_fighting() ) {
            add_mover( thing )
            return


    def check_movers(self, ) -> None:
            int when
            object thing, *things
            things = movers[ 0 ]
            movers[ 0 .. MAX_MOVERS - 2 ] = movers[ 1 .. ]
            movers[ MAX_MOVERS - 1 ] = 0
            asyncio.create_task(self. "check_movers", 10 )
            if ( !pointerp( things ) )
            return
            foreach ( thing in things ) {
            if ( objectp( thing ) ) {
            when += 2
            asyncio.create_task(self. "move_monster", when, thing )


    def ok_to_clone(self, ) -> int:
            if(time() > last_check + 300) {
            last_check = time()
            am_npcs = sizeof( filter( named_livings(),
            (: environment( $1 ) && base_name( environment( $1
            ) )[0..4] == "/d/am" :) ) )



class Hospital(MudObject):
