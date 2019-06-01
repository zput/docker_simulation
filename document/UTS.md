


> Question: What's a UTS namespace?

It means the process has a separate copy of the hostname and the (now mostly unused) NIS domain name, so it can set it to something else without affecting the rest of the system.

The hostname is set via sethostname and is the nodename member of the struct returned by uname. The NIS domain name is set by setdomainname and is the domainname member of the struct returned by uname.

UTS stands for **UNIX Timesharing System**.

References:

lwn.net - Namespaces in operation, part 1: namespaces overview
uts namespaces: Introduction
man uname(2)
Meaning of UTS in UTS_RELEASE


Notice: 上面的程序你会发现（需要root权限)




































