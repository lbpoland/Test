#define DEBUG 1;
#include <parse_command.h>
#include <obj_parser.h>
#define POSITION_SIZE 2
#define POSITION_DESC 0
#define POSITION_MULT 1
private mixed *_lng;
private string *_shrt;
private string *_adjs;
private string *_plu;
private string *_name;
#ifdef DEBUG
private string _creator_room;
#endif
private mapping _verb;
private mapping _plural;
private mapping _other_things;
private mapping _pattern;
private int *_cur_desc;
private mapping _gather;
private mapping _position_stuff;
private mapping _count;
void init() {
    string name;
    mixed rest;
    foreach (name, rest in _other_things) {
            this_player()->add_command(name, this_object(), _pattern[name]);
    }
}
#ifdef DEBUG
string query_creator_room() { return _creator_room; }
void print_stuff() {
    printf("lng = %O\nshrt = %O\nadjs = %O\nplu = %O\nname = %O\n" +
      "verb = %O\nplural = %O\nother_things = %O\npattern = %O\n" +
      "cur_desc = %O\ngather = %O\n", _lng, _shrt, _adjs, _plu, _name, _verb,
      _plural, _other_things, _pattern, _cur_desc, _gather);
}
#endif
void create() {
#ifdef DEBUG
    _creator_room = file_name(previous_object());
#endif
    _adjs = ({ });
    _lng = ({ "" });
    _shrt = ({ "" });
    _gather = ([ ]);
    _plu = ({ });
    _name = ({ });
    _verb = ([ ]);
    _plural = ([ ]);
    _pattern = ([ ]);
    _cur_desc = ({ });
    _count = ([ ]);
    _other_things = ([ "smell" : 0, "taste" : 0, "read" : 0 ]);
}
int query_visible( object thing ) { return 1; }
string hide_invis_string() { return ""; }
string *query_short_array() {
    string *ret;
    int i;
    ret = ({ });
    foreach (i in _cur_desc) {
        ret += ({ _shrt[i] });
    }
    return ret;
}
string short() {
    return query_multiple_short(query_short_array());
}
string pretty_short() {
    string *ret;
    ret = query_short_array();
    if (sizeof(ret)) {
        return query_multiple_short(ret);
    } else {
        return "something";
    }
}
string a_short() {
    return implode(map(query_short_array(),
        (: "$mirror_short:" + add_a( $1 ) + "$" :)), "");
}
string the_short() {
    return implode(map(query_short_array(),
        (: "$mirror_short:the " +  $1 + "$" :)), "");
}
string one_short() {
    return implode(map(query_short_array(),
        (: "$mirror_short:the " + $1 + "$" :)), "");
}
string poss_short() {
    return implode(map(query_short_array(),
        (: "$mirror_short:the " + $1 + "$" :)), "");
}
string query_read_short() {
    return "$name$";
}
string query_plural() {
    string *ret;
    int i;
    ret = ({ });
    foreach (i in _cur_desc) {
        ret += ({ pluralize(_shrt[i]) });
    }
    return query_multiple_short(ret);
}
string pretty_plural() {
    int i;
    foreach (i in _cur_desc) {
        return pluralize(_shrt[i]);
    }
    return 0;
}
string long( string name, int dark ) {
    int i;
    string *ret;
    ret = ({ });
    foreach (i in _cur_desc) {
        if ( !_lng[ i ] ) {
            continue;
        }
        if (functionp(_lng[ i ])) {
            ret += ({ evaluate(_lng[ i ]) });
        } else {
            ret += ({ _lng[ i ] });
        }
    }
    if ( !sizeof( ret ) ) {
        return "You don't think that the "+name+" is here.\n";
    }
    return implode( evaluate(ret), "\n")+"\n";
}
int *query_cur_desc() { return _cur_desc; }
mapping query_verbs() { return _verb; }
mapping query_plurals() { return _plural; }
string *query_lng() { return _lng; }
string *query_shrt() { return _shrt; }
mixed *query_gather() {
    mixed *g = ({ });
    int i;
    foreach (i in _cur_desc) {
        if (_gather[i]) {
            g += ({ _gather[i] });
        }
    }
    return g;
}
int drop() { return 1; }
int get() { return 1; }
int query_item(string str) { return _verb[str]; }
private void setup_bits_for_item(int index, mixed bits) {
    int i;
    string str;
    mixed pat;
    if (!pointerp(bits)) {
        _lng[index] = bits;
        return ;
    }
    _lng[index] = "You see nothing special.\n";
    for (i = 0; i < sizeof(bits); i += 2) {
        if ((arrayp( bits[i + 1] ) && sizeof( bits[i + 1] ) == 3) ||
          (sizeof( bits[i + 1] ) == 2 && functionp( bits[i + 1][0] ))) {
            pat = bits[i + 1][<1];
            if (!arrayp(pat)) {
                pat = ({ pat });
            }
        }
        else {
            pat = ({ "<direct:object>" });
        }
        if (!pointerp(bits[i])) {
            bits[i] = ({ bits[i] });
        }
        foreach (str in bits[i]) {
            if (str == "long") {
                _lng[index] = bits[i+1];
            } else if (str == "gather") {
                _gather[index] = bits[i+1];
            } else if (str == "item_count")  {
               if (!_count[index])  _count[index] = bits[i + 1];
            } else if (str == "position" ||
              str == "position multiple") {
                if (!_position_stuff)
                    _position_stuff = ([ ]);
                if (!_position_stuff[index]) {
                    _position_stuff[index] = allocate(POSITION_SIZE);
                }
                if (str == "position") {
                    _position_stuff[index][POSITION_DESC] = bits[i + 1];
                } else {
                    _position_stuff[index][POSITION_MULT] = bits[i + 1];
                }
            } else if (!_other_things[str]) {
                _pattern[str] = pat;
                _other_things[str] = ([ index : bits[i+1] ]);
            } else {
                if (member_array(pat, _pattern[str]) == -1) {
                    _pattern[str] += pat - (string *)_pattern[str];
                }
                _other_things[str][index]   = bits[i+1];
            }
        }
    }
}
private void remove_bits_for_item(int index) {
    string str;
    string adj;
    mixed value;
    int frog;
    int bing;
    int i;
    int j;
    map_delete(_gather, index);
    foreach (frog, bing in _gather) {
        if (frog > index) {
            map_delete(_gather, frog);
            _gather[frog - 1] = bing;
        }
    }
    if (_position_stuff) {
        map_delete(_position_stuff, index);
        foreach (frog, bing in _position_stuff) {
            if (frog > index) {
                map_delete(_position_stuff, frog);
                _position_stuff[frog - 1] = bing;
            }
        }
    }
    foreach (str, value in _other_things) {
        if (value) {
            map_delete(value, index);
            if (!sizeof(value)) {
                map_delete(_other_things, str);
                map_delete(_pattern, str);
            } else {
                foreach (frog, bing in value) {
                    if (frog > index) {
                        map_delete(value, frog);
                        value[frog - 1] = bing;
                    }
                }
            }
        }
    }
    foreach (str, value in _verb) {
        for (i = 0; i < sizeof(value); i += 2) {
            if (value[i + 1] > index) {
                value[i + 1] -= 1;
            } else if (value[i + 1] == index) {
                foreach (adj in value[i]) {
                    j = member_array(adj, _adjs);
                    if (j != -1) {
                        _adjs = _adjs[0..i - 1] + _adjs[i + 1..];
                    }
                }
                value = value[0.. i - 1] + value[i + 2..];
                i -= 2;
                j = member_array(str, _name);
                if (j != -1) {
                    _name = _name[0..j - 1] + _name[j + 1..];
                }
            }
        }
        _verb[str] = value;
    }
    foreach (str, value in _plural) {
        for (i = 0; i < sizeof(value); i += 2) {
            if (value[i + 1] > index) {
                value[i + 1] -= 1;
            } else if (value[i + 1] == index) {
                value = value[0.. i - 1] + value[i + 2..];
                i -= 2;
            }
        }
        _plural[str] = value;
    }
}
private void add_name_reference(int index, string name, int no_plural) {
    string *bits;
    string plural;
    string s;
    bits = explode(name, " ");
    s = bits[<1];
    if (member_array(s, _name) == -1) {
        _name += ({ s });
    }
    if (!_verb[s]) {
        _verb[s] = ({ bits[0..<2], index });
    } else {
        _verb[s] += ({ bits[0..<2], index });
    }
    if (!no_plural) {
        plural = pluralize(s);
        if (member_array(plural, _plu) == -1) {
            _plu += ({ plural });
        }
        if (!_plural[plural]) {
            _plural[plural] = ({ bits[0..<2], index });
        } else {
            _plural[plural] += ({ bits[0..<2], index });
        }
    }
    _adjs += bits[0..<2];
}
int setup_item(mixed nam, mixed long, int no_plural) {
    int index;
    string str;
    index = sizeof(_lng);
    if (pointerp(nam)) {
        if (sizeof(nam) > 0) {
            _shrt += ({ nam[0] });
            if (no_plural) {
                _plu += ({ "no plural" });
            } else {
                _plu += ({ pluralize(nam[0]) });
            }
        }
        foreach (str in nam) {
            add_name_reference(index, str, no_plural);
        }
    } else {
        _shrt += ({ nam });
        if (no_plural) {
            _plu += ({ "no plural" });
        } else {
            _plu += ({ pluralize(nam) });
        }
        add_name_reference(index, nam, no_plural);
    }
    _lng += ({ 0 });
    setup_bits_for_item(index, long);
    return index;
}
int modify_item_by_index(int index, mixed long) {
    if (index >= sizeof(_lng)) {
        return 0;
    }
    setup_bits_for_item(index, long);
    return 1;
}
int modify_item_by_name(string str, mixed long) {
    int index;
    index = member_array(str, _shrt);
    if (index == -1) {
        return 0;
    }
    return modify_item_by_index(index, long);
}
int modify_item(mixed str, mixed long) {
    if (stringp(str)) {
        return modify_item_by_name(str, long);
    }
    if (intp(str)) {
        return modify_item_by_index(str, long);
    }
    return 0;
}
int remove_item_by_index(int index) {
    if (index >= sizeof(_lng)) {
        return 0;
    }
    _shrt = _shrt[0..index - 1] + _shrt[index + 1..];
    _adjs = _adjs[0..index - 1] + _adjs[index + 1..];
    _lng = _lng[0..index - 1] + _lng[index + 1..];
    _plu = _plu[0..index - 1] + _plu[index + 1..];
    remove_bits_for_item(index);
}
int remove_item_by_name(string str) {
    int index;
    index = member_array(str, _shrt);
    if (index == -1) {
        return 0;
    }
    return remove_item_by_index(index);
}
int remove_item(mixed str) {
    if (stringp(str)) {
        return remove_item_by_name(str);
    }
    if (intp(str)) {
        return remove_item_by_index(str);
    }
    return 0;
}
string *parse_command_id_list() { return _name; }
string *parse_command_plural_id_list() { return _plu; }
string *parse_command_adjectiv_id_list() { return _adjs; }
object query_parse_id(mixed *arr)
{
    string *bits;
    mixed stuff;
    int i, j, match, all_match;
    bits = explode(arr[P_STR], " ");
    bits -= ({ "a", "an", "the" });
    if (arr[P_THING] == 0)
    {
        stuff = _plural[bits[<1]];
        if (!stuff) {
            stuff = _verb[bits[<1]];
            if (!stuff) {
                return 0;
            }
        }
        _cur_desc = ({ });
        all_match = 0;
        for (j = 0; j < sizeof(stuff); j += 2) {
            match = 1;
            for (i = 0; i < sizeof(bits) - 1; i++) {
                if (member_array(bits[i], stuff[j]) == -1) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                all_match = 1;
                if (member_array(stuff[j+1], _cur_desc) == -1) {
                    _cur_desc += ({ stuff[j+1] });
                }
            }
        }
        if (all_match) {
            return this_object();
        } else {
            return 0;
        }
    }
    if (arr[P_THING] < 0) {
        stuff = _verb[bits[<1]];
        if (!stuff) {
            return 0;
        }
        for (j = 0; j < sizeof(stuff); j += 2) {
            match = 1;
            for (i = 0; i < sizeof(bits) - 1; i++) {
                if (member_array(bits[i], stuff[j]) == -1) {
                    match = 0;
                    break;
                }
            }
            if (++arr[P_THING] != 0) {
                continue;
            }
            if (match) {
                _cur_desc = ({ stuff[j+1] });
                arr[P_THING] = -10321;
                return this_object();
            }
        }
        return 0;
    }
    stuff = _plural[bits[<1]];
    if (!stuff) {
        stuff = _verb[bits[<1]];
        if (!stuff) {
            return 0;
        }
    }
    _cur_desc = ({ });
    for (j = 0; j < sizeof(stuff); j += 2) {
        match = 1;
        for (i=0;i<sizeof(bits)-1;i++) {
            if ( member_array( bits[ i ], stuff[ j ] ) == -1 ) {
                match = 0;
                break;
            }
        }
        if (match) {
            if (member_array(stuff[j+1], _cur_desc) == -1) {
                _cur_desc += ({ stuff[j+1] });
            }
            arr[P_THING]--;
            if (arr[P_THING] <= 0) {
                arr[P_THING] = -10786;
                return this_object();
            }
        }
    }
    return 0;
}
mixed* parse_match_object(string* input,
                          object player,
                          class obj_match_context context) {
   int *stuff;
   mixed *plural;
   mixed *sing;
   string *its, *thems;
   string item;
   int i;
   int j;
   int match;
   int ret;
   if (input[<1] == "here" && sizeof(input) > 1) {
      input = input[0..<2];
   }
   if ( this_object() == context->it &&
        input[<1] == "it" ) {
      sing = ({ });
      its = map(_cur_desc, (: explode(_shrt[$1], " ")[<1] :));
      foreach( item in its ) {
          if ( arrayp( _verb[ item ] ) ) {
             sing += ({ ({ item }), _verb[ item ][ 1 ] });
          }
      }
      plural = ({ });
   } else if( input[<1] == "them" &&
              context->plural &&
              member_array( this_object(), context->plural ) != -1) {
      plural = ({ });
      thems = map(_cur_desc, (: explode(_shrt[$1], " ")[<1] :));
      foreach( item in thems ) {
          if ( arrayp( _verb[ item ] ) ) {
             plural += ({ ({ item }), _verb[ item ][ 1 ] });
          }
      }
      sing = ({ });
   } else {
      plural = _plural[input[<1]];
      sing = _verb[input[<1]];
   }
   if (!sizeof(plural) && !sizeof(sing)) {
      return 0;
   }
   stuff = ({ });
   for (i = 0; i < sizeof(sing); i += 2) {
      match = 1;
      for (j = 0; j < sizeof(input) - 1; j++) {
         if (member_array(input[j], sing[i]) == -1) {
            match = 0;
            break;
         }
      }
      if (match) {
         if (member_array(sing[i+1], stuff) == -1) {
            stuff += ({ sing[i+1] });
            ret |= OBJ_PARSER_MATCH_SINGULAR;
         }
      }
   }
   for (i = 0; i < sizeof(plural); i += 2) {
      match = 1;
      for (j = 0; j < sizeof(input) - 1; j++) {
         if (member_array(input[j], plural[i]) == -1) {
            match = 0;
            break;
         }
      }
      if (match) {
         if (member_array(plural[i+1], stuff) == -1) {
            stuff += ({ plural[i+1] });
            ret |= OBJ_PARSER_MATCH_PLURAL;
         }
      }
   }
   if (sizeof(stuff)) {
       if (context->ordinal) {
          if (context->ordinal > sizeof(stuff)) {
             context->ordinal -= sizeof(stuff);
             return 0;
          }
          context->ignore_rest = 1;
          context->ordinal--;
          _cur_desc = stuff[context->ordinal..context->ordinal];
       } else if (context->number_included) {
          _cur_desc = stuff[0..context->number_included];
          context->number_included -= sizeof(stuff);
          if (context->number_included <= 0) {
             context->ignore_rest = 1;
          }
       } else if (ret & OBJ_PARSER_MATCH_PLURAL) {
          _cur_desc = stuff;
       } else {
          _cur_desc = stuff[0..0];
       }
       return ({ ret, ({ this_object() }) });
   } else {
      return 0;
   }
}
void dest_me() {
    destruct(this_object());
    return ;
}
void dwep() {
    destruct(this_object());
    return ;
}
int move() { return 1; }
int command_control(string command, object *indir, string id_arg,
  string ii_arg, string *args, string pattern) {
    int desc, size, num;
    mixed temp;
    if (!_other_things[command]) {
        return 0;
    }
    size = sizeof(_cur_desc);
    foreach (desc in _cur_desc) {
        temp = _other_things[command][desc];
        if (arrayp(temp)) {
            if (sizeof(temp) == 3 || (sizeof(temp) == 2 && !functionp(temp[0]))) {
                num += call_other(temp[0], temp[1], command, indir, id_arg,
                  ii_arg, args, pattern);
            }
            else {
                if (sizeof(temp) == 2 && functionp(temp[0])) {
                        num += evaluate(temp[0], command, indir, id_arg, ii_arg,
                            args, pattern);
                }
            }
        }
        else {
            if (functionp(temp)) {
                temp = evaluate(temp, command, indir, id_arg, ii_arg, args,
                    pattern);
            }
            if (stringp(temp)) {
                write(temp);
                num++;
                add_succeeded_mess(({ "", "$N $V $D.\n" }));
            }
            else {
                if ( intp( temp ) ) {
                    num += temp;
                }
            }
        }
    }
    return num;
}
mapping query_other_things() { return _other_things; }
mapping query_pattern() { return _pattern; }
string query_position_string(string pos) {
    int i;
    if (!_position_stuff) {
        return 0;
    }
    for (i = 0; i < sizeof(_cur_desc); i++) {
        if (_position_stuff[_cur_desc[i]]) {
            return _position_stuff[_cur_desc[i]][POSITION_DESC];
        }
    }
    return 0;
}
int query_position_multiple(string pos) {
    int i;
    if (!_position_stuff) {
        return 0;
    }
    for (i = 0; i < sizeof(_cur_desc); i++) {
        if (_position_stuff[_cur_desc[i]]) {
            return _position_stuff[_cur_desc[i]][POSITION_MULT];
        }
    }
    return 0;
}
mapping query_position_stuff() { return _position_stuff; }
int query_count()  {
   int i;
   int ret = 0;
   foreach (i in _cur_desc)  {
      ret += evaluate(_count[i]);
   }
   return ret;
}