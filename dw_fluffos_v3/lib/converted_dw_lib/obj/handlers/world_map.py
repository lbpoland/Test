# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/world_map.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._regions = allocate(REGION_WIDTH, (: allocate(REGION_WIDTH) :))


    def __init__(self):
            self._regions = allocate(REGION_WIDTH, (: allocate(REGION_WIDTH) :))
            private void generate_main_templates() {
            int size
            mixed* last
            int x
            int y
            int u
            int v
            int e
            int i
            _templates = allocate(12)
            last = [[1]]
            for (size = 0; size < sizeof(_templates); size++) {
            for (i = 0; i < sizeof(last); i++) {
            last[i] = [0] + last[i] + [0]


    def load_region(self, x: int, y: int) -> None:
            class region region
            string fname
            if (_regions[x][y]) {
            _regions[x][y]->last_touched = time()
            return


    def save_region(self, x: int, y: int) -> None:
            string fname
            class region region
            if (_regions[x][y]) {
            region = _regions[x][y]
            fname = SAVE_DIR + "region_" + x + "_" + y
            unguarded( (: write_file($(fname), save_variable($(region)), 1) :))


    def add_terrain(self, path: str, x1: int, y1: int, x2: int, y2: int) -> int:
            int tmp
            int region_x
            int region_y
            if (x1 > x2) {
            tmp = x1
            x1 = x2
            x2 = tmp


    def find_terrain_at(self, x: int, y: int) -> str:
            int region_x
            int region_y
            x = ((x + OFFSET) / BOUNDARY)
            y = ((y + OFFSET) / BOUNDARY)
            region_x = x / REGION_SIZE
            region_y = y / REGION_SIZE
            load_region(region_x, region_y)
            return _regions[region_x][region_y]->terrains[x % REGION_SIZE][y % REGION_SIZE]


    def find_room_at(self, x: int, y: int) -> str:
            string path
            path = find_terrain_at(x, y)
            if (path) {
            return path.find_room_at_real_coord(x, y)


    def add_feature(self, feature: str) -> None:
            int x
            int y
            for (x = 0; x < REGION_WIDTH; x++) {
            for (y = 0; y < REGION_WIDTH; y++) {
            if (feature->is_inside_region(
            (x * REGION_WIDTH) * BOUNDARY - OFFSET,
            (y * REGION_WIDTH) * BOUNDARY - OFFSET,
            ((x + 1) * REGION_WIDTH) * BOUNDARY - OFFSET,
            ((y + 1) * REGION_WIDTH) * BOUNDARY - OFFSET)) {
            load_region(x, y)
            _regions[x][y]->features |= [feature]
            save_region(x, y)
            debug_printf("Added feature to region %d, %d\n", x, y)


    def remove_feature(self, feature: str) -> None:
            int x
            int y
            for (x = 0; x < REGION_WIDTH; x++) {
            for (y = 0; y < REGION_WIDTH; y++) {
            load_region(x, y)
            if (_regions[x][y]->features.index(feature) if feature in _regions[x][y]->features else -1 != -1) {
            _regions[x][y]->features -= [feature]
            save_region(x, y)



class World_map(MudObject):

    _regions = 'allocate(REGION_WIDTH, (: allocate(REGION_WIDTH) :))'
