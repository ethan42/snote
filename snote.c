#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void maintenance() {
    execl("/bin/sh", "sh", NULL);
}

void note(int hour, int min, char *subject, FILE *stream) {
    int __attribute__((no_reorder)) local_min = min;
    int __attribute__((no_reorder)) local_hour = hour;
    char __attribute__((no_reorder)) note_buf[64];

    fread(note_buf, 1, 128, stream);

    if ((unsigned int)(local_hour*local_min) > 24*60) {
        printf("*buffer overflow is detected!\n");
        exit(1);
    }

    printf("*Time: %d:%d\n", local_hour, local_min);
    printf("*Subject: %s by CTO\n", subject);
    printf("*Note: %s\n", note_buf);
}

int main(int argc, char *argv[]) {
    time_t now;
    struct tm *ts;
    char* subject = argv[1];
    char* note_file = argv[2];

    if(argc != 3) {
        printf("Usage: %s <subject> <note>\n", argv[0]);
        return -1;
    }

    FILE *fp = fopen(note_file, "r");

    if (fp == NULL) {
        printf("File not found\n");
        return -1;
    }

    time(&now);
    ts = localtime(&now);
    note(ts->tm_hour, ts->tm_min, subject, fp);
    fclose(fp);
    return 0;
}
