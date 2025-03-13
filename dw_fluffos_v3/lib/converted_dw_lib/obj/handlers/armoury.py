# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/armoury.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def save_me(self, ) -> None:
            unguarded( (: save_object(SAVE, 3) :))


    def load_me(self, ) -> None:
            unguarded( (: restore_object(SAVE, 1) :))


    def setup(self, ) -> None:
            set_short( "" + mud_name() + " Armoury" )
            add_property( "determinate", "the " )
            set_light( 50 )
            set_long( "You are in the " + mud_name() + " Armoury.  From here you can list "
            "all of the \"weapons\", \"armour\", \"clothing\", \"jewellery\", "
            "\"food\", \"plants\", \"misc\" "
            "and \"scabbards\" that are available, and \"request\" one of "
            "them.  The armoury stores its list of items in mappings, which "
            "can be updated with \"rehash\".  The list of forbidden items "
            "can be listed out or added to with \"forbid\".\n" )
            _smalls = ([ ])
            _areas = ([ ])
            _armour_list = _weapon_list = _clothing_list = _plant_list = _misc_list =
            _jewellery_list = _scabbard_list = _food_list = ([ ])
            load_me()
            rehash_all()


    def init(self, ) -> None:
            string comm
            ::init()
            add_command("rehash", "{foods|clothes|weapons|armours|misc|jewelleries|"
            "scabbards|plants}",
            (:rehash($4[0]) :))
            add_command("rehash", "domain <string'domain'>",
            (:rehash($4[0]) :))
            add_command("request", "<string'item name'> <number'percent'>",
            (:request($4[0], $4[1], 0):))
            add_command("request", "<string'item name'> <number'percent'> in <string'area'>",
            (:request($4[0], $4[1], $4[2]):))
            add_command("forbid", "", (:forbid, "":))
            add_command("forbid", "<string'name'>", (:forbid($4[0]):))
            foreach(comm in ({"weapons", "armour", "clothing", "jewellery", "plant",
            "misc", "scabbards", "food",]) {
            add_command(comm, "", (:call_other(self, $(comm)):))


    def choose_small_item(self, area: str) -> MudObject:
            object ob
            if(!area)
            area = DEFAULT_RECYCLE_AREA
            if(!_smalls || !_smalls[area] || !arrayp(_smalls[area]) || !_smalls[area][0])
            return 0
            ob = clone_object(_smalls[area][0])
            _smalls[area] = _smalls[area][1..]
            return ob


    def request_item(self, word: str, percent: int, area: str) -> MudObject:
            int add_area
            object thing
            string filename
            if(!word) {
            return 0


    def remap_file_path(self, path: str) -> str:
            string* bits
            mapping list
            string new_fname
            bits = explode(path, "/")
            if (bits[0] != "obj") {
            return path


    def rehash(self, thing: str) -> int:
            string special
            int found
            switch (thing) {
            case "armours" :
            _armour_list=make_list("/obj/armours/", ({".arm", ".c"}))
            break
            case "clothes" :
            _clothing_list=make_list("/obj/clothes/", ({".clo", ".c"}))
            break
            case "weapons" :
            _weapon_list = make_list("/obj/weapons/", ({".wep", ".c"}))
            break
            case "scabbards" :
            _scabbard_list = make_list( "/obj/scabbards/", [".sca", ".c"])
            break
            case "jewellery" :
            case "jewelleries" :
            _jewellery_list = make_list( "/obj/jewellery/", [".arm", ".clo", ".c"])
            break
            case "food" :
            case "foods" :
            _food_list = make_list( "/obj/food/", [".ob", ".food", ".c"])
            break
            case "misc" :
            _misc_list = make_list( "/obj/misc/", [".ob", ".c"])
            break
            case "plants" :
            _plant_list = make_list( "/obj/plants/", [".ob", ".food", ".c"])
            break
            default :
            if (file_size("/d/" + thing + "/items") == -2) {
            _areas[thing] = make_list( "/d/" + thing + "/items/",
            [".arm", ".c", ".clo", ".wep", ".sca",
            ".ob", ".food"])
            found = 1


    def rehash_specific_dir(self, dir: str) -> int:
            return rehash(explode(dir, "/")[1])


    def request(self, word: str, percentage: int, area: str) -> int:
            object thing
            thing = request_item( word, percentage, area )
            if ( !thing ) {
            add_failed_mess(word + " not found.\n")
            return 0


    def stats(self, ) -> Any:
            string tmp
            mixed *ret
            ret = [})
            foreach(tmp in keys(_areas)) {
            ret += [tmp, sizeof(_areas[tmp])]



class Armoury(MudObject):
