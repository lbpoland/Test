#ifndef __ERROR_HANDLER_H
#define __ERROR_HANDLER_H
#define ERROR_BAD_QUERY -1000
#define ERROR_HANDLER "/obj/handlers/error_handler"
#define ERROR_CATEGORIES ({ "ROOM", "OBJECT", "HELP", "RITUAL", "SPELL", "COMMAND", "GENERAL" })
#define ERROR_STATUS_OPEN "OPEN"
#define ERROR_STATUS_FIXING "FIXING"
#define ERROR_STATUS_CONSIDERING "CONSIDERING"
#define ERROR_STATUS_FIXED "FIXED"
#define ERROR_STATUS_DENIED "DENIED"
#define ERROR_STATUS ({ ERROR_STATUS_FIXED, ERROR_STATUS_DENIED, \
                        ERROR_STATUS_FIXING, ERROR_STATUS_CONSIDERING, \
                        ERROR_STATUS_OPEN })
#define ERROR_TYPE ({ "BUG", "TYPO", "IDEA", "COMMENT" })
#define ERROR_ORDER_BY_FILENAME "filename"
#define ERROR_ORDER_BY_DIRECTORY "directory"
#define ERROR_ORDER_BY_DATE "date"
#define ERROR_ORDER_BY_REPORTER "reporter"
#define ERROR_ASSIGNED_NO_ONE "nobody"
class error_summary {
   int id;
   int entry_date;
   string filename;
   string category;
   string assigned_to;
   string reporter;
   string type;
   string status;
   string directory;
}
class error_details {
   class error_summary summary;
   int fix_date;
   string fixer;
   string report;
   string runtime;
}
class error_comment {
   int date;
   string commenter;
   string comment;
}
class error_forward {
   int date;
   string forwarder;
   string old_directory;
}
class error_replies {
   int id;
   int bug_id;
   string sender;
   string recipient;
   string status;
   int senddate;
   string subject;
   string message;
}
class error_complete {
   class error_details details;
   class error_comment* comments;
   class error_forward* forwards;
   class error_replies* replies;
}
class error_query {
   int no_extra_details;
   int recursive;
   int id;
   int bug_offset;
   int* id_list;
   string dir;
   string assigned_to;
   string file_name;
   string reporter;
   string fixer;
   string* status;
   string* category;
   string* type;
   string order_by;
}
#endif