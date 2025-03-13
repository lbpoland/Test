# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/newbiehelpers.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.admin = ([ ])
            self.helpers = ([ ])
            self.applicants = ([ ])
            self.minimum_apply_age = 0
            self.minimum_vouch_age = 0


    def query_list(self, lister: MudObject) -> str:
            string list_mess, person
            if( !sizeof( admin ) ) {
            list_mess = "There are no newbie helpers admin at present.\n"


    def query_check_player(self, checker: MudObject, player: str) -> str:
            if( !helpers[player] && !admin[player] && !applicants[player] ) {
            return "$C$" + player + " is not registered with the newbie "
            "helpers handler.\n"


    def add_helper(self, adder: MudObject, player: str) -> int:
            string *player_vouches, player_class, player_nationality, name
            name = adder.query_name()
            if( !admin[name] ) {
            await  TP.send("You are not a member of newbiehelpers admin.\n" )
            return 0


    def remove_helper(self, remover: MudObject, player: str, reason: str) -> str:
            string name
            name = remover.query_name()
            if( !admin[name] ) {
            await  TP.send("You are not a member of newbiehelpers admin.\n" )
            return 0


    def submit_vouch(self, statement: str, args: Any) -> None:
            string name, player
            object voucher
            voucher = args[0]
            player = args[1]
            name = voucher.query_name()
            applicants[player]["vouches"][name] = ([ ])
            applicants[player]["vouches"][name]["time"] = time()
            applicants[player]["vouches"][name]["age"] = -voucher.query_time_on()
            applicants[player]["vouches"][name]["statement"] = statement
            save_file()
            log_message( name + " submits a vouch for " + player )


    def no_vouch_reason(self, voucher: MudObject, applicant: str) -> str:
            string name
            name = voucher.query_name()
            if( !applicants[applicant] ) {
            return "$C$" + applicant + " isn't applying to be a newbie helper, "
            "so you can't vouch for them.\n"


    def submit_application(self, statement: str, player: MudObject) -> None:
            string name
            name = player.query_name()
            applicants[name] = ([ ])
            applicants[name]["time"] = time()
            applicants[name]["age"] = -player.query_time_on()
            applicants[name]["statement"] = statement
            applicants[name]["vouches"] = ([ ])
            applicants[name]["class"] =
            (load_object(player.query_class_ob()))->query_short()
            if( player.query_nationality() ) {
            applicants[name]["nationality"] = "$C$" +
            (load_object(player.query_nationality()))->query_name()


    def no_apply_reason(self, player: MudObject) -> str:
            string name
            name = player.query_name()
            if( helpers[name] ) {
            return "You are already a newbie helper, why are you applying "
            "again?\n"


    def no_reject_reason(self, rejecter: MudObject, player: str) -> str:
            string name
            name = rejecter.query_name()
            if( !admin[name] ) {
            return "You are not a member of newbiehelpers admin.\n"


    def query_helper(self, name: str) -> int:
            if( helpers[name] ) {
            return 1


    def add_admin(self, name: str) -> int:
            if( !admin[TP.query_name()] ) {
            return 0


    def remove_admin(self, name: str) -> int:
            if( !admin[TP.query_name()] ) {
            return 0


    def query_admin(self, name: str) -> int:
            if( admin[name] ) {
            return 1


    def query_can_chat(self, who: MudObject) -> int:
            if( query_helper( who.query_name() ) ||
            query_admin( who.query_name() ) ||
            who.query_creator() ) {
            return 1


    def query_name(self, ) -> str:
            protected void log_message( string message ) {
            log_file("/log/NEWBIEHELPERS", ctime(time()) + ": " + message + "\n")



class Newbiehelpers(MudObject):

    admin = '([ ])'

    helpers = '([ ])'

    applicants = '([ ])'

    minimum_apply_age = 0

    minimum_vouch_age = 0
