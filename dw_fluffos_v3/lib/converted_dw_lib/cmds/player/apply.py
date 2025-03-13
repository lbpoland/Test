# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/apply.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_creator_apply(self, domain: str, type: str) -> int:
            int temp
            if (!domain) {
            domain = type


    def confirm(self, message: str, applying_player: Any) -> None:
            if (!message || !sizeof (message) || strsrch (message, "no") != -1
            || strsrch (message, "n") != -1) {
            return


    def query_application_info(self, domain: str) -> str:
            string ret
            if( file_size( "/d/" + domain + "/application.txt" ) != -1 ) {
            ret = read_file( "/d/" + domain + "/application.txt" )


    def start_asking(self, message: str, applying_player: Any) -> None:
            object player = tmp->player
            if (!message || sizeof (message) == 0) {
            tell_object (player, "Your application has been aborted.\n")
            return


    def submit_application(self, player: MudObject, applying_player: Any) -> None:
            int i
            string *text = [})
            for (int j = 0; j < sizeof (tmp->questions); j++) {
            text += ["%^CYAN%^" +sprintf( "%2d) %-=*s", ( j + 1), 70,
            tmp->questions[j] ) + "%^RESET%^\n"]
            text += [sprintf( "      %-=*s\n\n", 72, tmp->answers[j] )})


    def do_list_types(self, ) -> int:
            string ret = ""
            string *types
            types = APPLICATIONS_HANDLER.query_types()
            ret += "You can apply for the following positions with this command:\n\n"
            foreach (string t in types) {
            ret += t + "\n"


    def do_list_requirements(self, type: str) -> int:
            string ret = APPLICATIONS_HANDLER->application_requirements (type)
            this_player()->more_string (ret)
            return 1


    def domain_status(self, ) -> int:
            mapping map = APPLICATIONS_HANDLER.query_domain_status()
            string ret = ""
            foreach (string s, int o in map) {
            ret += (o ? "%^BOLD%^%^CYAN%^" : "") + capitalize (s) + " is " +
            (o ? "open" : "closed") + "%^RESET%^ to "
            "applications and is managed by " +
            capitalize (APPLICATIONS_HANDLER->query_responsibility (s)) + ".\n"


    def do_list_questions(self, type: str) -> int:
            string *quest = APPLICATIONS_HANDLER->query_questions (type)
            tell_object (this_player(), "\n\nPlease take time to write your application.  "
            "Preferably, prepare an answer to each of these questions off-line "
            "and copy your response into the editor on the MUD if possible.  "
            "You will be asked these questions one-by-one during the application "
            "process, so you should answer each question thoroughly.  Remember, "
            "this is a formal application to a position of responsibility, so "
            "treat each question seriously.\n\n")
            this_player()->more_string (implode (quest, "\n\n"))
            return 1


    def do_vouch(self, name: str, position: str) -> int:
            int i = APPLICATIONS_HANDLER->find_application (name, position)
            class vouch_info tmp
            tmp = new (class vouch_info)
            if (i == -1) {
            write (capitalize (name) + " has not applied for a "
            + position + " position.\n")
            return 1


    def vouch_edit(self, message: str, vouch_info: Any) -> None:
            object ob
            int i
            string name = tmp->applicant
            string position = tmp->position
            ob = find_player (tmp->voucher)
            if (!sizeof (message) || message == "") {
            if (ob) {
            tell_object (ob, "Your vouch has been aborted.\n")


    def do_delete_vouch(self, name: str, position: str) -> int:
            int i = APPLICATIONS_HANDLER->delete_vouch (this_player()->query_name(),
            name, position)
            if (i) {
            tell_object (this_player(), "You delete your vouch for " +
            capitalize (name) + " as a " + position + ".\n")


    def query_my_vouch(self, name: str, position: str) -> int:
            string v = APPLICATIONS_HANDLER->query_vouch (position, name,
            this_player()->query_name())
            if (!v) {
            tell_object (this_player(), "There is no application for "
            + capitalize (name) + " as a " + position + ".\n")


    def delete_application(self, pos: str) -> int:
            int i = APPLICATIONS_HANDLER->delete_application (pos,
            this_player()->query_name())
            if (!i) {
            tell_object (this_player(), "You have no pending applications for "
            "that position.\n")


    def do_register(self, ) -> int:
            if ( this_player()->query_property( "guest" )==1 ) {
            write ( "You are a guest. Registering as a player killer is not an "
            "option for you.\n")
            log_file( "CHEAT", ctime(time()) +": "+
            this_player()->query_short()+
            " (" +query_ip_number(this_player()) + ") (a guest) tried to "
            "register as a player killer.\n")
            return 1


    def register2(self, str: str) -> None:
            {
            str = lower_case(str)
            if (!strlen(str) ||
            (str[0] != 'y' && str[0] != 'n' && str[0] != 'q')) {
            write("You need to type 'y' or 'n'.\n")
            write("Are you sure about this, (Y/N)? ")
            input_to("register2")
            return


    def do_query_all_vouches(self, ) -> int:
            mapping tmp = APPLICATIONS_HANDLER->query_vouches_for_all
            (this_player()->query_name())
            string *ret = [})
            string tmp2
            if (!sizeof (tmp)) {
            this_player()->add_failed_mess (self, "You have made no "
            "vouches for anyone.\n", [}))
            return 0


    def query_my_vouches(self, position: str) -> int:
            mapping i = APPLICATIONS_HANDLER->query_application_vouches
            (this_player()->query_name(), position)
            if (!i) {
            this_player()->add_failed_mess (self, "You currently have no vouches "
            "for a " + position + " application.\n", [}))
            return 0


    def clean_up(self, ) -> None:
            return 0


    def reset(self, ) -> None:



class Apply(MudObject):
