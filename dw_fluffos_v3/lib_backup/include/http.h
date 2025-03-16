#ifndef __HTTP_H
#define __HTTP_H
#include <mime.h>
#define HTTPD "/net/daemon/http"
#define HTTP_PROTOCOL "HTTP/1.1"
#define HTTP_VERSION "Discworld/0.10.3"
#define HTTP_ACCEPT_ENCODING "accept-encoding"
#define HTTP_CODING_TYPE "Content-Encoding"
#define REQ_REQUEST 0
#define REQ_HEADERS 1
#define REQ_BODY 2
#define BODY_START 0
#define BODY_READ 1
#define BODY_CHUNK_FOOTER 2
#define BODY_CHUNK_END 3
#define DIR_WWW "/www"
#define CONTINUE 100
#define HTTP_OK 200
#define NO_CONTENT 204
#define PARTIAL_CONTENT 206
#define MOVED_PERMANENTLY 301
#define MOVED_TEMP 302
#define NOT_MODIFIED 304
#define BAD_CMD 400
#define AUTH_REQUIRED 401
#define ACCESS_DENIED 403
#define NOT_FOUND 404
#define NOT_ALLOWED 405
#define TIME_OUT 408
#define LENGTH_REQUIRED 411
#define PRECONDITION_FAILED 412
#define INTERNAL_ERROR 500
#define NOT_IMPLEMENTED 501
nosave private mapping status_lines = ([
   100 : "100 Continue",
   101 : "101 Switching Protocols",
   200 : "200 OK",
   201 : "201 Created",
   202 : "202 Accepted",
   203 : "203 Non-Authoritative Information",
   204 : "204 No Content",
   205 : "205 Reset Content",
   206 : "206 Partial Content",
   300 : "300 Multiple Choices",
   301 : "301 Moved Permanently",
   302 : "302 Moved Temporarily",
   303 : "303 See Other",
   304 : "304 Not Modified",
   305 : "305 Use Proxy",
   400 : "400 Bad Request",
   401 : "401 Authorization Required",
   402 : "402 Payment Required",
   403 : "403 Forbidden",
   404 : "404 File Not Found",
   405 : "405 Method Not Allowed",
   406 : "406 Not Acceptable",
   407 : "407 Proxy Authentication Required",
   408 : "408 Request Time-out",
   409 : "409 Conflict",
   410 : "410 Gone",
   411 : "411 Length Required",
   412 : "412 Precondition Failed",
   413 : "413 Request Entity Too Large",
   414 : "414 Request-URI Too Large",
   415 : "415 Unsupported Media Type",
   500 : "500 Internal Server Error",
   501 : "501 Method Not Implemented",
   502 : "502 Bad Gateway",
   503 : "503 Service Temporarily Unavailable",
   504 : "504 Gateway Time-out",
   505 : "505 HTTP Version Not Supported",
   506 : "506 Variant Also Varies"
]);
#define SAVE_FILE "/net/save/http"
#define status_drops_connection(x) (((x) == BAD_CMD)          || \
                                    ((x) == TIME_OUT)         || \
                                    ((x) == INTERNAL_ERROR)   || \
                                    ((x) == LENGTH_REQUIRED))
#undef DEBUG
#ifdef DEBUG
#define TP(STR) if (find_player("ceres")) tell_object(find_player("ceres"), STR)
#else
#define TP(STR)
#endif
#define RES_DIR    0
#define RES_FILE   1
#define RES_NORMAL 2
#define DAYS ({"Sun", "Mon", "Tue", "Wed", "Thu", \
         "Fri", "Sat"})
#define MONTHS ({"Jan", "Feb", "Mar", "Apr", "May", "Jun", \
     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"})
class http_session {
  int fd;
  int time;
  string address;
  string name;
}
class http_body {
  int state;
  int remaining;
  int read_chunked;
  int read_length;
  string buff;
  mapping data;
}
class http_request_header {
  int noheaders;
  class mime_header headers_in;
  class mime_header headers_out;
  class mime_header err_headers_out;
  int header_only;
}
class http_body_info {
  string content_type;
  int chunked;
  int clength;
  int byterange;
  string boundary;
  string range;
}
class http_request {
  class http_session sess;
  string hostname;
  int time;
  string request;
  string status_line;
  int status;
  int proto_num;
  string method;
  string uri;
  string args;
  string filename;
  string dir;
  string user;
  class http_request_header rh;
  string location;
  int id;
  string the_request;
  int state;
  int persistent;
  string compression;
  int proxyreq;
  int numredirect;
  int cgi_request;
  class http_body body;
  class http_body_info bi;
  class http_request prev;
  int delayed;
}
#endif