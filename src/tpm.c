#ifndef _TPM_C_
#define _TPM_C_

#include "tpm.h"
#include "def.c"

TPM_Canvas TPM_init_canvas(uint *pixels, uint canvas_width, uint canvas_height) 
{
    TPM_Canvas canvas = {
        .pixels = pixels,
        .width  = canvas_width,
        .height = canvas_height
    };

    return canvas;
}

uint* TPM_fill(uint *pixels, uint width, uint height, uint color)
{
    uint x, y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            pixels[y * width + x] = color;
        }
    }

    return pixels;
}

uint* TPM_fill_point(uint* pixels, uint canvas_width, uint canvas_height, int x, int y, uint color)
{
    pixels[y * canvas_width + x] = color;

    return pixels;
}

uint* TPM_draw_line(uint *pixels, uint canvas_width, uint height, int x1, int y1, int x2, int y2 , uint color)
{
    uint x, y;
    for (x = x1; x <= x2; x++) {
        y = (int)((float)(y2 - y1) / (float)(x2 - x1) * (float)(x - x1) + (float)y1);
        pixels[y * canvas_width + x] = color;
    }

    return pixels;
}

uint* TPM_fill_circle(uint *pixels, uint canvas_width, uint canvas_height, int cx, int cy, uint radius, uint color)
{
    uint x, y;
    for (y = 0; y < canvas_height; y++)
        for (x = 0; x < canvas_width; x++) {
            int dx = x - cx;
            int dy = y - cy;
            if (TPM_SQR(dx) + TPM_SQR(dy) <= TPM_SQR(radius)) {
                pixels[y * canvas_width + x] = color;
            }
        }

    return pixels;
}

uint* TPM_draw_circle(uint *pixels, uint canvas_width, uint canvas_height, int cx, int cy, uint radius, uint color)
{
    uint x, y;
    int r2 = TPM_SQR(radius);
    for (y = 0; y < canvas_height; y++) {
        for (x = 0; x < canvas_width; x++) {
            int dx = x - cx;
            int dy = y - cy;
            int d2 = TPM_SQR(dx) + TPM_SQR(dy);
            if (d2 > r2 - radius && d2 < r2 + radius) {
                pixels[y * canvas_width + x] = color;
            }
        }
    }

    return pixels;
}

uint* TPM_fill_rect(uint *pixels, uint canvas_width, uint canvas_height, int x, int y, uint width, uint height, uint color)
{
    uint i, j;
    for (i = x; i < (x + width); i++) {
        for (j = y; j < (y + height); j++) {
            pixels[j * canvas_width + i] = color;
        }
    }

    return pixels;
}

uint* TPM_draw_rect(uint *pixels, uint canvas_width, uint canvas_height, int x, int y, uint width, uint height, uint color) 
{
    uint i, j;

    for (i = x; i < x + width; i++) {
        pixels[y * canvas_width + i] = color;
        pixels[(y + height - 1) * canvas_width + i] = color;
    }

    for (j = y; j < y + height; j++) {
        pixels[j * canvas_width + x] = color;
        pixels[j * canvas_width + (x + width - 1)] = color;
    }

    return pixels;
}

//TODO: only fill triangle if inside canvas | donot fill if got out of canvas
uint* TPM_fill_triangle(uint* pixels, uint canvas_width, uint canvas_height, int x1, int y1, int x2, int y2, int x3, int y3, uint color)
{
    if (y1 > y2) {
        TPM_SWAP_INT(x1, x2);
        TPM_SWAP_INT(y1, y2);
    }
    if (y2 > y3) {
        TPM_SWAP_INT(x2, x3);
        TPM_SWAP_INT(y2, y3);
    }
    if (y1 > y2) {
        TPM_SWAP_INT(x1, x2);
        TPM_SWAP_INT(y1, y2);
    }
    
    float m1 = (float)(x2 - x1) / (y2 - y1);
    float m2 = (float)(x3 - x1) / (y3 - y1);
    float m3 = (float)(x3 - x2) / (y3 - y2);
    
    float xl = x1;
    float xr = x1;
    
    uint x, y;
    for (y = y1; y <= y3; y++) {
        for (x = (int)xl; x <= (int)xr; x++) {
            pixels[y * canvas_width + x]  = color;
        }
        if (y < y2) {
            xl += m1;
            xr += m2;
        } else {
            xl += m3;
            xr += m2;
        }
        xr += m3;
    }
    
    return pixels;
}

//TODO: implement draw triangle unfilled
uint* TPM_draw_triangle(uint* pixels, uint canvas_width, uint canvas_height, int x1, int y1, int x2, int y2, int x3, int y3, uint color) 
{
    return 0;
    if (y1 > y2) {
        TPM_SWAP_INT(x1, x2);
        TPM_SWAP_INT(y1, y2);
    }
    if (y2 > y3) {
        TPM_SWAP_INT(x2, x3);
        TPM_SWAP_INT(y2, y3);
    }
    if (y1 > y2) {
        TPM_SWAP_INT(x1, x2);
        TPM_SWAP_INT(y1, y2);
    }
    
    float m1 = (float)(x2 - x1) / (y2 - y1);
    float m2 = (float)(x3 - x1) / (y3 - y1);
    float m3 = (float)(x3 - x2) / (y3 - y2);
    
    uint x, y;
    
    return pixels;
}

#endif
