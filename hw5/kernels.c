/****************************************************
 * Kernels to be optimized for the CS201 Assignment 5
 ****************************************************/
//Abdullah Alshaikh 
//Homework 5 - CS201

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *source, pixel *destnation) 
{
  //  naive_rotate(dim, src, dst);
	int i, j, top1, top2;
	for(top2 = 0; top2 < dim; top2+=32)
	{
		for(top1 = 0; top1 < dim; top1+=32)
		{
			for(j = top2; j < top2+32; j+=4)
			{
				for(i = top1; i < top1+32; i+=4)
				{
					destnation[RIDX(dim-1-j, i, dim)] = source[RIDX(i, j, dim)];
					destnation[RIDX(dim-1-j, i+1, dim)] = source[RIDX(i+1, j, dim)];
					destnation[RIDX(dim-1-j, i+2, dim)] = source[RIDX(i+2, j, dim)];
					destnation[RIDX(dim-1-j, i+3, dim)] = source[RIDX(i+3, j, dim)];

					destnation[RIDX(dim-2-j, i, dim)] = source[RIDX(i, j+1, dim)];
					destnation[RIDX(dim-2-j, i+1, dim)] = source[RIDX(i+1, j+1, dim)];
					destnation[RIDX(dim-2-j, i+2, dim)] = source[RIDX(i+2, j+1, dim)];
					destnation[RIDX(dim-2-j, i+3, dim)] = source[RIDX(i+3, j+1, dim)];

					destnation[RIDX(dim-3-j, i, dim)] = source[RIDX(i, j+2, dim)];
					destnation[RIDX(dim-3-j, i+1, dim)] = source[RIDX(i+1, j+2, dim)];
					destnation[RIDX(dim-3-j, i+2, dim)] = source[RIDX(i+2, j+2, dim)];
					destnation[RIDX(dim-3-j, i+3, dim)] = source[RIDX(i+3, j+2, dim)];

					destnation[RIDX(dim-4-j, i, dim)] = source[RIDX(i, j+3, dim)];
					destnation[RIDX(dim-4-j, i+1, dim)] = source[RIDX(i+1, j+3, dim)];
					destnation[RIDX(dim-4-j, i+2, dim)] = source[RIDX(i+2, j+3, dim)];
					destnation[RIDX(dim-4-j, i+3, dim)] = source[RIDX(i+3, j+3, dim)];
				}
			}
		}
	}
return;
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    /* Register the naive_rotate as the first entry */
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    /* Register the grading version of the rotate function */
    add_rotate_function(&rotate, rotate_descr);   
    /* ... You may register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
	int i, j;
	for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	 dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}
/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void addPixel2(pixel_sum *total, pixel *one, pixel *two)
{
	total->red = one->red + two->red;
	total->green = one->green + two->green;
	total->blue = one->blue + two->blue;
	return;
}
void addPixel3(pixel_sum *totalPixel, pixel *first, pixel *second, pixel *third)
{
	totalPixel->red = first->red + second->red + third->red;
	totalPixel->green = first->green + second->green + third->green;
	totalPixel->blue = first->blue + second->blue + third->blue;
	return;
}
void rowSum(pixel_sum *all, int dim, pixel *row)
{
	int i;
	addPixel2(all++, row, row+1);
	row++;
	
	int end = dim -1;
	
	for (i=1; i<end; i++)
	{
		addPixel3(all++, row-1,row, row+1);
		row++;
	}
	addPixel2(all, row-1, row);
	return;
}
void avgPixel2(pixel *dest, pixel_sum *pixSumA, pixel_sum *pixSumB, int number)
{
	dest->red = (pixSumA->red + pixSumB->red)/number;
	dest->green = (pixSumA->green + pixSumB->green)/number;
	dest->blue = (pixSumA->blue + pixSumB->blue)/number;
	return;
}

void avgPixel3(pixel *destn, pixel_sum *firstSum, pixel_sum *secondSum, pixel_sum *thirdSum, int number)
{
	destn->red = (firstSum->red + secondSum->red + thirdSum->red)/number;
	destn->green = (firstSum->green + secondSum->green + thirdSum->green)/number;
	destn->blue = (firstSum->blue + secondSum->blue + thirdSum->blue)/number;
	return;
}
void smooth(int dim, pixel *src, pixel *destnation) 
{
	//naive_smooth(dim, src, dst);
	pixel_sum *row_sums = malloc(3*dim*sizeof(pixel_sum));
	pixel_sum *row = row_sums;
	pixel_sum *row1 = row+dim;
	pixel_sum *row2;
	int i, j;     
	

	rowSum(row, dim, src); 
	rowSum(row1, dim, src+dim);
	//this will calculate the row 0 alone 
	avgPixel2(destnation++, row++, row1++, 4);
	
	int top = dim -1;

		for (i=1; i<top; i++)
		{
			avgPixel2(destnation++,row++,row1++,6);
		}
	avgPixel2(destnation++,row,row1,4);
		//this one is to calculate the middle rows from 1 to the 3
		//int top = dim-1;
		for(i = 1; i < top; i++)
		{
			row = row_sums+((i-1)%3) *dim;
			row1 = row_sums+(i%3) *dim;
			row2 = row_sums+((i+1)%3) *dim;
			rowSum(row2, dim, src +(i+1)*dim);
			avgPixel3(destnation++,row++,row1++,row2++,6);
			for(j = 1; j <top; j++)
			{
				avgPixel3(destnation++,row++,row1++,row2++,9);
			}
			 avgPixel3(destnation++,row,row1,row2,6);
		}
	
	row = row_sums+((i-1)%3) *dim;
        row1 = row_sums+(i%3) *dim;

	avgPixel2(destnation++,row++,row1++,4);

	for(i=1; i<top; i++)
	{
		avgPixel2(destnation++,row++,row1++,6);
		avgPixel2(destnation,row,row1,4);
	}
return;
}
/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/
void register_smooth_functions() 
{
    /* Register the naive_smooth as the first entry */
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* Register the grading version of the smooth function */
    add_smooth_function(&smooth, smooth_descr);
    /* ... You may register additional test functions here */
}
