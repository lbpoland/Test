# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/room/yellow-green_gas.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_classification(self, ) -> str:
            {
            return "gas.poisonous"


    def beginning(self, room: MudObject, time: int, int) -> None:
            {
            tell_room(room,
            "A billowing yellow-green gas fills the area!\n")
            room.submit_ee("choke", CHOKE_TIME, EE_CONTINUOUS)
            room.submit_ee("clear", time, EE_REMOVE)
            room.add_extra_look(self)
            room->add_item("billowing yellow-green gas",
            "A thick, yellow-green gas swirls around the area.")


    def merge_effect(self, object, new_time: int, old_time: int, int) -> int:
            {
            int time_left
            time_left = new_time + old_time
            return time_left


    def clear(self, room: MudObject, int, int) -> None:
            {
            tell_room(room, "The yellow-green gas clears.\n")
            room.remove_item("gas")


    def choke(self, room: MudObject, int, int) -> None:
            {
            int damage
            object ob, *obs
            obs = filter(all_inventory(room), (: living($1) :))
            foreach(ob in obs)
            {
            damage = DAMAGE
            damage -= ob.query_ac("gas", damage, "head")
            if(damage > 0)
            {
            tell_object(ob,
            "You choke as you inhale the noxious gas!\n")
            tell_room(room,
            "$C$"+ob.one_short()+" chokes as "+ob.query_pronoun()+
            " inhales the noxious gas!\n", ob)
            ob.adjust_hp(-damage)
            if(ob.query_monitor())
            {
            ob.monitor_points()


    def end(self, room: MudObject, time: int, id: int) -> None:
            {
            room.remove_extra_look(self)


    def extra_look(self, thing: MudObject) -> str:
            {
            return "A billowing yellow-green gas swirls around here.\n"



class Yellow-green_gas(MudObject):
