#ifndef FS_H
#define FS_H

#include "sleeplock.h"




#define BSIZE 1280 // El tamaño del bloque

#define ROOTINO  1   // root i-number

// Disk layout:
// [ boot block | super block | log | inode blocks |
//                                          free bit map | data blocks]
// mkfs computes the super block and builds an initial file system. The
// super block describes the disk layout:
struct superblock {
  uint magic;        // Must be FSMAGIC
  uint size;         // Size of file system image (blocks)
  uint nblocks;      // Number of data blocks
  uint ninodes;      // Number of inodes.
  uint nlog;         // Number of log blocks
  uint logstart;     // Block number of first log block
  uint inodestart;   // Block number of first inode block
  uint bmapstart;    // Block number of first free map block
};

#define FSMAGIC 0x10203040


#define NDIRECT 12
#define NINDIRECT (BSIZE / sizeof(uint))
#define MAXFILE (NDIRECT + NINDIRECT)

// On-disk inode structure
struct dinode {
  short type;
  short major;
  short minor;
  short nlink;
  uint size;
  uint addrs[NDIRECT+1];
  int permissions;
  char padding[572];  // Ajuste del padding para que el tamaño sea exactamente igual a BSIZE
};

// In-memory inode copy
struct inode {
  uint dev;              // Device number
  uint inum;             // Inode number
  int ref;               // Reference count
  struct sleeplock lock; // Protects everything below here
  int valid;             // inode has been read from disk?

  short type;            // Copy of disk inode
  short major;
  short minor;
  short nlink;
  uint size;
  uint addrs[NDIRECT+1];
  int permissions;       // Permissions: 0=no access, 1=read-only, 2=write-only, 3=read/write
};

// Declaración de la función encapsuladora
void set_inode_permissions(struct inode *ip, int mode);

// Inodes per block
#define IPB (BSIZE / sizeof(struct dinode))

// Block containing inode i
#define IBLOCK(i, sb)     ((i) / IPB + sb.inodestart)

// Bitmap bits per block
#define BPB           (BSIZE*8)

// Block of free map containing bit for block b
#define BBLOCK(b, sb) ((b)/BPB + sb.bmapstart)

// Directory is a file containing a sequence of dirent structures
#define DIRSIZ 14

struct dirent {
  ushort inum;
  char name[DIRSIZ];
};

#endif // FS_H
