#if 0
syscall display by "strace stat Makefile":
    execve("/usr/bin/stat", ["stat", "Makefile"], 0x7ffe8c197dc8 /* 28 vars */) = 0
    brk(NULL)                               = 0x5600ae82a000
    arch_prctl(0x3001 /* ARCH_??? */, 0x7ffef18ecc10) = -1 EINVAL (Invalid argument)
    mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f1235e25000
    access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=24459, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 24459, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235e1f000
    close(3)                                = 0
    openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
    read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=166280, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 177672, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f1235df3000
    mprotect(0x7f1235df9000, 139264, PROT_NONE) = 0
    mmap(0x7f1235df9000, 106496, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6000) = 0x7f1235df9000
    mmap(0x7f1235e13000, 28672, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x20000) = 0x7f1235e13000
    mmap(0x7f1235e1b000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x27000) = 0x7f1235e1b000
    mmap(0x7f1235e1d000, 5640, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f1235e1d000
    close(3)                                = 0
    openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
    read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\237\2\0\0\0\0\0"..., 832) = 832
    pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
    pread64(3, "\4\0\0\0 \0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0"..., 48, 848) = 48
    pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\302\211\332Pq\2439\235\350\223\322\257\201\326\243\f"..., 68, 896) = 68
    newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=2220400, ...}, AT_EMPTY_PATH) = 0
    pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
    mmap(NULL, 2264656, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f1235bca000
    mprotect(0x7f1235bf2000, 2023424, PROT_NONE) = 0
    mmap(0x7f1235bf2000, 1658880, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x7f1235bf2000
    mmap(0x7f1235d87000, 360448, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1bd000) = 0x7f1235d87000
    mmap(0x7f1235de0000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x215000) = 0x7f1235de0000
    mmap(0x7f1235de6000, 52816, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f1235de6000
    close(3)                                = 0
    openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libpcre2-8.so.0", O_RDONLY|O_CLOEXEC) = 3
    read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=613064, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 615184, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f1235b33000
    mmap(0x7f1235b35000, 438272, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7f1235b35000
    mmap(0x7f1235ba0000, 163840, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6d000) = 0x7f1235ba0000
    mmap(0x7f1235bc8000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x94000) = 0x7f1235bc8000
    close(3)                                = 0
    mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f1235b30000
    arch_prctl(ARCH_SET_FS, 0x7f1235b30800) = 0
    set_tid_address(0x7f1235b30ad0)         = 18745
    set_robust_list(0x7f1235b30ae0, 24)     = 0
    rseq(0x7f1235b311a0, 0x20, 0, 0x53053053) = 0
    mprotect(0x7f1235de0000, 16384, PROT_READ) = 0
    mprotect(0x7f1235bc8000, 4096, PROT_READ) = 0
    mprotect(0x7f1235e1b000, 4096, PROT_READ) = 0
    mprotect(0x5600ad8a8000, 4096, PROT_READ) = 0
    mprotect(0x7f1235e5f000, 8192, PROT_READ) = 0
    prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
    munmap(0x7f1235e1f000, 24459)           = 0
    statfs("/sys/fs/selinux", 0x7ffef18ecc50) = -1 ENOENT (No such file or directory)
    statfs("/selinux", 0x7ffef18ecc50)      = -1 ENOENT (No such file or directory)
    getrandom("\x00\x93\xcc\x91\x39\x09\x73\xd0", 8, GRND_NONBLOCK) = 8
    brk(NULL)                               = 0x5600ae82a000
    brk(0x5600ae84b000)                     = 0x5600ae84b000
    openat(AT_FDCWD, "/proc/filesystems", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0444, st_size=0, ...}, AT_EMPTY_PATH) = 0
    read(3, "nodev\tsysfs\nnodev\ttmpfs\nnodev\tbd"..., 1024) = 478
    read(3, "", 1024)                       = 0
    close(3)                                = 0
    access("/etc/selinux/config", F_OK)     = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/share/locale/locale.alias", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=2996, ...}, AT_EMPTY_PATH) = 0
    read(3, "# Locale name alias data base.\n#"..., 4096) = 2996
    read(3, "", 4096)                       = 0
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_IDENTIFICATION", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_IDENTIFICATION", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=258, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 258, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235e5e000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache", O_RDONLY) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=27002, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 27002, PROT_READ, MAP_SHARED, 3, 0) = 0x7f1235b29000
    close(3)                                = 0
    futex(0x7f1235de5a6c, FUTEX_WAKE_PRIVATE, 2147483647) = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_MEASUREMENT", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_MEASUREMENT", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=23, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 23, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235e24000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_TELEPHONE", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_TELEPHONE", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=47, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 47, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235e23000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_ADDRESS", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_ADDRESS", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=127, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 127, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235e22000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_NAME", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_NAME", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=62, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 62, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235e21000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_PAPER", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_PAPER", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=34, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 34, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235e20000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_MESSAGES", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_MESSAGES", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFDIR|0755, st_size=4096, ...}, AT_EMPTY_PATH) = 0
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_MESSAGES/SYS_LC_MESSAGES", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=48, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 48, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235e1f000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_MONETARY", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_MONETARY", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=270, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 270, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235b28000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_COLLATE", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_COLLATE", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=1406, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 1406, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235b27000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_TIME", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_TIME", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=3360, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 3360, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235b26000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_NUMERIC", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_NUMERIC", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=50, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 50, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235b25000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_CTYPE", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/lib/locale/C.utf8/LC_CTYPE", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=353616, ...}, AT_EMPTY_PATH) = 0
    mmap(NULL, 353616, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f1235ace000
    close(3)                                = 0
    openat(AT_FDCWD, "/usr/share/locale/C.UTF-8/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/share/locale/C.utf8/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/share/locale/C/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/share/locale-langpack/C.UTF-8/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/share/locale-langpack/C.utf8/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/usr/share/locale-langpack/C/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
    statx(AT_FDCWD, "Makefile", AT_STATX_SYNC_AS_STAT|AT_SYMLINK_NOFOLLOW, STATX_ALL, {stx_mask=STATX_BASIC_STATS|STATX_MNT_ID, stx_attributes=0, stx_mode=S_IFREG|0777, stx_size=101, ...}) = 0
    newfstatat(1, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x2), ...}, AT_EMPTY_PATH) = 0
    write(1, "  File: Makefile\n", 17  File: Makefile
    )      = 17
    write(1, "  Size: 101       \tBlocks: 0    "..., 68  Size: 101          Blocks: 0          IO Block: 4096   regular file
    ) = 68
    write(1, "Device: 55h/85d\tInode: 844424930"..., 49Device: 55h/85d      Inode: 844424930132605  Links: 1
    ) = 49
    socket(AF_UNIX, SOCK_STREAM|SOCK_CLOEXEC|SOCK_NONBLOCK, 0) = 3
    connect(3, {sa_family=AF_UNIX, sun_path="/var/run/nscd/socket"}, 110) = -1 ENOENT (No such file or directory)
    close(3)                                = 0
    socket(AF_UNIX, SOCK_STREAM|SOCK_CLOEXEC|SOCK_NONBLOCK, 0) = 3
    connect(3, {sa_family=AF_UNIX, sun_path="/var/run/nscd/socket"}, 110) = -1 ENOENT (No such file or directory)
    close(3)                                = 0
    newfstatat(AT_FDCWD, "/etc/nsswitch.conf", {st_mode=S_IFREG|0644, st_size=510, ...}, 0) = 0
    newfstatat(AT_FDCWD, "/", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
    openat(AT_FDCWD, "/etc/nsswitch.conf", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=510, ...}, AT_EMPTY_PATH) = 0
    read(3, "# /etc/nsswitch.conf\n#\n# Example"..., 4096) = 510
    read(3, "", 4096)                       = 0
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=510, ...}, AT_EMPTY_PATH) = 0
    close(3)                                = 0
    openat(AT_FDCWD, "/etc/passwd", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=1418, ...}, AT_EMPTY_PATH) = 0
    lseek(3, 0, SEEK_SET)                   = 0
    read(3, "root:x:0:0:root:/root:/bin/bash\n"..., 4096) = 1418
    close(3)                                = 0
    socket(AF_UNIX, SOCK_STREAM|SOCK_CLOEXEC|SOCK_NONBLOCK, 0) = 3
    connect(3, {sa_family=AF_UNIX, sun_path="/var/run/nscd/socket"}, 110) = -1 ENOENT (No such file or directory)
    close(3)                                = 0
    socket(AF_UNIX, SOCK_STREAM|SOCK_CLOEXEC|SOCK_NONBLOCK, 0) = 3
    connect(3, {sa_family=AF_UNIX, sun_path="/var/run/nscd/socket"}, 110) = -1 ENOENT (No such file or directory)
    close(3)                                = 0
    newfstatat(AT_FDCWD, "/etc/nsswitch.conf", {st_mode=S_IFREG|0644, st_size=510, ...}, 0) = 0
    openat(AT_FDCWD, "/etc/group", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=773, ...}, AT_EMPTY_PATH) = 0
    lseek(3, 0, SEEK_SET)                   = 0
    read(3, "root:x:0:\ndaemon:x:1:\nbin:x:2:\ns"..., 4096) = 773
    close(3)                                = 0
    write(1, "Access: (0777/-rwxrwxrwx)  Uid: "..., 73Access: (0777/-rwxrwxrwx)  Uid: ( 1000/   julio)   Gid: ( 1000/   julio)
    ) = 73
    openat(AT_FDCWD, "/etc/localtime", O_RDONLY|O_CLOEXEC) = 3
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=2529, ...}, AT_EMPTY_PATH) = 0
    newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=2529, ...}, AT_EMPTY_PATH) = 0
    read(3, "TZif3\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\10\0\0\0\10\0\0\0\0"..., 4096) = 2529
    lseek(3, -1601, SEEK_CUR)               = 928
    read(3, "TZif3\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\10\0\0\0\10\0\0\0\0"..., 4096) = 1601
    close(3)                                = 0
    write(1, "Access: 2024-04-10 17:39:50.6862"..., 44Access: 2024-04-10 17:39:50.686281500 -0400
    ) = 44
    write(1, "Modify: 2024-04-09 20:47:10.9845"..., 44Modify: 2024-04-09 20:47:10.984558700 -0400
    ) = 44
    write(1, "Change: 2024-04-09 20:47:10.9845"..., 44Change: 2024-04-09 20:47:10.984558700 -0400
    ) = 44
    write(1, " Birth: -\n", 10 Birth: -
    )             = 10
    close(1)                                = 0
    close(2)                                = 0
    exit_group(0)                           = ?
    +++ exited with 0 +++
