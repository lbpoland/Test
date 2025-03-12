#include <book_handler.h>
#include <language.h>
#define SAVE_DIR "/save/book_handler/"
#define SAVE_FILE (SAVE_DIR "main_save")
#define OWNER_INDEX "owner"
#define PAGES_INDEX "pages"
int current_book_number;
mapping banished_books;
int compare_page(object page1, object page2);
void load_it();
void save_it();
int check_book_same(object book, int num);
protected string *query_pages(object book);
int compare_pages(string *pages1, string *pages2);
string *query_book_pages(int book_num);
void create() {
   banished_books = ([ ]);
   seteuid(getuid());
   load_it();
}
int query_book_exists(int book_num) {
   return unguarded((: file_size(SAVE_DIR + $(book_num) + ".o") :)) > 0;
}
int add_book(object book, int num, string pl_name) {
   string *stuff;
   mapping bing;
   if (num) {
      if (check_book_same(book, num)) {
         return num;
      }
   }
   while (query_book_exists(current_book_number)) {
      current_book_number++;
   }
   stuff = query_pages(book);
   bing = ([ OWNER_INDEX : pl_name, PAGES_INDEX : stuff ]);
   unguarded( (: write_file(SAVE_DIR + current_book_number + ".o",
              save_variable($(bing))) :) );
   num = current_book_number++;
   save_it();
   return num;
}
int check_book_same(object book, int num) {
   string *bing;
   string *fluff;
   int old_open_page;
   int same;
   old_open_page = book->query_open_page();
   same = 0;
   if (query_book_exists(num) > 0) {
      bing = query_book_pages(num);
      fluff = query_pages(book);
      if (compare_pages(bing, fluff) > 90) {
         same = 1;
      }
   } else {
      same = 0;
   }
   book->set_open_page(old_open_page);
   return same;
}
string *query_book_pages(int book_num) {
   mapping bing;
   string tmp;
   tmp = unguarded((: read_file(SAVE_DIR + $(book_num) + ".o") :));
   if (tmp) {
      bing = restore_variable(tmp);
      return bing[PAGES_INDEX];
   }
   return 0;
}
string query_book_owner(int book_num) {
   mapping bing;
   string tmp;
   tmp = unguarded((: read_file(SAVE_DIR + $(book_num) + ".o") :));
   if (tmp) {
      bing = restore_variable(tmp);
      return bing[OWNER_INDEX];
   }
   return 0;
}
string *query_pages(object book) {
   int i;
   string *ret;
   mixed *stuff;
   mixed *group;
   string text;
   int old_open_page;
   object ob;
   ret = ({ });
   old_open_page = book->query_open_page();
   for (i = 0; i < book->query_num_pages(); i++) {
      book->set_open_page(i);
      ob = book->query_current_page();
      if (!book->is_current_page_torn_out() &&
          !ob->query_property(BH_IGNORE_PAGE)) {
         stuff = ob->query_read_mess();
         text = "";
         foreach (group in stuff) {
            text += group[READ_MESS];
         }
         ret += ({ text  });
      }
   }
   book->set_open_page(old_open_page);
   return ret;
}
int compare_pages(string *pages1, string *pages2) {
   int no_chars;
   int no_same;
   int pos;
   int start;
   string page;
   string *tmp;
   pos = 0;
   if (sizeof(pages1) > sizeof(pages2)) {
      tmp = pages1;
      pages1 = pages2;
      pages2 = tmp;
   }
   foreach (page in pages1) {
      pos = 0;
      do {
         start = strsrch(page, pages2[pos]);
         if (start == -1) {
            start = strsrch(pages2[pos], page);
            if (start == -1) {
               pos++;
            } else {
               no_same += strlen(page);
            }
         } else {
            no_same += strlen(pages2[pos]);
         }
      } while ((start == -1) && (pos < sizeof(pages2)));
      no_chars += strlen(page);
   }
   if (no_chars > 0) {
      return (no_same * 100) / no_chars;
   }
   return 0;
}
int compare_page(string page1, string page2) {
   mixed *stuff1;
   mixed *stuff2;
   string text1;
   string text2;
   int i;
   stuff2 = page2->query_read_mess();
   text1 = "";
   for (i = 0; i < sizeof(stuff1); i++) {
      text1 += stuff1[READ_MESS];
   }
   text2 = "";
   for (i = 0; i < sizeof(stuff2); i++) {
      text2 += stuff2[READ_MESS];
   }
   return (text1 == text2);
}
int add_banished_book(int book_num, string reason) {
   if (!stringp(reason) || !intp(book_num)) {
      return 0;
   }
   if (!query_book_exists(book_num)) {
      return 0;
   }
   banished_books[book_num] = reason;
}
string query_banished_book(int book_num) {
   return banished_books[book_num];
}
mapping query_all_banished_books() {
   return banished_books;
}
void save_it() {
   unguarded((: save_object(SAVE_FILE) :));
}
void load_it() {
   unguarded((: restore_object(SAVE_FILE) :));
   if (!current_book_number) {
      current_book_number = 1;
   }
   if (!banished_books) {
      banished_books = ([ ]);
   }
}