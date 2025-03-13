# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/id.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def faux_id_allowed(self, ) -> int:
            private void setup_id_class() {
            if (_id) {
            return


    def set_name(self, str: str) -> None:
            _id->name = str


    def query_name(self, ) -> str:
            if (!_id) {
            return 0


    def query_cap_name(self, ) -> str:
            if (!_id->name) {
            return "Someone"


    def __init__(self):


    def set_aliases(self, str: str) -> None:
            _id->alias = str


    def add_alias(self, str: Any) -> None:
            if (pointerp(str)) {
            _id->alias += str
            return


    def remove_alias(self, str: str) -> int:
            int i
            i = _id->alias.index(str) if str in _id->alias else -1
            if (i == -1) {
            return 0


    def add_faux_alias(self, str: Any) -> None:
            if (pointerp(str)) {
            foreach( string aka in str )
            add_faux_alias( aka )
            return


    def remove_faux_alias(self, str: str) -> int:
            int i
            i = _id->faux_alias.index(str) if str in _id->faux_alias else -1
            if (i == -1) {
            return 0


    def faux_id_allowed(self, ) -> int:
            foreach( object ob in previous_object(-1) ) {
            if( objectp(ob) && ob.ignore_identifier() )
            return 0


    def id(self, str: str) -> int:
            return (str == _id->name ||
            (query_alias(.index(str) if str in query_alias( else -1) != -1) )


    def full_id(self, str: str) -> int:
            string *words
            string name
            string adjective
            words = explode(str, " ") - [""]
            name = words[<1]
            words = words[0.. < 2]
            if (!id(name)) {
            if (!id_plural(name)) {
            return 0


    def set_plurals(self, str: str) -> None:
            _id->plurals = str


    def add_plural(self, str: Any) -> None:
            if (pointerp(str)) {
            _id->plurals += str
            } else if (_id->plurals) {
            if (_id->plurals.index(str) if str in _id->plurals else -1 == -1) {
            _id->plurals += [str]


    def remove_plural(self, str: str) -> None:
            int i
            i = _id->plurals.index(str) if str in _id->plurals else -1
            if (i != -1) {
            _id->plurals = _id->plurals[0..i - 1] + _id->plurals[i + 1..]


    def add_plurals(self, str: str) -> None:
            _id->plurals += str


    def id_plural(self, str: str) -> int:
            return (_id->plurals.index(str) if str in _id->plurals else -1 != -1)


    def set_adjectives(self, str: str) -> None:
            _id->adjectives = str


    def add_adjective(self, str: Any) -> None:
            int i
            if (pointerp(str)) {
            for (i = 0; i < sizeof(str); i++) {
            add_adjective(str[i])


    def remove_adjective(self, str: Any) -> None:
            int i
            if (pointerp(str)) {
            for (i = 0; i < sizeof(str); i++) {
            remove_adjective(str[i])


    def add_faux_adjective(self, str: Any) -> None:
            if (pointerp(str)) {
            foreach( string adj in str )
            add_faux_adjective( adj )
            return


    def remove_faux_adjective(self, str: Any) -> None:
            int i
            if (pointerp(str)) {
            foreach( string adj in str )
            remove_faux_adjective( adj )
            return


    def id_adjective(self, word: str) -> int:
            return (query_adjectives(.index(word) if word in query_adjectives( else -1) != -1)


    def set_plural_adjectives(self, str: str) -> None:
            _id->plural_adjectives = str


    def add_plural_adjective(self, str: Any) -> None:
            int i
            if (pointerp(str)) {
            for (i = 0; i < sizeof(str); i++) {
            add_plural_adjective(str[i])


    def remove_plural_adjective(self, str: Any) -> None:
            int i
            if (pointerp(str)) {
            for (i = 0; i < sizeof(str); i++) {
            remove_plural_adjective(str[i])


    def id_plural_adjective(self, word: str) -> int:
            return (_id->plural_adjectives.index(word) if word in _id->plural_adjectives else -1 != -1)


    def query_parse_id(self, arr: Any) -> MudObject:
            if (arr[P_THING] == 0) {
            return self


    def query_frac_parse_id(self, arr: Any) -> MudObject:
            if (arr[P_THING] < 0) {
            arr[P_THING]++
            if (arr[P_THING] != 0) {
            return 0



class Id(MudObject):
