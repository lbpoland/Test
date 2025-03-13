# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/map_helper.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def save_dir(self, ) -> None:
            #ifdef HELPLOGTO
            await  find_living( LOGTO ).send("%^RED%^saving%^RESET%^ "+ loaded +"\n")
            #endif
            if (sizeof(shorts) ||
            sizeof(movezones) ||
            sizeof(changetimes) ||
            #ifdef COORDS
            sizeof(coords) ||
            sizeof(sizes) ||
            #endif
            #if !efun_defined(db_exec)
            sizeof(clusters) ||
            sizeof(map) ||
            #endif
            0) {
            unguarded((: save_object, "/save/map/" + loaded :))
            } else {
            unguarded((: rm("/save/map/" + loaded) :))


    def check_dir(self, dir: str) -> None:
            string tmp_file
            if ( dir == directory ) {
            return


    def change_map(self, dir: str, room: str, dd: str) -> None:
            check_dir( dir )
            map[ room ] = dd
            save = 1


    def change_shorts(self, dir: str, room: str, sh: str) -> None:
            check_dir( dir )
            shorts[ room ] = sh
            save = 1


    def change_movezones(self, dir: str, room: str, zones: str) -> None:
            check_dir( dir )
            movezones[ room ] = zones
            save = 1


    def change_clusters(self, dir: str, room: str, cluster: int) -> None:
            check_dir( dir )
            if(!clusters)
            clusters = ([])
            clusters[ room ] = cluster
            save = 1


    def change_changetimes(self, dir: str, room: str, time: int) -> None:
            check_dir( dir )
            if ( !changetimes )
            changetimes = ([ ])
            changetimes[ room ] = time
            save = 1


    def change_co_ords(self, dir: str, room: str, coord: int) -> None:
            check_dir( dir )
            if ( !coords )
            coords = ([ ])
            coords[ room ] = coord
            save = 1


    def change_sizes(self, dir: str, room: str, size: int) -> None:
            check_dir( dir )
            if ( !sizes )
            sizes = ([ ])
            sizes[ room ] = size
            save = 1


    def del(self, dir: str, room: str) -> None:
            check_dir( dir )
            #if !efun_defined(db_exec)
            if (mapp(map)) {
            map_delete( map, room )
            } else {
            map = ([ ])



class Map_helper(MudObject):
