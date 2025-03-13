# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/cont_medium.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.continuous = 0
            self.collective = 0
            self.weight_unit = ['1', '200']
            self.pile_name = "pile"
            self.amount = 1


    def set_name(self, word: str) -> None:
            ::set_name( word )
            if ( continuous )
            add_plural( word )


    def set_amount(self, number: int) -> None:
            if(environment() && continuous)
            environment()->add_volume(number - amount)
            amount = number
            if(continuous || collective)
            set_weight((amount * weight_unit[ 0 ] ) / weight_unit[ 1 ])


    def adjust_amount(self, number: int) -> None:
            if(environment() && continuous)
            environment()->add_volume(number)
            amount += number
            if(amount < 1) {
            no_join = 1
            move( "/room/rubbish" )
            return


    def set_continuous(self, ) -> None:
            collective = 0
            if (continuous) {
            return


    def reset_continuous(self, ) -> None:
            if (!continuous) {
            return


    def set_collective(self, ) -> None:
            collective = 1
            continuous = 0
            add_property( "determinate", "" )


    def reset_collective(self, ) -> None:
            collective = 0


    def set_medium_alias(self, word: str) -> None:
            medium_alias = word
            add_alias( medium_alias )


    def set_amount_types(self, map: Any) -> None:
            amount_types = map
            _sorted_amount_names = sort_array(m_indices( amount_types ),
            (: amount_types[$1][0] - amount_types[$2][0] :))


    def query_value(self, ) -> int:
            if (!floatp(value_scale) || !continuous) {
            if(collective)
            return (amount * ::query_value() )
            return ::query_value()


    def query_how_many(self, ) -> int:
            int biggest_amount
            int how_many
            string size
            string biggest_size
            if(!amount)
            return 0
            if(!m_sizeof(amount_types)) {
            if(collective)
            return amount
            return 0


    def amount_size_short(self, ) -> str:
            int biggest_amount
            int how_many
            string size
            string biggest_size
            string ret
            string biggest_plural
            if ( !amount || !sizeof( amount_types ) ||
            (query_property("determinate") == "some ") ) {
            if(collective)
            return query_num(amount, 20) + " "
            return ""


    def pile_size(self, ) -> str:
            int i
            if ( !sizeof( pile_types ) ) {
            return "a surreal "+ pile_name


    def short(self, dark: int) -> str:
            string ret
            ret = ::short( dark )
            if(!ret || ret == "something" || !collective)
            return(ret)
            if(amount == 1)
            return add_a(ret)
            return( query_num(amount, 9999 ) + " " + query_main_plural())


    def long(self, words: str, dark: int) -> str:
            int i
            string ret
            string *bits
            if(continuous)
            return replace( ::long( words, dark ),
            ["$amount_size$", amount_size(),
            "$pile_size$", pile_size()] )
            ret = replace( ::long( words, dark ), "$N", short( dark ) )
            if(collective && amount > 1) {
            ret = replace( ret, ",$", "$comma_dollar$" )
            ret = replace( ret, [",", " $spaced_comma$", ";", " $spaced_semi$",
            ":", " $spaced_colon$", ".", " $spaced_period$"] )
            ret = replace( ret, "$comma_dollar$", ",$")
            bits = explode(ret, " ")
            for(i = 0; i < sizeof(bits); i++) {
            switch( bits[ i ] ) {
            case "This":
            bits[i] = "These"
            break
            case "this":
            bits[i] = "these"
            break
            case "is":
            bits[i] = "are"
            break
            case "a":
            case "an":
            bits[i] = amount_size_short()
            bits[i] = bits[i][0..<2]
            break
            case "it":
            bits[i] = "they"
            break
            case "It":
            bits[i] = "They"
            break
            case "its":
            bits[i] = "their"
            break
            case "Its":
            bits[i] = "Their"
            break
            case "$a":
            case "$an":
            bits[i] = bits[i][1..]
            break
            default:
            if( bits[i][0..1] == "$V" ) {
            bits[i] = replace_string( bits[i], "$V", "" )
            bits[i] = explode( bits[i], "$" )[1]
            if( bits[i][0..1] == "$P" ) {
            bits[i] = replace_string( bits[i], "$P", "" )
            bits[i] = pluralize( bits[i] )
            if( bits[i][0..1] == "$A" ) {
            bits[i] = replace_string( bits[i], "$A", "" )
            bits[i] = pluralize( bits[i] )
            if(strsrch(bits[i], query_plural(dark)) == -1)
            bits[i] = replace(bits[i], short(dark), query_plural(dark))


    def query_long(self, words: str, dark: int) -> str:
            return long(words, dark)


    def new_collective(self, number: int) -> MudObject:
            object ob
            object place
            ob = make_medium_clone(number)
            adjust_amount(-number)
            ob.set_no_join()
            if(environment()) {
            place = (object)environment()->query_property( "medium dest" )
            if(!place)
            place = environment()
            ob.move(place)


    def merge_criteria(self, ob: MudObject) -> int:
            return medium_alias == ob.query_medium_alias()


    def merge(self, ) -> None:
            object *obs
            if(environment())
            obs = filter(all_inventory(environment()) - [self],
            "merge_criteria", self)
            if(sizeof(obs) && objectp(obs[0])) {
            no_join = 1
            move("/room/rubbish")
            obs[0]->adjust_amount(amount)


    def make_medium_clone(self, number: int) -> MudObject:
            object medium
            mapping map
            medium = clone_object( explode( file_name( self ), "#" )[ 0 ] )
            map = (mapping)self.query_dynamic_auto_load()
            medium.init_dynamic_arg( map )
            map = (mapping)self.query_static_auto_load()
            if ( map ) {
            medium.init_static_arg( map )


    def cont_query_parse_id(self, args: Any) -> MudObject:
            int i
            string *sizes
            object medium, place
            if ( args[ P_THING ] < 0 ) {
            args[ P_THING ]++
            if ( args[ P_THING ] ) {
            return 0


    def coll_query_parse_id(self, arr: Any) -> MudObject:
            string *bits
            if((arr[0] < 0)) {
            return 0


    def query_parse_id(self, args: Any) -> MudObject:
            if(continuous)
            return cont_query_parse_id(args)
            return coll_query_parse_id(args)


    def set_no_env_move(self, dest: MudObject) -> None:
            object place
            if ( file_name( environment() ) == "/room/rubbish" ) {
            return


    def no_env_move(self, dest: MudObject, place: MudObject) -> None:
            if ( environment() == place ) {
            move( dest )


    def dest_old_env(self, place: MudObject) -> None:
            if ( place ) {
            place.dest_me()


    def init_dynamic_arg(self, map: Any, object) -> None:
            if ( !mapp( map ) )
            return
            if ( map[ "::" ] )
            ::init_dynamic_arg( map[ "::" ])
            if ( map[ "amount" ] )
            set_amount( map[ "amount" ] )
            if ( !undefinedp( map[ "continuous" ] ) )
            if ( map[ "continuous" ] ) {
            set_continuous()
            } else {
            reset_continuous()


    def init_static_arg(self, map: Any) -> None:
            if ( !mapp( map ) )
            return
            if ( map[ "::" ] )
            ::init_static_arg( map[ "::" ] )
            if ( !undefinedp( map[ "medium_alias" ] ) )
            medium_alias = map[ "medium_alias" ]
            if ( pointerp( map[ "weight_unit" ] ) )
            weight_unit = map[ "weight_unit" ]
            if ( stringp( map[ "pile_name" ] ) )
            pile_name = map[ "pile_name" ]
            if ( mapp( map[ "amount_types" ] ) )
            set_amount_types(map[ "amount_types" ])
            if ( pointerp( map[ "pile_types" ] ) )
            pile_types = map[ "pile_types" ]
            if ( floatp( map[ "value_scale" ] ) )
            value_scale = map[ "value_scale" ]



class Cont_medium(MudObject):

    continuous = 0

    collective = 0

    weight_unit = "['1', '200']"

    pile_name = '"pile"'

    amount = 1
