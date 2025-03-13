# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/more_file.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_mark(self, s: str) -> int:
            int i
            if (!mark_name) {
            mark_name = [})
            mark_data = [})


    def next_page(self, str: str) -> None:
            int num, noargs, i, j, k, redraw
            string s1, *s3
            if (str == 0)
            str = ""
            if (sscanf(str, "%d%s", num, str) != 2)
            noargs = 1
            s1 = extract(str, 1)
            switch (str[0 .. 0]) {
            case "":
            case " ":
            topl += real_rows
            redraw = 1
            break
            case "f":
            if (noargs)
            num = 1
            topl += ROWS * num
            redraw = 1
            break
            case "q" :
            printf("OK.\n")
            return
            case "/":
            search_flag = 0
            j = topl + 4
            if (s1[0] == '!') {
            search_flag = 1
            s1 = extract(s1, 1)


    def more_file(self, str: str) -> int:
            filenames = expand_path(str)
            if (!sizeof(filenames)) {
            notify_fail("No matching files.\n")
            return 0



class More_file(MudObject):
