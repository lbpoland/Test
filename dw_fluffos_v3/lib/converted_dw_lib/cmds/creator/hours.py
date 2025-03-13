# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/hours.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, time: int, all: str) -> int:
            mapping people
            int seconds, num
            string mess
            if ( !time ) {
            if(all == "")
            people = unique_mapping( filter( users(),
            (: interactive( $1 ) && !$1.query_login_ob() &&
            !$1.query_creator() :) ),
            (: ( (time() - $1.query_last_log_on() ) / 3600 ) :) )
            else
            people = unique_mapping( filter( users(),
            (: interactive( $1 ) && !$1.query_login_ob() :) ),
            (: ( (time() - $1.query_last_log_on() ) / 3600 ) :) )
            people = map( people, (: sort_array( $2, (: strcmp( $1.query_name(),
            $2.query_name() ) :) ) :) )
            mess = ""
            foreach( num in sort_array( keys( people ), -1 ) ) {
            if ( num > 0 ) {
            mess += "Online for " + query_num( num ) +
            ( num == 1 ? " hour: \n" : " hours: \n" ) +
            query_multiple_short( people[ num ] ) + ".\n\n"



class Hours(MudObject):
