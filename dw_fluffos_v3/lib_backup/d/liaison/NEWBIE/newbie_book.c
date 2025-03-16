#include "path.h"
#define NEWBIE_SAVE "/d/liaison/NEWBIE/save/"
inherit "/std/book_dir";
void setup() {
  set_name( "book" );
  set_short( "newbie guide book");
  set_main_plural( "newbie guide books" );
  add_adjective( ({"newbie", "guide"}) );
  add_alias( "newbiebook" );
  set_weight( 2 );
  set_value( 0 );
  set_long( "This is a guide book for the newbies who rushed through the "
            "newbie foyer too fast or are just absent-minded in general.  "
            "It contains valuable information on the commands, guilds "
            "and the city of Ankh-Morpork.\n\n"
            "You may 'open book', 'read newbie book', 'turn page of "
            "newbie book' or 'open newbie book to page #'.\n" );
  set_book_language( "general" );
  set_book_dir( NEWBIE_SAVE + "newbie_book_page" );
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
"            |         |    |    Discworld    |    |          |         \n"
"            |        /      \\    Mudders    /      \\         |         \n"
"             \\   _  /        \\_           _/        \\   _   /         \n"
"              | | | |          \\_       _/           | | | |           \n"
"              |_| |_|            \\_____/             |_| |_|           \n"
"       ____________________________________________________________     \n"
"   ___|  Syntaxes: 'open book' 'read book' 'turn a page of book'   |___  \n"
"   \\  |____________        'open book to page #'       ____________|  /  \n"
"   /____/          \\__________________________________/          \\____\\ ",
"general");
}