# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/newbie_brochure.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "brochure" )
            set_short( "newbie brochure")
            set_main_plural( "brochures" )
            add_alias ( ( {"brochure", "pamphlet", "newbie brochure"} ) )
            set_weight( 0 )
            set_value( 400 )
            set_no_pages( PAGES )
            set_long( "This is a pamphlet for the newbies who rushed through the "
            "newbie foyer too fast or are just absent-minded in general.  "
            "It contains valuable information on the commands, classs "
            "and the city.  "
            "You may <read brochure>, and "
            "<turn a page of brochure>.\n" )
            set_open_page( 1 )
            set_read_mess( "                                                \n"
            "                                                                \n"
            "                            %^B_RED%^TABLE OF CONTENTS%^RESET%^                        Page 1\n"
            "                    .o0o.o0o.o0o.o0o.o0o.o0o.o0o.o0o.       \n"
            "                                            \n"
            "         General information.....................................2-3\n"
            "         Commands..................................................4\n"
            "         Guilds....................................................5\n"
            "         The lands around Waterdeep.............................6\n"
            "                                                                  "
            "                                                                  "
            "                                                                  "
            "%^B_RED%^ NOTE:%^RESET%^ If you haven't played MUD's before, we advise you"
            " to read any of the \n"
            " FAQ's around (Frequently Asked Questions).  To read the Faerûnworld FAQ,\n"
            " type 'help FAQ' or point your http browser at: \n"
            " http:
            "general", 100 )
            set_open_page( 2 )
            set_read_mess( "                                                        \n"
            "                            GENERAL INFORMATION                     Page 2\n"
            "                           -=-=-=-=-=-=-=-=-=-=-                 \n"
            "                                                \n"
            " At any time during the course of playing you can get HELP on various \n"
            " topics by typing  '%^B_RED%^help concepts%^RESET%^' "
            "and  '%^B_RED%^help command_list%^RESET%^'. \n"
            " If you need to ask something else, or have problems of any kind, \n"
            " the LIAISON people will kindly help you out, if you ask nicely. \n"
            " To see if any are logged on, simply type  '%^B_RED%^liaisons%^RESET%^'.\n"
            " Also, most of the players are usually very helpful when it comes to \n"
            " answering questions.                                \n"
            "                                                                        \n"
            " As soon as you have made a choice you should join a GUILD where you can \n"
            " advance your skills (take a look at page 5 in this brochure for more \n"
            " information on the different classs).  But while deciding, you can \n"
            " simply teach yourself.  Type  '%^B_RED%^help level%^RESET%^' and "
            " '%^B_RED%^help teach%^RESET%^' \n"
            " to find out more.\n"
            "                                 \n"
            " CONTINUES ON NEXT PAGE.\n",
            "general", 100 )
            set_open_page( 3 )
            set_read_mess( "                                                  \n"
            "                                                                   Page 3\n"
            " In Waterdeep there are GUIDES wandering around that can take you to \n"
            " certain destinations.  These are often waiting by the classs or in the \n"
            " Mended Drum.  To use one you say in the same room as one, for example: \n"
            " 'take me to wizards class please'.  \n"
            " Other places they can take you to, besides the classs, are \n"
            " 'the post office',  'the bank',  'least gate' and  'hubwards gate'.\n"
            "                                                    \n"
            " You start off with a total of eight lives.  If you should happen to die,\n"
            " Harry at the Temple of Small Gods, can RAISE you from the dead and you \n"
            " are then set to go again (one life shorter).  Player Priests also have \n"
            " the ability to resurrect.\n"
            " And please BUG report bugs and typos you see.  Do  '%^B_RED%^help bug%^RESET%^' "
            " and \n"
            " '%^B_RED%^help typo%^RESET%^' for more information.\n",
            "general", 100 )
            set_open_page( 4 )
            set_read_mess( "                                                       \n"
            "                                   COMMANDS                        Page 4\n"
            "                                 -=-=-=-=-=-\n"
            "                                                                  \n"
            " '%^B_RED%^who%^RESET%^' or '%^B_RED%^finger%^RESET%^'"
            "  Will show the people logged on.  \n"
            "                    You can also 'finger <playername>'\n"
            " '%^B_RED%^rearrange%^RESET%^'        Allows you to set your stats"
            " (You can only do this once).\n"
            " '%^B_RED%^score%^RESET%^'            Will show statistics.\n"
            " '%^B_RED%^i%^RESET%^'                Will show you your inventory.\n"
            " '%^B_RED%^skills%^RESET%^'           Will list your skills.\n"
            " '%^B_RED%^wimpy < % >%^RESET%^'      To automatically run away before "
            "you die.\n"
            " '%^B_RED%^monitor on%^RESET%^'       Will help you keep track of Hit"
            " and Guild points.\n"
            " '%^B_RED%^inform logon on/off%^RESET%^'    Gives you info on logon/out-"
            "events (once you've \n                    joined a class).\n"
            " '%^B_RED%^help map%^RESET%^'         Gives you a map of Waterdeep  "
            "(Try also \n"
            "                   'help ankh-morpork'.)\n"
            " '%^B_RED%^.%^RESET%^'                Will repeat your last command.\n"
            " Other commands "
            "worth checking out, or read the help files for, are: \n"
            " '%^B_RED%^alias%^RESET%^',  '%^B_RED%^earmuff%^RESET%^', "
            " '%^B_RED%^commands%^RESET%^', '%^B_RED%^score stats%^RESET%^',  "
            "'%^B_RED%^nickname%^RESET%^',  '%^B_RED%^consider%^RESET%^'\n"
            " '%^B_RED%^gp%^RESET%^' and  '%^B_RED%^playerkilling%^RESET%^'.\n",
            "general", 100 )
            set_open_page( 5 )
            set_read_mess( "                                                   \n"
            "                               THE GUILDS                           Page 5\n"
            "                             -=-=-=-=-=-=-\n"
            "                                                  \n"
            " Each player will usually join a class so that they can learn skills\n"
            " and commands and so advance their abilities.   Being in a class also \n"
            " adds character to your character.  These classs are currently available:\n"
            " WIZARDS GUILD is located west of Sator Square.  To join you have to look\n"
            " around in the Great Hall and find a staircase.\n"
            " THIEVES GUILD is at the beginning of Alchemist street.\n"
            " FIGHTERS GUILD is on Filigree Street, just a stone's throw from Mended \n"
            " Drum.\n"
            " PRIESTS GUILD with its various Gods is located on Small Gods Street.\n"
            " The Gods are: Hat, Pishe, Fish, Sek, Gapp, Gufnork and Sandelfon.\n"
            " For more information, type 'info' in their class rooms.\n"
            " ASSASSINS GUILD is located at the eastern end of Filigree Street.  Fill \n"
            " in an application and give it to the secretary in the class office.\n"
            " WITCHES GUILD is located at Granny Weatherwax' cottage in Lancre. \n"
            " See Gennie Applebottom at Dione Street in Ankh-\n"
            " Morpork if you have trouble finding the place.\n",
            "general", 100 )
            set_open_page( 6 )
            set_read_mess( "                                                    \n"
            "                        THE LANDS OUTSIDE ANKH-MORPORK              Page 6\n"
            "                       -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-                \n"
            "                                                           \n"
            " The lands around the city can sometimes be strange and dangerous \n"
            " places.  Through the northeastern (Least) gate is the path that goes \n"
            " through the plains, some small villages, and finally up to the \n"
            " mountains, also known as the Ramtops.\n"
            " The southeastern (Hubwards) gate takes you into the vast forest where \n"
            " innocent people are terrorised by wolves and other strange creatures \n"
            " that roam unfettered.  It's also a more direct route to the Ramtops\n"
            " (Carriages from Waterdeep are a nice alternative to tired feet for \n"
            " travelling to and from the towns in the Sto Plains and Ramtops).\n"
            " The tour operator at Sator Square is ready to send you to the warm \n"
            " and distant continent of Klatch, if you have enough money.\n"
            " There are more fantastic and exciting places to come.\n",
            "general", 100 )
            set_open_page( 1 )



class Newbie_brochure(MudObject):
