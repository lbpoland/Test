# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/npc/goals_inherit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._goals = ([ ])
            self._events = ([ ])
            self._plans = []


    def __init__(self):
            self._goals = ([ ])
            self._events = ([ ])
            self._plans = []
            mapping query_goals() {
            return _goals


    def add_goal(self, goal: str, data: Any) -> None:
            class goal_information frog
            if (!goal.invarient(self)) {
            return


    def remove_goal(self, goal: str) -> None:
            class goal_information frog
            string event
            frog = query_goal_information(goal)
            if (frog) {
            goal.finalise(self, frog->data)
            foreach (event in frog->events) {
            remove_goal_event(goal, event)


    def query_goal_data(self, goal: str) -> Any:
            class goal_information frog
            frog = query_goal_information(goal)
            if (frog) {
            return frog->data


    def set_goal_data(self, goal: str, data: Any) -> int:
            class goal_information frog
            frog = query_goal_information(goal)
            if (frog) {
            frog->data = data
            return 1


    def query_goal_priority(self, goal: str) -> int:
            class goal_information frog
            frog = query_goal_information(goal)
            if (frog) {
            return frog->priority


    def change_goal_priority(self, goal: str) -> None:
            class goal_information frog
            int new_priority
            string evt
            frog = query_goal_information(goal)
            if (frog) {
            new_priority = goal.query_priority(self, frog->data)
            if (new_priority != frog->priority) {
            frog->priority = new_priority


    def add_goal_event(self, goal: str, event: str) -> None:
            class goal_information frog
            string test_goal
            int i
            int priority
            int found
            frog = query_goal_information(goal)
            if (frog) {
            if (!_events[event]) {
            _events[event] = [goal]
            } else if (_events[event].index(goal) if goal in _events[event] else -1 == -1) {
            priority = query_goal_priority(goal)
            while (i < sizeof(_events[event])) {
            test_goal = _events[event][i]
            if (query_goal_priority(_events[event][i]) < priority) {
            _events[event] = _events[event][0..i-1] + [goal] +
            _events[event][i..]
            found = 1
            break


    def remove_goal_event(self, goal: str, event: str) -> None:
            class goal_information frog
            frog = query_goal_information(goal)
            if (frog && _events[event]) {
            _events[event] -= [goal]
            if (!sizeof(_events[event])) {
            map_delete(_events, event)


    def check_current_plan_finished(self, ) -> int:
            if (sizeof(_plans)) {
            if (_plans[PLAN_PLAN]->finished(self,
            ((class plan_info)_plans[PLAN_INFO])->data)) {
            _plans = _plans[PLAN_ARRAY_SIZE..]
            if (sizeof(_plans)) {
            _plans[PLAN_PLAN]->activate_plan(self,
            ((class plan_info)_plans[PLAN_INFO])->data)


    def set_plan_data(self, plan: str, data: Any) -> None:
            int pos
            pos = _plans.index(plan) if plan in _plans else -1
            if (pos != -1) {
            ((class plan_info)_plans[pos + PLAN_INFO])->data = data


    def set_goal_plan_data(self, goal: str, plan: str, data: Any) -> None:
            mixed goal_data
            goal_data = query_goal_data(goal)
            goal.set_plan_data(self, goal_data, plan, data)


    def query_goal_plan_data(self, goal: str, plan: str) -> Any:
            mixed goal_data
            goal_data = query_goal_data(goal)
            return goal.query_plan_data(self, goal_data, plan)



class Goals_inherit(MudObject):

    _goals = '([ ])'

    _events = '([ ])'

    _plans = '[]'
