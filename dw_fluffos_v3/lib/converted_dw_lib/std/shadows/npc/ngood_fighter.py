# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/npc/ngood_fighter.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.specials = []
            self.weapons = ([ ])


    def good_fighter_setup(self, ) -> None:
            {
            int adjust
            int lvl
            int *args = arg()
            if (!args || !arrayp(args) || sizeof(args) != 2)
            return
            specials = [})
            bluntorsharp = args[0]
            dodgeorparry = args[1]
            lvl = player.query_level()
            check_skill("other.perception", lvl / 2)
            check_skill("other.health", lvl)
            adjust = lvl * 3 / 4
            if (bluntorsharp == USE_PIERCE) {
            check_skill("fighting.combat.melee.blunt", lvl - adjust)
            check_skill("fighting.combat.melee.sharp", lvl - adjust)
            check_skill("fighting.combat.melee.pierce", lvl + adjust)
            check_skill("fighting.combat.melee.unarmed", lvl - adjust)
            } else if (bluntorsharp == USE_BLUNT) {
            check_skill("fighting.combat.melee.blunt", lvl + adjust)
            check_skill("fighting.combat.melee.sharp", lvl - adjust)
            check_skill("fighting.combat.melee.pierce", lvl - adjust)
            check_skill("fighting.combat.melee.unarmed", lvl - adjust)
            } else if (bluntorsharp == USE_SHARP) {
            check_skill("fighting.combat.melee.blunt", lvl - adjust)
            check_skill("fighting.combat.melee.sharp", lvl + adjust)
            check_skill("fighting.combat.melee.pierce", lvl - adjust)
            check_skill("fighting.combat.melee.unarmed", lvl - adjust)
            } else if (bluntorsharp == USE_UNARMED) {
            check_skill("fighting.combat.melee.blunt", lvl - adjust)
            check_skill("fighting.combat.melee.sharp", lvl - adjust)
            check_skill("fighting.combat.melee.pierce", lvl - adjust)
            check_skill("fighting.combat.melee.unarmed", lvl + adjust)
            } else {
            check_skill("fighting.combat.melee.blunt", lvl)
            check_skill("fighting.combat.melee.sharp", lvl)
            check_skill("fighting.combat.melee.pierce", lvl)
            check_skill("fighting.combat.melee.unarmed", lvl)


    def event_fight_in_progress(self, attacker: MudObject, opponent: MudObject) -> None:
            {
            object ts, temp, weapon
            int chance
            string cmd, str
            ts = player
            ts.event_fight_in_progress(attacker, opponent)
            if (victim && !objectp(victim))
            victim = 0
            if (victim && !interactive(victim))
            victim = 0
            if (victim && environment(victim) != environment(player))
            victim = 0
            if (victim && victim != attacker)
            return
            if (!victim) {
            victim = attacker
            if (!victim)
            return



class Ngood_fighter(MudObject):

    specials = '[]'

    weapons = '([ ])'
