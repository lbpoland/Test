# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/authorise.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, player: str) -> Any:
            if(find_player(player)) {
            find_player(player)->add_property("authorised player", 1)
            return 1


    def really_create(self, response: str, player: str) -> None:
            response = lower_case(response)
            if (response[0] != 'y') {
            write("Aborting create.\n")
            return


    def get_email(self, str: str, player: str) -> None:
            email = str
            write("What password do you wish to use: ")
            input_to("get_password", 0, player)


    def get_password(self, passw: str, player: str) -> None:
            string save_file_name
            save_file_name = PLAYER_HANDLER.query_player_file_name(player)
            map_prop = ([ "authorised player" : 1,
            "new player" : 1,
            "player" : 1,
            "authorised email" : email, ])
            player_info = ([ "email" : ":"+email, ])
            last_log_on = time()
            name = player
            password = crypt(passw, 0)
            save_object(save_file_name)
            write("Create player " + capitalize(player) + " with authorisation to login "
            "from nologin sites.\n")


    def enable(self, player: str, address: str) -> int:
            string *ips, file, *bits
            int i
            if(!PLAYER_HANDLER.test_user(player))
            return notify_fail("No such user " + player + ".\n")
            basename = "/save/players/" + player[0..0] + "/" + player
            unguarded ( (: uncompress_file (basename + ".o.gz") :))
            file = unguarded( (: read_file(basename + ".o") :))
            bits = explode(file, "\n")
            for (i = 0; i < sizeof(bits); i++) {
            if (bits[i][0..strlen("player_info")-1] == "player_info") {
            player_info = restore_variable(bits[i][strlen("player_info") + 1..])
            break


    def disable(self, player: str, address: str) -> int:
            string *ips, file, *bits
            int i
            if(!PLAYER_HANDLER.test_user(player))
            return notify_fail("No such user " + player + ".\n")
            basename = "/save/players/" + player[0..0] + "/" + player
            unguarded ( (: uncompress_file (basename + ".o.gz") :))
            file = unguarded( (: read_file(basename + ".o") :))
            bits = explode(file, "\n")
            for (i = 0; i < sizeof(bits); i++) {
            if (bits[i][0..strlen("player_info")-1] == "player_info") {
            player_info = restore_variable(bits[i][strlen("player_info") + 1..])
            break



class Authorise(MudObject):
