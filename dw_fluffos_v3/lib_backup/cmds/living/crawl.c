#define EFFECTPATH "/std/effects/other/"
#define PT "/obj/handlers/playtesters"
inherit "/cmds/base";
int is_in_water( object room );
varargs int cmd( string str ) {
   if( str == "stop" ) {
      if( !this_player()->query_crawling() ) {
         this_player()->add_failed_mess( this_object(),
                                         "You should be crawling first in order"
                                         " to stop doing it, don't you "
                                         "think?\n",
                                         ({ }) );
         return 0;
      };
      this_player()->stop_crawling();
      return 1;
   };
   if( !str ) {
      if( this_player()->query_property( "dead" ) ) {
         this_player()->add_failed_mess( this_object(),
                                         "You appear to be dead.  There is no "
                                         "necessity to torture your morphogenic"
                                         " arms, you know?\n",
                                         ({ }) );
         return 0;
      } else if( this_player()->query_crawling() ) {
         this_player()->add_failed_mess( this_object(),
                                         "You are already crawling.\n",
                                         ({ }) );
         return 0;
      } else if( is_in_water( environment( this_player() ) ) ) {
         this_player()->add_failed_mess( this_object(),
                                         "You are in water at the moment, so "
                                         "crawling is impossible.\n",
                                         ({ }) );
         return 0;
      } else {
         this_player()->add_effect( EFFECTPATH + "crawling" );
         return 1;
      };
   };
}
mixed* query_patterns() {
   return ({
      "", (: cmd() :),
      "stop", (: cmd( "stop" ) :)
   });
}
int is_in_water( object room ) {
   if( inherits( "/std/water_inside.c", room ) ||
       inherits("/std/water_outside.c", room ) ||
       inherits("/std/uwater.c", room ) ) {
      return 1;
   } else
      return 0;
}