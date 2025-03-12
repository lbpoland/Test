#ifndef __SYS__CMR
#define __SYS__CMR
#define MINERALS 0
#define GEMS 1
#define METALS 2
#define WOODS 3
#define MATERIALS ({ "mineral", "gem", "metal", "wood" })
#define MATERIAL_ADJECTIVES ({ "mineral", "gem", "metallic", "wooden" })
#define KNOWN 0
#define MAGIC 1
#define OS 2
#define OW 3
#define OVG 4
#define OVJ 5
#define LEARNT 99
#define SKILLS ({ \
      "none", \
      "magic", \
      "crafts.smithing", \
      "crafts.carpentry", \
      "other.valueing.gems", \
      "other.valueing.jewellery", \
   })
#define CMR_HANDLER "/obj/handlers/cmr_handler"
#define CMR_LIBRARY "/obj/handlers/cmr_library"
#endif