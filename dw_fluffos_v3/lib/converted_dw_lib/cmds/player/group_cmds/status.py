# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/status.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_group_status(self, verbose: str, group: str) -> int:
            int use_verbose
            switch( verbose ) {
            case "default":
            use_verbose = this_player()->query_verbose( "score" )
            break
            case "verbose":
            use_verbose = 1
            break
            case "brief":
            use_verbose = 0
            break
            default:
            return notify_fail( "[ERROR]: Unknown return value from verbose information.\n" )


    def display_verbose_group_status(self, group: str) -> int:
            int size, cols
            object member, *members, *assisting
            string pronoun, message, status, short, colour, idle
            cols = this_player()->query_cols()
            short = GROUP.query_party_short( party )
            colour = this_player()->colour_event( GROUP_COLOUR_EVENT, "" )
            message = "\n"
            message += sprintf( "   %'+'*|s\n", cols - 3, "|" + short + "|" )
            size = sizeof( message ) - 3
            message = replace( message, [short, ( colour + short +
            "%^RESET%^" )] )
            message += "\n"
            message += sprintf( "%' '*|s\n",
            cols - 3,
            "The party was started on " +
            ctime( GROUP.query_start_time( party ) ) + "." )
            message += "\n"
            members = GROUP.members_of( party )
            message += sprintf( "   %-=*s\n\n",
            size, "The party has %^BOLD%^" + query_num( sizeof( members ) ) +
            "%^RESET%^ " + ( sizeof( members ) > 1 ? "members" : "member" ) +
            ":" )
            if (!members) {
            message += "Very unhappy party.\n"
            } else {
            foreach( member in members ) {
            if(!member)
            continue
            status = "$I$+8,+0=   " + colour
            status += capitalize( member.query_cap_name() ) + "%^RESET%^" +
            " is " + generate_status_message( member ) + "  "
            pronoun = member.query_pronoun()
            idle = calc_idle_string( member )
            if( idle ) {
            status += "  %^BOLD%^" + idle + ".%^RESET%^"


    def display_brief_group_status(self, group: str) -> int:
            object member, *others
            string message, colour, idle
            int my_gp, my_hp, my_max_hp, my_max_gp
            message = ""
            colour = this_player()->colour_event( GROUP_COLOUR_EVENT, "" )
            others = GROUP.members_of( party ) - [this_player()]
            my_hp = this_player()->query_hp()
            my_gp = this_player()->query_gp()
            my_max_hp = this_player()->query_max_hp()
            my_max_gp = this_player()->query_max_gp()
            message += colour
            message += capitalize( this_player()->query_cap_name() )
            message += "%^RESET%^; Hp: " + convert_percentage_to_colour( my_hp * 100 / my_max_hp ) +
            my_hp + "/" + my_max_hp + "%^RESET%^ Gp: " +
            convert_percentage_to_colour( my_gp * 100 / my_max_gp ) +
            my_gp + "/" + my_max_gp + "%^RESET%^.\n"
            foreach( member in others ) {
            if(!member)
            continue
            message += colour
            message += capitalize( member.query_cap_name() )
            message += "%^RESET%^ is " + generate_status_message( member )
            idle = calc_idle_string( member )
            if( idle ) {
            message += "  (" + idle + ")"


    def calc_idle_string(self, player: MudObject) -> str:
            int idle
            if( !interactive( player ) ) {
            return "Net Dead"


    def generate_status_message(self, player: MudObject) -> str:
            int hp_percentage, gp_percentage
            hp_percentage = player.query_hp() * 100 / player.query_max_hp()
            gp_percentage = player.query_gp() * 100 / player.query_max_gp()
            return (
            convert_percentage_to_colour( hp_percentage ) +
            convert_percentage_to_hp_message( hp_percentage ) +
            "%^RESET%^ and " +
            convert_percentage_to_colour( gp_percentage ) +
            convert_percentage_to_gp_message( gp_percentage ) +
            "%^RESET%^." )


    def query_help_string_for(self, sub_command: str) -> str:
            return "The status sub-command displays vital statistics "
            "of your party's members.  Depending on your brief "
            "settings for \"score\", the command will either "
            "show the verbose statistics or prompt a brief "
            "display.  You can also force either version by "
            "adding the argument \"verbose\" or \"brief\"."


    def convert_percentage_to_colour(self, percentage: int) -> str:
            switch( percentage ) {
            case -1000..10: return "%^BOLD%^%^RED%^"
            case 11..20:    return "%^RED%^"
            case 21..30:    return "%^ORANGE%^"
            case 31..40:    return "%^YELLOW%^"
            case 41..50:    return "%^MAGENTA%^"
            case 51..60:    return "%^CYAN%^"
            case 61..70:    return "%^BOLD%^%^CYAN%^"
            case 71..80:    return "%^GREEN%^"
            case 81..90:    return "%^BOLD%^%^GREEN%^"
            case 91..100:   return "%^BOLD%^%^WHITE%^"
            default:        return ""


    def convert_percentage_to_hp_message(self, percentage: int) -> str:
            switch( percentage ) {
            case -1000..0: return "perfectly healthy, for a ghost"
            case 1..5:     return "near death"
            case 6..10:    return "critically wounded"
            case 11..20:   return "seriously wounded"
            case 21..30:   return "heavily wounded"
            case 31..40:   return "badly wounded"
            case 41..50:   return "wounded"
            case 51..60:   return "slightly wounded"
            case 61..70:   return "injured"
            case 71..80:   return "slightly injured"
            case 81..89:   return "slightly hurt"
            case 90..94:   return "scratched"
            case 95..99:   return "almost unhurt"
            case 100:      return "unhurt"
            default:       return "ERROR"


    def convert_percentage_to_gp_message(self, percentage: int) -> str:
            switch( percentage ) {
            case 0..10:    return "near unconscious"
            case 11..20:   return "severely fatigued"
            case 21..30:   return "highly fatigued"
            case 31..40:   return "very fatigued"
            case 41..50:   return "fatigued"
            case 51..60:   return "slightly fatigued"
            case 61..70:   return "confused"
            case 71..80:   return "slightly confused"
            case 81..90:   return "concentrated"
            case 91..99:   return "clear of mind"
            case 100:      return "refreshed"
            default:       return "ERROR"


    def convert_percentage_to_share_message(self, percentage: int) -> str:
            switch( percentage ) {
            case 100:       return "all"
            case 95..99:    return "almost all"
            case 90..94:    return "a very large portion"
            case 80..89:    return "a large portion"
            case 70..79:    return "a major portion"
            case 60..69:    return "an above average portion"
            case 52..59:    return "a slightly above average portion"
            case 49..51:    return "an average portion"
            case 41..48:    return "a slightly below average portion"
            case 31..40:    return "a below average portion"
            case 21..30:    return "a minor portion"
            case 11..20:    return "a small portion"
            case 6..10:     return "a very small portion"
            case 1..5:      return "a miniscule portion"
            case 0:         return "next to none"
            default:        return "an ERRONEOUS portion "



class Status(MudObject):
