# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/guild.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.cost_div = COST_DIV
            self.cost_mult = 100
            self.spells = ([ ])
            self.commands = ([ ])


    def init(self, ) -> None:
            {
            this_player()->add_command("advance", self,
            "<string>", (: do_advance($4[0]) :))
            this_player()->add_command("advance", self,
            "<string> to <number>",
            (: do_advance_to($4[0], $4[1]) :))
            this_player()->add_command("advance", self,
            "<string> by <number>",
            (: do_advance_by($4[0], $4[1]) :))
            this_player()->add_command("join", self, "")
            this_player()->add_command("info", self, "")
            this_player()->add_command("cost", self,
            "primaries", (: do_cost_primaries() :))
            this_player()->add_command("cost", self,
            "all", (: do_cost_all(0) :))
            this_player()->add_command("cost", self,
            "all brief", (: do_cost_all(1) :))
            this_player()->add_command("cost", self,
            "<string>", (: do_cost($4[0]) :))
            this_player()->add_command("cost", self,
            "<string> to <number>",
            (: do_cost_to($4[0], $4[1]) :))
            this_player()->add_command("cost", self, "<string> by <number>",
            (: do_cost_by($4[0], $4[1]) :))
            if ((string) this_player()->query_class_ob() == our_class) {
            if (stringp(start_pos) && !clonep(self)) {
            this_player()->add_start(file_name(self), start_pos)


    def set_cost_div(self, number: int) -> None:
            {
            cost_div = number
            if (!cost_div)
            cost_mult = 1000
            else
            cost_mult = 10 + (990 * cost_div) / (10 * COST_DIV + cost_div)


    def query_skill_cost(self, skill: str, offset: int) -> int:
            {
            int i
            int total
            string *next
            next = (string *) SKILL_OB.query_immediate_children(skill)
            if (!sizeof(next)) {
            if (!this_player()->query_class_ob())
            total = DEFAULT_COST
            else
            total = (int) our_class.query_skill_cost(skill)
            total *= (STD_COST * cost_mult) / 500
            total *= ((int) this_player()->query_skill(skill) + offset) /
            LEVEL_DIV + 1
            total = to_int(total * exp((this_player()->query_skill(skill) +
            offset) / 150.0))
            return total


    def do_advance_internal(self, skill: str, to: int, by: int) -> int:
            {
            string *bits
            string skill_name
            string outer_name
            string place
            int lvl
            int max_lvl
            int tmp
            int total_xp
            int total_cost
            int tmp_cost
            int p_val
            int i, j
            int round_value
            if ((string) this_player()->query_class_ob() != our_class) {
            add_failed_mess("You cannot advance here!  Go to your own class.\n")
            return 0


    def do_advance(self, skill: str) -> int:
            {
            return do_advance_internal(skill, 0, 1)


    def do_join(self, str: str) -> int:
            {
            if ((string) this_player()->query_class_ob() == our_class) {
            add_failed_mess("You're already in this class.\n")
            return 0


    def join2(self, str: str) -> int:
            {
            str = lower_case(str)
            if (str[0] != 'n' && str[0] != 'y') {
            write("I do not understand.  Yes or no? ")
            input_to("join2")
            return 1


    def do_leave(self, str: str) -> int:
            {
            if (str != "class") {
            add_failed_mess("Syntax : leave class\n")
            return 0


    def confirm_leave(self, str: str) -> None:
            {
            str = lower_case(str)
            if (str != "y") {
            write("You are still in the class.\n")
            return


    def check_primaries(self, lpath: str, g_o: str) -> int:
            {
            int i
            string dummy,
            *primaries
            primaries = (string *) g_o.query_skills()
            if (primaries.index(lpath) if lpath in primaries else -1 != -1)
            return 1
            for (i = 0; i < sizeof(primaries); i++)
            if (sscanf(primaries[i], lpath + ".%s", dummy))
            return 1
            return 0


    def do_cost_all(self, brief: int) -> int:
            {
            mixed *arr
            string list
            if ((string) this_player()->query_class_ob() != our_class) {
            add_failed_mess("You are not a member of this class.\n")
            return 0


    def do_cost_primaries(self, ) -> int:
            {
            mixed *arr
            string list
            string *primaries
            if ((string) this_player()->query_class_ob() != our_class) {
            add_failed_mess("You are not a member of this class.\n")
            return 0


    def do_cost_internal(self, skill: str, to: int, by: int) -> int:
            string *bits
            string skill_name
            string outer_name
            string place
            string cost_str
            int lvl
            int max_lvl
            int i
            int tmp
            int cost
            if ((string) this_player()->query_class_ob() != our_class) {
            add_failed_mess("You are not a member of this class.\n")
            return 0


    def do_cost(self, skill: str) -> int:
            {
            mixed *arr
            int i
            int depth
            string list
            string exp_skill
            string *sub_skills
            int only_leaf
            if ((string) this_player()->query_class_ob() != our_class) {
            add_failed_mess("You are not a member of this class.\n")
            return 0


    def do_cost_to(self, skill: str, num: int) -> int:
            {
            return do_cost_internal(skill, num, 0)


    def do_cost_by(self, skill: str, num: int) -> int:
            {
            return do_cost_internal(skill, 0, num)


    def do_info(self, ) -> int:
            {
            mixed *arr
            string *primaries
            write(our_class.long() +
            "\nThis class's primary skills and costs are:\n")
            arr = copy((mixed *)SKILL_OB.query_skills())
            if (!arr) {
            add_failed_mess("Hmmm, we appear to have an error here.\n")
            return 0


    def set_teaching_person(self, ob: MudObject) -> None:
            {
            teaching_person = ob


    def query_teaching_person(self, ) -> MudObject:
            {
            return teaching_person


    def add_spell(self, name: str, blue: str, lvl: int) -> None:
            {
            string path
            path = implode(blue, ".")
            if (!spells[path])
            spells[path] = [name, lvl]
            else
            spells[path] += [name, lvl]


    def add_command(self, name: str, blue: str, lvl: int) -> None:
            {
            string path
            path = implode(blue, ".")
            if (!commands)
            commands = ([ ])
            if (!commands[path])
            commands[path] = [name, lvl]
            else
            commands[path] += [name, lvl]


    def check_spells_commands(self, sk: str, lvl: int) -> None:
            {
            string *bits
            int val
            int i
            int j
            if (!teaching_person)
            return
            bits = keys(spells)
            for (i = 0; i < sizeof(bits); i++) {
            val = this_player()->query_skill(bits[i])
            for (j = 0; j < sizeof(spells[bits[i]]); j += 2)
            if ((spells[bits[i]][j + 1] < val) &&
            !(this_player()->query_spell(spells[bits[i]][j])))
            teaching_person->init_command("teach " + spells[bits[i]][j] +
            " to " +
            this_player()->query_name())


    def query_start_pos(self, ) -> str:
            {
            return start_pos


    def query_our_guild(self, ) -> str:
            {
            return our_class



class Guild(MudObject):

    cost_div = 'COST_DIV'

    cost_mult = 100

    spells = '([ ])'

    commands = '([ ])'
