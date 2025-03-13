# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/reactions/base.hdr_dc.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def data_return_0(self, ) -> Any:
            if (!mapp(data["TeaLeaf"])) data["TeaLeaf"] = ([])
            item = new( class reaction )
            item->ratio = 1.0/100
            item->result = "/obj/reagents/weak_black_tea.ob"
            item->result_amt = 1.0
            item->func = [})
            data["TeaLeaf"]["Water"] = item
            if (!mapp(data["BatGuano"])) data["BatGuano"] = ([])
            item = new( class reaction )
            item->ratio = [0.8, 1.2]
            item->result = "/obj/reagents/generic_liquid.ob"
            item->result_amt = 1
            item->func = [(:
            $3.set_decay_speed(0),
            $3.set_medium_alias( "GuanoSolution" ),
            $3.set_name( "guano_solution" ),
            $3.add_alias( "sludge" ),
            $3.set_short( "thick brown sludge" ),
            $3.add_adjective( ["thick", "brown"] ),
            $3->set_long( "This is some thick brown sludge, streaked through with "
            "white.  The smell is... prominent.\n" )
            :)]
            data["BatGuano"]["Water"] = item
            if (!mapp(data["BlueHealingWater"])) data["BlueHealingWater"] = ([])
            item = new( class reaction )
            item->ratio = [1.0, 1.0]
            item->result = "/obj/reagents/generic_liquid.ob"
            item->result_amt = 1.0
            item->func = ({
            (: $3.set_name( "ooze" ) :),
            (: $3.add_alias( "green ooze" ) :),
            (: $3.set_short( "thick green ooze" ) :),
            (: $3.set_main_plural( "thick green oozes" ) :),
            (: $3.add_plural( "oozes" ) :),
            (: $3.add_adjective( "green" ) :),
            (: $3->set_long( "This is a thick, green "
            "mush, $amount_size$.  It smells "
            "terrible, and is bubbling slightly.\n" ) :),
            (: $3.set_medium_alias( "ThickGreenOoze" ) :),
            (: $3.add_eat_effect( "/std/effects/ingested/drunk", 50 ) :),
            })
            data["BlueHealingWater"]["BrewedComfreyYarrowTea"] = item
            if (!mapp(data["BlueHealingWater"])) data["BlueHealingWater"] = ([])
            item = new( class reaction )
            item->ratio = [1.0, 1.0]
            item->result = "/obj/reagents/generic_liquid.ob"
            item->result_amt = 1.0
            item->func = ({
            (: $3.set_name( "ooze" ) :),
            (: $3.add_alias( "green ooze" ) :),
            (: $3.set_short( "thick green ooze" ) :),
            (: $3.set_main_plural( "thick green oozes" ) :),
            (: $3.add_plural( "oozes" ) :),
            (: $3.add_adjective( "green" ) :),
            (: $3->set_long( "This is a thick, green "
            "mush, $amount_size$.  It smells "
            "terrible, and is bubbling slightly.\n" ) :),
            (: $3.set_medium_alias( "ThickGreenOoze" ) :),
            (: $3.add_eat_effect( "/std/effects/ingested/drunk", 50 ) :),
            })
            data["BlueHealingWater"]["ComfreyYarrowTea"] = item


    def data_return(self, ) -> Any:
            data_return_0()
            return data



class Base.hdr_dc(MudObject):
