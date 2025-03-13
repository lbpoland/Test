# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/soul_compiler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._to_compile = []


    def test_security(self, fname: str) -> int:
            return 1


    def notify(self, mess: str) -> None:
            if (_current_player)
            await _current_player.send(mess)


    def compile_file(self, fname: str) -> None:
            if (file_size(SOUL_DIR+fname) == -1) {
            tell_object(this_player(), "The file "+
            SOUL_DIR+fname+" does not exist.\n")
            return


    def compile_directory(self, fname: str) -> None:
            string *bits, start
            int i
            if (file_size(SOUL_DIR+fname) != -2) {
            tell_object(this_player(), "The file "+
            fname+" is not a directory exist.\n")
            return


    def start_compile(self, ) -> None:
            if ((_current_file || !sizeof(_to_compile)) &&
            (time() - _last_chunk_compile) > 10) {
            return


    def compile_chunk(self, ) -> None:
            string chunk
            int end
            _last_chunk_compile = time()
            if (_current_line+CHUNK_SIZE > _file_len) {
            end = _file_len+1
            } else {
            end = _current_line+CHUNK_SIZE


    def parse_chunk(self, chunk: str) -> None:
            string *bits, s1, s2
            int pos, chunk_size, start
            chunk_size = strlen(chunk)
            pos = 0
            bits = explode(chunk, "(")
            while (pos < chunk_size) {
            switch (_look_for) {
            case OPEN_BRACKET :
            if (sscanf(chunk[pos..], "%s(%s", s1, s2)) {
            chunk = s2
            chunk_size = strlen(chunk)
            pos = 0
            _depth++
            _arguments += [0, 0]
            _look_for = ARGUMENT_NAME
            } else {
            pos = chunk_size


    def check_sort(self, pat1: str, pat2: str) -> int:
            int lvl1, lvl2
            lvl1 = ((mixed *)PATTERN_OB.compile_pattern(pat1))[0]
            lvl2 = ((mixed *)PATTERN_OB.compile_pattern(pat2))[0]
            return lvl2-lvl1


    def make_into_soul_commands(self, comms: Any) -> None:
            string *fluff
            int i, failed, j
            mapping ret, tmp
            fluff = keys(comms)
            ret = ([ ])
            for (i=0;i<sizeof(fluff);i++) {
            ret[fluff[i]] = [comms[fluff[i]]["pattern"], 0, 0]
            if (comms[fluff[i]]["single"]) {
            if (comms[fluff[i]]["single"][0]["no-arguments"]) {
            tmp = comms[fluff[i]]["single"][0]["no-arguments"][0]
            if (!tmp["self"]) {
            notify("The 'self' type is missing in the no-argument, single for the soul command "+fluff[i]+"\n")
            failed = 1
            } else if (!tmp["rest"]) {
            notify("The 'rest' type is missing in the no-argument, single for the soul command "+fluff[i]+"\n")
            failed = 1
            } else {
            ret[fluff[i]][SINGLE] = [[tmp["self"], tmp["rest"],
            tmp["position"]],
            0]


    def blue(self, ) -> None:
            printf("%O\n", sort_patterns(["[at] <indirect:object>", "<string>"]))



class Soul_compiler(MudObject):

    _to_compile = '[]'
