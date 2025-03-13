# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/communicate.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def communicate_commands(self, ) -> None:
            add_command("converse", "", (: converse(0) :))
            add_command("converse", "<string'person'>", (: converse($4[0]) :))
            add_command("frimble", "<string>", (: do_write($4[0]) :))
            add_command("repeat", "<string'command'>", (: do_repeat($4[0]) :))


    def query_real_max_sp(self, ) -> int:
            int ret
            ret = sqrt(self.query_time_on() / -15)
            if(ret < 50)
            return 50
            if(ret > 500)
            return 500
            return ret


    def adjust_max_sp(self, number: int) -> int:
            _sp[1] += number
            if ( _sp[1] < 0 )
            _sp[1] = 0
            number = query_real_max_sp()
            if ( _sp[1] > number )
            _sp[1] = number
            return _sp[1]


    def adjust_sp(self, number: int) -> int:
            if (_sp[0] + number < 0)
            return -1
            if (number < 0)
            adjust_max_sp(1)
            _sp[0] += number
            if ( _sp[0] > _sp[1] )
            _sp[0] = _sp[1]
            return _sp[0]


    def set_sp(self, number: int) -> int:
            return adjust_sp( number - _sp[0] )


    def do_converse(self, str: str) -> None:
            if(str == "**") {
            write("Ok.\n")
            converse_ob = 0
            return


    def add_language(self, lang: str) -> None:
            int lvl
            string skill
            if (!LANGUAGE_HAND.test_language(lang))
            return
            if (LANGUAGE_HAND.query_language_spoken(lang)) {
            skill = LANGUAGE_HAND.query_language_spoken_skill(lang)
            lvl = self.query_skill(skill)
            self.add_skill_level(skill, 100 - lvl)


    def set_language(self, str: str) -> int:
            if (!LANGUAGE_HAND.test_language(str))
            return 0
            fixup_lang_class()
            cur_lang->cur_lang = str
            return 1


    def query_current_language(self, ) -> str:
            fixup_lang_class()
            return cur_lang->cur_lang


    def set_default_language(self, def: str) -> None:
            fixup_lang_class()
            cur_lang->default_lang = def


    def query_default_language(self, ) -> str:
            fixup_lang_class()
            return cur_lang->default_lang


    def set_mangle_accent(self, flag: int) -> None:
            fixup_lang_class()
            cur_lang->mangle_accent = flag


    def query_mangle_accent(self, ) -> int:
            fixup_lang_class()
            return cur_lang->mangle_accent


    def set_tell_reply_list(self, list: Any) -> int:
            if (base_name(previous_object())[0 .. strlen(TELL_CMD) - 1] != TELL_CMD &&
            base_name(previous_object())[0 .. strlen(REMOTE_CMD) - 1] != REMOTE_CMD  &&
            !previous_object()->query_lord())
            return 0
            tell_reply_list = ({time() + (60 * 15), list]
            return 1


    def query_tell_reply_list(self, ) -> Any:
            if(base_name(previous_object())[0..strlen(TELL_CMD) - 1] != TELL_CMD &&
            base_name(previous_object())[0 .. strlen(REMOTE_CMD) - 1] != REMOTE_CMD  &&
            !previous_object()->query_lord())
            return 0
            if(tell_reply_list[0] < time())
            return 0
            return tell_reply_list[1]



class Communicate(MudObject):
