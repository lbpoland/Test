#ifndef __SYS__MAIL
#define __SYS__MAIL
#ifndef __MAIL_H_NO_CLASSES
class mail_header {
  int number;
  string status;
  string subject;
  string from;
}
class mail_message {
  string *to;
  string *cc;
  string body;
  string from;
  string subject;
}
#endif
#define DAYS ({"Sun", "Mon", "Tue", "Wed", "Thu", \
               "Fri", "Sat"})
#define MONTHS ({"Jan", "Feb", "Mar", "Apr", "May", "Jun", \
     "Jul", "Aug", "Sep", "Oct", "Nov", \
     "Dec"})
#define MAIL_TRACK "/obj/handlers/mail_track"
#define MAILER "/obj/handlers/mailer"
#define AUTO_MAILER "/global/auto_mailer"
#define OUT_MAIL "/net/daemon/out_mail"
#define POST_FROG "/obj/monster/post_frog"
#define FROG_HOME "/d/am/buildings/post/mailing"
#define SMTP "/net/obj/smtp"
#define EXTERNAL_MAIL_PATH "/secure/mail/incoming/"
#define MAIL_PARCEL_HANDLER "/obj/handlers/parcel"
#define MAX_FOLDER_SIZE 250
#define WARN_FOLDER_SIZE 100
#endif