# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/sqlcmd.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, db: str, query: str) -> int:
            DB_HANDLER->make_sql_request( db, CONFIG_DB_USER, "", query,
            (: set_results( $1, $2, $(this_player()) ) :) )
            return 1


    def set_results(self, flag: int, res: Any, who: MudObject) -> None:
            tell_creator( who, "flag: %O\n%O\n", flag, res )
            results = res


    def query_patterns(self, ) -> Any:
            return ({
            "<word'db'> <string:quoted'query'>",
            (: cmd( $4[0], $4[1] ) :)]



class Sqlcmd(MudObject):
