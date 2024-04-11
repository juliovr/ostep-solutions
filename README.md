# ostep-solutions
My solutions to Operating Systems: Three Easy Pieces

# Syscalls
open
read
write
close
fsync:
    Flushes the modified file that is in cache pages to reach the disk. The function blocks and returns when the transfer has completed.
    Note: If the file is new, it is possible that the new entry in the directory does not reach the disk.
          So, it has to be called a second time on the directory's file descriptor to ensure the persistence of the file.
    ref: https://man7.org/linux/man-pages/man2/fsync.2.html

strace:
      trace the syscalls made by a program
      Usage: strace <program>
             strace ls
             strace ls -l
      Notes: stat: syscall gives information about a file
             statx: same as stat by extended information (as the man page said)