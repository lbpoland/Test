# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/stats.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def get_stat(self, s: str) -> str:
            switch(s) {
            case "S": return "str"
            case "I": return "int"
            case "W": return "wis"
            case "D": return "dex"
            case "C": return "con"


    def cmd(self, ) -> int:
            object user
            string class_ob, stat, str
            mapping stats
            int val, m, i
            mapping tmp
            mapping mode
            stats = ([ ])
            foreach(user in users()) {
            if(user.query_creator() || user.query_known_command("rearrange"))
            continue
            tmp = ([])
            class_ob = user.query_class_ob()
            if(class_ob)
            class_ob = class_ob.query_name()
            if(stats[class_ob])
            tmp = stats[class_ob]
            else {
            foreach(stat in STATS) {
            tmp[stat] = [0, 0, 0, 0]


    def guild(self, gstr: str) -> int:
            string user, stat, gob, tstr, class
            mapping count, total
            int val, i
            foreach(class in GUILDS) {
            if(gstr && gstr != class && gstr != class+"s" &&
            gstr != class+"es")
            continue
            gob = "/std/classs/" + class
            count = ([ ])
            total = ([ ])
            foreach(user in users()) {
            if(user.query_class_ob() != gob || user.query_creator() ||
            user.query_known_command("rearrange"))
            continue
            foreach(stat in STATS) {
            total[stat] += 1
            val = call_other(user, "query_real_" + stat)
            if(!count[stat])
            count[stat] = ([ val : 1 ])
            if(!count[stat][val])
            count[stat][val] = 1
            else
            count[stat][val] += 1


    def stats(self, sstr: str) -> int:
            string user, class, tstr, st
            mapping count, total
            int val, i
            foreach(st in STATS) {
            if(sstr && st[0] != sstr[0])
            continue
            count = ([ ])
            total = ([ ])
            foreach(user in users()) {
            if(user.query_creator() || user.query_known_command("rearrange"))
            continue
            class = replace(user.query_class_ob(), "/std/classs/", "")
            if(!class)
            continue
            val = call_other(user, "query_real_" + st)
            if(!count[class])
            count[class] = ([ val : 1 ])
            else
            count[class][val] += 1
            total[class] += 1


    def primaries(self, ) -> int:
            string class, skill, st, stats
            mapping count
            int i, total
            string str
            write("Guild Primaries\n")
            foreach(class in GUILDS) {
            write(class + "\n")
            count = ([ ])
            total = 0
            str = ""
            foreach(skill in ("/std/classs/" + class)->query_skills()) {
            stats = "/std/skills"->query_skill_stat(skill)
            total += sizeof(stats)
            for(i=0; i<sizeof(stats); i++) {
            st = get_stat(stats[i..i])
            count[st] += 1


    def skills(self, ) -> int:
            string tree, skill, st, stats
            mapping count
            int i, total
            string str
            write("Guild Primaries\n")
            foreach(tree in TREES) {
            write(tree + "\n")
            count = ([ ])
            total = 0
            str = ""
            foreach(skill in ("/std/skills")->query_all_children(tree)) {
            stats = "/std/skills"->query_skill_stat(skill)
            total += sizeof(stats)
            for(i=0; i<sizeof(stats); i++) {
            st = get_stat(stats[i..i])
            count[st] = 1



class Stats(MudObject):
