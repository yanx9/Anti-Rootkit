#include <linux/kernel.h>
//#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/linkage.h>
#include <linux/version.h>
#include <linux/namei.h>
#include <linux/signal.h>
#include <linux/delay.h>
#include <linux/kthread.h>

#include "include/syscall_handler.h"
#include "include/cr0.h"
#include "include/interval.h"

#if !defined(CONFIG_X86_64)
#define VERSION_NOT_SUPPORTED
#endif

MODULE_LICENSE("GPL");
struct task_struct *thread;
int err;

  static int __init mod_init(void){
      #ifdef VERSION_NOT_SUPPORTED
        printk(KERN_ERR "ARK:: Version not supported");
        return -1;
      #endif
      
      syscall_handler_init();
      printk(KERN_INFO "ARK:: Init checks done");

      thread = kthread_run(interval_check, NULL, "ARKm thread");
      if (IS_ERR(thread)) {
        printk(KERN_ERR "ARK:: Cannot create thread\n");
        err = PTR_ERR(thread);
        thread = NULL;
        return err;
    }
      return 0;
  }
  static void __exit mod_exit(void){
      kthread_stop(thread);
      printk(KERN_INFO "ARK:: Module successfully unloaded");
  }
  
module_init(mod_init);
module_exit(mod_exit);