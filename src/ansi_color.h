#ifndef ANSI_COLOR_H
#define ANSI_COLOR_H
/*
 * You could add an ASCII mode by instetad setting the
 * background color. And then printing spaces.
 */

#define GRNSTR "\x1B[1;32m"
#define REDSTR "\x1B[1;31m"
#define ORGSTR "\x1B[0;33m"
#define YELSTR "\x1B[1;33m"
#define BLUSTR "\x1B[0;34m"
#define MAGSTR "\x1B[1;35m"
#define CYASTR "\x1B[0;36m"

#define DEFSTR "\x1B[m"

#endif // ANSI_COLOR_H
