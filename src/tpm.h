#ifndef TPM_H
#define TPM_H

//AABBGGRR format for pixel rgba value

typedef unsigned int uint;

typedef struct {
	uint *pixels, width, height;
} Canvas;


Canvas tpm_canvas(uint *pixels, uint width, uint height);
uint* tpm_fill(uint *pixels, uint width, uint height, uint color);
uint* tpm_draw_line(uint *pixels, uint canvas_width, uint height, uint x1, uint y1, uint x2, uint y2 , uint color);
uint* tpm_fill_circle(uint *pixels, uint canvas_width, uint canvas_height, int cx, int cy, uint radius, uint color);


#endif
