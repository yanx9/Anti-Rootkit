#include <asm/msr.h>
#include <asm/msr-index.h>

static void *syscall_handler;

static inline void *get_syscall_handler(void){
    unsigned long system_call_entry;
    rdmsrl(MSR_LSTAR, system_call_entry);
    return (void *)system_call_entry;
}

static inline void set_syscall_handler(const void *val){
    wrmsrl(MSR_LSTAR, (unsigned long)val);
}

void syscall_handler_check(void) {
    syscall_handler = get_syscall_handler();
    printk(KERN_INFO "ARK:: MSR-LSTAR address is %px", syscall_handler);
    if (get_syscall_handler() != syscall_handler) {
        printk(KERN_WARNING "ARK:: MSR_LSTAR address changed, recovering...");
        set_syscall_handler(syscall_handler);
    }
}

void syscall_handler_init(void){
    syscall_handler = get_syscall_handler();
}