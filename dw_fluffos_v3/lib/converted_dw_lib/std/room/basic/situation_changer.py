# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/basic/situation_changer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_room(self, room_o: MudObject) -> MudObject:
            ownerroom=room_o
            return self


    def choose_words(self, label: Any, choice: Any) -> None:
            {
            int i
            class situation sit
            string *wc
            sit = sitdata[ label ]
            if (sizeof(sit->random_words)) {
            if (!sitwords) sitwords= ([ ])
            if (intp(choice)) {
            wc=[})
            for (i=0;i<sizeof(sit->random_words);i++) {
            wc+=["#"+(i+1),
            ((sit->random_words)[i])[
            RANDOM(sizeof((sit->random_words)[i]),choice+i*3347483647)]]


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, parent: int) -> int:
            if (parent) {
            return 0


    def add_situation(self, label: Any, situation: Any) -> None:
            if (!sizeof(sitdata)) {
            sitdata= ([ label : sit ])
            sitwords= ([ ])


    def start_situation(self, label: Any, do_start_mess: int) -> None:
            class situation sdata
            string *chats
            mixed item,*items
            object chatter
            string *words
            sdata=sitdata[ label ]
            words=sitwords[ label ]
            if (!currentsits) currentsits=[label]
            else currentsits=currentsits+[label]
            if (sizeof(sdata->extra_look)) {
            if (els && sizeof(els))
            els+=[replace(sdata->extra_look,words)]
            else {
            els=[replace(sdata->extra_look,words)]
            ownerroom.add_extra_look(self)


    def end_situation(self, label: Any) -> None:
            class situation sdata
            string *chats
            mixed item,*items
            object chatter
            string *words
            sdata=sitdata[ label ]
            words=sitwords[ label ]
            if (currentsits) currentsits=currentsits-[label]
            if (els && sizeof(sdata->extra_look)) {
            els-=[replace(sdata->extra_look,words)]
            if (!sizeof(els)) ownerroom.remove_extra_look(self)


    def query_possible(self, situation_timing: Any, it: int, tod: int, cnt: int) -> int:
            {
            int possible
            class situation_timing sit2
            int cnt2,it2,tod2,possible2
            if (functionp(sit->when)) possible=(*(sit->when))(tod)
            else possible=sit->when
            possible=
            (possible&(1<<((AM_TIME_HANDLER)->query_am_hour(tod))))
            &&
            (RANDOM(1000,it*1147483647+cnt*2047483243) < sit->chance)
            if (possible && sit->category) {
            cnt2=0
            foreach (sit2 in sittiming) {
            cnt2++
            if (cnt2!=cnt && sit2->category == sit->category) {
            it2=(tod+offset+(cnt2*234231))/sit2->duration
            tod2=it2*sit2->duration-offset-(cnt2*234231)
            if (functionp(sit2->when)) possible2=(*(sit2->when))(tod2)
            else possible2=sit2->when
            possible2=
            (possible2&(1<<((AM_TIME_HANDLER)->query_am_hour(tod2))))
            &&
            (RANDOM(1000,it2*1147483647+cnt2*2047483243) < sit2->chance)
            if (possible2 && (tod2<tod || (tod==tod2 && cnt2<cnt))) {
            possible=0
            break


    def manage_situations(self, ) -> None:
            class situation_timing sit
            int t,t0,it,tod,cnt,possible,dt,tc,i
            mixed label,lb
            mixed *newsits
            mixed *changes
            mixed *background_on,*background_off
            int ttmp,tstep
            if (!automate) return
            if (!sizeof(filter_array( all_inventory( ownerroom ),(: interactive($1) :)))) {
            automate=2
            return


    def check_situations(self, ) -> None:
            if (automate==2 && interactive(this_player())) manage_situations()


    def make_seed(self, xval: int, yval: int) -> None:
            offset=(xval*38547+yval*1232444311)>>2


    def shutdown_all_situations(self, ) -> None:
            int label
            mixed h
            if (sizeof(cco)>1) {
            foreach (h in cco[1..<1]) {
            if (h) remove_asyncio.create_task(self.h)


    def shutdown_situation(self, handle: int, label: Any) -> None:
            mixed frog,bing
            if (sizeof(cco)) {
            if (!handle) handle=cco[0]
            if (handle && cco[handle]) remove_asyncio.create_task(self.cco[handle])
            cco[handle]=0


    def extra_look(self, ) -> str:
            if (!els || !sizeof(els)) {
            return ""



class Situation_changer(MudObject):
