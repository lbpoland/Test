# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/bank_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._banks = ([ ])
            self.str = unguarded((: read_file, RESTORE_PATH + "bank_data.o" :))
            self._banks = restore_variable(str)


    def __init__(self):
            self._banks = ([ ])
            self.str = unguarded((: read_file, RESTORE_PATH + "bank_data.o" :))
            self._banks = restore_variable(str)


    def get_data_file(self, name: str) -> int:
            int success
            success = unguarded((: restore_object, RESTORE_PATH+
            name[0..0]+"/"+name :))
            if(!success) {
            init_data(name)
            return success


    def query_account(self, word: str, bank_name: str) -> int:
            get_data_file( word )
            if ( !accounts ) {
            return -1


    def adjust_account(self, name: str, bank_name: str, amount: int) -> None:
            int before
            get_data_file( name )
            before = accounts[ bank_name ]
            accounts[bank_name] += amount
            if ( accounts[ bank_name ] < 0 ) {
            accounts = m_delete( accounts, bank_name )


    def set_account(self, name: str, bank_name: str, amount: int) -> None:
            int before
            get_data_file( name )
            before = accounts[ bank_name ]
            if ( amount < 0 ) {
            accounts = m_delete( accounts, bank_name )
            } else {
            accounts[ bank_name ] = amount


    def create_new_bank(self, name: str, master: str) -> None:
            class bank_data data
            if (_banks[name]) {
            return


    def remove_bank(self, name: str) -> None:
            map_delete(_banks, name)
            save_banks()


    def add_new_franchise(self, name: str, franchise_office: str) -> None:
            class franchise franchise
            if (!_banks[name]) {
            return


    def set_bank_default_cost_to_open(self, name: str, amount: int) -> None:
            if (!_banks[name]) {
            return


    def set_bank_default_cost_per_new_account(self, name: str, amount: int) -> None:
            if (!_banks[name]) {
            return


    def set_bank_franchise_cost_per_new_account(self, name: str, amount: int) -> None:
            if (!_banks[name]) {
            return


    def set_bank_default_cost_per_month(self, name: str, amount: int) -> None:
            if (!_banks[name]) {
            return


    def query_bank_default_cost_to_open(self, name: str) -> int:
            if (!_banks[name]) {
            return -1


    def query_bank_default_cost_per_new_account(self, name: str) -> int:
            if (!_banks[name]) {
            return -1


    def query_bank_franchise_cost_per_month(self, name: str, franchise_office: str) -> int:
            class franchise franchise
            if (!_banks[name]) {
            return -1


    def query_bank_default_cost_per_month(self, name: str) -> int:
            if (!_banks[name]) {
            return -1


    def query_bank_master_office(self, name: str) -> str:
            if (!_banks[name]) {
            return 0


    def set_bank_master_office(self, name: str, master: str) -> None:
            if (!_banks[name]) {
            return 0



class Bank_handler(MudObject):

    _banks = 'restore_variable(str)'

    str = 'unguarded((: read_file, RESTORE_PATH + "bank_data.o" :))'
