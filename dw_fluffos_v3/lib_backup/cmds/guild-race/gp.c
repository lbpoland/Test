#include <skills.h>
inherit "/cmds/guild_base";
void create() {
   ::create();
   set_nroff_file("gp");
   set_command_name("gp");
}
int cmd() {
   int i, gp, max_gp, other_gp;
   gp = (int)this_player()->query_gp();
   max_gp = (int)this_player()->query_max_gp();
   write( "You have "+ gp +" ("+ max_gp +") guild points.\n" );
   for ( i = 0; i < sizeof( STD_SKILLS ); i += SKILL_ARR_SIZE ) {
      other_gp = (int)this_player()->query_skill_bonus( STD_SKILLS[ i ]
            +".points" ) + 50;
      if ( other_gp >= max_gp ) {
         write( "* All of your guild points can be used for "+
               STD_SKILLS[ i ] +" commands.\n" );
         continue;
      }
      if ( gp + other_gp <= max_gp ) {
         write( "* You cannot use any guild points for "+
               STD_SKILLS[ i ] +" commands until\n    your points "+
               "reach "+ ( max_gp - other_gp ) +".\n" );
         continue;
      }
      write( "* You can use "+ ( gp + other_gp - max_gp ) +" ("+ other_gp +
            ") for "+ STD_SKILLS[ i ] +" commands.\n" );
   }
   return 1;
}