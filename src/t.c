#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "vec.h"
#include "cam.h"
#include "scene.h"
#include "sphere.h"
#include "ray.h"

/*void		xyindent(double *x, double *y, double planewidth, double planeheight, double hres, double wres)*/
/*{*/
	/**x = planewidth / wres;*/
	/**y = planeheight / hres;*/
/*}*/

/*t_vec3d		getplanepix(t_vec3d *viewPlaneUpLeft, t_vec3d *rightVec, double xIndent, t_vec3d *upVec, double yIndent, double x, double y)*/
/*{*/
	/*t_vec3d	v1;*/
	/*t_vec3d	v2;*/
	/*t_vec3d	v3;*/
	/*t_vec3d	v4;*/

	/*v1 = vec_scale(rightVec, xIndent * x);*/
	/*v2 = vec_scale(upVec, yIndent * y);*/
	/*v3 = vec_add(viewPlaneUpLeft, &v1);*/
	/*v4 = vec_sub(&v3, &v2);*/
	/*return v4;*/
 /*[>viewPlaneUpLeft + rightVec*xIndent*x - upVec*yIndent*y<]*/
/*}*/

/*t_vec3d		getur(t_vec3d *vecdir, t_vec3d *upvec, t_vec3d *rightvec, t_vec3d *campos)*/
/*{*/
	/*t_vec3d	v1;*/
	/*t_vec3d	v2;*/
	/*t_vec3d	v3;*/
	/*t_vec3d	v4;*/
	/*t_vec3d	v5;*/
	/*t_vec3d	v6;*/

	/*[>lookat = vec_add(&camPos, (vec_sub(vec_add(vec_scale(&vecdir, 1.0f), (vec_scale(&upvec, 0.5f/2.0f))), vec_scale(&rightvec, 0.35f/2.0f))));<]*/
	/*v1 = vec_scale(vecdir, 1.0f);*/
	/*v2 = vec_scale(upvec, 0.5f/2.0f);*/
	/*v3 = vec_add(&v1, &v2);*/
	/*v4 = vec_scale(rightvec, 0.35f/2.0f);*/
	/*v5 = vec_sub(&v3, &v4);*/
	/*v6 = vec_add(campos, &v5);*/
	/*return (v6);*/
/*}*/

void	w_byte(unsigned char b, int fd)
{
	write(fd, &b, 1);
}

int main(int ac, char **av)
{
	t_vec3d	camPos;
	t_vec3d	lookat;
	t_vec3d	upvec;
	t_vec3d	vecdir;
	t_vec3d	rightvec;
	t_cam	cam;
	t_scene	scene;
	t_ray	ray;
	t_sphere	s;

	vec_init(&s.pos, 233.f, 290.f, 0.f);
	s.radius = 100;
	vec_init(&ray.dir, 0.f, 0.f, 1.f);
	vec_init(&cam.pos, 0.f, 0.f, 0.0f);
	vec_init(&cam.dirvec, 0.f, 0.f, 1.0f);
	vec_init(&cam.upvec, 0.f, 1.f, 0.0f);
	cam.wfov = 0.35;
	cam.hfov = 0.5;
	scene.width = 50;
	scene.height = 30;

	cam.rightvec = vec_mul(&cam.upvec, &cam.dirvec);
	cam.viewplane_upleft = getupleft(&cam);
	double xindent, yindent;
	xyratio(&xindent, &yindent, &cam, &scene);
	char buf[256];

	if (ac < 2)
		return 1;
	int fptr = open(av[1], O_CREAT | O_WRONLY);
	int width = 640;
	int height = 480;
	w_byte(0,fptr);
	w_byte(0,fptr);
	w_byte(2,fptr);                 //        [> uncompressed RGB <]
	w_byte(0,fptr); w_byte(0,fptr);
	w_byte(0,fptr); w_byte(0,fptr);
	w_byte(0,fptr);
	w_byte(0,fptr); w_byte(0,fptr);//           [> X origin <]
	w_byte(0,fptr); w_byte(0,fptr);//           [> y origin <]
	w_byte((width & 0x00FF),fptr);
	w_byte((width & 0xFF00) / 256,fptr);
	w_byte((height & 0x00FF),fptr);
	w_byte((height & 0xFF00) / 256,fptr);
	w_byte(24,fptr);//                        [> 24 bit bitmap <]
	w_byte(0,fptr);

	for (int x = 0 ; x< 480;++x) {
		for (int y = 0 ; y< 640;++y) {
			/*t_vec3d p = getplanepix(&cam, (double)x, (double)y, xindent, yindent);*/
			/*vec_normalize(&p);*/
			vec_init(&ray.pos, x, y, -1000.0f);
			if (hit_sphere(&ray, (void*)&s))
			{
				w_byte((unsigned char)100,fptr);
				w_byte((unsigned char)0,fptr);
				w_byte((unsigned char)255,fptr);
			}
			else
			{
				w_byte((unsigned char)0,fptr);
				w_byte((unsigned char)0,fptr);
				w_byte((unsigned char)0,fptr);
			}
	
			/*bzero(buf, 256);*/
			/*sprintf(buf, "%lf,%lf,%lf\n", p.x, p.y, p.z);*/
			/*write(fd, buf, strlen(buf));*/
			/*printf("%d, %d\n", x, y);*/
		}
	}
	close(fptr);
	return 0;
}
