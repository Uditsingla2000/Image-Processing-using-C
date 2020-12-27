#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 #define PI 3.14159265
 #define WHITE 255
 #define BLACK 0
 #define THRESHOLD 128
 #define BMP_HEADER_SIZE 54
 #define BMP_COLOR_TABLE_SIZE 1024
 #define CUSTOM_IMG_SIZE 1024*1024
 #define MAX_PIXEL 255


void getImageDetail();
void getPixelVal();
void readImage(const char *imgName,
                  int *height,
                  int *width,
                  int *bitDepth,
                  unsigned char *header,
                  unsigned char *colorTable,
                  unsigned char *buf   );

void imageWriter(const char *imgName,
                 unsigned char *header,
                 unsigned char *colorTable,
                 unsigned char *buf,
                 int bitDepth);
void setPixel();
void colorToGray();
int  meanGray();
void grayToBinary();
void cropImage();
void nagative();
void ImgBlur();
void ImgSepia();
void TranslateImg();
void SizeChange();
void changeDetection();
void Morphing();
void rotation();
void reflectImg();

int  main()
{


   int x;

    int choice;
   {

    do{
        printf("Press 1 for details of image \n");
        printf("Press 2 for see pixel value\n");
        printf("Press 3 for set the pixel value\n");
        printf("Press 4 for convert Color image to grayscale \n");
        printf("Press 5 for find average gray level value\n");
        printf("Press 6 for convert gray image to binary\n");
        printf("Press 7 for Crop image\n");
        printf("Press 8 for Reflect Image (in horizontal or vertical ) \n");
        printf("Press 9 for using blur filter for color image\n");
        printf("Press 10 for using sepia filter for color image\n");
        printf("Press 11 for Image Morphing \n");
        printf("Press 12 for Change Detection\n");
        printf("Press 13 for Negative of image\n");
        printf("Press 14 to Enlarge or shrink image\n");
        printf("Press 15 to Translate image\n");
        printf("Press 16 for Rotating image \n");
        printf("Press 0 to EXIT \n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: getImageDetail();
                         break;
            case 2: getPixelVal();
                         break;
            case 3: setPixel();
                         break;
            case 4: colorToGray();
                         break;
            case 5: x=meanGray();
                    printf("The average Gray level Value of image is :%d\n\n",x);
                         break;
            case 6: grayToBinary();
                         break;
            case 7: cropImage();
                         break;
            case 8: reflectImg();
                         break;
            case 9: ImgBlur();
                         break;
           case 10: ImgSepia();
                         break;
           case 11: Morphing();
                         break;
           case 12: changeDetection();
                         break;
           case 13: nagative();
                         break;
           case 14: SizeChange();
                         break;
           case 15: TranslateImg();
                         break;
           case 16: rotation();
                         break;
        }

        }while(choice!=0);
}

    return 0;
}

void  readImage(const char *imgName,
                  int *height,
                  int *width,
                  int *bitDepth,
                  unsigned char *header,
                  unsigned char *colorTable,
                  unsigned char *buf
                  )
{
    int i;
    FILE *streamIn;
    streamIn = fopen(imgName,"rb");

    if(streamIn ==(FILE *)0)
    {

        printf("Unable to read image \n");
    }

    for(i =0;i<54;i++)
    {
        header[i] = getc(streamIn);
    }

    *width = *(int *)&header[18];
    *height = *(int *)&header[22];
    *bitDepth = *(int *)&header[28];

    if(*bitDepth <=8)
    {
        fread(colorTable,sizeof(unsigned char),1024,streamIn);
    }

    fread(buf,sizeof(unsigned char),CUSTOM_IMG_SIZE,streamIn);

    fclose(streamIn);
}



void getImageDetail()
{
    const char imgName[]= "images/man.bmp" ;

    int imgWidth, imgHeight, imgBitDepth;
   unsigned char imgHeader[BMP_HEADER_SIZE];
   unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
   unsigned char imgBuffer[CUSTOM_IMG_SIZE];

  readImage(imgName,&imgWidth,&imgHeight,&imgBitDepth,&imgHeader[0],&imgColorTable[0],&imgBuffer[0]);

    printf(" The number of columns in image is %d\n",imgWidth);
     printf(" The number of  rows in image is %d\n",imgHeight);
     int temp=imgBuffer[0];
     for(int i=0;i<CUSTOM_IMG_SIZE;i++)
{
    if(temp<imgBuffer[i])
        temp=imgBuffer[i];
}
printf("The Maximum pixel value is %d\n",temp);
printf("Success!!\n\n");

}

