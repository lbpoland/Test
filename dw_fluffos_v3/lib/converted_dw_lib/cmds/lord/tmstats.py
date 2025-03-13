# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/tmstats.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            string file, cmd, tmp
            mapping awards, summary, obs
            int lvl, i, total, files
            return do_summary()
            if(!str)
            str=""
            tmp = ""
            obs = ([ ])
            summary = ([ ])
            foreach(file in get_dir(STATS_DIR+str+"*")) {
            file = file[0..sizeof(file)-3]
            files++
            awards = TASKER.query_stats(file)
            foreach(lvl in keys(awards)) {
            foreach(cmd in keys(awards[lvl])) {
            total += awards[lvl][cmd]
            obs[cmd] += 1


    def do_summary(self, ) -> int:
            string skill
            mapping sum, stats
            int i
            int tries, awards
            stats = TASKER.query_stats("summary")
            sum = stats
            foreach(skill in keys(sum)) {
            if("/std/skills"->query_skill([skill]) != skill)
            continue
            printf("Skill: %s \n", skill)
            printf("  Level 0..49:       Tries: %d, Awards: %d, ",
            sum[skill][0][0], sum[skill][0][1])
            if(sum[skill][0][1] == 0)
            printf("Ratio: ?\n")
            else
            printf("Ratio: 1/%d\n", sum[skill][0][0]/(sum[skill][0][1]))
            printf("  Level 50..149:     Tries: %d, Awards: %d, ",
            sum[skill][1][0], sum[skill][1][1])
            if(sum[skill][1][1] == 0)
            printf("Ratio: ?\n")
            else
            printf("Ratio: 1/%d\n", sum[skill][1][0]/(sum[skill][1][1]))
            printf("  Level 150..299:    Tries: %d, Awards: %d, ",
            sum[skill][2][0], sum[skill][2][1])
            if(sum[skill][2][1] == 0)
            printf("Ratio: ?\n")
            else
            printf("Ratio: 1/%d\n", sum[skill][2][0]/(sum[skill][2][1]))
            printf("  Level 300..599:    Tries: %d, Awards: %d, ",
            sum[skill][3][0], sum[skill][3][1])
            if(sum[skill][3][1] == 0)
            printf("Ratio: ?\n")
            else
            printf("Ratio: 1/%d\n", sum[skill][3][0]/(sum[skill][3][1]))
            printf("  Level >= 600:      Tries: %d, Awards: %d, ",
            sum[skill][4][0], sum[skill][4][1])
            if(sum[skill][4][1] == 0)
            printf("Ratio: ?\n")
            else
            printf("Ratio: 1/%d\n", sum[skill][4][0]/(sum[skill][4][1]))
            tries = 0
            awards = 0
            for(i=0; i<3; i++) {
            tries += sum[skill][i][0]
            awards += sum[skill][i][1]



class Tmstats(MudObject):
