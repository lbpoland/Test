#pragma strict_types
#include <board.h>
#include <comms.h>
#include <mail.h>
#include <network.h>
#include <mime.h>
#include <player_handler.h>
#define MAIL_PATH "/save/mail/"
int *mesg_numbers;
class mail_header *info;
int new_thingy;
nosave int link;
class mail_header *get_messages(string pname, string fname);
string load_message(string pname, string fname, int number);
void delete_it(string pname, string fname, int *deleted);
string check_local(string arg);
private int load_counter();
private void save_counter(int counter);
void dest_me();
void delete_account(string player);
void create() {
  seteuid("Mailer");
}
private string folder_filename(string name) {
  if(file_size(MAIL_PATH + name) != -1) {
    unguarded((: rename, MAIL_PATH + name,
         MAIL_PATH + name[0..0] + "/" + name :));
  } else if(file_size(MAIL_PATH + name + ".o") != -1) {
    unguarded((: rename, MAIL_PATH + name + ".o",
         MAIL_PATH + name[0..0] + "/" + name + ".o" :));
  }
  return MAIL_PATH+name[0..0] + "/"  + name;
}
private string message_filename(int num, string prefix) {
  if(file_size(MAIL_PATH+"new_mesg/" + (num % 50)) == -1) {
    unguarded((: mkdir, MAIL_PATH+"new_mesg/" + (num % 50) :));
  }
  if(file_size(MAIL_PATH+"new_mesg/"+(num % 50)+"/"+((num / 50) % 50)) == -1) {
    unguarded((: mkdir, MAIL_PATH+"new_mesg/" + (num %50) + "/" +
         ((num / 50) % 50) :));
  }
#ifdef 0
  if(file_size(MAIL_PATH + "mesg/" + prefix + num) != -1) {
    unguarded((: rename, MAIL_PATH + "mesg/" + prefix + num,
     MAIL_PATH+"new_mesg/"+ (num % 50) + "/" + ((num / 50) % 50) +
     "/" + prefix + num :));
  }
#endif
  return MAIL_PATH+"new_mesg/"+  (num % 50) + "/" + ((num / 50) % 50) +
    "/" + prefix + num;
}
nomask int can_create_folder(string player, string folder) {
    return file_size(folder_filename(player) + folder + ".o") == -1;
}
private void convert_links(int number) {
  string message;
  int tmplink;
  message = unguarded((: read_file, message_filename(number, "l"), 1, 1 :));
  if (!message || sscanf(message, "%d", tmplink) != 1) {
    return;
  }
  sscanf(message, "%d", tmplink);
  message = unguarded((: read_file, message_filename(number, "") :));
  unguarded((: rm, message_filename(number, "") :));
  unguarded((: rm, message_filename(number, "l") :));
  unguarded((: write_file, message_filename(number, ""),
               "" + tmplink + "\n" + message :));
}
private string query_message_data(int number) {
   string data;
   convert_links(number);
   data = unguarded((: read_file, message_filename(number, "") :));
   if(!data)
     return data;
   sscanf(data, "%*d\n%s", data);
   return data;
}
private void create_new_message(int number, string data, int links) {
   unguarded((: rm, message_filename(number, "") :));
   unguarded((: write_file, message_filename(number, ""),
                            "" +links + "\n" + data :));
}
private void increment_links(int number) {
  string message;
  int num_links;
  convert_links(number);
  message = unguarded((: read_file, message_filename(number, "") :));
  if (!message) {
     return ;
  }
  sscanf(message, "%d\n%s", num_links, message);
  num_links++;
  unguarded((: rm, message_filename(number, "") :));
  unguarded((: write_file, message_filename(number, ""),
               "" + num_links + "\n" + message :));
}
private void decrement_links(int number) {
  string message;
  int num_links;
  convert_links(number);
  message = unguarded((: read_file, message_filename(number, "") :));
  if (!message) {
     return ;
  }
  sscanf(message, "%d\n%s", num_links, message);
  num_links--;
  unguarded((: rm, message_filename(number, "") :));
  if (num_links > 0) {
     unguarded((: write_file, message_filename(number, ""),
                  "" + num_links + "\n" + message :));
  }
}
private int check() {
  string base;
  base = base_name(previous_object());
  if (base != "/obj/handlers/mailer" &&
      base != "/obj/handlers/folder_handler" &&
      base != "/obj/handlers/converter" &&
      base != "/net/daemon/pop3" &&
      base != "/net/daemon/imap4" &&
      base != "/secure/bulk_delete") {
    printf("Folder handler: Illegal access ! (%O)\n", base);
    return 1;
  } else
    return 0;
}
private void convert_class(string pname, string fname) {
  class mail_header hdr;
  int i;
  i = sizeof(info);
  while (i--) {
    hdr = new(class mail_header);
    hdr->number = ((mapping)info[i])["number"];
    hdr->status = ((mapping)info[i])["status"];
    hdr->subject = ((mapping)info[i])["subject"];
    hdr->from = ((mapping)info[i])["from"];
    info[i] = hdr;
  }
  unguarded((: save_object, folder_filename(lower_case(pname)+fname) :));
}
class mail_header *get_messages(string pname, string fname) {
  if (check())
    return ({ });
  mesg_numbers = ({ });
  info = ({ });
  new_thingy = 0;
  unguarded((: restore_object, folder_filename(lower_case(pname)+fname) :));
  if (sizeof(info) && mapp(info[0])) {
    convert_class(pname, fname);
  }
  return info;
}
string load_message(string pname, string fname, int number) {
  string message;
  if (check()) {
    return " ";
  }
  if (file_size(message_filename(number, "l")) > 0)  {
    convert_links(number);
  }
  message = query_message_data(number);
  if (!message) {
    printf("* Failed to load message.\n", number);
  }
  return message;
}
void delete_it(string pname, string fname, int *deleted) {
  int i, idx;
  if (check()) {
    return;
  }
  if (!PLAYER_HANDLER->test_user(pname)) {
    return;
  }
  if (sizeof(deleted) > 1) {
    deleted = uniq_array(deleted);
    deleted = sort_array(deleted, 1);
  }
  mesg_numbers = ({ });
  info = ({ });
  new_thingy = 0;
  unguarded((: restore_object, folder_filename(lower_case(pname)+fname) :));
  if (sizeof(info) && mapp(info[0])) {
    convert_class(pname, fname);
  }
  i = sizeof(deleted);
  while (i--) {
    reset_eval_cost();
    if ((idx = member_array(deleted[i], mesg_numbers)) > -1) {
      if (file_size(message_filename(mesg_numbers[idx], "l")) > 0) {
        convert_links(mesg_numbers[idx]);
      }
      decrement_links(mesg_numbers[idx]);
      mesg_numbers = delete(mesg_numbers, idx, 1);
      if (idx < sizeof(info) && info[idx] &&
          ((class mail_header)info[idx])->status == "N") {
        new_thingy--;
      }
      info = delete(info, idx, 1);
    }
  }
  unguarded((: save_object, folder_filename(lower_case(pname)+fname) :));
}
private void send_frog(object player, string to, string from) {
   object ob;
   if (!player || !environment(player)->send_message(to)) {
      catch(ob = clone_object(POST_FROG));
      write("A small frog with a post office hat wanders up and takes "
            "your mail.\n");
      say("A small frog with a post office hat wanders up to "+
          player->query_cap_name()+" and takes "+
          player->query_possessive()+" mail.\n");
      if (find_player(to) && sscanf(from, "%*s@%*s") == 2) {
        catch(ob->move(COMM_ROOM, ob->query_mmsgin(), ob->query_mmsgout()));
      } else {
        catch(ob->move(environment(player)));
      }
      catch(ob->send_mail(to, from));
   }
}
private void send_notification(string to,
                               string from) {
    if (find_player(from) ||
        sscanf(from, "%*s@%*s") == 2) {
       call_out((: send_frog :), 0, find_player(from), to, from);
    }
}
void add_it(class mail_message mesg, int flag) {
  int i, counter, bong, ptpost;
  string *local_to, *remote_to, *fail_to, str;
  class mail_header hdr;
  if (check()) {
    return;
  }
  if (sizeof(mesg->cc)) {
    mesg->to += mesg->cc;
  }
  mesg->to = MIME->get_email_addrs(implode(mesg->to, ","))[0];
  local_to = ({ });
  remote_to = ({ });
  fail_to = ({ });
  str = "";
  bong = sizeof(mesg->to);
  for (i = 0; i < bong; i++) {
    if ((str = check_local(mesg->to[i]))) {
      if (MAIL_TRACK->query_list(str)) {
        local_to += MAIL_TRACK->query_members(str) - ({ mesg->from });
        if ( str == "playtesters" ) {
          ptpost = 1;
        }
      } else {
        local_to += ({ str });
      }
    } else {
      remote_to += ({ mesg->to[i] });
    }
  }
  local_to = uniq_array(local_to);
  remote_to = uniq_array(remote_to);
  if ((i = sizeof(local_to))) {
    if (!(counter = load_counter())) {
      if (!flag) {
        printf("Aborting send of message...\n");
      }
      return;
    }
    if (file_size(message_filename(counter, "")) > 0) {
      if (!flag) {
        printf("Fatal error when sending message: File %d exists.\n"
               "Please contact Turrican.\n", counter);
      }
      return;
    }
    for (i = 0; i < sizeof(local_to); i++) {
      if (!flag) {
        printf("Sending to: %s.\n", capitalize(local_to[i]));
      }
      if(MAIL_TRACK->find_mailer(local_to[i]) ||
         PLAYER_HANDLER->test_user(local_to[i])) {
        mesg_numbers = ({ });
        info = ({ });
        new_thingy = 0;
        unguarded((: restore_object, folder_filename(local_to[i]+"inbox") :));
        if (sizeof(info) && mapp(info[0]))
          convert_class(local_to[i], "inbox");
        if(sizeof(mesg_numbers) > MAX_FOLDER_SIZE) {
          write("Sorry, mailbox is full for " + local_to[i] + ".\n");
          mesg->to -= ({ local_to[i] });
          mesg->cc -= ({ local_to[i] });
          local_to = delete(local_to, i--, 1);
          continue;
        }
        if(!PLAYER_HANDLER->test_active(local_to[i])) {
          write("Sorry, " + local_to[i] + " is inactive and so unable to "
                "receive mail.\n");
          mesg->to -= ({ local_to[i] });
          mesg->cc -= ({ local_to[i] });
          local_to = delete(local_to, i--, 1);
          continue;
        }
        mesg_numbers += ({ counter });
        new_thingy++;
        hdr = new(class mail_header);
        hdr->number = counter;
        hdr->status = "N";
        hdr->subject = mesg->subject;
        hdr->from = mesg->from;
        info += ({ hdr });
        if (!unguarded((: save_object, folder_filename(local_to[i]+"inbox") :))) {
          if (!flag) {
            printf("Couldn't save mailbox for %s...\n",
                   capitalize(local_to[i]));
          }
          mesg->to -= ({ local_to[i] });
          mesg->cc -= ({ local_to[i] });
          local_to = delete(local_to, i--, 1);
          continue;
        }
        if(this_player() && environment(this_player()))
          send_notification(local_to[i], mesg->from);
      } else {
        fail_to += ({ local_to[i] });
        mesg->to -= ({ local_to[i] });
        mesg->cc -= ({ local_to[i] });
        local_to = delete(local_to, i--, 1);
      }
    }
    if (i) {
      ++counter;
      save_counter(counter);
      create_new_message(counter - 1, mesg->body, i);
    }
  }
  if ((i = sizeof(fail_to))) {
    while (i--) {
      MAILER->do_mail_message(mesg->from, "postmaster", "Error! User "+
                              fail_to[i]+" unknown", 0,
                              "Original message included:\n\n> "+
                              replace_string(mesg->body, "\n", "\n> "), 1, 0);
    }
  }
  if (sizeof(remote_to) && !flag) {
    for (i = 0; i < sizeof(remote_to); i++) {
      sscanf(remote_to[i], "%*s@%s", str);
      if (str && INTERMUD_D->GetMudName(str)) {
        printf("Sorry, Intermud mail is not currently supported.  "
               "Didn't send mail to %s.\n", remote_to[i]);
        remote_to = delete(remote_to, i--, 1);
        continue;
      }
    }
    SMTP->eventSendMail(remote_to, mesg->from, mesg->body);
  }
  if (ptpost) {
    BOARD_HAND->add_message("playtesters", capitalize(mesg->from),
                            mesg->subject, sprintf( "%-=78s\n",
                            mesg->body ));
  }
}
void mark_read(string pname, string fname, int *unread) {
  int i;
  if (check()) {
    return;
  }
  if (!PLAYER_HANDLER->test_user(pname)) {
    return;
  }
  unread = uniq_array(unread);
  mesg_numbers = ({ });
  info = ({ });
  new_thingy = 0;
  unguarded((: restore_object, folder_filename(lower_case(pname)+fname) :));
  if (sizeof(info) && mapp(info[0])) {
    convert_class(pname, fname);
  }
  if (new_thingy == sizeof(unread)) {
    return;
  }
  new_thingy = 0;
  i = sizeof(mesg_numbers);
  while (i--) {
    if (member_array(i, unread) > -1) {
      ((class mail_header)info[i])->status = "N";
      new_thingy++;
    }
    else if(i < sizeof(info))
      ((class mail_header)info[i])->status = " ";
    else
      write("\nErk, problems. The arrays don't quite match.\n");
    reset_eval_cost();
  }
  unguarded((: save_object, folder_filename(lower_case(pname)+fname) :));
  new_thingy = 0;
}
int move_it(string pname, string from, string to, int number) {
  class mail_header tmphdr;
  if (check())
    return 1;
  mesg_numbers = ({ });
  info = ({ });
  new_thingy = 0;
  unguarded((: restore_object, folder_filename(lower_case(pname)+to) :));
  if (sizeof(info) && mapp(info[0])) {
    convert_class(pname, to);
  }
  if (member_array(number, mesg_numbers) > -1) {
    return 1;
  }
  if(sizeof(mesg_numbers) > MAX_FOLDER_SIZE) {
    return 2;
  }
  if (file_size(message_filename(number, "l")) > 0) {
    convert_links(number);
  }
  increment_links(number);
  mesg_numbers = ({ });
  info = ({ });
  new_thingy = 0;
  unguarded((: restore_object, folder_filename(lower_case(pname)+from) :));
  if (sizeof(info) && mapp(info[0])) {
    convert_class(pname, from);
  }
  tmphdr = info[member_array(number, mesg_numbers)];
  mesg_numbers = ({ });
  info = ({ });
  new_thingy = 0;
  unguarded((: restore_object, folder_filename(lower_case(pname)+to) :));
  mesg_numbers += ({ number });
  info += ({ tmphdr });
  if (tmphdr->status == "N") {
    new_thingy++;
  }
  unguarded((: save_object, folder_filename(lower_case(pname)+to) :));
  return 0;
}
int check_empty(string pname, string fname) {
  mesg_numbers = ({ });
  info = ({ });
  new_thingy = 0;
  unguarded((: restore_object, folder_filename(lower_case(pname)+fname) :));
  if (!sizeof(mesg_numbers)) {
    unguarded((: rm, folder_filename(lower_case(pname)+fname)+".o" :));
    return 1;
  }
  return 0;
}
string check_local(string str) {
  string name;
  if (sscanf(lower_case(str),
             "%*([\n \t]*([ \t!-;=?-~]+<)?)%([A-Za-z]+)"
             "%*((.discworld(@|$))|$)",
             name) == 3) {
    return name;
  }
  return 0;
}
int *mail_count(string pname) {
  int num;
  mesg_numbers = ({ });
  info = ({ });
  new_thingy = 0;
  unguarded((: restore_object, folder_filename(pname+"inbox") :));
  if(sizeof(info) && mapp(info[0]))
    convert_class(pname, "inbox");
  num = sizeof(mesg_numbers);
  if (!mesg_numbers || !num)
    return ({ 0, 0 });
  return ({ num, new_thingy});
}
string finger_mail(string pname) {
  string ret;
  int *tmp;
  tmp = mail_count(pname);
  if(!tmp[0])
    return "No mail.\n";
  if (tmp[0] == 1) {
    ret = "1 mail message";
  } else {
    ret = tmp[0] + " mail messages";
  }
  if(tmp[1] <= 0)
    ret += ".\n";
  else
    ret += ", " + tmp[1] + " of them unread.\n";
  return ret;
}
string check_mail(string pname) {
  int *tmp;
  string ret;
  tmp = mail_count(pname);
  switch(tmp[1]) {
  case 0:
    ret = "";
    break;
  case 1:
    ret = "\nYou have %^YELLOW%^1 NEW%^RESET%^ mail message.  Go to a "
      "post office to read it.\n\n";
    break;
  default:
    ret = "\nYou have %^YELLOW%^" + tmp[1] + " NEW%^RESET%^ mail messages.  "
      "Go to a post office to read them.\n\n";
  }
  if(tmp[0] > MAX_FOLDER_SIZE) {
    ret = "\n%^BOLD%^%^RED%^You have " + tmp[0] + " messages in your inbox.  "
      "You will receive no more mail until this number is reduced below "
      "acceptable limits.%^RESET%^" + ret;
  } else if(tmp[0] > WARN_FOLDER_SIZE) {
    ret = "\n%^BOLD%^%^RED%^You have " + tmp[0] + " messages in your inbox.  "
      "This is far too many.\n  Please delete some immediately!%^RESET%^" +
      ret;
  }
  return ret;
}
private void save_counter(int counter) {
  if (check())
    return;
  unguarded((: rm, MAIL_PATH+"counter.save" :));
  unguarded((: rename, MAIL_PATH+"counter", MAIL_PATH+"counter.save" :));
  unguarded((: write_file, MAIL_PATH+"counter", ""+counter :));
}
private int load_counter() {
  string bing;
  int ret;
  if (check()) {
    return 0;
  }
  if (bing = unguarded((: read_file, MAIL_PATH+"counter" :))) {
    sscanf(bing, "%d", ret);
  } else {
    printf("The mail counter was lost. Please contact Turrican.\n");
    return 0;
  }
  return ret;
}
void set_counter(int x) {
  if(file_size(message_filename(x, "")) > 0) {
    printf("Invalid counter value: File exists.\n");
    return;
  }
  save_counter(x);
}
void dest_me() {
  destruct(this_object());
}
void delete_account(string pname) {
  string folder;
  string *folders;
  int message;
  object mailer;
  if(previous_object() != find_object( "/secure/related_files") &&
     previous_object() != find_object( "/secure/bulk_delete"))
    return;
  mailer = clone_object(MAILER);
  folders = (string *)mailer->query_folders(pname);
  destruct(mailer);
  if (!folders && file_size(folder_filename(pname+"inbox.o")) == -1)
    return;
  if (!folders)
    folders = ({"inbox"});
  foreach (folder in folders) {
    mesg_numbers = ({ });
    unguarded( (: restore_object, folder_filename(pname+folder) :) );
    if (pointerp(mesg_numbers)) {
      foreach (message in mesg_numbers) {
        reset_eval_cost();
        if (file_size(message_filename(message, "l")) > 0) {
          convert_links(message);
        }
        decrement_links(message);
      }
    }
    unguarded( (: rm, folder_filename(pname + folder + ".o") :) );
  }
  unguarded( (: rm, folder_filename(pname +".o") :) );
}