# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/office_code/cabinets.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def confirm_cabinet(self, confirm: str, rent: int) -> None:
            {
            if (previous_object() && previous_object() != self)
            {
            LOG_ERROR("office.c", "confirm_cabinet("+confirm+","+rent+")")
            return


    def do_remove(self, ) -> int:
            {
            int stock
            if (!((stock = _num_cabinets) > MIN_CABINETS))
            {
            tell_object(this_player(), "The shop already contains the "
            "minimum number of cabinets.\n")
            return 1


    def do_rent(self, ) -> int:
            {
            if (!(_num_cabinets < MAX_CABINETS))
            {
            tell_object(this_player(), "The shop already contains the "
            "maximum number of cabinets.\n")
            return 1


    def query_cabinet_used(self, cabinet: int) -> int:
            {
            foreach(string word in m_indices(_list))
            if ( _list[word][CHART_CAB].index(cabinet) if cabinet in _list[word][CHART_CAB] else -1 != -1)
            return TRUE
            return FALSE



class Cabinets(MudObject):
