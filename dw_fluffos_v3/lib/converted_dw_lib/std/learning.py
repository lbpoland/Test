# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/learning.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def lesson_response(self, string, object, int, string) -> int:
            int register_lesson(string name, mapping minimum_skills,
            mapping maximum_skills, string *materials, int cost,
            string currency, string *lesson_ending, object teacher ) {
            if(!_lessons)
            _lessons = ([ ])
            if(_lessons[name])
            return 0
            _lessons[name] = new(class lesson,
            minimum_skills : minimum_skills,
            maximum_skills : maximum_skills,
            materials : materials,
            cost : cost,
            currency : currency,
            lesson_ending : lesson_ending,
            teacher : teacher
            )
            return 1


    def has_required_skills(self, name: str, player: MudObject) -> int:
            string skill
            int p_level
            foreach( skill in (keys(_lessons[name]->minimum_skills)) ){
            p_level = player.query_skill(skill)
            if( p_level < _lessons[name]->minimum_skills[skill] ){
            return 0


    def has_required_materials(self, name: str, player: MudObject) -> int:
            string mat
            foreach( mat in _lessons[name]->materials ) {
            if( sizeof( filter_array(deep_inventory(player),
            (: ($1)->query_short() :) ) ) ){
            return 1


    def has_required_cash(self, name: str, player: MudObject) -> int:
            if(player.query_value_in(_lessons[name]->currency) < _lessons[name]->cost) {
            return 0
            } else {
            return 1


    def start_lesson(self, name: str, player: MudObject) -> int:
            string *needed
            if(!_lessons[name])
            return notify_fail(player, "Sorry, it's not clear what you want to learn "
            "here.\n")
            needed = [})
            if(!has_required_skills(name, player))
            needed += ["skills"]
            if(!has_required_materials( name, player ))
            needed += ["materials"]
            if(!has_required_cash( name, player ))
            needed += ["cash"]
            if(sizeof(needed)) {
            debug_printf( "Player doesn't have the correct %s\n",
            query_multiple_short(needed) )
            return add_failed_mess("Sorry, You don't have the correct " +
            query_multiple_short(needed) + " to learn today.\n")


    def lesson_response(self, name: str, student: MudObject, lessonstep: int, args: str) -> int:
            class step current
            if(this_player() != student)
            return 0
            current = _lessons[name]->plan[lessonstep]
            if(sizeof(current->params) &&
            current->params.index(args[0]) if args[0] in current->params else -1 == -1)
            return student->add_failed_mess(self, "Invalid response.\n",
            [}))
            switch(TASKER->perform_task(student, current->skill, current->difficulty,
            TM_FIXED)) {
            case AWARD:
            await student.send("%^YELLOW%^"+current->award_mess+"%^RESET%^\n")
            case SUCCEED:
            await  student.send(current->succeed_mess + "\n")
            student.remove_object(self, 1)
            if( (sizeof(_lessons[name]->plan)-1) == lessonstep ) {
            tell_creator("belle", "Lesson is on its last step: %d\n", lessonstep )
            asyncio.create_task(self. "lesson_end", 1, name, student )
            return 1
            } else {
            asyncio.create_task(self."lesson_step", 1, name, student, ++lessonstep)


    def lesson_end(self, name: str, student: MudObject) -> int:
            string str
            object teacher = _lessons[name]->teacher
            foreach( str in (_lessons[name]->lesson_ending) ) {
            if( teacher )
            teacher.queue_command(str)
            else
            await student.send(str)



class Learning(MudObject):
