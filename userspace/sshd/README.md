# Kadad SSH Server

SSH is a first-class userspace service for the VPS/headless edition of KadadOS.

Target flow:

```
SSH client
   |
   v
Kadad sshd
   |
   v
Kadad Shell
```

The implementation will be added after the kernel networking and TCP/IP stack are available.
