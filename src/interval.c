#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include "../include/syscall_handler.h"
#include "../include/cr0.h"
#include "../include/config.h"

int interval_check(void *args){
    while(!kthread_should_stop()){
      syscall_handler_check();
      _check_wr();
      printk(KERN_INFO "ARK:: All checks done, waiting %d seconds", INTERVAL);
      msleep(1000*INTERVAL);
    }
    return 0;
}