void getPixelVal()
{

   FILE *fIn = fopen("images/lighthouse.bmp","rb");


   unsigned  char imgHeader[54];
   unsigned  char colorTable[1024];

   if(fIn == NULL)
   {
       printf("Unable to open image \n");
   }

   for(int i=0;i<54;i++)
   {
       imgHeader[i] = getc(fIn);
   }
   int height = *(int*)&imgHeader[22];
   int width  = *(int*)&imgHeader[18];
   int bitDepth = *(int *)&imgHeader[28];

   int imgSize = height * width;


   unsigned char buffer[width][height];
   fread(buffer,sizeof(unsigned char),imgSize,fIn);
    fclose(fIn);

     int r;//row of pixel you want to find
     int c;//coloumn
     printf("enter the row and coloumn of required pixel\n");
     scanf("%d%d",&r,&c);
     int temp =buffer[r][c];
     printf("The value of required pixel is :%d \n",temp);
printf("\n");
}
 void setPixel()
{
    FILE *fIn = fopen("images/lighthouse.bmp","rb");
    FILE *fOut= fopen("images/lighthouse_pixelchange.bmp","wb");

   unsigned  char imgHeader[54];
   unsigned  char colorTable[1024];

   if(fIn == NULL)
   {
       printf("Unable to open image \n");
   }

   for(int i=0;i<54;i++)
   {
       imgHeader[i] = getc(fIn);
   }

   int height = *(int*)&imgHeader[22];
   int width  = *(int*)&imgHeader[18];
   int bitDepth = *(int *)&imgHeader[28];
 fwrite(imgHeader,sizeof(unsigned char),54,fOut);

   if(bitDepth<=8)
   {
     fread(colorTable,sizeof(unsigned char),1024,fIn);
     fwrite(colorTable,sizeof(unsigned char),1024,fOut);
   }
   int imgSize = height * width;


   unsigned char buffer[width][height];
   fread(buffer,sizeof(unsigned char),imgSize,fIn);


     int r;//row of pixel you want to find
     int c;//column
     printf("Enter the row and column of pixel whose value is to be altered\n");
     scanf("%d %d",&r,&c);
     int temp ;
     printf("Enter the new value of pixel(0 to 255)\n");
     scanf("%d",&temp);
     buffer[r][c]=temp;
     printf("The value of pixel is changed\n");

  fwrite(buffer,sizeof(unsigned char),imgSize,fOut);
    fclose(fIn);

  fclose(fOut);
printf("Success!!\n\n");
}


