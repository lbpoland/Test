# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/book_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.banished_books = ([ ])


    def query_book_exists(self, book_num: int) -> int:
            return unguarded((: file_size(SAVE_DIR + $(book_num) + ".o") :)) > 0


    def add_book(self, book: MudObject, num: int, pl_name: str) -> int:
            string *stuff
            mapping bing
            if (num) {
            if (check_book_same(book, num)) {
            return num


    def check_book_same(self, book: MudObject, num: int) -> int:
            string *bing
            string *fluff
            int old_open_page
            int same
            old_open_page = book.query_open_page()
            same = 0
            if (query_book_exists(num) > 0) {
            bing = query_book_pages(num)
            fluff = query_pages(book)
            if (compare_pages(bing, fluff) > 90) {
            same = 1


    def query_book_owner(self, book_num: int) -> str:
            mapping bing
            string tmp
            tmp = unguarded((: read_file(SAVE_DIR + $(book_num) + ".o") :))
            if (tmp) {
            bing = restore_variable(tmp)
            return bing[OWNER_INDEX]


    def compare_pages(self, pages1: str, pages2: str) -> int:
            int no_chars
            int no_same
            int pos
            int start
            string page
            string *tmp
            pos = 0
            if (sizeof(pages1) > sizeof(pages2)) {
            tmp = pages1
            pages1 = pages2
            pages2 = tmp


    def compare_page(self, page1: str, page2: str) -> int:
            mixed *stuff1
            mixed *stuff2
            string text1
            string text2
            int i
            stuff2 = page2.query_read_mess()
            text1 = ""
            for (i = 0; i < sizeof(stuff1); i++) {
            text1 += stuff1[READ_MESS]


    def add_banished_book(self, book_num: int, reason: str) -> int:
            if (!stringp(reason) || !intp(book_num)) {
            return 0


    def query_banished_book(self, book_num: int) -> str:
            return banished_books[book_num]


    def save_it(self, ) -> None:
            unguarded((: save_object(SAVE_FILE) :))


    def load_it(self, ) -> None:
            unguarded((: restore_object(SAVE_FILE) :))
            if (!current_book_number) {
            current_book_number = 1



class Book_handler(MudObject):

    banished_books = '([ ])'
