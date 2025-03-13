# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/board.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("board")
            set_short("bulletin board")
            add_adjective("bulletin")
            set_main_plural("boards")
            reset_get()
            add_property("there", "mounted on one wall")
            add_property("survive fire", 1)
            add_help_file("board")
            board_name = "frog"
            being_written = ([ ])
            action_pri = 0


    def query_plural(self, ) -> str:
            mixed *stuff
            stuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            switch (sizeof(stuff)) {
            case 0:
            return pluralize(::short(0))+" [ Empty ]"
            case 1:
            return pluralize(::short(0))+" [ 1 note ]"


    def short(self, dark: int) -> str:
            mixed *stuff
            stuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            switch (sizeof(stuff)) {
            case 0:
            return ::short(dark)+" [ Empty ]"
            case 1:
            return ::short(dark)+" [ 1 note ]"
            default:
            return ::short(dark)+" [ "+sizeof(stuff)+" notes ]"


    def the_date(self, i: int) -> str:
            return ctime(i)[4..9]


    def do_subjects(self, search: str) -> int:
            int i, size
            mixed *stuff
            string ret
            mapping news_rc
            search = lower_case(search)
            stuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            if (!sizeof(stuff)) {
            add_failed_mess("The board is completely empty.\n")
            return 0


    def long(self, str: str, dark: int) -> str:
            int i,newones, size
            mixed *stuff
            string ret
            mapping news_rc
            stuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            ret = "A bulletin board ("+board_name+").\n"
            if (!sizeof(stuff)) {
            return ret+"The board is completely empty.\n"


    def add_commands(self, ) -> None:
            add_command("read", "[new]", (: do_read_new :))
            add_command("r", "[new]", (: do_read_new :))
            add_command("read", "<number>", (: do_read($4[0]) :))
            add_command("r", "<number>", (: do_read($4[0]) :))
            add_command("read", "next", (: do_read_next :))
            if (!this_player()->query_property("guest")) {
            add_command("post", "<string'subject'>", (: do_post($4[0]) :))
            add_command("note", "<string'subject'>", (: do_post($4[0]) :))
            add_command("eat", "<number'message number'>", (: do_eat($4[0]) :))
            add_command("followup", "<number'message number'>",
            (: do_followup($4[0]) :))
            add_command("reply", "<number'message number'>", (: do_reply($4[0]) :))


    def init(self, ) -> None:
            if (!present("board master", this_player())) {
            add_commands()


    def mark_mine(self, stuff: Any, news_rc: Any) -> None:
            int i
            string their_name
            i = sizeof(stuff)-1
            their_name = this_player()->query_name()
            while (i > 0 && stuff[i][B_TIME] > news_rc[board_name])
            i--
            while ((i+1) < sizeof(stuff) && lower_case(stuff[i+1][B_NAME]) == their_name)
            i++
            if (i >= sizeof(stuff)) {
            news_rc[board_name] = stuff[sizeof(stuff)-1][B_TIME]
            return


    def do_read_next(self, ) -> int:
            mapping  news_rc
            mixed   *stuff
            string   their_name, sub, next_sub
            int      num, last_time
            news_rc = BOARD_HAND.query_newsrc(this_player()->query_name())
            if (undefinedp(news_rc["last board"])  ||
            news_rc["last board"] != board_name)
            {
            add_failed_mess("You have not read a note on this board yet!\n")
            return 0


    def do_read_new(self, ) -> int:
            int num
            string their_name
            mapping news_rc
            mixed *stuff
            news_rc = BOARD_HAND.query_newsrc(this_player()->query_name())
            if (!news_rc) {
            news_rc = ([ ])


    def do_read(self, num: int) -> int:
            mapping news_rc
            mixed *stuff
            news_rc = BOARD_HAND.query_newsrc(this_player()->query_name())
            if (!news_rc) {
            news_rc = ([ ])


    def do_post(self, str: str) -> int:
            class info_written bing
            if (board_name=="announcements" && !this_player()->query_creator()) {
            add_failed_mess("Sorry. You can't post messages here.  "
            "It's for announcements "
            "from the creators only.  If you have a comment or flame, try "
            "the 'flame' board or the 'frog' board.  Bing\n")
            return 0


    def end_of_thing(self, body: str) -> None:
            class info_written bing
            if (body && body != "" &&
            being_written[this_player()->query_name()]) {
            if(board_name != "announcements")
            body = sprintf( "%-=78s", body ) + this_player()->append_signature()
            bing = (class info_written)being_written[ this_player()->query_name() ]
            if ( !BOARD_HAND->add_message( board_name,
            capitalize( (string)this_player()->query_name() ),
            bing->subject,
            body,
            bing->note_num ) ) {
            printf( "Error writing message.\n" )
            } else {
            printf("Message posted.\n")
            this_player()->adjust_sp(-50)


    def do_eat(self, num: int) -> int:
            if (!BOARD_HAND.delete_message(board_name, num-1)) {
            add_failed_mess("Failed to eat note.\n")
            return 0


    def do_followup(self, num: int) -> int:
            int i
            mixed stuff
            string s
            class info_written bing
            stuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            if (num < 0) {
            num = sizeof(stuff) + num + 1


    def include_post(self, str: str, num: int, stuff: Any) -> None:
            if (!str || str == ""  || lower_case(str)[0] != 'y') {
            printf("No.\n")
            this_player()->do_edit(0, "end_of_thing")
            return


    def do_reply(self, num: int) -> int:
            mixed stuff
            stuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            if (num < 1 || num > sizeof(stuff)) {
            add_failed_mess("No note of that number.\n", [}))
            return 0


    def query_new_messages(self, ) -> int:
            mixed *notes
            mapping news_rc
            news_rc = BOARD_HAND.query_newsrc(this_player()->query_name())
            if (!news_rc)
            news_rc = ([ ])
            notes = (mixed *)BOARD_HAND.get_subjects(board_name)
            if (!sizeof(notes))
            return 0
            return (notes[sizeof(notes)-1][B_TIME] > news_rc[board_name])



class Board(MudObject):
