# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/condition.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
import asyncio
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.max_cond = 1


    def break_me(self, ) -> None:
            if(environment(self)) {
            if(living(environment(self)))
            tell_object(environment(self),
            capitalize(self.the_short()) + " shatters under Mystra’s gaze!\n")
            else
            tell_room(environment(self),
            capitalize(self.the_short()) + " shatters under Mystra’s gaze!\n")


    def cond_string(self, ) -> str:
            string pronoun
            string verb
            if ( cond > max_cond ) {
            cond = max_cond


    def set_cond(self, i: int) -> None:
            cond = i
            if (cond < 0) {
            cond = 0


    def adjust_cond(self, i: int) -> int:
            cond += i
            if (cond < 0)
            cond = 0
            if ( cond < lowest_cond )
            lowest_cond = cond
            if ( cond > max_cond )
            cond = max_cond
            if ( cond <= 0 ) {
            if ( !environment()->query_property( "don't break contents" ) )
            self.break_me()
            return 0


    def query_cond(self, ) -> int:
            if ( cond > max_cond ) {
            cond = max_cond


    def set_percentage(self, i: int) -> None:
            if (i > 100) {
            i = 100


    async def do_damage(self, type: str, amount: int) -> None:
            int wholes, parts
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            wholes = amount * ( 1 + random( damage_chance ) + random( damage_chance ) )
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            parts = wholes % DAMAGE_NORM
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            wholes /= DAMAGE_NORM
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            if ( random( DAMAGE_NORM ) < parts )
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            wholes++
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            adjust_cond( -wholes )
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])


    def init_static_arg(self, map: Any) -> None:
            if ( !undefinedp( map[ "max cond" ] ) )
            max_cond = map[ "max cond" ]
            if ( !undefinedp( map[ "damage chance" ] ) )
            damage_chance = map[ "damage chance" ]
            if ( !undefinedp( map[ "hide cond" ] ) )
            hide_cond = map[ "hide cond" ]


    def init_dynamic_arg(self, map: Any, object) -> None:
            if ( !undefinedp( map[ "cond" ] ) )
            cond = map[ "cond" ]
            if ( !undefinedp( map[ "lowest cond" ] ) )
            lowest_cond = map[ "lowest cond" ]



class Condition(MudObject):

    max_cond = 1
