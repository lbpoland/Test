#ifndef __SYS__BOARD
#define __SYS__BOARD
#define MASTER_OB "/secure/master"
#define NEWS_RC "news rc"
#define BOARD_ORDER "board order"
#define BOARD_FILE "/save/boards.o"
#define BOARD_DIR "/save/boards/"
#define BOARD_RAM_DIR "/save/ramdisk/boards/"
#define BOARD_HAND "/obj/handlers/board_handler"
#define BOARD_WEB "/www/boards"
#define B_SUBJECT 0
#define B_NAME 1
#define B_NUM 2
#define B_TIME 3
#define B_REPLY_TYPE 4
#define B_REPLY_NUM 5
class reply_type {
   int type;
   mixed data;
}
#define B_REPLY_POSTER 1
#define B_REPLY_NAMED 2
#define B_ACCESS_READ 1
#define B_ACCESS_WRITE 2
#define B_ACCESS_DELETE 3
#define B_ACCESS_APPROVE 4
#define B_ACCESS_INFORM 5
#define B_PRIV_NORMAL                 0
#define B_PRIV_READ_ONLY              1
#define B_PRIV_ACCESS_RESTRICTED      2
#define B_PRIV_ACCESS_RESTRICTED_FILE 3
#define B_PRIV_NO_INFORM              256
#define B_PRIV_TYPE_MASK              255
#define B_PRIV_ACCESS_RESTRICTED_METHOD 4
#define BOARD_SOCIAL_POINT_COST 50
#endif