#ifndef DB_H
#define DB_H
#define db_escape(query) replace_string((query), "'", "''")
#define DB_HANDLER "/net/daemon/mysql"
#define DB_SUCCESS 0
#define DB_ERROR_BAD_SOCKET -1
#endif