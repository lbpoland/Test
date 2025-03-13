# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/obj/check.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def dest_me(self, ) -> None:
            {
            destruct(self)


    def __init__(self):
            self.illegal = ([ ])
            self.paths = []
            self.cloned_by = []


    def log_file(self, ) -> None:
            {
            int p
            string *person, *filename
            filename=m_indices(illegal)
            person=values(illegal)
            if(sizeof(illegal)>0) {
            unguarded((: write_file, SAVE_FILE+"illegal.txt",
            "\nSearch carried out on "+ctime(time())+" from here.\n" :))
            for(p=0;p<sizeof(illegal);p++) {
            unguarded((: write_file, SAVE_FILE+"illegal.txt",
            filename[p]+"  -  on player "+person[p]+" - cloned by "+
            cloned_by[p]+"\n" :))


    def check_sub_inv(self, things: MudObject, owner: MudObject) -> None:
            {
            int q, r, check
            string *pre_filename, filename, *switcher
            mixed info
            for(q=0;q<sizeof(things);q++)
            {
            pre_filename=explode(file_name(things[q]),"#")
            filename=pre_filename[0]
            switcher=explode(filename,"/")
            if( (switcher[0]=="w") && (!owner.query_creator() ) )
            {
            illegal=illegal+([filename:owner.query_name()])
            info = things[q]->stats()
            for(r=0; r<sizeof(info);r++)
            {
            if(info[r][0] == "cloned by")
            {
            cloned_by = cloned_by + [info[r][1]]


    def check_inv(self, player: MudObject) -> None:
            {
            int q
            object *things, *contents, owner
            things=deep_inventory(player)
            owner=player
            check_sub_inv(things, player)



class Check(MudObject):

    illegal = '([ ])'

    paths = '[]'

    cloned_by = '[]'
