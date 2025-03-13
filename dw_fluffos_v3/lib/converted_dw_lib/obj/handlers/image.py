# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/image.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def print_image(self, IMAGE_INFO: Any) -> None:
            int i, j
            printf("size: %d x %d, %s, ", im->size[0], im->size[1],
            (im->rle?"rle":"no rle"))
            if (arrayp(im->nw_coord))
            printf("@ [%d, %d, %d]\n", im->nw_coord[0], im->nw_coord[1],
            im->nw_coord[2])
            else
            printf("(not placed)\n")
            printf("Image:\n    ")
            for (i = 0; i < sizeof(im->image); i++) {
            for (j = 0; j < sizeof(im->image[i]); j++) {
            printf("% 4d", im->image[i][j])



class Image(MudObject):