#endif

#define _GNU_SOURCE          /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <unistd.h>

#include <fcntl.h>           /* Definition of AT_* constants */

#define BUFFER_SIZE 4096
#define USERNAME_SIZE 128
#define GROUPNAME_SIZE 128

int extract_username_from_uid(char *username, int uid)
{
    int filefd;
    if ((filefd = open("/etc/passwd", O_RDONLY, 0)) >= 0) {
        char buffer[BUFFER_SIZE] = {};
        
        int colon_end_username = 1;
        int expected_colon_start_uid = 2;
        while (read(filefd, buffer, BUFFER_SIZE) > 0) {
            char *curr = buffer;
            char *start = buffer;
            char *colon_start;
            char *colon_filename_end;

            // for every line
            while (*curr) {
                int current_colon = 0;
                while (*curr != '\n') {
                    if (*curr == ':') {
                        ++current_colon;

                        if (current_colon == expected_colon_start_uid) {
                            colon_start = curr + 1; // + 1 to skip the ':'
                        } else if (current_colon == colon_end_username) {
                            colon_filename_end = curr;
                        }
                    }

                    curr++;
                }

                int extracted_uid = atoi(colon_start);
                if (uid == extracted_uid) {
                    snprintf(username, (colon_filename_end - start) + 1, start);

                    return 0;
                }
                
                curr++;
                start = curr;
            }
        }
    }

    return -1;
}

