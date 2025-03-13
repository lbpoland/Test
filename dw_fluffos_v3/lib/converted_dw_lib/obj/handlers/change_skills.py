# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/change_skills.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_level_in(self, skills: Any, skill: str) -> int:
            string *bits
            if ( !undefinedp( skills[ skill ] ) )
            return skills[ skill ]
            bits = explode( skill, "." )
            if ( sizeof( bits ) == 1 )
            return 0
            bits = delete( bits, sizeof( bits ) - 1, 1 )
            skill = implode( bits, "." )
            return query_level_in( skills, skill )


    def change_skills(self, thing: MudObject) -> None:
            int i, total
            mapping skills
            skills = (mapping)thing.query_skills()
            if ( !m_sizeof( skills ) )
            return
            for ( i = 0; i < sizeof( OLD_SKILLS ); i++ ) {
            total += query_level_in( skills, OLD_SKILLS[ i ] )
            if ( !undefinedp( skills[ OLD_SKILLS[ i ] ] ) )
            skills = m_delete( skills, OLD_SKILLS[ i ] )


    def query_minimum_skill_xp(self, lvl: int) -> int:
            int i
            int xp
            xp = 0
            for (i = 0; i < lvl; i++) {
            xp += ( DEFAULT_COST * STD_COST * 100 ) / (( LEVEL_DIV + 1) * 500)


    def change_language_skills(self, thing: MudObject, lev: int) -> None:
            int i
            int total_xp
            mapping skills
            string *bits
            string start
            string *langs
            string health
            skills = thing.query_skills()
            if (!sizeof(skills))
            return
            bits = keys(skills)
            health = skills["other.health"]
            start = "other.language."
            total_xp = 0
            for (i = 0; i < sizeof(bits); i++) {
            if (bits[i][0..strlen(start)-1] == start) {
            total_xp += query_minimum_skill_xp(skills[bits[i]])
            map_delete(skills, bits[i])


    def change_skills_epsilon(self, thing: MudObject) -> None:
            int lvl, rest
            mapping skills
            string *bits
            skills = thing.query_skills()
            if (!sizeof(skills))
            return
            bits = keys(skills)
            tell_object(thing, "A squirrel appears and says: I'm just updating your "
            "skill tree, will be just a jiffy.\n")
            lvl = skills["covert.sleight-of-hand"]
            if(lvl > 0) {
            m_delete(skills, "covert.sleight-of-hand")
            if(lvl > 300) {
            rest = lvl - 300
            lvl = 300
            if(rest > 600) {
            lvl += 300
            rest -= 600
            lvl += rest / 5
            } else
            lvl += rest / 2


    def new_skill_value(self, sk: int) -> int:
            float f = 1000.0
            float k = 0.3
            if(sk == 0)
            return 0
            return to_int(f * log( 1.0 + sk/(f + sk * k) ) + 0.5)


    def change_skills_zeta(self, thing: MudObject) -> None:
            mapping skills
            string *bits, bit
            skills = thing.query_skills()
            if (!sizeof(skills))
            return
            bits = keys(skills)
            tell_object(thing, "A small blue frog appears and says: I'm just updating "
            "your skill levels, this won't take a second.\n")
            foreach(bit in bits) {
            if(bit[0..13] != "other.language" &&
            SKILL_OB.query_immediate_children(bit) == [})) {
            skills[bit] = new_skill_value(skills[bit])
            skills = recalc_parents(skills, bit)


    def fixup_stats(self, thing: MudObject) -> None:
            mapping values
            mapping changes
            int stat_total
            string str
            changes = ([ ])
            values = ([
            "con" : thing.query_real_con(),
            "dex" : thing.query_real_dex(),
            "int" : thing.query_real_int(),
            "wis" : thing.query_real_wis(),
            "str" : thing.query_real_str()
            ])
            stat_total = values["con"] + values["dex"] + values["wis"] + values["str"] +
            values["int"]
            if (stat_total > 65) {
            if (thing.query_real_con() > 8) {
            thing.adjust_con(-1)
            stat_total--
            values["con"]--
            changes["con"]++


    def change_skills_eta(self, thing: MudObject) -> None:
            mapping skills
            string bit, effect
            class tactics tactics
            int eff
            tactics = new(class tactics,
            attitude : "neutral",
            response : "neutral",
            parry : "both",
            parry_unarmed : 0,
            mercy : "ask",
            focus_zone : 0,
            ideal_distance : 0)
            thing.set_tactics(tactics)
            skills = thing.query_skills()
            if(!sizeof(skills))
            return
            tell_object(thing, "An armadillo appears out of nowhere and says: "
            "I'm just updating your skills, this won't take a second.\n")
            foreach(bit in keys(ETA_CHANGES)) {
            await thing.send("Mapping " + bit + " to " + ETA_CHANGES[bit] + ".\n")
            skills[ETA_CHANGES[bit]] = skills[bit]
            map_delete(skills, bit)


    def entering(self, name: str, type: str) -> None:
            object thing
            int lvl
            if ( type != LOGIN )
            return
            if ( !( thing = find_player( name ) ) )
            return
            switch((string)thing.query_property( "skills version" )) {
            case VERSION:
            change_skills( thing )
            case VERSION_2:
            change_language_skills( thing, lvl )
            case VERSION_3:
            change_skills_epsilon( thing )
            case VERSION_4:
            change_skills_zeta(thing)
            case VERSION_5:
            change_skills_eta(thing)
            default:
            thing.add_property("skills version", VERSION_6)
            return



class Change_skills(MudObject):
