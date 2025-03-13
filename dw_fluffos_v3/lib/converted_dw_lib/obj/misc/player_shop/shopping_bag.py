# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/player_shop/shopping_bag.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_name("bag")
            set_short("shopping bag")
            add_adjective("shopping")
            set_main_plural("shopping bags")
            set_long("This is a small paper shopping bag, designed to "
            "hold a number of small items.  It doesn't look very sturdy.\n")
            set_value(3)
            set_transparent()
            add_property("no recycling",1)
            set_weight(1)
            set_max_weight(MAX_BAG_WEIGHT)


    def change_condition(self, ) -> None:
            {
            adjust_cond(-(10 + random(10)))


    def test_add(self, thing: MudObject, flag: int) -> int:
            {
            if (sizeof(all_inventory()) >= MAX_BAG_ITEMS)
            {
            tell_object(this_player(), "The bag can only hold "+
            query_num(MAX_BAG_ITEMS)+ " items.\n")
            return 0


    def test_remove(self, thing: MudObject, flag: int, dest: Any) -> int:
            {
            if (!query_cond()) set_cond(20)
            asyncio.create_task(self.(: change_condition() :), 1)
            return ::test_remove(thing,flag,dest)



class Shopping_bag(MudObject):
