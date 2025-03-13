# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/newspaper_subscription.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._subscribers = ([ ])


    def query_price_per_issue_subscriber(self, ) -> int:
            int deposit_cost = 400
            return deposit_cost + ( NEWSPAPER_HANDLER.query_paper_cost( _paper ) * 2 )


    def query_price_per_issue_box(self, ) -> int:
            return NEWSPAPER_HANDLER.query_paper_cost( _paper )


    def query_price_newspaper_box(self, ) -> int:
            return load_object( NEWSPAPER_SUBSCRIPTION_OB )->query_value() +
            ISSUES_PER_BOX * NEWSPAPER_HANDLER.query_paper_cost( _paper )


    def query_price_international_newspaper_box(self, ) -> int:
            return (load_object( NEWSPAPER_SUBSCRIPTION_OB )->query_value() +
            ISSUES_PER_BOX * NEWSPAPER_HANDLER.query_paper_cost( _paper )) * 2


    def dest_me(self, ) -> None:
            save_me()
            ::dest_me()


    def event_publish_paper(self, paper: str) -> None:
            string name
            int issues
            int price
            int last_issue = NEWSPAPER_HANDLER.query_last_edition_num( _paper )
            if (paper != _paper) {
            return


    def set_money_place(self, new_region: str) -> None:
            _region = new_region


    def query_money_place(self, ) -> str:
            return _region


    def do_subscribe(self, numbers: int) -> int:
            string name
            int price
            string mess
            if( !numbers || !this_player() || numbers < -1 ) {
            return 0


    def do_unsubscribe(self, ) -> int:
            if( undefinedp( _subscribers[ this_player()->query_name() ] ) ) {
            add_failed_mess( "You don't have a subscription for " + _paper +
            ", so you cannot unsubscribe.\n" )
            return 0


    def do_buy(self, international: int) -> int:
            object box
            int price
            if( international == 1 ) {
            price = query_price_international_newspaper_box()
            } else {
            price = query_price_newspaper_box()


    def do_check(self, ) -> int:
            int i
            if( !this_player() ) {
            return 0


    def do_list(self, subscription_type: str) -> int:
            string* subscriber_list
            string name
            subscriber_list = [})
            if( !this_player() || !subscription_type ) {
            return 0


    def init(self, ) -> None:
            string _office
            object office = 0
            add_command( "subscribe",
            "[to] <number> [issue|issues] of " + _paper,
            (: do_subscribe( $4[0] ) :) )
            add_command( "subscribe",
            "[to] " + _paper,
            (: do_subscribe( -1 ) :) )
            add_command( "unsubscribe",
            "[from] " + _paper,
            (: do_unsubscribe() :) )
            add_command( "buy",
            "[a] newspaper box",
            (: do_buy( 0 ) :) )
            add_command( "buy",
            "[an] international newspaper box",
            (: do_buy( 1 ) :) )
            add_command( "check",
            "subscription",
            (: do_check() :) )
            if( _office = NEWSPAPER_HANDLER.query_paper_office( _paper ) ) {
            office = load_object( _office )



class Newspaper_subscription(MudObject):

    _subscribers = '([ ])'
