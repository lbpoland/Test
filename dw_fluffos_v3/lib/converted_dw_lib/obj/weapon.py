# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapon.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.un_modifyable = []


    def short(self, dark: int) -> str:
            string str
            str = ""
            return ::short(dark)+str


    def set_wield_func(self, func: str, ob: Any) -> None:
            if (!func) {
            wield_func = 0
            } else {
            wield_func = [func, ob]


    def long(self, s: str, dark: int) -> str:
            return ::long(s, dark)+cond_string()


    def new_weapon(self, new_condition: int) -> None:
            set_cond( new_condition )
            set_max_cond( new_condition )
            set_lowest_cond( new_condition )


    def held_this_item(self, held: int, holder: MudObject, arg: Any) -> int:
            int weight
            object weapon
            if(held == 1 && interactive(holder)) {
            weight = self.query_weight()
            foreach(weapon in holder.query_weapons())
            weight += weapon.query_weight()
            weight -= holder.query_str()
            switch(weight) {
            case 76..10000:
            tell_object(holder, "You struggle to hold " +
            query_multiple_short(holder.query_holding() +
            [self] - [0]) +
            ".\n")
            break
            case 50..75:
            tell_object(holder, "You struggle slightly to hold " +
            query_multiple_short(holder.query_holding() +
            [self] - [0]) +
            ".\n")
            break
            default:


    def dest_me(self, ) -> None:
            holdable::dest_me()
            object::dest_me()


    def modify_damage(self, val: int, name: str) -> int:
            int tmp
            tmp = val + (val * query_enchant()) /
            (query_max_enchant() + query_enchant())
            if(un_modifyable.index(name) if name in un_modifyable else -1 != -1)
            return tmp
            tmp = ( tmp * query_cond() ) / query_max_cond()
            if(tmp < val / 10)
            return val / 10
            return tmp


    def hit_weapon(self, amount: int, type: str) -> None:
            if ( un_modifyable.index( type) if  type in un_modifyable else -1 != -1 )
            return
            do_damage( type, amount )


    def add_immune(self, name: str) -> int:
            if (un_modifyable.index(name) if name in un_modifyable else -1 != -1)
            return 0
            un_modifyable += [name]
            return 1


    def remove_immune(self, name: str) -> int:
            int i
            if ((i = un_modifyable.index(name) if name in un_modifyable else -1) == -1)
            return 0
            un_modifyable = delete(un_modifyable, i, 1)
            return 1


    def query_value(self, ) -> int:
            return ( ::query_value() * ( 10 + ( 90 * query_cond() ) /
            query_max_cond() ) ) / 100


    def query_full_value(self, {: Any) -> int:
            mixed *query_money_array() {
            return (mixed *)MONEY_HAND.create_money_array(query_value())


    def query_money(self, type: str) -> int:
            int i
            mixed *m_a
            m_a = (mixed *)MONEY_HAND.create_money_array(query_value())
            if ((i=m_a.index(type) if type in m_a else -1) == -1)
            return 0
            return m_a[i+1]


    def break_me(self, ) -> None:
            if ( query_holder() ) {
            await  query_holder().send("%^RED%^$C$"+ the_short() +" shatters under Mystra’s gaze!%^RESET%^\n" )
            tell_room( environment( query_holder() ), poss_short() +
            " shatters under Mystra’s gaze!\n", query_holder() )
            query_holder()->set_unhold( self )


    def player_wield(self, pos: int) -> None:
            if (!environment()) {
            return


    def init_static_arg(self, map: Any) -> None:
            if ( !mapp( map ) ) return
            if ( map[ "::" ] ) {
            object::init_static_arg( map[ "::" ] )


    def replace_me(self, ) -> None:
            object receipt
            receipt = clone_object( "/std/object" )
            receipt.set_name( "receipt" )
            receipt.set_short( "destructed item receipt" )
            receipt.add_adjective( ["destructed", "item"] )
            receipt.set_long( "This seems to be a small piece of paper.\n" )
            receipt.set_read_mess( "According to our sources, your "+query_short()+" was not "
            "allowed to exist.  Have a nice day." )
            receipt.move( environment() )
            receipt.set_weight( 1 )
            destruct( self )


    def init_dynamic_arg(self, map: Any, object) -> None:
            mapping stat_temp
            string virt_name, new_name
            if ( map[ "::" ] )
            object::init_dynamic_arg( map[ "::" ] )
            if ( !undefinedp( map[ "condition" ] ) ) {
            condition::init_dynamic_arg( map[ "condition" ] )



class Weapon(MudObject):

    un_modifyable = '[]'
