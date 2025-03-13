# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/room/swinging.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, arg: int) -> None:
            int st, tt
            player.submit_ee("swinging", ({15, 30}), EE_CONTINUOUS)
            player.submit_ee( 0, arg, EE_REMOVE )
            tt = (int)player.expected_tt()
            st = (tt - 15)
            player.submit_ee("slowing", (st), EE_ONCE)
            if (tt < 61) {
            player.add_succeeded_mess(previous_object(), ({
            "You push off with your feet and start to swing back and "
            "forth.\n",
            "$N push$s off with $p feet and start$s to swing back and "
            "forth.\n"}))
            player.set_position("swinging back and forth")
            player.set_position_type("on")


    def merge_effect(self, player: MudObject, old_arg: int, new_arg: int) -> None:
            int tt, st
            tt = (int)player.expected_tt()
            tell_room(environment(player), capitalize(player.a_short() ) +
            " leans back and pulls on the swing to gain momentum.\n", player)
            tell_object(player, "You lean back and pull on the swing "
            "to gain momentum.\n")
            player.submit_ee(0, new_arg + tt, EE_REMOVE)
            st = (tt -15)
            player.submit_ee("slowing", (st), EE_ONCE)


    def end(self, player: MudObject) -> None:
            if(file_name(environment(player)) != SWINGS)
            return
            await player.send("You stop swinging.\n")
            tell_room(environment(player), capitalize(player.a_short()) +
            " stops swinging.\n", player)
            player.set_position("sitting")
            player.set_position_type("in")


    def swinging(self, player: MudObject) -> None:
            if(file_name(environment(player)) != SWINGS){
            player.submit_ee(0, 0, EE_REMOVE)
            return


    def slowing(self, player: MudObject) -> None:
            if ( (int)player.expected_tt() < 20 ) {
            tell_object(player, "Your swinging is slowing down as you "
            "gradually lose momentum.\n")
            tell_room(environment(player), capitalize(player.a_short()) +
            " slows down a bit as "+player.query_pronoun()+" loses "
            "momentum.\n", player)



class Swinging(MudObject):
