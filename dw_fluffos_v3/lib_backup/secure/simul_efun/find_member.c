int *find_member( mixed target, mixed *array ) {
int *locs = ({ });
int start = 0;
  while ( start != -1 ) {
    start = member_array( target, array, start );
    if ( start != -1 ) {
      locs += ({ start });
      start ++;
    }
  }
  return locs;
}