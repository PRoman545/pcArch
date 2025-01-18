#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Hello, world module");
MODULE_AUTHOR("IO-26 Pindrus Roman");

uint param = 1;
module_param(param, uint, 0444);
MODULE_PARM_DESC(param, "UINT, the amount of times 'Hello, world!' will repeat\n");

struct list_struct {
	struct list_head list;
	ktime_t time;
};
static LIST_HEAD(list_list);
int i;

static int __init hello_init(void)
{
	struct list_struct *list_link;

	switch (param) {
	case 0:
		printk(KERN_WARNING "Warning: Parameter = 0\n");
		break;
	case 5 ... 10:
		printk(KERN_WARNING "Warning: Parameter >=5 & <=10\n");
		break;
	default:
		if (param > 10) {
			printk(KERN_ERR "Error: Parameter >10");
			return -EINVAL;
		}
		break;
	}
	for (i = 0; i < param; i++) {
		list_link = kmalloc(sizeof(*list_link), GFP_KERNEL);
		if (!list_link) {
			printk(KERN_ERR "Error: Memory Error\n");
			return -ENOMEM;
		}
		list_link->time = ktime_get();
		INIT_LIST_HEAD(&list_link->list);
		list_add_tail(&list_link->list, &list_list);
		printk(KERN_INFO "Hello, world!\n");
	}
	return 0;
}

static void __exit hello_exit(void)
{
	struct list_struct *loop, *tmp;

	printk(KERN_INFO "Farewell, world!\n");
	list_for_each_entry_safe(loop, tmp, &list_list, list) {
	printk(KERN_INFO "%d\n", loop->time);
	list_del(&loop->list);
	kfree(loop);
	}
}

module_init(hello_init);
module_exit(hello_exit);
