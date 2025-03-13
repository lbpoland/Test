# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/npc/basilisk_stare.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
import asyncio
from ..driver import MudObject, Player, driver
import asyncio

    async def do_damage(self, to: MudObject, amount: int, from: MudObject, id: int) -> None:
            {
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            if (!to) return
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            if (to.query_hp() <= amount)
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            to.delete_effect(to->sid_to_enum(id))
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            to.attack_by(self)
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            to.adjust_hp(-amount, from)
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])


    def stop_fighting(self, who: MudObject, arg: Any, id: int) -> None:
            {
            int *fights, i
            fights = who.effects_matching("fighting")
            if (sizeof(fights))
            for (i = sizeof(fights) - 1; i >= 0; i--)
            who.delete_effect(fights[i])


    def doit(self, them: MudObject, arg: int, id: int) -> None:
            {
            int dam
            object basilisk
            arg--
            them.set_arg_of(them->sid_to_enum(id), arg)
            if (!arg) {
            them.delete_effect(them->sid_to_enum(id))
            return


    def beginning(self, them: MudObject, arg: int, id: int) -> int:
            {
            tell_object(them, "You feel a pair of mental diamond drills penetrating "
            "your brain.\n")
            tell_room(environment(them), them.one_short() +
            "'s soul is about to be ripped apart.\n", them)
            them.submit_ee("stop_fighting", 1, EE_ONCE)
            them.submit_ee("doit", 10, EE_CONTINUOUS)
            them.add_property("passed out", 1)
            return arg


    def end(self, them: MudObject) -> None:
            {
            await them.send("You are freed from the basilisk's deadly stare.\n")
            them.remove_property("passed out")


    def query_shadow_ob(self, ) -> str:
            return SHADOWS+"basilisk_stare"


    def merge_effect(self, them: MudObject, arg1: int, arg2: int, id: int) -> None:
            {
            them.set_arg_of(them->sid_to_enum(id), arg1 + arg2)


    def query_name(self, ) -> str:
            {
            return "a horrible sight"



class Basilisk_stare(MudObject):
