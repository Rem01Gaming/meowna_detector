#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

bool is_logd_dead(void) {
    struct stat st;
    if (stat("/dev/socket/logdw", &st) == 0) {
        // Logd socket exists (running on privileged env)
        return false;
    } else {
        if (errno == ENOENT) {
            // Logd socket does not exist (logd is dead!)
            return true;
        } else {
            // Permission denied or other errors (running on unprivileged env)
            return false;
        }
    }
}

int main(void) {
    if (is_logd_dead()) {
        printf("Meowna detected 🔥🗑️🚮\n");
        return 1;
    } else {
        printf("I didn't see Meowna 👅✅\n");
        return 0;
    }
}
