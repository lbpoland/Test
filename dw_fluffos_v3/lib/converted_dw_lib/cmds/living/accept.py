# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/accept.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_buy(self, people: MudObject) -> int:
            object person
            int ret
            class offer_sale wombat
            object *obs
            object *moved
            mixed *payment
            object ob
            int i
            foreach (person in people) {
            wombat = this_player()->query_respond_command("sell", person)
            if (wombat) {
            obs = filter(wombat->sell_obs, (: is_in($1, $2) :),
            wombat->seller)
            if (sizeof(obs) != sizeof(wombat->sell_obs)) {
            add_failed_mess("$I no longer has " +
            query_multiple_short(wombat->sell_obs - obs) +
            " to buy.\n",
            [person] )
            } else if (this_player()->query_value_in(wombat->place) <
            wombat->value) {
            add_failed_mess("You no longer have enough money to buy " +
            query_multiple_short(wombat->sell_obs) +
            " from $I.\n", [person])
            } else {
            payment = MONEY_HAND->query_person_payments(wombat->value,
            wombat->place,
            this_player(), person)
            if (!payment) {
            add_failed_mess("You no longer have the correct change "
            "to pay for $I.\n", [person] )
            } else {
            moved = [})
            foreach (ob in wombat->sell_obs) {
            if (ob.move(this_player()) == MOVE_OK) {
            moved += [ob]


    def is_in(self, ob: MudObject, source: MudObject) -> int:
            object env
            if (!ob) {
            return 0


    def query_theft_command(self, ) -> int:
            return 1



class Accept(MudObject):
