#include "path.h";
inherit PLAYER_HOUSE;
void setup() {
   set_light(50);
   set_theft_handler( HOSPITAL );
   set_save_file("%savedir%/%N%bed3");
   set_orientation(%orientation%);
  set_quit_handler(%out%);
   set_short("bedroom");
   set_base_desc( "a small bedroom" );
   add_surface( "floor", "finished pine board" );
   add_surface( "ceiling", "plain plaster" );
   add_surface( "%0% wall", "plain plaster" );
   add_surface( "%2% wall", "plain plaster" );
   add_surface( "%4% wall", "plain plaster" );
   add_surface( "%6% wall", "plain plaster" );
   add_exit( "%0%", PATH +"%N%landing2", "door" );
   modify_exit("%0%", ({ "door short", "bedroom door" }));
   add_exit("window", PATH + "%N%half-roof", "window");
}