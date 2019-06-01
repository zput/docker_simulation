
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include<cstdlib>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

/* 定义一个给 clone 用的栈，栈大小1M */
#define STACK_SIZE (1024 * 1024)
static char container_stack[STACK_SIZE];

char* const container_args[] = {
	"/bin/bash",
	NULL
};

/*

mount命令的标准用法是你说的这样：
mount -t type device dir

对于proc文件系统来说，它没有设备，然后我查了一下内核代码，
proc filesystem根本没有处理dev_name这个参数，所以传什么都没有影响，
只影响你的mount命令输出。好的实践应该将设备名指定为nodev。


static struct dentry *proc_mount(struct file_system_type *fs_type,
		int flags, const char *dev_name, void *data)
{
	struct pid_namespace *ns;
	if (flags & MS_KERNMOUNT) {
		ns = data;
		data = NULL;
	} else {
		ns = task_active_pid_ns(current);
	}
	return mount_ns(fs_type, flags, data, ns, ns->user_ns, proc_fill_super);
}


*/


int container_main(void* arg)
{
	printf("Container[%5d] - inside the container!\n", getpid());
	sethostname("container_zxc",10); /* 设置hostname */
	system("mount -t proc myDeviceIsNull /proc");
		execv(container_args[0], container_args);
	printf("Something's wrong!\n");
	return 1;
}

int main()
{
	printf("Parent - start a container!\n");
	int container_pid = clone(container_main, container_stack+STACK_SIZE, 
			CLONE_NEWUTS|CLONE_NEWIPC |CLONE_NEWPID|CLONE_NEWNS| SIGCHLD, NULL); /*启用CLONE_NEWUTS Namespace隔离 */
	waitpid(container_pid, NULL, 0);
	printf("Parent - container stopped!\n");
	return 0;
}
