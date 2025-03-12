inherit "/cmds/base";
#include <creator.h>
#define CMD_NUM 5
mapping globals = ([]), ret = ([]);
string cmd_str;
#define TP globals[fd]
#define RET ret[fd]
mixed cmd(string arg) {
  string *files;
  int nfiles = 0;
  string bit, *bits;
  int add_comments;
  string tmp;
  if (!arg) {
    return notify_fail("rcscreate: No arguments.\n");
  }
  notify_fail("rcscreate: no such file "+arg+".\n");
  bits = explode(arg, " ");
  arg = "";
  bits -= ({""});
  foreach (bit in bits) {
    string  file;
    if (bit[0] == '-') {
      if (bit[1] == 'c') {
        add_comments = 1;
      } else {
        arg += (" " + bit);
      }
      continue;
    }
    files = this_player()->get_files(bit);
    foreach (file in files) {
      if (master()->valid_write(file, geteuid(this_player()), "cmd")) {
        string dir, *tmpbits;
        tmpbits = explode(file, "/");
        if (tmpbits[<1] == "RCS" ||
            tmpbits[<1] == "." ||
            tmpbits[<1] == ".." ||
            tmpbits[<1] == "ERROR_REPORTS") {
          continue;
        }
        if (sizeof(tmpbits) > 1) {
          dir = "/" + implode(tmpbits[0..<2], "/") + "/RCS";
        } else {
          dir = "/RCS";
        }
        if (file_size(dir) == -1) {
          write("No directory "+dir+", creating one.\n");
          mkdir(dir);
        }
        if (add_comments) {
          tmp = read_file(file);
          if ( file[ strsrch( file, ".", -1 ) .. ] == ".c"  ||
               file[ strsrch( file, ".", -1 ) .. ] == ".h" )  {
            tmp = replace_string(tmp, "\n", "");
            tmp = replace_string(tmp, "\n", "");
            write_file(file,
                       "\n"
                       "\n\n" + tmp);
          }
          else  {
            tmp = replace_string( tmp, "#  -*- LPC -*-  #\n", "" );
            tmp = replace_string( tmp, "# -*- LPC -*- #\n", "" );
            write_file( file,
                        "#  -*- LPC -*- #\n"
                        "#\n"
                        "# $", 1 );
            write_file( file,
                        "Locker$\n"
                        "# $");
            write_file(file, "Id$\n"
                        "#\n"
                        "#\n"
                        "#\n\n" + tmp );
          }
        }
        arg += (" " + file[1..]);
        nfiles++;
      } else {
        notify_fail("You do not have write access to "+file+"\n");
      }
    }
  }
  if (!nfiles) {
    return 0;
  }
  printf("Enter a comment.\n");
  cmd_str = arg;
  this_player()->do_edit(0, "do_ci");
  return 1;
}
void do_ci(string comment) {
  int fd;
  string *cmd = allocate(4);
  if (!comment) {
    printf("No comment given, aborting.\n");
    return;
  }
  cmd[0] = "-w" + this_player()->query_name();
  cmd[1] = "-i";
  cmd[2] = "-u";
  cmd[3] = "-t-" + comment;
  cmd += explode(cmd_str, " ");
#ifdef DEBUG
  printf("CMD: %O\n", cmd);
#endif
  fd = external_start(CMD_NUM, cmd, "read_call_back", "write_call_back",
                      "close_call_back");
  TP = this_player();
  RET = "";
}
void read_call_back(int fd, mixed mess) {
  mess = replace_string(mess, "/home/atuin/lib", "");
  RET += mess;
}
void write_call_back(int fd) {
  tell_object(TP, "rcscreate: Write_call_back called.\n");
}
void close_call_back(int fd) {
  if (RET != "") {
    TP->more_string(RET);
  } else {
    tell_object(TP, "rcscreate completed.\n");
  }
  map_delete(ret, fd);
  map_delete(globals, fd);
}