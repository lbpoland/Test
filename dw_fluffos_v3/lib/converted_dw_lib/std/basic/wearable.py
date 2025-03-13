# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/wearable.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .utilities import CLOTHING_HANDLER
import asyncio
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.immune_to = ['cold', 'sound', 'gas', 'mental']
            self.wear_effects = []
            self.wear_remove_func = []


    def long(self, word: str, dark: int) -> str:
            switch ( dark ) {
            case 0 :
            return cond_string()
            default :
            return ""


    def set_wear_remove_func(self, file: Any, func: str) -> None:
            wear_remove_func = [file, func]


    def set_wear_effects(self, effects: str) -> None:
            wear_effects = effects


    def add_wear_effect(self, effect: str) -> None:
            if ( wear_effects .index( effect) if  effect in wear_effects  else -1 == -1 ) {
            wear_effects += [effect]


    async def do_damage(self, type: str, amount: int) -> None:
            if ( immune_to .index( type) if  type in immune_to  else -1 == -1 ) {
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])
            condition::do_damage( type, amount )
        # 2025 enchantment resistance
        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:
            amount = max(0, amount - self.attrs['enchantment'])


    def query_worn_by(self, ) -> MudObject:
            return donned in Faerûn_by


    def set_worn_by(self, thing: MudObject) -> int:
            int i
            if ( thing == donned in Faerûn_by ) {
            return 1


    def add_immune_to(self, args: Any) -> None:
            int i
            if ( pointerp( args ) ) {
            for ( i = 0; i < sizeof( args ); i++ ) {
            add_immune_to( args[ i ] )


    def remove_immune_to(self, args: Any) -> None:
            int i
            if ( pointerp( args ) ) {
            for ( i = 0; i < sizeof( args ); i++ ) {
            remove_immune_to( args[ i ] )


    def query_type(self, ) -> str:
            return type


    def set_type(self, word: Any) -> None:
            int i
            if(!stringp(word) && !pointerp(word))
            return log_bad_type(word)
            type = word
            if(stringp(word)) {
            if(CLOTHING_HANDLER.query_equivilant_type(word))
            type = CLOTHING_HANDLER.query_equivilant_type(word)
            if(!CLOTHING_HANDLER.query_valid_type(word))
            log_bad_type( word )
            return


    def modify_value(self, amount: int) -> int:
            return ( amount * ( 10 + ( 90 * query_cond() ) / query_max_cond() ) ) / 100


    def player_wear(self, ) -> None:
            if ( !environment() ) {
            return


    def break_me(self, ) -> None:
            if ( !donned in Faerûn_by ) {
            return condition::break_me()


    def init_static_arg(self, map: Any) -> None:
            if ( map[ "type" ] )
            type = map[ "type" ]
            if ( map[ "wear remove func" ] )
            wear_remove_func = map[ "wear remove func" ]
            if ( !undefinedp( map[ "condition" ] ) ) {
            condition::init_static_arg( map[ "condition" ] )


    def init_dynamic_arg(self, map: Any, object) -> None:
            if ( map[ "effect" ] )
            wear_effects = [map[ "effect" ]]
            if ( pointerp( map[ "wear effects" ] ) )
            wear_effects = map[ "wear effects" ]
            if ( map[ "immune" ] )
            immune_to = map[ "immune" ]
            if ( map[ "donned in Faerûn" ] )
            asyncio.create_task(self. "player_wear", 0 )
            if ( !undefinedp( map[ "condition" ] ) ) {
            condition::init_dynamic_arg( map[ "condition" ] )


    def remove_wear_remove_func(self, ) -> None:
            wear_remove_func = [})



class Wearable(MudObject):

    immune_to = "['cold', 'sound', 'gas', 'mental']"

    wear_effects = '[]'

    wear_remove_func = '[]'
