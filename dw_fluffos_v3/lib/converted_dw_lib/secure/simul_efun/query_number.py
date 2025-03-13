# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/query_number.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_num(self, n: int, limit: int) -> str:
            string ret
            int i
            if (limit && n>limit) return "many"
            if (n < 0) return "many"
            if (n > 99999) return "many"
            ret = 0
            if ((i = n/1000)) {
            n = n%1000
            if (!n)
            return number_as_string(i) + " thousand"
            ret = number_as_string(i) + " thousand"


    def number_as_string(self, n: int) -> str:
            string ret
            if (!n) return "zero"
            if (n<20 && n>9) return ["ten", "eleven", "twelve", "thirteen",
            "fourteen", "fifteen", "sixteen", "seventeen",
            "eighteen", "nineteen"][n-10]
            ret = ["", "", "twenty", "thirty", "forty", "fifty", "sixty",
            "seventy", "eighty", "ninety"})[n/10]
            if ((n = n%10)&&(ret!="")) ret += "-"
            return ret + ["", "one", "two", "three", "four", "five", "six",
            "seven", "eight", "nine"})[n]


    def word_ordinal(self, num: int) -> str:
            string word = ""
            int    part
            switch (part = num % 100)  {
            case 0:
            word = "th"
            break
            case 1 .. 12:
            word = ({
            "first",   "second", "third", "fourth", "fifth",    "sixth",
            "seventh", "eighth", "ninth", "tenth",  "eleventh", "twelfth"
            })[part - 1]
            break
            case 13 .. 19:
            word = query_num(num % 100, 99999) + "th"
            break
            default:
            if (part % 10 == 0)  {
            word = ({
            "twentieth", "thirtieth", "fortieth", "fiftieth", "sixtieth",
            "seventieth", "eightieth", "ninetieth"
            })[part / 10 - 2]


    def query_times(self, num: int) -> str:
            string retval
            switch(num) {
            case 0:
            retval = ""
            break
            case 1:
            retval = "once"
            break
            case 2:
            retval = "twice"
            break
            default:
            retval = query_num(num, 0) + " times"



class Query_number(MudObject):
