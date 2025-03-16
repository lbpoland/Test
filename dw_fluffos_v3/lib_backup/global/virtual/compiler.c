#include "virtual.h"
#include "compiler.h"
void    initialize_methods();
string  strip_string( string str );
#define WHITESPACE(c) (c == 10 || c == 32 || c == '\n')
mapping o_funcs;
mapping r_funcs;
mapping arm_funcs;
mapping clo_funcs;
mapping sca_funcs;
mapping wep_funcs;
mapping cont_funcs;
mapping food_funcs;
mapping mon_funcs;
mapping clotrans_funcs;
object  return_ob;
int     tmp_file_no;
int     debug_file;
void    create()
{
  seteuid("Root");
  initialize_methods();
  o_funcs = O_FUN;
  r_funcs = O_FUN + R_FUN;
  arm_funcs = ARM_FUN + O_FUN;
  clo_funcs = CLO_FUN + O_FUN;
  sca_funcs = SCA_FUN + O_FUN;
  wep_funcs = WEP_FUN + O_FUN;
  mon_funcs = MON_FUN + O_FUN;
  cont_funcs = CONT_FUN + O_FUN;
  food_funcs = FOOD_FUN + CONT_FUN + O_FUN;
  clotrans_funcs = O_FUN + CLO_FUN + CLOTRANS_FUN;
}
object  query_return_ob()
{
    return return_ob;
}
void    set_return_ob( object ob )
{
    return_ob = ob;
}
void    initialize_methods()
{
    SERVER->add_method( "r", file_name( this_object() ), "compile_r",
                        CLONE|LOAD );
    SERVER->add_method( "ro", file_name( this_object() ), "compile_r",
                        CLONE|LOAD );
    SERVER->add_method( "ob", file_name( this_object() ), "compile_ob" );
    SERVER->add_method( "arm", file_name( this_object() ), "compile_arm" );
    SERVER->add_method( "clo", file_name( this_object() ), "compile_clo" );
    SERVER->add_method( "trans", file_name( this_object() ), "compile_clotrans" );
    SERVER->add_method( "sca", file_name( this_object() ), "compile_sca" );
    SERVER->add_method( "wep", file_name( this_object() ), "compile_wep" );
    SERVER->add_method( "mon", file_name( this_object() ), "compile_mon" );
    SERVER->add_method( "food", file_name( this_object() ), "compile_food" );
    SERVER->add_method( "cont", file_name( this_object() ), "compile_cont" );
    SERVER->add_method( "imp", file_name( this_object() ), "compile_imp" );
}
#define Error(s) write(s); log_file( "VO_COMPILER", s); return 0;
mixed  *extract_arguments( string str );
void    do_clone( object dest, string str )
{
    object  ob;
    ob = clone_object( str );
    if( ob )
        ob->move( dest );
}
object  prop_to_fun( string file, mapping funs, string virt_class,
                    string virt_include, int clone )
{
    string *segments, *ind, data, s1, dir, tmp_name, tmp_val;
    string file_data;
    mixed  *val;
    int     i;
    int pos;
    debug_file = 0;
    file_data = "";
    pos = strsrch(file, "/", -1);
    tmp_name = file[0..pos] + "." + file[pos+1..] + "_virtual_.c";
    if (file_size(tmp_name) <= 0 ||
        stat(file)[1] > stat(tmp_name)[1]) {
       tmp_file_no++;
       if( find_object( tmp_name ) ) {
           tmp_name->dest_me();
       }
       ind = explode( file, "/" );
       dir = implode( ind[ 0..sizeof( ind ) - 2 ], "/" );
       unguarded((: rm, tmp_name :));
       file_data = "#include <"+ virt_include +">\n\n"
                "void dest_me() { destruct( this_object() ); }\n\n"
                "void create()\n{\n"
                "  seteuid( (string)\"/secure/master\"->creator_file( file_name( this_object() ) ) );\n"
                "} \n"
                "\nobject create_virtual_ob() {\n"
                "   object clone;\n\n";
       data = read_file( file );
       if( !data )
       {
           Error( "prop_to_fun() : file " + file + " not found\n" );
       }
       segments = explode( "$\n" + data, "\n#" );
       if( !segments )
       {
           Error( "prop_to_fun() : Nothing but comments?\n" );
       }
       segments[ 0 ] = segments[ 0 ][ 1..(sizeof(segments[ 0 ]) - 1) ];
       for( i = 1; i < sizeof( segments ); i++ ) {
           if( sscanf( segments[ i ], "%s\n%s", s1, segments[ i ] ) != 2 ) {
               segments[ i ] = "";
           }
       }
       data = implode( segments, "\n" );
       segments = explode( strip_string( data ), "::" );
       if (sizeof( segments ) % 2) {
         segments += ({""});
       }
       ind = allocate( sizeof( segments ) / 2 );
       val = allocate( sizeof( segments ) / 2 );
       for( i = 0; i < sizeof( ind ); i++ )
       {
           ind[ i ] = segments[ i * 2 ];
           val[ i ] = replace( segments[ i * 2 + 1 ], "\n", " " );
           if( ind[ i ][ 0..0 ] == "#" )
           {
               ind[ i ] = lower_case( ind[ i ] );
               if( ind[ i ] == "#debug" )
               {
                   sscanf( val[ i ], "%d", debug_file );
               }
               else
               {
                   if( ind[ i ] == "#class" )
                   {
                       virt_class = replace( val[i], " ", "" );
                   }
                   else
                   {
                       if( ind[ i ] == "#include" )
                       {
                           tmp_val = val[i];
                           file_data += "#include " +
                                       replace( tmp_val, " ", "" ) +
                                       "\n";
                       }
                   }
               }
           }
       }
       file_data += "  clone = (object)SERVER->create_virtual_object( " +
                   virt_class + ", 1 );\n"
                   "  clone->add_property( VIRTUAL_NAME_PROP, \""
                   + file + (clone ? "#1" : "") + "\" );\n";
       for( i = 0; i < sizeof( ind ); i++ )
       {
           ind[ i ] = lower_case( ind[ i ] );
           if( ind[ i ][ 0..0 ] == "#" )
           {
               continue;
           }
           val[ i ] = replace( val[ i ], ({"(:", "bind( (:",
                                           ":)", ":), clone )" }) );
           if( ind[ i ][ 0..0 ] == "$" )
           {
               {
                   file_data +="  call_other( clone, \"" +
                               ind[ i ][ 1..100 ] + "\", " + val[ i ] +
                               " );\n";
               }
               continue;
           }
           if( funs[ ind[ i ] ] )
           {
               if( !pointerp( funs[ ind[ i ] ] ) )
               {
                   file_data += "  call_other( clone, \"" +
                               funs[ ind[ i ] ] + "\", " + val[ i ] + " );\n";
               }
               else
               {
                   file_data += "  call_other( " + funs[ ind[ i ] ][ 1 ] +
                               ", " + funs[ ind[ i ] ][ 0 ] + ", " + val[ i ] +
                               " );\n";
               }
           }
           else
           {
               write( "Error: Unknown index " + ind[ i ] + "\n" );
           }
       }
       file_data += "   return clone;\n} \n";
       unguarded((: write_file, tmp_name, file_data :));
   }
   if( data = catch( return_ob = tmp_name->create_virtual_ob() ) )
   {
        write( "Error loading " + file + ", " + data + "\n" );
        if( debug_file )
        {
            write( "File not removed.\n" );
        }
        else
        {
        }
    }
    else
    {
        tmp_name->dest_me();
        return return_ob;
    }
}
string  strip_string( string str )
{
    int     i, j;
    j = strlen( str ) - 1;
    for( ; WHITESPACE( str[ i ] ) && i < j; i++ ) ;
    for( ; WHITESPACE( str[ j ] ) && j > i; j-- ) ;
    return str[ i..j ];
}
mixed   str_to_var( string str )
{
    int     i;
    str = strip_string( str );
    switch( str[ 0 ] )
    {
        case '{':
            {
                str = str[ 1..strlen( str ) - 2 ];
                return map_array( explode( str, "," ), "str_to_var",
                                  this_object() );
            }
        case '"':
            {
                str = str[ 1..strlen( str ) - 2 ];
                return replace( str, "\n", " " ) + "\n";
            }
        case '0'..'9':
        case '-':
            {
                sscanf( str, "%d", i );
                return i;
            }
    }
    return str;
}
mixed  *extract_arguments( string str )
{
    return map_array( explode( str, "
}
object  compile_r( string name, int clone ) {
    object r;
    r = prop_to_fun( name, r_funcs, "\"/obj/virtual_room.c\"",
                    "virtual_room.h", 1 );
    r->reset();
    return r;
}
object  compile_ob( string name, int clone ) {
    return prop_to_fun( name, o_funcs, "\"/std/object.c\"",
                    "virtual.h", clone );
}
object  compile_arm( string name, int clone ) {
    if (name[0 .. 19] == "/obj/armours/shield/")
        return prop_to_fun(name, arm_funcs, "\"/obj/shield.c\"",
                        "virtual.h", clone );
    return prop_to_fun( name, arm_funcs, "\"/obj/armour.c\"",
                    "virtual.h", clone );
}
object  compile_clo( string name, int clone ) {
    return prop_to_fun( name, clo_funcs, "\"/obj/clothing.c\"",
                    "virtual.h", clone );
}
object compile_sca( string name, int clone ) {
   return prop_to_fun( name, sca_funcs, "\"/obj/scabbard.c\"",
                    "virtual.h", clone );
}
object  compile_wep( string name, int clone ) {
    return prop_to_fun( name, wep_funcs, "\"/obj/weapon.c\"",
                    "virtual.h", clone );
}
object  compile_mon( string name, int clone ) {
    return prop_to_fun( name, mon_funcs, "\"/obj/monster.c\"",
                    "virtual.h", clone );
}
object  compile_food( string name, int clone ) {
    return prop_to_fun( name, food_funcs, "\"/obj/food.c\"",
                    "virtual.h", clone );
}
object  compile_cont( string name, int clone ) {
    return prop_to_fun( name, cont_funcs, "\"/obj/cont_medium.c\"",
                    "virtual.h", clone );
}
object  compile_clotrans( string name, int clone ) {
    return prop_to_fun( name, clotrans_funcs, "\"/obj/clothing_transport.c\"",
                    "virtual.h", clone );
}
object  compile_imp( string name, int clone ) {
    return prop_to_fun( name, o_funcs, "\"/obj/implement.c\"",
                    "virtual.h", clone );
}
int set_debug_status(int d_stat) {
  debug_file=d_stat;
  return debug_file;
}