void colorToGray()
{

    FILE *fIn = fopen("images/lena_color.bmp","rb");
    FILE  *fOut = fopen("images/lena_gray.bmp","wb");

    unsigned char imgHeader[54];
    unsigned char  colorTable[1024];

    if(fIn ==NULL)
    {
        printf("Unable to open image\n");
    }

    for(int i =0;i<54;i++)
    {
        imgHeader[i] = getc(fIn);
    }
    fwrite(imgHeader,sizeof(unsigned char),54,fOut);

    int height = *(int*)&imgHeader[22];
    int width  = *(int*)&imgHeader[18];
    int bitDepth = *(int*)&imgHeader[28];

    if(bitDepth <= 8)
    {
        fread(colorTable,sizeof(unsigned char),1024,fIn);
        fwrite(colorTable,sizeof(unsigned char),1024,fOut);
    }

    int imgSize = height * width;
    unsigned char buffer[imgSize][3];

    for(int i =0;i<imgSize;i++)
    {
        buffer[i][0] = getc(fIn);       //red
        buffer[i][1] = getc(fIn);       //green
        buffer[i][2] = getc(fIn);       //blue
        int temp =0;

        temp = (buffer[i][0]*0.3 )+(buffer[i][1]*0.59)+(buffer[i][2]*0.11);
       putc(temp,fOut);
       putc(temp,fOut);
       putc(temp,fOut);
    }
    printf("Success!\n");

    fclose(fIn);
    fclose(fOut);
}
int meanGray()
{
 const char imgName[]= "images/man.bmp" ;

    int imgWidth, imgHeight, imgBitDepth;
   unsigned char imgHeader[BMP_HEADER_SIZE];
   unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
   unsigned char imgBuffer[CUSTOM_IMG_SIZE];

  readImage(imgName,&imgWidth,&imgHeight,&imgBitDepth,&imgHeader[0],&imgColorTable[0],&imgBuffer[0]);
   double total=0;
   int imgSize=imgWidth * imgHeight ;
   for(int i=0;i<imgSize;i++)
   {
       total =total+imgBuffer[i] ;
   }
   float mean = total/imgSize ;
   return (mean);

}
void grayToBinary()
{
    const char imgName[]= "images/man.bmp" ;
        const char newImgName[]= "images/man_binary.bmp" ;

    int imgWidth, imgHeight, imgBitDepth;
   unsigned char imgHeader[BMP_HEADER_SIZE];
   unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
   unsigned char imgBuffer[CUSTOM_IMG_SIZE];

  readImage(imgName,&imgWidth,&imgHeight,&imgBitDepth,&imgHeader[0],&imgColorTable[0],&imgBuffer[0]);
  //Black and White converter
  int imgSize=imgWidth*imgHeight;
    for(int i =0;i<imgSize;i++)
    {
        imgBuffer[i] = (imgBuffer[i]>THRESHOLD)? WHITE : BLACK;
    }
    imageWriter(newImgName,imgHeader,imgColorTable,imgBuffer,imgBitDepth);
}

void imageWriter(const char *imgName,
                 unsigned char *header,
                 unsigned char *colorTable,
                 unsigned char *buf,
                 int bitDepth)
   {
     FILE *fo = fopen(imgName,"wb");
     fwrite(header,sizeof(unsigned char),54,fo);
     if(bitDepth <=8)
     {
         fwrite(colorTable,sizeof(unsigned char),1024,fo);
     }
     fwrite(buf,sizeof(unsigned char),CUSTOM_IMG_SIZE, fo);
     fclose(fo);
printf("Success!!\n");
   }
void cropImage()
{ FILE *fIn = fopen("images/lighthouse.bmp","rb");
    FILE *fOut= fopen("images/lighthouse_croped.bmp","wb");

   unsigned  char imgHeader[54];
   unsigned  char colorTable[1024];

   if(fIn == NULL)
   {
       printf("Unable to open image \n");
   }

   for(int i=0;i<54;i++)
   {
       imgHeader[i] = getc(fIn);
   }

   int height = *(int*)&imgHeader[22];
   int width  = *(int*)&imgHeader[18];
   int bitDepth = *(int *)&imgHeader[28];
 fwrite(imgHeader,sizeof(unsigned char),54,fOut);

   if(bitDepth<=8)
   {
     fread(colorTable,sizeof(unsigned char),1024,fIn);
     fwrite(colorTable,sizeof(unsigned char),1024,fOut);
   }
   int imgSize = height * width;


   unsigned char buffer[width][height];
   fread(buffer,sizeof(unsigned char),imgSize,fIn);


  int l,r,d,u;
      unsigned char out_buffer[width][height];
      printf("How much you want to cut from left side: ");
      scanf("%d",&l);
      printf("How much you want to cut from right side: ");
      scanf("%d",&r);
      printf("How much you want to cut from upper side: ");
      scanf("%d",&u);
      printf("How much you want to cut from down side: ");
      scanf("%d",&d);
int x1,y1;
      for(int x=l;x<=width-r ;x++ )
      {
          for(int y=d ;y<=height-u;y++)
          {
              x1=x ;
              y1=y ;
            out_buffer[x1][y1]=buffer[x][y];
          }
      }
      fwrite(out_buffer,sizeof(unsigned char),imgSize,fOut);
    fclose(fIn);

  fclose(fOut);
printf("Success!!\n\n");

}

