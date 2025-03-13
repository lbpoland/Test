# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/autodoc/autodoc_html.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_html_file(self, file: MudObject, output: str) -> None:
            int i
            mapping stuff
            string *pub_funcs
            string *pro_funcs
            string *defs
            string *bits
            string name
            string bing
            bits = explode(file.query_file_name(), "/")
            name = bits[sizeof(bits)-1]
            bing = "<html><head><title>"
            bing += "File " + name +
            "\n</title></head><body bgcolor=\"#ffffff\" TEXT=\"#000030\" LINK=\"#4a529c\" VLINK=\"#b57339\">"
            bing += "[ <a href=\"index.html\">Package Index</a></code> | "
            bing += "<a href=\"index_std.html\">Mudlib Index</a></code> | "
            bing += "<a href=\"index_eff.html\">Effect Index</a></code> ]<br>"
            stuff = file.query_main_docs()
            if (stuff["main"]) {
            bing += "<h2>File " + file.query_file_name() +
            "</h2>"
            bing += implode(stuff["main"], " ")
            if (stuff["see"]) {
            bing += "<p><b>See also:</b><br>" +
            query_multiple_short(
            map(stuff["see"], (: create_href($1) :)))


    def create_html_index_file(self, index: str, letter: str, output: str) -> None:
            int i
            string name
            string bing
            bing = "<html><head><title>\nIndex of " + letter +
            "\n</title></head><body bgcolor=\"#ffffff\" TEXT=\"#000030\" LINK=\"#4a529c\" VLINK=\"#b57339\">\n"
            bing += "<img align=left src=\"" + CONFIG_EXTERNAL_WEB_ADDRESS +
            "pics/dw4.gif\">\n"
            "<p align=right><code><a href=\"index.html\">"
            "Main Index</a></code></p>\n"
            "<h2>Index of " + letter + "</h2>\n"
            "<h3><i>Letters can change the world, remove the l "
            "from world and you have word</i></h3>\n"
            "<br clear=both>\n"
            "<hr><dl>\n"
            index = sort_array(index, (: strcasecmp($1[0], $2[0]) ? strcasecmp($1[0], $2[0]) :
            strcasecmp($1[1], $2[1]) :) )
            for (i = 0; i < sizeof(index); i++) {
            name = replace(index[i][AUTO_INDEX_FILE_NAME], "/", ".")
            if (name[0] == '.') {
            name = name[1..]


    def create_main_index(self, chars: Any, output_dir: str) -> None:
            int i
            string output_index
            string output_eff
            string output_cre
            string *files
            mixed *stuff
            string str
            string fname
            string *index
            mapping summaries
            function write_all
            string bing_file
            string fluff
            summaries = AUTODOC_HANDLER.query_summary_map()
            output_index = output_dir + "index_std.html"
            output_eff = output_dir + "index_eff.html"
            output_cre = output_dir + "index_cre.html"
            bing_cre = ""
            bing_eff = ""
            bing_file = ""
            bing_index = ""
            rm (output_eff)
            rm (output_index)
            rm (output_cre)
            write_all = (: bing_eff += $1,
            bing_cre += $1,
            bing_index += $1 :)
            evaluate(write_all, "<html><head><title>\n")
            evaluate(write_all, "" + mud_name() + " autodoc index\n</title></head>\n"
            "<body bgcolor=\"#ffffff\" TEXT=\"#000030\" "
            "LINK=\"#4a529c\" VLINK=\"#b57339\">\n")
            bing_index += "<img align=left src=\"" + CONFIG_EXTERNAL_WEB_ADDRESS +
            "/pics/dw4.gif\">\n"
            "<h2>" + mud_name() + " Documentation</h2>\n"
            "<h3><i>Where cabbages evaporate in the sun</i></h3>\n"
            "<br clear=both>\n"
            bing_eff += "<img align=left src=\"" + CONFIG_EXTERNAL_WEB_ADDRESS +
            "/pics/dw4.gif\">\n"
            "<h2>" + mud_name() + " Effect Documentation</h2>\n"
            "<h3><i>Where your consequences are vanquished</i></h3>\n"
            "<br clear=both>\n"
            bing_cre += "<img align=left src=\"" + CONFIG_EXTERNAL_WEB_ADDRESS +
            "pics/dw4.gif\">\n"
            "<h2>" + mud_name() + " Creator Documentation</h2>\n"
            "<h3><i>Blue fluff?  No red and scruffy!</i></h3>\n"
            "<br clear=both>\n"
            evaluate(write_all, "<h2>Function index</h2>\n")
            files = AUTODOC_HANDLER.query_files()
            files = sort_array(files, (: strcasecmp :) )
            index = sort_array(keys(chars), (: strcasecmp :) )
            for (i = 0; i < sizeof(index); i++) {
            if (i > 0) {
            evaluate(write_all, ", ")



class Autodoc_html(MudObject):
