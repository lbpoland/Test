# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/dom/interview_inherit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def save(self, ) -> None:
            unguarded ((: save_object (SAVE) :))


    def load(self, ) -> None:
            unguarded ((: restore_object (SAVE) :))


    def __init__(self):


    def init(self, ) -> None:
            ::init()
            this_player()->add_command ("show", self, "movie")
            this_player()->add_command ("stop", self, "movie")
            this_player()->add_command ("interview", self,
            "<indirect:living>", (: do_interview ($1[0]) :))
            this_player()->add_command ("interview", self,
            "<indirect:living> with <string>", (: do_interview ($1[0], $4[1]) :))
            this_player()->add_command ("end", self, "interview")
            this_player()->add_command ("add", self, "<string> [as "
            "candidate]", (: do_add ($4[0]) :))
            this_player()->add_command ("query", self, "applicants")
            this_player()->add_command ("query", self, "permitted "
            "[creators]", (: query_allowed_creators () :))
            this_player()->add_command ("query", self,
            "{confirmation|acceptance|rejection} [text]",
            (: do_query_text ($4[0]) :))
            this_player()->add_command ("delete", self, "<string> [from "
            "candidates]", (: remove_candidate ($4[0]) :))
            this_player()->add_command ("clear", self, "[all] candidates",
            (: flush() :))
            this_player()->add_command ("confirm", self, "<string>",
            (: do_confirm ($4[0]) :))
            this_player()->add_command ("grant", self, "[access to] "
            "<string>", (: add_creator ($4[0]) :))
            this_player()->add_command ("remove", self, "<string> "
            "[as allowed]", (: remove_creator ($4[0]) :))
            this_player()->add_command ("flag", self, "<string> as "
            "{accepted|rejected}", (: do_flag ($4[0], $4[1]) :))
            this_player()->add_command ("read", self,
            "interview for <string>",
            (: do_read ($4[0]) :))
            this_player()->add_command ("list", self, "interviews")


    def set_movie(self, m: str) -> None:
            movie = m


    def query_permitted(self, name: str) -> int:
            object ob = load_object("/d/" + query_domain() + "/master")
            if (!ob) {
            printf ("Erk, this room is horribly borken!!  Please set the domain "
            "correctly.\n")
            return 0


    def event_person_say(self, ob: MudObject, start: str, mess: str, lang: str) -> None:
            if (query_subject()) {
            write_to_file (sprintf ("%s says: %s\n", ob.short(),
            mess))


    def event_emote(self, ob: MudObject, mess: str) -> None:
            if (query_subject()) {
            write_to_file (replace (EVENTS->convert_message (mess), ({"$C$", ""})))


    def do_show(self, ) -> int:
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot show a "
            "movie!\n", [}))
            return 0


    def do_stop(self, ) -> int:
            int i
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot stop a "
            "movie!\n", [}))
            return 0


    def play_movie(self, i: int) -> None:
            if (movie[i][0] == '#') {
            tell_room (self, "The movie shows " +
            movie[i][1..sizeof(movie[i])] + "\n")


    def do_end(self, ) -> int:
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot end an "
            "interview!\n", [}))
            return 0


    def event_soul(self, ob: MudObject, str: str, avoid: Any) -> None:
            if (environment (this_player()) != self) {
            return


    def do_query(self, ) -> int:
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot query "
            "creator candidates!\n",
            [}))
            return 0


    def do_add(self, candidate: str) -> int:
            int i = query_permitted (this_player()->query_name())
            if (!i) {
            this_player()->add_failed_mess (self, "You cannot add a "
            "candidate!\n", [}))
            return 0


    def query_applicants_text(self, ) -> str:
            string ret = "", *temp = allocate (sizeof (submitted))
            int i
            if (sizeof (submitted)) {
            for (i = 0; i < sizeof (submitted); i++) {
            if (find_player (submitted[i])) {
            temp [i] = "%^BOLD%^"+submitted[i] + "%^RESET%^"


    def clear_interviewed(self, ) -> int:
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot do this!\n",
            [}))
            return 0


    def clear_candidates(self, ) -> int:
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot do this!\n",
            [}))
            return 0


    def flush(self, ) -> int:
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot do this!\n",
            [}))
            return 0


    def remove_candidate(self, candidate: str) -> int:
            int i
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot do this!\n",
            [}))
            return 0


    def add_candidate(self, name: str) -> int:
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot do this!\n",
            [}))
            return 0


    def add_interviewed(self, name: str) -> int:
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot do this!\n",
            [}))
            return 0


    def add_confirmed(self, name: str) -> int:
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot do this!\n",
            [}))
            return 0


    def remove_interviewed(self, candidate: str) -> int:
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot do this!\n",
            [}))
            return 0


    def do_confirm(self, candidate: str) -> int:
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot do this!\n",
            [}))
            return 0


    def set_domain(self, dom: str) -> None:
            _domain = dom


    def query_domain(self, ) -> str:
            if (!_domain) {
            return "unset"


    def set_confirmation(self, text: str) -> None:
            _confirmation_text = text


    def query_confirmation(self, ) -> str:
            if (!sizeof (_confirmation_text)) {
            if (query_interview()) {
            return sprintf ("Bing!\n\n"
            "Thank you for sending in the second part of the application.  "
            "The next part of the application process will be an interview "
            "to discuss your application to the %s domain.  "
            "This interview is likely to take around an hour of your time, "
            "so if you could mail me with a list of your "
            "common online times, hopefully we'll be able to make an "
            "appointment that is mutually convenient.\n\nRegards,\n%s.",
            query_domain(), LORD)


    def query_lord(self, ) -> str:
            return LORD


    def set_part_two_required(self, i: int) -> None:
            _pt_two = i


    def query_part_two_required(self, ) -> int:
            return _pt_two


    def set_interview(self, i: int) -> None:
            _interview = i


    def query_interview(self, ) -> int:
            return _interview


    def query_subject(self, ) -> str:
            if (_subject) {
            return _subject


    def query_is_interviewer(self, name: str) -> int:
            if (!sizeof (_int)) {
            return 0


    def add_creator(self, name: str) -> int:
            object ob = find_object ("/d/" + query_domain() + "/master")
            if (this_player()->query_name() != ob.query_lord()) {
            this_player()->add_failed_mess (self, "Only the lord "
            "may permit creators to use this room.\n", [}))
            return 0


    def remove_creator(self, name: str) -> int:
            object ob = find_object ("/d/" + query_domain() + "/master")
            if (this_player()->query_name() != ob.query_lord()) {
            this_player()->add_failed_mess (self, "Only the lord "
            "may permit creators to use this room.\n", [}))
            return 0


    def query_allowed_creators(self, ) -> int:
            if (!sizeof (query_permitted_creators())) {
            this_player()->add_failed_mess (self, "Only the domain lord and "
            "the domain deputies are currently permitted to use this room.\n",
            [}))
            return 0


    def query_part_two(self, ) -> str:
            string temp
            if (_filename) {
            temp = unguarded ((: read_file (_filename) :))
            if (sizeof (temp)) {
            return temp


    def set_part_two(self, file: str) -> int:
            if (!sizeof (file)) {
            printf ("No file given for part two of application.  Aborting.\n")
            return 0


    def query_interview_dir(self, ) -> str:
            if (sizeof (_interview_dir)) {
            return _interview_dir


    def set_interview_dir(self, dir: str) -> int:
            if (!sizeof (dir)) {
            printf ("No directory given for interviews.  Aborting.\n")
            return 0


    def do_query_text(self, flag: str) -> int:
            string temp
            switch (flag) {
            case "confirmation":
            temp = query_confirmation()
            break
            case "acceptance":
            temp = query_acceptance()
            break
            case "rejection":
            temp = query_rejection()
            break
            default:
            temp = "I'm sorry, there has been an error.\n"
            break


    def do_flag(self, name: str, flag: str) -> int:
            if (member_array (name, candidates) != -1) {
            candidates -= ({name})


    def set_rejection(self, text: str) -> None:
            _rejection_text = text


    def set_acceptance(self, text: str) -> None:
            _acceptance_text = text


    def query_rejection(self, ) -> str:
            if (!sizeof (_rejection_text)) {
            return sprintf ("Hello.\n\n"
            "I'm sorry to say that your application to the %s domain has been "
            "unsuccessful.  My apologies that I cannot hire you at this time.  "
            "I will of course keep your details on file should you wish to "
            "apply again in the future.\n\nRegards,\n%s.",
            query_domain(), LORD)


    def query_acceptance(self, ) -> str:
            if (!sizeof (_acceptance_text)) {
            return sprintf ("Bing!\n\n"
            "It is my great pleasure to inform you that your application to the %s "
            "domain has been successful.  Congratulations!\n\nBefore being promoted, "
            "you will need to ensure you repay any debts you have.  If you wish "
            "to bequeath your inventory on a fellow player, this must also be "
            "done before you are employed - you won't get a chance once you're "
            "a creator.\n\nPlease send me a mail letting me know when you will "
            "be available for promotion and your orientation lecture.\n\n"
            "Congratulations,\n%s.",query_domain(), LORD)


    def do_read(self, name: str) -> int:
            string path
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot do this!\n",
            [}))
            return 0


    def query_cc(self, ) -> str:
            if (sizeof (_cc)) {
            return implode (_cc, ",")


    def set_cc(self, i: str) -> None:
            _cc = i


    def do_list(self, ) -> int:
            string *list, text
            if (!query_permitted (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You are not permitted "
            "to do this.\n", [}))
            return 0



class Interview_inherit(Room):
