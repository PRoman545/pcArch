#include <linux/module.h>
#include <linux/printk.h>
#include "hello.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Hello2 module");
MODULE_AUTHOR("IO-26 Pindrus Roman");

static int counter = 1;
module_param(counter, int, 0444);
MODULE_PARM_DESC(counter, "Number of times to print 'Hello, world!' message");

static int __init hello2_init(void)
{
    if (counter < 0 || counter >= 10) {
        pr_err("Error: count parameter is greater than 10 or less than 0: %d\n", counter);
        return -EINVAL;
    }
    
    if (counter == 0 || (counter >= 5 && counter <= 10)) {
	pr_warn("Warning: count parameter is 0 or between 5 and 10. Continuing.\n");
    }
    
    pr_info("Calling print_hello() from hello1 module\n");
    print_hello(counter);

    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("Goodbye from hello2 module\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
