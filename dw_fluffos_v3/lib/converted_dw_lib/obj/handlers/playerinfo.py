# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/playerinfo.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def fix_alts(self, player: Any) -> None:
            class source {
            string *add
            string *delete


    def save_handler_data(self, ) -> None:
            mapping vars = ([ ])
            string tmp
            vars["alerts"] = _alerts
            tmp = save_variable( vars )
            unguarded( (: write_file, SAVE_FILE, tmp, 1 :) )


    def load_handler_data(self, ) -> None:
            mapping vars
            string tmp
            if( file_size( SAVE_FILE ) <= 0 )
            return
            tmp = unguarded( (: read_file, SAVE_FILE :) )
            vars = restore_variable( tmp )
            _alerts = vars["alerts"]


    def __init__(self):
            self._sources = ([
            self._alerts = ([ ])
            self._lordonly = []
            self._dossier_cache = ([ ])
            self._dossier_cache_hits = 0
            self._dossier_total = 0


    def query_name(self, ) -> str:
            return "playerinfo handler"


    def query_source_ok(self, event: str, source: str) -> int:
            string *reqd
            reqd = _sources[event]->add
            if(reqd == 0) {
            return 1


    def player_remove(self, player: str) -> None:
            string alt, new_main
            string * alts
            if ( !player ) {
            return


    def delete_entry(self, creator: MudObject, player: str, event: str, n: int) -> int:
            int idx = n - 1
            class dbentry * data
            class dbentry fluff
            if( !query_can_delete( event, creator ) )
            return 0
            if( !query_deleter_ok( event, previous_object() ) )
            return 0
            load_player(player)
            if( ( idx < 0 ) || ( idx >= sizeof( dossier->data ) ) )
            return 0
            fluff =  dossier->data[idx]
            if( fluff->event != event )
            return 0
            data = copy( dossier->data )
            data = data[0 .. (idx - 1)] + data[(idx + 1) .. <1]
            dossier->data = data
            save_player(player)
            log_file("DELETE", ctime(time()) + ": " + event + " added by " +
            fluff->creator + "\n")
            if( event == "alert" )
            decrement_alerts_for(player)
            return 1


    def query_event(self, source: MudObject, player: str, event: str) -> str:
            int             i
            class dbentry   *list
            string          str
            load_player(player)
            str = query_header(player)
            list = dossier->data
            for( i = 0; i < sizeof(list); i++ ) {
            if( list[i]->event == event )
            str += query_entry( i, list[i], 0 )


    def query_interleaved(self, source: MudObject, player: str, event: str) -> str:
            class playerinfo * dossiers
            class dbentry * stuff
            string str
            string * alts
            int i, size, done, earliest, earliestt, count
            int * earliests
            load_player(player)
            if( dossier->main_alt ) {
            player = dossier->main_alt
            load_player(player)


    def query_alt_of(self, player: str) -> str:
            if(!PLAYER_HANDLER.test_user(player))
            return 0
            load_player(player)
            return dossier->main_alt


    def add_alt(self, creator: MudObject, player: str, alt: str) -> str:
            class dbentry new_entry
            int is_deleted
            string *alts, tmp
            if((base_name(previous_object()) != "/cmds/player/register") &&
            !query_can_handle_alts(this_player()))
            return "You are not allowed to add players' alts.\n"
            alt = lower_case(alt)
            if(!find_player(alt) && !PLAYER_HANDLER.test_user(alt)) {
            if(!creator)
            return "No such player: " + capitalize(alt) + ".\n"
            if(file_size(filename(alt)) == -1)
            return "No such player and no record for: " + capitalize(alt) + ".\n"
            is_deleted = 1


    def delete_alt(self, creator: MudObject, player: str, alt: str) -> str:
            string ret
            class dbentry new_entry
            if(!query_can_handle_alts(this_player()))
            return "You are not allowed to delete players' alts.\n"
            player = lower_case(player)
            alt = lower_case(alt)
            load_player(player)
            if(!dossier->alts || dossier->alts.index(alt) if alt in dossier->alts else -1 == -1)
            ret = capitalize(alt) + " was not an alt of " + capitalize(player)
            else {
            dossier->alts -= [alt]
            new_entry = new(class dbentry,
            time:       time(),
            creator:    capitalize(creator.query_name()),
            event:      "register",
            comment:    "Removed " + capitalize(alt) + " as an alt.\n",
            extra:      0)
            do_debouncing(alt, new_entry)
            save_player(player)


    def query_alerts_for(self, player: str) -> int:
            player = lower_case(player)
            if( !_alerts ) {
            _alerts = ([ ])


    def is_alert(self, player: str, idx: int) -> int:
            load_player( player )
            if( sizeof(dossier->data) < idx ) {
            return 0


    def clear_alerts_for(self, player: str) -> None:
            player = lower_case(player)
            if( !_alerts ) {
            _alerts = ([ ])


    def increment_alerts_for(self, player: str) -> int:
            player = lower_case(player)
            if( !_alerts ) {
            _alerts = ([ ])


    def decrement_alerts_for(self, player: str) -> int:
            player = lower_case(player)
            if( !_alerts ) {
            _alerts = ([ ])


    def reregister_parent(self, player: str) -> None:
            string main
            string * alts
            if ( !player ) {
            return


    def player_refreshed(self, player: Any, totally: int) -> None:
            class dbentry new_entry
            string comment
            if(objectp(player))
            player = player.query_name()
            switch (totally) {
            case PARTIAL_REFRESH:
            comment = "They did a partial refresh."
            break
            case TOTAL_REFRESH:
            comment = "They did a total and complete refresh.  (Even refreshed their "
            "breath)"
            break
            default:
            comment = "They did some weird sort of unknown refresh."
            break


    def player_deleted(self, player: Any, deleted: int) -> None:
            class dbentry new_entry
            string *tmp, *tmp2, alt, main
            if(objectp(player))
            player = player.query_name()
            if(file_size(filename(player)) == -1)
            return
            clear_alerts_for(player)
            load_player(player)
            new_entry = new(class dbentry,
            time:       time(),
            creator:    "Refresh Handler",
            event:      "delete",
            comment:    "Player deleted",
            extra:      0)
            do_debouncing(player, new_entry)
            save_player(player)
            if(dossier->main_alt) {
            main = dossier->main_alt
            dossier->main_alt = 0
            save_player(player)
            load_player(main)
            dossier->alts -= [player]
            dossier->old_alts += [player]
            save_player(main)
            return


    def player_created(self, player: str) -> None:
            if(file_size(filename(player)) == -1)
            return
            load_player(player)
            if(dossier->main_alt) {
            dossier->main_alt = 0
            dossier->alts = [})
            save_player(player)


    def fix_alts(self, player: Any) -> None:
            string *alts, alt, main
            if(objectp(player))
            player = player.query_name()
            if(file_size(filename(player)) == -1)
            return
            load_player(player)
            if(dossier->main_alt) {
            main = dossier->main_alt
            load_player(dossier->main_alt)
            if(!PLAYER_HANDLER.test_user(dossier->main_alt)) {
            if(sizeof(alts))
            main = alts[0]


    def reset(self, ) -> None:
            if ( sizeof( _dossier_cache ) > CACHE_SIZE ) {
            _dossier_cache = ([ ])


    def query_access_history(self, player: str) -> str:
            mapping history
            string ret = ""
            load_player(player)
            history = dossier->access_log
            ret += sprintf( "Access log for player %s:\n", capitalize( player ) )
            foreach( string name in sort_array( keys( history ),
            (: $(history)[$2] - $(history)[$1] :) ))
            ret += sprintf( "%12s:\t%s.\n", capitalize(name),
            query_time_string( time() - history[name], 2 ) + " ago")
            return ret



class Playerinfo(MudObject):

    _sources = '(['

    _alerts = '([ ])'

    _lordonly = '[]'

    _dossier_cache = '([ ])'

    _dossier_cache_hits = 0

    _dossier_total = 0
