#define SAVE "/save/hist_handler.o"
#define MAX_HIS 20
#define HISTORY_TIME (3600*24*2)
mapping history;
mixed *query_lord_history();
void add_lord_history( string start, string mess );
void create() {
  seteuid(master()->get_root_uid());
  history = ([]);
  if(!unguarded((: restore_object, SAVE+".gz" :)))
    unguarded((: restore_object, SAVE :));
  call_out("tidy_history", 2);
}
void save_me() {
  unguarded((: save_object, SAVE, 2 :));
}
void add_cre_history(string start, string mess) {
  mixed *cre_history = history["cre"];
  if (undefinedp(history["cre"]))
    cre_history = ({ ({ start, mess, time() }) });
  else
    cre_history += ({ ({ start, mess, time() }) });
  if (sizeof(cre_history) > MAX_HIS)
    cre_history = cre_history[1..];
  history["cre"] = cre_history;
}
mixed *query_cre_history() {
  return history["cre"];
}
void add_chat_history(string channel, string start, string mess) {
  mixed *chat_history = history[channel];
  if ( !chat_history ) {
    chat_history = ({ });
  }
  if (channel == "lord")   {
    add_lord_history( start, mess );
    return;
  } else {
    chat_history += ({ ({ start, mess, time() }) });
  }
  if (sizeof(chat_history) > MAX_HIS) {
    chat_history = chat_history[1..];
  }
  history[channel] = chat_history;
}
mixed *query_chat_history(string channel) {
  if (channel == "lord")
    return query_lord_history();
  return history[channel];
}
void add_lord_history(string start, string mess) {
  mixed *lord_history = history["lord"];
  if (!master()->query_lord(previous_object(-1)))
    return;
  if (undefinedp(history["lord"]))
    lord_history = ({ ({ start, mess, time() }) });
  else
    lord_history += ({ ({ start, mess, time() }) });
  if (sizeof(lord_history) > MAX_HIS)
    lord_history = lord_history[1..];
  history["lord"] = lord_history;
}
mixed *query_lord_history() {
  if (!master()->query_lord(previous_object(-1)))
    return ({ });
  return history["lord"];
}
void dest_me() {
  save_me();
  destruct(this_object());
}
void reset() {
  save_me();
}
void tidy_history() {
  string channel;
  int i;
  foreach(channel in keys(history)) {
    for(i = 0; i<sizeof(history[channel]); i++)
      if(history[channel][i][2] < time() - HISTORY_TIME) {
  history[channel] = history[channel][1..];
      } else
  break;
    if(!sizeof(history[channel]))
      map_delete(history, channel);
  }
  save_object(SAVE, 2);
}
void reset_history() {
  if (!master()->high_programmer(previous_object(-1)))
    return;
  history = ([]);
  save_object(SAVE, 2);
}