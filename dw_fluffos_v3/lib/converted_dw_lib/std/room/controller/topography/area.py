# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/controller/topography/area.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_handler(self, handler: str) -> None:
            _handler = handler


    def query_handler(self, ) -> str:
            return _handler


    def __init__(self):


    def __init__(self):


    def set_size(self, i: int, s: Any) -> None:
            if (intp(s)) {
            areas[i]->size = [s, s, s]
            } else if (arrayp(s) && (sizeof(s) == 3)) {
            areas[i]->size = copy(s)
            } else {
            error("Illegal size; must be int or 3-element array.\n")


    def new_area(self, ) -> int:
            areas += [new(class AREA_INFO)]


    def set_vertices(self, a: int, vs: Any) -> None:
            int v, i
            if (!arrayp(areas[a]->origin)) {
            error("Origin unset - setting to (0,0,0).\n")
            areas[a]->origin = [0, 0, 0]


    def in_bbox(self, coord: int, bbox: Any) -> int:
            if ((coord[0] < bbox[0][0]) || (coord[0] > bbox[1][0])) {
            return 0


    def in_area(self, a: int, v: int) -> int:
            int crossings, i, i0, i1, de, int_n, below_vertex
            mixed *vs
            if (!in_bbox(v, areas[a]->bbox)) {
            return 0


    def clone_room(self, a: int, coord_q: int, coord_s: str) -> MudObject:
            int i, j, e, bit
            string dir
            object room
            room = clone_object(areas[a]->base)
            room_cache[coord_s] = room
            area_cache[coord_s] = a
            room.set_room_size(areas[a]->size)
            room.set_co_ord(coord_q)
            if (areas[a]->exits) {
            i = (areas[a]->origin[0] - coord_q[0])/(2*areas[a]->size[0])
            j = (coord_q[1] - areas[a]->origin[1])/(2*areas[a]->size[1])
            if ((i < areas[a]->exits->size[0]) && (j < areas[a]->exits->size[1])
            && (i >= 0) && (j >= 0)) {
            e = areas[a]->exits->image[i][j]
            foreach (dir, bit in direction_bits) {
            if (e & bit) {
            room.add_exit(dir, "", "path")


    def find_room_at_coord(self, coord: int) -> MudObject:
            int a, ac, *coord_q
            string coord_s
            object room
            coord_s = sprintf("%d:%d:%d", coord[0], coord[1], coord[2])
            if (objectp(room = room_cache[coord_s])) {
            return room


    def find_room_at_exit(self, r: MudObject, d: int, direc: str) -> MudObject:
            int a, ac, i, *coord, *coord_r, *coord_q
            string coord_s
            object room
            mixed size_r
            if (dbg_lvl > 0) {
            tell_creator(debugger, "%s::find_room_at_exit()\n"
            "  r: %O\n"
            "  d: %O\n"
            "  direc: %O\n",
            file_name(self), r, d, direc)


    def goto_room_at_coord(self, coord: int) -> int:
            return this_player()->move_with_look(find_room_at_coord(coord))


    def goto_room_at_exit(self, d: int, direc: str) -> int:
            return this_player()->move_with_look(find_room_at_exit(
            environment(this_player()), d, direc))


    def print_images(self, a: int) -> None:
            if (areas[a]->height) {
            printf("-------- Height:\n")
            IMAGE_HANDLER.print_image(areas[a]->height)


    def print_map(self, a: int) -> None:
            int s, e
            string l = ""
            class IMAGE_INFO exits
            if (areas[a]->exits) {
            exits = areas[a]->exits
            for (s = 0; s < exits->size[1]; s++) {
            for (e = 0; e < exits->size[0]; e++) {
            l += (exits->image[s][e] & 128)?"\\":" "
            l += (exits->image[s][e] & 1)  ?"|":" "
            l += (exits->image[s][e] & 2)  ?"/":" "



class Area(Room):
