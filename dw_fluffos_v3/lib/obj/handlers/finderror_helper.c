#include <log.h>
#include <config.h>
#include <db.h>
nosave inherit "/std/object";
private void recursive_add_directory( string word, string dir );
class error_data {
    string name;
    string *dirs;
    int no_calls;
}
nosave mapping _error_cache;
string name, *dirs;
void create() {
    ::create();
    set_name( "finderror_helper" );
    set_short( "finderror helper" );
    _error_cache = ([ ]);
}
private string strip_extension( string file ) {
    if ( file[<1] == '/' ) {
        return file[0..<2];
    }
    return file;
}
private class error_data get_data_file( string word ) {
    string file;
    if ( _error_cache[ word ] ) {
        return _error_cache[ word ];
    }
    seteuid( word );
    file = "/w/" + word + "/finderror.o";
    if ( file_size( file ) > 0 ) {
        unguarded( (: restore_object, file :) );
        _error_cache[ word ] = new( class error_data,
            name : name,
            dirs : map( dirs, (: strip_extension :) ),
            no_calls : 0 );
    }
    else {
        _error_cache[ word ] = new( class error_data,
            name : word,
            dirs : ({ }),
            no_calls : 0 );
    }
    return _error_cache[ word ];
}
private int save_data_file( string word ) {
    seteuid( word );
    if ( _error_cache[ word ] ) {
        name = _error_cache[ word ]->name;
        dirs = _error_cache[ word ]->dirs;
        unguarded( (: save_object, "/w/" + word + "/finderror" :) );
        return 1;
    }
    return 0;
}
string escape( string txt ) {
    return replace( txt, ({ "'", "\\'" }) );
}
private string assemble_dirs_sql( string *dirs ) {
    dirs = map( dirs, (: escape :) );
    return "(" + implode( map( dirs,
            (: "Directory" + ( strsrch( $1, "%" ) > -1 ? " LIKE " : " = " )
            +  "'" + $1 + "'" :) ), " OR " ) + ")";
}
void finished_query( int status, mixed data, function func, object player ) {
    evaluate( func, player, status, data );
}
public int query_dirs_count(mixed player, function finish_func ) {
  class error_data info;
  string query;
  string txt;
  string word;
    if ( objectp( player ) ) {
  word = player->query_name();
    }
    else {
        word = player;
        player = this_object();
    }
  info = get_data_file( word );
  if ( sizeof( info->dirs ) ) {
        txt = assemble_dirs_sql( info->dirs );
        query = "SELECT Directory, Type, COUNT(Id) FROM errors WHERE " + txt + " AND "
            "Status = 'OPEN' GROUP BY Directory, Type;";
        DB_HANDLER->make_sql_request("errors", CONFIG_DB_ERRORS_USER, "",
            query, (: finished_query( $1, $2, $(finish_func), $(player) ) :) );
        return 1;
  }
  return 0;
}
public int query_errors_in_dirs(string *directories, function finish_func ) {
    string query;
    string txt;
    if ( directories ) {
        directories = map( directories , (: escape :) );
        txt = "(" + implode( map( directories,
            (: "Directory" + ( strsrch( $1, "%" ) > -1 ? " LIKE " : " = " )
            +  "'" + $1 + "'" :) ), " OR " ) + ")";
        query = "SELECT Directory, Type, COUNT(Id) AS C FROM errors WHERE " + txt + " AND "
            "Status = 'OPEN' GROUP BY Directory, Type";
        DB_HANDLER->make_sql_request("errors", CONFIG_DB_ERRORS_USER, "",
            query, (: finished_query( $1, $2, $(finish_func), $(this_player()) ) :) );
        return 1;
    }
    return 0;
}
public void query_next_dir( object player, function finish_func ) {
    string query;
    string txt;
    string word;
    class error_data info;
    word = player->query_name();
    info = get_data_file( word );
    if ( sizeof( info->dirs ) ) {
        txt = assemble_dirs_sql( info->dirs );
        query = "SELECT Directory, COUNT(Id) AS C FROM errors WHERE " + txt +
            " AND Status = 'OPEN' GROUP BY Directory HAVING C > 0 LIMIT 1;";
        DB_HANDLER->make_sql_request( "errors", CONFIG_DB_ERRORS_USER, "",
            query, (: finished_query( $1, $2, $(finish_func), $(player) ) :) );
    }
    else {
        tell_object( player, "You have no finderrors directories defined.  Add "
            "them with 'finderrors add'\n" );
    }
}
public string *query_directories( string player ) {
    class error_data data;
    data = get_data_file( player );
    return copy( data->dirs );
}
public int add_directory( object player, string dir, int recursive ) {
    int res;
    class error_data info;
    string word;
    word = player->query_name();
    info = get_data_file( word );
    res = member_array( dir, info->dirs );
    if ( recursive )  {
        dir += "%";
    }
    if ( res == -1 ) {
        if ( dir[ <1 ] == '/') {
            dir = dir[ 0 .. <2 ];
        }
        info->dirs = ({ dir }) + info->dirs;
        tell_object( player, "Added " + dir +
            (recursive ? " (recursive)" : "") + "\n" );
        save_data_file( word );
    }
    return 1;
}
private void recursive_add_directory( object player, string dir ) {
    mixed *directories, *file;
    class error_data info;
    string word;
    word = player->query_name();
    info = get_data_file( word );
    info->no_calls--;
    directories = get_dir( dir, -1 );
    if ( directories ) {
        foreach ( file in directories ) {
            if ( file[ 1 ] == -2 && file[ 0 ] != "Maps") {
                add_directory( player, dir + file[ 0 ] +"/", 1 );
            }
        }
    }
    if ( info->no_calls == 0 ) {
        tell_object( player,
            "All subdirectories have been added to the list.\n" );
        save_data_file( word );
    }
}
public int remove_directory( object player, string directory, int recursive ) {
    class error_data info;
    string word;
    int pos;
    word = player->query_name();
    info = get_data_file( word );
    if ( recursive ) {
        pos = sizeof( directory ) - 1;
        info->dirs = filter( info->dirs,
            (: $1[ 0..$(pos) ] != $(directory) :));
    }
    else {
        pos = member_array( directory, info->dirs );
        if ( pos == -1 ) {
            return 0;
        }
       info->dirs = info->dirs[ 0..pos - 1 ] + info->dirs[ pos+1.. ];
    }
    save_data_file( word );
    return 1;
}