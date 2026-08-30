#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>

int main(void)
{
    setbuf(stdin, NULL), setbuf(stdout, NULL);

    struct input_event event;
    while (1)
    {
        ssize_t bytes_read = read(STDIN_FILENO, &event, sizeof(event));

        if (bytes_read != sizeof(event)) break;
        else if (bytes_read == -1) break;


        if (event.type == EV_KEY && event.code == KEY_X)
            event.code = KEY_Y;

        fwrite(&event, sizeof(event), 1, stdout);
    }
    fprintf(stderr, "bytes: 555\n");
}
