#include <am_time.h>
#include <situations.h>
#define RANDOM(a,b) ("/obj/handlers/random_num.c"->random(a,b))
#define MIN_DURATION  1
#define SECTOCHECK    15
#define INSTALLDELAY  15
#define MAXROOMS      30
nosave mapping roominfo;
nosave mixed *rooms;
nosave mapping sitdata;
int query_status() { return 1; }
int *query_current_situations(object room)
{
  if (!roominfo[file_name(room)]) return 0;
  return (roominfo[file_name(room)])[0];
}
void dest_me() {
  destruct(this_object());
}
void add_situation(int num, function *func, string startmess, string endmess,
                   string extralookstring, string *chats, mixed *add_items ) {
  if (!sizeof(sitdata))
    sitdata= ([ num :
              ({ startmess, endmess, extralookstring, chats, add_items, func }) ]);
  else
    sitdata+= ([ num :
               ({ startmess, endmess, extralookstring, chats, add_items, func }) ]);
}
void start_situation(int num, int do_start_mess, object room) {
  mixed *sdata;
  string *chats;
  mixed item,*items;
  int *currentsits;
  string *els;
  object chatter;
  if (!(sdata=sitdata[num]) || !room) return;
  if (!roominfo[file_name(room)]) roominfo[file_name(room)]=
                 ({ 0,0,0,0,60,120,1 });
  currentsits=(roominfo[file_name(room)])[0];
  els=(roominfo[file_name(room)])[1];
  if (!currentsits) currentsits=({ num });
  else currentsits=currentsits+({ num });
  if (sizeof(sdata[2])) {
    if (els && sizeof(els)) els+=({ sdata[2] });
    else {
      els=({ sdata[2] });
      room->add_extra_look(this_object());
    }
  }
  if (do_start_mess && sizeof(sdata[0]))
    tell_room(room, sdata[0]+"\n");
  chats=sdata[3];
  if (chats && sizeof(chats)) {
    if (!(chatter=room->query_chatter())) {
      room->room_chat( ({ (roominfo[file_name(room)])[4],(roominfo[file_name(room)])[5], chats }) );
      chatter=room->query_chatter();
      chatter->check_chat();
    }
    else chatter->add_room_chats(chats);
  }
  items=sdata[4];
  if (sizeof(items)) {
    foreach(item in items) room->add_item(item[0],item[1]);
  }
  if (sdata[5]) {
    if (functionp(sdata[5])) (*(sdata[5]))(num,do_start_mess);
    else if (arrayp(sdata[5]) && functionp((sdata[5])[0]))
      (*((sdata[5])[0]))(num,do_start_mess);
  }
  (roominfo[file_name(room)])[0]=currentsits;
  (roominfo[file_name(room)])[1]=els;
}
void end_situation(int num, object room) {
  mixed *sdata;
  string *chats;
  mixed item,*items;
  int *currentsits;
  string *els;
  object chatter;
  if (!(sdata=sitdata[num]) || !room) return;
  if (!roominfo[file_name(room)]) return;
  currentsits=(roominfo[file_name(room)])[0];
  els=(roominfo[file_name(room)])[1];
  if (currentsits) currentsits=currentsits-({ num });
  if (els && sizeof(sdata[2])) {
    els-=({ sdata[2] });
    if (!sizeof(els)) room->remove_extra_look(this_object());
  }
  chats=sdata[3];
  if (chats && sizeof(chats) && (chatter=room->query_chatter())) {
    chatter->remove_room_chats(chats);
  }
  items=sdata[4];
  if (sizeof(items)) {
    foreach(item in items) room->remove_item(item[0],item[1]);
  }
  if (sizeof(sdata[1]))
    tell_room(room,sdata[1]+"\n");
  if (sdata[5]) {
    if (arrayp(sdata[5]) && functionp((sdata[5])[1]))
      (*((sdata[5])[1]))(num);
  }
  (roominfo[file_name(room)])[0]=currentsits;
  (roominfo[file_name(room)])[1]=els;
}
void manage_situations(object room) {
  mixed *sit;
  int num,t,it,cnt,possible;
  int *currentsits,*newsits,*changes;
  int ttmp,tstep,offset,awake;
  mixed data;
  if (!room || !(data=roominfo[file_name(room)])) return;
  if (!sizeof(filter_array( all_inventory( room ),(: interactive($1) :)))) {
    (roominfo[file_name(room)])[6]=0;
    return;
  }
  currentsits=data[0];
  offset=data[2];
  awake=data[6];
  t=time()+offset;
  newsits=({});
  tstep=2147483647;
  cnt=0;
  foreach(sit in data[3]) {
    cnt++;
    ttmp=sit[1];
    it=t/ttmp;
    possible=0;
    if (sit[2]) {
      if (functionp(sit[2])) possible=(*(sit[2]))();
      else possible=sit[2];
      possible=
	(possible&(1<<((AM_TIME_HANDLER)->query_am_hour(it*ttmp-offset))))
	&&
	(RANDOM(1000,it*1147483647+cnt*2047483243) < sit[3]);
    }
    if (possible) {
      if (arrayp(sit[0])) {
	num=(sit[0]) [((t % ttmp)*sizeof(sit[0]))/ttmp];
	ttmp=ttmp/sizeof(sit[0]);
      }
      else num=sit[0];
      if (member_array(num,newsits)==-1) newsits=newsits+({ num });
    }
    if (ttmp<tstep) tstep=ttmp;
  }
  if (currentsits && sizeof(currentsits)) {
    changes=currentsits-newsits;
    if (sizeof(changes)) foreach(num in changes) {
      if (awake) call_out("end_situation",random(INSTALLDELAY),
        num,room);
      else end_situation(num,room);
    }
    changes=newsits-currentsits;
    }
  else changes=newsits;
  if (sizeof(changes)) foreach(num in changes) {
    if (awake) call_out("start_situation",random(INSTALLDELAY),
       num,awake,room);
    else start_situation(num,awake,room);
  }
  if ((tstep/=SECTOCHECK)>=MAXROOMS) tstep=MAXROOMS-1;
  if (!rooms[tstep]) rooms[tstep]=({ room });
  else rooms[tstep]=rooms[tstep]+({ room });
  (roominfo[file_name(room)])[6]=1;
}
void manage_rooms_situations() {
  object room,*current_rooms;
  current_rooms = rooms[ 0 ];
  rooms[ 0 .. <2 ] = rooms[ 1 .. <1 ];
  rooms[ <1 ] = 0;
  call_out("manage_rooms_situations",SECTOCHECK);
  if ( !pointerp( current_rooms ) ) return;
  foreach ( room in current_rooms ) manage_situations(room);
}
void check_situations(object room) {
  if (room && roominfo[file_name(room)]
    && !((roominfo[file_name(room)])[6])
    && interactive(this_player())) manage_situations(room);
}
void automate_situations(mixed *chatargs, int xval, int yval, mixed *edata,
  object room) {
  mixed sit;
  mixed *sittiming;
  int offset;
  offset=xval*38547+yval*1232444311;
  if ( pointerp(chatargs[2]) && sizeof(chatargs[2])) {
    room->room_chat( chatargs );
  }
  if (sizeof(edata)) {
    foreach(sit in edata) {
      if (sit[1]<MIN_DURATION) {
        write("Invalid situation duration: "+sit[1]+"\n");
        return;
      }
      sit[1]*=60;
      if (!sittiming) sittiming=({ sit });
      else sittiming=sittiming+({ sit });
    }
  }
  roominfo[file_name(room)]=({  0,0, offset, sittiming,
       chatargs[0], chatargs[1], 0 });
  manage_situations(room);
}
void shutdown_situations(object room) {
  int num, *currentsits;
  currentsits=(roominfo[file_name(room)])[0];
  if (currentsits && sizeof(currentsits)) {
    foreach(num in currentsits) end_situation(num, room);
  }
}
string extra_look(object room) {
  string *els;
  if (!roominfo[file_name(room)]) return "";
  els=(roominfo[file_name(room)])[1];
  if (!els || !sizeof(els)) {
    return "";
  }
  return implode(els,"  ")+"\n";
}
void create() {
   rooms = allocate( MAXROOMS );
   manage_rooms_situations();
   roominfo= ([ ]);
}
object *query_rooms() { return rooms; }