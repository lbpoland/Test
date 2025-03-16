#include <language.h>
#include <nroff.h>
inherit "/std/basic/desc";
private nosave mixed *_read_mess = ({ });
private nosave int _max_size = 100;
private nosave int _cur_size;
varargs mixed add_read_mess(mixed str, string type, string lang, int size);
mixed query_property(string name);
void set_max_size(int siz) { _max_size = siz; }
int query_max_size() { return _max_size; }
void set_cur_size(int siz) { _cur_size = siz; }
int query_cur_size() { return _cur_size; }
varargs void set_read_mess(mixed str, string lang, int size) {
   if ( pointerp( str ) ) {
      _read_mess = str;
      return;
   }
  if (!lang)
    return;
  if (!size)
    size = 1;
  if ( str )
    _read_mess = ({ ({ str, 0, lang, size }) });
  else
    _read_mess = ({ });
}
mixed *query_read_mess() { return copy( _read_mess ); }
varargs mixed add_read_mess(mixed str, string type, string lang, int size) {
  int de_size;
  if (_cur_size >= _max_size) {
     return "";
  }
  if (!size) {
    size = 1;
  }
  de_size = size*((int)LANGUAGE_HAND->query_language_size(lang, str));
  if (_cur_size+de_size > _max_size) {
    str = (string)LANGUAGE_HAND->squidge_text(lang, str,
                                              (_max_size-_cur_size)/size);
    if (!strlen(str))
      return ;
    _cur_size += size*((int)LANGUAGE_HAND->query_language_size(lang, str));
  }
  _read_mess += ({ ({ str, type, lang, size }) });
  return str;
}
int remove_read_mess(string str, string type, string lang) {
  int i;
  for (i=0;i<sizeof(_read_mess);i++) {
    if (str && _read_mess[i][READ_STR] != str)
      continue;
    if (type && _read_mess[i][READ_TYPE] != type)
      continue;
    if (lang && _read_mess[i][READ_LANG] != lang)
      continue;
    _cur_size -= _read_mess[i][READ_SIZE]
                *((int)LANGUAGE_HAND->query_language_size(lang,
                                                    _read_mess[i][READ_STR]));
    _read_mess = _read_mess[0..i - 1] + _read_mess[i + 1..];
    return 1;
  }
  return 0;
}
string query_readable_message(object player, int ignore_labels) {
  string message;
  string file;
  string type;
  string lang;
  mixed mess;
  mixed *bit;
  mixed *read_mess;
  int pos;
  if(!player)
    player = this_player();
  read_mess = query_read_mess();
  if ( !sizeof( read_mess ) ) {
    return 0;
  }
  message = "";
  foreach ( bit in read_mess ) {
    mess = bit[ READ_MESS ];
    type = bit[ READ_TYPE ];
    lang = bit[ READ_LANG ];
    if ( functionp( mess ) ) {
      mess = evaluate( mess );
    }
    if ( stringp( mess ) ) {
      if ( sscanf( mess, "$$%s$$", file ) ) {
        mess = unguarded( (: read_file, file +".txt" :) );
        if ( !mess ) {
          mess = unguarded( (: NROFF_HAND->cat_file($(file)+"_nroff", 1) :) );
          if(!mess) {
            unguarded((: NROFF_HAND->create_nroff($(file),
                                                  $(file)+"_nroff") :));
            mess = unguarded((: NROFF_HAND->cat_file($(file)+"_nroff", 0) :));
            if(!mess)
              mess = "Warning: text file cannot be read!";
          }
        }
      }
    }
    mess = LANGUAGES->garble_text(lang, mess, this_object(), player);
#ifdef DISABLED
    if (stringp(mess)) {
      pos = strsrch(mess, "Written in ");
      while (pos != -1) {
        if ((pos == 0 && !type) || (pos > 0 && mess[pos-1] == '\n')) {
          mess = mess[0..pos-1] + "---> " + mess[pos..pos + 4] + " " +
            mess[pos + 5..];
        } else {
          mess = mess[0..pos + 4] + " " +
            mess[pos + 5..];
        }
        pos = strsrch(mess[pos + 5..], "Written in ");
      }
    }
#endif
    if ( !LANGUAGES->query_language_magic( lang ) ) {
      if ( !type && player && (lang == player->query_default_language())) {
        mess += "\n";
      } else {
        if (stringp(lang)) {
          mess = "Written"+ ( type ? " in "+ type : "" ) +
            ( lang != "general" ? " in "+ capitalize(lang) : "" ) +
            ": "+ mess +"\n";
        } else {
          mess = "Written in some weird broken language: " + mess + "\n";
        }
      }
    }
    message += mess;
  }
  return message;
}
string query_read_short(object player, int ignore_labels) {
   string id;
   string *read_mess;
   read_mess = query_read_mess();
   if ( !arrayp(read_mess) || !sizeof( read_mess ) ) {
      return 0;
   }
   id = query_property("read id");
   if (id) {
      id += " $name$";
   } else {
      id = "$name$";
   }
   return id;
}