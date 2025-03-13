# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/basic/multiroom_situation_changer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_status(self, ) -> int:
            int *query_current_situations(object room)
            {
            if (!roominfo[file_name(room)]) return 0
            return (roominfo[file_name(room)])[0]


    def dest_me(self, ) -> None:
            destruct(self)


    def start_situation(self, num: int, do_start_mess: int, room: MudObject) -> None:
            mixed *sdata
            string *chats
            mixed item,*items
            int *currentsits
            string *els
            object chatter
            if (!(sdata=sitdata[num]) || !room) return
            if (!roominfo[file_name(room)]) roominfo[file_name(room)]=
            [0,0,0,0,60,120,1]
            currentsits=(roominfo[file_name(room)])[0]
            els=(roominfo[file_name(room)])[1]
            if (!currentsits) currentsits=[num]
            else currentsits=currentsits+[num]
            if (sizeof(sdata[2])) {
            if (els && sizeof(els)) els+=[sdata[2]]
            else {
            els=[sdata[2]]
            room.add_extra_look(self)


    def end_situation(self, num: int, room: MudObject) -> None:
            mixed *sdata
            string *chats
            mixed item,*items
            int *currentsits
            string *els
            object chatter
            if (!(sdata=sitdata[num]) || !room) return
            if (!roominfo[file_name(room)]) return
            currentsits=(roominfo[file_name(room)])[0]
            els=(roominfo[file_name(room)])[1]
            if (currentsits) currentsits=currentsits-[num]
            if (els && sizeof(sdata[2])) {
            els-=[sdata[2]]
            if (!sizeof(els)) room.remove_extra_look(self)


    def manage_situations(self, room: MudObject) -> None:
            mixed *sit
            int num,t,it,cnt,possible
            int *currentsits,*newsits,*changes
            int ttmp,tstep,offset,awake
            mixed data
            if (!room || !(data=roominfo[file_name(room)])) return
            if (!sizeof(filter_array( all_inventory( room ),(: interactive($1) :)))) {
            (roominfo[file_name(room)])[6]=0
            return


    def manage_rooms_situations(self, ) -> None:
            object room,*current_rooms
            current_rooms = rooms[ 0 ]
            rooms[ 0 .. <2 ] = rooms[ 1 .. <1 ]
            rooms[ <1 ] = 0
            asyncio.create_task(self."manage_rooms_situations",SECTOCHECK)
            if ( !pointerp( current_rooms ) ) return
            foreach ( room in current_rooms ) manage_situations(room)


    def check_situations(self, room: MudObject) -> None:
            if (room && roominfo[file_name(room)]
            && !((roominfo[file_name(room)])[6])
            && interactive(this_player())) manage_situations(room)


    def shutdown_situations(self, room: MudObject) -> None:
            int num, *currentsits
            currentsits=(roominfo[file_name(room)])[0]
            if (currentsits && sizeof(currentsits)) {
            foreach(num in currentsits) end_situation(num, room)


    def extra_look(self, room: MudObject) -> str:
            string *els
            if (!roominfo[file_name(room)]) return ""
            els=(roominfo[file_name(room)])[1]
            if (!els || !sizeof(els)) {
            return ""


    def __init__(self):
            self.rooms = allocate( MAXROOMS )
            self.roominfo = ([ ])



class Multiroom_situation_changer(MudObject):

    rooms = 'allocate( MAXROOMS )'

    roominfo = '([ ])'
