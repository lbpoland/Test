# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/basic/door.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.name = ['door']
            self.lng = "It's just a door.\n"
            self.shrt = "door"
            self.adjs = []
            self.plu = []


    def query_how_many(self, ) -> int:
            return how_many


    def set_how_many(self, number: int) -> None:
            if(number)
            add_property("party object", 1)
            else
            remove_property("party object")
            how_many = number


    def query_one_way(self, ) -> int:
            return one_way


    def set_one_way(self, number: int) -> None:
            one_way = number


    def query_short(self, ) -> str:
            return shrt


    def set_short(self, words: str) -> None:
            string *bits
            shrt = words
            bits = explode( words, " " )
            bits += implode( map( bits, (: explode( $1, "-" ) :) ), (: $1 + $2 :) )
            bits = uniq_array( bits )
            name += [bits[ sizeof( bits ) - 1 ]]
            adjs += bits[ 0 .. sizeof( bits ) - 2 ]
            plu += [pluralize( bits[ sizeof( bits ) - 1 ] )]


    def query_door_name(self, ) -> str:
            return _door_name


    def set_door_name(self, word: str) -> None:
            _door_name = word


    def set_lock_owner(self, owner: str) -> None:
            _lock_owner = owner


    def query_lock_owner(self, ) -> Any:
            return _lock_owner


    def init(self, ) -> None:
            add_command( "knock", "on <direct:object>" )
            close_lock::init()


    def long(self, ) -> str:
            return lng + ( ( this_player()->query_see_octarine() ) ? enchant_string() :
            "" ) + long_status()


    def get(self, ) -> int:
            void setup_door( string word, object mine, string his, mixed *args,
            string type) {
            string *bits
            my_id = word
            my_room = mine
            dest = his
            switch(type) {
            case "window":
            if(word != "window")
            shrt = word + " window"
            else
            shrt = word
            lng = "It's just the " + shrt + ".\n"
            name = [shrt, "window"]
            plu = ["windows"]
            break
            default:
            if ( word[ 0 .. 5 ] == "enter " ) {
            if(SHORTEN[word[6..100]])
            name += [SHORTEN[word[6..100]]]
            shrt = word[ 6 .. 100 ] +" door"
            lng = "It's just the " + shrt + ".\n"
            name += [shrt]
            if(!args[D_SECRET ])
            plu = ["doors"]
            } else {
            if(SHORTEN[word])
            name += [SHORTEN[word]]
            shrt = word +" door"
            lng = "It's just the " + shrt + ".\n"
            name += [shrt]
            if(!args[D_SECRET ])
            plu = ["doors"]


    def add_alias(self, word: str) -> None:
            string *bits
            bits = explode( word, " " )
            name += [bits[ sizeof( bits ) - 1 ]]
            adjs +=  bits[ 0 .. sizeof( bits ) - 2 ]
            plu += [pluralize( bits[ sizeof( bits ) - 1 ] )]


    def force_other(self, ) -> int:
            string door_name, direc
            if(!find_object(dest)) {
            if(!load_object(dest))
            return 0
            dest.query_door( my_room, _door_name )


    def do_open(self, ) -> int:
            if(!::do_open())
            return 0
            if(!force_other() && !one_way) {
            set_closed()
            return 0


    def do_close(self, ) -> int:
            if(!::do_close())
            return 0
            if(!force_other() && !one_way) {
            set_open()
            return 0


    def do_lock(self, obs: MudObject) -> int:
            if(!::do_lock(obs))
            return 0
            if(!force_other() && !one_way) {
            set_unlocked()
            return 0


    def do_unlock(self, obs: MudObject) -> int:
            if(!::do_unlock(obs))
            return 0
            if(!force_other() && !one_way) {
            set_locked()
            return 0


    def do_knock(self, ) -> int:
            if(this_player()->query_property("dead"))
            return 0
            if ( !other_id && !one_way ) {
            ROOM_HANDLER.check_door( [my_room, my_id] )
            if ( !other_id )
            return 0


    def pick_unlock(self, thing: MudObject) -> int:
            if (stringp(_lock_owner)) {
            if (pk_check(_lock_owner, thing, 1)) {
            return 0


    def pick_lock(self, thing: MudObject) -> int:
            if (stringp(_lock_owner)) {
            if (pk_check(_lock_owner, thing, 1)) {
            return 0


    def query_parse_id(self, arr: Any) -> MudObject:
            if (arr[P_THING] == 0) {
            return self


    def dest_me(self, ) -> None:
            destruct( self )


    def moving_open(self, thing: MudObject) -> int:
            if(!::do_open())
            return 0
            if(!force_other() && !one_way) {
            set_closed()
            return 0


    def moving_close(self, thing: MudObject) -> int:
            if(!::do_close())
            return 0
            if(!force_other() && !one_way) {
            set_open()
            return 0


    def moving_unlock(self, thing: MudObject) -> int:
            if(!::do_unlock(all_inventory(thing)))
            return 0
            if(!one_way && find_object(dest))
            dest.modify_exit(other_id, ["locked", 0])
            await thing.send("You unlock the "+ shrt +".\n")
            if (thing.short())
            tell_room( my_room, capitalize( (string)thing.the_short() ) +
            " unlocks the "+ shrt +".\n", thing )
            return 1


    def moving_lock(self, thing: MudObject) -> int:
            if(!::do_lock(all_inventory(thing)))
            return 0
            if(!one_way && find_object(dest))
            dest.modify_exit(other_id, ["locked", 1])
            tell_object( thing, "You lock the "+
            (string)dest.call_door( other_id, "query_short" ) +".\n" )
            if (thing.short())
            dest.tell_door( other_id, capitalize( (string)thing.the_short() ) +
            " locks the $D.\n", thing )
            return 1


    def tell_door(self, words: str, thing: MudObject) -> None:
            tell_room(my_room, replace( words, ({
            "$D", shrt, "$p", PRONOUN[how_many], "$s", ["s", ""][how_many]]),
            [thing])


    def long_status(self, ) -> str:
            string str
            if (!query_stuck()) {
            if(query_how_many() > 0)
            {
            str = "They are"



class Door(MudObject):

    name = "['door']"

    lng = '"It\'s just a door.\\n"'

    shrt = '"door"'

    adjs = '[]'

    plu = '[]'
