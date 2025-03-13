# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/con_sider.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject) -> Any:
            object ob
            int level, ok, dif, total, them
            string out
            if(previous_object()->check_dark((int)environment(previous_object())->
            query_light()) < 0) {
            add_failed_mess("It's too dark to consider anyone.\n")
            return 0


    def do_compare(self, dif: int) -> str:
            string ret
            int level
            ret = "$C$$who$"
            level = PLAYER_DRUNK_EFFECT.query_drunk_level(this_player())
            if (level > 4) {
            if (level > 7) {
            return "%^BOLD%^%^GREEN%^Mate!  They looked at you wrong, you "
            "better sort them out before they get more cocky.%^RESET%^"


    def calc_weapon_damage(self, weapon: MudObject) -> int:
            mixed *data
            int wdam, *damage, i
            data = (mixed *)weapon.query_attack_data()
            if(sizeof(data)) {
            wdam = 0
            for ( i = 0; i < sizeof( data ); i += W_ARRAY_SIZE ) {
            if (member_array( data[ i + W_TYPE ], ["blunt", "unarmed",
            "sharp", "pierce"] ) == -1 )
            continue
            damage = data[ i + W_DAMAGE ]
            wdam += ( data[ i + W_CHANCE ] * ( damage[ F_FIXED ] +
            ( damage[ F_NUM ] * damage[ F_DIE ] ) / 2 ) ) / 100
            wdam += damage[ F_FIXED ] + damage[ F_NUM ] * damage[ F_DIE ]


    def calc_value(self, arr: Any) -> int:
            if (intp(arr))
            return arr
            if (!pointerp(arr))
            return 0
            if (sizeof(arr) == 1)
            return arr[F_FIXED]
            if (sizeof(arr) == 2)
            return arr[F_FIXED]+arr[F_NUM]
            return arr[F_FIXED]+(arr[F_NUM] * arr[F_DIE])


    def calc_armour_protection(self, armour: MudObject) -> int:
            int ac, i
            mapping data
            mixed *stuff
            if(!armour.query_armour())
            return 0
            data = armour.query_armour_class()
            if(!sizeof(data))
            return 0
            stuff = keys(data)
            for(i=0; i<sizeof(stuff); i++)
            ac += calc_value(data[stuff[i]][0])
            return ac


    def calc_danger(self, ob: MudObject) -> int:
            object weapon
            object *weapons
            object armour
            object rider
            int wdam
            int wskill
            int dskill
            int ac
            int hp
            int trans
            if (ob.query_transport()) {
            foreach (rider in ob.query_riders()) {
            trans += calc_danger(rider)



class Con_sider(MudObject):
