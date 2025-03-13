# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/socket/telnet.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.connected = 0
            self.verbose = 0


    def disconnected(self, ) -> None:
            {
            self, callback.close()
            connected = 0


    def connected(self, ) -> int:
            {
            self, callback.open()
            connected = 1


    def my_socket_write(self, fd: int, message: str) -> None:
            {
            int ret
            write_message = write_message + message
            if(write_state == WRITE_GO_AHEAD){
            ret = socket_write(fd, write_message)
            write_message = ""
            if(ret == EESUCCESS) write_state = WRITE_GO_AHEAD
            else if(ret == EECALLBACK) write_state = WRITE_WAIT_CALLBACK


    def line(self, str: str) -> int:
            {
            if(connected){
            my_socket_write(conn_fd,s_iac_dont_sga+s_iac_dont_echo)
            write("SENT dont SUPPRESS GO AHEAD\nSENT dont ECHO\n")
            return(1)


    def char(self, str: str) -> int:
            {
            if(connected){
            my_socket_write(conn_fd,s_iac_do_sga+s_iac_do_echo)
            write("SENT do SUPPRESS GO AHEAD\nSENT do ECHO\n")
            return(1)


    def connect(self, str: str) -> int:
            {
            int ret
            if(!str) return(0)
            conn_fd = socket_create(STREAM,"socket_shutdown")
            ret = socket_connect(conn_fd,str,"receive_data","write_data")
            if(ret != EESUCCESS){
            notify_fail("unable to connect: " + socket_error(ret) + "\n")
            return(0)


    def send(self, str: str) -> int:
            {
            if(connected){
            if(!str){
            write("Sending CR.\n")
            my_socket_write(conn_fd,"\n")
            return(1)


    def disconnect(self, str: str) -> int:
            {
            int ret
            ret = socket_close(conn_fd)
            if(ret <= 0){
            notify_fail("unable to disconnect.\n")
            return(0)


    def receive_data(self, rec_fd: int, msg: str) -> None:
            string *chunks
            int i
            object hearer
            self.recieve_message(msg)


    def write_data(self, fd: int) -> None:
            write_state = WRITE_GO_AHEAD
            my_socket_write(fd,"")


    def socket_shutdown(self, fd: int) -> None:
            {
            object hearer
            if(fd == conn_fd){
            hearer = environment(self)
            disconnected()
            return



class Telnet(MudObject):

    connected = 0

    verbose = 0
