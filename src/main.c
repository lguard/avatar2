/*#include <stdio.h>*/
/*#include <unistd.h>*/
/*#include <fcntl.h>*/

/*void	w_byte(unsigned char b, int fd)*/
/*{*/
	/*write(fd, &b, 1);*/
/*}*/

/*int main(int ac, char **av)*/
/*{*/
	/*int fptr = open(av[1], O_CREAT | O_WRONLY);*/
	/*int width = 10;*/
	/*int height = 10;*/
	/*w_byte(0,fptr);*/
	/*w_byte(0,fptr);*/
	/*w_byte(2,fptr);                         [> uncompressed RGB <]*/
	/*w_byte(0,fptr); w_byte(0,fptr);*/
	/*w_byte(0,fptr); w_byte(0,fptr);*/
	/*w_byte(0,fptr);*/
	/*w_byte(0,fptr); w_byte(0,fptr);           [> X origin <]*/
	/*w_byte(0,fptr); w_byte(0,fptr);           [> y origin <]*/
	/*w_byte((width & 0x00FF),fptr);*/
	/*w_byte((width & 0xFF00) / 256,fptr);*/
	/*w_byte((height & 0x00FF),fptr);*/
	/*w_byte((height & 0xFF00) / 256,fptr);*/
	/*w_byte(24,fptr);                        [> 24 bit bitmap <]*/
	/*w_byte(0,fptr);*/
	/*for(int i = 0;i< 10;++i)*/
	/*{*/
		/*for(int j = 0;j< 10;++j)*/
		/*{*/
			/*w_byte((unsigned char)100,fptr);*/
			/*w_byte((unsigned char)0,fptr);*/
			/*w_byte((unsigned char)255,fptr);*/
		/*}*/
	/*}*/
	/*close(fptr);*/
	/*return 0;*/
/*}*/
