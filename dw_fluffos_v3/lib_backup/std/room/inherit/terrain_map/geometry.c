class point {
   int x;
   int y;
}
#define SMALL_NUM 0.00001
class point intersection_of_line_and_segment(int lx1, int ly1, int lx2, int ly2,
                                             int sx1, int sy1, int sx2, int sy2) {
   float den;
   float uanum;
   float ubnum;
   float ua;
   float ub;
   class point p;
   den = to_float(sy2 - sy1) * to_float(lx2 - lx1) - to_float(sx2 - sx1) * to_float(ly2 - ly1);
   if (den == 0.0) {
      return 0;
   }
   ubnum = to_float(lx2 - lx1) * to_float(ly1 - sy1) - to_float(ly2 - ly1) * to_float(lx1 - sx1);
   ub = ubnum / den;
   if (ub < 0.0 || ub > 1.0) {
      return 0;
   }
   uanum = to_float(sx2 - sx1) * to_float(ly1 - sy1) - to_float(sy2 - sy1) * to_float(lx1 - sx1);
   ua = uanum / den;
   p = new(class point);
   p->x = lx1 + to_int(ua * (lx2 - lx1));
   p->y = ly1 + to_int(ub * (ly2 - ly1));
   return p;
}
int distance_point_to_line_segment(int x1, int y1, int x2, int y2,
                           int point_x, int point_y) {
   float v1_x;
   float v1_y;
   float v2_x;
   float v2_y;
   float distance;
   float dot1;
   float dot2;
   float b;
   float vm_x;
   float vm_y;
   v1_x = to_float(x1 - x2);
   v1_y = to_float(y1 - y2);
   v2_x = to_float(point_x - x2);
   v2_y = to_float(point_y - y2);
   dot1 = v1_x * v2_x + v1_y * v2_y;
   if (dot1 <= 0.0) {
      distance = sqrt(pow(x2 - point_x, 2) + pow(y2 - point_y, 2));
   } else {
      dot2 = v1_x * v1_x + v1_y * v1_y;
      if (dot2 <= dot1) {
         distance = sqrt(pow(x1 - point_x, 2) + pow(y1 - point_y, 2));
      } else {
         b = dot1 / dot2;
         vm_x = to_float(x2) + b * v1_x;
         vm_y = to_float(y2) + b * v1_y;
         distance = sqrt(pow(vm_x - point_x, 2) + pow(vm_y - point_y, 2));
      }
   }
   return to_int(distance);
}
int distance_between_two_line_segments(
     int x1_1, int y1_1, int x2_1, int y2_1,
     int x1_2, int y1_2, int x2_2, int y2_2) {
   float ux;
   float uy;
   float vx;
   float vy;
   float wx;
   float wy;
   float dpx;
   float dpy;
   float a;
   float b;
   float c;
   float d;
   float e;
   float dist;
   float sc;
   float sn;
   float sd;
   float tc;
   float tn;
   float td;
   ux = to_float(x2_1) - to_float(x1_1);
   uy = to_float(y2_1) - to_float(y1_1);
   vx = to_float(x2_2) - to_float(x1_2);
   vy = to_float(y2_2) - to_float(y1_2);
   wx = to_float(x1_1) - to_float(x1_2);
   wy = to_float(y1_1) - to_float(y1_2);
   a = ux * ux + uy * uy;
   b = ux * vx + uy * vy;
   c = vx * vx + vy * vy;
   d = ux * wx + uy * wy;
   e = vx * wx + vy * wy;
   dist = a * c - b * b;
   sd = dist;
   td = dist;
   if (dist < SMALL_NUM) {
      sn = 0.0;
      sd = 1.0;
      tn = e;
      td = c;
   } else {
      sn = b * e - c * d;
      tn = a * e - b * d;
      if (sn < 0.0) {
         sn = 0.0;
         tn = e;
         td = c;
      } else if (sn > sd) {
         sn = sd;
         tn = e + b;
         td = c;
      }
      if (tn < 0.0) {
         tn = 0.0;
         if (-d < 0.0) {
            sn = 0.0;
         } else if (-d > a) {
            sn = sd;
         } else {
            sn = -d;
            sd = a;
         }
      } else if (tn > td) {
         tn = td;
         if ((-d + b) < 0) {
            sn = 0.0;
         } else if ((-d + b) > a) {
            sn = sd;
         } else {
            sn = -d + b;
            sd  = a;
         }
      }
   }
   sc = sn / sd;
   tc = tn / td;
   dpx = wx + (sc * ux) - (tc * vx);
   dpy = wy + (sc * uy) - (tc * vy);
   dist = sqrt(dpx * dpx + dpy * dpy);
   if (dist > pow(2, 30)) {
      return to_int(pow(2, 30));
   }
   return to_int(sqrt(dpx  * dpx + dpy * dpy));
}