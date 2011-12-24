#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/module.h>
#include <linux/kallsyms.h>

int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
        printk("pre_handler: p->addr=0x%p, eflags=0x%lx\n",p->addr,
               regs->flags);
        return 0;
}

void handler_post(struct kprobe *p, struct pt_regs *regs, unsigned long flags)
{
        printk("post_handler: p->addr=0x%p, eflags=0x%lx \n", p->addr,
               regs->flags);
}

int handler_fault(struct kprobe *p, struct pt_regs *regs, int trapnr)
{
        printk("fault_handler:p->addr=0x%p, eflags=0x%lx\n", p->addr,
               regs->flags);
        return 0;
}

static struct kprobe kp = {
        .pre_handler    = handler_pre,
        .post_handler   = handler_post,
        .fault_handler  = handler_fault,
};

static __init int kp_test_init(void)
{
	kp.addr = (kprobe_opcode_t *) kallsyms_lookup_name("do_fork");
        register_kprobe(&kp);
        return 0;
}
module_init(kp_test_init);

static __exit void kp_test_exit(void)
{
        unregister_kprobe(&kp);
}
module_exit(kp_test_exit);
MODULE_LICENSE("GPL");
