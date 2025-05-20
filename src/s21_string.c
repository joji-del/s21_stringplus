#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = str;
  s21_size_t success = n;
  unsigned char ch = (const unsigned)c;
  for (s21_size_t i = 0; i < n; i++) {
    if (ptr[i] == ch) {
      success = i;
    }
  }
  return success == n ? S21_NULL : (void *)(str + success);
}
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *ptr1, *ptr2;
  ptr1 = str1;
  ptr2 = str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (ptr1[i] != ptr2[i]) {
      return (ptr1[i] > ptr2[i]) ? 1 : -1;
    }
  }
  return 0;
}
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  const unsigned char *ptr = (unsigned char *)src;
  unsigned char *arrdest = (unsigned char *)dest;
  for (s21_size_t i = 0; i < n; i++) {
    arrdest[i] = ptr[i];
  }
  return dest;
}
void *s21_memset(void *str, int c, s21_size_t n) {
  if (str != S21_NULL) {
    unsigned char *ptr = (unsigned char *)str;
    for (s21_size_t i = 0; i < n; i++) {
      ptr[i] = (unsigned char)c;
    }
  }
  return str;
}
char *s21_strchr(const char *str, int c) {
  int strLength = s21_strlen(str) + 1;
  const char *result = S21_NULL;
  for (int x = 0; x < strLength && result == S21_NULL; x += 1) {
    if (str[x] == c) {
      result = (str + x);
    }
  }
  return (char *)result;
}
s21_size_t s21_strlen(const char *str) {
  s21_size_t str_len = 0;
  for (; *str != '\0'; str++) {
    str_len += 1;
  }
  return str_len;
}
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  s21_size_t i = 0;
  for (i = 0; i < n; i++) {
    if (str1[i] == '\0' && str2[i] == '\0') {
      res = 0;
    } else if (str1[i] == '\0') {
      res = -1;
    } else if (str2[i] == '\0') {
      res = 1;
    }
    if (str1[i] != str2[i]) {
      return (unsigned char)str1[i] - (unsigned char)str2[i];
    }
  }
  return res;
}
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  for (i = 0; str1[i] != '\0' && !s21_strchr(str2, str1[i]); i++);
  return i;
}
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int destLength = s21_strlen(dest);

  for (s21_size_t x = 0; x < n && src[x] != '\0'; x++) {
    dest[destLength + x] = src[x];
    dest[destLength + x + 1] = '\0';
  }
  return dest;
}
char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t strLength = s21_strlen(str1);
  s21_size_t shift = 0;
  int status = 0;
  const char *result = S21_NULL;
  for (shift = 0; status == 0 && shift < strLength; shift += 1) {
    if (s21_strchr(str2, str1[shift])) {
      status = 1;
      result = (char *)(str1 + shift);
    }
  }
  return (char *)result;
}
char *s21_strrchr(const char *str, int c) {
  int strLength = s21_strlen(str);
  const char *result = S21_NULL;
  for (int x = strLength; result == S21_NULL && x >= 0; x -= 1) {
    if (str[x] == c) {
      result = (str + x);
    }
  }
  return (char *)result;
}
char *s21_strstr(const char *haystick, const char *needle) {
  size_t srcptrLength = s21_strlen(needle);
  const char *result = S21_NULL;

  if (srcptrLength != 0) {
    for (int x = 0; result == S21_NULL && haystick[x] != '\0'; x += 1) {
      if (haystick[x] == needle[0]) {
        if (s21_strncmp(haystick + x, needle, srcptrLength) == 0)
          result = haystick + x;
      }
    }
  } else {
    result = haystick;
  }
  return (char *)result;
}
char *s21_strtok(char *str, const char *delim) {
  static char *nexttok = S21_NULL;
  if (str == S21_NULL) {
    str = nexttok;
  }
  if (delim != S21_NULL && str != S21_NULL) {
    nexttok = S21_NULL;
    for (s21_size_t i = 0; str[i] && nexttok == S21_NULL; i++) {
      if (s21_strchr(delim, (int)str[i])) {
        if (i == 0) {
          i--;
          str += 1;
        } else {
          if (str[i + 1]) nexttok = &str[i + 1];
          str[i] = '\0';
        }
      }
    }
  }
  return (*str) ? str : S21_NULL;
}
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  int srcLength = s21_strlen(src);
  int cpyLength = 0;
  if (n > (s21_size_t)srcLength) {
    cpyLength = srcLength + 1;
  } else {
    cpyLength = n;
  }

  for (int x = 0; x < cpyLength; x += 1) {
    dest[x] = src[x];
  }

  return dest;
}
void *s21_to_upper(const char *str) {
  s21_size_t t = s21_strlen(str);
  char *new_str = (char *)malloc((t + 1) * sizeof(char));
  if (new_str) {
    for (s21_size_t i = 0; i < t; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        new_str[i] = str[i] + 'A' - 'a';
      } else {
        new_str[i] = str[i];
      }
    }
    new_str[t] = '\0';
  }
  return new_str;
}
void *s21_to_lower(const char *str) {
  s21_size_t t = s21_strlen(str);
  char *new_str = (char *)malloc((t + 1) * sizeof(char));
  if (new_str) {
    for (s21_size_t i = 0; i < t; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        new_str[i] = str[i] + 'a' - 'A';
      } else {
        new_str[i] = str[i];
      }
    }
    new_str[t] = '\0';
  }
  return new_str;
}
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) {
    return S21_NULL;
  }

  s21_size_t t1 = s21_strlen(src);
  s21_size_t t2 = s21_strlen(str);

  if (start_index > t1) {
    return S21_NULL;
  }

  static char new_str[1024];
  s21_size_t all_len = t1 + t2;
  if (all_len >= 1024) {
    return S21_NULL;
  }

  s21_size_t i = 0, pos = 0;
  for (; i < t1; i++) {
    if (i == start_index) {
      for (s21_size_t j = 0; j < t2; j++) {
        new_str[pos++] = str[j];
      }
    }
    new_str[pos++] = src[i];
  }

  if (start_index == t1) {
    for (s21_size_t j = 0; j < t2; j++) {
      new_str[pos++] = str[j];
    }
  }

  new_str[pos] = '\0';
  return new_str;
}
void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL) return S21_NULL;

  const char *start = src;
  while (*start != '\0' && s21_strchr(trim_chars, *start) != S21_NULL) start++;

  const char *end = start + s21_strlen(start) - 1;
  while (end >= start && s21_strchr(trim_chars, *end) != S21_NULL) end--;

  s21_size_t len = (s21_size_t)(end - start) + 1;
  char *result = (char *)malloc((len + 1) * sizeof(char));
  if (result != S21_NULL) {
    s21_strncpy(result, start, len);
    result[len] = '\0';
  }

  return result;
}
char *s21_strerror(int errnum) {
  static char result[512] = {'\0'};

#if defined(__APPLE__) || defined(__MACH__)
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1

  static const char *errorList[] = {
      "Undefined error: 0",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "Device not configured",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource deadlock avoided",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Resource busy",
      "File exists",
      "Cross-device link",
      "Operation not supported by device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Result too large",
      "Resource temporarily unavailable",
      "Operation now in progress",
      "Operation already in progress",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol family",
      "Address already in use",
      "Can't assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Socket is already connected",
      "Socket is not connected",
      "Can't send after socket shutdown",
      "Too many references: can't splice",
      "Operation timed out",
      "Connection refused",
      "Too many levels of symbolic links",
      "File name too long",
      "Host is down",
      "No route to host",
      "Directory not empty",
      "Too many processes",
      "Too many users",
      "Disc quota exceeded",
      "Stale NFS file handle",
      "Too many levels of remote in path",
      "RPC struct is bad",
      "RPC version wrong",
      "RPC prog. not avail",
      "Program version wrong",
      "Bad procedure for program",
      "No locks available",
      "Function not implemented",
      "Inappropriate file type or format",
      "Authentication error",
      "Need authenticator",
      "Device power is off",
      "Device error",
      "Value too large to be stored in data type",
      "Bad executable (or shared library)",
      "Bad CPU type in executable",
      "Shared library version mismatch",
      "Malformed Mach-o file",
      "Operation canceled",
      "Identifier removed",
      "No message of desired type",
      "Illegal byte sequence",
      "Attribute not found",
      "Bad message",
      "EMULTIHOP (Reserved)",
      "No message available on STREAM",
      "ENOLINK (Reserved)",
      "No STREAM resources",
      "Not a STREAM",
      "Protocol error",
      "STREAM ioctl timeout",
      "Operation not supported on socket",
      "Policy not found",
      "State not recoverable",
      "Previous owner died",
      "Interface output queue is full"};

#elif defined(__linux__)
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1

  static const char *errorList[] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Device or resource busy",
      "File exists",
      "Invalid cross-device link",
      "No such device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Numerical result out of range",
      "Resource deadlock avoided",
      "File name too long",
      "No locks available",
      "Function not implemented",
      "Directory not empty",
      "Too many levels of symbolic links",
      "Unknown error 41",
      "No message of desired type",
      "Identifier removed",
      "Channel number out of range",
      "Level 2 not synchronized",
      "Level 3 halted",
      "Level 3 reset",
      "Link number out of range",
      "Protocol driver not attached",
      "No CSI structure available",
      "Level 2 halted",
      "Invalid exchange",
      "Invalid request descriptor",
      "Exchange full",
      "No anode",
      "Invalid request code",
      "Invalid slot",
      "Unknown error 58",
      "Bad font file format",
      "Device not a stream",
      "No data available",
      "Timer expired",
      "Out of streams resources",
      "Machine is not on the network",
      "Package not installed",
      "Object is remote",
      "Link has been severed",
      "Advertise error",
      "Srmount error",
      "Communication error on send",
      "Protocol error",
      "Multihop attempted",
      "RFS specific error",
      "Bad message",
      "Value too large for defined data type",
      "Name not unique on network",
      "File descriptor in bad state",
      "Remote address changed",
      "Can not access a needed shared library",
      "Accessing a corrupted shared library",
      ".lib section in a.out corrupted",
      "Attempting to link in too many shared libraries",
      "Cannot exec a shared library directly",
      "Invalid or incomplete multibyte or wide character",
      "Interrupted system call should be restarted",
      "Streams pipe error",
      "Too many users",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol",
      "Address already in use",
      "Cannot assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Transport endpoint is already connected",
      "Transport endpoint is not connected",
      "Cannot send after transport endpoint shutdown",
      "Too many references: cannot splice",
      "Connection timed out",
      "Connection refused",
      "Host is down",
      "No route to host",
      "Operation already in progress",
      "Operation now in progress",
      "Stale file handle",
      "Structure needs cleaning",
      "Not a XENIX named type file",
      "No XENIX semaphores available",
      "Is a named type file",
      "Remote I/O error",
      "Disk quota exceeded",
      "No medium found",
      "Wrong medium type",
      "Operation canceled",
      "Required key not available",
      "Key has expired",
      "Key has been revoked",
      "Key was rejected by service",
      "Owner died",
      "State not recoverable",
      "Operation not possible due to RF-kill",
      "Memory page has hardware error"};

#endif
  if (errnum <= MIN_ERRLIST || errnum >= MAX_ERRLIST) {
    sprintf(result, "Unknown error %d", errnum);
  } else {
    s21_memcpy(result, (char *)errorList[errnum],
               s21_strlen((char *)errorList[errnum]) + 1);
  }

  return result;
}