# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/finger.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .utilities import CLOTHING_HANDLER
from ..driver import MudObject, Player, driver
import asyncio

    def finger_commands(self, ) -> None:
            add_command("password", self, "", (: change_password() :))
            add_command("passwd", self, "", (: change_password() :))


    def set_desc(self, str: str) -> None:
            if (!player_info) {
            player_info = ([ ])


    def query_desc(self, ) -> str:
            if (!player_info  ||  undefinedp(player_info["desc"])) {
            return ""


    def set_zone_desc(self, zone: str, desc: str) -> None:
            if (!player_info["zone desc"]) {
            player_info["zone desc"] = ([ ])


    def query_zone_desc(self, zone: str) -> str:
            if (!player_info["zone desc"]) {
            return 0


    def query_main_zone_desc(self, wearing: Any) -> str:
            object bing
            string zone
            string type
            string eq_type
            string str
            mixed types
            mapping covered
            if (!sizeof(player_info["zone desc"])) {
            return ""


    def set_password(self, pass: str) -> None:
            if (file_name(previous_object())[0..12] == "/secure/login" ||
            file_name(previous_object())[0..13] == "/secure/nlogin") {
            password = pass


    def set_rhosts(self, ips: str) -> None:
            if(file_name(previous_object())[0..18] != "/cmds/player/access" &&
            file_name(previous_object())[0..19] != "/cmds/lord/authorise")
            return
            if(!player_info)
            player_info = ([ ])
            player_info["allowed_ips"] = ips


    def query_real_name(self, ) -> str:
            if (!player_info) {
            return 0


    def set_real_name(self, str: str) -> None:
            if (!player_info) {
            player_info = ([ ])


    def query_where(self, ) -> str:
            if (!player_info) {
            return ""


    def set_where(self, str: str) -> None:
            if (!player_info) {
            player_info = ([ ])


    def query_birthday(self, ) -> str:
            if (!player_info) {
            return UNKNOWN_BIRTHDAY


    def set_birthday(self, i: str) -> None:
            if (!player_info) {
            player_info = ([])


    def query_is_birthday_today(self, ) -> int:
            string cmonth
            string dummy
            string bmonth
            int cdate
            int bdate
            if (sscanf(ctime(time()), "%s %s %d %s", dummy, cmonth, cdate, dummy)!=4) {
            return 0


    def query_email(self, ) -> str:
            if(file_name(previous_object())[0..13] != "/secure/finger" &&
            file_name(previous_object())[0..27] != "/obj/handlers/player_handler" &&
            file_name(previous_object())[0..28] != "/obj/handlers/options_handler") {
            return ""


    def query_homepage(self, ) -> str:
            if (!player_info) {
            player_info = ([ ])


    def finger_set(self, ) -> int:
            if (!player_info ||
            player_info == ([ ]) ||
            sizeof(keys(player_info)) == 1) {
            return 0



class Finger(MudObject):
