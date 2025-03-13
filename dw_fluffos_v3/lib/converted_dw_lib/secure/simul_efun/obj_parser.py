# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/obj_parser.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._ordinals = ([
            self._counters = ([
            self._fractions = ([


    def __init__(self):
            self._ordinals = ([
            self._counters = ([
            self._fractions = ([
            private void fixup_context(object player,
            object* objects,
            class obj_match_context context) {
            if (!player || !sizeof(objects)) {
            return


    def match_objects_failed_mess(self, obj_match: Any) -> str:
            switch (failed_match->result) {
            case OBJ_PARSER_BAD_ENVIRONMENT :
            return "Cannot find \""+ failed_match->text +
            "\" here, access is not allowed.\n"
            case OBJ_PARSER_NOT_LIVING :
            return "The objects \""+
            query_multiple_short(failed_match->objects) +
            "\" are not living.\n"
            case OBJ_PARSER_TOO_DARK :
            return "Cannot find \""+ failed_match->text +
            "\", it is too dark.\n"
            case OBJ_PARSER_NO_MATCH :
            return "Cannot find \""+ failed_match->text +
            "\", no match.\n"
            case OBJ_PARSER_BAD_FRACTION :
            return "The fraction \""+ failed_match->text +
            "\" is incorrectly specified.\n"
            case OBJ_PARSER_FRACTION :
            return "Can only reference a single object with a "
            "fraction, matched " +
            query_multiple_short(failed_match->objects) +
            " please be more specific.\n"
            case OBJ_PARSER_AMBIGUOUS :
            return "There are multiple matches for \"" + failed_match->text +
            "\".  See 'help parser' for more information on how to "
            "be more specific.\n"
            case OBJ_PARSER_NOT_ENOUGH :
            return "There are not enough \"" + failed_match->text +
            "\" to match as specified.\n"
            default :
            return "Unknow parser errror " + failed_match->result + ".\n"



class Obj_parser(MudObject):

    _ordinals = '(['

    _counters = '(['

    _fractions = '(['
