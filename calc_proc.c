#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>
//#include <asm/uaccess.h>

int first = 0, second = 0;
char operation = '+';

ssize_t calc_result_read(struct file *filp, char *buf, size_t count, loff_t *offp)
{
	int len;
	char number[15];
	
	len = sprintf(number, "%d\n", first + second);

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

ssize_t calc_first_write(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	int i = 0;
	first = 0;
	for (i = 0; i < count - 1; ++ i)
		first = first * 10 + (buf[i]-'0');
	return count;
}

ssize_t calc_second_write(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	int i = 0;
	second = 0;
	for (i = 0; i < count - 1; ++ i)
		second = second * 10 + (buf[i]-'0');
	return count;
}


static const struct file_operations calc_result_fops = {
	.owner = THIS_MODULE,
	.read = calc_result_read,
};

static const struct file_operations calc_first_fops = {
	.owner = THIS_MODULE,
	.write = calc_first_write,
};

static const struct file_operations calc_second_fops = {
	.owner = THIS_MODULE,
	.write = calc_second_write,
};


static int __init calc_proc_init(void) 
{
	proc_create("calc_proc_result", 0, NULL, &calc_result_fops);
	proc_create("calc_proc_first", 0666, NULL, &calc_first_fops);
	proc_create("calc_proc_second", 0666, NULL, &calc_second_fops);
	return 0;
}

static void __exit calc_proc_exit(void) 
{
	remove_proc_entry("calc_proc_result", NULL);
	remove_proc_entry("calc_proc_first", NULL);
	remove_proc_entry("calc_proc_second", NULL);
}

MODULE_LICENSE("GPL");
module_init(calc_proc_init);
module_exit(calc_proc_exit);
