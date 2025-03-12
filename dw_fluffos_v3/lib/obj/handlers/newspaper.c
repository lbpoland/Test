#include <room/newspaper.h>
#include <nroff.h>
#include <autodoc.h>
#include <login_handler.h>
#define SAVE_DIR "/save/newspaper/"
class edition {
   int date_published;
   class article* articles;
   class advert* adverts;
   string headline;
   int num_sold;
   int num_web_hits;
   int total_revenue;
}
class paper {
   class edition* published_editions;
   string dir_name;
   string long;
   string description;
   string office;
   int paper_cost;
   string language;
}
private mapping _papers;
private mapping _areas;
private mapping _xp;
private mapping _inform;
void load_me();
void save_me();
void create() {
   _papers = ([ ]);
   _areas = ([ ]);
   _xp = ([ ]);
   _inform = ([ ]);
   seteuid(getuid());
   load_me();
   if (!_inform) {
      _inform = ([ ]);
   }
}
int is_paper(string paper) {
   return classp(_papers[paper]);
}
void add_paper(string name, string long, string desc, string office,
    string language) {
   if (is_paper(name)) {
      return ;
   }
   _papers[name] = new(class paper);
   _papers[name]->published_editions = ({ });
   _papers[name]->dir_name = replace_string(lower_case(name), " ", "_");
   _papers[name]->long = long;
   _papers[name]->description = desc;
   _papers[name]->office = office;
   _papers[name]->paper_cost = 5 * 4;
   _papers[name]->language = language;
   save_me();
}
string* query_all_papers() {
   return keys(_papers);
}
int query_current_edition_num(string paper) {
   if (!is_paper(paper)) {
      return 0;
   }
   return sizeof(_papers[paper]->published_editions) + 1;
}
int query_last_edition_num(string paper) {
   if (!is_paper(paper)) {
      return 0;
   }
   return sizeof(_papers[paper]->published_editions);
}
int is_valid_edition(string paper, int edition) {
   if (!is_paper(paper)) {
      return 0;
   }
   if (edition > 0 && edition <= sizeof(_papers[paper]->published_editions)) {
      return 1;
   }
   return 0;
}
int query_edition_date(string paper, int edition) {
   if (!is_paper(paper)) {
      return 0;
   }
   if (!is_valid_edition(paper, edition)) {
      return 0;
   }
   return _papers[paper]->published_editions[edition - 1]->date_published;
}
class article* query_edition_articles(string paper, int edition) {
   if (!is_paper(paper)) {
      return ({ });
   }
   if (!is_valid_edition(paper, edition)) {
      return ({ });
   }
   return copy(_papers[paper]->published_editions[edition - 1]->articles);
}
class advert* query_edition_adverts(string paper, int edition) {
   if (!is_paper(paper)) {
      return ({ });
   }
   if (!is_valid_edition(paper, edition)) {
      return ({ });
   }
   return copy(_papers[paper]->published_editions[edition - 1]->adverts);
}
string query_paper_office(string paper) {
   if (!is_paper(paper)) {
      return  0;
   }
   return _papers[paper]->office;
}
void set_paper_office(string paper, string office) {
   if (!is_paper(paper)) {
      return  0;
   }
    _papers[paper]->office = office;
   save_me();
}
string query_paper_headline(string paper, int edition) {
   if (!is_valid_edition(paper, edition)) {
      return  "No news is good news.";
   }
   return _papers[paper]->published_editions[edition - 1]->headline;
}
void set_paper_headline(string paper, int edition, string headline) {
   if (!is_valid_edition(paper, edition)) {
      return  ;
   }
   _papers[paper]->published_editions[edition - 1]->headline = headline;
   save_me();
}
int query_edition_revenue(string paper, int edition) {
   if (!is_valid_edition(paper, edition)) {
      return  0;
   }
   return _papers[paper]->published_editions[edition - 1]->total_revenue;
}
void add_edition_revenue(string paper, int edition, int revenue) {
   if (!is_valid_edition(paper, edition)) {
      return  ;
   }
   _papers[paper]->published_editions[edition - 1]->total_revenue += revenue;
   save_me();
}
void add_edition_web_hit(string paper, int edition) {
   if (!is_valid_edition(paper, edition)) {
      return  ;
   }
   _papers[paper]->published_editions[edition - 1]->num_web_hits++;
   _papers[paper]->published_editions[edition - 1]->total_revenue += NEWSPAPER_WEB_HIT_REVENUE;
   save_me();
}
void add_edition_paper_sold(string paper, int edition, int cost) {
   if (!is_valid_edition(paper, edition)) {
tell_creator("pinkfish", "Not valid edition %O %O\n", paper, previous_object());
      return  ;
   }
tell_creator("pinkfish", "Updating num sold %O %O\n", paper, edition);
   _papers[paper]->published_editions[edition - 1]->num_sold++;
   _papers[paper]->published_editions[edition - 1]->total_revenue += cost;
   save_me();
}
int query_edition_num_sold(string paper, int edition) {
   if (!is_valid_edition(paper, edition)) {
      return  0;
   }
   return _papers[paper]->published_editions[edition - 1]->num_sold;
}
int query_edition_num_web_hits(string paper, int edition) {
   if (!is_valid_edition(paper, edition)) {
      return  0;
   }
   return _papers[paper]->published_editions[edition - 1]->num_web_hits;
}
int is_paper_area(string area) {
   return pointerp(_areas[area]);
}
void add_paper_area(string area) {
   if (is_paper_area(area)) {
      return ;
   }
   _areas[area] = ({ });
}
void add_paper_to_area(string paper, string area) {
   if (!is_paper(paper) || !is_paper_area(area)) {
      return ;
   }
   _areas[area] += ({ paper });
   save_me();
}
string* query_papers_in_area(string area) {
   if (_areas[area]) {
      return _areas[area];
   }
   return ({ });
}
void set_article_text(class article art, string text) {
   unguarded( (:
      write_file(SAVE_DIR + $(art->file_name), save_variable(({ $(art), $(text) })), 1) :) );
}
void add_newspaper_inform(string paper, string ob) {
   if (!_inform[paper]) {
      _inform[paper] = ({ });
   }
   if (!stringp(ob)) {
      return ;
   }
   if (member_array(ob, _inform[paper]) != -1) {
      return ;
   }
   _inform[paper] += ({ ob });
   save_me();
}
void remove_newspaper_inform(string paper, string ob) {
   if (!_inform[paper]) {
      return ;
   }
   _inform[paper] -= ({ ob });
   save_me();
}
string* query_newspaper_informs(string paper) {
   if (!_inform[paper]) {
      return ({ });
   }
   return _inform[paper];
}
string query_article_text(class article art) {
   string str;
   string* bits;
   str = unguarded( (: read_file(SAVE_DIR + $(art->file_name)) :) );
   if (str) {
      bits = restore_variable(str);
      return bits[1];
   }
   return "Error reading the article text.";
}
string query_article_text_html(class article art) {
   string str;
   string* bits;
   str = unguarded( (: read_file(SAVE_DIR + $(art->file_name)) :) );
   if (str) {
      bits = restore_variable(str);
      switch (art->type & NEWSPAPER_ARTICLE_TYPE_MASK) {
      case NEWSPAPER_ARTICLE_TYPE_PLAIN :
         bits[1] = replace_string(bits[1], "\n\n", "<p>");
         bits[1] = replace_string(bits[1], "\n", "<br>");
         return bits[1];
      case NEWSPAPER_ARTICLE_TYPE_HTML :
         bits[1] = replace_string(bits[1], "<pre>", "</font><pre>");
         bits[1] = replace_string(bits[1], "</pre>",
                                  "</pre>\n<font face=\"helvetica,arial\">");
         return bits[1];
      }
      return bits[1];
   }
   return "Error reading the article text.";
}
string convert_html(string input) {
   return AUTODOC_NROFF->convert_html(input);
}
string query_article_text_plain(class article art) {
   string str;
   string fluff;
   string* bits;
   switch (art->type & NEWSPAPER_ARTICLE_TYPE_MASK) {
   case NEWSPAPER_ARTICLE_TYPE_SECTION :
      return "";
   case NEWSPAPER_ARTICLE_TYPE_PLAIN :
      str = unguarded( (: read_file(SAVE_DIR + $(art->file_name)) :) );
      if (str) {
         bits = restore_variable(str);
         return bits[1];
      }
      break;
   case NEWSPAPER_ARTICLE_TYPE_HTML :
      fluff = unguarded( (: NROFF_HAND->cat_file(SAVE_DIR + $(art->file_name) + ".nroff", 1) :) );
      if (!fluff) {
         str = unguarded( (: read_file(SAVE_DIR + $(art->file_name)) :) );
         if (str) {
            bits = restore_variable(str);
            bits[1] = convert_html(bits[1]);
            unguarded( (: write_file(SAVE_DIR + $(art->file_name) + ".proc",
                                     $(bits[1]), 1) :) );
            unguarded( (: NROFF_HAND->create_nroff(SAVE_DIR + $(art->file_name) + ".proc",
                                SAVE_DIR + $(art->file_name) + ".nroff") :) );
            str = unguarded( (: NROFF_HAND->cat_file(SAVE_DIR + $(art->file_name) + ".nroff") :) );
            return str;
         }
      } else {
         return fluff;
      }
   }
   return "Error reading the article text.";
}
string query_paper_long(string paper) {
   if (!is_paper(paper)) {
      return "This is a very transperant and unhappy newspaper.\n";
   }
   return _papers[paper]->long;
}
void set_paper_description(string paper, string description) {
   if (!is_paper(paper)) {
      return ;
   }
   _papers[paper]->description = description;
   save_me();
}
string query_paper_description(string paper) {
   if (!is_paper(paper)) {
      return "This is a very transperant and unhappy newspaper.\n";
   }
   return _papers[paper]->description;
}
void set_paper_long(string paper, string long) {
   if (!is_paper(paper)) {
      return ;
   }
   _papers[paper]->long = long;
   save_me();
}
void set_paper_cost(string paper, int cost) {
   if (!is_paper(paper)) {
      return ;
   }
   _papers[paper]->paper_cost = cost;
   save_me();
}
int query_paper_cost(string paper) {
   if (!is_paper(paper)) {
      return 0;
   }
   return _papers[paper]->paper_cost;
}
int publish_paper(string paper,
                  string headline,
                  class article* articles,
                  string* text,
                  class advert* adds,
                  string* editors) {
   string paper_dir;
   string tmp;
   class paper fluff;
   class article article;
   class edition womble;
   int i;
   int edition;
   int total_xp;
   int type;
   if (!is_paper(paper)) {
      return 0;
   }
   fluff = _papers[paper];
   edition = sizeof(fluff->published_editions) + 1;
   paper_dir = SAVE_DIR + fluff->dir_name;
   unguarded( (: mkdir($(paper_dir)) :));
   paper_dir += "/" + edition;
   unguarded( (: mkdir($(paper_dir)) :));
   foreach (article in articles) {
      article->file_name = fluff->dir_name + "/" + edition + "/" +
                           article->file_name;
      type = article->type & NEWSPAPER_ARTICLE_TYPE_MASK;
      if ((type == NEWSPAPER_ARTICLE_TYPE_PLAIN ||
           type == NEWSPAPER_ARTICLE_TYPE_HTML) &&
           !(article->type & NEWSPAPER_ARTICLE_NO_XP_FLAG)) {
         _xp[lower_case(article->author)] += NEWSPAPER_XP_PER_ARTICLE;
         total_xp += NEWSPAPER_XP_PER_ARTICLE;
      }
   }
   total_xp = total_xp * 10 / 100;
   total_xp += NEWSPAPER_XP_EDITOR;
   if (sizeof(editors)) {
      foreach (tmp in editors) {
         _xp[tmp] += total_xp / sizeof(editors);
      }
   }
   for (i = 0; i < sizeof(articles); i++) {
      set_article_text(articles[i], text[i]);
   }
   womble = new(class edition);
   womble->articles = articles;
   womble->adverts = adds;
   womble->date_published = time();
   womble->headline = headline;
   fluff->published_editions += ({ womble });
   save_me();
   foreach (tmp in query_newspaper_informs(paper)) {
      call_out((: $1->event_publish_paper($2) :), 2, tmp, paper);
   }
   return 1;
}
void load_me() {
   string paper;
   class paper fluff;
   class paper rabbit;
   unguarded( (: restore_object(SAVE_DIR + "main", 1) :) );
   foreach (paper, fluff in _papers) {
      if (sizeof(fluff) == 6) {
         rabbit = new(class paper);
         rabbit->published_editions = fluff->published_editions;
         rabbit->dir_name = fluff->dir_name;
         rabbit->long = fluff->long;
         rabbit->description = fluff->description;
         rabbit->office = fluff->office;
         rabbit->paper_cost = 5 * 4;
         rabbit->language = "general";
         _papers[paper] = rabbit;
         fluff = rabbit;
      } else if( sizeof( fluff ) == 7 ) {
         rabbit = new(class paper);
         rabbit->published_editions = fluff->published_editions;
         rabbit->dir_name = fluff->dir_name;
         rabbit->long = fluff->long;
         rabbit->description = fluff->description;
         rabbit->office = fluff->office;
         rabbit->paper_cost = 5 * 4;
         rabbit->language = fluff->language;
         _papers[paper] = rabbit;
         fluff = rabbit;
      }
   }
}
void save_me() {
   unguarded( (: save_object(SAVE_DIR + "main") :) );
}
mixed* stats() {
   string paper;
   string person;
   class paper data;
   mixed* ret;
   int last;
   int xp;
   ret = ({ });
   foreach (paper, data in _papers) {
      last = query_last_edition_num(paper);
      ret += ({ ({ paper + ": office", data->office }),
                ({ paper + ": dir name", data->dir_name }),
                ({ paper + ": last issue", last }),
                ({ paper + ": current issue", query_current_edition_num(paper) }),
                ({ paper + ": num sold", query_edition_num_sold(paper, last) }),
                ({ paper + ": num web hits", query_edition_num_web_hits(paper, last) }),
                ({ paper + ": revenue", query_edition_revenue(paper, last) }),
              });
   }
   foreach (person, xp in _xp) {
      ret += ({ ({ person + ": xp", xp }) });
   }
   return ret;
}
void player_login_check(string player, string bing) {
   object play;
   int xp;
   if (bing != LOGIN) {
      return ;
   }
   xp = _xp[player];
   if (xp) {
      play = find_player(player);
      play->adjust_xp(xp);
      map_delete(_xp, player);
      save_me();
      tell_object(play, "%^YELLOW%^You feel like the experience of writing "
                        "an article has made you a better person.\n%^RESET%^");
   }
}
void set_language_for( string paper, string language ) {
    if( is_paper( paper ) )
        _papers[ paper ]->language = language;
}
string query_language_for( string paper ) {
    if( is_paper( paper ) ) {
        if( !undefinedp( _papers[ paper ]->language ) )
            return _papers[ paper ]->language;
        return "general";
    }
    return 0;
}