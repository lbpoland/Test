# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/delivery.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._delivery = ([ ])
            self._save_file = ""
            self._delivery_delay = 5
            self._delivery_mess = "\nA small womble wearing a bright green hat "
            self._burdened_mess = "\nA small womble wearing a bright purple "
            self._cont = clone_object("/std/container")


    def add_delivery(self, who: Any, sender: Any, item: MudObject, delay: int) -> None:
            string name, from
            class delivery_item parcel
            if (objectp(who))
            name = who.query_name()
            else
            name = who
            if (objectp(sender))
            from = sender.query_cap_name()
            else
            from = sender
            parcel = new(class delivery_item,
            delivery_ob : item, submit_time : time(), sent_by : from,
            delay_time : delay)
            if (undefinedp(_delivery[name]))
            _delivery[name] = [parcel]
            else
            _delivery[name] += [parcel]
            log_file("DELIVERY", "%s added a new delivery item for %s, %s sent "
            "by %s.\n", previous_object()->short(), name, item.short(),
            from)
            item.move(_cont)
            save_file()


    def query_theft_command(self, ) -> int:
            return -1


    def clean_delivery_mapping(self, ) -> None:
            string *people, person
            people = keys(_delivery)
            foreach (person in people) {
            _delivery[person] = filter(_delivery[person],
            (: objectp($1->delivery_ob) :))


    def load_file(self, ) -> None:
            int i, j, size
            mixed *tmp
            string who
            mixed *items
            if(_save_file == "")
            return
            log_file("DELIVERY", "Attempting to load save file at %s.\n",
            ctime(time()))
            tell_creator("ceres", "Loading: %s\n", _save_file)
            if (file_size(_save_file + ".o") > -1) {
            unguarded((: restore_object, _save_file :))
            if (!_cont)
            _cont = clone_object("/std/container")
            all_inventory(_cont)->move("/room/rubbish")
            for (i = 0; i < sizeof(_item_save); i = i + 2) {
            who = _item_save[i]
            items = _item_save[i + 1]
            if (!_delivery[who])
            return
            tmp = load_auto_load_to_array(items, this_player())
            size = sizeof(tmp)
            for (j = 0; j < size; j++) {
            _delivery[who][j]->delivery_ob = tmp[size - j - 1]
            tmp[j]->move(_cont)


    def dest_me(self, ) -> None:
            if (_cont)
            _cont.dest_me()


    def query_cont(self, ) -> MudObject:
            return _cont


    def tidy_up(self, ) -> None:
            string person
            foreach(person in keys(_delivery)) {
            if(!PLAYER_HANDLER.test_user(person) || !PLAYER_HANDLER.test_active(person)) {
            log_file("DELIVERY", "%s Removing delivery for %s (inactive).\n",
            self.query_short(), person)
            map_delete(_delivery, person)



class Delivery(MudObject):

    _delivery = '([ ])'

    _save_file = '""'

    _delivery_delay = 5

    _delivery_mess = '"\\nA small womble wearing a bright green hat "'

    _burdened_mess = '"\\nA small womble wearing a bright purple "'

    _cont = 'clone_object("/std/container")'
