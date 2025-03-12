#ifndef __SYS__NEWUDP
#define __SYS__NEWUDP
#ifndef __NEWUDP_H
#define __NEWUDP_H
#ifdef __UDP_H
#define NEW_INETD "/net/intermud/inetd"
#else
#define INETD		"/net/intermud/inetd"
#endif
#define UDP_CMD_DIR	"/net/intermud/udp/"
#define HOST_FILE	"/net/intermud/adm/INETD_HOSTS"
#define INETD_LOG_FILE	"INETD"
#define REPLY_TIME_OUT	12
#define RETRIES		2
#define LOCAL_NAME	MUD_NAME
#define LOCAL_UDP_PORT 5756
#define INETD_DIAGNOSTICS
#define INETD_VERSION	"0.61"
#define RECIPIENT	"RCPNT"
#define REQUEST		"REQ"
#define SENDER		"SND"
#define DATA		"DATA"
#define HOST		"HST"
#define ID		"ID"
#define NAME		"NAME"
#define PACKET		"PKT"
#define UDP_PORT	"UDP"
#define SYSTEM		"SYS"
#define PACKET_LOSS	"PKT_LOSS"
#define RESPONSE_TIME	"TIME"
#define PING		"ping"
#define QUERY		"query"
#define REPLY		"reply"
#define TIME_OUT	"TO"
#define HOST_NAME	0
#define HOST_IP		1
#define HOST_UDP_PORT	2
#define LOCAL_COMMANDS	3
#define HOST_COMMANDS	4
#define HOST_STATUS	5
#endif
#endif