#define LORD "wyvyrn"
#define DOMAIN "liaison"
#include <liaison.h>
inherit "/std/dom/base_master";
mapping member_alias;
nosave string* member_cache = 0;
string query_lord() {
  return LORD;
}
string author_file(string *path) {
  return capitalize(DOMAIN);
}
int check_permission(string euid, string *path, int mask) {
  if (euid == query_lord())
    return 1;
  return ::check_permission(euid, path, mask);
}
int valid_read(string *path, string euid, string funct);
int valid_write(string *path, string euid, string funct);
int query_member(string name) {
  return !undefinedp(members[name]) || name == LORD;
}
string log_who(string where) {
  return "eron";
}
string query_info() {
  if (file_size(LIAISON_DOMAIN_INFO) < 0) {
    return "\nFor information on this domain, please visit "
           "http:
  }
  return "\n"+ unguarded((: read_file(LIAISON_DOMAIN_INFO) :)) +"\n";
}
string *member_alias( string name ) {
   int i;
   if ( !member_alias )
      member_alias = ([ ]);
   if ( undefinedp( members[ name ] ) ) {
      map_delete(member_alias, name);
      return 0;
   }
   if ( !member_alias[ name ] )
      member_alias[ name ] = ({ });
   i = sizeof( member_alias[ name ] );
   while ( i-- )
      member_alias[ name ][ i ] = lower_case( member_alias[ name ][ i ] );
   return member_alias[ name ] + ({ });
}
int add_member_alias( string name, string alias ) {
   if ( !members[ name ] )
      return 0;
   if ( !"/secure/login"->test_user( alias ) )
      return 0;
   if ( !member_alias )
      member_alias = ([ ]);
   if ( !member_alias[ name ])
      member_alias[ name ] = ({ });
   member_alias[ name ] -= ({ alias });
   member_alias[ name ] += ({ alias });
   save_me();
   return 1;
}
int delete_member_alias( string name, string alias ) {
   if ( !members[ name ] )
      return 0;
   if ( !member_alias )
      member_alias = ([ ]);
   if ( !member_alias[ name ])
      member_alias[ name ] = ({ });
   member_alias[ name ] -= ({ alias });
   save_me();
   return 1;
}
string *query_unsorted_members() {
    return ::query_members();
}
string *query_members() {
    string* temporary_array = ({});
    string* first = ({});
    string* seniors = ({});
    string* newbies = ({});
    if (!member_cache) {
        first = ({ query_lord() })   +
                sort_array(query_deputies(),1);
        temporary_array = ::query_members() - first;
        temporary_array = sort_array( temporary_array, 1 );
        foreach ( string person in temporary_array ) {
          if ( master()->query_senior(person) ) {
              seniors += ({ person });
          }
        }
        temporary_array -= seniors;
        foreach ( string person in temporary_array ) {
          if ( regexp( members[ person ], "^(N|n)ewbie$" ) ) {
              newbies += ({ person });
          }
        }
        temporary_array -= newbies;
        member_cache = first + seniors + temporary_array + newbies;
    }
    return copy(member_cache);
}
string *query_projects() {
    return values(members);
}