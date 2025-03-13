# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/mtf/mtf2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def calc_long(self, ypos: int, xpos: int) -> str:
            int x, y, sameroad
            class map_class data
            string *exits = [})
            string *junctions = [})
            string long_str
            mixed *nearby
            if(!classp(map[ypos][xpos]))
            return ""
            sameroad = 0
            for(y = -1; y < 2; y++) {
            if((y*2)+ypos < 0)
            continue
            if((y*2)+ypos >= sizeof(map))
            continue
            for(x = -1; x < 2; x++) {
            if((x*2)+xpos < 0)
            continue
            if((x*2)+xpos >= sizeof(map[(y*2)+ypos]))
            continue
            if(!x && !y)
            continue
            if(classp(map[(y*2)+ypos][(x*2)+xpos])) {
            data = map[(y*2)+ypos][(x*2)+xpos]
            if(map[y+ypos][x+xpos] == '+' &&
            map[ypos][xpos]->basename ==
            map[(y*2)+ypos][(x*2)+xpos]->basename) {
            sameroad++
            exits += [DIRECTIONS[y+1][x+1]]


    def write_this_file(self, fdir: str, ypos: int, xpos: int) -> int:
            class map_class room
            string str, tmp, exit
            mapping exits
            int i
            room = map[ypos][xpos]
            str = "#include \"path.h\";\n\n"
            str += "inherit " + room->inheritname + ";\n"
            str += "\n"
            str += "void setup() {\n"
            str += "  set_short(\"" + room->short + "\");\n"
            str += "  set_long(\"" + room->long + "\\n\");\n"
            str += "  set_light( 80 );\n"
            exits = room->exits
            foreach(exit in keys(exits)) {
            i = DIRECTIONS.index(exit) if exit in DIRECTIONS else -1
            if(i % 2 == 1 &&
            exits[DIRECTIONS[i-1]] &&
            exits[DIRECTIONS[(i+1) % sizeof(DIRECTIONS)]])
            str += sprintf("  add_exit(\"%s\", %s, \"secret\");\n",
            exit, exits[exit]->dest)
            else
            str += sprintf("  add_exit(\"%s\", %s, \"road\");\n",
            exit, exits[exit]->dest)


    def map_to_files(self, mapfile: str, fdir: str, keyfile: str) -> int:
            int tot
            string *file_tmp
            string pstr
            int x, y
            if(!mapfile || mapfile == "")
            return NO_MAP_FILE
            file_tmp = this_player()->get_files(mapfile)
            if(!file_tmp || sizeof(file_tmp) != 1 || file_size(file_tmp[0]) < 1)
            return NO_MAP_FILE
            else
            mapfile = file_tmp[0]
            if(!fdir || fdir == "")
            file_tmp = [this_player()->query_path()]
            else
            file_tmp = this_player()->get_files(fdir)
            if(!file_tmp || sizeof(file_tmp) != 1 || file_size(file_tmp[0]) != -2)
            return NO_FILE_DIR
            else
            fdir = file_tmp[0]
            if(!keyfile || keyfile == "" )
            keyfile = DEFAULT_KEYS
            file_tmp = this_player()->get_files(keyfile)
            if(sizeof(file_tmp) != 1 || file_size(file_tmp[0]) < 1)
            return NO_KEY_FILE
            else
            keyfile = file_tmp[0]
            key_data = read_keys(keyfile)
            map = read_map(mapfile)
            for(y = 0; y < sizeof(map); y++)
            for(x = 0; x < sizeof(map[ y ]); x++)
            if(classp(map[y][x])) {
            map[y][x]->exits = get_exits(y, x)



class Mtf2(MudObject):
