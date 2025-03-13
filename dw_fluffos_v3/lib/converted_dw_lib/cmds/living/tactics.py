# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/tactics.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            class tactics tactics
            tactics = (class tactics) this_player()->query_tactics()
            write("Your combat options are:\n\n" )
            write("   Attitude - "+ tactics->attitude +".\n" )
            write("   Response - "+ tactics->response +".\n" )
            #ifdef USE_SURRENDER
            write("   Mercy - "+ (tactics->mercy?tactics->mercy:"none") + ".\n")
            #endif
            write("   Focus - "+ (tactics->focus_zone?tactics->focus_zone:"none") + ".\n" )
            #ifdef USE_DISTANCE
            write("   Target distance - "+ (tactics->ideal_distance?tactics->ideal_distance:"none") + ".\n" )
            #endif
            write("You will use "+
            (tactics->attack == "both" ? "both hands" :
            "your "+ (tactics->attack?tactics->attack:"either") +" hand" ) +
            " to attack.\n" )
            write("You will use "+
            (tactics->parry == "both" ? "both hands" :
            "your "+ (tactics->parry?tactics->parry:"either") +" hand" ) +
            " to parry.\n" )
            write("\nYou will"+ ( tactics->parry_unarmed ? " " : " not " ) +
            "attempt to parry unarmed.\n" )
            return 1


    def attitude(self, word: str) -> int:
            class tactics my_tactics
            my_tactics = new(class tactics)
            my_tactics = (class tactics) this_player()->query_tactics()
            switch(word) {
            case "insane":
            case "offensive":
            case "neutral":
            case "defensive":
            case "wimp":
            if((my_tactics->attitude) == word) {
            write("Your attitude is already " + word + ".\n")
            } else {
            my_tactics->attitude = word
            write("Your attitude is now " + word + ".\n")
            this_player()->set_tactics(my_tactics)


    def response(self, word: str) -> int:
            class tactics my_tactics
            my_tactics = this_player()->query_tactics()
            switch(word) {
            case "dodge":
            case "neutral":
            case "parry":
            if(my_tactics->response == word) {
            write("Your response is already " + word + ".\n")
            } else {
            my_tactics->response = word
            write("Your response is now " + word + ".\n")
            this_player()->set_tactics(my_tactics)


    def parry(self, word: str) -> int:
            class tactics my_tactics
            my_tactics = this_player()->query_tactics()
            switch(word) {
            case "unarmed":
            my_tactics->parry_unarmed = 1 - my_tactics->parry_unarmed
            write("You will"+ ( my_tactics->parry_unarmed ? " " : " not " ) +
            "now attempt to parry unarmed.\n" )
            this_player()->set_tactics(my_tactics)
            return 1
            case "left":
            case "right":
            case "both":
            if(my_tactics->parry == word) {
            write("You are already using "+
            ( word == "both" ? "both hands" :
            "your "+ word +" hand" ) +" to parry.\n" )
            } else {
            my_tactics->parry = word
            write("You will now use "+
            ( word == "both" ? "both hands" :
            "your "+ word +" hand" ) +" to parry.\n" )
            this_player()->set_tactics(my_tactics)


    def attack(self, word: str) -> int:
            class tactics my_tactics
            my_tactics = this_player()->query_tactics()
            switch(word) {
            case "left":
            case "right":
            case "both":
            if(my_tactics->attack == word) {
            write("You are already using "+
            ( word == "both" ? "both hands" :
            "your "+ word +" hand" ) +" to attack.\n" )
            } else {
            my_tactics->attack = word
            write("You will now use "+
            ( word == "both" ? "both hands" :
            "your "+ word +" hand" ) +" to attack.\n" )
            this_player()->set_tactics(my_tactics)


    def focus(self, word: str) -> int:
            class tactics my_tactics
            my_tactics = this_player()->query_tactics()
            switch(word) {
            case "head":
            case "neck":
            case "chest":
            case "abdomen":
            case "arms":
            case "hands":
            case "legs":
            case "feet":
            case "upper body":
            case "lower body":
            if(my_tactics->focus_zone == word) {
            write("You are already focussing on your opponent's "+ word + ".\n")
            } else {
            my_tactics->focus_zone = word
            write("You will now focus on your opponent's "+ word + ".\n")
            this_player()->set_tactics(my_tactics)


    def distance(self, word: str) -> int:
            class tactics my_tactics
            my_tactics = this_player()->query_tactics()
            switch(word) {
            case "long":
            case "medium":
            case "close":
            case "hand-to-hand":
            if(my_tactics->ideal_distance == word) {
            write("You are already set for " + word + " range.\n")
            return 1


    def mercy(self, word: str) -> int:
            class tactics my_tactics
            my_tactics = this_player()->query_tactics()
            switch(word) {
            case "always":
            case "ask":
            case "never":
            if(my_tactics->mercy == word) {
            write("Your mercy is already " + word + ".\n")
            } else {
            my_tactics->mercy = word
            write("Your mercy is now "+ word +".\n" )
            this_player()->set_tactics(my_tactics)



class Tactics(MudObject):
