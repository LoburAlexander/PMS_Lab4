#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>

int first = 0, second = 0;
char operation = '+';

ssize_t calc_result_read(struct file *filp, char *buf, size_t count, loff_t *offp)
{
	int len, result = 0;
	char number[12];
	
	if (operation == '+')
		result = first + second;
	if (operation == '-')
		result = first - second;
	if (operation == '*')
		result = first * second;
	if (operation == '/') {
		if (second != 0)
			result = first / second;
		else
			printk(KERN_INFO "Division by zero.\n");
	}

	len = sprintf(number, "%d\n", result);

	if (count < len)
		return -EINVAL;
	if (*offp >= len)
                return 0;
	if (*offp + count > len)
        	count = len - *offp;

	strcpy(buf, number);
	*offp += len;

	return len;
}

ssize_t calc_first_write(struct file *filp, const char *buf, size_t count, loff_t *offp)
{
	int i = 0, tmp = 0, sign = 1;
	
	if (buf[0] == '-')
		sign = -1;
	else if (buf[0] < '0' || buf[0] > '9') {
		printk(KERN_INFO "Invalid parameter.\n");
		return count;
	} else {
		tmp = tmp * 10 + (buf[0]-'0');	
	}

	for (i = 1; i < count - 1; ++i) {
		if (buf[i] < '0' || buf[i] > '9') {
			printk(KERN_INFO "Invalid parameter.\n");
			return count;
		} else {
			tmp = tmp * 10 + (buf[i]-'0');
		}
	}

	first = tmp * sign;
	return count;
}

ssize_t calc_second_write(struct file *filp, const char *buf, size_t count, loff_t *offp)
{
	int i = 0, tmp = 0, sign = 1;
	
	if (buf[0] == '-')
		sign = -1;
	else if (buf[0] < '0' || buf[0] > '9') {
		printk(KERN_INFO "Invalid parameter.\n");
		return count;
	} else {
		tmp = tmp * 10 + (buf[0]-'0');	
	}

	for (i = 1; i < count - 1; ++i) {
		if (buf[i] < '0' || buf[i] > '9') {
			printk(KERN_INFO "Invalid parameter.\n");
			return count;
		} else {
			tmp = tmp * 10 + (buf[i]-'0');
		}
	}

	second = tmp * sign;
	return count;
}

ssize_t calc_operation_write(struct file *filp, const char *buf, size_t count, loff_t *offp)
{
	if (count > 2 || (buf[0] != '+' && buf[0] != '-' && buf[0] != '*' && buf[0] != '/')) {
		printk(KERN_INFO "Invalid operation.\n");
		return count;
	}

	operation = buf[0];

	return count;
}


static const struct file_operations calc_result_fops = {
	.owner = THIS_MODULE,
	.read = calc_result_read
};

static const struct file_operations calc_first_fops = {
	.owner = THIS_MODULE,
	.write = calc_first_write
};

static const struct file_operations calc_second_fops = {
	.owner = THIS_MODULE,
	.write = calc_second_write
};

static const struct file_operations calc_operation_fops = {
	.owner = THIS_MODULE,
	.write = calc_operation_write
};


static int __init calc_proc_init(void) 
{
	proc_create("calc_proc_result", 0, NULL, &calc_result_fops);
	proc_create("calc_proc_first", 0666, NULL, &calc_first_fops);
	proc_create("calc_proc_second", 0666, NULL, &calc_second_fops);
	proc_create("calc_proc_operation", 0666, NULL, &calc_operation_fops);
	return 0;
}

static void __exit calc_proc_exit(void) 
{
	remove_proc_entry("calc_proc_result", NULL);
	remove_proc_entry("calc_proc_first", NULL);
	remove_proc_entry("calc_proc_second", NULL);
	remove_proc_entry("calc_proc_operation", NULL);
}

MODULE_LICENSE("GPL");
module_init(calc_proc_init);
module_exit(calc_proc_exit);

