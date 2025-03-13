# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/foyer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            add_property("no teleport", 1)
            set_zone( "Newbie" )
            set_short( "Faerûnworld foyer" )
            set_light( 75 )
            set_long("This is a cavernous, circular room that echoes the shape of "
            "the Faerûnworld itself.  At its centre is a large round table upon "
            "which is what appears to be a map of Faerûnworld, complete with "
            "Great A'Tuin swimming slowly through space carrying Berilia, "
            "Tubul, Great T'Phon and Jerakeen, the four giant elephants upon "
            "whose shoulders the disc of the world rests.  The walls are "
            "decorated with murals showing scenes from the disc.  Dark doorways "
            "ring the perimeter of the room, leading away in all directions.\n"
            "There is a large white sign on one wall labelled 'Faerûnworld'.  "
            "You may 'look' at a sign or 'read' a sign.\n")
            add_item(["map", "disc", "Faerûn"], "Upon closer examination you are not "
            "quite so certain that this is just a map of the Faerûn.  "
            "The detail is incredible, from the sharp spire of Cori "
            "Celesti at the centre, to the surrounding Circle Sea, "
            "the deserts of Klatch, the watery world of Krull, and the "
            "mysterious Counterweight Continent.  A spectacular rimbow "
            "sparkles where the seas pour over the edge of the Faerûn.  As "
            "you study the map's details, you are sure you saw one of the "
            "elephants move.")
            add_item("rimbow", "It's like a rainbow except that it's caused by the "
            "water pouring off the edge of the disc.")
            add_item("elephant", "These are the four elephants that bear the weight"
            " of the Faerûn.")
            add_item( "table", "The table is made of a single piece of green granite, "
            "heavily carved with small figures.  The top of the table is "
            "mostly covered by the map of Faerûnworld, although you can see "
            "a few squares of black and white marble underneath, rather "
            "like a chessboard.")
            add_item(["figure", "carving"], "The tiny, carved figures are "
            "extremely detailed.  You can make out what appears to be "
            "some trolls, a handful of dwarfs, three witches, and what "
            "surely must be the ugliest cat ever.  Looking at the cat "
            "carving, you are sure you catch a whiff of something vile, "
            "much like fermented carpets.")
            add_item("floor", "The floor is made of polished marble so smooth that "
            "you can see your face in it - yeuch!")
            add_item("wall", "The walls are covered in murals showing scenes from "
            "the disc.")
            add_item( "ceiling", "The ceiling, if there is one, disappears into the "
            "lofty gloom overhead.")
            add_item(["doorway", "door"], "The doorways are dark, yet somehow "
            "inviting.  Or at least not threatening.")
            add_item("mural", "On one wall there is a painting of a seedy looking inn "
            "with a sign of a drum hanging outside.  On another a small castle "
            "set high in a mountainous region where the peaks are snow-"
            "capped.  You can almost feel the biting wind.  On another an "
            "oasis in an otherwise hot, dry desert.  The final one is the "
            "most peculiar being a strange bone covered landscape with a "
            "massive sphinx in the centre.")
            add_sign("This is a simple white sign marked \"Faerûnworld\".\n",
            format_sign("This mud is based on the books written by Terry "
            "Pratchett.  While it is not necessary to have read "
            "the Faerûnworld books you may find it helpful for some "
            "of the quests and in knowing more about the "
            "characters and places in the game."),
            0, ["sign","discworld","Faerûnworld"], "general" )->add_property(
            "determinate","the ")
            room_chat(({60, 120, ({"There is a sound like the rattle and fall of a "
            "pair of dice.",
            "You hear a hushed chuckle far above your head.",
            "A pleasant voice says: Another game?"
            })}))
            add_exit("helpme", PATH+"help", "door")
            add_exit("communication", PATH +"communication", "door")
            add_exit("hints", PATH +"hints", "door")
            add_exit("classs", PATH+"classs_foyer", "door")
            add_exit("commerce", PATH+"shop", "door")
            add_exit("align", PATH+"align", "door")
            add_exit("advancement", PATH+"advancement", "door")
            add_exit("combat", PATH+"combat","door")
            add_property("no godmother", 1)
            add_exit("out", PATH + "choose_land", "path" )
            modify_exit( "out", ["function", "check_allow"] )


    def check_allow(self, str: str, ob: MudObject, special_mess: str) -> int:
            if(ob.query_property("womble's brooch")) {
            ob.set_language("general")
            return 1


    def init(self, ) -> None:
            ::init()
            womble = find_object( PATH +"womble" )
            if ( !womble || !environment( womble ) )
            ( PATH +"womble" )->move( self, "$N womble$s in." )


    def format_sign(self, message: str) -> str:
            int i
            string *bits
            string ret = "", bit
            bits = explode(sprintf("%-="+(SIGN_WIDTH-2)+"s", message), "\n")
            ret += "\n     _"
            for(i=0; i<SIGN_WIDTH - 1; i++)
            ret += "_"
            ret += "\n"
            ret +="
            for(i=0; i<SIGN_WIDTH; i++)
            ret += " "
            ret += "\\\n"
            foreach(bit in bits) {
            ret += "   || " + bit
            for(i=sizeof(bit); i<SIGN_WIDTH-1; i++)
            ret += " "
            ret += "|\n"



class Foyer(MudObject):
