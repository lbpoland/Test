#include <parse_command.h>
inherit "/std/object";
string item_name;
int scarcity;
string get_failure_mess = "Use \"gather\"\n";
void create() {
    ::create();
    reset_get();
}
void set_item_name(string name) { item_name = name; }
string query_item_name() { return item_name; }
void set_scarcity(int s) { scarcity = s; }
int query_scarcity() { return scarcity; }
void set_get_failure_mess(string s) { get_failure_mess = s; }
int do_get() {
    return notify_fail( get_failure_mess );
}