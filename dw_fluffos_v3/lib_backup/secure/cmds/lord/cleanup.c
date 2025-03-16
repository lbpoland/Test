inherit "/cmds/base";
inherit "/cmds/speech";
mixed cmd(string mess) {
	if("/secure/bulk_delete"->delete_files(mess))
		write("Ok.\n");
	else
		return notify_fail("Sorry.\n");
}