# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/mailer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.no_menu = full_header = 0
            self.last_read = -1
            self.newish = []
            self.folder = []
            self.folder_names = ['inbox']
            self.deleted = []
            self.current = ""
            self.owner = this_player()
            self.aliases = owner->query_aliases()
            self.mailrc = aliases[".mailrc"]


    def __init__(self):
            self.no_menu = full_header = 0
            self.last_read = -1
            self.newish = []
            self.folder = []
            self.folder_names = ['inbox']
            self.deleted = []
            self.current = ""
            self.owner = this_player()
            self.aliases = owner->query_aliases()
            self.mailrc = aliases[".mailrc"]


    def set_do_this_last(self, bing: Any) -> None:
            mixed *query_do_this_last() { return do_this_last; }
            varargs int do_mail_message(string t, string from, string sub, string ccs,
            string body, int, string only_to, int flag) {
            string *cc_e, *goto
            class mail_message msg
            if(file_name(previous_object())[0..12] != "/secure/login" &&
            file_name(previous_object())[0..13] != "/secure/nlogin" &&
            file_name(previous_object())[0..13] != "/obj/handlers/" &&
            file_name(previous_object())[0..4] != "/www/" &&
            file_name(previous_object())[0..11] != "/net/daemon/" &&
            file_name(previous_object())[0..11] != "/global/lord" &&
            file_name(previous_object())[0..14] != "/global/creator" &&
            file_name(previous_object())[0..18] != "/global/auto_mailer" &&
            file_name(previous_object())[0..12] != "/cmds/creator" &&
            file_name(previous_object())[0..9] != "/cmds/lord" &&
            file_name(previous_object()) != "/d/am/buildings/post/parcel" &&
            file_name(previous_object()) != "/d/am/buildings/apex/admin_office" &&
            file_name(previous_object()) != "/d/am/bookkeepers/weichert_office" &&
            file_name(previous_object()) != "/d/ram/ohulan/market/post_office" &&
            file_name(previous_object()) != "/d/ram/interview" &&
            file_name(previous_object()) != "/d/forn/utils/interview" &&
            file_name(previous_object()) != "/d/am/buildings/flintwick/lawyer_office" &&
            file_name(previous_object()) != "/d/am/buildings/council/court" &&
            file_name(previous_object()) != "/d/klatch/djel/city/palace/council_court" &&
            file_name(previous_object()) != "/d/classs/error_tracker" &&
            file_name(previous_object())[0..25] != "/d/ram/ohulan/market/post2") {
            printf("MAILER: illegal access (%O).\n", file_name(previous_object()))
            return 0


    def finger_mail(self, pname: str) -> str:
            return FOLDER_H.finger_mail(lower_case(pname))


    def new_mail(self, pname: str) -> str:
            return FOLDER_H.check_mail(lower_case(pname))


    def read_mail(self, str: str, sub: str) -> None:
            if (this_player()->query_property("guest")) {
            write("Sorry, mailer access is not allowed for guests.\n")
            if (do_this_last && objectp(do_this_last[0])) {
            call_other(do_this_last[0], do_this_last[1], do_this_last[2])
            } else {
            dest_me()


    def finish_write_message(self, input: str) -> None:
            if (!input || input == "") {
            if (no_menu) {
            delete_it("inbox", 1)
            return


    def finish_print(self, ) -> None:
            printf("\n")
            prompt()
            input_to("read_loop")


    def dest_me(self, ) -> None:
            MAIL_TRACK.delete_mailer(self)
            destruct(self)


    def format_date(self, x: int) -> str:
            string str
            string mon
            mixed *tm
            if (x<0 || !intp(x))
            return "Bad time"
            tm = localtime(x)
            str = DAYS[tm[LT_WDAY]]
            mon = MONTHS[tm[LT_MON]]
            str = sprintf("%s, %d %s %d %02d:%02d %s", str, tm[LT_MDAY], mon,
            tm[LT_YEAR], tm[LT_HOUR], tm[LT_MIN], tm[LT_ZONE])
            return str



class Mailer(MudObject):

    no_menu = 'full_header = 0'

    last_read = '-1'

    newish = '[]'

    folder = '[]'

    folder_names = "['inbox']"

    deleted = '[]'

    current = '""'

    owner = 'this_player()'

    aliases = 'owner->query_aliases()'

    mailrc = 'aliases[".mailrc"]'
