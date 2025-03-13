# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/cmr_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def save_cmr_handler(self, ) -> None:
            unguarded((: save_object, SAVE_FILE :))


    def __init__(self):
            self.colour_names = []
            self.colour_details = ([ ])
            self.material_names = []
            self.material_details = ([ ])


    def delete_colour(self, word: str) -> int:
            int temp
            temp = colour_names .index( word) if  word in colour_names  else -1
            if ( temp == -1 ) return 0
            colour_names -= [word]
            colour_details = m_delete( colour_details, word )
            save_cmr_handler()
            return 1


    def identify_colour(self, word: str, player: MudObject) -> str:
            int temp, *args
            temp = colour_names .index( word) if  word in colour_names  else -1
            if ( temp == -1 )
            return "unknown colour"
            args = allocate( 4 )
            args = colour_details[word]
            if ( !player )
            return word
            switch ( ( ( LIBRARY.query_quest_points(player->query_name()) ) > args[2] )+
            ( ( player.query_max_gp() ) > args[3] ) ) {
            case 0:
            return COLOURS[args[1]]
            case 1:
            return ( ( ( args[0] == args[1] )?"pure ":MODIFIERS[args[0]] ) +
            COLOURS[args[1]] )
            default:
            return word


    def delete_material(self, word: str) -> int:
            int temp
            temp = material_names .index( word) if  word in material_names  else -1
            if ( temp == -1 ) return 0
            material_names -= [word]
            material_details = m_delete( material_details, word )
            save_cmr_handler()
            return 1


    def identify_material(self, word: str, player: MudObject, article: int) -> str:
            int temp, *args
            string prefix
            temp = material_names .index( word) if  word in material_names  else -1
            if ( temp == -1 ) return "unknown material"
            args = allocate( 4 )
            args = material_details[word]
            prefix = ( ( article )?"a"+ ( ( args[0] == COL_ORANGE )?"n ":" " ):"" )
            if ( !args[ 2 ] || !player )
            return word
            if ( args[2] == LEARNT )
            if ( member_array( word,
            (string *)CMR_LIBRARY.query_known_materials( player->query_name() ) )
            == -1 )
            return prefix + COLOURS[ args[ 0 ] ] +" "+
            MATERIALS[ args[ 1 ] ]
            else
            return word
            if ( ( player.query_skill_bonus( SKILLS[args[2]] ) ) > args[3] )
            return word
            else return prefix + COLOURS[args[0]] +" "+ MATERIALS[args[1]]


    def query_material_adjective(self, word: str) -> str:
            int temp, *args
            temp = material_names .index( word) if  word in material_names  else -1
            if ( temp == -1 ) return "an unknown material"
            args = allocate( 4 )
            args = material_details[word]
            return COLOURS[args[0]] +" "+ MATERIAL_ADJECTIVES[args[1]]


    def query_material_ansi_colour(self, word: str) -> str:
            int temp, *args
            temp = material_names .index( word) if  word in material_names  else -1
            if ( temp == -1 ) return ""
            args = allocate( 4 )
            args = material_details[word]
            return ANSI_COLOURS[args[0]]



class Cmr_handler(MudObject):

    colour_names = '[]'

    colour_details = '([ ])'

    material_names = '[]'

    material_details = '([ ])'
