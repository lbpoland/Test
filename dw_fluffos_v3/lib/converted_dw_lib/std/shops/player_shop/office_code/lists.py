# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/office_code/lists.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def badge_list(self, ) -> str:
            {
            string *results = ({}),
            *creators = ({})
            foreach(object ob in children(BADGE))
            {
            if (ob == find_object(BADGE)) continue
            if (ob.query_channel() != _channel) continue
            if (environment(ob)->query_creator())
            creators += [environment(ob)->query_name()]


    def do_list(self, ) -> int:
            {
            int emps_in
            string results = "   Employees of "+ _shop_name + "\n"
            "     As at " + ctime(time()) + "\n\n"
            foreach (string word in sort_array(_retired, 1))
            {
            object ob = find_player(word)
            if (ob)
            results += "%^GREEN%^"
            results += "     "+ cap_name(word)+
            "%^RESET%^ (retired manager)\n"


    def employees_clocked_in(self, ) -> str:
            {
            object *words = ({}), ob
            if (!num_employees_in()) words = ({"No employees"})
            if (find_object(_shopkeeper) &&
            _employees[_shopkeeper.query_name()][EMP_POINTS] & CLOCKED_IN)
            words = ({_shopkeeper.query_short()})
            foreach (string word in m_indices(_employees))
            {
            ob = find_player(word)
            if (ob && _employees[word][EMP_POINTS] & CLOCKED_IN)
            words += ({ob.query_cap_name()})



class Lists(MudObject):
