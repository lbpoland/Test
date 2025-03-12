inherit "/std/races/base";
void create() {
   do_setup++;
   ::create();
   do_setup--;
   set_desc( "your standard tree.  Shouldn't be used since this is a base "
      "race" );
   bits = ({
      "trunk", "trunk", ({ 0, 1000, 0 }),
      "branch", "branch", ({ 0, 20, ({"/std/bit", 20}) }),
      "root", "root", ({ 0, 20, ({"/std/bit", 10}) })
   });
   inedible = ({ "trunk", "branch", "root" });
   unrottable = ({ });
   set_skin( "bark" );
   if( !do_setup )
      this_object()->setup();
}
string *query_target_zones() {
  return ({ "branch", "branch", "branch", "branch", "branch",
            "branch", "branch", "branch", "branch", "branch",
              "trunk", "trunk", "trunk", "trunk", "trunk",
              "trunk", "trunk", "trunk", "trunk", "trunk",
              "base", "base", "base", "base", "root"});
}
string map_target_zone(string zone) {
  switch(zone) {
  case "chest":
  case "abdomen":
  case "back":
    return "trunk";
  case "hands":
  case "neck":
  case "head":
  case "arms":
  case "legs":
    return "branches";
  case "feet":
    return "root";
  }
}