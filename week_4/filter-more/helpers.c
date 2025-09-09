#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Going through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Half picture since we are changing two pixels at a time
    int half_picture = width / 2;

    // Going through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < half_picture; j++)
        {
            int temporary_pixel;

            // Red
            temporary_pixel = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = temporary_pixel;

            // Green
            temporary_pixel = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = temporary_pixel;

            // Blue
            temporary_pixel = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = temporary_pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Declaring a temporary image to store the blurred pixels without affecting others
    typedef struct
    {
        int temp_Blue;
        int temp_Green;
        int temp_Red;
    } temporary_image;

    temporary_image pixel[height][width];

    // Going through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Checking the 3x3 neighbors
            double neighbors = 0;
            int total_red = 0;
            int total_green = 0;
            int total_blue = 0;
            for (int neighbor_i = -1; neighbor_i <= 1; neighbor_i++)
            {
                for (int neighbor_j = -1; neighbor_j <= 1; neighbor_j++)
                {
                    int row_neighbor = i + neighbor_i;
                    int column_neighbor = j + neighbor_j;

                    // Checking if there are neighbors "off limits"
                    if (row_neighbor < 0 || row_neighbor >= height || column_neighbor < 0 || column_neighbor >= width)
                    {
                        continue;
                    }

                    total_red += image[row_neighbor][column_neighbor].rgbtRed;
                    total_green += image[row_neighbor][column_neighbor].rgbtGreen;
                    total_blue += image[row_neighbor][column_neighbor].rgbtBlue;
                    neighbors++;
                }
            }

            // Getting the averages
            int average_red = round(total_red / neighbors);
            int average_green = round(total_green / neighbors);
            int average_blue = round(total_blue / neighbors);

            // Storing the blurred pixels
            pixel[i][j].temp_Red = average_red;
            pixel[i][j].temp_Green = average_green;
            pixel[i][j].temp_Blue = average_blue;
        }
    }

    // Storing the blurred picture from temporary into the output
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = pixel[i][j].temp_Red;
            image[i][j].rgbtGreen = pixel[i][j].temp_Green;
            image[i][j].rgbtBlue = pixel[i][j].temp_Blue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    // Declaring kernels for the Sobel function
    int gx_kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Declaring a temporary image to store the modified pixels without affecting others
    typedef struct
    {
        int temp_Blue;
        int temp_Green;
        int temp_Red;
    } temporary_image;

    temporary_image pixel[height][width];

    // Going through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Declaring colors:
            // Gx
            int gx_red = 0;
            int gx_green = 0;
            int gx_blue = 0;
            // Gy
            int gy_red = 0;
            int gy_green = 0;
            int gy_blue = 0;

            // Checking the 3x3 neighbors
            for (int neighbor_i = -1; neighbor_i <= 1; neighbor_i++)
            {
                for (int neighbor_j = -1; neighbor_j <= 1; neighbor_j++)
                {
                    // Position of the neighbors in the image
                    int row_neighbor = i + neighbor_i;
                    int column_neighbor = j + neighbor_j;

                    // Checking if the neighbor is "off limits"
                    if (row_neighbor < 0 || row_neighbor >= height || column_neighbor < 0 || column_neighbor >= width)
                    {
                        // We can ignore it because black == 0 anyway
                        continue;
                    }

                    // Selecting the value of the kernel
                    int gx_kernel_value = gx_kernel[neighbor_i + 1][neighbor_j + 1];
                    int gy_kernel_value = gy_kernel[neighbor_i + 1][neighbor_j + 1];

                    // Declaring colors for clarity
                    int current_pixel_red = image[row_neighbor][column_neighbor].rgbtRed;
                    int current_pixel_green = image[row_neighbor][column_neighbor].rgbtGreen;
                    int current_pixel_blue = image[row_neighbor][column_neighbor].rgbtBlue;

                    // Accumulating Gx colors
                    gx_red += gx_kernel_value * current_pixel_red;
                    gx_green += gx_kernel_value * current_pixel_green;
                    gx_blue += gx_kernel_value * current_pixel_blue;

                    // Accumulating Gy colors
                    gy_red += gy_kernel_value * current_pixel_red;
                    gy_green += gy_kernel_value * current_pixel_green;
                    gy_blue += gy_kernel_value * current_pixel_blue;
                }
            }

            // Calculate Sobel algorithm for each color and cap it at 255:
            // Final red
            int red_result = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            if (red_result > 255)
            {
                red_result = 255;
            }

            // Final green
            int green_result = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            if (green_result > 255)
            {
                green_result = 255;
            }

            // Final blue
            int blue_result = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));
            if (blue_result > 255)
            {
                blue_result = 255;
            }

            // Storing the Sobel pixels
            pixel[i][j].temp_Red = red_result;
            pixel[i][j].temp_Green = green_result;
            pixel[i][j].temp_Blue = blue_result;
        }
    }

    // Storing the new picture from temporary into the output
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = pixel[i][j].temp_Red;
            image[i][j].rgbtGreen = pixel[i][j].temp_Green;
            image[i][j].rgbtBlue = pixel[i][j].temp_Blue;
        }
    }
    return;
}
