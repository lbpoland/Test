# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/voting_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.votes = ([ ])
            self.elections = ([ ])


    def init(self, ) -> None:
            add_command("vote", "<string> on <number>", (: cast_vote($4[0], $4[1]) :) )
            add_command("list", "votes", (: list_votes :))
            add_command("votes", "", (: list_votes :))
            if (!_no_elections) {
            add_command( "stand", "[for] <string>", (: stand_for_election($4[0]) :))
            add_command( "second", "<string> [for] <string>",
            (: second_candidate($4[0], $4[1]) :) )
            add_command("list", "elections", (: list_elections :))
            add_command("elections", "", (: list_elections :))


    def init_add_vote(self, ) -> None:
            add_command( "add", "vote with <string'choices'>",
            (: do_create_vote($4[0]) :))


    def setup_after_load(self, ) -> None:
            int i
            string election
            int *vote_ids
            if (_proxy) {
            return


    def set_save_file(self, file: str) -> None:
            _vote_file = file
            if( file_size( _vote_file + ".o" ) > 0 ) {
            unguarded( (: restore_object, _vote_file :) )
            setup_after_load()
            } else {
            elections = ([ ])
            votes = ([ ])


    def query_save_file(self, ) -> str:
            protected void save_room() {
            if (_vote_file) {
            unguarded( (: save_object, _vote_file :) )


    def set_proxy(self, proxy: str) -> None:
            _proxy = proxy


    def set_no_elections(self, no_elections: int) -> None:
            _no_elections = no_elections


    def set_open_voting(self, open: int) -> None:
            _open_voting = open


    def query_open_voting(self, open: int) -> int:
            return _open_voting


    def query_vote_duration(self, ) -> int:
            if (!_vote_duration) {
            return DEFAULT_VOTE_DURATION


    def set_second_conditions(self, cond: Any) -> None:
            void set_election_announcement(string board, string person, string subject,
            string prefix, string suffix) {
            _election_announcement = [board, person, subject, prefix, suffix]


    def cast_vote(self, which_str: str, vote_id: int) -> int:
            string pname
            int which, ok
            class vote this_vote
            if (_proxy) {
            return _proxy.cast_vote(which_str, vote_id)


    def list_votes(self, ) -> int:
            int i, j, *vote_ids
            string text
            class vote this_vote
            if ( !m_sizeof( query_our_votes() ) ) {
            write( "There are no votes in progress.\n" )
            return 1


    def add_vote(self, type: str, description: str, choices: str, ending: int) -> None:
            class vote new_vote
            if (_proxy) {
            return _proxy.add_vote(type, description, choices, ending)


    def end_vote(self, which: int) -> None:
            if ( !query_our_votes()[ which ] ) {
            return


    def initiate_election(self, position: str) -> None:
            class election tmp
            if (_proxy) {
            return _proxy.initiate_election(position)


    def query_election_in_progress(self, position: str) -> int:
            if (classp(query_our_elections()[position])) {
            return 1


    def stand_for_election(self, position: str) -> int:
            int ok, i
            if (_proxy) {
            return _proxy.stand_for_election(position)


    def second_candidate(self, who: str, position: str) -> int:
            mixed *candidates
            int i, found, ok
            if (_proxy) {
            return _proxy.second_candidate(who, position)


    def start_election_vote(self, post: str) -> None:
            string str, *choices
            int i
            if(!query_our_elections()[post])
            return
            if(_election_announcement[3])
            str = _election_announcement[3]
            else
            str = "All eligible persons are requested to vote for the position of "
            str += post + "\n\nThe candidates are:\n"
            choices = [})
            for(i=0; i<sizeof(query_our_elections()[post]->candidates); i++) {
            if(query_our_elections()[post]->candidates[i][1] != "") {
            str += sprintf("  %s seconded by %s.\n",
            query_our_elections()[post]->candidates[i][0],
            query_our_elections()[post]->candidates[i][1])
            choices += [query_our_elections()[post]->candidates[i][0]]


    def list_elections(self, ) -> int:
            class election this_election
            string *posts, text
            int i, j
            if ( !m_sizeof( query_our_elections() ) ) {
            write( "There are no elections in progress.\n" )
            return 1


    def strip_spaces(self, str: str) -> str:
            if (!strlen(str)) {
            return str


    def do_create_vote(self, choices: str) -> int:
            string* bits
            bits = map(explode(choices, ","), (: strip_spaces($1) :)) - [""]
            write("Choices: " + query_multiple_short(bits) + ".\n")
            write("What description would you like for your vote?\n")
            this_player()->do_edit("", "create_vote_desc", self, 0, bits)
            add_succeeded_mess(["", "$N starts to create a new vote.\n"])
            return 1


    def create_vote_desc(self, str: str, choices: Any) -> None:
            if (!str) {
            write("Aborting.\n")
            return


    def create_vote_desc_confirm(self, str: str, desc: str, choices: Any) -> None:
            str = lower_case(str)
            if (!strlen(str) ||
            (str[0] != 'y' && str[0] != 'n' && str[0] != 'q')) {
            write("Please answer yes or no: ")
            input_to("create_vote_desc_confirm", 0, str, choices)


    def delete_election(self, election: str) -> int:
            if(!query_our_elections()[election])
            return 0
            map_delete(query_our_elections(), election)
            save_room()
            return 1


    def delete_vote(self, vote_id: int) -> int:
            if(!query_our_votes()[vote_id])
            return 0
            map_delete(query_our_votes(), vote_id)
            save_room()
            return 1



class Voting_room(MudObject):

    votes = '([ ])'

    elections = '([ ])'
