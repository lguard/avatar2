	/*ray		:	ray = c.pos + c.dir * t*/
	/*sphere	:	x² + y² + z² = r²*/
	/*tore	:	(x² + y² + z² + R² - r²)² - 4 R² (x² + z²) = 0*/
				/*((dx*t+px)² + (dy*t+py)² + (dz*t+pz)² + R² - r²)² = 4R²( (dx*t+px)²+ (dz*t+pz)²)*/

					  /*((dx²+dy²+dz²)*t² + 2*(dx*px+dy*py+dz*pz)*t + (px² + py² + pz²)+ R² - r²)² = 4R²( (dx*t+px)²+ (dz*t+pz)²)*/
	/*factorisation du terme de gauche*/
/*a²+b²+c²+2ab+2ac+2bc+=(        a          +            b            +                 c              )²*/

       /*a²          +           b²              +           c²            +                       2ab                  +*/
/*(dx²+dy²+dz²)²*t^4 + 4*(dx*px+dy*py+dz*pz)²*t² + (px²+py²+pz²+r²+R²+r²)² + 2*(dx²+dy²+dz²)*t²*2*(dx*px+dy*py+dz*pz)*t +*/

                       /*2ac                          +                               2bc	*/

/*2*(dx² + dy²+dz²)*t² * (px² + py² + pz² + R²-r²)+ 2*2*(dx*px+dy*py+dz*pz)*t*(px² + py² + pz² + R² - r²)*/


/*t^4*(dx²+dy²+dz²)² + t²*(dx*px+dy*py+dz*pz)²*4 + (px²+py²+pz²+r²+R²+r²)² + t^3*(dx²+dy²+dz²)*(dx*px+dy*py+dz*pz)*4 +*/
/*t²*(dx² + dy²+dz²) * (px² + py² + pz² + R² - r²)*2+ t*(dx*px+dy*py+dz*pz)*(px² + py² + pz² + R² - r²)*4*/

/*t^4*(dx²+dy²+dz²)² + t²*(dx*px+dy*py+dz*pz)²*4 + (px²+py²+pz²+r²+R²+r²)² + t^3*(dx²+dy²+dz²)*(dx*px+dy*py+dz*pz)*4 +*/
/*t²*(dx² + dy²+dz²) * (px² + py² + pz² + R² - r²)*2+ t*(dx*px+dy*py+dz*pz)*(px² + py² + pz² + R² - r²)*4*/

	/*factorisation du terme de droite*/
/*4R² * ((dx²+dz²)*t² + 2*(dx*px+dz*pz)*t + (px²+pz²))*/

/*4R² * (dx²+dz²)*t² + 4R²*2*(dx*px+dz*pz)*t + 4R² *(px²+pz²)*/

/*t²*(dx²+dz²)*4R²   + t*(dx*px+dz*pz)*4R²*2 +(px²+pz²)*4R²*/

/*t^4*(dx²+dy²+dz²)² + t^3*(dx²+dy²+dz²)*(dx*px+dy*py+dz*pz)*4+ t²*(dx*px+dy*py+dz*pz)²*4 + t²*(dx²+dy²+dz²)*(px²+py²+pz²+r²+R²-r²)*2 - t²*(dx²+dz²)*R²*4*/
/*+ t*(dx*px+dy*py+dz*pz)*(px²+py²+pz²+r²+R²-r²)*4 - t*(dx*px+dz*pz)*4R²*2* - (px²+pz²)*4R² + (px²+py²+pz²+R²+r²)² */

/*t^4*(dx²+dy²+dz²)² + t^3*(dx²+dy²+dz²)*(dx*px+dy*py+dz*pz)*4+ t²*((dx²+dy²+dz²)*(px²+py²+pz²+R²-r²)*2 + (dx*px+dy*py+dz*pz)²*4 - (dx²+dz²)*R²*4)*/
/*+ t*((dx*px+dy*py+dz*pz)*(px²+py²+pz²+r²+R²-r²)*4 -(dx*px+dz*pz)*8R²) + (px²+py²+pz²+R²+r²)² - (px²+pz²)*4R² */

/*a = (dx² + dy² + dz²)²*/
/*b = 4*(dx² + dy² + dz²)*(dx*px + dy*py + dz*pz)*/
/*c = 2*(dx² + dy² + dz²)*(px² + py² + pz² + R² - r²) + 4*(dx*px + dy*py + dz*pz)² - 4*R²*(dx² + dz²)*/
/*d = 4*(dx*px + dy*py + dz*pz) (px² + py² + pz² + R² - r²) - 8*R²*(dx*px + dz*pz)*/
/*e = (px² + py² + pz² + R² - r²)² - 4*R²*(px² + pz²)*/

