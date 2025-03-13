# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/poll_data.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._finished_votes = []


    def setup(self, ) -> None:
            set_name( "poll" )
            set_short( "opinion poll" )
            add_adjective( ["opinion" } ))
            set_long( "A box with a bunch of pieces paper sitting on it.  It seems "
            "to be keeping a tally of something.\n")
            set_allowed_positions(({"sitting", "lying", "kneeling", "meditating"}))
            set_allowed_room_verbs((["sitting" : "sits" ]))
            set_weight(2000)
            set_value(240000)
            set_commercial_size(2)
            set_commercial_type("misc")
            set_shop_use_types(["poll add", "poll vote"])
            set_completion_action((: finish_vote :))
            set_no_elections(1)
            set_vote_conditions((: is_open_for("poll vote", $1.query_name()) :))
            add_help_file("poll_data")


    def load_me(self, ) -> int:
            if (!query_commercial_id()) {
            setup_new_commercial_id()


    def do_show_results(self, ) -> int:
            string ret
            string result
            ret = ""
            foreach (result in _finished_votes) {
            ret += result + "\n\n"


    def do_create_vote(self, choices: str) -> int:
            if (!is_open_for("poll add", this_player()->query_name())) {
            add_failed_mess("Unable to add a vote.\n")
            return 0


    def do_set_duration(self, hours: int) -> int:
            if (hours <= 0) {
            add_failed_mess("The duration must be positive.\n")
            return 0


    def do_delete_vote(self, id: int) -> int:
            if (!::delete_vote(id)) {
            add_failed_mess("Cannot delete the vote id #" + id + ".\n")
            return 0


    def do_end_vote(self, id: int) -> int:
            if ( !query_our_votes()[ id ] ) {
            add_failed_mess("Cannot end the vote id #" + id + ".\n")
            return 0


    def query_main_status(self, ) -> str:
            string ret
            ret = "Vote duration:    " + (query_vote_duration() / (60 * 60)) +
            " hours\n"
            return ret


    def init(self, ) -> None:
            commercial::init()
            voting_room::init()
            voting_room::init_add_vote()
            add_command("results", "of votes", (: do_show_results() :))
            if (environment()->is_allowed(this_player()->query_name())) {
            add_command("set", "vote duration <number'hours'> on <direct:object>",
            (: do_set_duration($4[0]) :))
            add_command("delete", "vote <number'vote id'>",
            (: do_delete_vote($4[0]) :))
            add_command("finish", "vote <number'vote id'>",
            (: do_end_vote($4[0]) :))



class Poll_data(MudObject):

    _finished_votes = '[]'