int extract_groupname_from_gid(char *groupname, int gid)
{
    int filefd;
    if ((filefd = open("/etc/group", O_RDONLY, 0)) >= 0) {
        char buffer[BUFFER_SIZE] = {};
        
        int colon_end_username = 1;
        int expected_colon_start_gid = 2;
        while (read(filefd, buffer, BUFFER_SIZE) > 0) {
            char *curr = buffer;
            char *start = buffer;
            char *colon_start;
            char *colon_filename_end;

            // for every line
            while (*curr) {
                int current_colon = 0;
                while (*curr != '\n') {
                    if (*curr == ':') {
                        ++current_colon;

                        if (current_colon == expected_colon_start_gid) {
                            colon_start = curr + 1; // + 1 to skip the ':'
                        } else if (current_colon == colon_end_username) {
                            colon_filename_end = curr;
                        }
                    }

                    curr++;
                }

                int extracted_uid = atoi(colon_start);
                if (gid == extracted_uid) {
                    snprintf(groupname, (colon_filename_end - start) + 1, start);

                    return 0;
                }
                
                curr++;
                start = curr;
            }
        }
    }

    return -1;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "%s: missing operand\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat st;
    int rc = lstat(argv[1], &st);
    if (rc < 0) {
        fprintf(stderr, "%s: cannot stat '%s': %s\n", argv[0], argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("  File: %s\n", argv[1]);
    printf("  Size: %ld\t\tBlocks: %ld\t\tIO Block: %ld\t\t", 
           st.st_size, st.st_blocks, st.st_blksize);
    switch (st.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }
    printf("Device: %dh/%dd  Inode: %ld  Links: %ld\n", major(st.st_dev), minor(st.st_dev), st.st_ino, st.st_nlink);
    // printf("Access: (0777/-rwxrwxrwx)  Uid: ( 1000/   julio)   Gid: ( 1000/   julio)\n");

    char username[USERNAME_SIZE];
    extract_username_from_uid(username, st.st_uid);

    char groupname[GROUPNAME_SIZE];
    extract_groupname_from_gid(groupname, st.st_gid);

    printf("Access: (%o%o/%c%c%c%c%c%c%c%c%c%c)  Uid: (%d/%s)  Gid: (%d/%s)\n", 
           (st.st_mode & S_ISUID)|(st.st_mode & S_ISGID)|(st.st_mode & S_ISVTX),
           (st.st_mode & S_IRWXU)|(st.st_mode & S_IRWXG)|(st.st_mode & S_IRWXO), 
           
           (st.st_mode & S_IFDIR ? 'd' : '-'),

           (st.st_mode & S_IRUSR ? 'r' : '-'),
           (st.st_mode & S_IWUSR ? 'w' : '-'),
           (st.st_mode & S_IXUSR ? 'x' : '-'),

           (st.st_mode & S_IRGRP ? 'r' : '-'),
           (st.st_mode & S_IWGRP ? 'w' : '-'),
           (st.st_mode & S_IXGRP ? 'x' : '-'),

           (st.st_mode & S_IROTH ? 'r' : '-'),
           (st.st_mode & S_IWOTH ? 'w' : '-'),
           (st.st_mode & S_IXOTH ? 'x' : '-'),
           
           st.st_uid, username,
           st.st_gid, groupname);
    printf("Access: %s", ctime(&st.st_atim.tv_sec));
    printf("Modify: %s", ctime(&st.st_mtim.tv_sec));
    printf("Change: %s", ctime(&st.st_ctim.tv_sec));
    printf("Birth: -\n");

    // TODO: do the same with the gid




    return EXIT_SUCCESS;
}
