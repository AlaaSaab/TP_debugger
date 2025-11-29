#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Use a different random seed each run
    srandom(getpid());

    for (int i = 0; i < 1000; i++) {

        // Generate random number between 0 and 2
        // 0 or 1 → insertion (2/3)
        // 2 → extraction (1/3)
        int choice = random() % 3;

        if (choice < 2) {  // 2/3 probability
            int x = random() % 100;
            int y = random() % 100;
            printf("i %d %d\n", x, y);
        } else {           // 1/3 probability
            printf("e\n");
        }
    }

    // End of commands
    printf("q\n");
    return 0;
}
