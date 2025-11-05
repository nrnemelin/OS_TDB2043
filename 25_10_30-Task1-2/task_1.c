#include <stdio.h>
#include <stdlib.h>

int mutex = 1, full = 0, empty = 3, x = 0;

int wait(int s);
int signal(int s);
void producer();
void consumer();

int main() {
    int n;

    printf("\n1. PRODUCER\n2. CONSUMER\n3. EXIT\n");

    while (1) {
        printf("\nENTER YOUR CHOICE: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                if ((mutex == 1) && (empty != 0))
                    producer();
                else
                    printf("\nBUFFER IS FULL!");
                break;

            case 2:
                if ((mutex == 1) && (full != 0))
                    consumer();
                else
                    printf("\nBUFFER IS EMPTY!");
                break;

            case 3:
                printf("\nExiting program...\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please enter 1, 2, or 3.\n");
                break;
        }
    }
}

int wait(int s) {
    return (--s);
}

int signal(int s) {
    return (++s);
}

void producer() {
    mutex = wait(mutex);
    empty = wait(empty);
    full = signal(full);
    x++;
    printf("\nProducer produces item %d", x);
    mutex = signal(mutex);
}

void consumer() {
    mutex = wait(mutex);
    full = wait(full);
    empty = signal(empty);
    printf("\nConsumer consumes item %d", x);
    x--;
    mutex = signal(mutex);
}
