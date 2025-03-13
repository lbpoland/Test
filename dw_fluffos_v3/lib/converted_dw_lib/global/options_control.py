# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/options_control.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_property(self, string) -> Any:
            varargs void add_property(string,mixed,int)
            private class player_options_control query_player_options() {
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            return new(class player_options_control)


    def query_auto_follow_group(self, ) -> int:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            return 0


    def query_auto_follow_friends(self, ) -> int:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            return 0


    def query_auto_follow_everyone(self, ) -> int:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            return 0


    def query_lead_from_behind(self, ) -> int:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            return 0


    def set_auto_follow_group(self, flag: int) -> None:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            options = new(class player_options_control)


    def set_auto_follow_friends(self, flag: int) -> None:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            options = new(class player_options_control)


    def set_auto_follow_everyone(self, flag: int) -> None:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            options = new(class player_options_control)


    def set_lead_from_behind(self, flag: int) -> None:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            options = new(class player_options_control)


    def set_mxp_disable(self, flag: int) -> None:
            class player_options_control options
            options = query_player_options()
            options->mxp_disable = 1
            add_property(PLAYER_OPTIONS_CONTROL_PROP, options)


    def query_mxp_disable(self, ) -> int:
            class player_options_control options
            options = query_player_options()
            return options->mxp_disable


    def is_mxp_enabled(self, ) -> int:
            #if efun_defined(has_mxp)
            if (has_mxp(self)) {
            return !query_mxp_disable()



class Options_control(MudObject):
