#ifndef __NEWSPAPER_H
#define __NEWSPAPER_H
#define NEWSPAPER_PRESS_CREDITIALS "/obj/misc/press_credentials"
#define NEWSPAPER_HANDLER "/obj/handlers/newspaper"
#define NEWSPAPER_OB "/obj/misc/newspaper"
#define NEWSPAPER_SUBSCRIPTION_OB "/obj/furnitures/misc/newspaper_box"
#define NEWSPAPER_WWW_LOGO_BASE "/external/newspaper/logos/logo"
#define NEWSPAPER_ARTICLE_TYPE_PLAIN 1
#define NEWSPAPER_ARTICLE_TYPE_HTML 2
#define NEWSPAPER_ARTICLE_TYPE_NROFF 3
#define NEWSPAPER_ARTICLE_TYPE_SECTION 4
#define NEWSPAPER_ARTICLE_TYPE_ADVERTS 5
#define NEWSPAPER_ARTICLE_TYPE_MASK 7
#define NEWSPAPER_ARTICLE_ANONYMOUS_FLAG 1024
#define NEWSPAPER_ARTICLE_NO_XP_FLAG     2048
#define NEWSPAPER_WEB_HIT_REVENUE 40
#define NEWSPAPER_XP_PER_ARTICLE 60000
#define NEWSPAPER_XP_EDITOR 120000
class article {
   string file_name;
   string title;
   string author;
   int date_written;
   int type;
   string shown_name;
   string colour;
}
class advert {
   string text;
   string author;
   string category;
   int date_written;
   int value;
}
#endif