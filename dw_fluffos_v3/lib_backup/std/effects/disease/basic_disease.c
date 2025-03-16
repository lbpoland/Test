#include <effect.h>
#include <disease.h>
int do_setup;
string name, classification, shadow_ob;
void set_name( string str ) { name = str; }
string query_name() { return name; }
void set_classification( string str ) { classification = str; }
string query_classification() { return classification; }
void create() {
   name = "Some undefined disease";
   classification = "disease.unset";
   if ( !do_setup )
      this_object()->setup();
}
int cure( object person, string cure_classification, int power, int enum ) {
   int arg, i, scale;
   string *cure_class, *disease_class;
   arg = person->arg_of( enum );
   disease_class = explode( classification, "." )[ 1 .. <1 ];
   cure_class = explode( cure_classification, "." )[ 1 .. <1 ];
   while ( sizeof( disease_class ) && sizeof( cure_class ) &&
          ( disease_class[ 0 ] == cure_class[ 0 ] ) ) {
      disease_class = disease_class[ 1 .. <1 ];
      cure_class = cure_class[ 1 .. <1 ];
   }
   scale = 1;
   i = sizeof( disease_class );
   while ( i-- )
      scale *= DISEASE_SCALE[ i ];
   i = sizeof( cure_class );
   while ( i-- )
      scale *= CURE_SCALE[ i ];
   arg -= power / scale;
   power = -arg * scale;
   person->set_arg_of( enum, arg );
   if ( arg > 0 )
      this_object()->disease_better( person, arg );
   return power;
}