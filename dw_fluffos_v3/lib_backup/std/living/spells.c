#include <spells.h>
class spell_process {
   mapping spells;
   mapping process;
}
private mixed spells;
void create() {
   spells = ([ ]);
}
string help_spell(string str) {
   if (!mapp(spells)) {
     spells = ([ ]);
   }
   if (!m_sizeof(spells)) {
      return 0;
   }
   if (!spells[str]) {
      return 0;
   }
   return (string)spells[str][S_OBJECT]->help(str);
}
mapping query_spells() {
   if (!mapp(spells)) {
      spells = ([ ]);
   }
   return spells;
}
mapping query_spells_nocase() {
  mapping lc_spells = ([]);
  filter( this_object()->query_spells(),
                 (: $3 += ([ lower_case( $1 ) : $2 ]) :), lc_spells );
  return lc_spells;
}
int add_spell(string name, mixed ob, mixed func) {
   int i;
   mapping tmp;
   if (pointerp(spells)) {
      tmp = ([ ]);
      for (i=0;i<sizeof(spells);i+=2)
         tmp[spells[i]] = spells[i+1];
      spells = tmp;
   }
   if (!mapp(spells)) {
      spells = ([ ]);
   }
   spells[name] = ({ ob, func });
   return 1;
}
int remove_spell(string name) {
  string spell, name_lc;
  if ( !name ) {
      map_delete( spells, 0 );
      return 1;
  }
  name_lc = lower_case(name);
  foreach (spell in keys(spells)) {
     if (lower_case(spell) == name_lc) {
        map_delete(spells, spell);
     }
  }
  return 1;
}
mixed query_spell( string word ) {
   mapping tmp_spells;
   string test_spell;
   if ( !mapp( spells ) ) {
      return 0;
   }
   tmp_spells = query_spells_nocase();
   test_spell = lower_case(this_object()->expand_nickname(word));
   return tmp_spells[test_spell];
}
protected void reset_spells() {
   spells = ([ ]);
}