void nagative()
{
 const char imgName[]= "images/man.bmp" ;
        const char newImgName[]= "images/man_negative.bmp" ;

    int imgWidth, imgHeight, imgBitDepth;
   unsigned char imgHeader[BMP_HEADER_SIZE];
   unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
   unsigned char imgBuffer[CUSTOM_IMG_SIZE];

  readImage(imgName,&imgWidth,&imgHeight,&imgBitDepth,&imgHeader[0],&imgColorTable[0],&imgBuffer[0]);
  //Negative converter
  int temp;
  int imgSize=imgWidth*imgHeight;
    for(int i =0;i<imgSize;i++)
    {
        temp = (255-imgBuffer[i]);
        imgBuffer[i]=(temp<0)?0:temp;
    }
    imageWriter(newImgName,imgHeader,imgColorTable,imgBuffer,imgBitDepth);
printf("Success!!\n");
}

void ImgBlur()
{
    FILE *fIn =fopen("images/fruits.bmp","rb");
     FILE *fOut = fopen("images/fruits_blur.bmp","wb");

     unsigned char imgHeader[54];
     unsigned char colorTable[1024];

     if(fIn ==NULL)
     {
         printf("Unable to open file \n");
     }

     for(int i =0;i<54;i++)
     {
         imgHeader[i] = getc(fIn);
     }
     fwrite(imgHeader,sizeof(unsigned char),54,fOut);

     int height = *(int*)&imgHeader[22];
     int width  = *(int*)&imgHeader[18];
     int bitDepth = *(int*)&imgHeader[28];

     if(bitDepth <=8)
     {
         fread(colorTable,sizeof(unsigned char),1024,fIn);
         fwrite(colorTable, sizeof(unsigned char),1024,fOut);

     }

     int imgSize =  height * width;

     unsigned char buffer[imgSize][3];
     unsigned char output_buffer[imgSize][3];

     for(int i =0;i<imgSize;i++)
     {
         buffer[i][2] = getc(fIn);
         buffer[i][1] = getc(fIn);
         buffer[i][0] = getc(fIn);
     }
     float kernel[3][3] = {{1.0/9.0, 1.0/9.0,1.0/9.0},
                           {1.0/9.0, 1.0/9.0,1.0/9.0},
                           {1.0/9.0, 1.0/9.0,1.0/9.0}
                            };

    for(int x =1 ;x<height-1;x++)
    {
        for(int y =1;y<width -1;y++)
        {
            float sum0 = 0.0;
            float sum1 = 0.0;
            float sum2 = 0.0;
            for(int i =-1;i<=1;i++)
            {
                for(int j=-1;j<=1;j++)
                {
                    sum0  = sum0 + (float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][0];
                    sum1  = sum1 + (float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][1];
                    sum2  = sum2 + (float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][2];

                }
            }

            output_buffer[(x)*width+(y)][0] =  sum0;
            output_buffer[(x)*width+(y)][1] =  sum1;
            output_buffer[(x)*width+(y)][2] =  sum2;
        }
    }

    for(int i =0;i<imgSize;i++)
    {
        putc(output_buffer[i][2],fOut);
        putc(output_buffer[i][1],fOut);
        putc(output_buffer[i][0],fOut);
    }

    fclose(fOut);
    fclose(fIn);
printf("Success!!\n");
}

