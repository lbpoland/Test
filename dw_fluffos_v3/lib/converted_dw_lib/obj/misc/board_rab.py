# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/board_rab.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            ::setup()
            add_alias("board master")
            action_pri = 3
            reset_drop()
            set_get()


    def long(self, str: str, dark: int) -> str:
            int i, irp
            mixed *stuff
            string ret
            mapping news_rc
            stuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            ret = "A bulletin board ("+board_name+").\n"
            irp = (int)BOARD_HAND.query_minimum(board_name)
            if (irp)
            ret += "Minimum number of messages left by automagic deletion is "+ irp +
            ".\n"
            irp = (int)BOARD_HAND.query_maximum(board_name)
            if (irp)
            ret += "Maximum number of messages on this board is "+irp+".\n"
            irp = (int)BOARD_HAND.query_timeout(board_name)
            if (irp)
            ret += "Messages will automagically time out in "+ irp +" days.\n"
            irp = (int)BOARD_HAND.query_archive(board_name)
            if (irp)
            ret += "Deleted messages are archived in "+irp+".\n"
            ret += sprintf("%#-*s\n\n", this_player()->query_cols(),
            "read <note number>\npost <subject>\n"+
            "boards\n"+
            "store <note number> <file>\n"+
            "storeall <file> (optional)\n"+
            "eat <note number>\n"+
            "reply <note number>\nfollowup <note number>\n"+
            "summary [all]\nnext\nprev\nnew\n"+
            "board <board name>\n"+
            "timeout <time>\nminimum <num>\nmaximum <num>\n"+
            "archive <name|none>\n"+
            "security\nsadd <name>\nsremove <name>\n"+
            "killfile <board name>\nunkillfile <board name>\nlistkillfile\ntransfer <note> <board>")
            if (!sizeof(stuff))
            return ret+"The board is completely empty.\n"
            news_rc = (mapping)this_player()->query_property(NEWS_RC)
            if (!news_rc)
            news_rc = ([ ])
            for (i=0;i<sizeof(stuff);i++)
            if (news_rc[board_name] < stuff[i][B_TIME])
            ret += sprintf("N %2d: %-=*s\n", i+1, (int)this_player()->query_cols()-6,
            stuff[i][B_SUBJECT]+" ("+
            stuff[i][B_NAME]+" "+the_date(stuff[i][B_TIME])+")")
            else
            ret += sprintf("  %2d: %-=*s\n", i+1, (int)this_player()->query_cols()-6,
            stuff[i][B_SUBJECT]+" ("+
            stuff[i][B_NAME]+" "+the_date(stuff[i][B_TIME])+")")
            return ret


    def init(self, ) -> None:
            if (environment() == this_player() &&
            this_player()->query_creator()) {
            add_commands()
            add_command("store", "<number> <word>", (: do_store($4[0], $4[1]) :))
            add_command("storeall", "<word>", (: do_storeall($4[0]) :))
            add_command("next", "")
            add_command("prev", "")
            add_command("new", "")
            add_command("board", "<string>", (: do_board($4[0]) :))
            add_command("boards", "")
            add_command("killfile", "<string>", (: do_killfile($4[0]) :))
            add_command("unkillfile", "<string>",(: do_unkillfile($4[0]) :))
            add_command("listkillfile", "")
            add_command("security", "")
            add_command("sadd", "<word>", (: do_add($4[0]) :))
            add_command("sremove", "<word>", (: do_remove($4[0]) :))
            add_command("timeout", "<number>", (: do_timeout($4[0]) :))
            add_command("minimum", "<number>", (: do_minimum($4[0]) :))
            add_command("maximum", "<number>", (: do_maximum($4[0]) :))
            add_command("archive", "<word>", (: do_archive($4[0]) :))
            add_command("summary", "")
            add_command("skip", "")
            add_command("arts", "")
            add_command("transfer", "<number> <string>",
            (: do_transfer($4[0], $4[1]) :))


    def do_storeall(self, file: str) -> int:
            int which
            mixed *stuff
            int i, j, no, amt, cnt=0
            string *boards, their_name
            mapping news_rc
            seteuid( geteuid( this_player() ) )
            their_name = this_player()->query_name()
            boards = (string *)BOARD_HAND.list_of_boards()
            news_rc = (mapping)this_player()->query_property(NEWS_RC)
            if (!write_file(file, "File created on "+ctime(time())+
            " - Seattle time\n", 1)) {
            add_failed_mess("Unable to save the file "+file+"\n")
            return 0


    def do_store(self, which: int, file: str) -> int:
            mixed *stuff
            stuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            if (which < 1 || which > sizeof(stuff)) {
            add_failed_mess("Invalid note number.\n")
            return 0


    def do_next(self, ) -> int:
            int i
            string *boards
            boards = (string *)BOARD_HAND.list_of_boards()
            if ((i = boards.index(board_name) if board_name in boards else -1) == -1)
            i = 0
            else
            i = (i+1)%sizeof(boards)
            board_name = boards[i]
            add_succeeded_mess(self, ["Gone to board:"+board_name+".\n",
            "$N turns their board over.\n"], [}) )
            return 1


    def prev(self, ) -> int:
            int i
            string *boards
            boards = (string *)BOARD_HAND.list_of_boards()
            if ((i = boards.index(board_name) if board_name in boards else -1) == -1)
            i = 0
            else
            i = (i-1+sizeof(boards))%sizeof(boards)
            board_name = boards[i]
            add_succeeded_mess(self, ["Gone to board:"+board_name+".\n",
            "$N turns their board over.\n"], [}) )
            return 1


    def do_killfile(self, arg: str) -> int:
            this_player()->add_property( "news_kill_" +lower_case( arg ), 1 )
            add_succeeded_mess(self, ["Board "+arg+" killed.\n", ""], ({}))
            return 1


    def do_unkillfile(self, arg: str) -> int:
            if (!this_player()->query_property( "news_kill_" +lower_case( arg ) )) {
            add_failed_mess("Board "+arg+" is not kill file anyway.\n")
            return 0
            } else {
            this_player()->remove_property( "news_kill_" +lower_case( arg ) )
            add_succeeded_mess(self, ["Board "+arg+" unkilled.\n", ""],
            [}))


    def do_listkillfile(self, arg: str) -> int:
            string property, s1, *boards=[})
            mixed value
            foreach ( property, value in this_player()->query_properties() )
            if ( sscanf(property,"news_kill_%s",s1) == 1 &&
            value )
            boards += [s1]
            if ( sizeof( s1 ) )
            tell_object( this_player(), "You have the following boards killfiled: "+
            query_multiple_short( boards ) +".\n" )
            add_succeeded_mess(self, "", [}))
            return 1


    def do_new(self, ) -> int:
            int i, amt
            string *boards, their_name
            mixed *stuff
            mixed otherstuff
            mapping news_rc
            boards = (string *)BOARD_HAND.list_of_boards()
            their_name = this_player()->query_name()
            news_rc = (mapping)this_player()->query_property(NEWS_RC)
            for (i=0;i<sizeof(boards);i++) {
            if (!this_player()->query_property("news_kill_"+lower_case(boards[i]))) {
            stuff = (mixed *)BOARD_HAND.get_subjects(boards[i])
            if (!sizeof(stuff))
            continue
            for (amt=sizeof(stuff)-1;amt >= 0 &&
            (stuff[amt][B_TIME] > news_rc[boards[i]] &&
            lower_case(stuff[amt][B_NAME]) != their_name)
            amt--)
            if (amt != sizeof(stuff)-1) {
            board_name = boards[i]
            add_succeeded_mess(self, ({
            "The "+ boards[ i ] +" board has "+ ( sizeof( stuff ) - amt -
            1 ) +" new message"+ ( ( ( sizeof( stuff ) - amt ) > 2 ) ? "s" : "" )
            +".\n", "$N turns over their board.\n"], [}))
            return 1


    def do_board(self, str: str) -> int:
            int i
            string *boards
            boards = (string *)BOARD_HAND.list_of_boards()
            i = boards.index(str) if str in boards else -1
            if (i == -1) {
            add_failed_mess("The board "+str+" does not exist sorry.\n")
            return 0


    def do_boards(self, ) -> int:
            write( "The current boards are:\n\""+
            implode( (string *)BOARD_HAND.list_of_boards(), "\", \"" ) +
            "\".\n" )
            return 1


    def do_security(self, ) -> int:
            write( "The current people in this boards security array are:\n"+
            implode((string *)BOARD_HAND.query_security(board_name), ", ")+"\n")
            return 1


    def do_add(self, name: str) -> int:
            if (this_player() != this_player(1) ||
            !interactive(previous_object()))
            return 0
            return (int)BOARD_HAND.add_allowed(board_name, name)


    def do_remove(self, name: str) -> int:
            if (this_player() != this_player(1) ||
            !interactive(previous_object()))
            return 0
            return (int)BOARD_HAND.remove_allowed(board_name, name)


    def do_timeout(self, i: int) -> int:
            if (this_player() != this_player(1) ||
            !interactive(previous_object()))
            return 0
            return (int)BOARD_HAND.set_timeout(board_name, i)


    def do_minimum(self, i: str) -> int:
            if (this_player() != this_player(1) ||
            !interactive(previous_object()))
            return 0
            return (int)BOARD_HAND.set_minimum(board_name, i)


    def do_maximum(self, i: int) -> int:
            if (this_player() != this_player(1) ||
            !interactive(previous_object()))
            return 0
            return (int)BOARD_HAND.set_maximum(board_name, i)


    def do_archive(self, name: str) -> int:
            if (!name)
            return 0
            if (name != "none")
            return (int)BOARD_HAND.set_archive(board_name, name)
            return (int)BOARD_HAND.set_archive(board_name)


    def query_static_auto_load(self, ) -> Any:
            return board_name


    def init_static_arg(self, board: Any) -> None:
            if (stringp(board))
            board_name = board


    def do_summary(self, str: str) -> int:
            int i, no, amt
            string *boards, their_name
            mapping news_rc
            mixed *stuff
            boards = (string *)BOARD_HAND.list_of_boards()
            news_rc = (mapping)this_player()->query_property(NEWS_RC)
            their_name = this_player()->query_name()
            for (i=0;i<sizeof(boards);i++) {
            if (!this_player()->query_property("news_kill_"+lower_case(boards[i]))) {
            stuff = (mixed *)BOARD_HAND.get_subjects(boards[i])
            if (!sizeof(stuff))
            continue
            for (amt=sizeof(stuff)-1;amt >= 0 &&
            (stuff[amt][B_TIME] > news_rc[boards[i]] &&
            lower_case(stuff[amt][B_NAME]) != their_name)
            amt--)
            if (amt != sizeof(stuff)-1) {
            printf( "The "+ boards[ i ] +" board has "+ ( sizeof( stuff ) - amt -
            1 ) +" new message"+ ( ( ( sizeof( stuff ) - amt ) > 2 ) ? "s" : "" )
            +".\n" )
            no++
            } else if (str == "all") {
            printf("The "+boards[i]+" board has no new messages.\n")
            no++


    def do_skip(self, ) -> int:
            mapping news_rc
            mixed *otherstuff
            news_rc = (mapping)this_player()->query_property(NEWS_RC)
            otherstuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            if (sizeof(otherstuff)) {
            news_rc[board_name] = otherstuff[sizeof(otherstuff)-1][B_TIME]
            this_player()->add_property(NEWS_RC, news_rc)


    def do_arts(self, ) -> int:
            int i
            mixed *otherstuff
            otherstuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            for (i=0;i<sizeof(otherstuff);i++)
            printf("%2d# %-20s %d\n", i, otherstuff[i][B_NAME], otherstuff[i][B_NUM])
            add_succeeded_mess(self, "", [}))
            return 1


    def do_transfer(self, num: int, str: str) -> int:
            string mess
            string *boards
            mixed *otherstuff
            int i
            boards = (string *)BOARD_HAND.query_boards()
            otherstuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            if (boards.index(str) if str in boards else -1 == -1) {
            add_failed_mess("Cannot find the board '"+str+"'.\n")
            return 0



class Board_rab(MudObject):
