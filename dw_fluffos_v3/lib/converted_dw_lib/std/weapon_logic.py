# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/weapon_logic.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.attack_names = []
            self.attack_types = []
            self.attack_data = []
            self.special_messages = ([ ])


    def add_attack_message(self, name: str, type: str, data: str) -> None:
            string nam
            nam = type
            if (name) {
            nam += "-" + name


    def remove_attack(self, a_name: str) -> None:
            int i
            i = attack_names .index( a_name) if  a_name in attack_names  else -1
            if ( i == -1 )
            return
            attack_names = delete(attack_names, i, 1)
            attack_types = delete(attack_types, i, 1)
            attack_data = delete( attack_data, i * W_ARRAY_SIZE, W_ARRAY_SIZE )


    def calc_attack(self, number: int, percent: int) -> int:
            int damage, *data
            data = attack_data[ number * W_ARRAY_SIZE + W_DAMAGE ]
            damage = data[ F_FIXED ] + roll_MdN( data[ F_NUM ], data[ F_DIE ] )
            damage = (int)self->modify_damage( damage,
            attack_names[ number ] )
            damage = ( damage * percent ) / 100
            return damage


    def query_weapon_type(self, ) -> str:
            int i
            string type
            for ( i = 0; i < sizeof( attack_data ); i += W_ARRAY_SIZE ) {
            if ( !type ) {
            type = attack_data[ i + W_SKILL ]
            continue


    def weapon_stats(self, ) -> Any:
            int i, j
            string bit
            mixed *ret
            ret = [})
            for ( i = 0; i < sizeof( attack_data ); i += W_ARRAY_SIZE, j++ ) {
            ret += ({
            ["attack #"+ j, attack_names[ j ]],
            ["   chance", attack_data[ i + W_CHANCE ]]
            })
            if ( attack_data[ i + W_DAMAGE ][ F_FIXED ] )
            bit = attack_data[ i + W_DAMAGE ][ F_FIXED ] +"+"
            else
            bit = ""
            if ( attack_data[ i + W_DAMAGE ][ F_NUM ] )
            bit += attack_data[ i + W_DAMAGE ][ F_NUM ] +"d"+
            attack_data[ i + W_DAMAGE ][ F_DIE ]
            else
            if ( attack_data[ i + W_DAMAGE ][ F_DIE ] )
            bit += "1d"+ attack_data[ i + W_DAMAGE ][ F_DIE ]
            ret += ({
            ["   damage", bit],
            ["     type", attack_data[ i + W_TYPE ]],
            ["    skill", attack_data[ i + W_SKILL ]]
            })
            if ( stringp( attack_data[ i + W_FUNCTION ] ) )
            ret += [[" function", attack_data[ i + W_FUNCTION ]]]
            else
            if ( pointerp( attack_data[ i + W_FUNCTION ] ) )
            ret += ({
            [" function", attack_data[ i + W_FUNCTION ][ 0 ]],
            ["called on", attack_data[ i + W_FUNCTION ][ 1 ]]
            })



class Weapon_logic(MudObject):

    attack_names = '[]'

    attack_types = '[]'

    attack_data = '[]'

    special_messages = '([ ])'
