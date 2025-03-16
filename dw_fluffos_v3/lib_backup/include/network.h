#ifndef __NETWORK_H
#define __NETWORK_H
#include <socket_errors.h>
#define MUD                       0
#define STREAM                    1
#define DATAGRAM                  2
#define STREAM_BINARY             3
#define DATAGRAM_BINARY           4
#define PORT_MUD (mud_name() == "Discworld") ? 23 : 6677
#define PORT_FTP (mud_name() == "Discworld") ? 21 : 4444
#define PORT_HTTP                 80
#define PORT_INTERNAL_HTTP                  5678
#define PORT_OOB                  8765
#define PORT_FTPAUTH              2227
#undef  PORT_RCP
#undef  PORT_UDP
#define CLIENT                    "/net/inherit/client"
#define SERVER                    "/net/inherit/server"
#define INTERMUD_D                "/net/intermud3/intermud"
#define SERVICES_D                "/net/intermud3/services"
#define OOB_D                     "/net/intermud3/oob_server"
#define NETWORK_DICTIONARY_HANDLER "/net/daemon/dictionary"
#define NETWORK_SUCCESS 0
#define MUDLIB_VERSION "Discworld 17.0a"
#define ADMIN_ADDRESS (mud_name() == "Discworld") ? "trustees@discworld.imaginary.com" : "none"
#define STATUS (mud_name() == "Discworld") ? "open for players" : "Development"
#endif