void ImgSepia()
{
FILE  *fIn =fopen("images/lena_color.bmp","rb");
    FILE  *fOut =fopen("images/lena_sepia.bmp","wb");

    unsigned char imgHeader[54];
    unsigned char colorTable[1024];

    if(fIn ==NULL)
    {
        printf("Unable to open file \n");
    }
    for(int i =0;i<54;i++)
    {
       imgHeader[i] = getc(fIn);
    }
    fwrite(imgHeader,sizeof(unsigned char),54,fOut);

    int height = *(int*)&imgHeader[22];
    int width  = *(int*)&imgHeader[18];
    int bitDepth = *(int*)&imgHeader[28];

    if(bitDepth <=8)
    {
        fread(colorTable,sizeof(unsigned char),1024,fIn);
        fwrite(colorTable,sizeof(unsigned char),1024,fOut);
    }

    int imgSize = height * width;
    int r,g,b;
    unsigned char buffer[imgSize][3];

    for(int i =0;i<imgSize;i++)
    {
        r=g=b=0;
        buffer[i][0] = getc(fIn);      //red
        buffer[i][1] = getc(fIn);      //green
        buffer[i][2] = getc(fIn);      //blue

        r = (buffer[i][0]*0.393) + (buffer[i][1]*0.769) + (buffer[i][2]*0.189);
        g = (buffer[i][0]*0.349) + (buffer[i][1]*0.686) + (buffer[i][2]*0.168);
        b = (buffer[i][0]*0.272) + (buffer[i][1]*0.534) + (buffer[i][2]*0.131);

        if(r>MAX_PIXEL){ r =MAX_PIXEL;}
        if(g>MAX_PIXEL){ g = MAX_PIXEL;}
        if(b>MAX_PIXEL){ b = MAX_PIXEL;}

        putc(b,fOut);
        putc(g,fOut);
        putc(r,fOut);

    }

    fclose(fOut);
    fclose(fIn);

printf("Success!!\n");
}


