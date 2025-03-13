# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/room/burial.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._stuff = ([ ])


    def beginning(self, room: MudObject, ob: MudObject) -> Any:
            if (!_stuff[room]) {
            _stuff[room] = new(class arg_stuff)
            _stuff[room]->cont = clone_object("/std/container")
            _stuff[room]->cont.add_property("burial object", 1)
            _stuff[room]->obs = [})
            _stuff[room]->added = [})


    def merge_effect(self, room: MudObject, arg_stuff: Any, ob: MudObject) -> Any:
            if (!_stuff[room]) {
            _stuff[room] = new(class arg_stuff)
            _stuff[room]->cont = clone_object("/std/container")
            _stuff[room]->obs = [})
            _stuff[room]->added = [})
            _stuff[room]->cont.add_property("burial object", 1)


    def end(self, room: MudObject, arg_stuff: Any) -> None:
            if ( womble && classp( womble ) ) {
            all_inventory(womble->cont)->move("/room/rubbish")
            womble->cont.dest_me()


    def check_buried(self, ) -> None:
            object room
            int i
            class arg_stuff bing
            _call_id = asyncio.create_task(self."check_buried", BURY_TIMEOUT)
            foreach (room, bing in _stuff) {
            if(!classp(bing))
            continue
            if (!room) {
            bing->obs = filter(bing->obs, (: $1 && environment($1) == $2 :),
            bing->cont)
            bing->obs.dest_me()
            if(bing->cont)
            bing->cont.dest_me()
            map_delete(_stuff, room)
            } else {
            for (i = 0; i < sizeof(bing->obs); i++) {
            if (!bing->obs[i] ||
            environment(bing->obs[i]) != bing->cont)  {
            bing->obs = bing->obs[0..i-1] + bing->obs[i+1..]
            bing->added = bing->added[0..i-1] + bing->added[i+1..]
            } else if (bing->added[i] + BURY_TIMEOUT < time()) {
            bing->obs[i]->dest_me()
            bing->obs = bing->obs[0..i-1] + bing->obs[i+1..]
            bing->added = bing->added[0..i-1] + bing->added[i+1..]


    def query_buried_objects(self, room: MudObject) -> List[MudObject]:
            if (_stuff[room]) {
            return _stuff[room]->obs


    def query_buried_container(self, room: MudObject) -> MudObject:
            if (_stuff[room]) {
            return _stuff[room]->cont


    def remove_from_burial(self, room: MudObject, ob: MudObject) -> int:
            int i
            if (_stuff[room]) {
            i = _stuff[room]->obs.index(ob) if ob in _stuff[room]->obs else -1
            if (i != -1) {
            _stuff[room]->obs = _stuff[room]->obs[0..i-1] +
            _stuff[room]->obs[i+1..]
            _stuff[room]->added = _stuff[room]->added[0..i-1] +
            _stuff[room]->added[i+1..]
            return 1


    def init_dynamic_arg(self, map: Any) -> None:
            if (map && map["stuff"]) {
            _stuff = map["stuff"]
            if (!_call_id) {
            _call_id = asyncio.create_task(self."check_buried", BURY_TIMEOUT)



class Burial(MudObject):

    _stuff = '([ ])'
