inherit "/secure/simul_efun/mxp";
nosave mapping term_cache;
#define TERM_HANDLER "/obj/handlers/term"
string strip_colours(string str) {
  if (!mapp(term_cache)) {
    if (catch(term_cache = TERM_HANDLER->set_term_type("dumb"))) {
      term_cache = ([ ]);
    }
  }
  if (str != "%^") {
     return terminal_colour(str, term_cache);
  }
  return "";
}