void changeDetection()
{
      FILE * original_file = fopen("images/cameraman.bmp","rb");
   FILE * original_file2 = fopen("images/lena512.bmp","rb");
   FILE * duplicate_file = fopen("images/lt.bmp","wb");
   FILE * duplicate_file2 = fopen("images/ltc.bmp","wb");

   unsigned char imgHeader[54];
   unsigned char colorTable[1024];

   unsigned char imgHeader2[54];
   unsigned char colorTable2[1024];


   for(int i =0;i<54;i++)
   {
       imgHeader[i] = getc(original_file);
      imgHeader2[i] = getc(original_file2);
   }
   fwrite(imgHeader, sizeof(unsigned char),54,duplicate_file);
   fwrite(imgHeader2, sizeof(unsigned char),54,duplicate_file2);

   int height = *(int *)&imgHeader[22];
   int width =  *(int *)&imgHeader[18];
   int bitDepth = *(int *)&imgHeader[28];
   int imgSize = height * width;

   int height2 = *(int *)&imgHeader2[22];
   int width2 =  *(int *)&imgHeader2[18];
   int bitDepth2 = *(int *)&imgHeader2[28];
   int imgSize2 = height2 * width2;

   if(bitDepth <=8)
   {
       fread(colorTable,sizeof(unsigned char), 1024, original_file);
       fwrite(colorTable,sizeof(unsigned char), 1024,duplicate_file);
       fread(colorTable2,sizeof(unsigned char), 1024, original_file2);
       fwrite(colorTable2,sizeof(unsigned char), 1024,duplicate_file2);
   }
   unsigned char buffer[imgSize];
     unsigned char buffer2[imgSize2];
   fread(buffer,sizeof(unsigned char),imgSize,original_file);
   fread(buffer2,sizeof(unsigned char),imgSize2,original_file2);
   int temp ;
   int array[imgSize] ;
   for(int i =0;i<imgSize;i++)
   {
       temp = buffer[i] -  buffer2[i];
         if (temp < 0 )
         {
           temp = temp*(-1) ;
         }
         buffer[i] = temp ;
    }

fwrite(buffer,sizeof(unsigned char), imgSize,duplicate_file);

  fwrite(buffer2,sizeof(unsigned char), imgSize2,duplicate_file2);
   fclose(original_file);
   fclose(original_file2);
   fclose(duplicate_file);
      fclose(duplicate_file2);
printf("Success!!\n\n");

    return 0;
}
void Morphing()
{
   FILE * original_file = fopen("images/lighthouse.bmp","rb");
   FILE * original_file2 = fopen("images/lena512.bmp","rb");
   FILE * duplicate_file = fopen("images/mt.bmp","wb");
   FILE * duplicate_file2 = fopen("images/mtc.bmp","wb");

   unsigned char imgHeader[54];
   unsigned char colorTable[1024];

   unsigned char imgHeader2[54];
   unsigned char colorTable2[1024];


   for(int i =0;i<54;i++)
   {
       imgHeader[i] = getc(original_file);
      imgHeader2[i] = getc(original_file2);
   }
   fwrite(imgHeader, sizeof(unsigned char),54,duplicate_file);
   fwrite(imgHeader2, sizeof(unsigned char),54,duplicate_file2);

   int height = *(int *)&imgHeader[22];
   int width =  *(int *)&imgHeader[18];
   int bitDepth = *(int *)&imgHeader[28];
   int imgSize = height * width;

   int height2 = *(int *)&imgHeader2[22];
   int width2 =  *(int *)&imgHeader2[18];
   int bitDepth2 = *(int *)&imgHeader2[28];
   int imgSize2 = height2 * width2;

   if(bitDepth <=8)
   {
       fread(colorTable,sizeof(unsigned char), 1024, original_file);
       fwrite(colorTable,sizeof(unsigned char), 1024,duplicate_file);
       fread(colorTable2,sizeof(unsigned char), 1024, original_file2);
       fwrite(colorTable2,sizeof(unsigned char), 1024,duplicate_file2);
   }
   unsigned char buffer[imgSize];
     unsigned char buffer2[imgSize2];
   fread(buffer,sizeof(unsigned char),imgSize,original_file);
   fread(buffer2,sizeof(unsigned char),imgSize2,original_file2);
   int temp ;
   int array[imgSize] ;
   for(int i =0;i<imgSize;i++)
   {
       temp = buffer[i] +  buffer2[i];
         if (temp >255 )
         {
           temp = 255 ;
         }
         buffer[i] = temp ;
    }
fwrite(buffer,sizeof(unsigned char), imgSize,duplicate_file);

  fwrite(buffer2,sizeof(unsigned char), imgSize2,duplicate_file2);
   fclose(original_file);
   fclose(original_file2);
   fclose(duplicate_file);
      fclose(duplicate_file2);
 printf("Success!!\n\n");



}
void TranslateImg()
{
    FILE *fIn = fopen("images/lighthouse.bmp","rb");
    FILE *fOut= fopen("images/lighthouse_translated.bmp","wb");

   unsigned  char imgHeader[54];
   unsigned  char colorTable[1024];

   if(fIn == NULL)
   {
       printf("Unable to open image \n");
   }

   for(int i=0;i<54;i++)
   {
       imgHeader[i] = getc(fIn);
   }

   int height = *(int*)&imgHeader[22];
   int width  = *(int*)&imgHeader[18];
   int bitDepth = *(int *)&imgHeader[28];
 fwrite(imgHeader,sizeof(unsigned char),54,fOut);

   if(bitDepth<=8)
   {
     fread(colorTable,sizeof(unsigned char),1024,fIn);
     fwrite(colorTable,sizeof(unsigned char),1024,fOut);
   }
   int imgSize = height * width;


   unsigned char buffer[width][height];
   fread(buffer,sizeof(unsigned char),imgSize,fIn);


  int c1,c2;
      unsigned char out_buffer[width][height];
      printf("How much you want to shift in horizontal : ");
      scanf("%d",&c1);
      printf("How much you want to shift in vertical : ");
      scanf("%d",&c2);

int x1,y1;
      for(int x=1;x<=width ;x++ )
      {
          for(int y=1 ;y<=height;y++)
          {
              x1=x +c1 ;
              y1=y +c2;
            out_buffer[x1][y1]=buffer[x][y];
          }
      }
      fwrite(out_buffer,sizeof(unsigned char),imgSize,fOut);
    fclose(fIn);

  fclose(fOut);
printf("Success!!\n\n");
}
void SizeChange()
{
    FILE *fIn = fopen("images/cameraman.bmp","rb");
    FILE *fOut= fopen("images/cameraman_resized.bmp","wb");

   unsigned  char imgHeader[54];
   unsigned  char colorTable[1024];

   if(fIn == NULL)
   {
       printf("Unable to open image \n");
   }

   for(int i=0;i<54;i++)
   {
       imgHeader[i] = getc(fIn);
   }

   int height = *(int*)&imgHeader[22];
   int width  = *(int*)&imgHeader[18];
   int bitDepth = *(int *)&imgHeader[28];
 fwrite(imgHeader,sizeof(unsigned char),54,fOut);

   if(bitDepth<=8)
   {
     fread(colorTable,sizeof(unsigned char),1024,fIn);
     fwrite(colorTable,sizeof(unsigned char),1024,fOut);
   }
   int imgSize = height * width;


   unsigned char buffer[width][height];
   fread(buffer,sizeof(unsigned char),imgSize,fIn);


  float c;
      unsigned char out_buffer[width][height];
      printf("How much is the factor for size change(>1 for enlarge and <1 for shrink) : ");
      scanf("%f",&c);


int x1,y1;
      for(int x=0;x<width ;x++ )
      {
          for(int y=0 ;y<height;y++)
          {
              x1=x*c ;
              y1=y*c;
            out_buffer[x1][y1]=buffer[x][y];
          }
      }
      fwrite(out_buffer,sizeof(unsigned char),imgSize,fOut);
    fclose(fIn);

  fclose(fOut);
printf("Success!!\n\n");
}

