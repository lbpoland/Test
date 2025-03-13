# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/mgr_office.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            {
            ::init()
            if (!_office || _office == "") return
            if ( !_office.query_manager(this_player()->query_name()) &&
            !_office.query_retired(this_player()->query_name()) &&
            !this_player()->query_creator()) return
            add_command("list", ({LIST_BLANK, LIST_CHOICE}),
            (: do_list($4) :))
            add_command("memo", "", (: do_memo() :))
            add_command("office", "", (: do_office() :))
            add_command("claim", "", (: do_claim() :))
            add_command("accounts", "", (: do_accounts() :))
            add_command("logs", ({LOG_BLANK, LOG_NUMBER, LOG_MGR}),
            (: do_logs($4,$5) :))
            add_command("mail", ({"", "<string>"}), (: do_mail($4) :))
            add_command("query", "{pay|employees}", (: do_query($4[0]) :))
            add_command("view", ({VIEW_EMP, VIEW_APP}), (: do_view($4[0],$5) :))
            add_command("project", "{pay|bonus}", (: do_project($4[0]) :))
            add_command("vote", VOTE_POLICY, (: do_vote($4,$5) :))
            add_command("policy", ({POLICY_SUGGEST, POLICY_REMOVE}),
            (: do_policy($4,$5) :))
            add_command("policies", "", (: do_policies() :))
            if (_office.query_retired(this_player()->query_name())) return
            add_command("rent", "cabinet", (: do_rent() :))
            add_command("remove", "cabinet", (: do_remove() :))
            add_command("retire", "", (: do_retire() :))
            add_command("vote", VOTE_APPLICANT, (: do_vote($4,$5) :))
            add_command("check", "votes", (: do_check() :))
            add_command("commend", "<word'employee'>", (: do_commend($4[0]) :))
            add_command("fire", "<word'employee'> [for] <string'reason'>",
            (: do_fire($4) :))
            add_command("warn", "<word'employee'> [for] <string'reason'>",
            (: do_warn($4) :))
            add_command("demote", "<word'employee'>", (: do_demote($4[0]) :))
            add_command("suspend", "<word'employee'> [for] <number> [months]",
            (: do_suspend($4) :))
            add_command("leave", "<word'employee'> [for] <number> [days]",
            (: do_leave($4) :))
            add_command("ban", "<word'person'> [for] <string'reason'>",
            (: do_ban($4) :))
            add_command("unban", "<word'person'>", (: do_unban($4[0]) :))
            add_command("set", ({SET_EMPS, SET_PAY}), (: do_set($4,$5) :))
            add_command("transfer", "<number'amount'> <string'type'> [from] "
            "{register|bonus|profit} [to] {register|bonus|profit}",
            (: do_transfer($4) :))


    def dest_me(self, ) -> None:
            {
            if (_notice) _notice.dest_me()
            ::dest_me()


    def event_death(self, k: MudObject, o: MudObject, k2: MudObject, r: str, k3: str) -> None:
            {
            _office.event_death(k, o, k2, r, k3)


    def event_enter(self, ob: MudObject, message: str, from: MudObject) -> None:
            {
            _office.event_enter(ob, message, from)



class Mgr_office(MudObject):
