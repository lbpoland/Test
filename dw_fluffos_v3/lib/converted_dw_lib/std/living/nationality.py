# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/living/nationality.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_nationality(self, ) -> str:
            if (_nationality_data && _nationality_data->nationality) {
            return _nationality_data->nationality


    def query_nationality_region(self, ) -> str:
            if (_nationality_data && _nationality_data->region) {
            return _nationality_data->region


    def query_nationality_data(self, ) -> Any:
            if (_nationality_data && _nationality_data->data) {
            return _nationality_data->data


    def set_nationality(self, nationality: str) -> None:
            if (!_nationality_data) {
            _nationality_data = new(class living_nationality)


    def set_nationality_region(self, region: str) -> None:
            if (!_nationality_data) {
            _nationality_data = new(class living_nationality)


    def set_nationality_data(self, data: Any) -> None:
            if (!_nationality_data) {
            _nationality_data = new(class living_nationality)


    def query_nationality_name(self, ) -> str:
            if (_nationality_data && _nationality_data->nationality) {
            return _nationality_data->nationality.query_name()


    def query_nationality_description(self, looker: MudObject) -> str:
            if (_nationality_data && _nationality_data->nationality) {
            return _nationality_data->nationality.query_look_description(self, looker)


    def query_nationality_accent_ob(self, ) -> str:
            if (_nationality_data && _nationality_data->nationality) {
            return _nationality_data->nationality.query_region_accent_ob(_nationality_data->region)


    def query_nationality_start_location(self, ) -> str:
            if (_nationality_data && _nationality_data->nationality) {
            return _nationality_data->nationality.query_start_location(_nationality_data->region)



class Nationality(MudObject):
