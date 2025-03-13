# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/chfn.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            write("Change finger information.\n")
            write("Pressing return at the prompts will take the default.  The default "
            "is the option in []'s.\n")
            write("What real name do you wish to use ["+TP.query_real_name()+"] ? ")
            input_to("real_name")
            return 1


    def real_name(self, str: str) -> int:
            string real_name
            str = strip_colours(str)
            real_name = TP.query_real_name()
            if (str && str != "") {
            if (str == "none") {
            real_name = 0
            } else {
            real_name = str


    def get_where(self, str: str) -> int:
            string where
            str = strip_colours(str)
            where = TP.query_where()
            if (str && str != "") {
            if (str == "none") {
            where = 0
            } else {
            where = str


    def convert_birthday(self, str: str) -> str:
            #undef MONTHS
            #define MONTHS ["January", "February", "March", "April", "May", "June", \
            "July", "August", "September", "October", "November", "December"]
            int day, month, tot
            string retval
            sscanf(str, "%d", tot)
            day = tot / 100
            month = tot % 100
            switch(day) {
            case 11:
            retval = "11th"; break
            case 12:
            retval = "12th"; break
            case 13:
            retval = "13th"; break
            default:
            switch(day%10) {
            case 1:
            retval = day+"st"; break
            case 2:
            retval = day+"nd"; break
            case 3:
            retval = day+"rd"; break
            default:
            retval = day+"th"


    def valid_birthday(self, str: str) -> int:
            #define LENGTHS [0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
            int tot, month, day
            if(strlen(str) != 4) {
            return 0


    def birthday(self, str: str) -> None:
            string birth_day
            birth_day = TP.query_birthday()
            if (str == "") {
            if (birth_day)
            write("Birthday unchanged from "+birth_day+".\n")
            else
            write("Birthday left as blank.\n")
            } else {
            if(birth_day != "Unknown") {
            write("You can't change when you were born! Please ask a Creator or "
            "a Lord to change it if you made an error.\n")
            } else if(!valid_birthday(str)) {
            write("Invalid Birthday.  Birthday cleared.\n")
            birth_day = 0
            } else {
            birth_day = convert_birthday(str)
            write("Birthday set to " + birth_day + ".\n")
            TP.birthday_gifts()


    def get_email(self, str: str) -> None:
            string email
            email = TP.query_email()
            str = strip_colours(str)
            if (str == "") {
            if (!email || email == "") {
            write("Email address left blank.\n")
            } else {
            write("Email address left as "+email+".\n")


    def get_home_page(self, str: str) -> None:
            str = strip_colours(str)
            if (str == "") {
            if (!TP.query_homepage()) {
            write("Home page left as blank.\n")
            } else {
            write("Home page left as "+TP.query_homepage()+"\n")



class Chfn(MudObject):
