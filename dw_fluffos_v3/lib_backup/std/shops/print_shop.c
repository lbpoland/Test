#include <language.h>
#include <money.h>
#include <book_handler.h>
inherit "/std/room/basic_room";
#define COPYRIGHT_NUMBER 3
nosave mixed *discount_schedule;
mapping collectables;
int current_save_number;
nosave int letter_cost;
nosave int time_to_collect;
nosave int time_per_copy;
nosave string save_dir;
nosave string office_room;
nosave int no_collection;
nosave function open_func;
nosave string default_language;
nosave mapping translation_costs;
nosave string print_shop_name;
#define SCHEDULE_NUM 1
#define SCHEDULE_PERCENTAGE 0
#define COLLECT_TIME 0
#define COLLECT_NUM  1
#define COLLECT_OB_NAME 2
#define COLLECT_LANGUAGE 3
#define COLLECT_AUTO_LOAD_NUM 4
#define COLLECT_ARR_SIZE 5
#define BINDING_COST 600
#define DEFAULT_LETTER_COST 1
#define DEFAULT_TIME_TO_COLLECT (8*60*60)
#define DEFAULT_TIME_PER_COPY (20*60)
#define MAX_NUMBER 30
int price_object(object ob, int num, string language);
protected int do_print_copies(object *obs, int num, string language);
protected int do_print(object *obs, string language);
protected int do_claim(object *obs);
protected int do_collect();
void do_print_run(object ob, int number, int cost, string language);
void print_pricing(object ob, string language);
void remove_print_run(string name, mixed *info);
mixed *query_print_run(string name);
void add_print_run(string name, object ob, int number, string language);
void load_it();
void save_it();
string query_print_shop_name();
string query_static_auto_load_info(int num);
mapping query_dynamic_auto_load_info(int num);
protected int add_auto_load_info(string static, string dynamic);
private object create_fly_leaf(object book, string language);
private void remove_auto_load_info(int num);
void create() {
   letter_cost = DEFAULT_LETTER_COST;
   time_to_collect = DEFAULT_TIME_TO_COLLECT;
   time_per_copy = DEFAULT_TIME_PER_COPY;
   collectables = ([ ]);
   discount_schedule = ({ ({ 100, 5 }),
                          ({ 95, 10 }),
                          ({ 90, 20 }),
                          ({ 80, 101 }) });
   default_language = "common";
   translation_costs = ([ ]);
   print_shop_name = "Rabbits happy little printing press";
   ::create();
   load_it();
   add_help_file("print_shop");
}
void init() {
   string languages;
   if (!office_room) {
      add_command("print", "<indirect:object>",
                   (: do_print($1, default_language) :));
      add_command("print", "<number> [copies] of <indirect:object>",
                      (: do_print_copies($1, $4[0], default_language) :) );
      add_command("claim", "copyright on <indirect:object>", (: do_claim :));
      if (sizeof(translation_costs)) {
         languages = implode(keys(translation_costs) + ({ default_language }), "|");
         add_command("print", "<indirect:object> in {" + languages + "}",
                   (: do_print($1, $4[1]) :));
         add_command("print", "<number> [copies] of <indirect:object> in "
                              "{" + languages + "}",
                         (: do_print_copies($1, $4[0], $4[2]) :) );
      }
   }
   if (!no_collection) {
      add_command("collect", "", (: do_collect :));
   }
}
protected int is_copyright(object book) {
  if (BOOK_HANDLER->check_book_same(book, book->query_book_num())) {
     return 1;
  }
  return 0;
}
protected string copyright_holder(object book) {
   return BOOK_HANDLER->query_book_owner(book->query_book_num());
}
protected int do_claim(object *obs) {
   object ob;
   object *already_copyright;
   object *new_copyright;
   object *cannot_copyright;
   string name;
   string place;
   int value;
   int player_money;
   already_copyright = ({ });
   new_copyright = ({ });
   cannot_copyright = ({ });
   name = this_player()->query_name();
   foreach (ob in obs) {
      if (!ob->query_book()) {
         cannot_copyright += ({ ob });
      } else if (is_copyright(ob)) {
         already_copyright += ({ ob });
      } else {
         new_copyright += ({ ob });
      }
   }
   if (!sizeof(new_copyright)) {
      if (sizeof(cannot_copyright)) {
         add_failed_mess("You cannot copyright $I.\n", cannot_copyright);
      }
      if (sizeof(already_copyright) == 1) {
         add_failed_mess("$I is copyrighted.\n",
                         already_copyright);
      } else {
         add_failed_mess("$I are copyrighted.\n",
                         already_copyright);
      }
      return 0;
   }
   place = query_property( "place" );
   if ( !place || ( place == "" ) ) {
      place = "default";
   }
   value = 0;
   foreach (ob in new_copyright) {
      value += price_object(ob, COPYRIGHT_NUMBER, default_language);
   }
   player_money = (int)this_player()->query_value_in( place );
   if ( place != "default" ) {
      player_money += (int)this_player()->query_value_in( "default" );
   }
   write("It will cost you " + MONEY_HAND->money_value_string( value, place ) +
         " to make " + query_multiple_short(new_copyright) +
         " copyright.\n");
   if (player_money > value) {
      write("Do you wish to continue? ");
      input_to("check_copyright", 0, new_copyright, value);
   } else {
      write("Although you do not currently have enough money.\n");
   }
   add_succeeded_mess( ({ "", "$N enquires about copyrighting $I.\n" }),
                       new_copyright);
   return 1;
}
protected void check_copyright(string str, object *new_copyright, int value) {
   int new_num;
   object ob;
   string place;
   if (!strlen(str) || (str[0] != 'y' && str[0] != 'Y')) {
      write("Ok, never mind.  See you again soon.\n");
      return ;
   }
   place = query_property( "place" );
   if ( !place || ( place == "" ) ) {
      place = "default";
   }
   this_player()->pay_money( (mixed *)MONEY_HAND->create_money_array(
               value, place ), place );
   foreach (ob in new_copyright) {
      new_num = BOOK_HANDLER->add_book(ob, 0, this_player()->query_name());
      ob->set_book_num(new_num);
      ob->add_property(BH_COPYRIGHT, this_player()->query_name());
   }
   write("Ok, added " + query_multiple_short(new_copyright) +
         " as a copyright book.\n");
}
protected int do_collect() {
   object new_ob;
   object page;
   object fly_leaf;
   int i;
   int j;
   int number;
   int no_printed;
   string ob_name;
   mixed static_arg;
   mixed dynamic_arg;
   string language;
   mixed *info;
   mixed *stuff;
   mixed *collectables;
   mixed room;
   int auto_load_num;
   if (open_func) {
      if (!evaluate(open_func)) {
         return 0;
      }
   }
   if (office_room) {
      room = office_room;
   } else {
      room = this_object();
   }
   collectables = room->query_print_run(this_player()->query_name());
   if (!collectables) {
      add_failed_mess("No books available for collection.\n");
      return 0;
   }
   no_printed = 0;
   foreach (info in collectables) {
      if (time() < info[COLLECT_TIME]) {
         add_failed_mess("You need to wait until " +
                         amtime(info[COLLECT_TIME]) +
                         " to collect your book.\n");
         continue;
      }
      auto_load_num = info[COLLECT_AUTO_LOAD_NUM];
      static_arg = room->query_static_auto_load_info(auto_load_num);
      dynamic_arg = room->query_dynamic_auto_load_info(auto_load_num);
      ob_name = info[COLLECT_OB_NAME];
      number = info[COLLECT_NUM];
      language = info[COLLECT_LANGUAGE];
      if (office_room) {
         office_room->remove_print_run(this_player()->query_name(), info);
      } else {
         remove_print_run(this_player()->query_name(), info);
      }
      new_ob = clone_object(ob_name);
      if (static_arg) {
         new_ob->init_static_arg(static_arg);
      }
      if (dynamic_arg) {
         new_ob->init_dynamic_arg(dynamic_arg);
      }
      new_ob->set_open_page(0);
      for (j = 0; j < new_ob->query_num_pages(); j++) {
         if (j > 0) {
            page = new_ob->query_selected_page(j);
         } else {
            new_ob->set_open_page(0);
            page = new_ob;
         }
         if (j == 1) {
             fly_leaf = create_fly_leaf(new_ob, language);
             if (page->query_property(BH_IGNORE_PAGE)) {
                new_ob->replace_page_with(fly_leaf, j);
             } else {
                new_ob->add_page_after(fly_leaf, j - 1);
             }
             page = new_ob->query_selected_page(j + 1);
         }
         stuff = page->query_read_mess();
         foreach (info in stuff) {
            if (info[READ_LANG] != language) {
               info[READ_LANG] = language;
            }
         }
         page->set_read_mess(stuff);
      }
      static_arg = new_ob->query_static_auto_load();
      dynamic_arg = new_ob->query_dynamic_auto_load();
      new_ob->dest_me();
      for (i = 0; i < number; i++) {
         new_ob = clone_object(ob_name);
         new_ob->set_player(this_player());
         if (static_arg) {
            new_ob->init_static_arg(static_arg, this_player());
         }
         if (dynamic_arg) {
            new_ob->init_dynamic_arg(dynamic_arg, this_player());
         }
         new_ob->move(this_object());
      }
      if (number > 1) {
         write("Ok, your " + query_num(number, 1000) + " copies of " +
               new_ob->the_short() +
               " have been placed on the floor here.\n");
      } else {
         write("Ok, your copy of " + new_ob->the_short() +
               " has been placed on the floor here.\n");
      }
      no_printed++;
   }
   return no_printed;
}
private object create_fly_leaf(object book, string language) {
    object page;
    page = book->create_default_page_object();
    if (is_copyright(book)) {
       page->add_read_mess("\n\nPrinted " + amtime(time()) +
                             " by " + query_print_shop_name() +
                             "\n\nCopyright " +
                             this_player()->query_name(), 0,
                             language);
    } else {
       page->add_read_mess("\n\nPrinted " + amtime(time()) +
                             " by " + query_print_shop_name() +
                             "\n", 0,
                             language);
    }
    page->add_property(BH_IGNORE_PAGE, 1);
    return page;
}
int check_for_magic_writing(object ob) {
   mixed *stuff;
   int i;
   stuff = ob->query_read_mess();
   for (i = 0; i < sizeof(stuff); i++) {
      if (LANGUAGE_HAND->query_language_magic(stuff[i][READ_LANG])) {
         return 1;
      }
   }
   return 0;
}
int check_for_untranslatable_language(object ob) {
   mixed *stuff;
   int i;
   string lang;
   stuff = ob->query_read_mess();
   for (i = 0; i < sizeof(stuff); i++) {
      lang = stuff[i][READ_LANG];
      if (lang != default_language &&
          !translation_costs[lang]) {
         return 1;
      }
   }
   return 0;
}
object find_book_or_paper(object *obs) {
   object *paper;
   object *books;
   object *magic;
   object *torn_out;
   object *nothing;
   object ob;
   int page;
   int old_page;
   string owner;
   paper = ({ });
   books = ({ });
   magic = ({ });
   torn_out = ({ });
   nothing = ({ });
   foreach (ob in obs) {
      owner = copyright_holder(ob);
      if (is_copyright(ob) && owner != this_player()->query_name()) {
         add_failed_mess("$I has been copyrighted by " + owner +
                         " and cannot be copied.\n", ({ ob }));
      } else if (ob->query_book()) {
         if (ob->query_spell_book()) {
            magic += ({ ob });
         } else {
            old_page = ob->query_open_page();
            for (page = 0; page <= ob->query_num_pages(); page++) {
               ob->set_open_page(page);
               if (ob->is_current_page_torn_out()) {
                  torn_out += ({ ob });
                  break;
               }
               if (check_for_magic_writing(ob)) {
                  magic += ({ ob });
                  break;
               }
            }
            ob->set_open_page(old_page);
            if (page == ob->query_num_pages() + 1) {
               books += ({ ob });
            }
         }
      } else if (ob->query_paper()) {
         if (check_for_magic_writing(ob)) {
            magic += ({ ob });
         } else {
            paper += ({ ob });
         }
      } else {
         nothing += ({ ob });
      }
   }
   if (sizeof(magic)) {
      add_failed_mess("$I have magic writing in them and cannot be copied.\n",
                      magic);
   }
   if (sizeof(torn_out)) {
      add_failed_mess("$I have pages torn out and cannot be copied.\n",
                      torn_out);
   }
   if (!sizeof(books) && !sizeof(paper)) {
      if (sizeof(nothing)) {
         add_failed_mess("Unable to print $I as they are not a book or paper.\n", nothing);
      }
      return 0;
   }
   if (sizeof(books + paper) > 1) {
      add_failed_mess("Can only do print one book or piece of paper at a time.  "
                  "Please be more specific and choose from " +
                  query_multiple_short(books + paper) + ".\n");
      return 0;
   }
   if (sizeof(books) > 0) {
      return books[0];
   }
   return paper[0];
}
int do_print(object *obs, string language) {
   object ob;
   if (open_func) {
      if (!evaluate(open_func, obs)) {
         return 0;
      }
   }
   ob = find_book_or_paper(obs);
   if (!ob) {
      return 0;
   }
   print_pricing(ob, language);
   write("Use: print <number> of <book>\n");
   add_succeeded_mess(({ "",
                       "$N enquires about the cost of printing a book.\n" }));
   return 1;
}
int do_print_copies(object *obs, int number, string language) {
   object ob;
   int cost;
   int player_money;
   string place;
   if (open_func) {
      if (!evaluate(open_func, obs)) {
         return 0;
      }
   }
   if (number < 1) {
      add_failed_mess("Must print at least one copy.\n", obs);
      return 0;
   }
   if (number > MAX_NUMBER) {
      add_failed_mess("Cannot print more than " + MAX_NUMBER +
                      " copies.\n", obs);
      return 0;
   }
   place = query_property( "place" );
   if ( !place || ( place == "" ) ) {
      place = "default";
   }
   ob = find_book_or_paper(obs);
   if (!ob) {
      return 0;
   }
   cost = price_object(ob, number, language);
   player_money = (int)this_player()->query_value_in( place );
   if ( place != "default" ) {
      player_money += (int)this_player()->query_value_in( "default" );
   }
   if (player_money < cost) {
      add_failed_mess("This will cost you " +
                       (string)MONEY_HAND->money_value_string(
                      cost, place ) + " and you do not have enough "
                  "money to afford it.\n", ({ ob }));
      return 0;
   }
   if (is_copyright(ob)) {
      write("NOTE:  You are printing a copyright document.\n");
   } else {
      write("NOTE:  Please use 'claim copyright' to claim copyright "
            "on a document.\n");
   }
   add_succeeded_mess(({ "This will cost you " +
                       (string)MONEY_HAND->money_value_string(
                      cost, place ) +
                       " to do, do you wish to continue? ",
                       "$N starts to do some printing.\n" }));
   input_to("check_cost", 0, ob, number, cost, language);
   return 1;
}
void check_cost(string str, object ob, int number, int cost, string language) {
   if (strlen(str) < 1 || (str[0] != 'y' && str[0] != 'Y')) {
      write("Ok, don't worry.  See you again.\n");
      return ;
   }
   do_print_run(ob, number, cost, language);
}
void do_print_run(object ob, int number, int cost, string language) {
   string place;
   int player_money;
   mixed *stuff;
   place = query_property( "place" );
   if ( !place || ( place == "" ) ) {
      place = "default";
   }
   player_money = (int)this_player()->query_value_in( place );
   if ( place != "default" ) {
      player_money += (int)this_player()->query_value_in( "default" );
   }
   if (player_money < cost) {
      write("You do not seem to have enough money any more.\n");
      return ;
   }
   this_player()->pay_money( (mixed *)MONEY_HAND->create_money_array(
               cost, place ), place );
   add_print_run(this_player()->query_name(),
                 ob,
                 number,
                 language);
   stuff = query_print_run(this_player()->query_name());
   if (no_collection) {
      write("The copies will be ready at " +
            amtime(stuff[<1][COLLECT_TIME]) + " for 'collect'ion at the "
            "collection office.\n");
   } else {
      write("The copies will be ready at " +
            amtime(stuff[<1][COLLECT_TIME]) + " for 'collect'ion.\n");
   }
}
int price_object(object ob, int num, string to_language) {
   int i;
   int num_letters;
   int multiplier;
   int cost;
   mixed *stuff;
   if (num <= 0 || !ob) {
     return 0;
   }
   ob->set_open_page(0);
   stuff = ob->query_read_mess();
   for (i = 0; i < sizeof(stuff); i++) {
      num_letters += strlen(stuff[i][READ_MESS]);
      if (stuff[i][READ_LANG] != default_language) {
         cost = translation_costs[stuff[i][READ_LANG]];
         if (!cost) {
            cost = 1000;
         }
         num_letters = (num_letters * cost) / 100;
      }
      if (to_language != default_language) {
         cost = translation_costs[to_language];
         if (!cost) {
            cost = 1000;
         }
         num_letters = (num_letters * cost) / 100;
      }
   }
   cost = ob->query_value() + (num_letters / 10) * letter_cost;
   if (ob->query_book()) {
      for (i = 1; i < ob->query_num_pages(); i++) {
         ob->set_open_page(i + 1);
         if (ob != ob->query_current_page()) {
            cost += price_object(ob->query_current_page(), 1, to_language);
         }
      }
      cost += BINDING_COST;
   }
   multiplier = 200;
   for (i = 0; i < sizeof(discount_schedule); i++) {
      if (num < discount_schedule[i][SCHEDULE_NUM]) {
         multiplier = discount_schedule[i][SCHEDULE_PERCENTAGE];
      }
   }
   return (cost * num * multiplier) / 100;
}
void print_pricing(object ob, string language) {
   int i;
   int num;
   string place;
   int cost;
   place = query_property( "place" );
   if ( !place || ( place == "" ) ) {
      place = "default";
   }
   write("The cost for the different numbers of " + ob->the_short() + " is:\n");
   write("  1 for " + (string)MONEY_HAND->money_value_string(
                    price_object(ob, 1, language), place ) +
                    " and will be ready at " +
                    amtime(time_to_collect + time_per_copy + time()) + ".\n");;
   for (i = 0; i < sizeof(discount_schedule); i++) {
      num = discount_schedule[i][SCHEDULE_NUM];
      if (num < MAX_NUMBER) {
         write(sprintf("%3d for %s and will be ready at %s.\n", num,
                       (string)MONEY_HAND->money_value_string(
                       price_object(ob, num, language), place ),
                       amtime(time_to_collect + time_per_copy * num + time()) ));
      }
   }
   if (sizeof(translation_costs)) {
      write("You can translate a book to or from " +
            query_multiple_short(keys(translation_costs) + ({ default_language })) +
            ", the cost of doing the translation is defined in the "
            "following table.");
      if (sizeof(translation_costs) > 2) {
         write("  Translating between two of these languages "
               "is also possible, but it will cost the amount to translate "
               "from the language to " + default_language + " and back again.");
      }
      write("\n");
      foreach (language, cost in translation_costs) {
         write(sprintf("   %3d%% %s", cost, language));
      }
      write("\n");
   }
}
mixed *query_discount_schedule() {
   return discount_schedule;
}
void set_discount_schedule(mixed *value) {
   discount_schedule = value;
}
int query_letter_cost() {
   return letter_cost;
}
void set_letter_cost(int value) {
   letter_cost = value;
}
void add_print_run(string name, object ob, int number, string language) {
   mixed *arr;
   int num;
   if (!collectables[name]) {
      collectables[name] = ({ });
   }
   arr = allocate(COLLECT_ARR_SIZE);
   arr[COLLECT_TIME] = time() + time_to_collect + time_per_copy * number;
   arr[COLLECT_NUM] = number;
   arr[COLLECT_LANGUAGE] = language;
   arr[COLLECT_OB_NAME] = base_name(ob);
   num = add_auto_load_info(ob->query_static_auto_load(),
                             ob->query_dynamic_auto_load());
   arr[COLLECT_AUTO_LOAD_NUM] = num;
   collectables[name] += ({ arr });
   save_it();
}
mixed *query_print_run(string name) {
   return collectables[name];
}
void remove_print_run(string name, mixed *info) {
   int index;
   if (collectables[name]) {
      index = member_array(info, collectables[name]);
      if (index != -1) {
         remove_auto_load_info(info[COLLECT_AUTO_LOAD_NUM]);
         collectables[name] = collectables[name][0.. index - 1] +
                              collectables[name][index + 1..];
         if (!sizeof(collectables[name])) {
            map_delete(collectables, name);
         }
         save_it();
      }
   }
}
protected int add_auto_load_info(string static, string dynamic) {
   int num;
   num = current_save_number;
   while (unguarded( (: file_size(save_dir + "/" + $(num)) :) ) > 0) {
      num++;
   }
   current_save_number = num + 1;
   unguarded( (: write_file(save_dir + "/" + $(num),
                            save_variable( ({ $(static), $(dynamic) }) ) +
                            "\n") :) );
   return num;
}
private void remove_auto_load_info(int num) {
   unguarded( (: rm(save_dir + "/" + $(num) ) :) );
}
string query_static_auto_load_info(int num) {
   string *arr;
   string tmp;
   if (unguarded( (: file_size(save_dir + "/" + $(num)) :) ) > 0) {
      tmp = unguarded( (: read_file(save_dir + "/" + $(num)) :) );
      if (tmp) {
         arr = restore_variable(tmp);
         return arr[0];
      }
   }
   return 0;
}
mapping query_dynamic_auto_load_info(int num) {
   mixed arr;
   string tmp;
   if (unguarded( (: file_size(save_dir + "/" + $(num)) :) ) > 0) {
      tmp = unguarded( (: read_file(save_dir + "/" + $(num)) :) );
      if (tmp) {
         arr = restore_variable(tmp);
         return arr[1];
      }
   }
   return 0;
}
void set_save_dir(string name) {
   save_dir = name;
}
string query_save_dir() {
   return save_dir;
}
void load_it() {
   if (save_dir) {
      unguarded((: restore_object(save_dir + "/main") :));
      if (!collectables) {
         collectables = ([ ]);
      }
   }
}
void save_it() {
   if (save_dir) {
      unguarded((: save_object(save_dir + "/main") :));
   }
}
void set_office_room(string room) {
   office_room = room;
}
string query_office_room() {
   return office_room;
}
void set_no_collection(int collect) {
   no_collection = collect;
}
int query_no_collection() {
   return no_collection;
}
void set_open_func(function func) {
   open_func = func;
}
function query_open_func() {
   return open_func;
}
void set_default_language(string lang) {
   default_language = lang;
}
string query_default_language() {
   return default_language;
}
void add_translation_cost(string lang, int cost) {
   translation_costs[lang] = cost;
}
void remove_translation_cost(string lang) {
   map_delete(translation_costs, lang);
}
mapping query_all_translantion_costs() {
   return translation_costs;
}
void set_print_shop_name(string name) {
   print_shop_name = name;
}
string query_print_shop_name() {
   return print_shop_name;
}