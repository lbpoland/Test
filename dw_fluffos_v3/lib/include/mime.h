#ifndef __MIME_H
#define __MIME_H
#define MIME "/obj/handlers/mime"
#define isspace(c) (((c) == ' ') || ((c) == '\t') || ((c) == '\n') || \
                    ((c) == 12) || ((c) == '\r') || ((c) == 11))
#define iscntrl(c) (((c) == 127) || (((c) >= 0) && ((c) <= 31)))
#define isxdigit(c) ((((c) >= 'A') && ((c) <= 'F')) || \
                     (((c) >= 'a') && ((c) <= 'f')) || \
                     (((c) >= '0') && ((c) <= '9')))
#define isalnum(c) ((((c) >= '0') && ((c) <= '9')) || \
                    (((c) >= 'A') && ((c) <= 'Z')) || \
                    (((c) >= 'a') && ((c) <= 'z')))
#define isdigit(c) (((c) >= '0') && ((c) <= '9'))
class mime_header {
  mapping header_m;
  string *header_k;
}
#endif