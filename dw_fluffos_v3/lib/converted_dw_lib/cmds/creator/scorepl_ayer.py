# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/scorepl_ayer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def score_quests(self, obs: MudObject) -> int:
            object play
            foreach(play in obs) {
            write("Quests score for " + play.the_short() + ":\n")
            SCORE_CMD.score_quests(play)


    def score_stats(self, obs: MudObject) -> int:
            object play
            foreach(play in obs) {
            write("Stats score for " + play.the_short() + ":\n")
            SCORE_CMD.score_stats(play, "verbose")


    def score_normal(self, obs: MudObject) -> int:
            object play
            foreach(play in obs) {
            write("Score for " + play.the_short() + ":\n")
            SCORE_CMD.score_normal(play, "verbose")



class Scorepl_ayer(MudObject):
