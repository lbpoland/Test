# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/npc/good_fighter.c (2003 FluffOS v3) for Forgotten Realms MUD
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
            adjust += (lvl / 3)
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
            object ts, weapon
            int chance
            string cmd
            ts = player
            ts.event_fight_in_progress(attacker, opponent)
            if(ts.query_specific_gp("fighting") < 50)
            return
            if (victim && !objectp(victim))
            victim = 0
            if (victim && !interactive(victim))
            victim = 0
            if (victim && environment(victim) != environment(player))
            victim = 0
            if (victim && victim != attacker)
            return
            if (!victim) {
            if(ts.query_attacker_list(.index(attacker) if attacker in ts.query_attacker_list( else -1) != -1)
            victim = attacker
            if (!victim)
            return



class Good_fighter(MudObject):

    specials = '[]'

    weapons = '([ ])'
