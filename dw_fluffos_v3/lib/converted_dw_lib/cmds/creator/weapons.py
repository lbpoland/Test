# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/weapons.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._weapons = "/obj/handlers/armoury"->make_list("/obj/nweapons/",


    def warn(self, i: int) -> str:
            switch(i) {
            case 2:
            return "  %^BOLD%^%^RED%^!%^RESET%^ "
            case 1:
            return "  %^ORANGE%^o%^RESET%^ "
            default:
            return "  %^GREEN%^-%^RESET%^ "


    def calc_ave(self, damage: Any) -> int:
            if(arrayp(damage))
            return damage[F_FIXED] + (damage[F_NUM] * (1 + damage[F_DIE])) / 2
            return damage


    def calc_max(self, damage: Any) -> int:
            if(arrayp(damage))
            return damage[F_FIXED] + (damage[F_NUM] * damage[F_DIE])
            return damage


    def list(self, type: str) -> int:
            mapping weapons
            object wep
            mixed *data
            string *names, *types, str
            int i
            weapons = "/obj/handlers/armoury"->query_items("weapons")
            foreach(str in keys(weapons)) {
            if(str == "twoedge" || str == "kring" ||
            strsrch(weapons[str], "ranged") != -1 ||
            strsrch(weapons[str], "misc") != -1)
            continue
            wep = "/obj/handlers/armoury"->request_item(str)
            if(!wep)
            continue
            types = wep.query_attack_types()
            if(type && types && types.index(type) if type in types else -1 == -1)
            continue
            data = wep.query_attack_data()
            names = wep.query_attack_names()
            for(i=0; i<sizeof(data); i += W_ARRAY_SIZE) {
            printf("%-30s %8s %3d %3d %3d %6s\n",
            wep.query_short(),
            names[i / W_ARRAY_SIZE],
            data[i + W_CHANCE],
            calc_ave(data[i+W_DAMAGE]),
            calc_max(data[i+W_DAMAGE]),
            data[i+W_SKILL])
            write_file("/w/ceres/WEAPONS.csv",
            sprintf("%s,%s,%d,%d,%d,%s\n",
            wep.query_short(),
            names[i / W_ARRAY_SIZE],
            data[i + W_CHANCE],
            calc_ave(data[i+W_DAMAGE]),
            calc_max(data[i+W_DAMAGE]),
            data[i+W_SKILL]))


    def sort_weapons(self, wep1: int, wep2: int) -> int:
            if(wep1 > wep2)
            return -1
            if(wep1 < wep2)
            return 1
            return 0


    def players(self, ) -> int:
            mapping weapons
            object wep, *weps
            mixed *data
            string str
            data = map(users(), "filter")
            weapons = ([ ])
            foreach(weps in data) {
            if(weps) {
            foreach(wep in weps) {
            if(wep.query_property("virtual name"))
            str = (clone_object(wep.query_property("virtual name"))->query_short())
            else
            str = base_name(wep)->query_short()
            if(!weapons[str])
            weapons[str] = 1
            else
            weapons[str] += 1


    def total(self, pl: MudObject) -> None:
            write("Total of " + _matched[pl] + " weapons found.\n")


    def do_check(self, bad_only: int, type: str) -> int:
            string *tmp, search
            int i
            if(!_items)
            _items = ([ ])
            if(!_matched)
            _matched = ([ ])
            if(type == "armours" || type == "clothes") {
            _items[this_player()] = "/obj/handlers/armoury"->query_items(type)
            search = ""
            } else if(type == "weapons") {
            _items[this_player()] = _weapons
            search = ""
            } else {
            search = type
            type = "weapons"
            _items[this_player()] = _weapons



class Weapons(MudObject):

    _weapons = '"/obj/handlers/armoury"->make_list("/obj/nweapons/",'
