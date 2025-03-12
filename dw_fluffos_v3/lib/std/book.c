inherit "/std/object";
#include <move_failures.h>
#include <player.h>
private mixed *_pages;
private string _default_page_object;
private object _def_p_obj;
private int _open_page;
private int _book_num;
private int _ignore_open_page;
private int _ignore_saved_pages;
private nosave object _player;
private nosave int _num_torn_out = -1;
protected int do_open(int page);
protected int do_tear(int number);
protected int do_turn(int number);
protected int do_close();
object create_default_page_object();
void create() {
  _pages = ({ });
  _default_page_object = "/obj/misc/paper";
  load_object(_default_page_object);
  _def_p_obj = find_object(_default_page_object);
  ::create();
  add_help_file("book");
}
int query_book() { return 1; }
int query_weight() {
   if (!_def_p_obj) {
      load_object(_default_page_object);
      _def_p_obj = find_object(_default_page_object);
   }
   return ::query_weight() +
          sizeof(filter(_pages, (: objectp($1) :))) * _def_p_obj->query_weight();
}
void init() {
  add_command("open", "<direct:object>", (: do_open(1) :));
  add_command("open", "<direct:object> to [page] <number>",
              (: do_open($4[1]) :));
  add_command("tear", "page from <direct:object>", (: do_tear(1) :));
  add_command("tear", "[all] pages from <direct:object>", (: do_tear(0) :));
  add_command("tear", "<number> [of] pages from <direct:object>",
              (: do_tear($4[0]) :));
  add_command("rip", "page from <direct:object>", (: do_tear(1) :));
  add_command("rip", "<number> [of] pages from <direct:object>",
              (: do_tear($4[0]) :));
  add_command("rip", "[all] pages from <direct:object>", (: do_tear(0) :));
  add_command("turn", "[a|1] page of <direct:object>", (: do_turn(1) :));
  add_command("turn", "<number> pages of <direct:object>",
              (: do_turn($4[0]) :));
  add_command("turn", "<direct:object> to [page] <number>",
              (: do_open($4[1]) :) );
  add_command("turn", "to page <number> of <direct:object>",
              (: do_open($4[0]) :) );
  add_command("close", "<direct:object>", (: do_close() :));
}
int add_weight( int number ) {
   adjust_weight( number );
   return 1;
}
int test_add(object ob, int flag) {
  return (object)ob->query_property("my book") == this_object();
}
int test_remove( object ob, int flag, mixed dest ) {
  return ob->query_property("my book") != this_object();
}
void set_no_pages(int no) {
  int i;
  int siz;
  siz = sizeof(_pages);
  if (no < siz) {
    _pages = _pages[0..no-1];
    if (_open_page >= no) {
      _open_page = no;
    }
  } else {
    _pages = _pages + allocate(no-siz);
    for (i=siz;i<no;i++) {
      _pages[i] = ({ });
    }
  }
}
mixed *query_pages() { return _pages; }
void set_open_page(int i) {
  if (i < 0 || i == _open_page) {
     return ;
  }
  if (!_open_page && i) {
    add_alias("page");
    add_plural("pages");
  }
  if (i > sizeof(_pages)) {
    _open_page = sizeof(_pages);
  } else {
    _open_page = i;
  }
  if (!_open_page) {
    remove_alias("page");
    remove_plural("pages");
  }
}
int query_open_page() {
   return _open_page;
}
int is_current_page_torn_out() {
   if (!_open_page) {
      return 0;
   }
   if ( !_pages ) {
      return 0;
   }
   if (!_pages[_open_page-1]) {
      return 1;
   }
   return 0;
}
int is_page_torn_out(int page) {
   if (page < 1 || page > sizeof(_pages)) {
      return 0;
   }
   if (!_pages[page - 1]) {
      return 1;
   }
   return 0;
}
object query_current_page() {
   int i;
   if (!_open_page) {
      return this_object();
   }
   for (i = _open_page - 1; i < sizeof(_pages); i++) {
     if (_pages[i]) {
       if (!_def_p_obj) {
         load_object(_default_page_object);
         _def_p_obj = find_object(_default_page_object);
       }
       return _def_p_obj;
     }
   }
   return 0;
}
object query_current_page_clone() {
  return this_object();
}
int is_default_page(int num) {
   if (num > 0 && num <= sizeof(_pages)) {
      if (_pages[num - 1] &&
          !objectp(_pages[num - 1])) {
         return 1;
      }
   }
   return 0;
}
object query_selected_page(int num) {
   if (!intp(num) || num <= 0 || num > sizeof(_pages)) {
      return 0;
   }
   if (_pages[num - 1]) {
      if (objectp(_pages[num - 1])) {
         return _pages[num - 1];
      } else {
         if (!_def_p_obj) {
            load_object(_default_page_object);
            _def_p_obj = find_object(_default_page_object);
         }
         return _def_p_obj;
      }
   }
   return 0;
}
object query_selected_page_clone(int num) {
  return this_object();
}
object tear_current_page_out(object dest) {
  object page;
  if (is_current_page_torn_out()) {
    return 0;
  }
  if (_pages[_open_page-1]) {
    page = clone_object(_default_page_object);
    page->add_alias("page");
    page->add_plural("pages");
    if(_pages[_open_page-1] != 1)
      page->set_read_mess(_pages[_open_page-1]);
   }
  if (page && page->move(dest) == MOVE_OK) {
    _pages[_open_page-1] = 0;
    return page;
  }
  return 0;
}
int add_page_after(object page, int after) {
   if (after < 0 || after > sizeof(_pages) + 1 ||
       !objectp(page) || !intp(after)) {
      return 0;
   }
   _pages = _pages[0..after - 1] + page->query_read_mess() + _pages[after..];
   page->move("/room/rubbish");
   return 1;
}
int replace_page_with(object page, int num) {
   if (num < 1 || num > sizeof(_pages) ||
       !objectp(page) || !intp(num)) {
      return 0;
   }
   _pages[num-1] = page->query_read_mess();
   page->move("/room/rubbish");
}
int make_page_blank(int num) {
   if (num < 1 || num > sizeof(_pages) || !intp(num)) {
      return 0;
   }
   _pages[num-1] = 1;
}
string short(int flags) {
  if (!flags || _ignore_open_page) {
    return ::short(flags);
  }
  if (_open_page) {
    return "open " + ::short(flags);
  }
  return "closed " + ::short(flags);
}
string *parse_command_adjectiv_id_list() {
   if (_open_page) {
      return ::parse_command_adjectiv_id_list() + ({ "open" });
   }
   return ::parse_command_adjectiv_id_list() + ({ "closed" });
}
string long(string str, int dark) {
  string ret;
  int i;
  if (!_open_page) {
    return ::long(str, dark)+"It is closed.\n";
  }
  ret = ::long(str, dark)+"It is open at page " + _open_page + ".\n";
  for (i=_open_page-1;i<sizeof(_pages) && !_pages[i];i++) {
    if (!_pages[i]) {
      ret += "Page "+(i+1)+" has been torn out.\n";
    }
  }
  if (i >= sizeof(_pages)) {
    ret += "All the rest of the pages have been torn out!\n";
  } else {
    if (i != _open_page -1) {
      ret += "You can see page "+(i+1)+" however.\n";
    }
    if(str && strsrch(str, "page") != -1) {
      ret += _default_page_object->long(str, dark);
    }
  }
  return ret;
}
protected int do_open(int page) {
  if (page <= 0)  {
     write("Oddly enough, the first page is page 1.\n");
     page = 1;
  }
  else if (page > sizeof(_pages))  {
     write("There " + (sizeof(_pages) == 1 ? "is only " : "are only ") +
           query_num(sizeof(_pages)) +
           (sizeof(_pages) == 1 ? " page in " : " pages in ") +
           the_short() + ".\n");
     page = sizeof(_pages);
  }
  if (query_open_page() == page) {
    add_failed_mess("The $D is already open at page " + page + ".\n");
  }
  if (_open_page > 0  &&  is_page_torn_out (page)) {
     add_failed_mess("The page " +  page + " in $D is torn out.\n");
     return 0;
  }
  _ignore_open_page = 1;
  call_out((: _ignore_open_page = 0 :), 4);
  set_open_page(page);
  add_succeeded_mess("$N $V $D to page " + page + ".\n", ({ }));
  return 1;
}
protected int do_turn(int number) {
  int tmp;
  tmp = query_open_page();
  if (tmp+number > sizeof(_pages)) {
    set_open_page(0);
    add_succeeded_mess("$N close$s $D.\n");
  } else {
    if (tmp == 0) {
       add_succeeded_mess("$N turn$s $D to page " + number + ".\n");
    }
    else add_succeeded_mess("$N turn$s " + number +
           (number > 1 ? " pages " : " page ") + "of $D.\n");
    set_open_page(tmp + number);
  }
  if (tmp == query_open_page()) {
     add_failed_mess("Unable to turn page of $D.\n", ({ }));
     return 0;
  }
  _ignore_open_page = 1;
  call_out((: _ignore_open_page = 0 :), 4);
  return 1;
}
protected int do_close() {
  if (!query_open_page()) {
    this_player()->add_failed_mess(this_object(), "$D is already closed.\n",
                                   ({}));
    return 0;
  }
  _ignore_open_page = 1;
  call_out((: _ignore_open_page = 0 :), 4);
  set_open_page(0);
  return 1;
}
int do_tear(int number) {
  int i;
  if (_ignore_saved_pages) {
    add_failed_mess("For some reason you cannot seem to tear any pages "
                    "from $D.\n");
    return 0;
  }
  if (!_open_page) {
    this_player()->add_failed_mess(this_object(), "$D is closed!\n",
                                   ({}));
    return 0;
  }
  if(number == 0) {
    _open_page = 1;
    number = sizeof(_pages);
  }
  for(i=0; i<number; i++) {
    if(!tear_current_page_out(this_player()))
      break;
    if ( _open_page != sizeof( _pages ) ) {
        _open_page++;
    }
  }
  if(i) {
    if(i > 1)
      add_succeeded_mess("$N $V " + i + " pages from $D.\n");
    else
      add_succeeded_mess("$N $V a page from $D.\n");
    return 1;
  }
  return 0;
}
varargs void set_read_mess(string str, string lang, int size) {
  if (_open_page) {
    if(pointerp(str)) {
      _pages[_open_page-1] = str;
      return;
    }
    if(str)
      _pages[_open_page-1] = ({ ({ str, 0, lang, size }) });
    else
      _pages[_open_page-1] = 1;
    return;
  }
  return ::set_read_mess(str, lang, size);
}
void add_read_mess(mixed str, string type, string lang, int size) {
  if(_open_page) {
    if(!arrayp(_pages[_open_page-1]))
      _pages[_open_page-1] = ({ });
    _pages[_open_page-1] += ({ ({ str, type, lang, size }) });
    return;
  }
  ::add_read_mess(str, type, lang, size);
}
mixed query_read_mess() {
  if (_open_page) {
    if(!_pages[_open_page-1])
      return ({ });
    return _pages[_open_page-1];
  }
  return ::query_read_mess();
}
mixed *stats() {
  return ({
    ({ "num pages" , sizeof(_pages) }),
    ({ "ignore saved pages" , _ignore_saved_pages }),
    ({ "default page ob" , _default_page_object }),
    ({ "open page", _open_page }),
    ({ "book number" , _book_num }),
  }) + ::stats();
}
void dest_me() {
  int i;
  for (i=0;i<sizeof(_pages);i++) {
    if (objectp(_pages[i])) {
      _pages[i]->dest_me();
    }
  }
  ::dest_me();
}
mixed query_static_auto_load() {
  if (file_name(this_object())[0..8] == "/std/book") {
    return int_query_static_auto_load();
  }
}
mapping query_dynamic_auto_load() {
  mapping bing;
  bing = ([
      "::" : ::query_dynamic_auto_load(),
      "default page object" : _default_page_object,
      "open page" : _open_page,
      "book num" : _book_num,
    ]);
  if (!_ignore_saved_pages) {
    bing["pages"] = _pages;
  }
  return bing;
}
void init_dynamic_arg(mapping map, object player) {
  int i;
  object *tmp;
  if (!player) {
    player = _player;
    if (!player) {
       player = this_player();
    }
  }
  if (map["::"]) {
    ::init_dynamic_arg(map["::"]);
  }
  if (map["default page object"]) {
    _default_page_object = map["default page object"];
    load_object(_default_page_object);
    _def_p_obj = find_object(_default_page_object);
  }
  if (map["pages"] && !_ignore_saved_pages) {
    if(sizeof(map["pages"]) && sizeof(map["pages"][0]) == 3) {
      for(i=0; i<sizeof(_pages); i++) {
        tmp = (object *)player->load_auto_load_to_array(map["pages"][i],
                                                        this_object(), player);
        if(sizeof(tmp->query_read_mess()))
          _pages[i] = tmp->query_read_mess()[0];
        tmp->move("/room/rubbish");
      }
    } else
      _pages = map["pages"];
  }
  _book_num = map["book num"];
  set_open_page(map["open page"]);
}
void set_default_page_object(string obj) {
  load_object(obj);
  if (find_object(obj)) {
    _default_page_object = obj;
    _def_p_obj = find_object(obj);
  }
}
string query_default_page_object() {
   return _default_page_object;
}
object create_default_page_object() {
   return clone_object(_default_page_object);
}
int query_num_pages() {
  return sizeof(_pages);
}
int query_book_num() {
   return _book_num;
}
void set_book_num(int num) {
   _book_num = num;
}
int query_ignore_saved_pages() {
   return _ignore_saved_pages;
}
protected void set_ignore_saved_pages(int saved) {
   _ignore_saved_pages = saved;
}
void set_player(object player) {
   _player = player;
}
object query_player() {
   return _player;
}
string query_read_short(object player, int ignore_labels) {
  if(!::query_read_short(player, 0))
    return 0;
  if (!_open_page) {
    return "the cover of " + ::query_read_short(player, 0);
  }
  return "page " + query_num(_open_page) + " of " +
    ::query_read_short(player, 1);
}
string query_readable_message(object player, int ignore_labels) {
   return ::query_readable_message(player, _open_page != 0);
}