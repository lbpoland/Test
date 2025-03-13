# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/applications_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def load_me(self, ) -> None:
            unguarded ((: restore_object (APPLY_SAVE_FILE) :))


    def save_me(self, ) -> None:
            unguarded ((: save_object (APPLY_SAVE_FILE) :))


    def toggle_domain_lock(self, dom: str) -> int:
            object ob = load_object ("/d/" + dom + "/master")
            if (ob.query_lord() != this_player()->query_name()) {
            return -1


    def query_applications_accepted(self, dom: str) -> int:
            return (undefinedp (domain_lockout[dom]) ? -1 : domain_lockout[dom])


    def query_responsibility(self, type: str) -> str:
            int i
            object ob
            string dom
            i = find_type (type)
            if (i == -1) {
            dom = type
            type = "creator"
            i = find_type (type)


    def add_application(self, t: str, n: str, te: str, dom: str) -> int:
            class application tmp
            int i
            i = find_application (n, t)
            if (i != -1) {
            return 0


    def __init__(self):


    def find_application(self, name: str, type: str) -> int:
            for (int i = 0; i < sizeof (applications); i++) {
            if (applications[i]->name == name && applications[i]->type == type) {
            return i


    def find_type(self, type: str) -> int:
            for (int i = 0; i < sizeof (types); i++) {
            if (types[i]->type == type) {
            return i


    def reset(self, ) -> None:
            int j
            class application *tmp = [})
            for (int i = 0; i < sizeof (applications); i++) {
            j = find_type (applications[i]->type)
            if (applications[i]->time + types[j]->timeout < time()) {
            tmp += [applications[i]]
            mail_message (0, i)


    def delete_vouch(self, who: str, name: str, position: str) -> int:
            int i = find_application (name, position)
            if (i == -1) {
            return 0


    def delete_application(self, t: str, n: str) -> int:
            int i = find_application (n, t)
            if (i == -1) {
            return 0


    def number_of_vouches(self, name: str, type: str) -> int:
            int i = find_application (name, type)
            if (i == -1) {
            return 0


    def query_vouch(self, t: str, p: str, n: str) -> str:
            int i = find_application (p, t)
            if (i == -1) {
            return 0


    def make_vouch(self, t: str, p: str, n: str, v: str) -> int:
            int i = find_application (p, t)
            int newv = 1
            if (i == -1) {
            return -1


    def query_intro_text(self, type: str) -> str:
            int i = find_type (type)
            return types[i]->intro_text


    def valid_application(self, name: str, type: str) -> int:
            int i = find_type (type)
            object ob = find_player (name)
            if (ob.query_level() < types[i]->gl_requirement) {
            return 0


    def application_requirements(self, type: str) -> str:
            int i = find_type (type)
            string ret = ""
            if (i == -1) {
            return "Applications of that category are not handled by this "
            "system."


    def format_application(self, i: int) -> str:
            string post
            post = "%^BOLD%^Application:%^RESET%^\n"
            "=-=-=-=-=-=-\n\n" +
            "Age: " + query_time_string(-1 * PLAYER_HANDLER->test_age
            (applications[i]->name)) + "\n" +
            "Application made: " + ctime (applications[i]->time) + "\n\n"
            + applications[i]->text + "\n\n"
            post += "\n\n%^BOLD%^Vouches:%^RESET%^\n"
            "=-=-=-=-\n"
            foreach (string v, string t in applications[i]->vouches) {
            post += "\n\n%^CYAN%^" + capitalize (v) + " (" + query_time_string (-1 *
            PLAYER_HANDLER->test_age (v)) + "):%^RESET%^\n\n" + t


    def list_applications(self, ) -> str:
            string *ret = [})
            ret += ({"\n"})
            ret += ({"\n\n/---------------------------------------------------------------------------\\"})
            ret += ({sprintf ("| %|12s | %|12s | %|24s | %|2s  | %|10s |",
            "Type", "Name", "Made At", "V", "Domain")]
            ret += ({"|---------------------------------------------------------------------------|"})
            for (int i = 0; i < sizeof (applications); i++) {
            ret += ({sprintf ("| %|12s | %|12s | %|s | %|2d  | %|10s |",
            capitalize (applications[i]->type),
            capitalize (applications[i]->name), ctime (applications[i]->time),
            sizeof (applications[i]->vouches),
            capitalize ((applications[i]->type == "creator" ? applications[i]->domain :
            "")))]


    def fix_name(self, n: str, n2: str) -> int:
            int i
            int c = 0
            for (int j =0; j < sizeof (types); j++) {
            i = find_application (n, types[j]->type)
            if (i != -1) {
            applications[i]->name = n2
            c++


    def query_name(self, ) -> str:
            return "Applications Handler"



class Applications_handler(MudObject):
