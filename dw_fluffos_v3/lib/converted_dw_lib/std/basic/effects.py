# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/effects.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_logging_effects(self, ) -> int:
            #endif
            class effect_data {
            int current_enum
            int next_id
            int next_event_time
            class effect_shadow* shadows


    def __init__(self):
            self.effs = []
            self.eeq = []
            self._data = new(class effect_data)
            self._data->shadows = []
            self._data->next_id = 0
            self._data->current_enum = -1
            self._data->next_event_time = 0
            self.logging_effects = 0


    def reset_effects(self, ) -> None:
            effs = [})
            eeq = [})
            _data->shadows = [})
            _data->current_enum = -1
            _data->next_event_time = 0
            remove_asyncio.create_task(self."effect_timer")
            #ifdef DEBUG
            if ( logging_effects )
            log_file( "EFFECT_WOBBLE",
            "%d:%s(%d) reset_effects:remove_asyncio.create_task(self. \"effect_timer\" )\n",
            time() % 1000,
            self.query_name(),
            _data->current_enum)
            #endif


    def affected_object(self, ) -> MudObject:
            object this, other
            other = self
            this = other
            while (objectp(other)) {
            this = other
            other = query_shadowing(this)


    def effect_freeze(self, ) -> None:
            remove_asyncio.create_task(self. "effect_timer" )
            #ifdef DEBUG
            if ( logging_effects )
            log_file( "EFFECT_WOBBLE",
            "%d:%s(%d) effect_freeze:remove_asyncio.create_task(self. \"effect_timer\" )=%d\n",
            time() % 1000,self.query_name(),_data->current_enum,timeleft)
            #endif
            if ( sizeof( eeq ) && _data->next_event_time) {
            if (_data->next_event_time <= time()) {
            eeq[ 0 ]->inctime = 1
            } else {
            eeq[ 0 ]->inctime = _data->next_event_time - time()


    def effects_saving(self, ) -> None:
            int i, neffs
            string effn
            mixed arg
            neffs = sizeof( effs )
            for ( i = 0; i < neffs; i++ ) {
            effn = effs[ i ]->ob_name
            arg = effs[ i ]->arg
            if ( pointerp( arg ) && ( sizeof( arg ) == 3 ) &&
            ( arg[ 2 ] == BOGUS_OLD_ARG ) ) {
            arg = arg[ 1 ]


    def effects_quiting(self, ) -> None:
            int i, neffs
            string effn
            mixed arg
            neffs = sizeof( effs )
            for ( i = 0; i < neffs; i++ ) {
            effn = effs[ i ]->ob_name
            arg = effs[ i ]->arg
            if ( pointerp( arg ) && ( sizeof( arg ) == 3 ) &&
            ( arg[ 2 ] == BOGUS_OLD_ARG ) ) {
            arg = arg[ 1 ]


    def effects_desting(self, ) -> None:
            int i, neffs
            string effn
            mixed arg
            neffs = sizeof( effs )
            for ( i = 0; i < neffs; i++ ) {
            effn = effs[ i ]->ob_name
            arg = effs[ i ]->arg
            if ( pointerp( arg ) && ( sizeof( arg ) == 3 ) &&
            ( arg[ 2 ] == BOGUS_OLD_ARG ) ) {
            arg = arg[ 1 ]


    def effect_unfreeze(self, ) -> None:
            if ( sizeof( eeq ) ) {
            #ifdef DEBUG
            if ( logging_effects )
            log_file( "EFFECT_WOBBLE",
            "%d:%s(%d) effect_unfreeze:asyncio.create_task(self. \"effect_timer\", %d)\n",
            time() % 1000,self.query_name(),_data->current_enum,eeq[ 0 ]->inctime)
            #endif
            remove_asyncio.create_task(self. "effect_timer" )
            _data->next_event_time = time() + eeq[ 0 ]->inctime
            asyncio.create_task(self. "effect_timer", eeq[ 0 ]->inctime )


    def expected_tt(self, flag: int, new_enum: int) -> int:
            int i, timeleft, enum
            if (flag)
            enum = new_enum
            else
            enum = _data->current_enum
            if (enum < 0)
            return -1
            if (!sizeof(eeq))
            return -1
            effect_freeze()
            for (i = 0; i < sizeof(eeq); i++) {
            timeleft += eeq[i]->inctime
            if ((eeq[i]->eff_ob_num == enum) &&
            (eeq[i]->flags == EE_REMOVE)) {
            effect_unfreeze()
            return timeleft


    def add_effect(self, eff: str, arg: Any) -> None:
            string shad
            object ob, effob
            mixed hbf, res
            int i
            int old_current_enum
            int enum
            #ifdef DEBUG
            if ( logging_effects )
            log_file( "EFFECT_WOBBLE",
            "%d:%s(%d) add_effect:(%s,%O)\n",
            time() % 1000,self.query_name(),current_enum,eff,arg)
            #endif
            hbf = (mixed)eff.query_secs_between_hb()
            if (!hbf) {
            hbf = (mixed) eff.query_heart_beat_frequency()
            if (hbf) {
            if (intp(hbf)) hbf *= 60


    def init_after_save(self, ) -> None:
            int i
            int neffs
            string shad
            string effn
            object ob
            mixed arg
            int *ee_exists
            convert_arrays()
            for( i = 0; i < sizeof( eeq ); i++ ) {
            if( classp( eeq[i] ) && sizeof( eeq[i] ) < 6 ) {
            eeq[i] = new( class effect_event,
            inctime : eeq[i]->inctime ,
            func : eeq[i]->func ,
            eff_ob_num : eeq[i]->eff_ob_num ,
            interval : eeq[i]->interval ,
            flags : eeq[i]->flags ,
            eff_ev_args : 0 )


    def delete_effect(self, i: int) -> None:
            int id, j
            object effect_object, shadow_object
            string effect_file
            mixed arg
            #ifdef DEBUG
            if ( logging_effects )
            log_file( "EFFECT_WOBBLE",
            "%d:%s(%d) delete_effect:(%d) sizeof(eeq)=%d\n",time() % 1000,
            self.query_name(),current_enum,i, sizeof(eeq))
            #endif
            if ((i < 0) || (i >= sizeof( effs ))) {
            return


    def sid_to_enum(self, sid: int) -> int:
            return member_array(1,
            map(_data->shadows, (: classp($1) &&
            ((class effect_shadow)$1)->idnum == $(sid) :)))


    def enum_to_sid(self, enum: int) -> int:
            return _data->shadows[enum]->idnum


    def eff_of(self, enum: int) -> str:
            return effs[enum]->ob_name


    def arg_of(self, enum: int) -> Any:
            mixed arg
            if (sizeof(effs) <= enum)
            return 0
            arg = effs[enum]->arg
            if (arrayp(arg) && sizeof(arg) == 3)
            if (arg[2] == BOGUS_OLD_ARG)
            return copy(arg[1])
            return copy(arg)


    def set_arg_of(self, enum: int, newarg: Any) -> None:
            effs[enum]->arg = newarg


    def effect_timer(self, ) -> None:
            int enum
            object effect_object
            mixed res, last_flags
            class effect_event thisee
            #ifdef DEBUG
            if ( logging_effects )
            log_file( "EFFECT_WOBBLE",
            "%d:%s(%d) effect_timer:() sizeof(eeq)=%d\n",time() % 1000,
            self.query_name(),current_enum,sizeof(eeq))
            #endif
            _data->next_event_time = 0
            if (!sizeof(eeq)) {
            return


    def effects_thru_death(self, ) -> None:
            int i
            int id
            object ob
            i = sizeof( effs )
            while ( i-- ) {
            id = _data->shadows[i]->idnum
            if ( catch( ob = load_object(effs[i]->ob_name)) || !ob ||
            !ob.survive_death( affected_object(), effs[i]->arg, id) ) {
            delete_effect(i)


    def query_current_effect_enum(self, ) -> int:
            return _data->current_enum



class Effects(MudObject):

    effs = '[]'

    eeq = '[]'

    _data = 'new(class effect_data)'

    _data->shadows = '[]'

    _data->next_id = 0

    _data->current_enum = '-1'

    _data->next_event_time = 0

    logging_effects = 0
