# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/print_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.letter_cost = DEFAULT_LETTER_COST
            self.time_to_collect = DEFAULT_TIME_TO_COLLECT
            self.time_per_copy = DEFAULT_TIME_PER_COPY
            self.collectables = ([ ])
            self.discount_schedule = ['({ 100', '5 })']
            self.default_language = "common"
            self.translation_costs = ([ ])
            self.print_shop_name = "Rabbits happy little printing press"


    def init(self, ) -> None:
            string languages
            if (!office_room) {
            add_command("print", "<indirect:object>",
            (: do_print($1, default_language) :))
            add_command("print", "<number> [copies] of <indirect:object>",
            (: do_print_copies($1, $4[0], default_language) :) )
            add_command("claim", "copyright on <indirect:object>", (: do_claim :))
            if (sizeof(translation_costs)) {
            languages = implode(keys(translation_costs) + [default_language], "|")
            add_command("print", "<indirect:object> in {" + languages + "}",
            (: do_print($1, $4[1]) :))
            add_command("print", "<number> [copies] of <indirect:object> in "
            "{" + languages + "}",
            (: do_print_copies($1, $4[0], $4[2]) :) )


    def check_for_magic_writing(self, ob: MudObject) -> int:
            mixed *stuff
            int i
            stuff = ob.query_read_mess()
            for (i = 0; i < sizeof(stuff); i++) {
            if (LANGUAGE_HAND.query_language_magic(stuff[i][READ_LANG])) {
            return 1


    def check_for_untranslatable_language(self, ob: MudObject) -> int:
            mixed *stuff
            int i
            string lang
            stuff = ob.query_read_mess()
            for (i = 0; i < sizeof(stuff); i++) {
            lang = stuff[i][READ_LANG]
            if (lang != default_language &&
            !translation_costs[lang]) {
            return 1


    def find_book_or_paper(self, obs: MudObject) -> MudObject:
            object *paper
            object *books
            object *magic
            object *torn_out
            object *nothing
            object ob
            int page
            int old_page
            string owner
            paper = [})
            books = [})
            magic = [})
            torn_out = [})
            nothing = [})
            foreach (ob in obs) {
            owner = copyright_holder(ob)
            if (is_copyright(ob) && owner != this_player()->query_name()) {
            add_failed_mess("$I has been copyrighted by " + owner +
            " and cannot be copied.\n", [ob])
            } else if (ob.query_book()) {
            if (ob.query_spell_book()) {
            magic += [ob]
            } else {
            old_page = ob.query_open_page()
            for (page = 0; page <= ob.query_num_pages(); page++) {
            ob.set_open_page(page)
            if (ob.is_current_page_torn_out()) {
            torn_out += [ob]
            break


    def do_print(self, obs: MudObject, language: str) -> int:
            object ob
            if (open_func) {
            if (!evaluate(open_func, obs)) {
            return 0


    def do_print_copies(self, obs: MudObject, number: int, language: str) -> int:
            object ob
            int cost
            int player_money
            string place
            if (open_func) {
            if (!evaluate(open_func, obs)) {
            return 0


    def check_cost(self, str: str, ob: MudObject, number: int, cost: int, language: str) -> None:
            if (strlen(str) < 1 || (str[0] != 'y' && str[0] != 'Y')) {
            write("Ok, don't worry.  See you again.\n")
            return


    def do_print_run(self, ob: MudObject, number: int, cost: int, language: str) -> None:
            string place
            int player_money
            mixed *stuff
            place = query_property( "place" )
            if ( !place || ( place == "" ) ) {
            place = "default"


    def price_object(self, ob: MudObject, num: int, to_language: str) -> int:
            int i
            int num_letters
            int multiplier
            int cost
            mixed *stuff
            if (num <= 0 || !ob) {
            return 0


    def print_pricing(self, ob: MudObject, language: str) -> None:
            int i
            int num
            string place
            int cost
            place = query_property( "place" )
            if ( !place || ( place == "" ) ) {
            place = "default"


    def set_discount_schedule(self, value: Any) -> None:
            discount_schedule = value


    def query_letter_cost(self, ) -> int:
            return letter_cost


    def set_letter_cost(self, value: int) -> None:
            letter_cost = value


    def add_print_run(self, name: str, ob: MudObject, number: int, language: str) -> None:
            mixed *arr
            int num
            if (!collectables[name]) {
            collectables[name] = [})


    def remove_print_run(self, name: str, info: Any) -> None:
            int index
            if (collectables[name]) {
            index = collectables[name].index(info) if info in collectables[name] else -1
            if (index != -1) {
            remove_auto_load_info(info[COLLECT_AUTO_LOAD_NUM])
            collectables[name] = collectables[name][0.. index - 1] +
            collectables[name][index + 1..]
            if (!sizeof(collectables[name])) {
            map_delete(collectables, name)


    def query_static_auto_load_info(self, num: int) -> str:
            string *arr
            string tmp
            if (unguarded( (: file_size(save_dir + "/" + $(num)) :) ) > 0) {
            tmp = unguarded( (: read_file(save_dir + "/" + $(num)) :) )
            if (tmp) {
            arr = restore_variable(tmp)
            return arr[0]


    def set_save_dir(self, name: str) -> None:
            save_dir = name


    def query_save_dir(self, ) -> str:
            return save_dir


    def load_it(self, ) -> None:
            if (save_dir) {
            unguarded((: restore_object(save_dir + "/main") :))
            if (!collectables) {
            collectables = ([ ])


    def save_it(self, ) -> None:
            if (save_dir) {
            unguarded((: save_object(save_dir + "/main") :))


    def set_office_room(self, room: str) -> None:
            office_room = room


    def query_office_room(self, ) -> str:
            return office_room


    def set_no_collection(self, collect: int) -> None:
            no_collection = collect


    def query_no_collection(self, ) -> int:
            return no_collection


    def set_open_func(self, func: Any) -> None:
            open_func = func


    def set_default_language(self, lang: str) -> None:
            default_language = lang


    def query_default_language(self, ) -> str:
            return default_language


    def add_translation_cost(self, lang: str, cost: int) -> None:
            translation_costs[lang] = cost


    def remove_translation_cost(self, lang: str) -> None:
            map_delete(translation_costs, lang)


    def set_print_shop_name(self, name: str) -> None:
            print_shop_name = name


    def query_print_shop_name(self, ) -> str:
            return print_shop_name



class Print_shop(MudObject):

    letter_cost = 'DEFAULT_LETTER_COST'

    time_to_collect = 'DEFAULT_TIME_TO_COLLECT'

    time_per_copy = 'DEFAULT_TIME_PER_COPY'

    collectables = '([ ])'

    discount_schedule = "['({ 100', '5 })']"

    default_language = '"common"'

    translation_costs = '([ ])'

    print_shop_name = '"Rabbits happy little printing press"'
