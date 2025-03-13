# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/book_dir.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_book_language(self, lang: str) -> None:
            language = lang


    def set_book_dir(self, dir: str) -> None:
            int i, max
            set_no_pages(10)
            set_ignore_saved_pages(1)
            max = 10
            i = 1
            set_default_page_object("/obj/misc/nroff_paper")
            set_open_page (0)
            while (file_size(dir+i) > 0) {
            set_open_page(i)
            set_read_mess("$$" + dir + i + "$$" , language, 0)
            i++
            if (i >= max) {
            max += 10
            set_no_pages(max)



class Book_dir(MudObject):
