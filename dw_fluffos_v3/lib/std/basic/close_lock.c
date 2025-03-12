#include <move_failures.h>
#include <tasks.h>
#include <clothing.h>
#define MAX_INVENT 40
#define C_CLOSED 1
#define C_TRANS 2
#define C_OPAQUE 1
#define LOCKED        1
#define CLOSED        2
#define CLOSED_LOCKED 3
#define SKILL "covert.manipulation.sleight-of-hand"
#define STEALTH_NONE        0
#define STEALTH_FAILED      1
#define STEALTH_SUCCEEDED   2
#define TP this_player()
#define TO this_object()
int do_open();
int do_close();
int do_lock(object *keys);
int do_unlock(object *keys);
private int _locked;
private int _closed;
private string _pick_skill;
private nosave int _stuck;
private nosave int _trans;
private nosave int _difficulty;
private nosave int _autolock;
private nosave string _trap_open_func;
private nosave string _trap_lock_func;
private nosave object _trap_open_ob;
private nosave object _trap_lock_ob;
private nosave mixed _key;
void create() {
  _difficulty = 5;
  _pick_skill = "covert.lockpick.doors";
}
void set_open() {
    if (!_closed)
        return;
    _closed = 0;
    _locked = 0;
    if (environment()) {
      event( ({ environment(), TO, }), "open", TP);
    } else if (TO->query_my_room()) {
      event( ({ TO->query_my_room(), TO, }), "open", TP);
    }
}
void set_closed() {
    if (_closed)
        return;
    _closed = 1;
    if (environment()) {
      event( ({ environment(), TO, }), "close", TP);
    } else if (TO->query_my_room()) {
      event( ({ TO->query_my_room(), TO, }), "close", TP);
    }
}
int query_closed() {
  return _closed;
}
int query_open() {
  return !_closed;
}
void set_locked() {
    if (!_closed)
        return;
    if (_locked)
        return;
    _locked = 1;
    if (environment()) {
        event( ({ environment(), TO, }), "lock", TP);
    } else if (TO->query_my_room()) {
        event( ({ TO->query_my_room(), TO, }), "lock", TP);
    }
}
void set_unlocked() {
    if (!_locked)
        return;
    _locked = 0;
    if (environment()) {
        event( ({ environment(), TO, }), "unlock", TP);
    } else if (TO->query_my_room()) {
        event( ({ TO->query_my_room(), TO, }), "unlock", TP);
    }
}
int query_locked() {
  return _locked;
}
int query_unlocked() {
  return !_locked;
}
void set_autolock(int number) { _autolock = number; }
int query_autolock() { return _autolock; }
void set_key(mixed val) {
    if (!stringp(val) && !functionp(val))
        return;
    _key = val;
}
string query_key() {
    if (stringp(_key))
        return _key;
    if (functionp(_key))
        return evaluate(_key);
    return 0;
}
void set_pick_skill(string str) {
  _pick_skill = str;
}
string query_pick_skill() {
  return _pick_skill;
}
void set_difficulty(int i) {
  _difficulty = i;
}
int query_difficulty() {
  return _difficulty;
}
void set_stuck(int i) {
  _stuck = i;
}
int query_stuck() {
  return _stuck;
}
void set_transparent() {
  _trans = C_TRANS;
}
void reset_transparent() {
  _trans = 0;
}
int query_transparent() {
  return _trans;
}
void set_open_trap(object ob, string func) {
  _trap_open_func =  func;
  _trap_open_ob = ob;
}
string query_open_trap_func() {
  return _trap_open_func;
}
object query_open_trap_ob() {
  return _trap_open_ob;
}
void set_lock_trap(object ob, string func) {
  _trap_lock_func = func;
  _trap_lock_ob = ob;
}
string query_lock_trap_func() {
  return _trap_lock_func;
}
object query_lock_trap_ob() {
  return _trap_lock_ob;
}
int query_closed_locked_status() {
    if (_closed && _locked) {
        return CLOSED_LOCKED;
    }
    if (_closed) {
        return CLOSED;
    }
    if (_locked) {
        return LOCKED;
    }
    return 0;
}
void add_close_lock_commands(object player) {
  if(!player)
    return;
    player->add_command("open", TO,
        "<direct:object:me-here>",
        (: do_open() :) );
    player->add_command("close", TO,
        "<direct:object:me-here>",
        (: do_close() :) );
    if (TO->query_key()) {
        player->add_command("lock", TO,
            "<direct:object:me-here>",
            (: do_lock(0) :) );
        player->add_command("lock", TO,
            "<direct:object:me-here> with <indirect:object:me>",
            (: do_lock($1) :) );
        player->add_command("unlock", TO,
            "<direct:object:me-here>",
            (: do_unlock(0) :) );
        player->add_command("unlock", TO,
            "<direct:object:me-here> with <indirect:object:me>",
            (: do_unlock($1) :) );
    }
}
void init() {
    add_close_lock_commands(this_player());
}
string short_status() {
    return "";
}
string long_status() {
    if (TO->query_stuck())
        return "";
    switch (query_closed_locked_status()) {
        case CLOSED_LOCKED:
            return "It is closed and locked.\n";
        case CLOSED:
            return "It is closed.\n";
        default:
            return "It is open.\n";
    }
}
int check_stealth() {
    mapping hide_invis;
    int hiding, sneaking, difficulty, light, my_light, items_blocking;
    hide_invis = (mapping) TP->query_hide_invis();
    hiding = undefinedp(hide_invis["hiding"]) ? 0 : 1;
    sneaking = TP->query_sneak_level() ? 1 : 0;
    if (!hiding && !sneaking)
        return STEALTH_NONE;
    my_light = TP->query_light();
    light = environment(TP)->query_light();
    difficulty = light + (4 * my_light) / (light + 1);
    items_blocking = sizeof(CLOTHING_HANDLER->query_items_blocking(TO, TP));
    if (items_blocking) {
        difficulty += 50 * items_blocking;
    }
    debug_printf( "Difficulty = %d.\n Skill = %s\n Bonus = %d\n",
                  difficulty, SKILL, TP->query_skill_bonus( SKILL ) );
    switch (TASKER->perform_task(TP, SKILL, difficulty, TM_FREE)) {
        case AWARD:
            write("%^YELLOW%^" + ({
                "You discover something that lets your fingers move more nimbly.",
                "You find yourself capable of deceiving the eye with greater ease "
                "than before.",
                "You realise how to deceive the eye more effectively."
                })[ random(3) ] + "%^RESET%^\n" );
        case SUCCEED :
            return STEALTH_SUCCEEDED;
        default :
            return STEALTH_FAILED;
    }
}
int do_unlock(object *keys) {
    object *gkeys = ({ });
    string key = TO->query_key();
    int inv = 0;
    if (!_locked) {
        TP->add_failed_mess(TO,
            "$D $V$0=isn't,aren't$V$ locked.\n",
            ({ }) );
        return 0;
    }
    if (_stuck) {
        TP->add_failed_mess(TO,
            "$D $V$0=is,are$V$ stuck.\n",
            ({ }) );
        return 0;
    }
    if (!_closed) {
        TP->add_failed_mess(TO,
            "$D $V$0=isn't,aren't$V$ closed.\n",
            ({ }) );
        return 0;
    }
    if (!key) {
        TP->add_failed_mess(TO,
            "$D $V$0=doesn't,don't$V$ have a lock.\n",
            ({ }) );
        return 0;
    }
    if (key != "by hand") {
        if (!keys || !sizeof(keys)) {
            keys = all_inventory(TP);
            inv = 1;
        }
        gkeys = filter(keys, (: $1->query_property( $(key) ) :) );
        if (!sizeof(gkeys)) {
            if (!inv) {
                TP->add_failed_mess(TO,
                    "You cannot $V $D with $I.\n",
                        keys);
                return 0;
            }
            TP->add_failed_mess(TO,
                "You cannot $V $D.\n",
                ({ }) );
            return 0;
        }
        gkeys[0]->use_key(TO);
    }
    if (_trap_lock_func && _trap_lock_ob) {
        if (!call_other(_trap_lock_ob, _trap_lock_func, "unlock", TO, TP)) {
            return 0;
        }
    }
    set_unlocked();
    switch (check_stealth()) {
        case STEALTH_SUCCEEDED:
          if (sizeof (gkeys)) {
            TP->add_succeeded_mess(TO, ({
                "$N $V $D with $I, managing to stay unnoticed.\n",
                "", }),
                ({ ( gkeys[0] ) }) );
          } else {
            TP->add_succeeded_mess(TO, ({
                "$N $V $D, managing to stay unnoticed.\n",
                "", }),
                ({ }) );
          }
            break;
        case STEALTH_FAILED:
            TP->add_succeeded_mess(TO,
                "$N unsuccessfully tr$y to " + query_verb() + " $D while "
                "staying unnoticed.\n", ({ }) );
            break;
        default:
            if (sizeof (gkeys)) {
              TP->add_succeeded_mess(TO,
                 "$N $V $D with $I.\n", ({ gkeys[0] }) );
            } else {
              TP->add_succeeded_mess (TO, "$N $V $D.\n", ({ }));
            }
            break;
    }
    return 1;
}
int do_lock(object *keys) {
    object *gkeys = ({ });
    string key = TO->query_key();
    int inv = 0;
    if (_locked) {
        TP->add_failed_mess(TO,
            "$D $V$0=is,are$V$ already locked.\n",
            ({ }) );
        return 0;
    }
    if (_stuck) {
        TP->add_failed_mess(TO,
            "$D $V$0=is,are$V$ stuck.\n",
            ({ }) );
        return 0;
    }
    if (!_closed && !do_close()) {
        TP->add_failed_mess(TO,
            "$D $V$0=isn't,aren't$V$ closed.\n",
            ({ }) );
        return 0;
    }
    if (!key) {
        TP->add_failed_mess(TO,
            "$D $V$0=doesn't,don't$V$ have a lock.\n",
            ({ }) );
        return 0;
    }
    if (key != "by hand") {
        if (!keys || !sizeof(keys)) {
            keys = all_inventory(TP);
            inv = 1;
        }
        gkeys = filter(keys, (: $1->query_property( $(key) ) :) );
        if (!sizeof(gkeys)) {
            if (!inv) {
                TP->add_failed_mess(TO, "You cannot lock $D with $I.\n", keys);
                return 0;
            }
            TP->add_failed_mess(TO, "You cannot lock $D.\n", ({ }) );
            return 0;
        }
        gkeys[0]->use_key(TO);
    }
    if (_trap_lock_func && _trap_lock_ob) {
        if (!call_other(_trap_lock_ob, _trap_lock_func, "lock", TO, TP)) {
            return 0;
        }
    }
    set_locked();
    switch (check_stealth()) {
    case STEALTH_SUCCEEDED:
          if (sizeof (gkeys)) {
            TP->add_succeeded_mess(TO, ({
                "$N lock$s $D with $I, managing to stay unnoticed.\n",
                "", }),
                ({ ( gkeys[0] ) }) );
          } else {
            TP->add_succeeded_mess(TO, ({
                "$N lock$s $D, managing to stay unnoticed.\n",
                "", }),
                ({ }) );
          }
        break;
      case STEALTH_FAILED:
        TP->add_succeeded_mess(TO, "$N unsuccessfully tr$y to " +
                               "lock $D while staying unnoticed.\n",
                               ({ }) );
        break;
      default:
        if (sizeof (gkeys)) {
          TP->add_succeeded_mess(TO,
                                 "$N lock$s $D with $I.\n", ({ gkeys[0] }) );
        } else {
          TP->add_succeeded_mess (TO, "$N lock$s $D.\n", ({ }));
        }
        break;
    }
    return 1;
}
int pick_lock(object player) {
    if (_trap_lock_ob
     && !call_other(_trap_lock_ob, _trap_lock_func, "pick", TO, player)) {
        return 0;
    }
    set_locked();
    return 1;
}
int pick_unlock(object player) {
    if (_trap_lock_ob
     && !call_other(_trap_lock_ob, _trap_lock_func, "pick", TO, player)) {
        return 0;
    }
    set_unlocked();
    return 1;
}
int do_open() {
    if (!_closed) {
        TP->add_failed_mess(TO,
            "$D $V$0=is,are$V$ already open.\n",
            ({ }) );
        return 0;
    }
    if (_stuck) {
        TP->add_failed_mess(TO,
            "$D $V$0=is,are$V$ stuck.\n",
            ({ }) );
        return 0;
    }
    if (_locked && !do_unlock(0)) {
        TP->add_failed_mess(TO,
            "$D $V$0=is,are$V$ locked.\n",
            ({ }) );
        return 0;
    }
    if (_trap_open_func && _trap_open_ob) {
        if (!call_other(_trap_open_ob, _trap_open_func, "open", TO, TP)) {
            return 0;
        }
    }
    set_open();
    if (!TO->query_door_name()) {
        switch (check_stealth()) {
            case STEALTH_SUCCEEDED:
                TP->add_succeeded_mess(TO, ({
                    "$N $V $D, managing to stay unnoticed.\n",
                    "", }),
                    ({ }) );
                break;
            case STEALTH_FAILED:
                TP->add_succeeded_mess(TO,
                    "$N unsuccessfully tr$y to " + query_verb() + " $D while "
                    "staying unnoticed.\n", ({ }) );
                break;
            default:
                TP->add_succeeded_mess(TO,
                    "$N $V $D.\n",
                    ({ }) );
                break;
        }
    }
    return 1;
}
int do_close() {
    if (_closed) {
        TP->add_failed_mess(TO,
            "$D $V$0=is,are$V$ already closed.\n",
            ({ }) );
        return 0;
    }
    if (_stuck) {
        TP->add_failed_mess(TO,
            "$D $V$0=is,are$V$ stuck.\n",
            ({ }) );
        return 0;
    }
    if (_trap_open_func && _trap_open_ob) {
        if (!call_other(_trap_open_ob, _trap_open_func, "close", TO,TP)) {
            return 0;
        }
    }
    set_closed();
    if (_autolock)
        set_locked();
    if (!TO->query_door_name()) {
        switch (check_stealth()) {
            case STEALTH_SUCCEEDED:
                TP->add_succeeded_mess(TO, ({
                    "$N $V $D, managing to stay unnoticed.\n",
                    "", }),
                    ({ }) );
                break;
            case STEALTH_FAILED:
                TP->add_succeeded_mess(TO,
                    "$N unsuccessfully tr$y to " + query_verb() + " $D while "
                    "staying unnoticed.\n", ({ }) );
                break;
            default:
                TP->add_succeeded_mess(TO,
                    "$N $V $D.\n",
                    ({ }) );
                break;
        }
    }
    return 1;
}
string *parse_command_adjectiv_id_list() {
    switch( query_closed_locked_status() ) {
        case CLOSED_LOCKED:
            return ({ "closed", "locked" });
        case CLOSED:
            return ({ "closed", "unlocked" });
        case LOCKED:
            return ({ "open", "locked" });
        default:
            return ({ "open", "unlocked" });
    }
}
mixed *stats() {
  return ({
    ({"closed", query_closed()}),
    ({"transparent", query_transparent()}),
    ({"key", query_key()}),
    ({"difficulty", query_difficulty()}),
    ({"locked", query_locked()}),
    ({"stuck", query_stuck()}),
    ({"open trapped", _trap_open_func != 0}),
    ({"lock trapped", _trap_lock_func != 0}),
    ({"pick skill", query_pick_skill()}),});
}