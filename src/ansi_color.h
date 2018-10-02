#ifndef ANSI_COLOR_H
#define ANSI_COLOR_H
/*
 * You could add an ASCII mode by instetad setting the
 * background color. And then printing spaces.
 */

#define GREENSTR   "\x1B[1;32m"
#define REDSTR     "\x1B[1;31m"
#define ORANGESTR  "\x1B[0;33m"
#define YELLOWSTR  "\x1B[1;33m"
#define BLUESTR    "\x1B[0;34m"
#define MAGENTASTR "\x1B[1;35m"
#define CYANSTR    "\x1B[0;36m"

#define DEFSTR "\x1B[m"

#endif /* ANSI_COLOR_H */
