#include <am_time.h>
#include <situations.h>
#define RANDOM(a,b) ("/obj/handlers/random_num.c"->random(a,b))
class situation_timing {
  mixed label;
  mixed duration;
  mixed when;
  int chance;
  int *endat;
  mixed background;
  mixed category;
  int it;
  mapping it_data;
}
nosave int offset;
nosave string *els;
nosave mixed *currentsits,*autosits;
nosave mapping sitdata;
nosave mapping sitwords;
nosave class situation_timing *sittiming;
nosave int chatmin=60,chatmax=120;
nosave object ownerroom;
nosave int automate=0;
nosave mixed cco;
varargs mixed change_situation( mixed label, mixed duration,
  mixed words, mixed handle );
object set_room(object room_o) {
  ownerroom=room_o;
  return this_object();
}
object query_room() { return ownerroom; }
void choose_words( mixed label, mixed choice )
{
  int i;
  class situation sit;
  string *wc;
  sit = sitdata[ label ];
  if (sizeof(sit->random_words)) {
    if (!sitwords) sitwords= ([ ]);
    if (intp(choice)) {
      wc=({ });
      for (i=0;i<sizeof(sit->random_words);i++) {
        wc+=({ "#"+(i+1),
          ((sit->random_words)[i])[
          RANDOM(sizeof((sit->random_words)[i]),choice+i*3347483647)] });
      }
      sitwords[label] = wc;
    }
    else
      sitwords[label] = choice;
  }
}
string *insert_words_chats(class situation sit, string *words) {
  string *outarray=({ });
  string s1;
  if (!sizeof(sit->chats)) return ({ });
  foreach (s1 in sit->chats) outarray+= ({ replace(s1,words) });
  return outarray;
}
mixed *insert_words_items(class situation sit, string *words) {
  mixed *outarray=({ });
  mixed ai,e0,e1;
  if (!sizeof(sit->add_items)) return ({ });
  foreach (ai in sit->add_items) {
    if (sizeof(ai)>=2) {
      e0=ai[0];
      if (arrayp(e0)) e0=explode(lower_case(replace(implode(e0,"|"),words)),"|");
      else e0=lower_case(replace(e0,words));
      e1=ai[1];
      if (arrayp(e1)) e1=explode(replace(implode(e1,"|"),words),"|");
      else e1=replace(e1,words);
      ai = ({ e0,e1 })+ai[2..];
    }
    outarray+= ({ ai });
  }
  return outarray;
}
int query_status() { return automate; }
int *query_current_situations() { return ({ currentsits, autosits }); }
mixed *query_sittiming() { return sittiming; }
mapping query_situations() { return sitdata; }
void dest_me() {
  destruct(this_object());
}
int clean_up( int parent ) {
  if (parent) {
    return 0;
  }
  return 1;
}
void add_situation( mixed label, class situation sit ) {
  if (!sizeof(sitdata)) {
    sitdata= ([ label : sit ]);
    sitwords= ([ ]);
  }
  else {
    sitdata+= ([ label : sit ]);
  }
}
void start_situation(mixed label, int do_start_mess) {
  class situation sdata;
  string *chats;
  mixed item,*items;
  object chatter;
  string *words;
  sdata=sitdata[ label ];
  words=sitwords[ label ];
  if (!currentsits) currentsits=({ label });
  else currentsits=currentsits+({ label });
  if (sizeof(sdata->extra_look)) {
    if (els && sizeof(els))
      els+=({ replace(sdata->extra_look,words) });
    else {
      els=({ replace(sdata->extra_look,words) });
      ownerroom->add_extra_look(this_object());
    }
  }
  if (do_start_mess && sizeof(sdata->start_mess))
    tell_room(ownerroom, replace(sdata->start_mess,words)+"\n");
  chats=insert_words_chats(sdata,words);
  if (chats && sizeof(chats)) {
    if (!(chatter=ownerroom->query_chatter())) {
      if (sdata->chat_rate) {
        ownerroom->room_chat( ({ chatmin,chatmax, ({ }) }),
                      clone_object("/std/room/basic/multichatter")  );
        chatter=ownerroom->query_chatter();
        chatter->setup_chatter( ownerroom,
        ({ (sdata->chat_rate)[0],(sdata->chat_rate)[1], chats }) );
      } else {
        ownerroom->room_chat( ({ chatmin,chatmax, chats }) );
        chatter=ownerroom->query_chatter();
      }
      chatter->check_chat();
    } else {
      if (sdata->chat_rate) {
        if (!(chatter->query_multichatter())) {
          mixed *args;
          args=(chatter->query_room_chats())[0..2];
          chatter->dest_me();
          ownerroom->room_chat( args,
                        clone_object("/std/room/basic/multichatter")  );
          chatter = ownerroom->query_chatter();
        }
        chatter->setup_chatter( ownerroom,
          ({ (sdata->chat_rate)[0],(sdata->chat_rate)[1], chats }) );
        chatter->check_chat();
      }
      else chatter->add_room_chats(chats);
    }
  }
  items=insert_words_items(sdata,words);
  if (sizeof(items)) {
    foreach(item in items) {
      ownerroom->add_item(item[0],item[1]);
    }
  }
  if (sdata->start_func) {
    (*(sdata->start_func))(label,do_start_mess,ownerroom);
  }
}
void end_situation(mixed label) {
  class situation sdata;
  string *chats;
  mixed item,*items;
  object chatter;
  string *words;
  sdata=sitdata[ label ];
  words=sitwords[ label ];
  if (currentsits) currentsits=currentsits-({ label });
  if (els && sizeof(sdata->extra_look)) {
    els-=({ replace(sdata->extra_look,words) });
    if (!sizeof(els)) ownerroom->remove_extra_look(this_object());
  }
  chats=insert_words_chats(sdata,words);
  if (chats && sizeof(chats) && (chatter=ownerroom->query_chatter())) {
    chatter->remove_room_chats(chats);
  }
  items=insert_words_items(sdata,words);
  if (sizeof(items)) {
    foreach(item in items) {
      if (arrayp(item[0]))
        ownerroom->remove_item((item[0])[0]);
      else
        ownerroom->remove_item(item[0]);
    }
  }
  if (sizeof(sdata->end_mess))
    tell_room(ownerroom,replace(sdata->end_mess,words)+"\n");
  if (sdata->end_func) {
    (*(sdata->end_func))(label,ownerroom);
  }
}
varargs mixed change_situation( mixed label, mixed duration,
     mixed words, mixed handle  ) {
  mixed frog,bing;
  mixed ending;
  if (!cco) cco=({ 1, 0 });
  if (!handle) {
    handle=member_array(0,cco[1..<1])+1;
    if (!handle) {
      cco+=({ 0 });
      handle=sizeof(cco)-1;
    }
  }
  cco[0]=handle;
  if (!duration) {
    if (arrayp(label)) frog=label[0];
    else frog=label;
    if (stringp(frog)) frog=explode(frog,",");
    else frog=({ frog });
    foreach(bing in frog) end_situation(bing);
    cco[handle]=0;
    return 0;
  }
  if (!arrayp(duration)) {
    if (arrayp(label)) {
      bing=duration/sizeof(label);
      duration=({ });
      foreach (frog in label) duration+=({ bing });
    }
    else duration=({ duration });
  }
  if (arrayp(label) && sizeof(label)>1 && sizeof(label)>sizeof(duration)) {
    frog=label[0];
    if (stringp(frog)) ending=explode(frog,",");
    else ending=({ frog });
    label=label[1..<1];
  }
  if (sizeof(duration)==1) {
    if (arrayp(label)) frog=label[0];
    else frog=label;
    if (stringp(frog)) frog=explode(frog,",");
    else frog=({ frog });
    if (ending) {
      ending-=frog;
      foreach(bing in ending) end_situation(bing);
    }
    if (currentsits) frog=frog-currentsits;
    foreach(bing in frog) {
      if (!sizeof(words)) choose_words( bing, time()*335423611 );
      else choose_words( bing, words );
      start_situation(bing,1);
    }
    if (duration[0]!=-1)
      cco[handle]=call_out("change_situation",duration[0],
                           label,0,words,handle);
    return handle;
  }
  if (arrayp(label)) frog=label[0];
  else frog=label;
  if (stringp(frog)) frog=explode(frog,",");
  else frog=({ frog });
  if (ending) {
    ending-=frog;
    foreach(bing in ending) end_situation(bing);
  }
  if (currentsits) frog=frog-currentsits;
  foreach(bing in frog) start_situation(bing,1);
  if (duration[0]!=-1)
    cco[handle]=
    call_out("change_situation",duration[0],
             label,duration[1..<1],words,handle);
  return handle;
}
int query_possible(class situation_timing sit, int it, int tod, int cnt)
{
  int possible;
  class situation_timing sit2;
  int cnt2,it2,tod2,possible2;
  if (functionp(sit->when)) possible=(*(sit->when))(tod);
  else possible=sit->when;
  possible=
    (possible&(1<<((AM_TIME_HANDLER)->query_am_hour(tod))))
    &&
    (RANDOM(1000,it*1147483647+cnt*2047483243) < sit->chance);
  if (possible && sit->category) {
    cnt2=0;
    foreach (sit2 in sittiming) {
      cnt2++;
      if (cnt2!=cnt && sit2->category == sit->category) {
	it2=(tod+offset+(cnt2*234231))/sit2->duration;
	tod2=it2*sit2->duration-offset-(cnt2*234231);
	if (functionp(sit2->when)) possible2=(*(sit2->when))(tod2);
	else possible2=sit2->when;
	possible2=
	  (possible2&(1<<((AM_TIME_HANDLER)->query_am_hour(tod2))))
	  &&
	  (RANDOM(1000,it2*1147483647+cnt2*2047483243) < sit2->chance);
	if (possible2 && (tod2<tod || (tod==tod2 && cnt2<cnt))) {
	  possible=0;
	  break;
	}
      }
    }
  }
  return possible;
}
void manage_situations() {
  class situation_timing sit;
  int t,t0,it,tod,cnt,possible,dt,tc,i;
  mixed label,lb;
  mixed *newsits;
  mixed *changes;
  mixed *background_on,*background_off;
  int ttmp,tstep;
  if (!automate) return;
  if (!sizeof(filter_array( all_inventory( ownerroom ),(: interactive($1) :)))) {
    automate=2;
    return;
  }
  t0=time()+offset;
  newsits=({});
  tstep=2147483648;
  background_on=({ });
  background_off=({ });
  cnt=0;
  foreach (sit in sittiming) {
    cnt++;
    t=t0+(cnt*234231);
    ttmp=sit->duration;
    it=t/ttmp;
    tod=it*ttmp-offset-(cnt*234231);
    possible=sit->it_data[ it ];
    if (undefinedp(possible)) {
      possible=query_possible(sit, it, tod, cnt);
      sit->it_data[ it ]=possible;
      if (!undefinedp(sit->it_data[ it-1 ]))
	map_delete(sit->it_data,it-1);
    } else {
    }
    if (possible) {
      if (sit->background) background_off+=explode(sit->background,",");
      if (arrayp(sit->label)) {
	dt=(t % ttmp);
	i=0;
	foreach (tc in sit->endat) {
	  if (tc>dt) break;
	  i++;
	}
	label=(sit->label)[i];
	ttmp=tc-dt;
      }
      else label=sit->label;
      if (stringp(label)) {
	label=explode(label,",");
	newsits=newsits+label;
	foreach(lb in label) choose_words(lb,it*1147483647+cnt*2047555777);
      }
      else {
	newsits=newsits+({ label });
	choose_words(label,it*1147483647+cnt*2047555777);
      }
    }
    else {
      if (sit->background) background_on+=explode(sit->background,",");
      possible=sit->it_data[ it+1 ];
      if (undefinedp(possible)) {
	possible=query_possible(sit, it+1, tod+sit->duration, cnt);
	sit->it_data[ it+1 ]=possible;
	if (!undefinedp(sit->it_data[ it-1 ]))
	  map_delete(sit->it_data,it-1);
      }
      if (possible)
	ttmp=ttmp-(t % ttmp);
      else
	ttmp=2*ttmp-(t % ttmp);
    }
    if (ttmp<tstep) tstep=ttmp;
  }
  call_out("manage_situations",tstep+1);
  newsits = newsits+(background_on-background_off);
  if (autosits && sizeof(autosits)) {
    changes=autosits-newsits;
    if (sizeof(changes)) {
      foreach(label in changes) end_situation(label);
      autosits=autosits-changes;
    }
    changes=newsits-autosits;
  }
  else changes=newsits;
  if (sizeof(changes)) {
    foreach(label in changes) start_situation(label,2-automate);
    if (autosits) autosits=autosits+changes;
    else autosits=changes;
  }
  automate=1;
}
void check_situations() {
  if (automate==2 && interactive(this_player())) manage_situations();
}
void make_seed(int xval, int yval) {
  offset=(xval*38547+yval*1232444311)>>2;
}
void automate_situation( mixed label, mixed duration, mixed when, mixed chance,
     mixed category ) {
  mixed chatargs,endat,background,labels;
  int i,d;
  string ook;
  if (!offset) {
    ook=file_name(ownerroom);
    if (!ook || ook=="") {
      write( "Bad file name" );
      return;
    }
    offset=1;
    foreach (i in ook) offset*=i;
    offset=(offset>>2)+1;
  }
  if (ownerroom->query_chatter()) {
    chatargs=(ownerroom->query_chatter())->query_room_chats();
    if (sizeof(chatargs)==3) {
      chatmin=chatargs[0];
      chatmax=chatargs[1];
    }
  }
  endat=({ });
  if (arrayp(duration)) {
    if (!arrayp(label) || sizeof(duration)!=sizeof(label)) {
      write("Duration must be an array of the same length as label");
      return;
    }
    d=0;
    labels=({ });
    for (i=0;i<sizeof(duration);i++) {
      if (duration[i]!=-1) {
	d+=duration[i];
        endat+=({ d });
	labels=labels+({ label[i] });
      }
      else {
	if (background) background=implode(explode(background,",")+({ label[i] }),",");
        else background=label[i];
      }
    }
  } else {
    labels=label;
    d=duration;
    if (arrayp(label)) {
      for (i=0;i<sizeof(label);i++) {
        endat+=({ ((i+1)*duration)/sizeof(label) });
      }
    } else {
      endat=({ duration });
    }
  }
  if (!sittiming)
    sittiming=
      ({ new(class situation_timing, label: labels, duration: d,
             when: when, chance: chance, endat: endat, background: background,
             category: category, it: 0, it_data: ([ ]) ) });
  else
    sittiming=sittiming+
      ({ new(class situation_timing, label: labels, duration: d,
             when: when, chance: chance, endat: endat, background: background,
             category: category, it: 0, it_data: ([ ]) ) });
  automate=2;
}
void shutdown_all_situations() {
  int label;
  mixed h;
  if (sizeof(cco)>1) {
    foreach (h in cco[1..<1]) {
       if (h) remove_call_out(h);
    }
  }
  cco=({ 0 });
  if (currentsits && sizeof(currentsits)) {
    foreach(label in currentsits) end_situation(label);
  }
  autosits=0;
  automate=0;
}
void shutdown_situation(int handle, mixed label) {
  mixed frog,bing;
  if (sizeof(cco)) {
    if (!handle) handle=cco[0];
    if (handle && cco[handle]) remove_call_out(cco[handle]);
    cco[handle]=0;
  }
  if (arrayp(label)) {
    frog=({ });
    foreach(bing in label) {
      if (stringp(bing)) frog+=explode(bing,",");
      else frog+=({ bing });
    }
  }
  else if (stringp(label)) label=explode(label,",");
  else label=({ label });
}
string extra_look() {
  if (!els || !sizeof(els)) {
    return "";
  }
  return implode(els,"  ")+"\n";
}