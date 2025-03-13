# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/living/combat.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._combat = new(class combat_information,
            self._surrender = new(class surrender_information,


    def __init__(self):
            self._combat = new(class combat_information,
            self._surrender = new(class surrender_information,
            private void init_tactics() {
            if(!classp(_tactics) || sizeof(_tactics) != 8) {
            _tactics = new(class tactics,
            attitude : "neutral",
            response : "neutral",
            parry : "both",
            attack : "both",
            parry_unarmed : 0,
            mercy : "ask",
            focus_zone : 0,
            ideal_distance : 0)


    def combat_debug(self, fmt: str, args: Any) -> None:
            if(userp(self))
            self->event_inform(self,
            sprintf("%s " + fmt,
            self.query_name(), args ...),
            "combat-debug", self)
            event(environment(self), "inform",
            sprintf("%s " + fmt, self.query_name(), args ...),
            "combat-debug", self)


    def query_can_attack(self, ) -> int:
            if(self.query_property(PASSED_OUT) ||
            self.query_property("dead") ||
            self.query_auto_loading() ||
            self.query_hp() < 0 ||
            self.query_casting_spell() ||
            (userp(self) && !interactive(self)) ||
            self.query_property("cannot attack"))
            return 0
            return 1


    def query_can_defend(self, ) -> int:
            if(self.query_property(PASSED_OUT) ||
            self.query_property("dead") ||
            self.query_auto_loading() ||
            self.query_hp() < 0 ||
            self.query_casting_spell() ||
            (userp(self) && !interactive(self)) ||
            self.query_property("cannot defend"))
            return 0
            return 1


    def clear_protection(self, attacker: MudObject, protector: MudObject) -> None:
            if(attacker.remove_protector(protector))
            protector->event_combat(protector,
            "You stop protecting "+ attacker.the_short() +
            " as "+ attacker.query_pronoun() +
            " moves to attack "+
            "you!\n", [}), 0)
            if(attacker.remove_defender(protector))
            protector->event_combat(protector, "You stop defending "+
            attacker.the_short() + " as "+
            attacker.query_pronoun() +" moves to attack "+
            "you!\n", [}), 0)


    def query_attackable(self, ) -> int:
            if(self.query_property(PASSED_OUT) ||
            self.dont_attack_me() ||
            self.attack_inhibit() ||
            self.query_property("dead") ||
            self.query_auto_loading() ||
            self.query_hp() < 0 ||
            (userp(self) && !interactive(self)))
            return 0
            return 1


    def query_defend(self, ) -> int:
            if(!query_attackable() || self.query_casting_spell() ||
            self.query_specific_gp("fighting") < 1)
            return 0
            return ((_tactics->response == "parry" || _tactics->response == "both") &&
            _combat->action_defecit < (COMBAT_ACTION_TIME * 4))


    def query_protect(self, ) -> int:
            if(!query_attackable() || self.query_casting_spell() ||
            self.query_specific_gp("fighting") < 1)
            return 0
            return (_combat->action_defecit < (COMBAT_ACTION_TIME * 4))


    def do_attack(self, ) -> None:
            class tasker_result result
            class attack att
            mixed *sp_result
            int modifier, tmp
            init_tactics()
            if(_callout)
            _callout = remove_asyncio.create_task(self."announce_intent")
            att = new(class attack,
            attacker : self,
            attacker_tactics : self.query_tactics(),
            attacker_specials : self.query_specials(),
            attacker_concentrating : self.query_concentrating(),
            attacker_defecit : self.query_action_defecit(),
            attacker_last_opponent : self.query_last_opponent(),
            attacker_last_weapon : self.query_last_weapon(),
            attacker_last_action : self.query_last_action(),
            attacker_last_result : self.query_last_result(),
            repeat : 0
            )
            sp_result = call_special(E_OPPONENT_SELECTION, att)
            if(!sp_result || sp_result[0] & R_CONTINUE || sp_result[0] & R_PASSTHRU)
            att = self.choose_opponent(att)
            else if(!(sp_result[0] & R_ABORT) && classp(sp_result[1]))
            att = (class attack)sp_result[1]
            else
            return
            if(!(att->opponent) || !(att->opponent)->attack_by(att->attacker)) {
            combat_debug("No opponent chosen, aborting attack")
            return


    def recalc_hunting_list(self, ) -> None:
            mixed ob
            object tmp
            tmp = 0
            foreach(ob in keys(_combat->attacker_list)) {
            if(stringp(ob) && find_player(ob))
            tmp = find_player(ob)
            else if(ob && objectp(ob))
            tmp = ob
            if(!tmp) {
            _combat->attacker_list = filter_mapping(_combat->attacker_list,(: $1 :))
            } else if(tmp.query_property("dead") ||
            !environment(tmp) ||
            base_name(environment(tmp)) == "/room/rubbish") {
            map_delete(_combat->attacker_list, ob)
            } else if(environment(tmp) != environment() ||
            !tmp.query_visible(self)) {
            _combat->hunting_list[ob] = time()
            map_delete(_combat->attacker_list, ob)


    def monitor_points(self, ) -> None:
            int hp
            int max
            string colour
            #ifdef UNUSED
            self.clear_gp_info()
            if ( (int)self.adjust_gp( -1 ) < 0 )
            return
            #endif
            hp = (int)self.query_hp()
            if(hp < 0)
            hp = 0
            max = (int)self.query_max_hp()
            switch ( ( hp * 100 ) / max) {
            case 50 .. 100 :
            colour = "%^GREEN%^"
            break
            case 20 .. 49 :
            colour = "%^YELLOW%^"
            break
            default :
            colour = "%^RED%^"


    def announce_intent(self, opponent: MudObject) -> None:
            int difficulty = 50
            object *things, ob
            if(environment(opponent) != environment(self))
            return
            switch(self.check_dark((int)environment(self)->query_light())) {
            case -2:
            case 2:
            difficulty *= 4
            break
            case -1:
            case 1:
            difficulty *= 2


    def heart_beat(self, ) -> None:
            int i
            if(!_combat->in_combat)
            return
            recalc_hunting_list()
            if(!sizeof(keys(_combat->attacker_list)) &&
            !sizeof(keys(_combat->hunting_list))) {
            for(i=0; i<sizeof(_combat->specials); i++)
            if(!((_combat->specials[i])->type & T_CONTINUOUS))
            _combat->specials -= [(_combat->specials)[i]]
            _combat->in_combat = 0
            adjust_action_defecit(-MAX_ACTION_DEFECIT)
            end_combat()
            return


    def register_special(self, type: int, events: int, callback: Any, data: Any) -> int:
            _combat->specials += [new(class combat_special,
            id : ++(_combat->special_id),
            type : type,
            events : events,
            callback : callback,
            data : data)]
            return _combat->special_id


    def remove_special(self, id: int) -> int:
            int i
            for(i=0; i<sizeof(_combat->specials); i++) {
            if((_combat->specials[i])->id == id) {
            _combat->specials -= [(_combat->specials)[i]]
            return 1


    def set_specials(self, combat_special: Any) -> None:
            _combat->specials = specials


    def set_special_data(self, id: int, data: Any) -> int:
            int i
            for(i=0; i<sizeof(_combat->specials); i++) {
            if((_combat->specials[i])->id == id) {
            _combat->specials[i]->data = data
            return 1


    def adjust_action_defecit(self, amount: int) -> None:
            _combat->action_defecit += amount
            if(_combat->action_defecit > MAX_ACTION_DEFECIT)
            _combat->action_defecit = MAX_ACTION_DEFECIT
            else if(_combat->action_defecit < MIN_ACTION_DEFECIT)
            _combat->action_defecit = MIN_ACTION_DEFECIT


    def query_action_defecit(self, ) -> int:
            class tactics query_tactics() {
            init_tactics()
            return copy(_tactics)


    def set_combat_distance(self, distance: str) -> None:
            object *query_protectors() {
            _combat->protectors -= [0]
            return copy(_combat->protectors + [}))


    def add_protector(self, thing: MudObject) -> int:
            if(thing == self ||
            thing.query_property("dead") ||
            thing.query_protectors(.index(self) if self in thing.query_protectors( else -1 +
            thing.query_defenders()) != -1 ||
            query_attacker_list(.index(thing) if thing in query_attacker_list( else -1)  != -1)
            return 0
            if(_combat->protectors.index(thing) if thing in _combat->protectors else -1 == -1)
            _combat->protectors += [thing]
            return 1


    def remove_protector(self, protector: MudObject) -> int:
            if(_combat->protectors.index(protector) if protector in _combat->protectors else -1 == -1)
            return 0
            _combat->protectors -= [protector]
            return 1


    def reset_protectors(self, ) -> None:
            _combat->protectors = [})


    def add_defender(self, thing: MudObject) -> int:
            if(thing == self ||
            thing.query_property("dead") ||
            thing.query_defenders(.index(self) if self in thing.query_defenders( else -1 +
            thing.query_protectors()) != -1 ||
            query_attacker_list(.index(thing) if thing in query_attacker_list( else -1)  != -1)
            return 0
            if(_combat->defenders.index(thing) if thing in _combat->defenders else -1 == -1)
            _combat->defenders += [thing]
            return 1


    def remove_defender(self, defender: MudObject) -> int:
            if(_combat->defenders.index(defender) if defender in _combat->defenders else -1 == -1)
            return 0
            _combat->defenders -= [defender]
            return 1


    def reset_defenders(self, ) -> None:
            _combat->defenders = [})


    def set_distance(self, opponent: MudObject, distance: int) -> int:
            if(userp(opponent)) {
            if(!_combat->attacker_list[opponent.query_name()])
            return 0
            _combat->attacker_list[opponent.query_name()] = distance
            } else {
            if(!_combat->attacker_list[opponent])
            return 0
            _combat->attacker_list[opponent] = distance


    def query_distance(self, opponent: MudObject) -> int:
            if(userp(opponent)) {
            if(!_combat->attacker_list[opponent.query_name()])
            return 0
            return _combat->attacker_list[opponent.query_name()]
            } else {
            if(!_combat->attacker_list[opponent])
            return 0
            return _combat->attacker_list[opponent]


    def remove_attacker_list(self, ob: MudObject) -> None:
            if(userp(ob)) {
            map_delete(_combat->attacker_list, ob.query_name())
            map_delete(_combat->hunting_list, ob.query_name())
            } else {
            map_delete(_combat->attacker_list, ob)
            map_delete(_combat->hunting_list, ob)


    def attack_by(self, opponent: MudObject) -> int:
            int starting
            if(!objectp(opponent) ||
            opponent == self ||
            !self.query_attackable() ||
            pk_check(self, opponent))
            return 0
            if(_combat->protectors.index(opponent) if opponent in _combat->protectors else -1 != -1)
            _combat->protectors -= [opponent]
            if(_combat->defenders.index(opponent) if opponent in _combat->defenders else -1 != -1)
            _combat->defenders -= [opponent]
            if(!sizeof(query_attacker_list()))
            starting = 1
            #ifdef USE_DISTANCE
            if(userp(opponent)) {
            if(!_combat->attacker_list[opponent.query_name()])
            _combat->attacker_list[opponent.query_name()] =
            opponent.query_distance(self)
            } else if(!_combat->attacker_list[opponent])
            _combat->attacker_list[opponent] = opponent.query_distance(self)
            #else
            if(userp(opponent)) {
            if(!_combat->attacker_list[opponent.query_name()])
            _combat->attacker_list[opponent.query_name()] = 1
            } else if(!_combat->attacker_list[opponent])
            _combat->attacker_list[opponent] = 1
            #endif
            if(starting) {
            _combat->action_defecit = (MAX_ACTION_DEFECIT - MIN_ACTION_DEFECIT) / 3
            start_combat(opponent)


    def attack_ob(self, opponent: MudObject) -> int:
            int starting, new_opponent
            if(!objectp(opponent) ||
            opponent == self ||
            !opponent.query_attackable() ||
            !self.query_attackable() ||
            pk_check(self, opponent))
            return 0
            if(_combat->protectors.index(opponent) if opponent in _combat->protectors else -1 != -1)
            _combat->protectors -= [opponent]
            if(_combat->defenders.index(opponent) if opponent in _combat->defenders else -1 != -1)
            _combat->defenders -= [opponent]
            if(!sizeof(query_attacker_list()))
            starting = 1
            else if(query_attacker_list(.index(opponent) if opponent in query_attacker_list( else -1) == -1)
            new_opponent = 1
            #ifdef USE_DISTANCE
            if(userp(opponent)) {
            if(!_combat->attacker_list[opponent.query_name()])
            _combat->attacker_list[opponent.query_name()] = INITIAL_DISTANCE
            } else {
            if(!_combat->attacker_list[opponent])
            _combat->attacker_list[opponent] = INITIAL_DISTANCE


    def stop_fight(self, opponent: MudObject) -> None:
            class combat_special tmp
            #if DEBUG == 2
            combat_debug("stop_fight called against %s", opponent.query_name())
            #endif
            if(!objectp(opponent))
            return
            if(userp(opponent)) {
            map_delete(_combat->attacker_list, opponent.query_name())
            map_delete(_combat->hunting_list, opponent.query_name())
            } else {
            map_delete(_combat->attacker_list, opponent)
            map_delete(_combat->hunting_list, opponent)


    def stop_all_fight(self, ) -> None:
            class combat_special tmp
            #if DEBUG == 2
            combat_debug("stop_all_fight called")
            #endif
            _combat->attacker_list = ([ ])
            _combat->hunting_list = ([ ])
            _combat->in_combat = 0
            #ifdef USE_SURRENDER  _surrender->from = [})
            _surrender->refusers = [})
            _surrender->to = [})
            #endif
            foreach(tmp in _combat->specials)
            if(!(tmp->type & T_CONTINUOUS))
            remove_special(tmp->id)
            end_combat()


    def stop_hunting(self, opponent: MudObject) -> None:
            if(userp(opponent))
            map_delete(_combat->hunting_list, opponent.query_name())
            else
            map_delete(_combat->hunting_list, opponent)
            if(!sizeof(query_attacker_list()))
            end_combat()


    def do_surrender(self, thing: MudObject) -> MudObject:
            mixed *attackers
            mixed att
            if(self.query_property("dead"))
            return 0
            death_helper(thing, 0)
            catch(DEATH.someone_surrendered(self))
            attackers = query_attacker_list()
            foreach(att in attackers) {
            att.stop_fight(self)


    def dont_attack_me(self, ) -> int:
            if(sizeof(_surrender->to))
            return 1
            else
            return 0


    def event_surrender(self, victim: MudObject, attackers: MudObject) -> None:
            object *offer
            offer = [})
            if (self == victim) {
            _surrender->refusers -= [0]
            _surrender->to -= [0]
            offer = filter(attackers, (: member_array($1, _surrender->refusers +
            _surrender->to) == -1 :))
            if(sizeof(offer)) {
            event(environment(), "combat",
            sprintf("%s kneels down and surrenders to %s.\n",
            self.one_short(), query_multiple_short(offer)),
            [self] + _surrender->to + _surrender->refusers, 0)
            self->event_combat(self,
            sprintf("%s kneel down and surrender to %s.\n",
            self.one_short(),
            query_multiple_short(offer)), [}), 0)
            offer.offered_surrender(victim)
            _surrender->to += offer


    def remove_surrenderer(self, victim: MudObject) -> None:
            _surrender->from -= [0, victim]
            return


    def offered_surrender(self, victim: MudObject) -> None:
            string mercy = self.query_combat_mercy()
            switch(mercy) {
            case "ask":
            if (interactive(self)) {
            _surrender->from -= [0, victim]
            _surrender->from += [victim]
            self->event_combat(self,
            victim.one_short() + " has surrendered to "
            "you.  Either \"accept " +
            victim.query_name() + "\" or \"reject " +
            victim.query_name() + ".\n", [}), 0)
            } else {
            if (self.query_accept_surrender(victim))
            victim.accepted_surrender(self)
            else
            victim.refused_surrender(self)


    def refused_surrender(self, attacker: MudObject) -> None:
            _surrender->to -= [0]
            if (_surrender->to.index(attacker) if attacker in _surrender->to else -1 == -1)
            return
            _surrender->to -= [attacker]
            _surrender->refusers -= [0]
            _surrender->refusers += [attacker]
            self.event_combat(self, attacker->one_short() +
            " refused your surrender\n", [}), 0)


    def accepted_surrender(self, attacker: MudObject) -> None:
            _surrender->to -= [0]
            if(_surrender->to.index(attacker) if attacker in _surrender->to else -1 == -1) {
            return


    def stopped_fighting(self, thing: MudObject) -> None:
            event( environment(), "stopped_fighting", thing )


    def fight_in_progress(self, thing: MudObject) -> None:
            event(environment(), "fight_in_progress", thing )


    def set_concentrating(self, thing: MudObject) -> int:
            if(userp(thing)) {
            if(!_combat->attacker_list[thing.query_name()])
            return 0
            #ifdef USE_DISTANCE
            _combat->attacker_list[thing.query_name()] =
            thing.query_distance(self)
            #else
            _combat->attacker_list[thing.query_name()] = 1
            #endif
            } else {
            if(!_combat->attacker_list[thing])
            return 0
            #ifdef USE_DISTANCE
            _combat->attacker_list[thing] = thing.query_distance(self)
            #else
            _combat->attacker_list[thing] = 1
            #endif


    def query_concentrating(self, ) -> MudObject:
            object thing
            thing = _combat->concentrating
            if(!thing || !objectp(thing))
            return 0
            if(userp(thing) && !_combat->attacker_list[thing.query_name()])
            return 0
            else if(!_combat->attacker_list[thing])
            return 0
            return thing


    def query_attacker(self, ) -> MudObject:
            return _combat->last_opponent


    def query_last_opponent(self, ) -> MudObject:
            return _combat->last_opponent


    def query_last_weapon(self, ) -> MudObject:
            return _combat->last_weapon


    def set_last_result(self, last: int) -> None:
            varargs int is_fighting(object ob, int actively) {
            if(!objectp(ob))
            return 0
            if(actively)
            return userp(ob) ? _combat->attacker_list[ob.query_name()] :
            _combat->attacker_list[ob]
            return userp(ob) ? _combat->attacker_list[ob.query_name()] ||
            _combat->hunting_list[ob.query_name()] :
            _combat->attacker_list[ob] || _combat->hunting_list[ob]


    def query_fighting(self, ) -> int:
            if(!environment() || base_name(environment()) == "/room/rubbish")
            return 0
            if(sizeof(filter(query_attacker_list(),
            (: environment($1) == environment(self) :))))
            return 1
            if(sizeof(filter(all_inventory(environment(self)),
            (: $1 && living($1) && $1.is_fighting(self, 1) :))))
            return 1
            return 0


    def stats(self, ) -> Any:
            int i
            int j
            object *weapons
            mixed ret
            init_tactics()
            ret = ({
            ["attitude", _tactics->attitude],
            ["response", _tactics->response],
            ["mercy", _tactics->mercy],
            ["parry", _tactics->parry],
            ["attack", _tactics->attack],
            ["unarmed parry", ["no", "yes"][ _tactics->parry_unarmed ]],
            ["attack zone", _tactics->focus_zone ? _tactics->focus_zone :
            "none"],
            ["distance", _tactics->ideal_distance ? _tactics->ideal_distance :
            "none"],
            })
            weapons = (object *)self.query_weapons()
            if(!sizeof(weapons))
            return ret + weapon_logic::stats()
            for ( i = 0; i < sizeof( weapons ); i++ )
            ret += [["weapon #"+ i, weapons[ i ]->short()]] +
            (mixed)weapons[ j ]->weapon_stats()
            return ret + weapon_logic::stats()



class Combat(MudObject):

    _combat = 'new(class combat_information,'

    _surrender = 'new(class surrender_information,'
