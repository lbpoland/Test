# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/curses/ken_mangle.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.replace_matrix = []
            self.trans = ([ ])
            self.trans["stairs"] = "apples and pears"
            self.trans["Downstairs"] = "Down the apples and pears"
            self.trans["downstairs"] = "down the apples and pears"
            self.trans["Upstairs"] = "Up the apples and pears"
            self.trans["upstairs"] = "up the apples and pears"
            self.trans["mouth"] = "North and South"
            self.trans["Mouth"] = "North and South"
            self.trans["Face"] = "Boat Race"
            self.trans["face"] = "Boat Race"
            self.trans["Trouble"] = "Barney Rubble"
            self.trans["trouble"] = "Barney Rubble"
            self.trans["wife"] = ['trouble and strife', 'ole lady']
            self.trans["Road"] = "Frog and Toad"
            self.trans["road"] = "frog and toad"
            self.trans["pub"] = "rub-a-dub "
            self.trans["bar"] = "boozer"
            self.trans["husband"] = "ole man"
            self.trans["Party"] = "Knees-up"
            self.trans["party"] = "knees-up"
            self.trans["Parties"] = "Knees-ups"
            self.trans["parties"] = "knees-ups"
            self.trans["My"] = "Me"
            self.trans["my"] = "me"
            self.trans["Your"] = "Yer"
            self.trans["your"] = "yer"
            self.trans["You"] = "Yer"
            self.trans["you"] = "yer"
            self.trans["Those"] = "Them"
            self.trans["those"] = "them"
            self.trans["those"] = "them"
            self.trans["(those"] = "(them"
            self.trans["The"] = ["The bleedin'", 'The']
            self.trans["Fe"] = ["The bleedin'", 'The']
            self.trans["the"] = ["the bleedin'", 'the']
            self.trans["fe"] = ["the bleedin'", 'the']
            self.trans["Thus"] = "So"
            self.trans["thus"] = "so"
            self.trans["(thus"] = "(so"
            self.trans["thus"] = "so"
            self.trans["old"] = "ole"
            self.trans["to"] = "ter"
            self.trans["Aren't"] = "Ain't"
            self.trans["aren't"] = "ain't"
            self.trans["Isn't"] = "Ain't"
            self.trans["isn't"] = "ain't"
            self.trans["Hallo"] = "Wotcher"
            self.trans["Hello"] = "Wotcher"
            self.trans["Hullo"] = "Wotcher"
            self.trans["Hi"] = "Wotcher"
            self.trans["hallo"] = "wotcher"
            self.trans["hello"] = "wotcher"
            self.trans["hullo"] = "wotcher"
            self.trans["hi"] = "wotcher"
            self.trans["What"] = "Wot"
            self.trans["what"] = "wot"
            self.trans["Were"] = "Was"
            self.trans["were "] = "was"
            self.trans["Bother"] = "Ars"
            self.trans["bother"] = "ars"
            self.trans["Mother"] = "Muvver"
            self.trans["Other"] = "Uvver"
            self.trans["other"] = "uvver"
            self.trans["Father"] = "Favver"
            self.trans["father"] = "favver"
            self.trans["Rather"] = "Ravver"
            self.trans["rather"] = "ravver"
            self.trans["Weather"] = "Wevver"
            self.trans["weather"] = "wevver"
            self.trans["Leather"] = "Levver"
            self.trans["leather"] = "levver"
            self.trans["Wither"] = "Wivver"
            self.trans["wither"] = "wivver"
            self.trans["Either"] = "Eever"
            self.trans["either"] = "eever"
            self.trans["With"] = "Wiv"
            self.trans["with"] = "wiv"
            self.trans["Anything"] = "Anyfink"
            self.trans["anything"] = "anyfink"
            self.trans["Something"] = "Sumfink"
            self.trans["something"] = "sumfink"
            self.trans["Nothing"] = "Nuffink"
            self.trans["nothing"] = "nuffink"
            self.trans["guitars"] = "spoons"
            self.trans["guitar"] = "spoons"
            self.trans["drums"] = "spoons"
            self.trans["drum"] = "spoons"
            self.trans["trumpets"] = "spoons"
            self.trans["trumpet"] = "spoons"
            self.trans["violins"] = "spoons"
            self.trans["violin"] = "spoons"
            self.trans["clarinets"] = "spoons"
            self.trans["clarinet"] = "spoons"
            self.trans["trombones"] = "spoons"
            self.trans["trombone"] = "spoons"
            self.trans["oboes"] = "spoons"
            self.trans["oboe"] = "spoons"
            self.trans["flutes"] = "spoons"
            self.trans["flute"] = "spoons"
            self.trans["tubas"] = "spoons"
            self.trans["tuba"] = "spoons"
            self.trans["Data"] = "Info"
            self.trans["data"] = "info"
            self.trans["Directory"] = "Lockup"
            self.trans["directory"] = "lockup"
            self.trans["Directories"] = "Lockups"
            self.trans["directories"] = "lockups"
            self.trans["Stopped"] = "'Ad the mockers put on"
            self.trans["stopped"] = "'ad the mockers put on"
            self.trans["Stopping"] = "Putting the mockers on"
            self.trans["stopping"] = "putting the mockers on"
            self.trans["stops"] = "puts the mockers on"
            self.trans["stop"] = "put the mockers on"
            self.trans["STOP"] = "Put The Mockers On"
            self.trans["Londoner"] = "Cockney"
            self.trans["londoner"] = "Cockney"
            self.trans["friend"] = ['mucker', 'mate', 'china']
            self.trans["sin'"] = "sing"
            self.trans["rin'"] = "ring"


    def do_transmute(self, str: str) -> str:
            string tmp, *bits
            mixed erp
            int i
            tmp = replace(" "+str+" ", replace_matrix)
            bits = explode(tmp, " ")
            for (i=0;i<sizeof(bits);i++) {
            if (erp = trans[bits[i]])
            if (stringp(erp))
            bits[i] = erp
            else
            bits[i] = erp[random(sizeof(erp))]



class Ken_mangle(MudObject):

    replace_matrix = '[]'

    trans = '([ ])'

    trans["stairs"] = '"apples and pears"'

    trans["Downstairs"] = '"Down the apples and pears"'

    trans["downstairs"] = '"down the apples and pears"'

    trans["Upstairs"] = '"Up the apples and pears"'

    trans["upstairs"] = '"up the apples and pears"'

    trans["mouth"] = '"North and South"'

    trans["Mouth"] = '"North and South"'

    trans["Face"] = '"Boat Race"'

    trans["face"] = '"Boat Race"'

    trans["Trouble"] = '"Barney Rubble"'

    trans["trouble"] = '"Barney Rubble"'

    trans["wife"] = "['trouble and strife', 'ole lady']"

    trans["Road"] = '"Frog and Toad"'

    trans["road"] = '"frog and toad"'

    trans["pub"] = '"rub-a-dub "'

    trans["bar"] = '"boozer"'

    trans["husband"] = '"ole man"'

    trans["Party"] = '"Knees-up"'

    trans["party"] = '"knees-up"'

    trans["Parties"] = '"Knees-ups"'

    trans["parties"] = '"knees-ups"'

    trans["My"] = '"Me"'

    trans["my"] = '"me"'

    trans["Your"] = '"Yer"'

    trans["your"] = '"yer"'

    trans["You"] = '"Yer"'

    trans["you"] = '"yer"'

    trans["Those"] = '"Them"'

    trans["those"] = '"them"'

    trans["(those"] = '"(them"'

    trans["The"] = '["The bleedin\'", \'The\']'

    trans["Fe"] = '["The bleedin\'", \'The\']'

    trans["the"] = '["the bleedin\'", \'the\']'

    trans["fe"] = '["the bleedin\'", \'the\']'

    trans["Thus"] = '"So"'

    trans["thus"] = '"so"'

    trans["(thus"] = '"(so"'

    trans["old"] = '"ole"'

    trans["to"] = '"ter"'

    trans["Aren't"] = '"Ain\'t"'

    trans["aren't"] = '"ain\'t"'

    trans["Isn't"] = '"Ain\'t"'

    trans["isn't"] = '"ain\'t"'

    trans["Hallo"] = '"Wotcher"'

    trans["Hello"] = '"Wotcher"'

    trans["Hullo"] = '"Wotcher"'

    trans["Hi"] = '"Wotcher"'

    trans["hallo"] = '"wotcher"'

    trans["hello"] = '"wotcher"'

    trans["hullo"] = '"wotcher"'

    trans["hi"] = '"wotcher"'

    trans["What"] = '"Wot"'

    trans["what"] = '"wot"'

    trans["Were"] = '"Was"'

    trans["were "] = '"was"'

    trans["Bother"] = '"Ars"'

    trans["bother"] = '"ars"'

    trans["Mother"] = '"Muvver"'

    trans["Other"] = '"Uvver"'

    trans["other"] = '"uvver"'

    trans["Father"] = '"Favver"'

    trans["father"] = '"favver"'

    trans["Rather"] = '"Ravver"'

    trans["rather"] = '"ravver"'

    trans["Weather"] = '"Wevver"'

    trans["weather"] = '"wevver"'

    trans["Leather"] = '"Levver"'

    trans["leather"] = '"levver"'

    trans["Wither"] = '"Wivver"'

    trans["wither"] = '"wivver"'

    trans["Either"] = '"Eever"'

    trans["either"] = '"eever"'

    trans["With"] = '"Wiv"'

    trans["with"] = '"wiv"'

    trans["Anything"] = '"Anyfink"'

    trans["anything"] = '"anyfink"'

    trans["Something"] = '"Sumfink"'

    trans["something"] = '"sumfink"'

    trans["Nothing"] = '"Nuffink"'

    trans["nothing"] = '"nuffink"'

    trans["guitars"] = '"spoons"'

    trans["guitar"] = '"spoons"'

    trans["drums"] = '"spoons"'

    trans["drum"] = '"spoons"'

    trans["trumpets"] = '"spoons"'

    trans["trumpet"] = '"spoons"'

    trans["violins"] = '"spoons"'

    trans["violin"] = '"spoons"'

    trans["clarinets"] = '"spoons"'

    trans["clarinet"] = '"spoons"'

    trans["trombones"] = '"spoons"'

    trans["trombone"] = '"spoons"'

    trans["oboes"] = '"spoons"'

    trans["oboe"] = '"spoons"'

    trans["flutes"] = '"spoons"'

    trans["flute"] = '"spoons"'

    trans["tubas"] = '"spoons"'

    trans["tuba"] = '"spoons"'

    trans["Data"] = '"Info"'

    trans["data"] = '"info"'

    trans["Directory"] = '"Lockup"'

    trans["directory"] = '"lockup"'

    trans["Directories"] = '"Lockups"'

    trans["directories"] = '"lockups"'

    trans["Stopped"] = '"\'Ad the mockers put on"'

    trans["stopped"] = '"\'ad the mockers put on"'

    trans["Stopping"] = '"Putting the mockers on"'

    trans["stopping"] = '"putting the mockers on"'

    trans["stops"] = '"puts the mockers on"'

    trans["stop"] = '"put the mockers on"'

    trans["STOP"] = '"Put The Mockers On"'

    trans["Londoner"] = '"Cockney"'

    trans["londoner"] = '"Cockney"'

    trans["friend"] = "['mucker', 'mate', 'china']"

    trans["sin'"] = '"sing"'

    trans["rin'"] = '"ring"'
