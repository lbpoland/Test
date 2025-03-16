inherit "/obj/lantern";
void setup() {
   fuel_left = 3600;
   is_lit    = 0;
   set_name( "lantern" );
   set_main_plural( "lanterns");
   set_short( "lantern" );
   add_help_file("torch");
   set_long(function() {
     string str;
     str = "This is a camping lantern, which smells of lamp oil.\n";
     if ( is_lit ) {
       return str + "The wick flickers inside spreading a dull "
         "glow.\n";
     }
     str += "The lantern is not lit, and ";
     if ( !fuel_left )
       return str + "is out of oil.\n";
     return str + "has some oil left in it.\n";
   } );
   set_weight( 60 );
   set_value( 150 );
}