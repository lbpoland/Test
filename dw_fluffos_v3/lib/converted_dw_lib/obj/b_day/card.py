# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/b_day/card.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup_card(self, name: str, language: str, status: int) -> None:
            mapping init_query_static_auto_load() {
            return ([ "::" : ::int_query_static_auto_load(),
            "owner_name":owner_name,
            "owner_language":owner_language,
            "is_open":is_open,
            "opened_before":opened_before])


    def init_static_arg(self, map: Any) -> None:
            if ( map[ "::" ] ) {
            ::init_static_arg( map[ "::" ] )


    def set_closed_mesg(self, ) -> None:
            {
            set_long("The closed card has been carefully handmade from pink "
            "cardboard. There is a rather vague illustration of a "
            "non-identifiable piece of flora on the front.\n")


    def set_open_mesg(self, ) -> None:
            {
            set_long("The open card has been carefully handmade from pink "
            "cardboard.\n")


    def setup_card(self, own_name: str, own_language: str, cre_status: int) -> None:
            {
            string *wizards, list
            int i
            owner_name = own_name
            owner_language = own_language
            creator_status = cre_status
            set_short(owner_name + "'s birthday card")
            add_adjective( [owner_name, owner_name + "'s"}) )
            wizards = get_dir("/w/")
            if(creator_status) {
            int start = wizards.index(lower_case(owner_name)) if lower_case(owner_name) in wizards else -1
            wizards = wizards[0..start-1] + wizards[start+1..]
            list =
            "\n    Have a wonderful birthday, " + owner_name + "!!!  \n"
            "    LOVE AND KISSES FROM...                \n\n"
            for(i=0;i<sizeof(wizards);i++) {
            if(PLAYER_HANDLER.test_user(wizards[i])) {
            list += colour_array[random(sizeof(colour_array))] +
            capitalize(wizards[i])
            if(i == sizeof(wizards)-1) list += "%^RESET%^.\n\n"
            else if(i == sizeof(wizards)-2) list += "%^RESET%^ and "
            else list += ",%^RESET%^ "


    def setup(self, ) -> None:
            {
            set_name("card")
            set_short("birthday card")
            add_adjective("birthday")
            set_main_plural("birthday cards")
            add_property("determinate", "")
            add_property("no recycling", 1)
            set_closed_mesg()
            if(owner_name && owner_language) {
            setup_card(owner_name, owner_language, creator_status)


    def init(self, ) -> None:
            {
            this_player()->add_command("open", self)
            this_player()->add_command("close", self)


    def do_open(self, ) -> int:
            {
            object demon
            if(is_open) {
            write("It is already open.\n")
            return 1


    def start_demon(self, thing: MudObject) -> None:
            thing.do_the_act(0)


    def do_close(self, ) -> int:
            {
            if(!is_open) {
            write("It is not open for you to close!\n")
            return 1



class Card(MudObject):
