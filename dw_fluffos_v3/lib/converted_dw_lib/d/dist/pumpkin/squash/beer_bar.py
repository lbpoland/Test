# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/squash/beer_bar.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("beer room")
            set_room_size(5)
            add_property( "place", "Pumpkin")
            set_light(60)
            set_theft_handler( HOSPITAL )
            set_zone("Flaming Cabbage")
            set_open_function( (: ref_to_serve :) )
            set_long("This is a beer bar.  Hence, all the bottles, signs and glasses "
            "are related to beer.  Maybe it could be possible to get something "
            "else, but most likely, beer (and of course the sort of healthy, "
            "nutritious food that goes along with beer) is all they sell here.  "
            "The customers, sitting on chairs around the tables, are all drinking "
            "beer and chatting merrily.  At one of the more secluded tables, "
            "some seedy-looking characters are whispering less merrily.  Of course, "
            "they too are enjoying a tasty beer.  A menu is tacked to the "
            "wall behind the counter.\n")
            add_item("floor", "The floor is sticky, and it seems like it'd be hard "
            "to walk out of here.  That could explain why some of the clientele "
            "here seem to have been drinking for days.")
            add_item("sign","There are a number of signs in this bar.  Most of "
            "them are tacky, sticky old cardboard signs pointing out the "
            "special benefits of drinking beer X or ale Y.")
            add_item("bottle","There are a vast amount of bottles on the wall "
            "behind the counter.  They all seem to be the same sort, and quite "
            "a few of them seem to be empty.  At least they catch the seedy "
            "light in a very pretty way.")
            add_item("glass","Beer glasses (the empty kind which are not overly dirty "
            "on the inside) are flooding the bar behind the counter.  Considering "
            "how empty, used glasses seem to disappear altogether, it is probably "
            "necessary to have quite a few glasses around.")
            add_item(({"customer","clientele"}), "The people in here seem to be "
            "mainly concerned with the intake of beer.  They all look rather red "
            "around their noses and, for some reason, they all look rather "
            "happy.  All except those who wouldn't be caught dead doing something "
            "as silly as looking happy, of course.")
            add_item(({"seedy-looking character","character","corner"}), "In a "
            "corner of the bar, some people (who seem to melt in extraordinarily "
            "well into the dark shadows) are quietly drinking some beer, keeping "
            "a watchful eye on everything that happens")
            add_item(({"bar","counter"}), "The counter runs along one wall of the "
            "room.  All empty glasses put on it seem to disappear to some other "
            "dimension.  Only Dogbolter, the God of Empty Beer Pints, knows "
            "where that is.")
            add_item("wall", "The walls are sticky with dried in beer.  Somehow it "
            "has ended up on the walls, but there is nothing here to explain how.  "
            "On one of the walls there's a sign - it appears to be stuck there "
            "without the aid of a pin or anything...")
            add_item("ceiling", "The ceiling is sticky.  They must have had quite a "
            "party here recently.  Or maybe they had a party a long time ago and "
            "just haven't washed the ceiling since?")
            add_item( "wooden table", ({"long", "This is a rather nice wooden "
            "table.  At least it could be, somewhere underneath all that "
            "sticky beer.",
            "position","the wooden table"}))
            add_item( "small table", ({"long", "This table is made of wood, but a "
            "lot smaller than the other tables here.",
            "position","the small table"}))
            add_item( "sticky table", ({"long", "This large table is a lot stickier "
            "than anything else in here, and that means it's pretty darn sticky!",
            "position","the sticky table"}))
            add_item( "old chair",
            ["long", "The chairs around the wooden table are old and donned in Faerûn.",
            "position","the wooden table"
            }) )
            add_item( "small chair",
            ["long", "The chairs around the wooden table are old and donned in Faerûn.",
            "position","a chair at the wooden table"
            }) )
            add_item("sticky beer", "It's just about everywhere.")
            add_menu_item("Spicy sausage", PUB_APPETISER, 396, "spicy sausage")
            add_menu_alias("sausage", "Spicy sausage")
            add_menu_item("Salad", PUB_MAINCOURSE, 796, "salad",
            PUB_STD_SIDEPLATE)
            add_menu_item("Fish'n'chips", PUB_MAINCOURSE, 1196, "fish'n'chips",
            PUB_STD_DINNERPLATE)
            add_menu_item("Ribs", PUB_MAINCOURSE, 1304, "ribs",
            PUB_STD_DINNERPLATE)
            add_menu_item("Hot chicken sandwich", PUB_MAINCOURSE, 796,
            "chicken sandwich")
            add_menu_alias("chicken sandwich", "Hot chicken sandwich")
            add_menu_item("Ham'n'cheese sandwich", PUB_MAINCOURSE, 796, "ham sandwich")
            add_menu_alias("ham sandwich", "Ham'n'cheese sandwich")
            add_menu_item("Unnameable liquid", PUB_ALCOHOL, 1704, "unnameable",
            PUB_STD_PINT, 0, 1)
            add_menu_alias("unnameable", "Unnameable liquid")
            add_menu_item("CMOTD's Finest Brew", PUB_ALCOHOL, 1704, "finest brew",
            PUB_STD_PINT, 0, 1)
            add_menu_alias("brew", "CMOTD's Finest Brew")
            add_menu_alias("cmotd", "CMOTD's Finest Brew")
            add_menu_item("Pumpkine Ale", PUB_ALCOHOL, 1838, "/obj/food/ale.food",
            PUB_STD_PINT, 0, 1)
            add_menu_alias("ale", "Pumpkine Ale")
            add_menu_item("Troll Beer", PUB_ALCOHOL, 1838, "troll beer",
            PUB_STD_PINT, 0, 3)
            add_menu_alias("beer", "Troll Beer")
            add_menu_item("Schlorg Beer", PUB_ALCOHOL, 1838, "schlorg beer",
            "schlorg bottle", 0, 2)
            add_menu_alias("schlorg", "Schlorg Beer")
            add_exit("west", PATH + "squash9", "corridor")


    def create_item(self, word: str) -> MudObject:
            object thing, thang
            switch ( word ) {
            case "spicy sausage" :
            thing = clone_object( "/obj/food" )
            thing.set_weight_per_bite(1)
            thing.set_name("sausage")
            thing.set_short("spicy sausage")
            thing->set_long( "The sausage, of a very questionable origin, seems "
            "to be designed to increase the thirst of whomever eats it.\n" )
            thing.set_value( 396 )
            thing.set_weight(5)
            return thing
            case "unnameable liquid" :
            thang = clone_object( "/obj/reagents/generic_liquid.ob" )
            thang.set_medium_alias("beer")
            thang.set_name("unnameable")
            thang.set_short( "unnameable liquid" )
            thang->set_long( "This sludge is definitely better off without a "
            "name.  If someone was to try to give it a name, it'd have to be "
            "something along the lines of \"Stinking Mud\", \"Utterly "
            "Disgusting and Undrinkable Slush\" or maybe just \"Yuck!\".\n" )
            thang.add_eat_effect( "/std/effects/ingested/drunk", 40 )
            thang.add_eat_effect("/std/effects/ingested/nausea", 100)
            thang.set_amount( 2000 )
            return thang
            case "finest brew" :
            thang = clone_object( "/obj/reagents/generic_liquid.ob" )
            thang.set_name("brew")
            thang.set_medium_alias("beer")
            thang.set_short( "CMOTD's Finest Brew" )
            thang.add_alias(({"finest brew","CMOTD's finest","CMOTD's brew"}))
            thang->set_long( "CMOT Dibbler has produced an amazing beer from "
            "Pumpkin, weird spices and possibly some more things.  Being "
            "Dibbler, he has of course made sure that the pint is rather "
            "a small one.\n" )
            thang.add_eat_effect( "/std/effects/ingested/drunk", 50 )
            thang.set_amount( 980 )
            return thang
            case "troll beer" :
            thang = clone_object( "/obj/reagents/generic_liquid.ob" )
            thang.add_alias("beer")
            thang.set_name("beer")
            thang.set_short("troll beer")
            thang.add_adjective("pint")
            thang->set_long("This is trollish beer.  You suspect a human "
            "shouldn't really be drinking this stuff.\n" )
            thang.add_alias( "trollbeer" )
            thang.add_adjective("troll")
            thang.add_eat_effect("/std/effects/ingested/drunk", 70)
            thang.set_amount( 2000 )
            return thang
            case "schlorg" :
            thang = clone_object( "/obj/reagents/generic_liquid.ob" )
            thang.set_name("schlorg")
            thang.set_short("Schlorg")
            thang.set_medium_alias("beer")
            thang->set_long("This beer must be \"forn\".  It has none of the "
            "characteristic muddiness that all beer brewed from Pumpkin water "
            "possesses.\n" )
            thang.add_eat_effect("/std/effects/ingested/drunk", 180)
            thang.set_amount(3900)
            thang.move(thing)
            thing.do_close()
            return thing
            break
            case "salad" :
            thing = clone_object( "/obj/food" )
            thing.set_name("salad")
            thing.add_property("food", 1)
            thing.set_short( "green salad" )
            thing->set_long( "This green salad is at least partially green, "
            "with interesting bits and thingies in it.\n" )
            thing.add_eat_effect("/std/effects/ingested/nausea", 10)
            thing.set_value( 796 )
            thing.set_amount( 2000 )
            return thing
            case "fish'n'chips" :
            thing = clone_object( "/obj/food" )
            thing.add_alias(({"fish","chips"}))
            thing.add_property("food", 1)
            thing.set_name("cod")
            thing.set_short( "fish'n'chips" )
            thing->set_long( "It's hard to tell what is the fish and which of "
            "the small, sloppy pieces that are supposed to be the chips.  "
            "They all taste the same anyway.\n" )
            thing.add_eat_effect("/std/effects/ingested/nausea", 10)
            thing.set_value( 1196 )
            thing.set_amount( 2000 )
            return thing
            case "ribs" :
            thing = clone_object( "/obj/food" )
            thing.set_name("ribs")
            thing.add_property("food", 1)
            thing.set_short( "ribs" )
            thing.set_main_plural("ribs")
            thing.set_long( "These are ribs.  What animal(s) they come from is "
            "not of any interest, rest assured...  They are quite a lot smaller "
            "than the Real Pork Ribs that you can get in the posh restaurants "
            "in any case.\n" )
            thing.set_value( 1304 )
            thing.set_amount( 2000 )
            return thing
            case "chicken sandwich" :
            thing = clone_object( "/obj/food" )
            thing.add_alias("sandwich")
            thing.add_property("food", 1)
            thing.set_name("chicken")
            thing.set_short( "hot chicken sandwich" )
            thing->set_long( "The chicken on this sandwich is of the green sort.  "
            "It smells funny, moves funny and even sounds a bit funny.  The "
            "only nice thing to say about this sandwich is that it is indeed "
            "hot.  It should probably be eaten with caution, though.\n" )
            thing.add_eat_effect("/std/effects/ingested/nausea", 40)
            thing.set_value( 796 )
            thing.set_amount( 2000 )
            return thing
            case "ham sandwich" :
            thing = clone_object( "/obj/food" )
            thing.add_alias("sandwich")
            thing.add_property("food", 1)
            thing.set_name("ham")
            thing.set_short( "ham'n'cheese sandwich" )
            thing->set_long( "This sandwich has some ham and some cheese on it, "
            "which is why it is called a ham and cheese sandwich.  It has been "
            "baked in an oven.  A long time ago.  It is rather cold an clammy "
            "now.\n" )
            thing.set_value( 796 )
            thing.set_amount( 2000 )
            return thing


    def create_container(self, name: str) -> MudObject:
            object thing
            switch (name) {
            case "schlorg" :
            thing = clone_object( "/obj/bottle" )
            thing.make_bottle("green", 1000)
            thing.set_value(1596)
            thing.set_long( (string)thing.query_long() + "This bottle has a "
            "slightly odd-looking porcelain cap, and no label at all, "
            "in the ordinary fashion of Schlorg-bottles discwide.\n")
            return thing


    def reset(self, ) -> None:
            int i, j, x, y, z
            string *kinds = ({"jolly","burly","fat","happy","drunk","very drunk",
            "silly"})
            j = 5 + random(2)
            if (sizeof(drunkards) < 3) {
            drunkards = allocate(j)


    def make_drunk(self, ob: MudObject, y: int, str: str) -> None:
            int a = random(2)
            string adj, adv
            adv = ["not at all", "very", "quite", "extremely", "rather"]
            [ random(5) ]
            ob->move(self, "A "+  str + " drunkard comes in, looking " + adv +
            " thirsty.")
            switch (y) {
            case 0:
            adj = "small"
            break
            case 1:
            case 2:
            adj = "wooden"
            break
            case 3:
            adj = "sticky"
            break


    def make_bart(self, ob: MudObject, obette: MudObject) -> None:
            ob->move(self, "The bartender pops up from behind the counter "
            "with a wide grin on his face.")
            asyncio.create_task(self."make_barm", 5, obette)


    def make_barm(self, ob: MudObject) -> None:
            ob->move(self, "The barmaid appears from behind the counter and "
            "tries to look innocent.  She desperately tries to sort out her "
            "hair which is a bit unordered.")


    def buy_new(self, ob: MudObject) -> None:
            int tim
            if (!undefinedp(ob)) {
            if (environment(ob) == self) {
            int z
            string beer
            beer = ["troll beer", "brew", "brew",
            "unnameable liquid"][ random(4) ]
            ob.adjust_money(5, "Pumpkin dollar")
            ob.do_command("buy " + beer )
            ob.do_command("hold glass in left hand")
            z = 120 + random(120)
            tim = 20 + random(20)
            while (tim < z) {
            asyncio.create_task(self."sip_beer", tim, ob)
            tim += 30 + random(20)


    def sip_beer(self, ob: MudObject) -> None:
            if (ob &&
            environment(ob) == self) {
            ob.do_command("drink 1/3rd of glass")


    def drink_beer(self, ob: MudObject) -> None:
            if (!undefinedp(ob)) {
            ob.do_command("drink glass")
            ob.do_command("'Ha!  Nice beer, this.")
            asyncio.create_task(self."no_litter",3,ob)


    def no_litter(self, ob: MudObject) -> None:
            object pint, *obinv
            int z
            int a = random(2)
            if (!ob) {
            return


    def ref_to_serve(self, player: MudObject, type: int) -> int:
            int clock, servtime
            clock = (time()%(3600*24))
            servtime = ((clock > 35000) && (clock < 60000))
            if((!servtime) && (type == PUB_MAINCOURSE)) {
            add_failed_mess("Unfortunately, this pub doesn't serve food at the "
            "moment.  Try to change your order, please.\n")
            return 2


    def event_enter(self, ob: MudObject, str: str, from: MudObject) -> None:
            if (ob.query_name() == "drunkard") {
            if( sizeof( match_objects_for_existence( "pint", ob ))) {
            ob.do_command("'Time for another beer for me.")
            asyncio.create_task(self."buy_new",5 + random(50),ob)



class Beer_bar(MudObject):
