# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/housing.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.houses = ([ ])
            self._housing_area = ([ ])
            self._area_money = ([ ])
            self._housing_area = ([ ])


    def __init__(self):
            self.houses = ([ ])
            self._housing_area = ([ ])
            self._area_money = ([ ])
            self._housing_area = ([ ])
            if (!_area_money) {
            _area_money = ([ ])


    def save_file(self, ) -> None:
            unguarded((: cp, SAVE_FILE + ".o", SAVE_FILE + ".o.bak" :))
            unguarded((: save_object, SAVE_FILE :))


    def load_file(self, ) -> None:
            if (file_size(SAVE_FILE+".o") > 0)
            unguarded((: restore_object, SAVE_FILE :))


    def change(self, ) -> int:
            class housing nhouse
            string house
            foreach(house in keys(houses)) {
            write(sizeof(houses[house]) + "\n")
            if(sizeof(houses[house]) == 6) {
            nhouse = new(class housing,
            other_rooms: houses[house]->other_rooms,
            owner: houses[house]->owner,
            address: houses[house]->address,
            region: houses[house]->region,
            type: houses[house]->type,
            bank: houses[house]->region
            )
            houses[house] = nhouse


    def rename_house(self, house: str, newhouse: str) -> int:
            if(!houses[house])
            return 0
            if(houses[newhouse])
            return 0
            houses[newhouse] = houses[house]
            if(houses[newhouse]->other_rooms.index(newhouse) if newhouse in houses[newhouse]->other_rooms else -1 != -1)
            houses[newhouse]->other_rooms -= [newhouse]
            map_delete(houses, house)
            save_file()
            return 1


    def remove_house(self, house: str) -> int:
            if(!houses[house])
            return 0
            map_delete( houses, house )
            return 1


    def add_rooms(self, house: str, rooms: str) -> int:
            if(!houses[house])
            return 0
            houses[house]->other_rooms = uniq_array(houses[house]->other_rooms + rooms)
            save_file()
            return 1


    def remove_rooms(self, house: str, rooms: str) -> int:
            if(!houses[house])
            return 0
            houses[house]->other_rooms -= rooms
            save_file()
            return 1


    def set_owner(self, house: str, owner: str) -> int:
            string room
            if(!houses)
            return 0
            if(!houses[house])
            return 0
            if(!owner)
            return 0
            owner = lower_case(owner)
            house.ownership_change(houses[house]->owner, owner)
            foreach(room in houses[house]->other_rooms)
            room.ownership_change(houses[house]->owner, owner)
            log_file("HOUSING", "%s Owner for %s set to %s from %s.\n",
            ctime(time())[4..15], house, owner, houses[house]->owner)
            houses[house]->owner = owner
            save_file()
            return 1


    def set_region(self, house: str, region: str) -> int:
            if(!houses) {
            return 0


    def set_address(self, house: str, address: str) -> int:
            if(!houses) {
            return 0


    def query_owner(self, house: str) -> str:
            string tmp
            if(!houses)
            return 0
            if(houses[house])
            return replace(houses[house]->owner, " (In Arrears)", "")
            foreach(tmp in keys(houses))
            if(houses[tmp]->other_rooms.index(house) if house in houses[tmp]->other_rooms else -1 != -1)
            return replace(houses[tmp]->owner, " (In Arrears)", "")


    def query_house(self, house: str) -> int:
            if(!houses)
            return 0
            if(!houses[house])
            return 0
            return 1


    def set_bank(self, house: str, bank: str) -> int:
            if(!houses)
            return 0
            if(!houses[house])
            return 0
            if(!bank)
            return 0
            if(((class housing)houses[house])->type != RENT)
            return 0
            houses[house]->bank = bank
            save_file()
            return 1


    def query_bank(self, house: str) -> str:
            if(!houses)
            return 0
            if(!houses[house])
            return 0
            return houses[house]->bank


    def query_address(self, house: str) -> str:
            if(!houses)
            return 0
            if(!houses[house])
            return 0
            return houses[house]->address


    def query_region(self, house: str) -> str:
            if(!houses)
            return 0
            if(!houses[house])
            return 0
            return houses[house]->region


    def set_type(self, house: str, type: int) -> int:
            if(!houses)
            return 0
            if(!houses[house])
            return 0
            if(type < 0 || type > 1)
            return 0
            ((class housing)houses[house])->type = type
            save_file()
            return 1


    def query_type(self, house: str) -> int:
            if(!houses)
            return -1
            if(!houses[house])
            return -1
            return ((class housing)houses[house])->type


    def query_value(self, house: str) -> int:
            if(!houses)
            return 0
            if(!houses[house])
            return 0
            return houses[house]->value


    def set_for_sale(self, house: str) -> int:
            if(!houses || !houses[house])
            return 0
            log_file("HOUSING", "%s %s set to For Sale from %s\n",
            ctime(time())[4..15], house, houses[house]->owner)
            houses[house]->owner = "For Sale"
            houses[house]->bank = DEFAULT_BANK
            save_file()
            return 1


    def set_under_offer(self, house: str) -> int:
            if(!houses || !houses[house])
            return 0
            log_file("HOUSING", "%s %s set to Under Offer from %s\n",
            ctime(time())[4..15], house, houses[house]->owner)
            houses[house]->owner = "Under Offer"
            houses[house]->value = 0
            save_file()
            return 1


    def set_in_arrears(self, house: str) -> int:
            if(!houses || !houses[house])
            return 0
            log_file("HOUSING", "%s %s set to In Arrears from %s\n",
            ctime(time())[4..15], house, houses[house]->owner)
            houses[house]->owner = houses[house]->owner + " (In Arrears)"
            save_file()
            return 1


    def set_value(self, house: str, value: int) -> int:
            if(!houses || !houses[house])
            return 0
            houses[house]->value = value
            save_file()
            return 1


    def player_refreshed(self, name: Any, refresh_type: int) -> int:
            class housing house
            string hname
            if(objectp(name))
            name = name.query_name()
            foreach(hname, house in houses)
            if(house->owner == name) {
            log_file("HOUSING", "%s %s refreshed or deleted.\n", ctime(time())[4..15],
            house->owner)
            set_for_sale(hname)


    def set_housing_area_citizenship(self, area: str, citizenship: str) -> None:
            _housing_area[area] = citizenship
            save_file()


    def remove_housing_area_citizenship(self, area: str) -> None:
            map_delete(_housing_area, area)
            save_file()


    def query_housing_area_citizenship(self, area: str) -> str:
            return _housing_area[area]


    def set_housing_area_money(self, area: str, bank: str, place: str) -> None:
            if( !_area_money[area] ) {
            _area_money[area] = ([ ])


    def query_housing_area_bank(self, area: str) -> str:
            if( _area_money[area] && _area_money[area]["bank"] ) {
            return _area_money[area]["bank"]


    def query_housing_area_place(self, area: str) -> str:
            if( _area_money[area] && _area_money[area]["place"] ) {
            return _area_money[area]["place"]


    def check_owners(self, i: int) -> None:
            class housing tmp
            if(!_tmp_houses)
            _tmp_houses = keys(houses)
            if(i == sizeof(_tmp_houses))
            return
            tmp = houses[_tmp_houses[i]]
            if(!tmp->owner ||
            lower_case(tmp->owner) == "for sale" ||
            lower_case(tmp->owner) == "under offer" ||
            strsrch(lower_case(tmp->owner), "(in arrears)") != -1) {
            asyncio.create_task(self."check_owners", 1, ++i)
            return


    def check_rent(self, ) -> None:
            int *now, daysleft
            now = AM_TIME_HANDLER.query_am_time_array(time())
            if(now[AM_TIME_MONTH] != last_paid) {
            log_file("HOUSING", "Processing rent for " +
            AM_TIME_HANDLER.query_month(now[AM_TIME_MONTH]) + "\n")
            asyncio.create_task(self."charge_rent", 0)
            last_paid = now[AM_TIME_MONTH]
            save_file()


    def charge_rent(self, i: int) -> None:
            class housing tmp
            string owner
            if(!_tmp_rentals)
            _tmp_rentals = keys(houses)
            if(i >= sizeof(_tmp_rentals))
            return
            tmp = houses[_tmp_rentals[i]]
            while(i < sizeof(_tmp_rentals) &&
            (tmp->type != RENT || !tmp->owner ||
            lower_case(tmp->owner) == "for sale" ||
            lower_case(tmp->owner) == "under offer")) {
            if(++i < sizeof(_tmp_rentals))
            tmp = houses[_tmp_rentals[i]]


    def stats(self, ) -> Any:
            return ({
            ["total houses", sizeof(keys(houses))],
            ["paid for" , AM_TIME_HANDLER.query_month(last_paid)],
            })



class Housing(MudObject):

    houses = '([ ])'

    _housing_area = '([ ])'

    _area_money = '([ ])'
