# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/controller/topography/interroom.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def abs(self, i: int) -> int:
            return (i<0)?-i:i


    def set_milestones(self, s: str) -> None:
            int i
            milestones = copy(s)
            if (milestones[0] == milestones[<1]) {
            closed = 1


    def set_milestone_coords(self, i: int, c: int) -> None:
            if (!arrayp(c) || (sizeof(c) != 3)) {
            return


    def set_bases(self, s: str) -> None:
            int i
            if (sizeof(s) != sizeof(iroom_info)) {
            error("Wrong number of bases (" + sizeof(s) + ") for given milestones (" +
            sizeof(milestones) + ").\n")
            return


    def set_sizes(self, s: Any) -> None:
            int i
            if (sizeof(s) != sizeof(iroom_info)) {
            error("Wrong number of sizes (" + sizeof(s) + ") for given milestones (" +
            sizeof(milestones) + ").\n")
            return


    def query_endpoint(self, i: int, j: int, dir: int) -> int:
            if ((dir && (j == sizeof(irooms[i])-1)) || (!dir && (j == 0))) {
            return 1


    def in_bbox(self, coord_a: int, bbox: Any) -> int:
            if ((coord_a[0] < bbox[0][0]) || (coord_a[0] > bbox[1][0])
            || (coord_a[1] < bbox[0][1]) || (coord_a[1] > bbox[1][1]))
            return 0
            return 1


    def number_of_irooms(self, i: int) -> int:
            int n
            mixed bbox
            class IROOM_INFO ir
            ir = iroom_info[i]
            bbox = ir->bbox
            if (ir->sgn_n == 0) {
            n = (bbox[1][1] - bbox[0][1])/(ir->size[1]*2)
            } else if (ir->sgn_e == 0) {
            n = (bbox[1][0] - bbox[0][0])/(ir->size[0]*2)
            } else {
            n = (bbox[1][1] - bbox[0][1])/(ir->size[1]*2)
            if (n != (bbox[1][0] - bbox[0][0])/(ir->size[0]*2)) {
            error("Interroom sizes don't match diagonal.\n")
            return 0


    def clone_iroom(self, i: int, idx: int, icoord: int) -> MudObject:
            object iroom
            iroom = clone_object(iroom_info[i]->base)
            iroom.set_room_size(iroom_info[i]->size)
            iroom.set_co_ord(icoord)
            iroom.set_milestone_index( [i, idx] )
            iroom.add_exit(iroom_info[i]->exits[0], milestones[i], "road")
            iroom.add_exit(iroom_info[i]->exits[1], milestones[i+1], "road")
            iroom.add_milestone_dir(iroom_info[i]->exits[0])
            iroom.add_milestone_dir(iroom_info[i]->exits[1])
            iroom.add_topo_exits_int()
            return iroom


    def setup_milestone(self, ms: MudObject) -> None:
            int *coord, i, j, idir
            string *dir
            if (undefinedp(i = milestone_idx[file_name(ms)])) {
            error("This room (" + file_name(ms) + ") is not a milestone.\n")
            return


    def find_room_at_index(self, i: int, idx: int) -> MudObject:
            int *icoord = [0, 0, 0]
            class IROOM_INFO ir
            if (dbg_lvl > 0) {
            tell_creator(debugger, "%s::find_room_at_index()\n"
            "  i: %O, idx: %O\n",
            file_name(self), i, idx)


    def query_region(self, coord: int, bbox: Any) -> int:
            int ret
            if (coord[0] < bbox[0][0]) {
            ret += 1
            } else if (coord[0] > bbox[1][0]) {
            ret += 2


    def find_room_at_crossing(self, coord_a: int, coord_b: int) -> MudObject:
            int i, a, b, c, d, dist2, ret_dist2
            float e, f, det
            int *isect
            object ret
            mixed bbox, road_a, road_b
            if (dbg_lvl > 0) {
            tell_creator(debugger, "%s::find_room_at_crossing()\n"
            "  coord_a: %O\n"
            "  coord_b: %O\n",
            file_name(self), coord_a, coord_b)


    def __init__(self):
            self.std_euid = "/secure/master"->creator_file(file_name(this_object()))


    def dest_me(self, ) -> None:
            if (stringp(save_file)) {
            unguarded( (: save_object, save_file :) )


    def goto_room_at_coord(self, coord: int) -> int:
            return this_player()->move_with_look(find_room_at_coord(coord))


    def goto_room_at_index(self, i: int, j: int) -> int:
            return this_player()->move_with_look(find_room_at_index(i, j))


    def goto_room_at_crossing(self, a: int, b: int) -> int:
            return this_player()->move_with_look(find_room_at_crossing(a, b))


    def recalc_milestones(self, idx: int, callouts: int, tp: MudObject) -> None:
            int *c
            string ms
            if (callouts > 10) {
            error(sprintf("Too many callouts in %s:recalc_iroom_info(%d, %d)\n",
            file_name(self), idx, callouts))
            return


    def clear_map_handler(self, ) -> None:
            int i
            string ms, directory, troom
            for (i = 0; i < sizeof(milestones); i++) {
            ms = milestones[i]
            directory = implode( explode( ms, "/" )[ 0..<2 ], "/" )
            troom = explode( ms, "/" )[ <1 ]
            if ( troom[ <2.. ] == ".c" ) {
            troom = troom[ 0..<3]


    def sanity_checks(self, ) -> int:
            int i, success = 1
            for (i = 0; i < sizeof(milestone_coords); i++) {
            if (sizeof(milestone_coords[i]) != 3) {
            printf("Milestone %d (%s) doesn't have proper coordinates: %O\n",
            i, milestones[i], milestone_coords[i])
            success = 0



class Interroom(Room):

    std_euid = '"/secure/master"->creator_file(file_name(this_object()))'
