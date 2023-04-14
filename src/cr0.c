#include <asm/paravirt.h>
#include <linux/kern_levels.h>

static inline void _write_cr0(unsigned long val)
{
  unsigned long __force_order;

  asm volatile(
      "mov %0, %%cr0": "+r"(val), "+m"(__force_order));
}
void _check_wr(void)
{
  unsigned long cr0 = read_cr0();
  if ((cr0 & 0x00010000) != 0x00010000)
    {
        //printk(KERN_INFO "ARK:: 0x%lx", cr0);
        printk(KERN_WARNING "ARK:: WP  disabled! Enabling...\n");
        _write_cr0(cr0);
    }
    else
    {
        //printk(KERN_INFO "DWR:: 0x%lx", cr0);
        printk(KERN_INFO "ARK:: WP enabled!\n");
    }
}
static inline void _enable_wr(unsigned long cr0){
    _write_cr0(cr0 | 0x00010000);
    _check_wr();
}