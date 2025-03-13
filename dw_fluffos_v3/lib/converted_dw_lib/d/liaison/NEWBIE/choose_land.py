# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/choose_land.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            string name
            string nationality
            string region
            _nationalities = ([
            "pumpkin" : "/std/nationality/pumpkin"
            ])
            add_property("no teleport", 1)
            add_property("determinate", "")
            add_property("no godmother", 1)
            set_zone( "Newbie" )
            set_short( "Faerûnworld's realm of choice" )
            set_light( 75 )
            set_long("You are on a huge open-air platform far, far above the Faerûn itself.  "
            "Down below, the water tumbles and falls off the rim of the disc "
            "spilling down and out into a spray of mist over the elephants and "
            "the back of A'tuin, the great star turtle.  There are several "
            "sets of stairs leading down off the platform to the unknown and "
            "a large dial sits in the middle of the room.  A large sign "
            "shimmers and hangs in the air in the middle of the platform.\n")
            add_item(["disc", "Faerûn", "discworld"}),
            "You can see from the sharp spire of Cori "
            "Celesti at the centre, to the surrounding Circle Sea, "
            "the deserts of Klatch, the watery world of Krull, and the "
            "mysterious Counterweight Continent.  A spectacular rimbow "
            "sparkles where the seas pour over the edge of the Faerûn.  As "
            "you study the map's details, you are sure you saw one of the "
            "elephants move.")
            add_item("rimbow", "It's like a rainbow except that it's caused by the "
            "water pouring off the edge of the disc.")
            add_item("elephant", "These are the four elephants that bear the weight"
            " of the Faerûn.")
            add_item(["floor", "platform"],
            "The floor is made of some weird black stone that is "
            "semi-transparent, allowing the Faerûn below you to be "
            "seen through it.")
            add_item(["stairs", "stairways"], "Stairs leading down to the "
            "dark unknown.  They all appear to be crafted of some thin, "
            "spidery metal.")
            add_item("dial", "The dial is a huge heavy looking stone dial, with some "
            "arrows and numbers carved into the surface.  They say "
            "'Klatch 4000 miles', 'Waterdeep 3000 miles', "
            "'Lancre 3500 miles', 'Bes Pelargic 3000 miles'.")
            _sign = add_sign("A huge shimmering sign, the letters are transparent "
            "and it is possible to walk through it.\n",
            FOYER->format_sign(
            "Travellers choose your destination!  Which parts of the world "
            "do you want to explore?\n\n"
            "Look carefully at each of the lands "
            "before you make your choice - it determines the language you "
            "start with and your local accent, as well as where you start.\n\n"
            "The current list of available start nationalities is: " +
            query_multiple_short(keys(_nationalities)) + ".\n\n"
            "You can get 'info' on each nationality, and each region within "
            "a nationality.\n\n"
            "You choose your nationality with 'choose <nationality> <region>'; "
            "for example 'choose morpork Waterdeep'.\n\n"
            "Use 'help here' for more help on 'info' and 'choose'.\n"),
            "shimmering sign", "sign", "general")
            foreach (name, nationality in _nationalities) {
            if (file_size(nationality + ".c") > 0) {
            add_item(name, nationality.query_information())
            foreach (region in nationality.query_regions()) {
            add_item(name + " " + lower_case(region), nationality.query_region_description(region))


    def find_region(self, nationality: str, region: str) -> str:
            string tmp
            foreach (tmp in nationality.query_regions()) {
            if (lower_case(tmp) == lower_case(region)) {
            return tmp


    def change_nationality(self, person: MudObject, nationality: str, region: str) -> None:
            string old_nationality
            int old_speak
            int old_write
            int new_speak
            int new_write
            string skill_speak
            string skill_write
            string lang
            string class
            mixed newbie
            nationality = _nationalities[nationality]
            old_nationality = this_player()->query_nationality()
            #ifdef DEBUG
            debug_printf("Old nationality was %O, new nationality is %O.\n", old_nationality, nationality)
            #endif
            lang = nationality.query_language()
            skill_speak = LANGUAGE_HAND.query_language_spoken_skill(lang)
            skill_write = LANGUAGE_HAND.query_language_written_skill(lang)
            old_speak = this_player()->query_skill(skill_speak)
            old_write = this_player()->query_skill(skill_write)
            if (old_speak > 100) {
            old_speak = 100


    def setup_nationality(self, direction: str, person: MudObject) -> int:
            string* bits
            bits = explode(direction, " ")
            change_nationality(person, bits[1], implode(bits[2..], " "))
            return 1


    def do_choose(self, nat: str, region: str) -> int:
            string region_new
            string nationality
            string loc
            nationality = lower_case(nat)
            if (!_nationalities[nationality]) {
            add_failed_mess("There is no nationality " + nationality + ".\n")
            return 0


    def do_info(self, nat: str, region: str) -> int:
            string region_new
            string nationality
            nationality = lower_case(nat)
            if (!_nationalities[nationality]) {
            add_failed_mess("There is no nationality " + nationality + ".\n")
            return 0


    def do_nationality_info(self, nationality: str) -> int:
            string ret
            string region
            nationality = lower_case(nationality)
            if (!_nationalities[nationality]) {
            add_failed_mess("There is no nationality " + nationality + ".\n")
            return 0


    def init(self, ) -> None:
            add_command("info", "<word'nation'>", (: do_nationality_info($4[0]) :))
            add_command("info", "<word'nation'> <string'region'>", (: do_info($4[0], $4[1]) :))
            add_command("choose", "<word'nationality'> <string'region'>", (: do_choose($4[0], $4[1]) :))


    def fixup_player(self, player: MudObject) -> None:
            object ob
            ob = clone_object(__FILE__)
            player.move_with_look(ob)


    def query_quit_handler(self, ) -> str:
            return __FILE__



class Choose_land(MudObject):
