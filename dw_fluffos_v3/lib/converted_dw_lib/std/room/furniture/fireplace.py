# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/fireplace.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):
            self.add_extra_look( self )
            add_help_file("fireplace")


    def init(self, ) -> None:
            this_player()->add_command("light", self, "<direct:object> with <indirect:object>")
            this_player()->add_command("extinguish", self, "<direct:object>", (: do_dowse :) )
            this_player()->add_command("dowse", self, "<direct:object>")
            if( this_player()->query_class_ob() == WIZARD ){
            this_player()->add_command("zap", self, "<direct:object>")
            this_player()->add_command("point", self, "[finger] at <direct:object>", (: do_zap :) )


    def do_light(self, obs: MudObject) -> int:
            string q_n
            q_n = obs[0]->query_name()
            if( _is_lit ){
            this_player()->add_failed_mess( self,
            "$D is already ablaze.\n", [}) )
            return 0


    def do_zap(self, ) -> int:
            object tp
            tp = this_player()
            if(tp.query_gp() < 10){
            await tp.send("You don't even have the energy for such a small task!\n")
            return 1


    def msg_on(self, ) -> None:
            if(_is_lit){
            tell_room(environment( self ), query_turn_on_mess() )


    def turn_on(self, ) -> int:
            int x
            FUEL_HANDLER.add_burner( self )
            _is_lit = 1
            adjust_light( query_light_produced() )
            x = query_light_produced() / 4
            add_property("degrees", query_light_produced() * 4)
            environment( self )->add_property("warmth", x )
            asyncio.create_task(self. "msg_on", 7 )
            return 1


    def do_dowse(self, obs: MudObject) -> int:
            if( !_is_lit ){
            this_player()->add_failed_mess( self,
            "There is no fire to put out.\n", [}) )
            return 0
            } else {
            this_player()->add_succeeded_mess(self,
            "$N $V $D and the room loses its warm glow.\n", [}) )
            return turn_off()


    def msg_off(self, ) -> None:
            if(!_is_lit){
            tell_room(environment( self ), query_turn_off_mess() )


    def turn_off(self, ) -> int:
            FUEL_HANDLER.remove_burner( self )
            _is_lit = 0
            adjust_light( -query_light_produced() )
            add_property( "degrees", 0 )
            environment( self )->remove_property("warmth")
            asyncio.create_task(self. "msg_off", 10 )
            return 1


    def out_of_fuel(self, ) -> None:
            turn_off()
            tell_room(environment( self ), query_out_of_fuel_mess() )


    def add_lit_chat(self, str: str) -> None:
            if( !_lit_chats ){
            _lit_chats = [})


    def request_lit_chat(self, ) -> str:
            return _lit_chats[random( sizeof(_lit_chats) - 1 )]


    def add_dying_chat(self, str: str) -> None:
            if( !_dying_chats ){
            _dying_chats = [})


    def request_dying_chat(self, ) -> str:
            return _dying_chats[random( sizeof(_dying_chats) - 1 )]


    def consume_fuel(self, ) -> None:
            int x
            int q
            int z
            int w
            int amount
            string r
            object *inv
            object ashes
            object thing
            object env
            inv = filter(all_inventory( self ),
            (:$1.query_property("fuel") :))
            if( !inv || inv == [}) || calc_fuel() < 1){
            out_of_fuel()
            return


    def calc_fuel(self, ) -> int:
            object *inv
            object thing
            int tot_fuel = 0
            int w
            int amt
            inv = all_inventory( self )
            if( !inv || inv == [}) ) { return 0; }
            foreach(thing in inv){
            if( thing.query_property("fuel") ){
            w =  thing.query_weight()
            amt = thing.query_amount_left()
            tot_fuel += w * amt * K / 100


    def test_remove(self, thing: MudObject, flat: int, dest: Any) -> int:
            object tp
            object *prev
            tp = this_player()
            prev = previous_object(-1)
            if(_is_lit && tp && strsrch( file_name(prev[1]), CMD ) != -1 ){
            tell_object(tp, "You reach out towards the fire but "
            "you can't brave the flames and quickly pull away.\n")
            tell_room( environment(tp), tp.query_short() + " tries to take something "
            "from the fire but pulls back sucking " + tp.query_possessive() +
            " fingers.\n", tp)
            tp.adjust_hp( -random(120) )
            return 0


    def test_add(self, thing: MudObject, flag: int) -> int:
            if( !thing.query_property("fuel") && environment(thing) ){
            await this_player().send("You don't think " + thing.the_short() +
            " would be a suitable fuel.\n")
            return 0


    def extra_look(self, ob: MudObject) -> str:
            if( _is_lit ) {
            return query_lit_mess()


    def pre_dest_me(self, ) -> None:
            int tmp
            if(_is_lit && environment()) {
            FUEL_HANDLER.remove_burner( self )
            _is_lit = 0
            adjust_light( -query_light_produced() )
            tmp = environment()->query_property("warmth")
            if(tmp > query_light_produced() / 4)
            environment()->add_property("warmth", tmp -
            (query_light_produced() / 4))
            else
            environment()->remove_property("warmth")


    def dest_me(self, ) -> None:
            FUEL_HANDLER.remove_burner( self )
            _is_lit = 0
            ::dest_me()



class Fireplace(MudObject):
