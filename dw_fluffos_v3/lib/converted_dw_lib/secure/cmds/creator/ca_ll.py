# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/ca_ll.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            mixed *args, file, f
            mixed retobj
            string *s, s1, s2
            string fn,os, obvarname
            string *argv
            object *ov
            object fish, shad, ob
            notify_fail("USAGE : call [obvar=]lfun(arg[,arg[,arg...]]) object[s]\n")
            if (!str)
            return 0
            obvarname = (string)0
            sscanf(str, "%s=%s", obvarname, str)
            s = explode("&"+str+"&", ")")
            if (sizeof(s) < 2 || sscanf(s[0], "%s(%s", s1, s2) != 2)
            return 0
            fn = replace(s1[1..], " ", "")
            s[0] = s2
            args = PARSER.parse_args(implode(s, ")"), ")")
            if (!args) return 1
            argv = args[0]
            os = args[1][0..<2]
            while (strlen(os) && os[0] == ' ')
            os = os[1..]
            notify_fail("Can't find object "+os+".\n")
            ov = WIZ_PRESENT.wiz_present(os, this_player())
            ov = filter( ov, (: reference_allowed( $1, $( this_player() ) ) :) )
            if (!sizeof(ov)) return 0
            if (sizeof(argv) < 6) argv += allocate(6 - sizeof(argv))
            foreach (ob in ov) {
            fish = ob
            while (shad = shadow(fish, 0)) {
            fish = shad
            if (f = function_exists(fn, fish)) file = f



class Ca_ll(MudObject):
