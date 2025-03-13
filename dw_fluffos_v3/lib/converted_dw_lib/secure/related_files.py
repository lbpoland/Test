# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/related_files.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def delete_related_files(self, name: str, mail: int, refresh_type: int) -> None:
            string *files
            string area
            string dir
            if (previous_object() != find_object("/secure/bulk_delete") &&
            previous_object() != find_object("/secure/delete_clear") &&
            previous_object() != find_object("/obj/handlers/refresh")) {
            if (!master()->high_programmer(previous_object(-1)) &&
            ((string)previous_object()->query_name() != name)) {
            tell_object(find_player("ceres"), "Not doing erasing. %O\n",
            previous_object())
            unguarded( (: write_file, "/log/CHEAT", ctime( time() ) +
            ": illegal attempt to delete related files using "+
            "/secure/related_files\nTrace: "+ back_trace() :) )
            return



class Related_files(MudObject):
