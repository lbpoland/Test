# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/qwho.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, filter: str, arg: str) -> int:
            string* determine_location( object person ) {
            mixed *areas, *place
            areas = ({
            ["/d/liaison/NEWBIE", ["Misc", "The newbie area"]],
            ["/room/air", ["Misc", "The air"]],
            ["/room/void", ["Misc", "The void"]],
            ["/room/rubbish", ["Misc", "The rubbish room"]],
            ["/room/departures", ["Misc", "The departures lounge"]],
            ["/room/jail", ["Misc", "Jail"]],
            ["/w/", ["Misc", "/w dirs"]],
            ["/d/cwc/utils/interview", ["CWC", "Interview room"]],
            ["/d/cwc/common", ["CWC", "Commonroom"]],
            ["/d/cwc/Brown_Islands", ["CWC", "Brown Islands"]],
            ["/d/cwc/Bes_Pelargic/Bad_Poo-Ning/roads/medina",
            ["CWC", "Medina"]],
            ["/d/cwc/Bes_Pelargic/Sum_Bing/roads/snail",
            ["CWC", "The Snail"]],
            ["/d/cwc/Bes_Pelargic", ["CWC", "Bes Pelargic"]],
            ["/d/cwc/Hunghung", ["CWC", "HungHung"]],
            ["/d/cwc/Isle_of_Tonahamen", ["CWC", "Isle of Tonahamen"]],
            ["/d/cwc/families/mcsweeny", ["CWC", "McSweeney Estate"]],
            ["/d/cwc/Maps", ["CWC", "Terrains"]],
            ["/d/cwc", ["CWC", "?"]],
            ["/d/classs/assassins/Bes-Pelargic", ["CWC", "BP classs"]],
            ["/d/classs/thieves/Bes-Pelargic", ["CWC", "BP classs"]],
            ["/d/classs/warriors/BesPelargic", ["CWC", "BP classs"]],
            ["/d/classs/warriors/Hunghung", ["CWC", "HH classs"]],
            ["/d/classs/priests/Bes_Pelargic", ["CWC", "BP classs"]],
            ["/d/classs/wizards/Bes_Pelargic", ["CWC", "BP classs"]],
            ["/d/classs/witches/bespelargic", ["CWC", "BP classs"]],
            ["/d/underworld/moving_shop/rooms/cwc", ["CWC", "F-shop"]],
            ["/d/am/utils/interview", ["AM", "Interview room"]],
            ["/d/am/shades", ["AM", "The Shades"]],
            ["/d/am/common", ["AM", "Commonroom"]],
            ["/d/am", ["AM", "Waterdeep"]],
            ["/d/special/player_shops", ["AM", "Tarnach's"]],
            ["/d/classs/merchants", ["AM", "Waterdeep"]],
            ["/d/classs/assassins/Waterdeep", ["AM", "AM classs"]],
            ["/d/classs/thieves/Waterdeep", ["AM", "AM classs"]],
            ["/d/classs/warriors/Waterdeep", ["AM", "AM classs"]],
            ["/d/classs/priests/Waterdeep", ["AM", "AM classs"]],
            ["/d/classs/wizards/Waterdeep",
            ["AM", "Unseen University"]],
            ["/d/classs/witches/Waterdeep", ["AM", "AM classs"]],
            ["/d/classs/witches/am", ["AM", "AM classs"]],
            ["/d/klatch/utils/interview", ["Klatch", "Interview room"]],
            ["/d/klatch/common", ["Klatch", "Commonroom"]],
            ["/d/klatch/djel/city", ["Klatch", "KLK"]],
            ["/d/klatch/djel/necropolis", ["Klatch", "Necropolis"]],
            ["/d/klatch/djel/netherworld", ["Klatch", "Netherworld"]],
            ["/d/klatch/tsort/desert/roads",
            ["Klatch", "Tsort desert road"]],
            ["/d/klatch/tsort/desert", ["Klatch", "Tsort desert"]],
            ["/d/klatch/tsort", ["Klatch", "Tsort"]],
            ["/d/klatch/Maps", ["Klatch", "Terrains"]],
            ["/d/klatch", ["Klatch", "?"]],
            ["/d/classs/assassins/Khot-lip-khin",
            ["Klatch", "KLK classs"]],
            ["/d/classs/thieves/Khot-lip-khin", ["Klatch", "KLK classs"]],
            ["/d/classs/warriors/Khot-lip-khin",
            ["Klatch", "KLK classs"]],
            ["/d/classs/priests/Djelibeybi", ["Klatch", "KLK classs"]],
            ["/d/classs/priests/Khot-lip-khin", ["Klatch", "KLK classs"]],
            ["/d/classs/wizards/Khot-lip-khin", ["Klatch", "KLK classs"]],
            ["/d/classs/wizards/Ephebe", ["Klatch", "Ephebe classs"]],
            ["/d/classs/wizards/Tsort", ["Klatch", "Tsort classs"]],
            ["/d/classs/witches/klk", ["Klatch", "KLK classs"]],
            ["/d/ram/utils/interview", ["Ram", "Interview room"]],
            ["/d/ram/common", ["Ram", "Commonroom"]],
            ["/d/ram/Gloomy_Forest", ["Ram", "Gloomy forest"]],
            ["/d/ram/Lancre_Kingdom", ["Ram", "Lancre Kingdom"]],
            ["/d/ram/Listening_Monks", ["Ram", "Listening Monks"]],
            ["/d/ram/Razorback", ["Ram", "Razorback"]],
            ["/d/ram/Slice", ["Ram", "Slice"]],
            ["/d/ram/Sprite_Caverns", ["Ram", "Sprite caverns"]],
            ["/d/ram/Temple_of_Soyin", ["Ram", "Temple of Soyin"]],
            ["/d/ram/Uberwald", ["Ram", "Uberwald"]],
            ["/d/ram/badass", ["Ram", "Bad Ass"]],
            ["/d/ram/madstoat", ["Ram", "Mad Stoat"]],
            ["/d/ram/ohulan", ["Ram", "Ohulan-Cutash"]],
            ["/d/ram/foothills", ["Ram", "Connecting paths"]],
            ["/d/ram/bridge", ["Ram", "Connecting paths"]],
            ["/d/ram/moorland", ["Ram", "Connecting paths"]],
            ["/d/ram/gorge_road", ["Ram", "Connecting paths"]],
            ["/d/ram/Lower_Valleys", ["Ram", "Connecting paths"]],
            ["/d/ram/lancre_town", ["Ram", "Lancre Town"]],
            ["/d/ram/bandit_camp", ["Ram", "Bandit camp"]],
            ["/d/ram/druid_circle", ["Ram", "Druid circle"]],
            ["/d/ram/mountains", ["Ram", "Ramtops"]],
            ["/d/ram", ["Ram", "?"]],
            ["/d/classs/assassins/Ohulan-Cutash", ["Ram", "OC classs"]],
            ["/d/classs/thieves/Madstoat", ["Ram", "Mad Stoat classs"]],
            ["/d/classs/warriors/Lancre", ["Ram", "Lancre classs"]],
            ["/d/classs/priests/Monks-of-Cool", ["Ram", "Monks of Cool"]],
            ["/d/classs/priests/Ohulan-Cutash", ["Ram", "OC classs"]],
            ["/d/classs/wizards/Creel-Springs",
            ["Ram", "Creel Springs classs"]],
            ["/d/classs/witches/badass", ["Ram", "Bad Ass classs"]],
            ["/d/classs/witches/lancre", ["Ram", "Lancre classs"]],
            ["/d/classs/witches/madstoat", ["Ram", "Mad Stoat classs"]],
            ["/d/classs/witches/razorback", ["Ram", "Razorback classs"]],
            ["/d/sur/utils/interview", ["Sur", "Interview room"]],
            ["/d/sur/common", ["Sur", "Commonroom"]],
            ["/d/sur/Maps", ["Sur", "Terrains"]],
            ["/d/sur/Dinky", ["Sur", "Dinky"]],
            ["/d/sur/Sto_Helit", ["Sur", "Sto Helit"]],
            ["/d/sur/StoLat", ["Sur", "Sto Lat"]],
            ["/d/sur/Hillshire", ["Sur", "Hillshire"]],
            ["/d/sur/Holywood", ["Sur", "Holywood"]],
            ["/d/sur/Nowhere", ["Sur", "Nowhere"]],
            ["/d/sur/PekanFord", ["Sur", "Pekan Ford"]],
            ["/d/sur/Sheepridge", ["Sur", "Sheepridge"]],
            ["/d/sur/Scrogden", ["Sur", "Scrogden"]],
            ["/d/sur/items/carriage", ["Sur", "Carriage"]],
            ["/d/sur", ["Sur", "?"]],
            ["/d/classs/assassins/Sto-Lat", ["Sur", "SL classs"]],
            ["/d/classs/assassins/Sto-Helit", ["Sur", "SH classs"]],
            ["/d/classs/assassins/Sheepridge",
            ["Sur", "Sheepridge classs"]],
            ["/d/classs/thieves/Sto-Lat", ["Sur", "SL classs"]],
            ["/d/classs/thieves/Sto-Helit", ["Sur", "SH classs"]],
            ["/d/classs/thieves/Pekan_Ford", ["Sur", "PF classs"]],
            ["/d/classs/warriors/Sto-Lat", ["Sur", "SL classs"]],
            ["/d/classs/priests/Sto-Lat", ["Sur", "SL classs"]],
            ["/d/classs/wizards/Sto-Lat", ["Sur", "SL classs"]],
            ["/d/classs/witches/skund", ["Sur", "Skund classs"]],
            ["/d/classs/witches/stolat", ["Sur", "SL classs"]],
            ["/d/forn/utils/interview", ["Forn", "Interview room"]],
            ["/d/forn/common", ["Forn", "Commonroom"]],
            ["/d/forn/genua", ["Forn", "Genua"]],
            ["/d/forn", ["Forn", "?"]],
            ["/d/classs/assassins/Genua", ["Forn", "Genua classs"]],
            ["/d/special/utils/interview", ["Special", "Interview room"]],
            ["/d/special/common", ["Special", "Commonroom"]],
            ["/d/special/ctf", ["Special", "CTF"]],
            ["/d/special", ["Special", "?"]],
            ["/d/playtesters/utils/interview", ["Playtesters",
            "Interview room"]],
            ["/d/playtesters/common", ["Playtesters", "Commonroom"]],
            ["/d/playtesters/palace_rooms", ["Playtesters", "Palace"]],
            ["/d/playtesters", ["Playtesters", "?"]],
            ["/d/liaison/utils/interview", ["Liaison", "Interview room"]],
            ["/d/liaison/common", ["Liaison", "Commonroom"]],
            ["/d/liaison", ["Liaison", "?"]],
            ["/d/underworld/common", ["Underworld", "Commonroom"]],
            ["/d/underworld/death", ["Underworld", "Death's domain"]],
            ["/d/underworld/lspace", ["Underworld", "L-space"]],
            ["/d/underworld/moving_shop", ["Underworld", "T-shop"]],
            ["/d/underworld", ["Underworld", "?"]],
            ["/d/classs/common", ["Guilds", "Commonroom"]],
            ["/d/classs/assassins", ["Guilds", "Assassins"]],
            ["/d/classs/thieves", ["Guilds", "Thieves"]],
            ["/d/classs/warriors", ["Guilds", "Warriors"]],
            ["/d/classs/priests/rooms", ["Guilds", "Passage rooms"]],
            ["/d/classs/priests", ["Guilds", "Priests"]],
            ["/d/classs/wizards", ["Guilds", "Wizards"]],
            ["/room/magic_circle", ["Guilds", "Witches' circle"]],
            ["/d/classs/witches", ["Guilds", "Witches"]],
            ["/d/classs", ["Guilds", "?"]],
            ["/d/admin/room/domain_control", ["Admin", "Domain control"]],
            ["/d/admin", ["Admin", "?"]],
            ["/d", ["Other", "Unknown /d room"]],
            })
            if( !environment(person) ) {
            return ["Other", "No environment"]


    def get_guild_id(self, person: MudObject) -> int:
            switch(person.query_class_ob()) {
            case "/std/classs/warrior":
            return 0
            case "/std/classs/assassin":
            return 1
            case "/std/classs/thief":
            return 2
            case "/std/classs/wizard":
            return 3
            case "/std/classs/priest":
            return 4
            case "/std/classs/witch":
            return 5
            default:
            return 6


    def cmd(self, filter: str, arg: str, verbose: int) -> int:
            string place, zone, *classs
            mapping players, zones
            int total, i, j
            string tmp
            string ret
            ret = ""
            players = get_dist(filter,arg)
            total = sizeof(filter( users(), (: !$1.query_creator() &&
            $1.query_name() != "logon" :) ))
            classs = ["Warriors", "Assassins", "Thieves", "Wizards", "Priests",
            "Witches", "Adventurers"]
            tmp = "\n"
            tmp+= sprintf( "%-27s", "Distribution of players:" )
            if( filter == "category" && arg == "class" ) {
            j = (this_player()->query_cols() - 27) / (sizeof(classs))
            for( i=0; i<sizeof(classs); i++ ) {
            tmp += sprintf( "%" + j + ".3s", classs[i] )



class Qwho(MudObject):
