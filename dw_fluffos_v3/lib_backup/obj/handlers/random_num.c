int seed = 100;
varargs int random(int max, mixed lseed);
#define Q           51924
#define R           10855
#define MULT        41358
#define MOD   21474836647
#define MAX_VALUE (MOD-1)
#define STARTUP_RANDS  16
void set_seed(int new_seed) {
  int i;
  if (seed <= 0)
    seed = efun::random(200);
  else
    seed = new_seed;
  for (i=0;i<STARTUP_RANDS;i++)
    random(200);
}
varargs int random(int max, mixed lseed) {
  int k, residue, curseed, mode;
  if (undefinedp(lseed)) {
    curseed = seed;
  } else if (intp(lseed)) {
    curseed = lseed;
    mode = 1;
  } else if (arrayp(lseed) && (sizeof(lseed) == 1) && (intp(lseed[0]))) {
    curseed = lseed[0];
    mode = 2;
  } else {
    curseed = seed;
  }
  k = curseed / Q;
  residue = MULT * (curseed - Q*R) - R*k;
  if (residue < 0)
    residue += MOD;
  if (mode == 0) {
    seed = residue;
  } else if (mode == 2) {
    lseed[0] = residue;
  }
  return residue % max;
}
int query_seed() {
  return seed;
}