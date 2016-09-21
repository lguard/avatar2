/*void	write_byte(unsigned char b, int fd)*/
/*{*/
	/*write(fd, &b, 1);*/
/*}*/

/*void	write_tga_header(int fd, t_scene *scene, t_color **src)*/
/*{*/
	/*int width = scene->render_width ;*/
	/*int height = scene->render_height;*/
	/*write_byte(0,fd);*/
	/*write_byte(0,fd);*/
	/*write_byte(2,fd);                 //        [> uncompressed RGB <]*/
	/*write_byte(0,fd); write_byte(0,fd);*/
	/*write_byte(0,fd); write_byte(0,fd);*/
	/*write_byte(0,fd);*/
	/*write_byte(0,fd); write_byte(0,fd);//           [> X origin <]*/
	/*write_byte(0,fd); write_byte(0,fd);//           [> y origin <]*/
	/*write_byte((width & 0x00FF),fd);*/
	/*write_byte((width & 0xFF00) / 256,fd);*/
	/*write_byte((height & 0x00FF),fd);*/
	/*write_byte((height & 0xFF00) / 256,fd);*/
	/*write_byte(24,fd);//                        [> 24 bit bitmap <]*/
	/*write_byte(0,fd);*/

	/*for (int y = 0 ; y < height;++y) {*/
		/*for (int x = 0 ; x < width;++x) {*/
				/*write_byte((unsigned char)(src[x][y].b*255.0f),fd);*/
				/*write_byte((unsigned char)(src[x][y].g*255.0f),fd);*/
				/*write_byte((unsigned char)(src[x][y].r*255.0f),fd);*/
		/*}*/
	/*}*/
/*}*/

	/*int fd = open("output.tga", O_WRONLY | O_CREAT | S_IRWXU);*/
	/*write_tga_header(fd, &scene, buff.a);*/
	/*close(fd);*/
