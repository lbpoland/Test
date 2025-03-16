#include <mail.h>
#include <player_handler.h>
int auto_mail(string to,
              string from,
              string sub,
              string cc,
              string body,
              int send_inter,
              string only_to,
              int flag)
{
  if (PLAYER_HANDLER->test_player(from) &&
      this_player() &&
      from != this_player()->query_name()) {
    write("AUTO_MAILER: Illegal access!\n");
    unguarded((: write_file, "/log/CHEAT",
           "Illegal access to AUTO_MAILER.\n" "Backtrace: " +
           back_trace() :));
    return 0;
  }
  return MAILER->do_mail_message(to, from, sub, cc, body,
                 send_inter, only_to, flag);
}