private nosave int _light;
private nosave int _my_light;
private nosave int _need_recalculate;
private nosave object *_inform_of_change;
void new_recalc_light();
mixed query_property(string name);
void add_property(string name, mixed value);
void remove_property(string name);
void create() {
    _inform_of_change = ({ });
}
int query_light() {
    if (_need_recalculate) {
        _need_recalculate = 0;
        new_recalc_light();
    }
    return _light;
}
int query_light_needs_inform() {
    return _light || _need_recalculate;
}
int query_my_light() { return _my_light; }
varargs void new_recalc_light() {
    object *obs;
    object ob;
    int tmp_light;
    _need_recalculate = 0;
    _light = _my_light * _my_light;
    if (_my_light < 0)  _light = -_light;
    if ( !this_object()->query_opaque() ) {
        obs = all_inventory(this_object());
        foreach (ob in obs) {
            if (ob->query_opaque()) {
                tmp_light = ob->query_my_light();
            } else {
                tmp_light = ob->query_light();
            }
            if (tmp_light >= 0)  _light += tmp_light * tmp_light;
            else  _light -= tmp_light * tmp_light;
        }
    }
    if (_light >= 0)  _light = sqrt(_light);
    else  _light = -sqrt(-_light);
    _inform_of_change->event_light_change(this_object(), 0, _light);
}
void light_level_changed() {
    _need_recalculate = 1;
}
void inform_of_light_level_change(object ob) {
    if (ob) {
        ob->light_level_changed();
    }
    while (ob && !ob->query_opaque()) {
        ob->light_level_changed();
        ob = environment(ob);
    }
}
void add_inform_light_change(object ob) {
    _inform_of_change += ({ ob });
}
void remove_inform_light_change(object ob) {
    _inform_of_change -= ({ ob });
}
void set_opaque() {
    add_property( "opaque", 1 );
}
void reset_opaque() {
    remove_property( "opaque" );
}
int query_opaque() {
    return query_property("opaque");
}
int adjust_light( int number ) {
    if (number) {
        _my_light += number;
        inform_of_light_level_change(this_object());
    }
    return _light;
}
int set_light(int number) {
    return adjust_light(number - _my_light);
}
mixed *stats() {
    return ({
      ({ "light", _light, }),
      ({ "my light", _my_light, }),
    });
}