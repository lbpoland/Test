#include <mime.h>
#define HEADER_NAME 1
#define HEADER_VAL  2
#define MUDMAIL     3
#define TOK_QP      4
#define TOK_QUOTE   5
#define TOK_OP      6
#define TOK_CP      7
#define TOK_LT      8
#define TOK_GT      9
#define TOK_SEP     10
#define TOK_AMP     11
#define SPECIAL     12
#define LWS         13
#define ATOM        14
#define COMMENT     15
#define EMAIL       16
#define QUOTE       17
private mixed *tokenize(string header_field) {
  int i, quoted, paren_count, angle_count;
  int *tokens, state;
  mixed *bits;
  bits = reg_assoc(header_field,
                   ({ "\\\\.", "\"", "\\(", "\\)", "<", ">",
                      ",", "@",
                      "[]()<>@,;:\\\\\".[]",
                      "(\n?[ \t])+",
                      "[!#-'*+/-9=?A-Z^-~-]+" }),
                   ({ TOK_QP, TOK_QUOTE, TOK_OP, TOK_CP, TOK_LT, TOK_GT,
                      TOK_SEP, TOK_AMP, SPECIAL, LWS, ATOM }));
  tokens = ({ 0 });
  for (i = 1; i < sizeof(bits[0]); i += 2) {
    switch(bits[1][i]) {
    case LWS:
      if (quoted) {
        tokens += ({ state, 0 });
      } else {
        tokens += ({ 0, 0 });
      }
      break;
    case TOK_QUOTE:
      quoted = !quoted;
      if (!state && quoted) {
        state = QUOTE;
      }
      tokens += ({ state, 0 });
      if (state == QUOTE && !quoted) {
        state = 0;
      }
      break;
    case TOK_OP:
      if (!quoted) {
        paren_count++;
        state = COMMENT;
      }
      tokens += ({ state, 0 });
      break;
    case TOK_CP:
      if (!quoted) {
        paren_count--;
        if (paren_count < 0) {
          printf("Unbalanced ')'\n");
          return ({ });
        }
      }
      tokens += ({ state, 0 });
      if (!paren_count) {
        state = 0;
      }
      break;
    case TOK_LT:
      tokens += ({ state, 0 });
      if (!(quoted || paren_count)) {
        angle_count++;
        state = EMAIL;
      }
      break;
    case TOK_GT:
      if (!(quoted || paren_count)) {
        angle_count--;
        if (angle_count != 0) {
          printf("Unbalanced '%c'\n", (angle_count < 0?'>':'<'));
          return ({ });
        }
        state = 0;
      }
      tokens += ({ state, 0 });
      break;
    default:
      if (!state) {
        tokens += ({ bits[1][i], 0 });
      } else {
        tokens += ({ state, 0 });
      }
      break;
    }
    if (paren_count < 0) {
      printf("Unbalanced ')'\n");
      return ({ });
    }
  }
  if (paren_count != 0) {
    printf("Unbalanced '%c'\n", (paren_count < 0?')':'('));
    return ({ });
  }
  bits += ({ tokens });
  return bits;
}
mixed *get_email_addrs(string arg) {
  string *addrs, *full_addrs;
  int i, idx, state;
  mixed *bits;
  if (!arg) {
    return ({ ({ }), ({ }) });
  }
  bits = tokenize(arg);
  if (!sizeof(bits)) {
    return ({ ({ }), ({ }) });
  }
  addrs = allocate(1);
  addrs[0] = "";
  full_addrs = allocate(1);
  full_addrs[0] = "";
  idx = 0;
  for (i = 1; i < sizeof(bits[2]); i += 2) {
    switch (bits[2][i]) {
    case TOK_SEP:
      idx++;
      addrs += ({ "" });
      full_addrs += ({ "" });
      break;
    case EMAIL:
      if (state != EMAIL) {
        addrs[idx] = bits[0][i];
        state = EMAIL;
      } else {
        addrs[idx] += bits[0][i];
      }
      full_addrs[idx] += bits[0][i];
      break;
    case COMMENT:
    case LWS:
    case 0:
      full_addrs[idx] += bits[0][i];
      break;
    default:
      addrs[idx] += bits[0][i];
      full_addrs[idx] += bits[0][i];
      break;
    }
  }
  return ({ addrs, full_addrs });
}
string rewrite_field(string header_field) {
  int i, idx, state;
  mixed *bits, *addrs, *indices;
  if (!header_field) {
    return "";
  }
  bits = tokenize(header_field);
  if (!sizeof(bits)) {
    return "";
  }
  addrs = allocate(1);
  addrs[0] = ({ });
  indices = allocate(1);
  indices[0] = ({ });
  idx = 0;
  for (i = 1; i < sizeof(bits[2]); i += 2) {
    switch (bits[2][i]) {
    case TOK_SEP:
      if (sizeof(addrs[idx]) && member_array(TOK_AMP, addrs[idx]) == -1) {
        if (bits[0][indices[idx][<1]] == "discworld") {
          bits[0][indices[idx][<1]] += "@discworld.imaginary.com";
        } else {
          bits[0][indices[idx][<1]] += ".discworld@discworld.imaginary.com";
        }
      }
      idx++;
      addrs += ({ ({ }) });
      indices += ({ ({ }) });
      break;
    case EMAIL:
      if (state != EMAIL) {
        addrs[idx] = ({ bits[1][i] });
        indices[idx] = ({ i });
        state = EMAIL;
      } else {
        addrs[idx] += ({ bits[1][i] });
        indices[idx] += ({ i });
      }
      break;
    case COMMENT:
    case LWS:
    case 0:
      break;
    default:
      addrs[idx] += ({ bits[1][i] });
      indices[idx] += ({ i });
      break;
    }
  }
  if (sizeof(addrs[<1]) && member_array(TOK_AMP, addrs[<1]) == -1) {
    if (bits[0][indices[<1][<1]] == "discworld") {
      bits[0][indices[<1][<1]] += "@discworld.imaginary.com";
    } else {
      bits[0][indices[<1][<1]] += ".discworld@discworld.imaginary.com";
    }
  }
  return implode(bits[0], "");
}
class mime_header parse_headers(string message) {
  string *bits, bit, cont, headers;
  int idx, len;
  class mime_header hdr;
  if ((idx = strsrch(message, "\n\n")) == -1) {
    return hdr;
  }
  headers = message[0..idx];
  hdr = new(class mime_header, header_m : ([]), header_k : ({}));
  bits = explode(headers, "\n") - ({ "", 0 });
  foreach (bit in bits[1..]) {
    if (cont && ((bit[0] == ' ') || (bit[0] == '\t'))) {
      hdr->header_m[cont] += "\n" + bit[1..];
      continue;
    }
    len = strlen(bit);
    if ((idx = strsrch(bit, ':')) == -1) {
      continue;
    }
    cont = bit[0..idx-1];
    if (undefinedp(hdr->header_m[lower_case(cont)])) {
      hdr->header_k += ({ cont });
    }
    cont = lower_case(cont);
    ++idx;
    while ((idx < len) && isspace(bit[idx])) {
      ++idx;
    }
    if (undefinedp(hdr->header_m[cont])) {
      hdr->header_m[cont] = bit[idx..];
    } else {
      hdr->header_m[cont] += sprintf(", %s", bit[idx..]);
    }
  }
  return hdr;
}
string rewrite_header(string message) {
  mixed *ra;
  int i;
  string header, field;
  if ((i = strsrch(message, "\n")) == -1) {
    return message;
  }
  message = message[i+1..];
  if ((i = strsrch(message, "\n\n")) == -1) {
    return message;
  }
  header = message[0..i];
  message = message[i+1..];
  ra = reg_assoc(header,
                 ({ "^[!-9;-~]+:", "((\n?[ \t])+[^\n]*(\n|$))+" }),
                 ({ HEADER_NAME, HEADER_VAL }));
  for (i = 1; i + 2 < sizeof(ra[0]); i += 2) {
    if (ra[1][i] == HEADER_NAME && ra[1][i+2] == HEADER_VAL) {
      switch(lower_case(ra[0][i])) {
      case "to:":
      case "from:":
      case "cc:":
      case "bcc:":
      case "reply-to:":
        field = rewrite_field(ra[0][i+2]);
        if (field != "") {
          ra[0][i+2] = field;
        }
        break;
      default:
        break;
      }
    }
  }
  return implode(ra[0], "") + message;
}
void dest_me() {
  destruct(this_object());
}
int cleanup(int inherited) {
  if (!inherited) {
    dest_me();
  }
  return 1;
}