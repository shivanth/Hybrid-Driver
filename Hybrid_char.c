#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/types.h>
#include<asm/types.h>
#include<asm/uaccess.h>
#include<linux/cdev.h>

MODULE_LICENSE("Dual BSD/GPL");
#define MAJOR_NO 12
#define MINOR_NO 3
#define MAX_OPEN 100

int hybrid_char_open(struct inode *inodep,struct file*filp);
void  hybrid_char_close();
ssize_t hybrid_char_read(struct file * filep,char* buff,size_t count,loff_t* f_pos);
ssize_t hybrid_char_write(struct file*filp,char * buff,size_t count,loff_t * f_pos);

void hybrid_char_exit();

int memory_init();
/*The file ops structure definition for my driver Currently dealing only with open close read and write 
 */
struct file_operations memory_fops={
 read:hybrid_char_read,
 write:hybrid_char_write,
 open:hybrid_char_open,
 release:hybrid_char_close
};
struct hybrid_dev{
  dev_t devno;
  int count;

  char * * buff_map;// an array that contains pointer to maximum 100 buffers
  int map_length;//indiactes the length of the map starts from 0 )
  struct cdev hybrid_char;
  int lock;//used as a lock for read/write operations 
}
  hy_dev;
int hybrid_char_open(struct inode *inode,struct file*filp){

}
int __init module_start_up(){
  hy_dev.devno=MKDEV(MAJOR_NO,MINOR_NO);
  cdev_init(&(mydev.mycdev),&hy_dev_fops);
  int result=cdev_add(&(mydev.mycdev),mydev.devno,MINOR_NO);
  if(result<0){
    printk(KERN_ALERT "Error Reistering Device");
    return result;
  }
    buff_map=malloc(100*sizeof(char*));
    if (buf_map==NULL)
      unregister_hybrid_dev();
      return -ENOMEM;
}

void unregister_hybrid_dev(){// call this only after checking for all locks and synchro stuffs
  cdev_del(&(hy_dev.hybrid_char));
}

void module_unload(){
  if(count=0)//check for locks as well
    unregister_hybrid_dev();
  //dont know wat else logic must go in here

}
