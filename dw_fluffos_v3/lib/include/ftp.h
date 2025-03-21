#ifndef __SYS__FTP
#define __SYS__FTP
#define FTP_PORT 4444
class dataconn {
  mixed data;
  string path;
  int pos;
  int parent_fd;
  int type;
  int len;
  int append;
}
class session {
  int fd;
  string user_name;
  int logged_in;
  string cwd;
  string data_addr;
  int last_data;
  int data_port;
  int data_fd;
  int type;
  int idle;
  string rnfr;
  int offset;
  int use_default;
  int pasv_fd;
  int pasv_cb;
}
#define STRING 1
#define FILE 2
#define DOWNLOAD 3
#define BINARY 4
#define MASK_L  1
#define MASK_C  2
#define MASK_F  4
#define MASK_A  8
#define MASK_R 16
#define MASK_D 32
#define TP_CRE "turrican"
#undef DEBUG
#ifdef DEBUG
#define TP(STR) if (find_player(TP_CRE)) \
                    tell_object(find_player(TP_CRE), STR)
#define DEBUG_SEND
#define DEBUG_RECEIVE
#else
#define TP(STR)
#undef DEBUG_SEND
#undef DEBUG_RECEIVE
#endif
#define LOGGING
#ifdef LOGGING
#define LOG_CONNECT
#define LOG_FILE
#define LOG_CD_SIZE
#define LOG_DEBUG
#define LOG_FILENAME "/d/admin/log/FTPD.log"
#else
#undef LOG_CONNECT
#undef LOG_FILE
#undef LOG_CD_SIZE
#undef LOG_DEBUG
#endif
#define BLOCK_SIZE 65536
#define NEWDRIVER
#ifdef __VERSION__
#define VERSION __VERSION__
#else
#ifndef VERSION
#define VERSION version()
#endif
#endif
#define CHECK_LOGIN() if (!sess->logged_in) \
                      { \
                        eventWrite(fd, "530 Please login with USER and PASS.\r\n"); \
                        break; \
                      }
#define CHECK_CMD(INT) if (sizeof(bits) != INT+1) \
                       { \
                         eventWrite(fd, sprintf("500 '%s': command not understood.\r\n", \
                            str)); \
                         break; \
                       }
#define CHECK_CMD2(INT,INT2) if (sizeof(bits) < INT+1 ||\
                                 sizeof(bits) > INT2+1) \
                       { \
                         eventWrite(fd, sprintf("500 '%s': command not understood.\r\n", \
                            str)); \
                         break; \
                       }
#define CHECK_PLAYER() if (sess->logged_in == 2) \
                       { \
                         eventWrite(fd, "553 Permission denied (you are not a creator)\r\n"); \
                         break; \
                       }
#define CHECK_STRING sess->type == STRING
#define UNAME sess->user_name
#define HOME_DIR(NAME) "/w/"+NAME
protected void setup_ftp();
protected string get_path(int fd, string str);
protected void do_update(string name, int fd);
protected void data_write_callback(int fd);
mapping cmdtab = ([
    "user" : ({ "USER", 1, "<sp> username" }),
    "pass" : ({ "PASS", 1, "<sp> password" }),
    "acct" : ({ "ACCT", 0, "(specify account)" }),
    "smnt" : ({ "SMNT", 0, "(structure mount)" }),
    "rein" : ({ "REIN", 0, "(reinitialize server state)" }),
    "quit" : ({ "QUIT", 1, "(terminate service)", }),
    "port" : ({ "PORT", 1, "<sp> b0, b1, b2, b3, b4" }),
    "pasv" : ({ "PASV", 0, "(set server in passive mode)" }),
    "type" : ({ "TYPE", 1, "<sp> [ A | E | I | L ]" }),
    "stru" : ({ "STRU", 0, "(specify file structure)" }),
    "mode" : ({ "MODE", 0, "(specify transfer mode)" }),
    "retr" : ({ "RETR", 1, "<sp> file-name" }),
    "stor" : ({ "STOR", 1, "<sp> file-name" }),
    "appe" : ({ "APPE", 1, "<sp> file-name" }),
    "mlfl" : ({ "MLFL", 0, "(mail file)" }),
    "mail" : ({ "MAIL", 0, "(mail to user)" }),
    "msnd" : ({ "MSND", 0, "(mail send to terminal)" }),
    "msom" : ({ "MSOM", 0, "(mail send to terminal or mailbox)" }),
    "msam" : ({ "MSAM", 0, "(mail send to terminal and mailbox)" }),
    "mrsq" : ({ "MRSQ", 0, "(mail recipient scheme question)" }),
    "mrcp" : ({ "MRCP", 0, "(mail recipient)" }),
    "allo" : ({ "ALLO", 1, "allocate storage (vacuously)" }),
    "rest" : ({ "REST", 1, "(restart command)" }),
    "rnfr" : ({ "RNFR", 1, "<sp> file-name" }),
    "rnto" : ({ "RNTO", 1, "<sp> file-name" }),
    "abor" : ({ "ABOR", 1, "(abort operation)" }),
    "dele" : ({ "DELE", 1, "<sp> file-name" }),
    "cwd"  : ({ "CWD" , 1, "[ <sp> directory-name ]" }),
    "xcwd" : ({ "XCWD", 1, "[ <sp> directory-name ]" }),
    "list" : ({ "LIST", 1, "[ <sp> path-name ]" }),
    "nlst" : ({ "NLST", 1, "[ <sp> path-name ]" }),
    "site" : ({ "SITE", 1, "site-cmd [ <sp> arguments ]" }),
    "syst" : ({ "SYST", 1, "(get type of operating system)" }),
    "stat" : ({ "STAT", 1, "[ <sp> path-name ]" }),
    "help" : ({ "HELP", 1, "[ <sp> <string> ]" }),
    "noop" : ({ "NOOP", 1, "" }),
    "mkd"  : ({ "MKD" , 1, "<sp> path-name" }),
    "xmkd" : ({ "XMKD", 1, "<sp> path-name" }),
    "rmd"  : ({ "RMD" , 1, "<sp> path-name" }),
    "xrmd" : ({ "XRMD", 1, "<sp> path-name" }),
    "pwd"  : ({ "PWD" , 1, "(return current directory)" }),
    "xpwd" : ({ "XPWD", 1, "(return current directory)" }),
    "cdup" : ({ "CDUP", 1, "(change to parent directory)" }),
    "xcup" : ({ "XCUP", 1, "(change to parent directory)" }),
    "stou" : ({ "STOU", 0, "<sp> file-name" }),
    "size" : ({ "SIZE", 1, "<sp> path-name" }),
    "mdtm" : ({ "MDTM", 1, "<sp> path-name" })
]);
mapping sitecmdtab = ([
    "idle"  : ({ "IDLE",  1, "[ <sp> timeout ]" }),
    "help"  : ({ "HELP",  1, "[ <sp> <string> ]" }),
    "newer" : ({ "NEWER", 0, "<sp> YYYYMMDDHHMMSS [ <sp> path-name ]" }),
    "minfo" : ({ "MINFO", 0, "<sp> YYYYMMDDHHMMSS [ <sp> path-name ]" }),
    "time"  : ({ "TIME",  1, "(prints local time)" }),
    "upd"   : ({ "UPD",   1, "<sp> path-name" })
]);
#define FTP_VERSION "Version 13.2"
#define LOGIN_OB "/secure/login"
#endif