/*(x^2+y^2+z^2+R^2-r^2)^2 = 4*R^2*(x^2+z^2)*/
/*((px+dx*t)^2+(py+dy*t)^2+(pz+dz*t)^2+R^2-r^2)^2 = 4*R^2*((px+dx*t)^2+(pz+dz*t)^2)*/
/*(px^2+dx^2*t^2+2*px*dx*t  + py^2+dy^2*t^2+2*py*dy*t + pz^2+dz^2*t^2+2*pz*dz*t  + R^2-r^2)^2 = 4*R^2*(px^2+dx^2*t^2+2*px*dx*t + pz^2+dz^2*t^2+2*pz*dz*t)*/
/*(px^2+py^2+pz^2+R^2-r^2+ dx^2*t^2+dy^2*t^2+dz^2*t^2+ 2*px*dx*t +2*py*dy*t +2*pz*dz*t)^2 = 4*R^2*(px^2+pz^2+ dx^2*t^2+dz^2*t^2+ 2*px*dx*t + 2*pz*dz*t)*/
/*(px^2+py^2+pz^2+R^2-r^2+ t^2*(dx^2*+dy^2+dz^2)+ t*2*(px*dx+py*dy+pz*dz))^2 = 4*R^2*(px^2+pz^2+ t^2*(dx^2+dz^2)+ t*2*(px*dx + pz*dz))*/

/*(px^2+py^2+pz^2+R^2-r^2+ t^2*(dx^2*+dy^2+dz^2)+ t*2*(px*dx+py*dy+pz*dz))^2 = 4*R^2*(px^2+pz^2+ t^2*(dx^2+dz^2)+ t*2*(px*dx + pz*dz))*/

/*(px^2+py^2+pz^2+R^2-r^2)^2 + (t^2*(dx^2*+dy^2+dz^2))^2 + (t*2*(px*dx+py*dy+pz*dz))^2 + 2* px^2+py^2+pz^2+R^2-r^2 * t^2*(dx^2*+dy^2+dz^2) +*/
/*2 * px^2+py^2+pz^2+R^2-r^2 * t*2*(px*dx+py*dy+pz*dz)+ 2*t^2*(dx^2*+dy^2+dz^2) *t*2*(px*dx+py*dy+pz*dz) = 4*R^2*(px^2+pz^2)+ t^2*(dx^2+dz^2)*4*R^2+ t*2*(px*dx + pz*dz)*4*R^2*/



/*t^4*(dx^2*+dy^2+dz^2)^2 +*/

/**t^3*4(dx^2*+dy^2+dz^2) *(px*dx+py*dy+pz*dz)+*/

/*t^2*2*((px*dx+py*dy+pz*dz)^2 + px^2+py^2+pz^2+R^2-r^2 *(dx^2*+dy^2+dz^2)) +*/

/*t*4 * px^2+py^2+pz^2+R^2-r^2 * (px*dx+py*dy+pz*dz)+*/

/*(px^2+py^2+pz^2+R^2-r^2)^2  = t^2*(dx^2+dz^2)*4*R^2 +  t*2*(px*dx + pz*dz)*4*R^2 + 4*R^2*(px^2+pz^2)*/



/*t^4*(dx^2*+dy^2+dz^2)^2 +*/

/**t^3*4(dx^2*+dy^2+dz^2) *(px*dx+py*dy+pz*dz)+*/

/*t^2*2*((px*dx+py*dy+pz*dz)^2 + px^2+py^2+pz^2+R^2-r^2 *(dx^2*+dy^2+dz^2)) - t^2*(dx^2+dz^2)*4*R^2 +*/

/*t*4 * px^2+py^2+pz^2+R^2-r^2 * (px*dx+py*dy+pz*dz) - t*2*(px*dx + pz*dz)*4*R^2 +*/

/*(px^2+py^2+pz^2+R^2-r^2)^2 - 4*R^2*(px^2+pz^2) = 0*/



/*t^4*(dx^2*+dy^2+dz^2)^2 +*/

/**t^3*4(dx^2*+dy^2+dz^2) *(px*dx+py*dy+pz*dz)+*/

/*t^2 *( 2* (dx^2*+dy^2+dz^2) * (px^2+py^2+pz^2+R^2-r^2) + 4*(px*dx+py*dy+pz*dz)^2 - (dx^2+dz^2)*4*R^2)*/

/*t*(4 * px^2+py^2+pz^2+R^2-r^2 * (px*dx+py*dy+pz*dz) - (px*dx + pz*dz)*8*R^2) +*/

/*(px^2+py^2+pz^2+R^2-r^2)^2 - 4*R^2*(px^2+pz^2) = 0*/


/*a = (dx² + dy² + dz²)²*/
/*b = 4*(dx² + dy² + dz²)*(dx*px + dy*py + dz*pz)*/
/*c = 2*(dx² + dy² + dz²)*(px² + py² + pz² + R² - r²) + 4*(dx*px + dy*py + dz*pz)² - 4*R²*(dx² + dz²)*/
/*d = 4*(dx*px + dy*py + dz*pz) (px² + py² + pz² + R² - r²) - 8*R²*(dx*px + dz*pz)*/
/*e = (px² + py² + pz² + R² - r²)² - 4*R²*(px² + pz²)*/

