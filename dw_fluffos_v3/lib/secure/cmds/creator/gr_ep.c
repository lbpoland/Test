inherit "/cmds/base";
#include <creator.h>
mapping globals = ([]), files = ([]), ret = ([]);
#define TP globals[fd]
#define RET ret[fd]
string *check_perms(string *done, string file){
  mixed perm=master()->valid_read(file, this_player()->query_name(), "cat");
  if(!perm)
    return done;
  if(intp(perm))
    perm = file;
  return done + ({perm});
}
mixed cmd(string arg) {
  int fd, search = 0, nfiles = 0;
  if(!arg)
    arg = "";
  else {
    string bit, *bits = explode(arg, " ");
    arg = "";
    bits -= ({""});
    foreach(bit in bits){
      string *files, file;
      if (bit[0] == '-'){
        if( ( bit == "-r" || bit == "--recursive" || bit== "-d=recurse" ||
       bit == "--directories=recurse" || bit == "-recursive" ||
        bit == "-directories=recurse" ) && !this_player()->query_lord() )
          continue;
        arg += (" " + bit);
        continue;
      }
      if(!search){
        search = 1;
        arg += (" " + bit);
      } else {
        files = this_player()->get_files(bit);
        files = implode(files, (:check_perms:), ({}));
        foreach(file in files){
          arg += (" " + file[1..]);
          nfiles++;
        }
      }
    }
  }
  if(nfiles || !search)
    fd = external_start(6, arg, "read_call_back", "write_call_back",
                      "close_call_back");
  else
    return notify_fail("Grep needs at least one file.\n");
  if (fd == -1)
    return notify_fail("grep failed somehow.\n");
  TP = this_player();
  RET = "";
  write("grep started.\n");
  return 1;
}
void read_call_back(int fd, mixed mess) {
  mess = replace(mess, "/usr/bin/", "");
  RET += mess;
}
void write_call_back(int fd) {
  tell_object(TP, "grep: Whoops! fatal error.\n");
}
void close_call_back(int fd) {
  if(RET != "")
    TP->more_string(RET);
  else
    tell_object(TP, "grep finished.\n");
  map_delete(ret, fd);
  map_delete(globals, fd);
}