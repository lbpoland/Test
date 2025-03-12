#include <player_shop.h>
#include <mail.h>
#define REFRESH_HANDLER "/obj/handlers/refresh"
#define save_me() unguarded((:write_file, "/save/player_shops", \
                  save_variable(_shops), 1:));
private nosave mapping _shops = 0;
void create()
{
    seteuid("Root");
    if (file_size("/save/player_shops") > 0)
    {
        _shops = restore_variable(unguarded((:read_file,
              "/save/player_shops":)));
    }
}
int add_shop(string short_name, string office_path)
{
    string savedir;
    object ob;
    if (!(ob = find_object(office_path)))
    {
        tell_object(this_player(), "No such object "+ office_path+ ".\n");
        return 0;
    }
    if (_shops)
    {
        if (_shops[short_name])
        {
            tell_object(this_player(), "Shop already exists.\n");
            return 0;
        }
        _shops += ([short_name:""]);
    }
    else
    {
        _shops = ([short_name:""]);
    }
    _shops[short_name] = office_path;
    REFRESH_HANDLER->register_refresh(office_path);
    REFRESH_HANDLER->register_delete(office_path);
    savedir = sprintf("/save/player_housing/%s/",
      lower_case(geteuid(ob)));
    if (!sizeof(get_dir(savedir)))
        unguarded((: mkdir, savedir :));
    savedir += sprintf("/player_shops");
    if (!sizeof(get_dir(savedir)))
        unguarded((: mkdir, savedir :));
    savedir += sprintf("/%s", short_name);
    if (!sizeof(get_dir(savedir)))
        unguarded((: mkdir, savedir :));
    save_me();
    return 1;
}
int remove_shop(string short_name)
{
    if (!_shops || !_shops[short_name])
    {
        tell_object(this_player(), "Shop doesn't exist.\n");
        return 0;
    }
    if (!this_player()->query_lord() &&
      this_player()->query_name() != CREATOR)
    {
        tell_object(this_player(), "Permission denied.\n");
        return 0;
    }
    map_delete(_shops, short_name);
    save_me();
    return 1;
}
int update_shop(string short_name, string office_path)
{
    if (!_shops || !_shops[short_name])
    {
        tell_object(this_player(), "Shop doesn't exist.\n");
        return 0;
    }
    if (!this_player()->query_lord() &&
      this_player()->query_name() != CREATOR)
    {
        tell_object(this_player(), "Permission denied.\n");
        return 0;
    }
    if (!find_object(office_path))
    {
        tell_object(this_player(), "No such object "+ office_path+ ".\n");
        return 0;
    }
    REFRESH_HANDLER->register_refresh(office_path);
    REFRESH_HANDLER->register_delete(office_path);
    _shops[short_name] = office_path;
    save_me();
    return 1;
}
string query_shop(string short_name)
{
    if (!_shops || !_shops[short_name])
        return "";
    if (!find_object(_shops[short_name]))
        return "No such file "+ _shops[short_name]+ ".";
    return _shops[short_name];
}
mapping query_shops() { return copy(_shops); }
void auto_mail(string to, string from, string sub, string cc, string body)
{
    if (_shops)
    {
        foreach (string shop in keys(_shops))
        {
            if (_shops[shop] == file_name(previous_object()))
            {
                return MAILER->do_mail_message(to, from, sub, cc, body, 0, 0, 1);
            }
        }
    }
    unguarded((: write_file, "/log/CHEAT",
        "Illegal access to AUTO_MAILER.\n" "Backtrace: " +
        back_trace() :));
}