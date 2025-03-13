# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/crowd/crowd.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def include_gender(self, long: str, gender: int) -> str:
            switch ( gender ) {
            case 2:
            return
            replace( long, ["$POSS$","her","$OBJ$","her","$PRO$","She"] )
            default:
            return
            replace( long, ["$POSS$","his","$OBJ$","him","$PRO$","He"] )


    def long(self, word: str, dark: int) -> str:
            int i
            string ret=""
            if ( !lookflag ) {
            foreach (i in crowd) ret += include_gender( (members[i>>2])->long, i&3 )
            return ret


    def a_short(self, ) -> str:
            string ret=""
            int i,n_match
            string prev=file_name(previous_object(1))
            if ( prev == "/cmds/living/glance" ||
            prev == "/cmds/living/l_ook" ) {
            lookflag = 0
            i_member = 0
            selection = crowd
            n_selection = n_crowd


    def the_short(self, ) -> str:
            string ret=""
            int i
            for (i=0;i<n_crowd;i++)
            ret+="$the_short:"+ file_name( self ) +"$"
            return ret


    def one_short(self, ) -> str:
            string ret=""
            int i
            for (i=0;i<n_crowd;i++)
            ret+="$one_short:"+ file_name( self ) +"$"
            return ret


    def poss_short(self, ) -> str:
            return a_short()


    def __init__(self):
            self.string adjs = []
            self.string names = []
            self.crowd = []
            self.for (j = 0; j<sizeof(members);j++) {
            self.p = members[j]
            self.tmp = explode(p->short," ")
            self.p->names = ['tmp[<1]']
            self.p->plurals = ['pluralize(tmp[<1])']
            self.names + = ['tmp[<1]']
            self.p->adjectives = tmp[0..<2]
            self.adjs + = tmp[0..<2]
            self.for (k = 0;k<sizeof(p->original_number);k++)
            self.for (i = 0; i<(p->original_number)[k]; i++) crowd += ({ (j<<2)+k })


    def crowd_member_died(self, ) -> None:
            n_alive--
            n_cloned--
            if (!n_alive) dest_me()


    def merge_crowd_member(self, member: MudObject) -> None:
            await driver.tell_room(environment(), "%^YELLOW%^"+sprintf("%O reabsorbed into %O", exclude=member, self)+"%^RESET%^\n")
            if (member && environment(member)==environment() ) {
            int i
            for (i=0;i<sizeof(members);i++) {
            if ( base_name(member) == members[i]->file ) {
            n_cloned--
            n_crowd++
            n_here--
            here -= [member.crowd_number()]
            n_max = MAXATONCE - ((n_here + n_cloned) >> 2)
            if ( n_max < 1 ) n_max = 1
            crowd = [(i<<2)+member.query_gender()] + crowd
            member.dest_me()


    def make_member(self, ) -> MudObject:
            object frog
            int i,j
            if (i_member<0 || i_member>=sizeof(selection)) i_member=0
            i = selection[i_member]
            j = crowd .index( i) if  i in crowd  else -1
            frog = clone_object(members[i>>2]->file)
            if (frog) {
            n_crowd--
            n_cloned++
            n_here++
            n_max = (n_max+1)>>1
            n_selection--
            crowd = crowd[0..j-1] + crowd[j+1..<1]
            selection = selection[0..i_member-1]+selection[i_member+1..<1]
            crowd = crowd[0..j-1] + crowd[j+1..<1]
            here += [i]
            await driver.tell_room(environment(), "%^YELLOW%^"+sprintf("Cloned %O : %i of %i selected (%i remaining)", exclude=frog,i_member+1,sizeof(selection)+1,n_crowd)+"%^RESET%^\n")
            frog.fix_gender( i&3 )
            frog.add_effect( CROWD+"crowd_merge_effect", [self, i] )
            frog.move( environment(self) )


    def query_parse_id(self, arr: Any) -> Any:
            string *bits, bat
            int i
            selection = [})
            i_member = 0
            if (!n_crowd) return 0
            lastmatch=arr[P_THING]
            switch (query_verb()) {
            case 0:
            case "look":
            case "glance":
            case "destruct":
            case "lose":
            case "trans":
            lookflag=1
            break
            default:
            lookflag=0


    def event_enter(self, ob: MudObject, message: str, from: MudObject) -> None:
            if (from) {
            object *things
            n_here = sizeof( things = filter(all_inventory( environment() ),
            (: $1.crowd_object() == self :) ))
            here = [})
            if ( n_here ) here = map( things, (: $1.crowd_number() :) )
            n_max = MAXATONCE - ((n_here + n_cloned) >> 2)
            if ( n_max < 1 ) n_max = 1
            tell_creator("shaggy","ENTER %O: n_here: %i n_cloned: %i n_alive: %i n_crowd:%i n_max: %i %O\n",from,n_here,n_cloned,n_alive,n_crowd,n_max, here)


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            object *things
            n_here = sizeof( things = filter(all_inventory( environment() ),
            (: $1.crowd_object() == self :) ))
            here = [})
            if ( n_here ) here = map( things, (: $1.crowd_number() :) )
            n_max = MAXATONCE - ((n_here + n_cloned) >> 2)
            if ( n_max < 1 ) n_max = 1
            tell_creator("shaggy","EXIT: n_here: %i n_cloned: %i n_alive: %i n_crowd:%i n_max: %i %O\n",n_here,n_cloned,n_alive,n_crowd,n_max, here)



class Crowd(MudObject):

    string adjs = '[]'

    string names = '[]'

    crowd = '[]'

    for (j = '0; j<sizeof(members);j++) {'

    p = 'members[j]'

    tmp = 'explode(p->short," ")'

    p->names = "['tmp[<1]']"

    p->plurals = "['pluralize(tmp[<1])']"

    names + = "['tmp[<1]']"

    p->adjectives = 'tmp[0..<2]'

    adjs + = 'tmp[0..<2]'

    for (k = '0;k<sizeof(p->original_number);k++)'

    for (i = '0; i<(p->original_number)[k]; i++) crowd += ({ (j<<2)+k })'
