inherit "/std/object";
mapping paths = allocate_mapping(10);
mapping potions = allocate_mapping(10);
#define POTION_DIR "/obj/potions/"
string *directories = ({
    POTION_DIR,
});
void create() {
    string dir, s, dummy, title, path, index;
    int d, i;
    seteuid("Room");
    for (d = 0; d < sizeof(directories); d++) {
        dir = directories[d];
        index = dir + "index";
        i = 1;
        if (file_size(index) > 0) {
            while (s = read_file(index, i++, 1)) {
                if ((s == "") || (sscanf(s, "#%s", dummy))) {
                    continue;
                }
                if (sscanf(s, "\"%s\"%*s\"%s\"", title, path) != 3) {
                    continue;
                }
                paths[title] = path;
                potions[title] = 0;
            }
        }
    }
    ::create();
}
int query_min_level(string s) {
    s = this_player()->expand_nickname(s);
    if (undefinedp(paths[s])) {
        return -1;
    }
    if (!potions[s]) {
        potions[s] = clone_object(paths[s]);
    }
    return potions[s]->query_min_level();
}
string query_chant(string s) {
    s = this_player()->expand_nickname(s);
    if (undefinedp(paths[s])) {
        return 0;
    }
    if (!potions[s]) {
        potions[s] = clone_object(paths[s]);
    }
    return potions[s]->query_chant();
}
object query_potion(string s) {
    s = this_player()->expand_nickname(s);
    if (undefinedp(paths[s])) {
       return 0;
    }
    if (!potions[s]) {
       potions[s] = clone_object(paths[s]);
    }
    return potions[s];
}
mixed clone_reagent(string s) {
    object pot;
    string potion;
    potion = this_player()->expand_nickname(s);
    if (undefinedp(paths[potion])) {
      return -1;
    }
    pot = query_potion(s);
    printf("Verb = %O\n", query_verb());
    return pot->clone_reagent(query_verb());
}
mapping query_paths() {
    return paths;
}
mapping query_potions() {
    return potions;
}