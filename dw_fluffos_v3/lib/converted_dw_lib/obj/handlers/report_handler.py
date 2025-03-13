# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/report_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("report handler")
            add_property("determinate", "the ")
            set_long("This is a rather tacky statue of a woman holding "
            "a sword and some wonky scales.\n")
            if(file_size(NEWCASES) > -1) {
            new_cases = restore_variable(read_file(NEWCASES))


    def save_new_cases(self, ) -> None:
            unguarded((: rm, NEWCASES :))
            unguarded((: write_file, NEWCASES, save_variable(new_cases)+"\n" :))


    def query_new(self, ) -> Any:
            return new_cases


    def sizeof_new_cases(self, ) -> int:
            if(!new_cases) {
            new_cases = restore_variable(read_file(NEWCASES))


    def query_new_cases(self, ) -> str:
            int i, j
            string reports = ""
            for(i = 0; i < sizeof(new_cases); i++) {
            if(i < 10) {
            reports += "   "+(i + 1)+": "
            } else {
            reports += "  "+(i + 1)+": "


    def query_new_case(self, i: int) -> str:
            string report = ""
            mixed *stuff
            if(!new_cases) {
            new_cases = restore_variable(read_file(NEWCASES))


    def add_report(self, stuff: str) -> None:
            if(!new_cases) {
            new_cases = restore_variable(read_file(NEWCASES))


    def deal_with_it(self, num: int, name: str, decision: str) -> None:
            mixed *thing
            num--
            thing = new_cases[num]
            thing += [name]
            thing += [decision]
            new_cases -= ({new_cases[num]})
            move_to_recent_cases(thing)


    def save_recent_cases(self, ) -> None:
            unguarded((: rm, RECENT :))
            unguarded((: write_file, RECENT, save_variable(recent_cases)+"\n" :))


    def move_to_recent_cases(self, thing: Any) -> None:
            int i, j
            mixed *c_record, *chars
            for(i = sizeof(recent_cases) - NO_RECENT; i > -1; i--) {
            chars = ({recent_cases[i][NAME]})
            if(arrayp(recent_cases[i][CHARS])) {
            chars += recent_cases[i][CHARS]


    def query_recent(self, ) -> Any:
            if(!recent_cases) {
            recent_cases = restore_variable(read_file(RECENT))


    def query_recent_cases(self, ) -> str:
            int i, j
            string reports = ""
            for(i = 0; i < sizeof(recent_cases); i++) {
            if(i < 10) {
            reports += "   "+(i + 1)+": "
            } else {
            reports += "  "+(i + 1)+": "


    def query_recent_case(self, i: int) -> str:
            string report = ""
            mixed *stuff
            if(!recent_cases) {
            recent_cases = restore_variable(read_file(RECENT))


    def case_history(self, name: str) -> str:
            int i, j
            mixed *history, *cases, *stuff, *all_cases, *check_case
            string report, *other_chars = [})
            history = get_dir(SAVEPATH+lower_case(name)+".o")
            all_cases = get_dir(SAVEPATH)
            all_cases -= ({"recent.o", "new.o"})
            for(i = 0; i < sizeof(all_cases); i++) {
            check_case = restore_variable(read_file((SAVEPATH+all_cases[i])))
            for(j = 0; j < sizeof(check_case); j++) {
            if(arrayp(check_case[j][CHARS])) {
            if(check_case[j][CHARS].index(capitalize(name)) if capitalize(name) in check_case[j][CHARS] else -1 != -1) {
            other_chars += check_case[j][CHARS]
            other_chars += ({check_case[j][NAME]})


    def add_comment(self, i: int, name: str, comment: str) -> None:
            i--
            recent_cases[i] += [capitalize(name), comment]
            save_recent_cases()



class Report_handler(MudObject):
