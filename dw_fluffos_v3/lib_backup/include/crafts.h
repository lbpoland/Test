#ifndef __CRAFTS
#define __CRAFTS
#define CRAFT_ERROR 0
#define CRAFT_INHERIT "/obj/crafts/base"
#define CRAFT_HANDLER "/obj/crafts/craft_handler"
#define CRAFT_MATERIAL_REQUIRED 1
#define CRAFT_MATERIAL_ONE_OF 2
#define CRAFT_MATERIAL_OPTIONAL 3
#define CRAFT_MATERIAL_DENIED 4
#define CRAFT_MATERIAL_TYPE_MASK 127
#define CRAFT_MATERIAL_ALL    128
#define CRAFT_QUALITY_WORTHLESS -4
#define CRAFT_QUALITY_AWFUL -3
#define CRAFT_QUALITY_BAD -2
#define CRAFT_QUALITY_POOR -1
#define CRAFT_QUALITY_NORMAL 0
#define CRAFT_QUALITY_FINE 1
#define CRAFT_QUALITY_GOOD 2
#define CRAFT_QUALITY_EXCELLENT 3
#define CRAFT_QUALITY_PERFECT 4
class crafts_bonus {
   mapping result;
   mapping skill_bonus;
   int quality;
   int bonus;
}
#endif