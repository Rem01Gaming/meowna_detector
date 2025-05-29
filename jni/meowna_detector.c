#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

bool is_meow_installed(void) {
    char* cmd = "pm list packages </dev/null 2>&1 | cat | grep -q meow.helper";
    if (system(cmd) == 0) {
        printf("meow.helper is installed!\n");
        return true;
    } else {
        return false;
    }
}

bool is_logd_dead(void) {
    struct stat st;
    if (stat("/dev/socket/logdw", &st) == 0) {
        // Logd socket exists (running on privileged env)
        return false;
    } else {
        if (errno == ENOENT) {
            // Logd socket does not exist (logd is dead!)
            printf("Logd socket is missing!\n");
            return true;
        } else {
            // Permission denied or other errors (running on unprivileged env)
            return false;
        }
    }
}

int main(void) {
    if (is_logd_dead() || is_meow_installed()) {
        printf("Meowna detected 🔥🗑️🚮\n");
        return 1;
    } else {
        printf("I didn't see Meowna 👅✅\n");
        return 0;
    }
}
