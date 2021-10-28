#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
void random_arr(int * arr, int bytes){
  int RANDOM_FILE = open("/dev/random", O_RDONLY);
  read(RANDOM_FILE, arr, bytes);
}

 void transfer_file(int * arr1, int * arr2, int bytes){
  printf("Writing numbers to file ...\n");
  int fd = open("random.txt", O_RDWR|O_CREAT, S_IRWXU);
  if(fd<0){
    printf("Error1 = %d", errno);
    return;
  }
  write(fd, arr1, bytes);
  close(fd);
  fd = open("random.txt", O_RDONLY);
  if(fd<0){
    printf("Error2 = %d", errno);
    return;
  }
  printf("Reading numbers to file ...\n");
  read(fd, arr2, bytes);
}

int main(){
  int len = 10;
  int * arr1 =  calloc(len , sizeof(int));
  int * arr2 =  calloc(len , sizeof(int));
  random_arr(arr1, len*sizeof(int));
  int i;
  for(i = 0; i < len; i++){
    printf("Random number %d: %d \n", i, arr1[i]);
  }
  transfer_file(arr1, arr2, len*sizeof(int));
  for(i = 0; i < len; i++){
    printf("Random number %d: %d \n", i, arr2[i]);
  }
  free(arr1);
  free(arr2);
  return 0;
}
