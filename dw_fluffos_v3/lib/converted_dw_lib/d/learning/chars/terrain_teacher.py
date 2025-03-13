# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/chars/terrain_teacher.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            object obj
            object backpack
            set_name("terrain teacher")
            add_alias("teacher")
            set_short("terrain teacher")
            add_property("determinate", "the ")
            add_property("unique", 1)
            set_long("This man is middle aged, and apparently human.  That's about "
            "all you can really see, because he's soaking wet, his hair is caked "
            "with leaves and mud, his clothes are torn, and his boots are caked "
            "with dirt.\n")
            set_race("human")
            set_class("monk")
            set_level(50)
            set_gender(1)
            add_effect("/std/effects/other/wetness", 10000)
            set_respond_to_with( ({
            ["@say", "teach", "please"], "#new_pupil",
            ["@say", "please", "teach"], "#new_pupil",
            ["@say", "teach"], "#new_rude_pupil",
            ["@say", ["ok", "ready"]], "#next_speech",
            }) )
            backpack = ARMOURY.request_item("large backpack", 80)
            if (!backpack) backpack = ARMOURY.request_item("black leather backpack", 80)
            if (!backpack) backpack = ARMOURY.request_item("small backpack", 80)
            if (backpack) backpack.move(self)
            obj = ARMOURY.request_item("large leather boots", 20)
            if (obj) obj.move(self)
            obj = ARMOURY.request_item("thermal underwear", 10)
            if (obj) obj.move(self)
            obj = ARMOURY.request_item("fawn cotton trousers", 50)
            if (obj) obj.move(self)
            obj = ARMOURY.request_item("leather belt", 50)
            if (obj) obj.move(self)
            obj = ARMOURY.request_item("black wool socks", 40)
            if (obj) obj.move(self)
            obj = ARMOURY.request_item("gaudy shirt", 35)
            if (obj) obj.move(self)
            obj = ARMOURY.request_item("brown felt hat", 10)
            if (obj) obj.move(self)
            obj = ARMOURY.request_item("white cotton toga", 80)
            if (obj) obj.move(backpack)
            obj = ARMOURY.request_item("yellow raincoat", 60)
            if (obj) obj.move(backpack)
            obj = ARMOURY.request_item("old black cloak", 72)
            if (obj) obj.move(backpack)
            obj = ARMOURY.request_item("amusing earmuffs", 100)
            if (obj) obj.move(backpack)
            init_equip()
            costume = COSTUME_NORMAL
            hq = find_object(TERRAIN_TUTORIAL "foyer")
            impatience = 0
            lesson_step = 0
            speeching = 0


    def check_anyone_here(self, ) -> int:
            if (pupil) return 1
            else return ::check_anyone_here()


    def heart_beat(self, ) -> None:
            ::heart_beat()
            if (!pupil) return
            ++impatience
            if (impatience == CROSS_IMPATIENCE) {
            init_command("emote is beginning to look a bit impatient.", 1)
            } else if (impatience == TAPS_IMPATIENCE) {
            init_command("emote begins tapping his foot.", 1)
            } else if (impatience == MAX_IMPATIENCE) {
            init_command("'That's it, you clearly don't really want to learn.  "
            "I give up on you, " + pupil.short(), 1)
            asyncio.create_task(self."come", 3 + costume_normal(), hq)
            pupil = 0
            impatience = 0


    def add_follower(self, who: MudObject) -> int:
            if (who == pupil) {
            int lesson
            impatience = 0
            lesson = pupil.query_property(PROPERTY)
            if (lesson < 0 || lesson >= sizeof(lessons)) {
            init_command("think", 1)
            init_command("'Odd, you seem to have done more lessons than I know.", 2)
            init_command("'I'm afraid I have nothing to teach you.", 3)
            pupil.remove_property(PROPERTY)
            pupil = 0
            return 0
            } else if (::add_follower(who)) {
            int delay
            switch (lessons[lesson][1]) {
            case COSTUME_NORMAL: delay = costume_normal(); break
            case COSTUME_DESERT: delay = costume_desert(); break
            case COSTUME_WET: delay = costume_wet(); break
            case COSTUME_COLD: delay = costume_cold(); break


    def coming(self, where: MudObject) -> None:
            tell_room( where,
            "%^CYAN%^Someone says: One moment!  I'll be right down!%^RESET%^\n",
            [self] )


    def annoyed_coming(self, where: MudObject) -> None:
            tell_room( where,
            "%^CYAN%^An annoyed someone says: I said I'm coming!  "
            "Jeez!%^RESET%^\n",
            [self] )


    def come(self, where: MudObject) -> None:
            hq = where
            if (where != environment())
            move( where, self.a_short() + " arrives",
            self.a_short() + " stomps away" )
            init_command( "emote looks around", 1 )
            init_command( "sigh", 4 )
            init_command( "get sign", 7 )
            init_command( "emote looks at the sign", 9 )
            init_command( "sit on bench", 10 )
            init_command( "'What can I do for you?", 12 )


    def done(self, ) -> None:
            int delay = costume_normal()
            int lesson
            lesson = pupil.query_property(PROPERTY) + 1
            if (lesson == sizeof(lessons)) {
            init_command("'congratulations, " + pupil.short() + ", you have "
            "completed all the terrain handler lessons.", ++delay)
            pupil.remove_property(PROPERTY)
            } else
            pupil.add_property(PROPERTY, lesson)
            init_command("emote looks around", delay + 1)
            init_command("sigh", delay + 4)
            init_command("get sign", delay + 7)
            init_command("emote looks at the sign", delay + 9)
            init_command("sit on bench", delay + 10)
            pupil = 0
            impatience = 0
            speeching = 0


    def speech(self, ) -> None:
            int lesson = pupil.query_property(PROPERTY)
            int delay
            delay = 0
            speeching = 1
            if (lesson_step == sizeof(lessons[lesson][2])) {
            init_command(lessons[lesson][3], delay + 3)
            asyncio.create_task(self."done", delay + 4)
            asyncio.create_task(self. (: speeching = 0 :), delay + 5)
            return


    def pupil_arrived(self, where: MudObject) -> None:
            if (pupil) return
            if (!environment()) {
            if (find_asyncio.create_task(self."come") != -1)
            asyncio.create_task(self."annoyed_coming", 0, where)
            else {
            asyncio.create_task(self."come", 10, where)
            if (find_asyncio.create_task(self."coming") == -1)
            asyncio.create_task(self."coming", 2, where)


    def costume_normal(self, ) -> int:
            int i
            if (costume == COSTUME_NORMAL) return 0
            i = modesty()
            init_command("remove backpack", ++i)
            init_command("remove toga, raincoat, cloak, earmuffs", ++i)
            init_command("put toga, raincoat, cloak, earmuffs in backpack", ++i)
            init_command("get trousers, belt, shirt, hat from backpack", ++i)
            init_command("equip", ++i)
            costume = COSTUME_NORMAL
            return i


    def costume_desert(self, ) -> int:
            int i
            if (costume == COSTUME_DESERT) return 0
            i = modesty()
            init_command("remove backpack", ++i)
            init_command("remove raincoat, cloak, earmuffs", ++i)
            init_command("remove belt, hat, shirt", ++i)
            init_command("remove trousers", ++i)
            init_command("put trousers, belt, shirt, hat, raincoat, cloak, "
            "earmuffs in backpack", ++i)
            init_command("get toga from backpack", ++i)
            init_command("equip", ++i)
            costume = COSTUME_DESERT
            return i


    def costume_wet(self, ) -> int:
            int i
            if (costume == COSTUME_WET) return 0
            i = modesty()
            init_command("remove backpack", ++i)
            init_command("remove toga, cloak, earmuffs", ++i)
            init_command("put toga, cloak, earmuffs in backpack", ++i)
            init_command("get trousers, belt, shirt, hat, raincoat from "
            "backpack", ++i)
            init_command("equip", ++i)
            costume = COSTUME_WET
            return i


    def costume_cold(self, ) -> int:
            int i
            if (costume == COSTUME_COLD) return 0
            i = modesty()
            init_command("remove backpack", ++i)
            init_command("remove toga, raincoat, hat", ++i)
            init_command("put toga, raincoat, hat in backpack", ++i)
            init_command("get trousers, belt, shirt, cloak, earmuffs "
            "from backpack", ++i)
            init_command("equip", ++i)
            costume = COSTUME_COLD
            return i


    def next_speech(self, who: MudObject, message: str) -> None:
            if (who != pupil) return
            if (speeching) return
            impatience = 0
            asyncio.create_task(self."speech", 1)


    def new_pupil(self, who: MudObject, message: str) -> None:
            if ( pupil ) {
            if ( pupil == who ) {
            impatience = 0
            init_command("pat " + who.short(), 1)
            init_command("'That's alright.  I understand you can get "
            "excited at times like this.  Be assured that I am going "
            "to teach you, " + who.short(), 3)
            } else {
            init_command("'sorry, " + who.short() + ", but I am teaching " +
            pupil.short() + " right now.", 1)


    def new_rude_pupil(self, who: MudObject, message: str) -> None:
            if (!pupil) {
            init_command("emote hums quietly to himself.", 2)
            init_command("mumble rude pupils", 5)



class Terrain_teacher(MudObject):
