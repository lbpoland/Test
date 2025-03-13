# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/board_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.num = 1
            self.boards = ([ ])
            self.security = ([ ])
            self._read_access_cache = ([ ])
            self.priv = ([ ])
            self.timeouts = ([ ])
            self.archives = ([ ])
            self.message_cache = ([ ])
            self._newsrc_cache = ([ ])
            self._allowed_objects = []
            self._idiots = ([ ])


    def __init__(self):
            self.num = 1
            self.boards = ([ ])
            self.security = ([ ])
            self._read_access_cache = ([ ])
            self.priv = ([ ])
            self.timeouts = ([ ])
            self.archives = ([ ])
            self.message_cache = ([ ])
            self._newsrc_cache = ([ ])
            self._allowed_objects = []
            self._idiots = ([ ])
            lines = unguarded((: get_dir, BACKUPS_DIR +"boards.*" :))
            if ( sizeof( lines ) > 6 ) {
            last = time() - BACKUP_TIME_OUT
            foreach(line in lines) {
            sscanf(line, "boards.%d", number)
            if (number < last)
            unguarded((: rm, BACKUPS_DIR + line :))


    def is_board(self, board: str) -> int:
            if (boards[board]) {
            return 1


    def is_idiot(self, name: str) -> int:
            if (!_idiots) {
            _idiots = ([ ])


    def add_idiot(self, idiot: str, length: int) -> None:
            _idiots[idiot] = time() + (60 * 60 * 24 * length)
            save_me()


    def query_idiot(self, idiot: str) -> int:
            return _idiots[idiot]


    def get_message(self, board: str, num: int, person: str) -> str:
            string name, rname
            if (file_name(previous_object()) == BOARD_WEB) {
            name = person
            } else  if (file_name(previous_object())[0..10] !=
            "/obj/misc/board"[0..10]) {
            name = "unknown"
            } else {
            name = (string)this_player()->query_name()


    def clean_cache(self, ) -> None:
            int i
            int count
            int *list
            string name
            count = sizeof(keys(message_cache))
            list = sort_array(keys(message_cache), 0)
            for(i=0; i < (count - CACHE_SIZE); i++) {
            map_delete(message_cache, list[i])


    def save_me(self, ) -> None:
            unguarded((: save_object, BOARD_FILE, 2 :))


    def add_allowed(self, board: str, name: str) -> int:
            string nam
            int board_type
            board_type = priv[board] & B_PRIV_TYPE_MASK
            if (sscanf(file_name(previous_object()), "/obj/misc/board%s", nam) != 1) {
            return 0


    def remove_allowed(self, board: str, name: str) -> int:
            string nam
            int i
            int board_type
            if (sscanf(file_name(previous_object()), "/obj/misc/board%s", nam) != 1) {
            return 0


    def set_method_access_call(self, board: str, method: str, name: str) -> int:
            string pl
            if (!boards[board] ||
            (priv[board] & B_PRIV_TYPE_MASK) != B_PRIV_ACCESS_RESTRICTED_METHOD) {
            return 0


    def force_board_method_access_restricted(self, board: str) -> int:
            string pl
            if (!boards[board]) {
            return 0


    def delete_message(self, board: str, off: int, override_name: str) -> int:
            string nam
            if (file_name(previous_object()) == "/www/boards") {
            nam = override_name
            } else {
            nam = this_player()->query_name()


    def can_delete_message(self, board: str, off: int, pname: str) -> int:
            if (!boards[board]) {
            return 0


    def delete_board(self, board: str) -> int:
            string nam
            if (!boards[board]) {
            return 0


    def set_timeout(self, board: str, timeout: int) -> int:
            string nam
            if (!boards[board]) {
            return 0


    def set_minimum(self, board: str, min: int) -> int:
            string nam
            if (!boards[board]) {
            return 0


    def set_maximum(self, board: str, max: int) -> int:
            string nam
            if (!boards[board]) {
            return 0


    def set_archive(self, board: str, file: str) -> int:
            string nam
            if (!boards[board]) {
            return 0


    def query_timeout(self, board: str) -> int:
            if (!timeouts[board]) {
            return 0


    def query_minimum(self, board: str) -> int:
            if (!timeouts[board]) {
            return 0


    def query_maximum(self, board: str) -> int:
            if (!timeouts[board]) {
            return 0


    def query_archive(self, board: str) -> str:
            if (!boards[board]) {
            return 0


    def query_restricted_access(self, board: str) -> int:
            return (priv[board] & B_PRIV_TYPE_MASK) == B_PRIV_ACCESS_RESTRICTED


    def query_restricted_access_file(self, board: str) -> int:
            return (priv[board] & B_PRIV_TYPE_MASK) == B_PRIV_ACCESS_RESTRICTED_FILE


    def query_read_only(self, board: str) -> int:
            return (priv[board] & B_PRIV_TYPE_MASK) == B_PRIV_READ_ONLY


    def query_no_inform(self, board: str) -> int:
            return priv[board] & B_PRIV_NO_INFORM


    def query_privilage(self, board: str) -> int:
            return priv[board]


    def expire_boards(self, ) -> None:
            string nam
            int tim, num, *val
            foreach (nam, val in timeouts) {
            num = 0
            if ((tim = val[T_TIMEOUT]) &&
            (sizeof(boards[nam]) > val[T_MIN]) &&
            ((boards[nam][0][B_TIME]+(tim*(24*60*60))) < time())) {
            while (sizeof(boards[nam]) > val[T_MIN] &&
            boards[nam][0][B_TIME]+(tim*24*60*60) < time()) {
            zap_message(nam, 0, 0)
            num++


    def query_prevent_shadow(self, ) -> int:
            return 1


    def query_num(self, ) -> int:
            return num


    def query_cache(self, ) -> None:
            printf("%O\n", sort_array(keys(message_cache), 0))


    def load_newsrc(self, player: str) -> int:
            string fname, board
            _newsrc_reads++
            if(_newsrc_cache[player]) {
            _newsrc_cache_hits++
            return 1


    def flush_newsrc(self, force: int) -> None:
            string fname, player, board, *board_list
            object ob
            board_list = map(keys(boards), (: lower_case($1) :))
            foreach(player in keys(_newsrc_cache)) {
            if(!force && (!_newsrc_cache[player]->changed ||
            (_newsrc_cache[player]->changed > time() - NEWSRC_SAVE_DELAY &&
            !find_object("/obj/shut"))))
            continue
            fname = NEWSRC_SAVE_DIR + player[0..0] + "/" + player + ".o"
            if(unguarded( (: file_size($(fname)) :)) > 0) {
            _newsrc_cache[player]->newsrc =
            filter(_newsrc_cache[player]->newsrc,
            (: $(board_list.index(lower_case($1)) if lower_case($1) in $(board_list else -1) != -1 :))
            if(_newsrc_cache[player]->kill)
            _newsrc_cache[player]->kill =
            filter(_newsrc_cache[player]->kill,
            (: $(board_list.index(lower_case($1)) if lower_case($1) in $(board_list else -1) != -1 :))
            if(_newsrc_cache[player]->board_order)
            _newsrc_cache[player]->board_order =
            filter(_newsrc_cache[player]->board_order,
            (: $(board_list.index(lower_case($1)) if lower_case($1) in $(board_list else -1) != -1 :))
            unguarded( (: write_file($(fname), save_variable(_newsrc_cache[$(player)]),
            1) :))
            } else if(ob = find_player(player)) {
            unguarded( (: write_file($(fname),
            save_variable(_newsrc_cache[$(player)]), 1) :))
            ob.remove_property(NEWS_RC)
            ob.remove_property(BOARD_ORDER)
            foreach(board in keys(boards)) {
            ob.remove_property("news_kill_" + lower_case(board))


    def set_newsrc(self, player: str, newsrc: Any) -> int:
            if(!load_newsrc(player))
            return 0
            _newsrc_cache[player]->newsrc = (mapping)newsrc
            _newsrc_cache[player]->cached = time()
            _newsrc_cache[player]->changed = time()
            if(find_asyncio.create_task(self."flush_newsrc") == -1)
            asyncio.create_task(self."flush_newsrc", NEWSRC_SAVE_DELAY)
            return 1


    def query_killfile(self, player: str, board: str) -> int:
            if(!load_newsrc(player))
            return 0
            _newsrc_cache[player]->cached = time()
            return _newsrc_cache[player]->kill.index(board) if board in _newsrc_cache[player]->kill else -1 != -1


    def set_killfile(self, player: str, board: str) -> int:
            if(!load_newsrc(player))
            return 0
            if(_newsrc_cache[player]->kill.index(board) if board in _newsrc_cache[player]->kill else -1 != -1)
            return 1
            _newsrc_cache[player]->kill += [board]
            _newsrc_cache[player]->changed = time()
            _newsrc_cache[player]->cached = time()
            if(find_asyncio.create_task(self."flush_newsrc") == -1)
            asyncio.create_task(self."flush_newsrc", NEWSRC_SAVE_DELAY)
            return 1


    def remove_killfile(self, player: str, board: str) -> int:
            if(!load_newsrc(player))
            return 0
            if(_newsrc_cache[player]->kill.index(board) if board in _newsrc_cache[player]->kill else -1 == -1)
            return 1
            _newsrc_cache[player]->kill -= [board]
            _newsrc_cache[player]->changed = time()
            _newsrc_cache[player]->cached = time()
            if(find_asyncio.create_task(self."flush_newsrc") == -1)
            asyncio.create_task(self."flush_newsrc", NEWSRC_SAVE_DELAY)
            return 1


    def set_board_order(self, player: str, new_order: str) -> int:
            if(!load_newsrc(player))
            return 0
            _newsrc_cache[player]->board_order = new_order
            _newsrc_cache[player]->changed = time()
            _newsrc_cache[player]->cached = time()
            if(find_asyncio.create_task(self."flush_newsrc") == -1)
            asyncio.create_task(self."flush_newsrc", NEWSRC_SAVE_DELAY)
            return 1


    def dest_me(self, ) -> None:
            flush_newsrc(1)
            destruct(self)



class Board_handler(MudObject):

    num = 1

    boards = '([ ])'

    security = '([ ])'

    _read_access_cache = '([ ])'

    priv = '([ ])'

    timeouts = '([ ])'

    archives = '([ ])'

    message_cache = '([ ])'

    _newsrc_cache = '([ ])'

    _allowed_objects = '[]'

    _idiots = '([ ])'
