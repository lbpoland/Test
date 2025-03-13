# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/player_shop/shop_badge.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_name("badge")
            set_short("employee badge")
            add_adjective("employee")
            add_adjective("tin")
            add_adjective("small")
            set_main_plural("employee badges")
            set_weight(1)
            set_value(0)
            set_type("badge")
            setup_armour(640)
            set_damage_chance(5)
            set_wear_remove_func(file_name(self),
            "wear_remove_badge")
            add_property("no recycling", 1)
            add_extra_look(self)
            if (!query_property("office") || !query_property("owner"))
            {
            return


    def init(self, ) -> None:
            {
            object tp
            if (!_office || !_owner)
            {
            if (!get_properties()) return
            set_long("This is a small tin badge which marks "+
            cap_name(_owner) + " as an employee of "+
            _office.query_shop_name()+ ", "+ _office.query_place()+ ".\n")
            add_adjective(_channel)


    def extra_look(self, thing: MudObject) -> str:
            {
            object tp
            tp = this_player()
            if (!_office || !_owner)
            {
            if (!get_properties()) return ""


    def receive(self, channel: str, sender: str, text: str) -> None:
            {
            object owner = environment()
            string *ignoring, prev_ob
            if (!_office || !_owner)
            {
            if (!get_properties()) return


    def set_props(self, path: str, owner: str) -> None:
            {
            if (!path || path == "")
            {
            return


    def wear_remove_badge(self, thing: MudObject) -> None:
            {
            if (!_office || !_owner)
            {
            if (!get_properties()) return



class Shop_badge(MudObject):
