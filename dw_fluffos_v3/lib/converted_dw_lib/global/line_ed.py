# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/line_ed.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.editor = "menu"


    def __init__(self):
            self.editor = "menu"
            protected void editor_commands()  {
            add_command("editor", "{menu|magic|ed|command}", (: set_editor($4[0]) :))


    def end_of_edit_more(self, ) -> None:
            self.set_finish_func(0)
            main_bit("")


    def editor_exit_ed(self, ) -> None:
            string str
            str = read_file(_filename)
            if ((file_size(_filename) >= 0) && !rm(_filename))
            log_file(LOG_FILE, "ed: couldn't rm %s\n", _filename)
            _lines = explode("#" + str, "\n")
            _lines[0] = _lines[0][1..]
            main_bit("")
            return


    def editor_finish_ed(self, ) -> None:
            string str
            str = read_file(_filename)
            if ((file_size(_filename) >= 0) && (_filename == TMP_FILE) &&
            !rm(_filename)) {
            log_file(LOG_FILE, "ed: couldn't rm %s\n", _filename)


    def editor_do_quit(self, str: str) -> None:
            _lines = [})
            if ((editor == "magic") && (_filename == TMP_FILE) &&
            (file_size(_filename) >= 0) && !rm(_filename))  {
            printf("magic: couldn't remove %s\n" , _filename)
            str = 0


    def set_editor(self, str: str) -> int:
            editor = str
            printf("Editor set to %s.\n", str)
            return 1


    def append_signature(self, ) -> str:
            return PLAYER_HANDLER.query_signature(self->query_name())


    def editor_check_do_quit(self, ) -> None:
            if (_in_editor)  {
            printf("Saving what you are editing.\n")
            if (editor != "ed") {
            editor_do_quit(implode(_lines, "\n"))
            } else {
            editor_finish_ed()


    def query_editor(self, ) -> str:
            return editor


    def query_in_editor(self, ) -> int:
            return _in_editor



class Line_ed(MudObject):

    editor = '"menu"'
