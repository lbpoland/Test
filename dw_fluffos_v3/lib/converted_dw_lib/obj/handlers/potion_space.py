# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/potion_space.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def add_effect(self, ob: str, x1: int, x2: int, y1: int, y2: int) -> int:
            if (!stringp(ob)) {
            await this_player().send("Effect object must be a string.\n")
            return 0


    def remove_effect(self, ob: MudObject) -> int:
            int i
            for (i = 0; i < sizeof(effect_vols); i+=5)
            if (effect_vols[i] == ob) {
            effect_vols = effect_vols[0..i-1] + effect_vols[i+5..sizeof(effect_vols)]
            break


    def potion_drunk(self, ob: Any, coord: int, quantity: int) -> None:
            string *effects
            int i, pass_through
            effects = query_effect_at(coord)
            pass_through = 100
            for (i = 0; i < sizeof(effects) && pass_through; i++) {
            if (i > 0 && effects[i]->backdrop()) break
            effects[i]->action_drunk(ob, coord, quantity * pass_through / 100)
            pass_through = pass_through * effects[i]->query_pass_through(coord) / 100


    def potion_touch(self, ob: Any, coord: int, quantity: int) -> None:
            string *effects
            int i, pass_through
            effects = query_effect_at(coord)
            pass_through = 100
            for (i = 0; i < sizeof(effects) && pass_through; i++) {
            if (i > 0 && effects[i]->backdrop()) break
            effects[i]->action_touch(ob, coord, quantity * pass_through / 100)
            pass_through = pass_through * effects[i]->query_pass_through(coord) / 100


    def potion_smell(self, ob: Any, coord: int, quantity: int) -> None:
            string *effects
            int i, pass_through
            effects = query_effect_at(coord)
            pass_through = 100
            for (i = 0; i < sizeof(effects) && pass_through; i++) {
            if (i > 0 && effects[i]->backdrop()) break
            effects[i]->action_smell(ob, coord, quantity * pass_through / 100)
            pass_through = pass_through * effects[i]->query_pass_through(coord) / 100


    def potion_create(self, ob: Any, coord: int, quantity: int) -> None:
            string *effects
            int i, pass_through
            effects = query_effect_at(coord)
            pass_through = 100
            for (i = 0; i < sizeof(effects) && pass_through; i++) {
            if (i > 0 && effects[i]->backdrop()) break
            effects[i]->action_create(ob, coord, quantity * pass_through / 100)
            pass_through = pass_through * effects[i]->query_pass_through(coord) / 100



class Potion_space(MudObject):
