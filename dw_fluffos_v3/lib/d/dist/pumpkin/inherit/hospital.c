#include <armoury.h>
#include <hospital.h>
#include "path.h"
#include HOSPITAL_INC
#define CREATE_NPCS 1
#define REGEN_TIME 1 * 60 * 60
#define DEFAULT_LOG_DIRECTORY "/d/cwc/log"
#define DEFAULT_POPULATION 3
#define MINIMUM_DEATH_REGEN 3
inherit "/std/room";
class regenerated_npc {
    string type;
    string load_position;
}
protected void load_file();
protected void save_file();
protected void set_save_file(string new_save);
protected void restore_default_npcs();
protected void set_max_living(int new_living);
protected void set_hospital_type(string new_type);
protected object *make_monster(string type);
public object *get_monster(string type);
public void hospital_log_file(string file, string format, mixed *args ...);
public int get_item(object destination, string *items);
public string query_save_file();
public int query_max_living();
public int *query_npcs();
public mapping query_hospital_npcs();
public void add_npc_type(string type, string *data);
public void regen_after_death( object dead_npc );
private nosave string _save_file, _hospital_type;
private nosave int _max_living;
private nosave mixed *_regenerated_npcs;
private nosave int _hospital_call_id;
private nosave mapping _log_file_info;
private nosave string _hospital_log_directory;
public mapping _unique_npcs;
public mapping _hospital_npcs;
public int _last_npc_check, _zone_npcs;
private nosave mapping _npc_groups;
private nosave mapping _npc_info;
void create() {
    seteuid(master()->creator_file(file_name(this_object())));
    do_setup++;
    ::create();
    do_setup--;
    if (_save_file) {
        load_file();
        if (!_hospital_npcs) {
            restore_default_npcs();
        }
        if (!_unique_npcs) {
            _unique_npcs = ([ ]);
        }
        save_file();
    }
    if (!_npc_groups)
        _npc_groups = ([ ]);
    if (!_npc_groups)
        _npc_info = ([ ]);
    _regenerated_npcs = ({ });
    _log_file_info = ([ ]);
    if (!do_setup) {
        set_short("Counterweight Continent Hospital");
        set_long("All around you NPC's wait in neat little lines, "
            "ready to be sent on a massive journey that will ultimately "
            "lead to their deaths.  Some of them stand by a small window "
            "in the far wall, looking out at freedom.\n");
        add_property("determinate", "the ");
        set_light(60);
    }
}
public int get_item(object destination, string *items) {
    int i;
    object item;
    if (!objectp(destination)) {
        return 0;
    }
    while (!item) {
        i = random(sizeof(items));
        item = ARMOURY->request_item(items[i], 80 + random(21));
        if (!objectp(item)) {
            items = items[0..i-1] + items[i+1..];
            continue;
        }
        if (!sizeof(items)) {
            hospital_log_file("BROKEN_ITEMS", "Unable to select any items "
                "for %s in the CWC hospital.\n", previous_object()->short());
            break;
        }
    }
    if (objectp(item)) {
        item->move(destination);
        return 1;
    }
    return 0;
}
protected void load_file() {
    if (file_size(_save_file + ".o") > -1) {
        unguarded((: restore_object, _save_file :));
    }
}
protected void save_file() {
    unguarded((: save_object, _save_file :));
}
protected void set_save_file(string new_save) {
    _save_file = new_save;
}
public string query_save_file() {
    return _save_file;
}
public int make_unique(mixed who) {
    if (!_unique_npcs)
        return 0;
    if (objectp(who))
        who = who->query_name();
    if ( _unique_npcs[who] > time() )
        return 0;
    _unique_npcs[who] = time() + REGEN_TIME;
    save_file();
}
public int query_regen_time(mixed who) {
    if (objectp(who))
        who = who->query_name();
    if (!_unique_npcs)
        return 0;
    return _unique_npcs[who];
}
protected void set_max_living(int new_living) {
    _max_living = new_living;
}
public int query_max_living() {
    return _max_living;
}
protected void restore_default_npcs() {
    _hospital_npcs = ([ ]);
}
public int ok_to_clone(string where) {
    if (time() > _last_npc_check + 300) {
        _last_npc_check = time();
        _zone_npcs = sizeof(filter(named_livings(), (: environment($1) &&
            base_name(environment($1))[0..(sizeof(CWC) + sizeof($(where)) - 1)] ==
                (CWC + $(where)) :)));
    }
    return _zone_npcs < _max_living;
}
public int *query_npcs() {
    return ({ _zone_npcs, _last_npc_check });
}
public void add_npc_type(string type, string *data) {
    if (undefinedp(_hospital_npcs[type])) {
        _hospital_npcs[type] = copy(data);
    }
    else {
        if (arrayp(_hospital_npcs[type])) {
            _hospital_npcs[type] += data;
        }
    }
    save_file();
}
public mapping query_hospital_npcs() {
    return copy(_hospital_npcs);
}
public object *get_monster(string type) {
    object *monsters, monster;
    if (_hospital_npcs[type]) {
        tell_creator("taffyd", "Attempting to create a %s NPC.\n", type);
        monsters = make_monster(_hospital_npcs[type][random(sizeof(_hospital_npcs[type]))]);
        tell_creator("taffyd", "Monsters are now %O.\n", monsters);
    }
    else {
        monsters = make_monster(type);
    }
    foreach (monster in monsters) {
        monster->add_property("monster_type", type);
        monster->add_effect("/std/effects/npc/i_died",
            (: regen_after_death :) );
    }
    return monsters;
}
protected object *make_monster(string type) {
    object monster;
    monster = clone_object("/obj/monster");
    monster->set_name("failure");
    monster->set_short("hospital accident");
    monster->set_race("human");
    monster->set_guild("warrior");
    monster->set_level(1);
    return ({ monster });
}
public void regen_after_death( object dead_npc ) {
    object *monsters, destination;
    class regenerated_npc new_npc;
    int i, max;
    if ( !dead_npc )
        return;
    _regenerated_npcs += ({ new( class regenerated_npc,
        type : dead_npc->query_property("monster_type"),
        load_position : previous_object()->query_property("start location") ) });
    if ( !ok_to_clone(_hospital_type) || sizeof(_regenerated_npcs) < MINIMUM_DEATH_REGEN )
        return;
    new_npc = _regenerated_npcs[0];
    if ( !classp( new_npc ) )
        return;
    _regenerated_npcs = _regenerated_npcs[1..];
    if (!new_npc->load_position || !new_npc->type );
        return;
    max = random(5);
    for ( i = 0; i < max; i++ ){
        destination = find_object( new_npc->load_position );
        if ( !objectp( destination ) )
            return;
        monsters = get_monster(new_npc->type);
        destination->replace_monster(previous_object(), monsters);
        call_out((: $1->announce_entry($2) :), 8 + random(6), destination,
            monsters);
    }
}
protected void set_hospital_type(string new_type) {
    _hospital_type = new_type;
}
public void hospital_log_file(string file, string format, mixed *args ...) {
    string filename;
    filename = _hospital_log_directory;
    if (file[0] == '/') {
        file = file[ strsrch( file, "/", -1 ) + 1 .. ];
    }
    log_file( _hospital_log_directory + "/" + file, format, args ...);
}
protected void set_log_directory(string new_dir) {
    if (file_size(new_dir) != -2) {
        tell_creator( previous_object( 1 ), "%s: Invalid "
            "log directory -- defaulting to %s.\n",
            file_name( this_object() ), DEFAULT_LOG_DIRECTORY );
        new_dir = DEFAULT_LOG_DIRECTORY;
    }
    _hospital_log_directory = new_dir;
}
protected void set_npc_groups(mapping x) {
    _npc_groups = x;
}
protected void set_npc_info(mapping x) {
    _npc_info = x;
}
public object data_get_npc(string npc_name) {
    class npc_info info;
    object npc;
    function func;
    if ( undefinedp(_npc_info[npc_name]) )
        return 0;
    info = _npc_info[npc_name];
    if (stringp(info->base))
        npc = clone_object(info->base);
    else
        return 0;
    if (arrayp(info->functions)) {
        foreach (func in info->functions) {
            evaluate(func, npc, previous_object());
        }
    }
    return npc;
}
object *data_get_group(string group_name) {
    class npc_group group;
    function func;
    int population, quantity, i;
    object *npcs, npc;
    if ( undefinedp(_npc_groups[group_name]) )
        return 0;
    group = _npc_groups[group_name];
    if (functionp(group->population))
        population = evaluate(group->population);
    else {
        population = DEFAULT_POPULATION;
    }
    if (!group->storage) {
        group->storage = ({ });
    }
    else {
        group->storage = filter(group->storage, (: objectp($1) :));
        if (sizeof(group->storage) >= population)
            return 0;
    }
    if (functionp(group->quantity)) {
        quantity = evaluate(group->quantity);
    }
    else {
        quantity = 1;
    }
    if (stringp(group->npc)) {
        npcs = allocate(quantity);
        for (i = 0; i < quantity; i++) {
            npcs[i] = data_get_npc(group->npc);
        }
        npcs = filter(npcs, (: objectp($1) :));
        group->storage += npcs;
    }
    foreach (npc in npcs) {
        if (arrayp(group->functions)) {
            foreach (func in group->functions) {
                evaluate(func, npc, previous_object());
            }
        }
    }
    return npcs;
}
mixed accumulate_npc_array( mixed a ) {
    int cum, i;
    mixed choices;
    choices = copy(a);
    cum = 0;
    for (i = 0; i < sizeof(choices); i++) {
        cum += choices[i][0];
        choices[i][0] = cum;
    }
    return choices;
}
varargs mixed get_random_npcs(mixed *choices) {
    int i;
    int chance;
    if (!choices)
        choices = previous_object()->query_npcs();
    if (!arrayp(choices) || !sizeof(choices))
        return 0;
    chance = random(choices[<1][0]);
    for (i = 0; i < sizeof( choices ); i++) {
        if ( choices[ i ][ 0 ] > chance ) {
            return data_get_group( choices[ i ][ 1 ]);
        }
    }
    return 0;
}