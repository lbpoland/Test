# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/virtual/handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def find_virtual_object(self, name: str) -> MudObject:
            string trash
            if(sscanf(name, "%s#%s", name, trash) == 2)
            name = trash
            if(cloned_objects[name])
            return (object)cloned_objects[name]
            return (object)0


    def error(self, str: str) -> int:
            write(str+"\n")
            return 1


    def str_to_int(self, str: str) -> int:
            int i, j, k
            for(i=strlen(str)-1,j=1;i>-1;k+=(str[i--]-48)*j,j*=10)
            return k


    def use_efun_clone(self, file: str) -> MudObject:
            log_file("NON_VIRTUAL", file +"\n")
            return efun::clone_object(file)


    def clone_virtual_object(self, file: str) -> MudObject:
            int i, j, k, l, m, len
            string data, *line, file_to_inherit, start, comment, rest
            object obj
            mixed *args
            if(file_size(file) > 5000)
            return use_efun_clone(file)
            data = read_file(file)
            line = explode(file, "/")
            file_to_inherit = "/" + implode(line[0..sizeof(line)-2], "/") + "/"
            line = [(string)0]
            while(sscanf(data, "%s#include \"%s\"%s", start, comment, rest) == 3) {
            if(!(line[0] = read_file(file_to_inherit + comment)))
            line[0] = read_file("/include/" + comment)
            if(line[0])
            data = start + line[0] + rest
            else {
            error("Include file not found.")
            return (object)0



class Handler(MudObject):
