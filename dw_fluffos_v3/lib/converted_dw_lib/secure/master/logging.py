# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/logging.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def get_wiz_name(self, file: Any) -> str:
            if (!previous_object())
            return "root"
            if (objectp(file))
            file = file_name(file)
            file = explode(file, "/") - [""]
            if (file[0] == "w") {
            if (file_size("/w/" + file[1]) != -2) {
            return "root"
            } else {
            return file[1]


    def get_dom_name(self, file: Any) -> str:
            if (objectp(file))
            file = file_name(file)
            file = explode(file, "/") - [""]
            if (file[0] == "d" && sizeof(file) >= 2)
            return file[1]


    def get_prg_name(self, file: Any) -> str:
            if (objectp(file))
            file = file_name(file)
            file = explode(file, "/") - [""]
            if (file[0] == "w")
            return file[1]
            return "root"


    def different(self, fn: str, pr: str) -> int:
            sscanf(fn, "%s#%*d", fn)
            fn += ".c"
            return (fn != pr) && (fn != ("/" + pr))


    def trace_line(self, obj: MudObject, prog: str, file: str, line: int) -> str:
            string ret
            string objfn = obj ? file_name(obj) : "<none>"
            ret = objfn
            if (different(objfn, prog))
            ret += sprintf(" (%s)", prog)
            if (file != prog)
            ret += sprintf(" in %s:%d\n", file, line)
            else
            ret += sprintf(" at line %d\n", line)
            return ret


    def printable_arg(self, arg: Any) -> str:
            switch (typeof(arg)) {
            case ARRAY:
            case MAPPING:
            case CLASS:
            case STRING:
            if((strlen(typeof(arg)) + strlen(save_variable(arg)) + 4) <  __MAX_STRING_LENGTH__)
            return "(" + typeof(arg) + ") " + save_variable(arg)
            else
            return sprintf("(%s) <too large>", typeof(arg))
            default:
            return sprintf("(%s) %O", typeof(arg), arg)


    def trace_args(self, args: Any) -> str:
            string *tmp
            if (!sizeof(args))
            return " (void)"
            tmp = map(args, (: printable_arg($1) :))
            return "\n(\n    "+implode(tmp, ",\n    ")+"\n)"


    def trace_locals(self, args: Any) -> str:
            string *tmp
            if (!sizeof(args))
            return " none."
            tmp = map(args, (: printable_arg($1) :))
            return "\n    " + implode(tmp, ",\n    ")


    def error_handler(self, error: Any, caught: int) -> None:
            string file, ret, path, name, obname
            object ob
            ret = "--------------------\n"+ctime(time()) + ":  " + standard_trace(error)
            if (caught) {
            file = "catch"
            } else {
            file = "runtime"


    def log_error(self, file: str, message: str) -> None:
            string name, efile, epath, colour
            if (sscanf(message, "%*sWarning:%*s") == 2) {
            if(sscanf(message, "%*sTrying to put%*s") == 2) {
            efile = "type-error"
            colour = "%^RED%^"
            } else {
            efile = "warnings"
            colour = "%^CYAN%^"


    def do_log(self, person: str, text: str) -> None:
            if (file_name(previous_object()) != "/std/smart_log")
            return
            if (file_size("/w/"+person) != -2)
            return
            unguarded((: rm, "/w/"+person+"/"+PLAYER_ERROR_LOG :))
            unguarded((: write_file, "/w/"+person+"/"+PLAYER_ERROR_LOG, text :))


    def forward_error(self, file: str, text: str) -> None:
            if (!((file_name(previous_object()) == "/secure/cmds/creator/errors") ||
            (file_name(previous_object()) == "/www/secure/errors")))
            return
            unguarded((: write_file, file, text :))



class Logging(MudObject):
