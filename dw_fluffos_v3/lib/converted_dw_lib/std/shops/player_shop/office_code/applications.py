# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/office_code/applications.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_applicant(self, player: str, message: str) -> None:
            {
            if (previous_object() && previous_object() != find_object(_shop_front))
            {
            LOG_ERROR("office.c", "add_applicant("+player+","+message+")")
            return


    def check_hire_list(self, ) -> None:
            {
            int count
            string *hirees = ({})
            load_applicants()
            foreach (string word in m_indices(filter(_applicants,
            (: _applicants[$1][APP_TYPE] == HIRED :))))
            if (time() - _applicants[word][APP_TIME] > HIRE_TIMEOUT)
            {
            PLAYER_SHOP->auto_mail(word, _proprietor,
            _shop_name, "", "Since you have not returned to confirm "
            "your employment with us, we have assumed that you are no "
            "longer interested, and removed your name from our files.  "
            "If you wish to re-apply at any time in the future, please "
            "return to the shop to do so.\n")
            employee_log(word, "Lapsed their application")
            remove_applicant(word)


    def do_cancel(self, ) -> int:
            {
            object tp = this_player()
            remove_applicant(tp.query_name())
            employee_log(tp.query_name(), "Cancelled application")
            await tp.send("You cancel your application.\n")
            return 1


    def do_confirm(self, ) -> int:
            {
            object tp = this_player()
            string applicant = lower_case(tp.query_name())
            if (previous_object() && previous_object() != find_object(_shop_front))
            {
            LOG_ERROR("office.c", "do_confirm()")
            return 0


    def do_vote(self, args: Any, pattern: str) -> int:
            {
            int query_app
            string tp = this_player()->query_name()
            if (pattern == VOTE_APPLICANT)
            {
            args[0] = lower_case(args[0])
            if (!(query_app = query_applicant(args[0])))
            {
            await this_player().send(cap_name(args[0])+
            " hasn't applied!\n")
            return 1



class Applications(MudObject):
