# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/dom/base_master.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_domain(self, ) -> str:
            string *words
            if (!file_name (self)) {
            return ""


    def query_prevent_shadow(self, ) -> int:
            return 1


    def __init__(self):
            self.members = ([ ])
            self.access = ([ ])
            self.deputies = []
            self._project_cache = ([ ])
            self._rcsforce_allowed = ([ ])
            self._idle_mess = 0
            self.deputies = []


    def save_me(self, ) -> None:
            unguarded((: save_object, file_name(self) :))


    def dest_me(self, ) -> None:
            {
            destruct(self)


    def check_call_tree(self, only_lord: int) -> int:
            {
            object *obs
            int found
            int i
            obs = previous_object(-1)
            for (i = 0; i < sizeof(obs); i++) {
            if (file_name(obs[i])[0..12] == "/global/lord#" ||
            (file_name(obs[i])[0..15] == "/global/creator#")) {
            if("/secure/master"->query_administrator(obs[i]->query_name()) ||
            obs[i]->query_name() == query_lord() ||
            (!only_lord &&
            (deputies.index(obs[i]->query_name()) if obs[i]->query_name() in deputies else -1 != -1))) {
            found = 1
            } else {
            return 0


    def add_member(self, name: str) -> int:
            {
            if (!check_call_tree(0)) {
            return 0


    def remove_member(self, name: str) -> int:
            {
            int pos
            if (!check_call_tree(deputies.index(name) if name in deputies else -1 != -1)) {
            return 0


    def add_deputy(self, name: str) -> int:
            {
            if (!check_call_tree(1)) {
            return 0


    def remove_deputy(self, name: str) -> int:
            {
            int pos
            if (!check_call_tree(1)) {
            return 0


    def add_rcsforce_allowed(self, creator: str, directory: str) -> int:
            if (!check_call_tree(1)) {
            return 0


    def remove_rcsforce_allowed(self, creator: str, directory: str) -> int:
            if (!check_call_tree(1)) {
            return 0


    def query_project(self, name: str) -> str:
            {
            string *proj
            string project
            project = members[name]
            if (!project) {
            return "project unset"


    def query_deputy(self, name: str) -> int:
            {
            if (!deputies)
            return 0
            if (deputies.index(name) if name in deputies else -1 != -1)
            return 1
            return 0


    def query_lord(self, ) -> str:
            {
            return "Something is broken"


    def can_rcsforce(self, file: str, person: str, locker: str) -> int:
            string *directories
            string fdir
            if (query_deputy(person)) {
            return 1


    def query_changelog(self, filename: str) -> str:
            return  "/d/" + query_domain() + "/ChangeLog"


    def set_use_tracker(self, i: int) -> None:
            _use_tracker = i


    def query_use_tracker(self, ) -> int:
            return _use_tracker


    def nuke_creator_project_cache(self, creators: str) -> int:
            if (!_project_cache) {
            return 0


    def set_idle_mess(self, txt: str) -> int:
            if (!check_call_tree(1)) {
            return 0


    def query_idle_mess(self, ) -> str:
            return _idle_mess


    def assign_people_to_directory(self, dir: str, people: Any) -> int:
            if (previous_object() != master()) {
            return 0



class Base_master(MudObject):

    members = '([ ])'

    access = '([ ])'

    deputies = '[]'

    _project_cache = '([ ])'

    _rcsforce_allowed = '([ ])'

    _idle_mess = 0