void rotation()
{
    FILE *fIn = fopen("images/lighthouse.bmp","rb");
    FILE *fOut= fopen("images/lighthouse_rotated(90).bmp","wb");

   unsigned  char imgHeader[54];
   unsigned  char colorTable[1024];

   if(fIn == NULL)
   {
       printf("Unable to open image \n");
   }

   for(int i=0;i<54;i++)
   {
       imgHeader[i] = getc(fIn);
   }

   int height = *(int*)&imgHeader[22];
   int width  = *(int*)&imgHeader[18];
   int bitDepth = *(int *)&imgHeader[28];
 fwrite(imgHeader,sizeof(unsigned char),54,fOut);

   if(bitDepth<=8)
   {
     fread(colorTable,sizeof(unsigned char),1024,fIn);
     fwrite(colorTable,sizeof(unsigned char),1024,fOut);
   }
   int imgSize = height * width;


   unsigned char buffer[width][height];
   unsigned char out_buffer[width][height];
   fread(buffer,sizeof(unsigned char),imgSize,fIn);

  float h , val;
  int x1,y1;
    printf("Enter the value of angle :");
    scanf("%f",&h) ;
    val = PI / 180;
    for(int x =0;x<width;x++)
    {
        for(int y =0;y<height;y++)
        {   if (h<=90 && h>=0)
        {
                 x1 = x*cos(h*val) + y*sin(h*val) ;
             y1 = -1*x*sin(h*val ) + y*cos(h*val) ;
        }

             out_buffer[x1][y1] = buffer[x][y];
        }
    }
fwrite(out_buffer,sizeof(unsigned char),imgSize,fOut);
    printf("Success !\n\n");

   fclose(fIn);
   fclose(fOut);
    return 0;

}

void reflectImg()
{
  FILE *fIn = fopen("images/lighthouse.bmp","rb");
    FILE *fOut= fopen("images/lighthouse_reflected.bmp","wb");

   unsigned  char imgHeader[54];
   unsigned  char colorTable[1024];

   if(fIn == NULL)
   {
       printf("Unable to open image \n");
   }

   for(int i=0;i<54;i++)
   {
       imgHeader[i] = getc(fIn);
   }

   int height = *(int*)&imgHeader[22];
   int width  = *(int*)&imgHeader[18];
   int bitDepth = *(int *)&imgHeader[28];
 fwrite(imgHeader,sizeof(unsigned char),54,fOut);

   if(bitDepth<=8)
   {
     fread(colorTable,sizeof(unsigned char),1024,fIn);
     fwrite(colorTable,sizeof(unsigned char),1024,fOut);
   }
   int imgSize = height * width;


   unsigned char buffer[width][height];
   fread(buffer,sizeof(unsigned char),imgSize,fIn);
      unsigned char out_buffer[width][height];


int x1,y1;
printf("Image will be reflected upside down\n");

   for(int x =0;x<width;x++)
   {
    for(int y = 0;y<height;y++)
    {
      x1 = width - x ;
      y1 = y  ;
      out_buffer[x1][y1] = buffer[x][y];

        }
    }
fwrite(out_buffer,sizeof(unsigned char),imgSize,fOut);
    fclose(fIn);

  fclose(fOut);
printf("Success!!\n\n");
}
