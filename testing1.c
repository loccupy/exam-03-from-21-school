#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int width, height;
char *map;
char back, color, type;
float x, y, w, h;

int check(float i, float j)
{
    if(i < x || j < y || x + w < i || y + h < j)
        return 0;
    if(i - x < 1 || j - y < 1 || x + w - i < 1 || y + h - j < 1)
        return 2;
    return 1;
}

void draw(void)
{
    int i = 1, j, count;
    while(++i < width)
    {
        j = -1;
        while(++j < height)
        {
            count = check((float)i, (float)j);
            if(count == 2 || (count == 1 && type =='R'))
                map[i + j*width] = color;
        }
    }
}

int parse(FILE *file)
{
    int i = 0, res;
    if(fscanf(file, "%d %d %c\n", &width, &height, &back) != 3)
        return 1;
    if(width < 1 || width > 300 || height < 1 || height > 300)
        return 1;
    map = malloc(width * height);
    if(map == NULL)
        return 1;
    while(i < width * height)
        map[i++] = back;
    while((res = fscanf(file, "%c %f %f %f %f %c\n", &type, &x, &y, &w, &h, &color)) == 6)
    {
        if(w < 1 || h < 1 || !(type == 'r' || type == 'R'))
            return 1;
        draw();
    }
    if(res != -1)
        return 1;
    return 0;
}
// int parse(FILE *file)
// {
//     int i = 0, res;

//     if(fscanf(file, "%d %d %c\n", &width, &height, &back) != 3)
//         return(1);
//     if(width < 1 || width > 300 || height < 1 || height > 300)
//         return(1);
//     map = malloc(width*height);
//     if(map == NULL)
//         return(1);
//     while(i < width*height)
//         map[i++]= back;
//     while((res = fscanf(file, "%c %f %f %f %f %c\n", &type, &x, &y, &w, &h, &color)) == 6)
//     {
//         if(w < 1 || h < 1 || !(type == 'r' || type == 'R'))
//             return(1);
//         draw();
//     }
//     if(res != -1)
//         return(1);
//     return(0);
// }
void print(void)
{
    int i = -1;
    while(++i < height)
    {
        write(1, map + i * width, width);
        write(1, "\n", 1);
    }
}

int main(int argc, char **argv)
{
    FILE *file;
    if(argc != 2)
    {
        write(1, "Error: argument\n", 16);
        return (1);
    }
    if(!(file = fopen(argv[1], "r")) || parse(file))
    {
        write(1, "Error: Operation file corrupted\n", 32);
        return (1);
    }
    print();
    fclose(file);
    free(map);
    return (0);
}