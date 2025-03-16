#ifndef __SYS__PUB_SHOP
#define __SYS__PUB_SHOP
#define PUB_APPETISER   0
#define PUB_MAINCOURSE  1
#define PUB_DESSERT     2
#define PUB_ALCOHOL     3
#define PUB_SOFTDRINK   4
#define PUB_HOTDRINK    5
#define PUB_MENU_FILE     "/obj/misc/menu"
#define PUB_COUNTER_FILE  "/std/shops/objs/counter"
#define PUB_GLASS_PATH    "/obj/misc/glasses/"
#define PUB_STD_TANKARD   PUB_GLASS_PATH + "std_tankard.ob"
#define PUB_STD_PINT      PUB_GLASS_PATH + "std_pint_glass.ob"
#define PUB_STD_HALFPINT  PUB_GLASS_PATH + "std_half_glass.ob"
#define PUB_STD_SHOT      PUB_GLASS_PATH + "std_shot_glass.ob"
#define PUB_STD_WINE      PUB_GLASS_PATH + "std_wine_glass.ob"
#define PUB_STD_BRANDY    PUB_GLASS_PATH + "std_brandy_glass.ob"
#define PUB_STD_TUMBLER   PUB_GLASS_PATH + "std_tumbler.ob"
#define PUB_STD_COCKTAIL  PUB_GLASS_PATH + "std_cocktail_glass.ob"
#define PUB_STD_FLUTE     PUB_GLASS_PATH + "std_flute_glass.ob"
#define PUB_STD_TEACUP    PUB_GLASS_PATH + "std_teacup.ob"
#define PUB_STD_MUG       PUB_GLASS_PATH + "std_mug.ob"
#define PUB_PLATE_PATH    "/obj/misc/plates/"
#define PUB_STD_PLATE         PUB_PLATE_PATH + "std_plate.ob"
#define PUB_STD_DISH          PUB_PLATE_PATH + "std_dish.ob"
#define PUB_STD_BOWL          PUB_PLATE_PATH + "std_bowl.ob"
#define PUB_STD_SOUPDISH      PUB_PLATE_PATH + "std_soup_dish.ob"
#define PUB_STD_DINNERPLATE   PUB_PLATE_PATH + "std_dinner_plate.ob"
#define PUB_STD_SIDEPLATE     PUB_PLATE_PATH + "std_side_plate.ob"
#define PUB_STD_DESSERTPLATE  PUB_PLATE_PATH + "std_dessert_plate.ob"
#define PUB_STD_DESSERTDISH   PUB_PLATE_PATH + "std_dessert_dish.ob"
class menu_item {
   int type;
   int cost;
   string item;
   string container;
   int volume;
   int intox;
}
#define PUB_EVENT_NOT_AVAILABLE "not_available"
#define PUB_EVENT_NOT_OPEN "not_open"
#define PUB_EVENT_BOUGHT_STUFF "bought_stuff"
#define PUB_EVENT_DEAD_PEOPLE "dead_people"
#define PUB_EVENT_FAILED_PEOPLE "failed_people"
#define PUB_EVENT_POOR_PERSON "poor_people"
#endif