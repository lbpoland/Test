#include "weapon_old.h"
nosave mapping ac;
nosave mixed armour_types;
void create() {
  ac = ([ ]);
  armour_types = ({ });
}
int add_ac(string name, string type, mixed a_c) {
  int i;
  if (!stringp(type))
    return 0;
  if (!ac) ac = ([ ]);
  if (ac[name])
    return 0;
  ac[name] = ({ a_c, type });
  if ((i=member_array(type, armour_types)) == -1)
    armour_types += ({ type, ({ name }) });
  else
    armour_types[i+1] += ({ name });
  return 1;
}
int remove_ac(string name) {
  int j, k;
  if (!ac[name])
    return 0;
  j = member_array(ac[name][1], armour_types);
  k = member_array(name, armour_types[j+1]);
  armour_types[j+1] = delete(armour_types[j+1], k, 1);
  if (!sizeof(armour_types[j+1]))
    armour_types = delete(armour_types, j, 2);
  map_delete(ac, name);
  return 1;
}
int calc_value(mixed arr) {
  int i, val;
  if (intp(arr)) {
    if(!random(10))
      return random(arr);
    else
      return arr;
  }
  if (!pointerp(arr))
    return 0;
  if (sizeof(arr) == 1)
    return arr[F_FIXED];
  if (sizeof(arr) == 2)
    return arr[F_FIXED]+random(arr[F_RAND]);
  for (i=0;i<arr[F_NUM];i++)
    val += random(arr[F_DIE]);
  return val + arr[F_FIXED];
}
varargs int query_ac( string type, int dam, string zone ) {
  int val, i, j;
  if ( !armour_types )
    return 0;
  if ((i=member_array(type, armour_types)) != -1) {
    for ( j = 0; j < sizeof( armour_types[ i + 1 ] ); j++ )
      if ( ac[ armour_types[ i + 1 ][ j ]])
        if ( sizeof( ac[ armour_types[ i + 1 ][ j ] ] ) == A_ARRAY_SIZE )
          val += calc_value( ac[ armour_types[ i + 1 ][ j ] ][ A_AC ] );
  }
  val -= (val / 4);
  return val;
}
mapping query_armour_class() { return ac; }
string calc_string(mixed b) {
  if (intp(b))
    return "rand("+b+")";
  if (!pointerp(b))
    return "Dead";
  switch (sizeof(b)) {
    case 1 :
      return ""+b[0];
    case 2 :
      return ""+b[0]+"+rand("+b[1]+")";
    case 3 :
      return ""+b[0]+"+"+b[1]+"d"+b[2];
    default :
      return "Oh hell";
  }
}
mixed *stats() {
  int i;
  mixed *ret;
  mixed *stuff;
  ret = ({ });
  stuff = keys(ac);
  for (i=0;i<sizeof(stuff);i++)
    ret += ({ ({ "ARM"+ i +" name", stuff[ i ], }),
              ({ "     type", ac[stuff[i]][A_TYPE], }),
              ({ "    class", calc_string(ac[stuff[i]][A_AC]) }),
          });
  return ret;
}
void set_ac(mixed *bing) {
  int i;
  for (i=0;i<sizeof(ac);i+=A_ARRAY_SIZE)
    add_ac(ac[i], ac[i+1][A_TYPE], ac[i+1][A_AC]);
}