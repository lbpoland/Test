# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/autodoc/autodoc_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.filters = ['(: create_nroff_file($1', '$2) :)']
            self.file_pos = 0
            self.something_changed = 0
            self.files = []


    def __init__(self):
            self.filters = ['(: create_nroff_file($1', '$2) :)']
            self.file_pos = 0
            self.something_changed = 0
            self.files = []
            private void create_nroff_file(mixed ob, int type) {
            string fname
            mixed *stuff
            mixed *index_stuff
            int i
            if (type == MAIN_FILE) {
            fname = replace(ob.query_file_name(), "/", ".")
            if (fname[0] == '.') {
            fname = fname[1..]


    def recreate_documentation(self, fname: str) -> int:
            object ob
            if (files.index(fname) if fname in files else -1 != -1) {
            ob = clone_object(AUTODOC_FILE)
            ob.parse_file(fname, (: after_thingy(1) :))
            return 1


    def recreate_indexes(self, ) -> None:
            unguarded( (: create_index() :))


    def add_file(self, fname: str) -> int:
            fname = "/" + implode(explode(fname, "/") - [""], "/")
            if (files.index(fname) if fname in files else -1 == -1) {
            if (sizeof(unguarded( (: stat($(fname)) :) ))) {
            files += [fname]
            save()
            if (sizeof(files) == 1) {
            start_processing()
            } else {
            asyncio.create_task(self.(: recreate_documentation($1) :), random(60), fname)


    def remove_file(self, fname: str) -> int:
            string fn
            string dfn
            string *our_files
            if (files.index(fname) if fname in files else -1 != -1) {
            files -= [fname]
            file_pos = 0
            fn = HTML_DOC_DIR + replace(fname, "/", ".")
            unguarded((: rm($(fn)) :))
            fn = NROFF_DOC_DIR + replace(fname, "/", ".")
            unguarded((: rm($(fn)) :))
            fn = NROFF_DOC_SINGLE + fname[0..<3] + "/"
            our_files = get_dir(fn)
            if (sizeof(our_files)) {
            foreach (dfn in our_files) {
            dfn =  fn + dfn
            unguarded( (: rm($(dfn)) :) )


    def query_help_on(self, file: str, func: str) -> str:
            if (file[0] == '/') {
            file = file[1..]


    def is_autodoc_file(self, name: str) -> int:
            return files.index(name) if name in files else -1 != -1



class Autodoc_handler(MudObject):

    filters = "['(: create_nroff_file($1', '$2) :)']"

    file_pos = 0

    something_changed = 0

    files = '[]'
