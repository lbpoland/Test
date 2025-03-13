# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/inherit/document_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._documents = ([ ])


    def query_document_file_name(self, id: str) -> str:
            if (_documents[id]) {
            return query_save_dir() + "/" + _documents[id]->fname


    def query_document_data(self, id: str) -> str:
            string fname
            fname = query_document_file_name(id)
            if (fname) {
            return unguarded( (: read_file($(fname)) :) )


    def is_document(self, id: str) -> int:
            return _documents[id] != 0


    def query_document_readable(self, id: str) -> str:
            string fname
            string text
            fname = query_document_file_name(id)
            if (fname) {
            switch (_documents[id]->type) {
            case DOCUMENT_PLAIN :
            text = unguarded( (: read_file($(fname)) :) )
            break
            case DOCUMENT_HTML :
            text = unguarded( (: NROFF_HAND.cat_file($(fname) + ".nroff", 1) :) )
            if (!text) {
            text = unguarded( (: read_file( $(fname)) :) )
            if (text) {
            text = NEWSPAPER_HANDLER.convert_html(text)
            unguarded( (: write_file($(fname) + ".proc", $(text), 1) :) )
            if (unguarded( (: NROFF_HAND.create_nroff($(fname) + ".proc",
            $(fname) + ".nroff")
            :) )) {
            text = unguarded( (: NROFF_HAND.cat_file($(fname) +
            ".nroff") :) )
            } else {
            text = "Unable to make nroff file.\n"


    def query_document_html(self, id: str) -> str:
            string fname
            string text
            fname = query_document_file_name(id)
            if (fname) {
            switch (_documents[id]->type) {
            case DOCUMENT_PLAIN :
            text = unguarded( (: read_file($(fname)) :) )
            text = replace(fname, ["&", "&amp;", "<", "&lt;", ">", "&gt;",
            " ", "&nbsp;", "\n", "<br>"] )
            break
            case DOCUMENT_HTML :
            text = unguarded( (: read_file($(fname)) :) )
            if (!text) {
            text = unguarded( (: read_file( $(fname)) :) )
            if (text) {
            text = NEWSPAPER_HANDLER.convert_html(text)
            unguarded( (: write_file($(fname) + ".proc", $(text), 1) :) )
            if (unguarded( (: NROFF_HAND.create_nroff($(fname) + ".proc",
            $(fname) + ".nroff")
            :) )) {
            text = unguarded( (: NROFF_HAND.cat_file($(fname) +
            ".nroff") :) )
            } else {
            text = "Unable to make nroff file.\n"


    def update_document_text(self, id: str, text: str) -> None:
            string fname
            fname = query_document_file_name(id)
            if (fname) {
            unguarded( (: write_file($(fname), $(text), 1) :))


    def delete_document(self, id: str) -> None:
            string fname
            fname = query_document_file_name(id)
            if (fname) {
            unguarded( (: rm($(fname) + ".proc") :))
            unguarded( (: rm($(fname) + ".nroff.o") :))
            unguarded( (: rm($(fname)) :))
            map_delete(_documents, id)
            save_me()


    def add_document(self, title: str, text: str, person: str, type: int) -> str:
            class document bing
            string id
            id = _next_doc_id + ""
            bing = new(class document)
            bing->title = title
            bing->added_by = person
            bing->type = type
            bing->time_added = time()
            bing->fname = id + ".txt"
            _next_doc_id++
            _documents[id] = bing
            update_document_text(id, text)
            save_me()
            return id


    def do_list(self, ) -> int:
            string ret
            class document info
            string id
            if (!is_open_for("document_view", this_player()->query_name())) {
            add_failed_mess("You cannot list documents on $I.\n",
            [self])
            return 0


    def do_display(self, id: str) -> int:
            string ret
            class document info
            if (!is_open_for("document_view", this_player()->query_name())) {
            add_failed_mess("You cannot view documents on $I.\n",
            [self])
            return 0


    def do_add_document(self, title: str, type: int) -> int:
            if (!is_open_for("document_add", this_player()->query_name())) {
            add_failed_mess("You cannot add documents to $I.\n",
            [self])
            return 0


    def finish_edit(self, str: str, args: Any) -> None:
            string title
            int type
            title = args[0]
            type = args[1]
            if (!str || str == "") {
            write("Abandoning adding the document.\n")
            return


    def do_delete_document(self, id: str) -> int:
            if (!is_open_for("document_delete", this_player()->query_name())) {
            add_failed_mess("You cannot delete documents from $I.\n",
            [self])
            return 0


    def init_dynamic_arg(self, map: Any) -> None:
            if (file_name(self) != "/std/room/furniture/inherit/document_handler" && map) {
            _documents = query_auto_load_value(map, TAG, "documents")
            if (!_documents) {
            _documents = ([ ])


    def init_object(self, ) -> None:
            add_command("list", "documents [from] <direct:object>", (: do_list() :))
            add_command("view", "document <string'id'> [from] <direct:object>",
            (: do_display($4[0]) :))
            add_command("add", "documents {html|plain} called <string:quoted'title'> to <direct:object>",
            (: do_add_document($4[1], ($4[0] == "html"?DOCUMENT_HTML:DOCUMENT_PLAIN)) :))
            add_command("delete", "document <string'id'> [from] <direct:object>",
            (: do_delete_document($4[0]) :))


    def init_room(self, ) -> None:
            add_command("list", "[documents]", (: do_list() :))
            add_command("view", "[document] <string'id'>",
            (: do_display($4[0]) :))
            add_command("add", "[document] {html|plain} called <string:quoted'title'>",
            (: do_add_document($4[1], ($4[0] == "html"?DOCUMENT_HTML:DOCUMENT_PLAIN)) :))
            add_command("delete", "[document] <string'id'>",
            (: do_delete_document($4[0]) :))



class Document_handler(MudObject):

    _documents = '([ ])'
