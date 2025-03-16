inherit "/obj/monster";
void setup() {
    string *name_adjectives = ({ "furry", "manky",
      "flea-ridden", "obnoxious", "sharp-toothed", "stinky", "dirty, stinking",
      "brown", "beady-eyed", "corpse-eating" });
    string adjective;
    adjective = name_adjectives[random(sizeof(name_adjectives))];
    set_name("rat");
    add_alias("rodent");
    set_gender(1 + random(2));
    set_short(adjective + " rat");
    add_adjective(adjective);
    set_long("The learning domain is full of rats.  This one appears "
    "not to have eaten for some hours and has a look"
    " of hunger in " + query_possessive()
      + " eyes.\n");
    basic_setup ("rat", "fighter", 2 + random(5));
}