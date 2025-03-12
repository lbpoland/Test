#include <image.h>
varargs class IMAGE_INFO load_image(string image_file, int rle) {
  int i, j, n, size_x, size_y;
  string image_type, l;
  mixed vals;
  class IMAGE_INFO ret;
  image_type = read_file(image_file, 1, 1);
  image_type = replace_string(image_type, " ", "");
  image_type = replace_string(image_type, "\n", "");
  if (image_type != "RAW") {
    error("Only image type RAW is currently supported.\n");
  }
  l = read_file(image_file, 2, 1);
  if (sscanf(l, "%d%d", size_x, size_y) != 2) {
    error("Image size(s) not found.\n");
  }
  ret = new(class IMAGE_INFO);
  ret->size = ({ size_x, size_y });
  vals = read_file(image_file, 3);
  vals = reg_assoc(vals, ({ "[0-9]+" }), ({ 1 }));
  n = 0;
  while (vals[1][n] != 1) n++;
  ret->image = allocate(size_x);
  for (i = 0; i < size_x; i++) {
    ret->image[i] = allocate(size_y);
    for (j = 0; j < size_y; j++) {
      if (n >= sizeof(vals[0])) {
        error("Ran out of values for image at " + i + ", " + j + ".\n");
      }
      ret->image[i][j] = to_int(vals[0][n++]);
      while ((n < sizeof(vals[0])) && (vals[1][n] != 1))
        n++;
    }
  }
  return ret;
}
void print_image(class IMAGE_INFO im) {
  int i, j;
  printf("size: %d x %d, %s, ", im->size[0], im->size[1],
         (im->rle?"rle":"no rle"));
  if (arrayp(im->nw_coord))
    printf("@ ({ %d, %d, %d })\n", im->nw_coord[0], im->nw_coord[1],
           im->nw_coord[2]);
  else
    printf("(not placed)\n");
  printf("Image:\n    ");
  for (i = 0; i < sizeof(im->image); i++) {
    for (j = 0; j < sizeof(im->image[i]); j++) {
      printf("% 4d", im->image[i][j]);
    }
    printf("\n    ");
  }
  printf("\n");
}