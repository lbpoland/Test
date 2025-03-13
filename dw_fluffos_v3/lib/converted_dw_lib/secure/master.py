# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.permissions = ([ ])
            self.positions = ([ ])
            self.checked_master = ([ ])
            self.snoop_list = ([ ])
            self.unguarded_ob = 0
            self.trustees = TRUSTEES


    def connect(self, port: int) -> MudObject:
            object ob
            if (!find_object("/secure/login")) {
            log_file("REBOOT", "Mud rebooted at "+ctime(time())+"["+time()+"]"+"\n")


    def query_trustee(self, str: Any) -> int:
            if (pointerp(str)) {
            str = filter(str, (: interactive($1) :))
            return sizeof(filter((object *)str,
            (: geteuid($1) == ROOT ||
            positions[geteuid($1)] == TRUSTEE ||
            trustees[geteuid($1)] :))) == sizeof(str)


    def query_administrator(self, str: Any) -> int:
            return query_trustee(str)


    def high_programmer(self, str: Any) -> int:
            return query_trustee(str)


    def query_director(self, arg: Any) -> int:
            if ( pointerp( arg ) ) {
            arg = filter(arg, (: interactive($1) :))
            return sizeof( filter( (object *)arg,
            (: ( positions[ geteuid( $1 ) ] == DIRECTOR ) ||
            query_trustee( geteuid( $1 ) ) :) ) ) == sizeof( arg )


    def query_only_director(self, word: str) -> int:
            return positions[ word ] == DIRECTOR


    def query_only_lord(self, word: str) -> int:
            string *query_directors() {
            return filter_array(keys(positions),
            "query_only_director", self)


    def query_player_trustee(self, str: str) -> int:
            return query_trustee(str) && PLAYER_HANDLER.test_user(str)


    def query_player_administrator(self, str: str) -> int:
            return query_player_trustee(str)


    def query_player_high_lord(self, str: str) -> int:
            return query_player_trustee(str)


    def is_leader_of(self, person: str, domain: str) -> int:
            return ("/d/" + domain + "/master")->query_lord() == person


    def is_deputy_of(self, person: str, domain: str) -> int:
            return ("/d/" + domain + "/master")->query_deputy(person)


    def is_liaison_deputy(self, person: str) -> int:
            return "/d/liaison/master"->query_deputy(person)


    def query_liaison_deputy_or_director(self, arg: Any) -> int:
            if ( pointerp( arg ) ) {
            arg = filter(arg, (: interactive($1) :))
            return sizeof( filter( (object *)arg,
            (: query_director(geteuid( $1 )) ||
            is_liaison_deputy( geteuid( $1 ) ) :) ) ) == sizeof( arg )


    def query_liaison_deputy_or_lord(self, arg: Any) -> int:
            return query_liaison_deputy_or_director(arg)


    def query_senior(self, arg: Any) -> int:
            if ( pointerp( arg ) )
            return sizeof(filter( (object *)arg,
            (: ( positions[ geteuid( $1 ) ] == SENIOR ) ||
            query_leader( geteuid( $1 ) ) :) ) ) == sizeof( arg )
            return ( ( positions[ arg ] == SENIOR ) || query_leader( arg ) )


    def get_bb_uid(self, ) -> str:
            string *define_include_dirs() {
            return ["/include/%s"]


    def shut(self, min: int) -> None:
            "/obj/shut"->shut(min)


    def remove_checked_master(self, name: str) -> None:
            map_delete(checked_master, name)



class Master(MudObject):

    permissions = '([ ])'

    positions = '([ ])'

    checked_master = '([ ])'

    snoop_list = '([ ])'

    unguarded_ob = 0

    trustees = 'TRUSTEES'
