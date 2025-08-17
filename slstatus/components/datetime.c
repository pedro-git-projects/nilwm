// patched to be have an optional TZ parameter
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../slstatus.h"
#include "../util.h"

const char *datetime(const char *fmt) {
  time_t t;
  const char *real_fmt = fmt;
  char tzbuf[64];
  const char *oldtz = getenv("TZ");

  t = time(NULL);

  if (fmt && strncmp(fmt, "TZ=", 3) == 0) {
    const char *tz = fmt + 3;
    const char *space = strchr(tz, ' ');
    if (space) {
      size_t len = space - tz;
      if (len < sizeof(tzbuf)) {
        memcpy(tzbuf, tz, len);
        tzbuf[len] = '\0';
        setenv("TZ", tzbuf, 1);
        tzset();
        real_fmt = space + 1;
      }
    }
  }

  if (!strftime(buf, sizeof(buf), real_fmt, localtime(&t))) {
    warn("strftime: Result string exceeds buffer size");
    buf[0] = '\0';
  }

  /* restore old TZ (or unset if none existed) */
  if (fmt && strncmp(fmt, "TZ=", 3) == 0) {
    if (oldtz)
      setenv("TZ", oldtz, 1);
    else
      unsetenv("TZ");
    tzset();
  }

  return buf;
}
