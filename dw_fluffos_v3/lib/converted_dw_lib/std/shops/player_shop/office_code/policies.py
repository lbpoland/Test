# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/office_code/policies.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_policy_suggest(self, name: str, text: str, mgr: str, type: int) -> None:
            {
            if (previous_object() && previous_object() != find_object(_mgr_office))
            {
            LOG_ERROR("office.c", "add_policy_suggest("+name+","+text+","+mgr+")")
            return


    def get_stock_policy(self, {: Any) -> str:
            private void remove_policy(string policy)
            {
            load_new_policies()
            PLAYER_SHOP->auto_mail(_new_policies[policy][POLICY_MGR],
            "Tarnach Fendertwin", "Policy proposition - "+ policy, "",
            "Your proposition has been rejected by majority vote.\n")
            shop_log(GENERAL, "Shop", "rejected the "+ policy + " policy.\n", UNPAID)
            map_delete(_new_policies, policy)
            save_new_policies()



class Policies(MudObject):
