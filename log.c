/**
 * @file log.c
 * @author Max Rimlinger
 *
 * Functions to log info to a log file
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

#include "types.h"

const int MAX_STATUS_BAR_MSG_LEN = 200;

/**
 * Logs a message to the mim.log file. No \n needed at the end of the message.
 * Use params just like printf.
 */
void log_to_file(const char *fmt, ...) {
    FILE *file = fopen("mim.log", "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening mim.log\n");
    }

    time_t curr_time = time(NULL);
    char *time_str = ctime(&curr_time);
    time_str[strlen(time_str)-1] = '\0';

    va_list args;
    va_start(args, fmt);

    fprintf(file, "[%s] ", time_str);
    vfprintf(file, fmt, args);
    fprintf(file, "\n");

    fclose(file);
    va_end(args);
}

/** Clears the log file */
void clear_log() {
    FILE *file = fopen("mim.log", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening mim.log\n");
    }
    fprintf(file, "");
    fclose(file);
}

/**
 * Logs a message to the status bar. Use params just like printf.
 */
void log_to_status_bar(MimState *ms, const char *fmt, ...) {
    char msg[MAX_STATUS_BAR_MSG_LEN];

    time_t curr_time = time(NULL);
    char *time_str = ctime(&curr_time);
    time_str[strlen(time_str)-1] = '\0';

    va_list args;
    va_start(args, fmt);

    sprintf(msg, "[%s] ", time_str);
    vsprintf(msg, fmt, args);

    va_end(args);

    ms->status_msg = msg;
    log_to_file("len of msg: %lu", strlen(msg));
}
