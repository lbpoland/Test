# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/mail_track.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("tracker")
            set_short("mail tracker")
            add_property("determinate", "the ")
            add_property("there", "mounted on one wall")
            add_adjective("mail")
            set_long("This thing tracks mail.   Clever, innit?\n")
            reset_get()
            reset_drop()
            our_mailers = [})
            mailing_lists = ([ ])
            seteuid("Root")
            load_me()
            if (!query_list("postmaster")) {
            create_list("postmaster", "pinkfish")


    def add_mailer(self, ob: MudObject, str: str) -> int:
            int i
            if (!stringp(str) || !objectp(ob)) {
            return 0


    def find_mailer(self, str: str) -> MudObject:
            int i
            if (!stringp(str)) {
            return 0


    def delete_mailer(self, ob: MudObject) -> int:
            int i
            if (!objectp(ob)) {
            return 0


    def we_are_done(self, me: MudObject) -> None:
            if (objectp(me)) {
            me.dest_me()


    def mail(self, str: str, sub: str) -> int:
            object mailer
            mailer = clone_object(MAILER)
            mailer.set_do_this_last([self, "we_are_done", mailer])
            mailer.read_mail(str, sub)
            return 2


    def query_list(self, list: str) -> int:
            return query_mailing_lists(.index(list) if list in query_mailing_lists( else -1) != -1


    def query_member(self, list_name: str, name: str) -> int:
            class mailing_list list
            list = mailing_lists[list_name]
            if (list) {
            return list->members.index(name) if name in list->members else -1 != -1


    def query_controller(self, list_name: str, name: str) -> int:
            class mailing_list list = mailing_lists[list_name]
            if (!list) {
            return 0


    def query_creator(self, list_name: str) -> str:
            class mailing_list list = mailing_lists[list_name]
            if (!classp(list)) {
            return 0


    def create_list(self, list: str, creator: str) -> int:
            SECURITY
            if (mailing_lists[list]) {
            return 0


    def add_controller(self, list_name: str, mem: str) -> int:
            class mailing_list list = mailing_lists[list_name]
            SECURITY
            if (!classp(list)) {
            return 0


    def remove_controller(self, list_name: str, name: str) -> int:
            int i
            class mailing_list list = mailing_lists[list_name]
            SECURITY
            if (!classp(list)) {
            return 0


    def add_member(self, list_name: str, mem: str) -> int:
            class mailing_list list = mailing_lists[list_name]
            if (file_name(previous_object()) != MAIL_ROOM) {
            return 0


    def remove_member(self, list_name: str, mem: str) -> int:
            int i
            class mailing_list list = mailing_lists[list_name]
            if (file_name(previous_object()) != MAIL_ROOM) {
            return 0


    def delete_member(self, list_name: str, mem: str) -> int:
            class mailing_list list = mailing_lists[list_name]
            SECURITY
            if (!remove_member(list_name, mem)) {
            return 0



class Mail_track(MudObject):
