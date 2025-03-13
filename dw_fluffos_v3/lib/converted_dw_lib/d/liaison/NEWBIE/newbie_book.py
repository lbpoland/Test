# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/newbie_book.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "book" )
            set_short( "newbie guide book")
            set_main_plural( "newbie guide books" )
            add_adjective( ({"newbie", "guide"}) )
            add_alias( "newbiebook" )
            set_weight( 2 )
            set_value( 0 )
            set_long( "This is a guide book for the newbies who rushed through the "
            "newbie foyer too fast or are just absent-minded in general.  "
            "It contains valuable information on the commands, classs "
            "and the city of Waterdeep.\n\n"
            "You may 'open book', 'read newbie book', 'turn page of "
            "newbie book' or 'open newbie book to page #'.\n" )
            set_book_language( "general" )
            set_book_dir( NEWBIE_SAVE + "newbie_book_page" )
            set_read_mess("\n"
            "                          _______   nn   _______                      \n"
            "                          \\____ _\\ [@@] / _____/                       \n"
            "                             \\__ _\\/\\/\\/ ___/                        \n"
            "                               \\__| [] |__/                            \n"
            "                  ___              \\__/              ___             \n"
            "                 / ..\\             /__\\             /.. \\          \n"
            "               _/ \\___\\            (())            /___/ \\_        \n"
            "             _/@  /V /V   _________=||=________    V\\ V\\  @\\_      \n"
            "             \\   |_n_n    \\         ||        /     n_n_|   /          \n"
            "              |   ____|    |                 |     |____   |           \n"
            "              |-----|_____ |       The       | _____|------|           \n"
            "             / __    \\ ___)|      NEWBIE     |(___ /     __ \\          \n"
            "            | /  \\___ |    |    Guide book   |    | ____/  \\ |         \n"
            "            | \\______)|    |      f o r      |    |(_______/ |         \n"
            "            |         |    |    Faerûnworld    |    |          |         \n"
            "            |        /      \\    Mudders    /      \\         |         \n"
            "             \\   _  /        \\_           _/        \\   _   /         \n"
            "              | | | |          \\_       _/           | | | |           \n"
            "              |_| |_|            \\_____/             |_| |_|           \n"
            "       ____________________________________________________________     \n"
            "   ___|  Syntaxes: 'open book' 'read book' 'turn a page of book'   |___  \n"
            "   \\  |____________        'open book to page #'       ____________|  /  \n"
            "   /____/          \\__________________________________/          \\____\\ ",
            "general")



class Newbie_book(MudObject):
