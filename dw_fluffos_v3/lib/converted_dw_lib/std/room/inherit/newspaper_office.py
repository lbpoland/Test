# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/newspaper_office.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._reporters = ([ ])
            self._editors = []
            self._payees = ([ ])
            self._articles = []
            self._category = ([ ])
            self._adverts = []
            self._setters = []
            self._sponsors = []
            self._next_article_num = 2


    def __init__(self):
            self._reporters = ([ ])
            self._editors = []
            self._payees = ([ ])
            self._articles = []
            self._category = ([ ])
            self._adverts = []
            self._setters = []
            self._sponsors = []
            self._next_article_num = 2
            protected void save_me()
            {
            if (_save_dir && !_proxy) {
            unguarded( (: save_object(_save_dir + "main") :) )


    def set_save_directory(self, dir: str) -> None:
            if (dir[<1] != '/') {
            dir += "/"


    def save_article_text(self, our_article: Any, text: str) -> None:
            if (a_type(art->art->type) != NEWSPAPER_ARTICLE_TYPE_HTML &&
            a_type(art->art->type) != NEWSPAPER_ARTICLE_TYPE_PLAIN) {
            return


    def load_article_text(self, our_article: Any) -> str:
            mixed* bits
            string str
            str = unguarded( (: read_file(_save_dir + $(art->art->file_name)) :) )
            if (str) {
            bits = restore_variable(str)
            return bits[1]


    def load_article_text_by_file(self, fname: str) -> str:
            int i
            for (i = 0; i < sizeof(_articles); i++) {
            if (_articles[i]->art->file_name == fname) {
            return load_article_text(_articles[i])


    def save_article_text_by_file(self, fname: str, text: str) -> None:
            int i
            for (i = 0; i < sizeof(_articles); i++) {
            if (_articles[i]->art->file_name == fname) {
            update_article_info(_articles[i], text)
            return save_article_text(_articles[i], text)


    def set_article_title_by_file(self, fname: str, title: str) -> None:
            int i
            for (i = 0; i < sizeof(_articles); i++) {
            if (_articles[i]->art->file_name == fname) {
            _articles[i]->art->title = title
            save_me()
            return


    def delete_article(self, our_article: Any) -> None:
            unguarded( (: rm(_save_dir + $(article->art->file_name)) :) )
            unguarded( (: rm(_save_dir + $(article->art->file_name) + ".proc" ) :) )
            unguarded( (: rm(_save_dir + $(article->art->file_name) + ".nroff.o" ) :) )


    def query_article_index(self, match: str) -> int:
            int index
            match = lower_case(match)
            if (strlen(match) && (match[0] >= '0' && match[0] <= '9')) {
            sscanf(match, "%d", index)
            index--
            if (index < 0 || index >= sizeof(_articles)) {
            return -1


    def query_category(self, category: str) -> str:
            string name
            category = lower_case(category)
            foreach (name in keys(_category)) {
            if (lower_case(name) == category ||
            lower_case(name)[0..strlen(category) - 1] == category) {
            return name


    def query_log_file_name(self, ) -> str:
            return _save_dir + "event.log"


    def query_article_log_file_name(self, ) -> str:
            return _save_dir + "aritcle.log"


    def query_current_edition(self, ) -> int:
            {
            return NEWSPAPER_HANDLER.query_current_edition_num(query_paper_name())


    def query_paper_name(self, ) -> str:
            {
            return _paper_name


    def query_the_paper_name(self, ) -> str:
            {
            if (lower_case(_paper_name[0..3]) == "the") {
            return _paper_name


    def set_paper_name(self, name: str) -> str:
            {
            _paper_name = name


    def query_next_article_file_name(self, ) -> str:
            {
            while (file_size(_save_dir + _next_article_num + ".txt") != -1) {
            _next_article_num++


    def query_bank_branch(self, ) -> str:
            {
            return _bank_branch


    def set_bank_branch(self, bank: str) -> None:
            _bank_branch = bank


    def do_apply(self, ) -> int:
            {
            if (_proxy) {
            return _proxy.do_apply()


    def mail_application(self, text: str) -> int:
            {
            string word
            string *eds
            if (!text) {
            await this_player().send("You decide not to apply just yet.\n")
            return 0


    def part_two(self, str: str, author: str, html: int) -> int:
            {
            if (!sizeof(str)) {
            await this_player().send("The article must have a name!\n")
            tell_room(self, this_player()->the_short() +
            " stops writing to think of a name.\n",
            this_player())
            return 0


    def do_submit(self, str: str, author: str, html: int) -> int:
            {
            if (_proxy) {
            return _proxy.do_submit(str, author, html)


    def do_retrieve(self, edn: str, source: int) -> int:
            {
            class our_article article
            if (_proxy) {
            return _proxy.do_retrieve(edn, source)


    def show_article(self, our_article: Any, source: int) -> int:
            {
            string text
            mixed* bits
            int i
            mixed* stuff
            class advert data
            switch (a_type(article->art->type)) {
            case NEWSPAPER_ARTICLE_TYPE_SECTION :
            text = "%^BOLD%^" + article->art->title + "%^RESET%^\n\n"
            for (i = 0; i < sizeof(_articles); i++) {
            if (_articles[i] == article) {
            i++
            break


    def do_logs(self, article_log: int) -> int:
            {
            string logfile
            if (_proxy) {
            return _proxy.do_logs(article_log)


    def do_articles(self, scroll: int) -> int:
            {
            string str
            class our_article article
            int pos
            int editor
            if (_proxy) {
            return _proxy.do_articles(scroll)


    def do_resign(self, ) -> int:
            {
            object *inv
            object ob
            string person
            if (_proxy) {
            return _proxy.do_resign()


    def do_delete(self, str: str) -> int:
            {
            class our_article article
            int i
            if (_proxy) {
            return _proxy.do_delete(str)


    def do_hire(self, person: str, setter: int) -> int:
            {
            string bing
            object thatguy
            if (_proxy) {
            return _proxy.do_hire(person, setter)


    def do_dismiss(self, person: str) -> int:
            {
            object thatguy
            if (_proxy) {
            return _proxy.do_dismiss(person)


    def do_sponsor_add(self, person: str) -> int:
            {
            if (_proxy) {
            return _proxy.do_sponsor_add(person)


    def do_sponsor_remove(self, person: str) -> int:
            {
            if (_proxy) {
            return _proxy.do_sponsor_remove(person)


    def do_promote(self, person: str) -> int:
            {
            object thatguy
            if (_proxy) {
            return _proxy.do_promote(person)


    def do_demote(self, person: str, editor: int) -> int:
            {
            object thatguy
            if (_proxy) {
            return _proxy.do_demote(person, editor)


    def do_everyone_status(self, ) -> int:
            string ret
            if (_proxy) {
            return _proxy.do_everyone_status()


    def do_status(self, ) -> int:
            {
            string ret
            int i
            int last_num
            if (_proxy) {
            return _proxy.do_status()


    def do_claim(self, ) -> int:
            {
            object badge
            object *deepinv
            object *inv
            if (_proxy) {
            return _proxy.do_claim()


    def do_publish(self, headline: str) -> int:
            {
            class our_article* bing
            if (_proxy) {
            return _proxy.do_publish(headline)


    def query_total_profit(self, num_articles: int) -> int:
            int last_pub
            int amount
            int edition
            int adds
            class advert data
            class our_article bing
            string text
            if (num_articles == -1) {
            num_articles = 0
            foreach (bing in _articles) {
            if (!(bing->flags & NEWSPAPER_POSTPONE_FLAG)) {
            text = load_article_text(bing)
            if (strlen(text) > 500) {
            num_articles++


    def really_publish(self, char: str, headline: str) -> None:
            {
            int article_count
            int amount
            int total
            string *things
            string temp
            class article* to_publish
            string* text
            class our_article bing
            class payee_data data
            string stuff
            string place
            int i
            int editor_bonus
            int num_editors
            place = query_property("place")
            char = lower_case(char)
            things = [})
            if (strlen(char) && char[0] == 'y') {
            tell_object(this_player(),
            "Okay, warm up the frogs, let's see if everything is "
            "sorted out.\n")
            } else {
            await this_player().send("Okay, publishing aborted.\n")
            return 0


    def do_summary(self, ) -> int:
            int amount
            int adds
            string person
            int total
            class our_article bing
            class payee_data payee_data
            string text
            string ret
            int article_count
            string place
            class advert data
            int i
            int last_num
            int num_editors
            int editor_bonus
            if (_proxy) {
            return _proxy.do_summary()


    def do_deposit(self, amt: str) -> int:
            int amt_int
            string place
            if (_proxy) {
            return _proxy.do_deposit(amt)


    def do_set_bank_branch(self, branch: str) -> int:
            {
            string* accounts
            if (_proxy) {
            return _proxy.do_set_bank_branch(branch)


    def do_title(self, id: str, title: str) -> int:
            {
            class our_article art
            if (_proxy) {
            return _proxy.do_title(id, title)


    def do_author(self, id: str, author: str) -> int:
            {
            class our_article art
            if (_proxy) {
            return _proxy.do_author(id, author)


    def do_change(self, id: str, type: str) -> int:
            {
            class our_article art
            if (_proxy) {
            return _proxy.do_change(id, type)


    def do_change_xp(self, id: str, type: str) -> int:
            {
            class our_article art
            if (_proxy) {
            return _proxy.do_change_xp(id, type)


    def do_change_colour(self, id: str, colour: str) -> int:
            {
            class our_article art
            if (_proxy) {
            return _proxy.do_change_colour(id, colour)


    def do_editing(self, id: str) -> int:
            {
            class our_article art
            string contents
            if (_proxy) {
            return _proxy.do_editing(id)


    def move_article(self, index: int, up_down: str) -> int:
            class our_article womble
            if (index == -1) {
            return 0


    def do_move(self, article: str, up_down: str) -> int:
            int index
            class our_article womble
            if (_proxy) {
            return _proxy.do_move(article, up_down)


    def do_move_pos(self, article: str, pos: str) -> int:
            int index
            int to_index
            class our_article womble
            if (_proxy) {
            return _proxy.do_move_pos(article, pos)


    def do_postpone(self, id: str, on_off: str) -> int:
            class our_article art
            if (_proxy) {
            return _proxy.do_postpone(id, on_off)


    def do_lock_article(self, id: str, on_off: str) -> int:
            class our_article art
            if (_proxy) {
            return _proxy.do_lock_article(id, on_off)


    def do_category_list(self, ) -> int:
            string ret
            string place
            string name
            class category_data data
            if (_proxy) {
            return _proxy.do_category_list()


    def do_advert_list(self, ) -> int:
            string ret
            string place
            class advert data
            int editor
            int found
            int pos
            if (_proxy) {
            return _proxy.do_advert_list()


    def do_advert_remove(self, id: int) -> int:
            class advert fluff
            if (_proxy) {
            return _proxy.do_advert_remove(id)


    def do_category_remove(self, category: str) -> int:
            if (_proxy) {
            return _proxy.do_category_remove(category)


    def do_category_add(self, category: str) -> int:
            string new_category
            if (_proxy) {
            return _proxy.do_category_add(category)


    def do_category_open(self, category: str, open: str) -> int:
            if (_proxy) {
            return _proxy.do_category_open(category, open)


    def do_category_cost(self, category: str, cost: str) -> int:
            int value
            string place
            if (_proxy) {
            return _proxy.do_category_cost(category, cost)


    def do_category_cost_per_ten_chars(self, category: str, cost: str) -> int:
            int value
            string place
            if (_proxy) {
            return _proxy.do_category_cost_per_ten_chars(category, cost)


    def do_submit_section(self, name: str) -> int:
            class our_article cur_art
            if (_proxy) {
            return _proxy.do_submit_section(name)


    def do_submit_add(self, category: str) -> int:
            if (_proxy) {
            return _proxy.do_submit_add(category)


    def do_lock(self, locked: int) -> int:
            if (_proxy) {
            return _proxy.do_lock(locked)


    def finish_add(self, str: str, category: str) -> None:
            int value
            string place
            if (!str || !strlen(str)) {
            write("Ok, Aborted writing an add.\n")
            return


    def confirm_add(self, str: str, text: str, category: str, value: int) -> None:
            class advert add
            string place
            int found
            class our_article bing
            if (!str || !strlen(str)) {
            return 0


    def finish_editing(self, story: str, our_article: Any) -> int:
            {
            if (!story) {
            await this_player().send("Ok, no editing saved.\n")
            return 0


    def do_transfer_ownership(self, new_owner: str) -> int:
            int value
            string place
            if (!is_owner(this_player()->query_name())) {
            add_failed_mess("You must be the owner to transfer the ownership.\n")
            return 0


    def check_transfer(self, test: str, new_owner: str, value: int) -> None:
            string place
            test = lower_case(test)
            if (!strlen(test) || test[0] != 'y') {
            write("Aborted.\n")
            return 0


    def is_postponed(self, article: Any) -> int:
            class our_article rabbit
            foreach (rabbit in _articles) {
            if (rabbit->art->file_name == art->file_name) {
            return rabbit->flags & NEWSPAPER_POSTPONE_FLAG


    def is_locked(self, article: Any) -> int:
            class our_article rabbit
            foreach (rabbit in _articles) {
            if (rabbit->art->file_name == art->file_name) {
            return rabbit->flags & NEWSPAPER_LOCK_FLAG


    def is_reporter(self, word: str) -> int:
            {
            if (_proxy) {
            return _proxy.is_reporter(word)


    def is_setter(self, word: str) -> int:
            {
            if (_proxy) {
            return _proxy.is_setter(word)


    def is_sponsor(self, word: str) -> int:
            {
            if (_proxy) {
            return _proxy.is_sponsor(word)


    def is_editor(self, word: str) -> int:
            {
            if (_proxy) {
            return _proxy.is_editor(word)


    def is_owner(self, word: str) -> int:
            {
            if (_proxy) {
            return _proxy.is_owner(word)


    def add_reporter(self, word: str) -> None:
            {
            if (!_reporters[word]) {
            _reporters[word] = new(class reporter)
            _reporters[word]->date_added = time()
            update_commands(word)
            save_me()


    def add_sponsor(self, word: str) -> None:
            {
            if (!is_sponsor(word)) {
            _sponsors += [word]
            update_commands(word)
            save_me()


    def add_setter(self, word: str) -> None:
            {
            if (!is_setter(word)) {
            if (!is_reporter(word)) {
            add_reporter(word)


    def add_editor(self, word: str) -> None:
            {
            if (!is_editor(word)) {
            if (!is_reporter(word)) {
            add_reporter(word)


    def remove_reporter(self, word: str) -> None:
            {
            if (!is_reporter(word)) {
            return


    def remove_editor(self, word: str) -> None:
            {
            if (!is_editor(word)) {
            return


    def remove_setter(self, word: str) -> None:
            {
            if (!is_setter(word)) {
            return


    def remove_sponsor(self, word: str) -> None:
            {
            if (!is_sponsor(word)) {
            return


    def update_commands(self, word: str) -> None:
            {
            object player
            player = find_player(word)
            if (player && environment(player) == self) {
            player.move("/room/void")
            player.move(file_name(self))


    def query_owner(self, ) -> str:
            if (_proxy) {
            return _proxy.query_owner()


    def set_owner(self, person: str) -> None:
            _owner = person
            save_me()


    def ownership_change(self, old_owner: str, new_owner: str) -> None:
            set_owner(new_owner)


    def set_proxy(self, proxy: str) -> None:
            _proxy = proxy


    def query_proxy(self, ) -> str:
            return _proxy


    def board_access_check(self, type: int, board: str, previous: MudObject, name: str) -> int:
            switch (type) {
            case B_ACCESS_READ :
            return is_reporter(lower_case(name))
            case B_ACCESS_WRITE :
            return is_reporter(lower_case(name))
            case B_ACCESS_DELETE :
            return is_editor(name)


    def init(self, ) -> None:
            {
            string person
            person = this_player()->query_name()
            add_command("advert", "categories", (: do_category_list() :))
            add_command("advert", "list", (: do_advert_list() :))
            add_command("category", "list", (: do_category_list() :))
            add_command("submit", "advert {in|to|into} <string'category'>",
            (: do_submit_add($4[1]) :))
            add_command("submit", "advert <string'category'>",
            (: do_submit_add($4[0]) :))
            if (!is_editor(person) && !is_reporter(person) && !is_setter(person)) {
            add_command("apply", "", (: do_apply() :))
            add_command("status", "", (: do_everyone_status() :))
            return



class Newspaper_office(MudObject):

    _reporters = '([ ])'

    _editors = '[]'

    _payees = '([ ])'

    _articles = '[]'

    _category = '([ ])'

    _adverts = '[]'

    _setters = '[]'

    _sponsors = '[]'

    _next_article_num = 2
