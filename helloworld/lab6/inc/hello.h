#ifndef HELLO_H
#define HELLO_H

struct hello_data {
    struct list_head list;
    ktime_t start_time;
    ktime_t end_time;
};

void print_hello(int counter);

#endif
