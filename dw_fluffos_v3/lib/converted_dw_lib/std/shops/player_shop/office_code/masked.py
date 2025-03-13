# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/office_code/masked.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def dest_me(self, ) -> None:
            {
            if (_very_short != UNSET_STR)
            {
            if (remove_asyncio.create_task(self._call_save) != -1) do_save()
            if (remove_asyncio.create_task(self._call_apps) != -1) do_save_applicants()
            if (remove_asyncio.create_task(self._call_hist) != -1) do_save_hist()
            if (remove_asyncio.create_task(self._call_newpols) != -1) do_save_new_policies()
            if (remove_asyncio.create_task(self._call_pols) != -1) do_save_policies()
            if (remove_asyncio.create_task(self._call_times) != -1) save_times()
            if (remove_asyncio.create_task(self._call_emps) != -1) do_save_emps()


    def event_enter(self, ob: MudObject, message: str, from: MudObject) -> None:
            {
            string room
            if (!from || ob.query_creator() || from == find_object("/room/void") ||
            !ob.query_player()) return
            room = file_name(from)
            if (room == _counter || room == _shop_front || room == _storeroom ||
            room == _mgr_office || from == self) return
            #ifdef DEBUG
            tell_creator(CREATOR, "%s arrived from %O.\n", ob.query_name(), from)
            #endif
            fire_them(_proprietor, ob.query_name(), "for teleporting into the shop")


    def init(self, ) -> None:
            {
            object tp = this_player()
            string word = tp.query_name()
            ::init()
            if (!tp.query_creator() && !_employees[word] &&
            (_retired.index(word) if word in _retired else -1 == -1)) return
            add_command("claim", "{badge|handbook|bonus}", (: do_claim($4[0]) :))
            add_command("resign", "", (: do_resign() :))
            add_command("list", "", (: do_list() :))
            add_command("office", "", (: do_office() :))
            if (!_board) add_command("memo", "", (: do_memo() :))
            if (_retired.index(word) if word in _retired else -1 != -1) return
            add_command("clock", "{in|out}", (: do_clock($4[0]) :))
            add_command("bank", ["", "<number>"], (: do_bank($4) :))
            if (!this_player()->query_property("no score"))
            add_command( "promotion", "{on|off}", (: do_promote($4[0]) :) )
            if (!tp.query_creator() &&  !(_employees[word][EMP_POINTS] & SUPERVISOR))
            return
            add_command("chart", ({CHART_ADDITEM, CHART_REMITEM, CHART_MAXITEM,
            CHART_BUYITEM, CHART_SELLITEM, CHART_ASSIGN_ITEM, CHART_UNASSIGN_ITEM}),
            (: do_chart($4,$5) :))
            add_command("check", "cabinets", (: do_check() :))
            if (!tp.query_creator() && !(_employees[word][EMP_POINTS] & MANAGER))
            add_command( "logs", ({LOG_BLANK, LOG_NUMBER, LOG_CHART}),
            (: do_logs($4,$5) :))
            else
            add_command("logs", ({LOG_BLANK, LOG_NUMBER,
            LOG_MGR}), (: do_logs($4,$5) :))


    def refresh_function(self, employee: Any, flag: int) -> None:
            {
            string emp_name
            switch (flag)
            {
            case PLAYER_DELETED :
            emp_name = employee
            break
            case TOTAL_REFRESH :
            case PARTIAL_REFRESH :
            emp_name = employee.query_name()
            break



class Masked(MudObject):
