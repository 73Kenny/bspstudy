#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/input.h>


#define KERR_LOG printk(KERN_ERR "DEMO: Line %d, function %s()\n", __LINE__, __func__)

static struct input_dev *key_input;

static int hello_open(struct inode *inode, struct file *filp){
    KERR_LOG;
    return 0;
}

static int hello_release(struct inode *inode, struct file *filp){
    KERR_LOG;
    return 0;
}

static ssize_t hello_read(struct file *filp, char __user* buf, size_t size, loff_t *pos){
    KERR_LOG;
    
    // key report
    input_report_key(key_input, KEY_B, 1); 
    input_sync(key_input);
    input_report_key(key_input, KEY_B, 0); 
    input_sync(key_input);
    return 0;
}

static ssize_t hello_write(struct file *filp, const char __user* buf, size_t size, loff_t *pos){    
    KERR_LOG;
    return 0;
}

static struct file_operations misc_ops = { 
    .owner = THIS_MODULE,
    .open = hello_open,
    .release = hello_release,
    .read = hello_read,
    .write = hello_write,
};

static struct miscdevice misc_dev = { 
    .minor = MISC_DYNAMIC_MINOR,
    .name = "hello_misc_node",
    .fops = &misc_ops,
};

static int __init misc_init(void){
    int ret;
    ret = misc_register(&misc_dev);
    if(ret < 0){
        printk("DEMO: register failed\n");
        return -1;
    }

    key_input = devm_input_allocate_device(misc_dev.this_device);
    if(!key_input){
        printk("DEMO: devm_input_allocate_device failed\n");
        misc_deregister(&misc_dev);
        return -ENOMEM;
    }

    input_set_capability(key_input, EV_KEY, KEY_B);
    ret = input_register_device(key_input);
    if(ret){
        printk("DEMO: input_register_device\n");
        input_free_device(key_input);
        return ret;
    }

    printk("DEMO: register succeed\n");

    return 0;
}

static void __exit misc_exit(void){
    input_unregister_device(key_input);
    misc_deregister(&misc_dev);
    printk("DEMO: misc deregister\n");
}

module_init(misc_init);
module_exit(misc_exit);
MODULE_LICENSE("GPL");


                                                                      
