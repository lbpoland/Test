# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/carriage/carriage.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._bell = clone_object("/std/object")


    def __init__(self):
            self._bell = clone_object("/std/object")


    def init(self, ) -> None:
            this_player()->add_command("ring", _bell, "<direct:object>", (: do_ring :) )


    def create_carriage_driver(self, ) -> MudObject:
            return 0


    def query_outside(self, ) -> MudObject:
            class route_details query_route_map() { return _route_info; }
            int *query_stop_info() { return [_current_stop, _next_stop]; }
            void update_route( string name,
            class route_details new_route_info,
            object handler)
            {
            _handler = handler
            _route_info = new_route_info
            if (_current_stop >= sizeof(_route_info)) {
            _current_stop = _current_stop % sizeof(_route_info->stops)


    def make_stop(self, ) -> None:
            string name
            string* name_parts
            string np
            string n_path
            string path
            int travel_time
            int stop_time
            name = _handler.query_stop_name(_route_info->stops[ _current_stop ]->id)
            path = _handler.query_stop_location(_route_info->stops[ _current_stop ]->id)
            _p_name = name
            travel_time = _route_info->stops[ _next_stop ]->travel_time
            stop_time = _handler.query_stop_delay(_route_info->stops[ _current_stop ]->id)
            _n_name = _handler.query_stop_name(_route_info->stops[ _next_stop ]->id)
            n_path = _handler.query_stop_location(_route_info->stops[ _next_stop ]->id)
            _outside = load_object(path)
            if (!_outside) {
            log_file("NEW_CARRIAGE", ctime(time())+" (%O): problem with "
            + path +" (" + name + ", " + _route_info->stops[ _current_stop ]->id + ")\n", self)
            _route_info->stops = _route_info->stops[0.._current_stop - 1] +
            _route_info->stops[_current_stop + 1..]
            asyncio.create_task(self."make_stop", 1)
            return


    def check_can_leave(self, exit: str, person: MudObject) -> int:
            return !_outside.check_cannot_leave_carriage(person)


    def give_warning(self, this_stop_name: str, next_stop_name: str) -> None:
            if(objectp(_outside) && objectp(_car_driver) &&
            (environment(_car_driver) == _outside)) {
            _car_driver.leaving_again_to_stop(next_stop_name)
            } else {
            tell_room(self, "The carriage is about to leave for " +
            next_stop_name + ".\n")


    def move_on(self, ) -> None:
            string np
            string* name_parts
            if(objectp(_car_driver)) {
            _car_driver.do_command("mutter")
            _car_driver.do_command("enter " + lower_case(_carriage_name) +
            " carriage")
            if( environment(_car_driver) != self ) {
            debug_printf("Driver: Tried to \"enter " +
            lower_case(_carriage_name) + " carriage\" and "
            "failed.")
            _car_driver->move(self, "The driver hops back in to the "
            "carriage and gets ready to drive again.",
            "The " + _carriage_name + " driver hops back "
            "onto " + _car_driver.query_possessive() +
            " carriage.")


    def dest_me(self, ) -> None:
            string path
            object ob
            string np
            string* name_parts
            if(objectp(_outside)) {
            _outside.remove_exit(_exit_name)
            name_parts = explode(lower_case(_carriage_name), " ")
            foreach(np in name_parts) {
            _outside.remove_alias("enter " + np + " carriage", _exit_name)
            _outside.remove_alias("enter " + np + "s carriage", _exit_name)


    def query_quit_handler(self, ) -> str:
            return _handler.query_stop_location(_route_info->stops[ _current_stop ]->id)


    def do_ring(self, ) -> int:
            if ( sizeof( co() ) != 0 ) {
            add_succeeded_mess(({"You ring the bell.\n", "$N $V the "
            "bell.\n"}))
            if(objectp(_car_driver) && environment(_car_driver) == self) {
            _car_driver.bell_ring(_n_name)
            } else {
            tell_room(self, "Nothing much happens.\n")


    def query_environ_long(self, ) -> str:
            if ( !_outside ) {
            return "Outside the carriage, the road from " + _p_name + " to "
            + _n_name + " swishes by."
            } else {
            return "Outside the window you can see:\n" + _outside.long()



class Carriage(MudObject):

    _bell = 'clone_object("/std/object")'
