inherit "/std/book";
#include "nroff.h"
string language = 0;
void set_book_language(string lang) {
   language = lang;
}
string query_language() { return language; }
void set_book_dir(string dir) {
  int i, max;
  set_no_pages(10);
  set_ignore_saved_pages(1);
  max = 10;
  i = 1;
  set_default_page_object("/obj/misc/nroff_paper");
  set_open_page (0);
  while (file_size(dir+i) > 0) {
    set_open_page(i);
    set_read_mess("$$" + dir + i + "$$" , language, 0);
    i++;
    if (i >= max) {
      max += 10;
      set_no_pages(max);
    }
  }
  set_no_pages(i-1);
  set_open_page(0);
}