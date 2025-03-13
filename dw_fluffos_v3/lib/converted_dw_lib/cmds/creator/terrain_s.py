# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/terrain_s.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_map(self, ) -> int:
            string map
            object hand
            int* coords
            int x
            int y
            hand = environment(this_player())->query_map_handler()
            if (!hand) {
            add_failed_mess("You must be in a terrain to use this command.\n")
            return 0


    def do_map_terrain(self, ) -> int:
            string map
            object hand
            string* map_data
            int i
            hand = environment(this_player())->query_map_handler()
            if (!hand) {
            add_failed_mess("You must be in a terrain to use this command.\n")
            return 0


    def do_features_distant(self, ) -> int:
            object hand
            string title
            mixed tmp
            string fluff
            string ret
            int* coords
            int x
            int y
            int z
            string* features
            hand = environment(this_player())->query_map_handler()
            if (!hand) {
            add_failed_mess("You must be in a terrain to use this command.\n")
            return 0


    def do_features_local(self, ) -> int:
            mapping features
            string ret
            object hand
            mapping hand_features
            string name
            mixed stuff
            hand = environment(this_player())->query_map_handler()
            if (!hand) {
            add_failed_mess("You must be in a terrain to use this command.\n")
            return 0


    def do_feature_local_map(self, feature: str) -> int:
            object hand
            mapping hand_features
            string ret
            hand = environment(this_player())->query_map_handler()
            if (!hand) {
            add_failed_mess("You must be in a terrain to use this command.\n")
            return 0


    def do_feature_distant_map(self, feature: str) -> int:
            object hand
            string* dist_features
            string ret
            int* coords
            int x
            int y
            int z
            hand = environment(this_player())->query_map_handler()
            if (!hand) {
            add_failed_mess("You must be in a terrain to use this command.\n")
            return 0


    def do_terrain_status(self, ) -> int:
            string ret
            object hand
            mixed* coords
            mapping features
            string name
            int x
            int y
            int z
            string* dist_features
            mapping terrs
            hand = environment(this_player())->query_map_handler()
            if (!hand) {
            add_failed_mess("You must be in a terrain to use this command.\n")
            return 0



class Terrain_s(MudObject):
