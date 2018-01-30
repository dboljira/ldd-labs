/*
* A user space program that talks to usb device using a 
* usb device file. The usb driver creates the device file
* when it is loaded and handles any file operations from
* this user space program as per USB protocol.
* This user space program sends a command(max 8 Bytes) to toggle the usb
* device LEDs, reads the status of the LEDs and AVR AT90USBKEY board temp sensor.
* 
* 
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#define DEFAULT_DEVICE "/dev/lddusb0"
#define MAX_BYTES 8
int main(int argc, char *argv[])
{
  char c;
  int fd;
  char *dev = DEFAULT_DEVICE;
  int    p = 0;
  uint8_t command[MAX_BYTES];
  fd=open(dev,O_RDWR);
  if (fd == -1)
  {
    printf("No such device %s\n",dev);
    perror("open");
    exit(1);
  }
  while (1)
  {
    memset(command, 0x00, sizeof(command));
    int i;
    /*Packet to toggle LEDs (only the 4 MSB of the  message 
     changes every time and the 4 LSB are set to zero) */
    
    for (i=0;i<4;i++) 
    {
      command[i]=(p >> (3-i)) & 1;
    }
    command[4]=0;

    printf("Packet sent to toggle LEDs: ");
    for (i=0;i<MAX_BYTES;i++)
    {
      printf("%d",command[i]);
    }

    printf("\n");

    int retval = 0;
    retval = write(fd, &command, sizeof(command));

    if (retval < 0) 
      fprintf(stderr, "an error occured: %d\n", retval);

    //allocate and zero initialize array
    char *data=(char *)calloc(MAX_BYTES, sizeof(char));

    retval=read(fd, data, MAX_BYTES);

    printf("Reading LEDs and Temp...\n");
    for (i=0;i<5;i++) 
    {
      if (i<4)
        printf("LED %d: %s\n",i+1,data[i]?"ON":"OFF");
      else 
        printf("Temp (C): %d\n",data[i]);
    }

    free(data);
    p = (p + 1) % 16;
    sleep(2);
  }
  close(fd);
  return 0;
}
