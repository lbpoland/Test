# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/monster/commercial.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("spulluf")
            set_gender(1 + random(2) )
            set_long("A nice happy person with a nice smile.\n")
            add_property("demon", 1)
            set_race( "human" )
            set_level( 1 )
            add_help_file("spulluf")
            add_respond_to_with(["@say", "browse"], "#do_browse")
            add_respond_to_with(["@say", "buy"], "#do_buy")
            _furniture = ({
            "/obj/furnitures/commercial/smithy",
            "/obj/furnitures/commercial/money_changer",
            "/obj/furnitures/commercial/blackjack",
            "/obj/furnitures/commercial/small_shop",
            "/obj/furnitures/commercial/pickler",
            "/obj/furnitures/commercial/blackboard",
            "/obj/furnitures/commercial/newspaper_box",
            "/obj/furnitures/commercial/newspaper_archive_box",
            "/obj/furnitures/commercial/bank_master",
            "/obj/furnitures/commercial/bank_franchise_small",
            "/obj/furnitures/commercial/postal",
            "/obj/furnitures/commercial/poll_data",
            })


    def query_money_place(self, ) -> str:
            return environment()->query_property("place")


    def set_commercial_type(self, commercial_type: str) -> None:
            _commercial_type = commercial_type


    def do_start_speil(self, sellto: MudObject) -> None:
            setup_nationality(sellto.query_nationality(), sellto.query_nationality_region())
            _sell_to = sellto
            queue_command("sayto " + file_name(_sell_to) +
            " Hello!  So you are looking at some commercial "
            "furniture?")


    def do_list(self, force: int) -> int:
            string furn
            string place
            int num
            int size
            object ob
            if (!_sell_to) {
            asyncio.create_task(self."leave_room", 5)
            return 0


    def strip_spaces(self, str: str) -> str:
            while (strlen(str) && str[0] == ' ') {
            str = str[1..]


    def leave_room(self, ) -> None:
            move("/room/rubbish", "$N shuffles away.")


    def do_browse(self, str: str) -> int:
            mapping options
            mapping values
            string option_name
            string thing
            string* bits
            string place
            int cost
            int pos
            string* furns
            if (!_sell_to) {
            asyncio.create_task(self."leave_room", 5)
            return 0


    def do_buy(self, str: str, options: str) -> int:
            string place
            string* bits
            string name
            string value
            string thing
            string option_name
            string my_option
            int pos
            int size
            int cost
            int total_cost
            int bad_option
            int found
            mapping option_types
            object ob
            string* furns
            mapping values
            mapping option_values
            if (!_sell_to) {
            asyncio.create_task(self."leave_room", 5)
            return 0


    def do_dismiss(self, ) -> int:
            if (_sell_to && this_player() != _sell_to) {
            queue_command("sayto " + file_name(this_player()) +
            " I am dealing with " + _sell_to.the_short() +
            " right now.")
            return 1


    def do_trash(self, obs: Any) -> int:
            object* ok
            object* bad
            ok = filter(obs, (: $1.query_commercial_furniture() :))
            if (!sizeof(ok)) {
            queue_command("sayto " + file_name(_sell_to) +
            " None of " + query_multiple_short(obs) + " are "
            "commercial items, so I cannot remove them.")
            return 0


    def complete_trash(self, str: str, obs: Any) -> None:
            str = lower_case(str)
            if (!strlen(str) || str[0] != 'y') {
            write("Aborting trash.\n")


    def init(self, ) -> None:
            ::init()
            this_player()->add_command("trash", self,
            "<indirect:object> with <direct:object>",
            (: do_trash :))
            this_player()->add_command("dismiss", self,
            "<direct:object>",
            (: do_dismiss() :))
            this_player()->add_command("list", self,
            "<direct:object>",
            (: do_list(0) :))
            this_player()->add_command("list", self,
            "{on|from} <direct:object>",
            (: do_list(0) :))
            this_player()->add_command("browse", self,
            "<string'name'> on <direct:object>",
            (: do_browse($4[0]) :))
            this_player()->add_command("buy", self,
            "<string'name'> {on|from} <direct:object>",
            (: do_buy($4[0], "") :))
            this_player()->add_command("buy", self,
            "<string'name'> with <string'options'> {on|from} <direct:object>",
            (: do_buy($4[0], $4[1]) :))



class Commercial(MudObject):
