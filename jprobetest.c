#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>

#include <linux/bottom_half.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/module.h>
#include <linux/random.h>
#include <linux/cache.h>
#include <linux/jhash.h>
#include <linux/init.h>
#include <linux/times.h>
#include <linux/slab.h>

#include <net/net_namespace.h>
#include <net/icmp.h>
#include <net/inet_hashtables.h>
#include <net/tcp.h>
#include <net/transp_v6.h>
#include <net/ipv6.h>
#include <net/inet_common.h>
#include <net/timewait_sock.h>
#include <net/xfrm.h>
#include <net/netdma.h>

#include <linux/inet.h>
#include <linux/ipv6.h>
#include <linux/stddef.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include <linux/crypto.h>
#include <linux/scatterlist.h>
#define NIPQUAD(addr) \
    ((unsigned char *)&addr)[0], \
    ((unsigned char *)&addr)[1], \
    ((unsigned char *)&addr)[2], \
    ((unsigned char *)&addr)[3]


struct jprobe jp;

int jp_tcp_v4_rcv(struct sk_buff *skb){
	const struct iphdr *iph;
	struct tcphdr *th;
	th = tcp_hdr(skb);
	iph = ip_hdr(skb);

	printk ("iph->saddr = %d.%d.%d.%d\n",NIPQUAD(iph->saddr));
	printk ("iph->daddr = %d.%d.%d.%d\n",NIPQUAD(iph->daddr));
	printk ("th->sport = %d\n",htons(th->source));
	printk ("th->dest = %d\n",htons(th->dest));
	jprobe_return();
	return 0;
}

static __init int init_jprobe_sample(void)
{
	jp.kp.symbol_name = "tcp_v4_rcv";
	jp.entry = JPROBE_ENTRY(jp_tcp_v4_rcv);
	register_jprobe(&jp);
	return 0;
}
module_init(init_jprobe_sample);
/*
int jp_do_execve(const char * filename,
	const char __user *const __user *argv,
	const char __user *const __user *envp,
	struct pt_regs * regs)
{
	int cnt = 0;
	printk(KERN_INFO "filenme: %s\n", filename);
	printk(KERN_INFO "envp %p\n",envp);

	for(; *argv != NULL; argv++, cnt++)
		printk(KERN_INFO "argv[%d]: %s\n", cnt, *argv);

	jprobe_return();
	return 0;

}


static __init int init_jprobe_sample(void)
{
	jp.kp.symbol_name = "do_execve";
	jp.entry = JPROBE_ENTRY(jp_do_execve);
	register_jprobe(&jp);
	return 0;
}
module_init(init_jprobe_sample);
*/
static __exit void cleanup_jprobe_sample(void)
{
	unregister_jprobe(&jp);
}
module_exit(cleanup_jprobe_sample);

MODULE_LICENSE("GPL");





