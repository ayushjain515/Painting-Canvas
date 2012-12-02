#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>


/*---------------------------------------------------------------------
 ----------------------------------------------------------------------
  LIST OF FUNCTIONS USED IN THE PROGRAMS...
 ----------------------------------------------------------------------
 ---------------------------------------------------------------------*/
 void button();
 void paint_screen();
 void color_pallet();
 void color_choice();
 void DialogBox();
 void exit_func();
 void option_menu();
 void option_choice();
 void screen1();
 void namepage();
 void kosh();
 void square();
/*---------------------------------------------------------------------
 most of the variables used in the program below have been
 collectively declared here as global variables for the
 convinience of editting later on if needed...
 -----------------------------------------------------------------------
 ---------------------------------------------------------------------*/

 union REGS i,o;
 char *dbox,*yes_up,*no_up,*yes_down,*no_down,*icon;
 void far *ptr[4];
 int x1=0,y1=0,x2=0,y2=0,x3=0,y3=0,x4=0,y4=0,rx=0,ry=0;
 int run=0,p=1;
 int color=0;
 int flag=0,bflag=0;
 int far *a=NULL;
 int tmp,tem;
 int bsize=0;
 int p,q;

 typedef struct poly
 {
	int x;
	int y;
	struct poly *next;
 }poly1;
 poly1 *start,*temp,*last,*temp1;

/*---------------------------------------------------------------------
 ----------------------------------------------------------------------
 ----------------------------------------------------------------------
 These are the functions used to include mouse pointer in the program..
 ----------------------------------------------------------------------
 ----------------------------------------------------------------------
 ---------------------------------------------------------------------*/

 readKey(int *ascii, int *scan)
 {
	i.h.ah=0x00;
	int86(0x16,&i,&o);
	*scan=o.h.ah;
	*ascii=o.h.al;
 }

 watchKey(int *ascii, int *scan)
 {
	i.h.ah=0x01;
	int86(0x16,&i,&o);
	*scan=o.h.ah;
	*ascii=o.h.al;
 }

 initMouse()
 {
	i.x.ax=0;
	int86(0x33,&i,&o);
	return(o.x.ax);
 }

 showMouse()
 {
	i.x.ax=1;
	int86(0x33,&i,&o);
 }

 hideMouse()
 {
	i.x.ax=2;
	int86(0x33,&i,&o);
 }

 getMousePos(int *button,int *x,int *y)
 {
	i.x.ax=3;
	int86(0x33,&i,&o);
	*button=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
 }

 setMousePos(int x,int y)
 {
	i.x.ax=4;
	i.x.cx=x;
	i.x.dx=y;
	int86(0x33,&i,&o);
 }

 setMouseHoriz(int minX,int maxX)
 {
	i.x.ax=7;
	i.x.cx=minX;
	i.x.dx=maxX;
 }

 setMouseVert(int minY,int maxY)
 {
	i.x.ax=8;
	i.x.cx=minY;
	i.x.dx=maxY;
 }

 restrictMouse(int left,int top,int right,int bottom)
 {
	setMouseHoriz(left,right);
	setMouseVert(top,bottom);
 }

 isMouseIn(int left,int top,int right,int bottom,int *button)
 {
	int x,y;
	getMousePos(button,&x,&y);
	if(x>=left && x<=right && y>=top && y<=bottom)
		return(1);
	else
		return(0);
 }

 /*---------------------------------------------------------------------
  ----------------------------------------------------------------------
  ----------------------------------------------------------------------
  end of mouse functions....
  ----------------------------------------------------------------------
  ----------------------------------------------------------------------
  ---------------------------------------------------------------------*/

  void save_screen(void far *buf[4],int mx,int my)
{
   unsigned size;
   int ystart=0, yend, yincr, block;

   yincr = (my+1) / 4;
   yend = yincr;
   size = imagesize(0, ystart, mx, yend);
/* get byte size of image */

   for (block=0; block<=3; block++)
   {
      if ((buf[block] = farmalloc(size)) == NULL)
      {
	 closegraph();
	 printf("Error: not enough heap space in save_screen().\n");
	 exit(1);
      }

      getimage(0, ystart, mx, yend, buf[block]);
      ystart = yend + 1;
      yend += yincr + 1;
   }
}
/*save the last display on the screen to buffer memory*/



void restore_screen(void far *buf[4],int mx,int my)
{
   int ystart=0, yend, yincr, block;

   yincr = (my+1) / 4;
   yend = yincr;

   for (block=0; block<=3; block++)
   {
      putimage(0, ystart, buf[block], COPY_PUT);
      farfree(buf[block]);
      ystart = yend + 1;
      yend += yincr + 1;
   }
}


void namepage(int mx,int my)
  {
  int gd=DETECT,gm;
  int j;
	   setbkcolor(BLUE);
			settextstyle(0,0,11);
	       //	 setcolor(11);
		 while(flag!=1)
		 {
	     //	for(j=0;j<(getmaxx()-400);j=j+8)
		for(j=0;j<(getmaxx()/3);j=j+8)
		{
		     // b=random(16);

		    // cleardevice();
		      setcolor(LIGHTGRAY);
		      cleardevice();
		      outtextxy(30,j,"J");
			delay(20);
		 }
	       //	 for(i=(getmaxx());i>150;i=i-8)
			for(j=0;j<(getmaxx()/3);j=j+8)
		 {
		   //	b=random(16);
		     //cleardevice();
			 setcolor(LIGHTGRAY);
			   cleardevice();
			 outtextxy(150,j,"I");
			 delay(20);
		  }
		 // for(i=0;i<(getmaxx()-400);i=i+8)
			for(j=0;j<(getmaxx()/3);j=j+8)
		  {
	    //	  b=random(16);
	      //	  cleardevice();
		  setcolor(LIGHTGRAY);
		    cleardevice();
		     outtextxy(270,j,"I");
		     delay(20);
		    }
		    for(j=0;j<(getmaxx()/3);j=j+8)
		    {
		    setcolor(LIGHTGRAY);
		      cleardevice();
		    outtextxy(390,j,"T");
		    delay(20);
		    }
				for(j=0;j<(getmaxx()/3);j=j+8)
		 {

			 setcolor(LIGHTGRAY);
			   cleardevice();
			 outtextxy(510,j,"U");
			 delay(20);
		  }

		 flag++;
		 }  cleardevice();
 setbkcolor(BLACK);
setcolor(RED);
settextstyle(2,0,7);
outtextxy(30,3,"(JAYPEE INSTITUTE OF INFORMATION TECHNOLOGY, NOIDA)");
setcolor(BROWN);

settextstyle(1,0,2);
sound(5000);
outtextxy(10,24,"Hemant Wadhwa");
delay(500);
outtextxy(20,60,"                     &");
delay(500);
outtextxy(20,100,"                          Ayush Jain");
delay(500);
outtextxy(20,140,"                                         &");

delay(500);
outtextxy(20,180,"                                            Surbhi Bhasker");
delay(500);
settextstyle(5,0,3);
outtextxy(20,200,"                presents");
delay(500);

cleardevice();

//setcolor(WHITE);
//outtextxy(20,300,"     panters canvas ");
nosound();
settextstyle(1,0,1);
setcolor(BLUE);
outtextxy(400,390,"Student      Mentor:");
setcolor(RED);
outtextxy(400,410," Anant       Mittal");
settextstyle(1,0,1);
setcolor(BLUE);
outtextxy(10,390,"Faculty sir:");
setcolor(RED);
outtextxy(10,410,"Mr.Sandeep Kumar Singh");

//clrscr();
//cleardevice();
settextstyle(4, 0,6);
   setbkcolor(0);
   setcolor(LIGHTGRAY);
   ellipse(mx/2-35, my/2, 0,360,180,120);
   setfillstyle(1,WHITE);
   floodfill(321,280,LIGHTGRAY);



   /*handle of palet*/
    setbkcolor(0);
   setcolor(BLACK);
   ellipse(148,240,0,360,40,28);
   setfillstyle(1,BLACK);
   floodfill(148,240,BLACK);



  /*colors of pallet*/
    setbkcolor(0);
   setcolor(RED);
   ellipse(230, 180, 0, 360, 50, 30);
   setfillstyle(1,RED);
   floodfill(230,180,RED);



    setbkcolor(0);
   setcolor(BLUE);
   ellipse(340,175, 0, 360, 50, 30);
   setfillstyle(1,BLUE);
   floodfill(340,175,BLUE);



   setbkcolor(0);
   setcolor(YELLOW);
   ellipse(395,240, 0, 360, 50, 30);
   setfillstyle(1,YELLOW);
   floodfill(395,240,YELLOW);



     setbkcolor(0);
   setcolor(GREEN);
   ellipse(230,300, 0, 360, 50, 30);
   setfillstyle(1,GREEN);
   floodfill(230,300,GREEN);



    setbkcolor(0);
   setcolor(MAGENTA);
   ellipse(340,305, 0, 360, 50, 30);
   setfillstyle(1,MAGENTA);
   floodfill(340,305,MAGENTA);

    /* circle of brush*/
    setcolor(LIGHTGRAY);
   circle(500,100,10);
   setfillstyle(1,LIGHTGRAY);
   floodfill(500,100,LIGHTGRAY);


   /*handel of brush*/
   setcolor(BROWN);
   ellipse(500,285,0,360,10, 185);
   setfillstyle(1,BROWN);
   floodfill(500,285,BROWN);


    /*brush of brush*/
    for(p=0;p<3;p++)
    {
       for(q=1;q<16;q++)
	{
	 tem=q;
	  setcolor(tem);
	  ellipse(492,75,60,270,3,20);
	  ellipse(488,50,325,60,8,15);
	  ellipse(498,75,300,120,12,45);
	  delay(400);
	}
     }

}


void screen1(void)
 {
 int i,tem,j;
 int poly[8];
 int gd=DETECT,gm;

 cleardevice();
 setcolor(BROWN);
 /*for frame*/
 for(i=0;i<10;i++)
 {
 line(75+i,120+i,500+i,40+i);
 line(75+i,120+i,120+i,430+i);
 line(120+i,430+i,560+i,350+i);
 line(500+i,40+i,560+i,350+i);
 }

 /*for stand*/
 for(i=0;i<12;i++)
 {
 line(240+i,10+i,130+i,110+i);
 line(240+i,10+i,450+i,50+i);
 line(250+2*i,410,230+2*i,480);
 }
 for(i=0;i<20;i++)
 {
 line(430+i,375,490+i,480);
 }


 setcolor(BLUE);
 line(86,131,500,51);
 line(86,131,131,420);
 line(131,420,560,350);
 line(500,51,560,350);
 setfillstyle(1,WHITE);
 floodfill(320,240,BLUE);
 /*getch();
 closegraph();
 restorecrtmode();


 void fun(int x)
 { int i;
 int tem;*/

 settextstyle(TRIPLEX_FONT,0,8);
 for(j=0;j<3;j++)
 {
 for(i=0;i<14;i++)
 {
  tem=i;
setcolor(tem);
 outtextxy(145,120,"PAINTERS");
 outtextxy(150,240,"CANVAS");
  setfillstyle(SOLID_FILL,BROWN);
 bar3d(140,220,480,230,20,20);
 bar3d(140,340,430,350,20,20);
 delay(450);

 }
 }

/* i=0;
 x=i;

 fun(x);*/
 getch();
 }

 void kosh(int x,int y,int x4,int y4,int n)
{
 int x1,y1,x2,y2,x3,xc,y3,yc;
 if (n==1)
 {
  line(x,y,x4,y4);
delay(20);
 }
 else
 {
  x1=(2*x+x4)/3;
  y1=(2*y+y4)/3;
  x2=(x+2*x4)/3;
  y2=(y+2*y4)/3;
 // x=(xl+xr)/2;
  xc=(x+x4)/2;
  yc=(y+y4)/2;

  x3=xc+p*1.73*(y2-yc);
  y3=yc+p*1.73 *(xc-x2);

  kosh(x,y,x1,y1,n-1);
  kosh(x1,y1,x3,y3,n-1);
  kosh(x3,y3,x2,y2,n-1);
  kosh(x2,y2,x4,y4,n-1);
//  delay(500);
 }
}


void square(int x1,int y1,int x2,int y2, int n)
{

	int x3,x4,x5,y3,y4,y5,m,x6,y6;
	if(n==1)
		line(x1,y1,x2,y2);

	else
	{
		x3 = (2*x1 +x2)/3;
		y3 = (2*y1 + y2)/3;
		x6 = (x1 + 2*x2)/3;
		y6 = (y1 + 2*y2)/3;
		x4=x3-(y6-y3);
		y4=y3-(x3-x6);
		x5=x6-(y2-y6);
		y5=y6-(x6-x2);

		square(x1,y1,x3,y3,n-1);
		square(x3,y3,x4,y4,n-1);
		square(x4,y4,x5,y5,n-1);
		square(x5,y5,x6,y6,n-1);
		square(x6,y6,x2,y2,n-1);
	}
}
 /*---------------------------------------------------------------------
 ----------------------------------------------------------------------
 ----------------------------------------------------------------------
 These are the functions used to generate 3-D buttons....
 ----------------------------------------------------------------------
 ----------------------------------------------------------------------
 ---------------------------------------------------------------------*/

 void button(int x1,int y1,int x2,int y2,int click,char* text,int colour)
{
      int up=0,low=15;
      setcolor(0);
      bar3d(x1,y1,x2,y2,0,0);
      if(click==0)
      up=7,low=11;
      else
      up=11,low=7;
      setcolor(low);
      line(x2,y1,x2,y2);
      line(x2+1,y2-1,x2,y2-1);
      line(x2+1,y1,x2+1,y2);
      line(x1,y2,x2,y2);

      setcolor(up);
      line(x1,y1,x2,y1);
      line(x1+1,y1+1,x2-1,y1+1);
      line(x1,y1,x1,y2);
      line(x1+1,y1+1,x1+1,y2-1);

      setcolor(colour);
      settextstyle(2,0,4);
      outtextxy(x1+(x2-x1)/2-22,(y1+(y2-y1)/2)-5,text);
      settextstyle(4,0,5);
      setcolor(1);
      settextjustify(CENTER_TEXT,CENTER_TEXT);
      outtextxy(320,12,"Painter's Canvas");
      settextjustify(LEFT_TEXT,TOP_TEXT);
}

/******************************************************************************************
 ******************************************************************************************
 This is the fucntion that is used to generate the orignal display on the scree.....
 ******************************************************************************************
 *****************************************************************************************/
void paint_screen(int mx,int my)
{

     cleardevice();
     setcolor(0);
     setbkcolor(0);
     gotoxy(30,4);
     settextstyle(DEFAULT_FONT, HORIZ_DIR,2);
     button(10,20,mx,my,0,"~~Painter's~~~~Canvas~~",15);
     button(0,0,mx,my,0," ",15);
     button(0,0,mx,50,0," ",15);
     button(0,50,90,my,0," ",15);
     button(90,50,mx,90,0," ",15);
     floodfill(mx-10,my-10,12);
     setcolor(9);
     line(0,50,mx,50);
     line(90,50,mx,50);
     line(90,50,90,my);
     line(90,90,mx,90);
     color_pallet(mx,my);
     option_menu(mx,my);
}

/******************************************************************************************
 ******************************************************************************************
 This function generates all the paint options as given on the left hand side...
 ******************************************************************************************
 *****************************************************************************************/

 void option_menu(int mx,int my)
{
	setcolor(8);
//	button(10,95,85,115,0,"Pencil",15);
	button(10,120,85,140,0,"Lines",15);
	button(10,145,85,165,0,"Circle",15);
	button(10,170,85,190,0,"Rectangle",15);
	button(10,195,85,215,0,"Triangle",15);
	button(10,220,85,240,0,"Elipse",15);
	button(10,245,85,265,0,"Figures",15);
	button(10,270,85,290,0,"Polygon",15);
	button(10,295,85,315,0,"Brush Size",15);
	button(10,375,85,395,0,"Eraser",15);
	button(10,400,85,420,0,"Clear",15);
	button(10,435,85,460,0,"EXIT",15);
}


/***************************************************************
 ***************************************************************
  This function is used to check for options selected and
  to inplement there use.....
 ***************************************************************
 ***************************************************************/


void option_choice(int x,int y,int input,int mx,int my)
{
     int i=0;
     if(x>10&&x<85)
     {
		   if(y>120&&y<140)
		   {
		   if((input&1)==1)
		   {               hidemouseptr();
				   button(10,120,85,140,1,"Line",15);
				   delay(300);
				   button(10,120,85,140,0,"Line",15);
				   showmouseptr();


				   while(!kbhit())
				   {
				   if((input&1)==1)
				   {
						   if(x1==0&&y1==0)
						   while((input&1)==1)
						   getmousepos(&input,&x1,&y1);
									       //else
								   else if(x2==0&&y2==0)
						   while((input&1)==1)
						   getmousepos(&input,&x2,&y2);
						   else
									       while((input&1)==1)
									       getmousepos(&input,&x3,&y3);
									//if(x1!=0&&y1!=0&&x2!=0&&y2!=0)
						if(x2!=0&&y2!=0&&x3!=0&&y3!=0)
						{
								     hidemouseptr();
								     setcolor(color);
											      //line(x1,y1,x2,y2);
												  line(x2,y2,x3,y3);
												  x2=y2=x3=y3=0;
												  showmouseptr();
						}
				   }
				   getmousepos(&input,&x,&y);
						   }
		  }
			  }



	    if(y>170&&y<190)
	    {
			    if((input&1)==1)
			    {
					    hidemouseptr();
					    button(10,170,85,190,1,"Rectangle",15);
					    delay(300);
							    button(10,170,85,190,0,"Rectangle",15);
							    showmouseptr();
							    while(!kbhit())
							{
								if((input&1)==1)
					    {
							    if(x1==0&&y1==0)
							    while((input&1)==1)
											getmousepos(&input,&x1,&y1);
										    else if(x2==0&&y2==0)
											while((input&1)==1)
											getmousepos(&input,&x2,&y2);
										    else
											  while((input&1)==1)
										  getmousepos(&input,&x3,&y3);
							    if(x2!=0&&y2!=0&&x3!=0&&y3!=0)
										{
											  hidemouseptr();
											  setcolor(color);
														  rectangle(x2,y2,x3,y3);
														      x2=y2=x3=y3=0;
														      showmouseptr();
							    }
								}
							getmousepos(&input,&x,&y);
							    }
			     }
		}



		if(y>195&&y<215)
		{
			if((input&1)==1)
				    {
					hidemouseptr();
					button(10,195,85,215,1,"Triangle",15);
							delay(300);
							button(10,195,85,215,0,"Triangle",15);
							showmouseptr();
							while(!kbhit())
							{
							    if((input&1)==1)
							    {
							if(x1==0&&y1==0)
							while((input&1)==1)
												       getmousepos(&input,&x1,&y1);
										else if(x2==0&&y2==0)
										    while((input&1)==1)
												       getmousepos(&input,&x2,&y2);
										else if(x3==0&&y3==0)
										    while((input&1)==1)
												       getmousepos(&input,&x3,&y3);
										else
										    while((input&1)==1)
												       getmousepos(&input,&x4,&y4);
										if(x2!=0&&y2!=0&&x3!=0&&y3!=0&&x4!=0&&y4!=0)
									    {                       hidemouseptr();
												    setcolor(color);
												    line(x2,y2,x3,y3);
												    line(x3,y3,x4,y4);
												    line(x2,y2,x4,y4);
												    x2=y2=x3=y3=x4=y4=0;
												    showmouseptr();
							}
				       }
				       getmousepos(&input,&x,&y);
						       }
			 }    getmousepos(&input,&x,&y);
		}



		if(y>145&&y<165)
		{
			if((input&1)==1)
			{
							hidemouseptr();
							button(10,145,85,165,1,"Circle",15);
							delay(300);
							button(10,145,85,165,0,"Circle",15);
							showmouseptr();
							while(!kbhit())
							{
							    if((input&1)==1)
							    {
							if(x1==0&&y1==0)
								while((input&1)==1)
												       getmousepos(&input,&x1,&y1);
								else if(x2==0&&y2==0)
										    while((input&1)==1)
										    getmousepos(&input,&x2,&y2);
										    else
										    while((input&1)==1)
												       getmousepos(&input,&x3,&y3);
							if(x2!=0&&y2!=0&&x3!=0&&y3!=0)
									    {         hidemouseptr();
										      setcolor(color);
													      x4=(int)(sqrt(pow(x3-x2,2)+pow(y3-y2,2))/2);
													      circle((x2+x3)/2,(y2+y3)/2,x4);
														  x2=y2=x3=y3=0;
														  showmouseptr();
								}
					 }
					 getmousepos(&input,&x,&y);
							 }
			 }
  }



  if(y>220&&y<240)
  {
		  if((input&1)==1)
			      {
				  hidemouseptr();
				  button(10,220,85,240,1,"Elipse",15);
				  delay(300);
				  button(10,220,85,240,0,"Elipse",15);
				  showmouseptr();
				  while(!kbhit())
				  {

				   if((input&1)==1)
				   {
					 if(x1==0&&y1==0)
					 while((input&1)==1)
					     getmousepos(&input,&x1,&y1);

					 else if(x2==0&&y2==0)
					 while((input&1)==1)
					     getmousepos(&input,&x2,&y2);

					 else if(x3==0&&y3==0)
					 while((input&1)==1)
						getmousepos(&input,&x3,&y3);

					 else
					      while((input&1)==1)
						getmousepos(&input,&x4,&y4);

					 if(x2!=0&&y2!=0&&x3!=0&&y3!=0&&x4!=0&&y4!=0)
					 {
					     setcolor(color);
					     hidemouseptr();
					     rx=(int)sqrt(pow(x3-x2,2)+pow(y3-y2,2));
					     ry=(int)sqrt(pow(x4-x2,2)+pow(y4-y2,2));
					     ellipse(x2,y2,0,360,rx,ry);
					     x2=y2=x3=y3=x4=y4=rx=ry=0;
					     showmouseptr();
					 }
					 }
					  getmousepos(&input,&x,&y);
				  }
			 }
  }



		if(y>245&&y<265)
		{
			if((input&1)==1)
			{
							button(10,245,85,265,1,"Figure",15);
							delay(300);
							button(10,245,85,265,0,"Figure",15);
							button(10,335,85,350,0,"Kosh",15);
							button(10,355,85,370,0,"Square",15);
			}
			getmousepos(&input,&x,&y);
		}



		if(y>335&&y<350)
		{
			if((input&1)==1)
				    {
					while(!kbhit())
					{
					    if((input&1)==1)
			{
					if(x1==0&&y1==0)
								    while((input&1)==1)
								    getmousepos(&input,&x1,&y1);
								else
								    while((input&1)==1)
										       getmousepos(&input,&x2,&y2);
					if(x2!=0&&y2!=0)
					{               hidemouseptr();
							setcolor(color);
										kosh(x2,y2,x2+110,y2,4);
										kosh(x2+110,y2,x2+110,y2+110,4);
										kosh(x2+110,y2+110,x2,y2+110,4);
										kosh(x2,y2+110,x2,y2,4);
										    x2=y2=0;
							showmouseptr();
					 }
					    }
					    getmousepos(&input,&x,&y);
					}
			}
	 }



		if(y>355&&y<370)
		{
	     if((input&1)==1)
	     {               hidemouseptr();
			     button(10,355,85,370,1,"Square",15);
					     delay(300);
					     button(10,355,85,370,0,"Square",15);
					     showmouseptr();
					     while(!kbhit())
					     {
								if((input&1)==1)
								{
							    if(x1==0&&y1==0)
											while((input&1)==1)
													   getmousepos(&input,&x1,&y1);
							    else
											while((input&1)==1)
													   getmousepos(&input,&x2,&y2);
							    if(x2!=0&&y2!=0)
										{                       hidemouseptr();
									    setcolor(color);
												    square(x2,y2,x2+110,y2,4);
												    square(x2+110,y2,x2+110,y2+110,4);
												    square(x2+110,y2+110,x2,y2+110,4);
												    square(x2,y2+110,x2,y2,4);
												    x2=y2=0;
												    showmouseptr();
								}
						}
				getmousepos(&input,&x,&y);
				}
	     }
       }



		if(y>400&&y<420)
		{
			if((input&1)==1||tmp==1)
				{
				cleardevice();
				paint_screen(mx,my);
			}
		}



		if(y>375&&y<395)
		{
			if((input&1)==1)
				    {                   hidemouseptr();
							button(10,375,85,395,1,"Eraser",15);
							delay(300);
							button(10,375,85,395,0,"Eraser",15);
							showmouseptr();
							while(!kbhit())
							{
							    if((input&1)==1)
							{
							if(x1==0&&y1==0)
										    while((input&1)==1)
												       getmousepos(&input,&x1,&y1);
							else
										{
										hidemouseptr();
										while((input&1)==1)
										{
										getmousepos(&input,&x2,&y2);
										setcolor(0);
										circle(x2,y2,3);
										setfillstyle(SOLID_FILL,0);
										floodfill(x2,y2,0);
										}
							showmouseptr();
										}
					}
					getmousepos(&input,&x,&y);
					}
			 }
       }



       if(y>295&&y<315)
	   {
		       if((input&1)==1)
				   {
				       while((input&1)==1)
					   getmousepos(&x,&y);
				       if(x>10&&x<85&&y>295&&y<315)
				       {
					   if(bflag=0)
					   {
				  button(10,295,85,315,1,"Brush Size",15);
						      bflag=1;
					   }
		       else
					   {
					   button(10,295,85,315,0,"Brush Size",15);
					   bflag=0;
					   }
				       }
				   }
	getmousepos(&input,&x,&y);
		}



		if(y>270&&y<300)
		{
			int a=1;
			if((input&1)==1)
			{       hidemouseptr();
				button(10,270,85,290,1,"Polygon",15);
				delay(300);
				button(10,270,85,290,0,"Polygon",15);
				showmouseptr();
				while(!kbhit())
				{
				if((input&1)==1)
				{
					if(x1==0&&y1==0)

					while((input&1)==1)
					      getmousepos(&input,&x1,&y1);

					else if(x2==0&&y2==0)

					while((input&1)==1)
					      getmousepos(&input,&x2,&y2);
					else if(x3==0&&y3==0)

					while((input&1)==1)
					      getmousepos(&input,&x3,&y3);
					else

					while((input&1)==1)
					      getmousepos(&input,&x4,&y4);

					if(x2!=0&&y2!=0&&x3!=0&&y3!=0&&x4!=0&&y4!=0)
					{
					   setcolor(color);
					   hidemouseptr();
					   line(x2,y2,x3,y3);
					   line(x3,y3,x4,y4);
					  if(a)
					  {rx=x2; ry=y2; a=0;}
					   x2=x3=x4; y2=y3=y4;
					   x4=0; y4=0;
					   showmouseptr();
					}
				       }
				       getmousepos(&input,&x,&y);
				       }
				line(rx,ry,x3,y3);
			 }    getmousepos(&input,&x,&y);
		}



		if(y>435&&y<460)
		{
			if((input&1)==1)
				{
				    while((input&1)==1)
							   getmousepos(&input,&x,&y);
			if(x>10&&x<85&&y>435&&y<460)
			{
						    exit_func();
						    DialogBox();
			}
				}
				getmousepos(&input,&x,&y);
		}
     }
}


/***********************************************************************************************
 ***********************************************************************************************
 Function for drawing color pallet.....
 ***********************************************************************************************
 ***********************************************************************************************/

void color_pallet(int mx,int my)
{
	setfillstyle(SOLID_FILL,9);
	setcolor(1);
	setfillstyle(SOLID_FILL,1);
	bar3d(95,55,115,89,3,1);
	setcolor(2);
	setfillstyle(SOLID_FILL,2);
	bar3d(125,55,145,89,3,2);
	setcolor(3);
	setfillstyle(SOLID_FILL,3);
	bar3d(155,55,175,89,3,3);
	setcolor(4);
	setfillstyle(SOLID_FILL,4);
	bar3d(185,55,205,89,3,4);
	setcolor(5);
	setfillstyle(SOLID_FILL,5);
	bar3d(215,55,235,89,3,5);
	setcolor(6);
	setfillstyle(SOLID_FILL,6);
	bar3d(245,55,265,89,3,6);
	setcolor(7);
	setfillstyle(SOLID_FILL,7);
	bar3d(275,55,295,89,3,7);
	setcolor(8);
	setfillstyle(SOLID_FILL,8);
	bar3d(305,55,325,89,3,8);
	setcolor(9);
	setfillstyle(SOLID_FILL,9);
	bar3d(335,55,355,89,3,9);
	setcolor(10);
	setfillstyle(SOLID_FILL,10);
	bar3d(365,55,385,89,3,9);
	setcolor(11);
	setfillstyle(SOLID_FILL,11);
	bar3d(395,55,415,89,3,11);
	setcolor(12);
	setfillstyle(SOLID_FILL,12);
	bar3d(423,55,445,89,3,12);
	setcolor(13);
	setfillstyle(SOLID_FILL,13);
	bar3d(453,55,475,89,3,13);
	setcolor(14);
	setfillstyle(SOLID_FILL,14);
	bar3d(485,55,505,89,3,14);
	setcolor(0);
//	bar3d(515,55,535,86,0,0);
  //	setcolor(15);
	setfillstyle(SOLID_FILL,15);
	bar3d(515,55,535,89,3,0);
	setcolor(15);
	setfillstyle(SOLID_FILL,0);
	bar3d(545,55,565,89,3,0);

	}



  /*---------------------------------------------------------------------
 ----------------------------------------------------------------------
 ----------------------------------------------------------------------
 This is the function for exit loop(handling)...
 ----------------------------------------------------------------------
 ----------------------------------------------------------------------
 ---------------------------------------------------------------------*/


void DialogBox(int mx,int my)       //Event Handler for dialog box
{
	int button,x,y,in1=0,in2=0;
	struct textsettingstype textinfo;
	cleardevice();
	putimage(198,158,dbox,XOR_PUT);
	showmouseptr();
	gettextsettings(&textinfo);
	settextstyle(0,HORIZ_DIR,1);
	while(1)
	{
		getmousepos(&button,&x,&y);


		if(x>=388&&x<=398&&y>=162&&y<=172)
		{
			if((button&1)==1)
			{
				while((button&1)==1)
					getmousepos(&button,&x,&y);
				hidemouseptr();                    //close button click
				cleardevice();
				settextstyle(textinfo.font,0,textinfo.charsize);
				hidemouseptr();
				cleardevice();
				showmouseptr();
				DialogBox(mx,my);
				break;
			}
		}
		getmousepos(&button,&x,&y);


		if(x>=230&&x<=280&&y>=215&&y<=238)
		{
			if((button&1)==1)
			{
				while((button&1)==1)
				{
					getmousepos(&button,&x,&y);
					if(x>=230&&x<=280&&y>=215&&y<=238)
					{
						if(in1==1) continue;
						hidemouseptr();
						putimage(230,215,yes_down,COPY_PUT);
						showmouseptr();
						in1=1;
					}                                    //yes button click

					else
					{
						if(in1==0)
							continue;
						hidemouseptr();
						putimage(230,215,yes_up,COPY_PUT);
						showmouseptr();
						in1=0;
					}
				}

				if(x>=230&&x<=280&&y>=215&&y<=238)
				{
					closegraph();
					restorecrtmode();

					exit(0);
				}
			}
		}

		if(x>=320&&x<=370&&y>=215&&y<=238)
		{
			if((button&1)==1)
			{

				while((button&1)==1)
				{
					getmousepos(&button,&x,&y);
					if(x>=320&&x<=370&&y>=215&&y<=238)
					{
						if(in2==1) continue;
						hidemouseptr();
						putimage(320,215,no_down,COPY_PUT);
						showmouseptr();
						in2=1;

					}

					else                                 //no button click
					{
						if(in2==0)
							continue;
						hidemouseptr();
						putimage(320,215,no_up,COPY_PUT);
						showmouseptr();
						in2=0;
					}
				}

				getmousepos(&button,&x,&y);
				if(x>=320&&x<=370&&y>=215&&y<=238)
				{
					hidemouseptr();
					cleardevice();
					settextstyle(textinfo.font,0,textinfo.charsize);
					hidemouseptr();
					cleardevice();
					showmouseptr();
//				   	exit_func();
//					DialogBox();
					main();

					//paint_screen(mx,my);
				}
			}
		}
   }
}

/*---------------------------------------------------------------------
 ----------------------------------------------------------------------
 ----------------------------------------------------------------------
 This is the function used to display the exit function on the screen.
 ----------------------------------------------------------------------
 ----------------------------------------------------------------------
 ---------------------------------------------------------------------*/


void exit_func(void)    //	actual drawing of dialog box
{
	int area;
	int poly[10];
	struct textsettingstype textinfo;
	cleardevice();
	gettextsettings(&textinfo);
	settextstyle(0,HORIZ_DIR,1);
	setfillstyle(1,BLUE);
	bar(200,160,400,235);
	setcolor(7);
	outtextxy(205,163,"Message");           //title bar
	setfillstyle(1,7);
	bar(200,175,400,250);
	bar(388,162,398,172);
	setcolor(WHITE);
	line(388,162,398,162);
	line(388,162,388,172);
	setcolor(5);
	line(388,172,398,172);
	line(398,162,398,172);
	setcolor(7);
	setcolor(8);
	outtextxy(390,164,"X");                 //close button
	outtextxy(260,190,"  Exit ?");           //message
	setcolor(WHITE);
	line(200,160,400,160);
	line(200,160,200,250);
	setcolor(8);                  // normal look
	line(400,160,400,250);
	line(200,250,400,250);
	setfillstyle(1,BLUE);
	outtextxy(243,223,"Yes");         //button text
	outtextxy(337,223,"No");
	setcolor(LIGHTBLUE);
	setcolor(WHITE);
	line(230,215,280,215);
	line(230,215,230,238);
	line(320,215,370,215);
	line(320,215,320,238);

	setcolor(8);
	line(280,215,280,238);
	line(230,238,280,238);

	line(370,215,370,238);
	line(320,238,370,238);
	poly[0] = 100;
	poly[1] = 100;
	poly[2] = 90;
	poly[3] = 122;
	poly[4] = 110;
	poly[5] = 122;
	poly[6] = poly[0];
	poly[7] = poly[1];
	setcolor(YELLOW);
	setfillstyle(1,7);
	bar(89,99,111,123);
	setfillstyle(1,YELLOW);
	fillpoly(4, poly);
	setcolor(8);
	settextstyle(4,0,1);
	outtextxy(98,100,"!");
	setcolor(WHITE);
	area=imagesize(89,99,111,123);
	icon=malloc(area);
	getimage(89,99,111,123,icon);
	putimage(89,99,icon,XOR_PUT);
	putimage(210,180,icon,COPY_PUT);
	setfillstyle(1,BLUE);
	settextstyle(0,HORIZ_DIR,1);
	setcolor(WHITE);
	area=imagesize(198,158,402,252);
	dbox=malloc(area);
	getimage(198,158,402,252,dbox);
	putimage(198,158,dbox,XOR_PUT);
	putimage(198,158,dbox,XOR_PUT);

	area=imagesize(230,215,280,238);
	yes_up=malloc(area);
	getimage(230,215,280,238,yes_up);
	putimage(230,215,yes_up,XOR_PUT);
	putimage(230,215,yes_up,XOR_PUT);

	area=imagesize(320,215,370,238);
	no_up=malloc(area);
	getimage(320,215,370,238,no_up);
	putimage(320,215,no_up,XOR_PUT);
	putimage(320,215,no_up,XOR_PUT);

	setcolor(8);
	line(230,215,280,215);
	line(230,215,230,238);

	line(320,215,370,215);
	line(320,215,320,238);

	setcolor(WHITE);
	line(280,215,280,238);
	line(230,238,280,238);

	line(370,215,370,238);
	line(320,238,370,238);

	area=imagesize(230,215,280,238);
	yes_down=malloc(area);
	getimage(230,215,280,238,yes_down);
	putimage(230,215,yes_down,XOR_PUT);
	putimage(230,215,yes_down,XOR_PUT);

	area=imagesize(320,215,370,238);
	no_down=malloc(area);
	getimage(320,215,370,238,no_down);
	putimage(320,215,no_down,XOR_PUT);
	putimage(320,215,no_down,XOR_PUT);

	putimage(320,215,no_up,COPY_PUT);
	putimage(230,215,yes_up,COPY_PUT);
	settextstyle(textinfo.font,0,textinfo.charsize);
}
/*******************************************************************************
*******************************************************************************
	       MAIN FUNCTION START HERE
*******************************************************************************
*******************************************************************************/


main()
{
int gd=DETECT,gm,maxx,maxy,x,y,button,prevx,prevy,run=0;
//initgraph(&gd,&gm,"c:\tc\bgi");
initgraph(&gd,&gm,"");
maxx=getmaxx();
maxy=getmaxy();
if(run==0)
{
namepage(maxx,maxy);
screen1();
tmp=1;
run=1;
}
setbkcolor(0);
option_choice(30,410,button,maxx,maxy);
tmp=0;
paint_screen(maxx,maxy);
setviewport(1,1,maxx-1,maxy-1,1);
if(initmouse()==0)
{
	closegraph();
	restorecrtmode();
	printf("mouse driver could not be loaded .. The program will now exit...");
	exit(1);
}
restrictmouseptr(1,51,maxx-1,maxy-1);
showmouseptr();

/***********************************************************************************
************************************************************************************
 this funtion is an infinite loop that handles
 free hand drawing and the choice option calling....
 ***********************************************************************************
 ***********************************************************************************/
while(1)
{
getmousepos(&button,&x,&y);

if(y>50&&y<90&&x>90&&x<maxx)
{
	while(x>90&&y>50&&y<90)
	{
		if((button&1)==1)
		{
		if(x>95&&x<115)
		{	setcolor(1);      color=1;}
		else if(x>125&&x<145)
		{	setcolor(2);      color=2;}
		else if(x>155&&x<175)
		{	setcolor(3);	  color=3;}
		else if(x>185&&x<205)
		{	setcolor(4);      color=4;}
		else if(x>215&&x<235)
		{	setcolor(5);      color=5;}
		else if(x>245&&x<265)
		{	setcolor(6);      color=6;}
		else if(x>275&&x<295)
		{	setcolor(7);      color=7;}
		else if(x>305&&x<325)
		{	setcolor(8);      color=8;}
		else if(x>335&&x<355)
		{	setcolor(9);      color=9;}
		else if(x>365&&x<385)
		{	setcolor(10);     color=10;}
		else if(x>395&&x<415)
		{	setcolor(11);     color=11;}
		else if(x>425&&x<445)
		{	setcolor(12);     color=12;}
		else if(x>455&&x<475)
		{	setcolor(13);     color=13;}
		else if(x>485&&x<505)
		{	setcolor(14);     color=14;}
		else if(x>515&&x<535)
		{	setcolor(15);     color=15;}
		else if(x>545&&x<565)
		{	setcolor(0);      color=0;}
		}
		getmousepos(&button,&x,&y);
	}
}

while(x>10&&x<85)
{		option_choice(x,y,button,maxx,maxy);
		getmousepos(&button,&x,&y);
}

if(x>90&&x<maxx&&y>90&&y<maxy)
{
 if((button&1)==1)
  {
  hidemouseptr();
  prevx=x;
  prevy=y;

 while((button&1)==1)
 {
 if(x>90&&x<maxx&&y>90&&y<maxy)
 {
	line(prevx,prevy,x,y);
	if(bflag==1)
	{
	line(prevx+1,prevy+1,x+1,y+1);
	line(prevx-1,prevy-1,x-1,y-1);
	}
 }
 prevx=x;prevy=y;
 getmousepos(&button,&x,&y);
 }
 showmouseptr();
 }
}
}
 exit_func();
// getch();
// getch();
 DialogBox(maxx,maxy);
 getch();
 getch();
 }

/*initilises mouse*/
initmouse()
{
i.x.ax=0;
int86(0x33,&i,&o);
return(o.x.ax);
}

//display mouse pointer
showmouseptr()
{
i.x.ax=1;
int86(0x33,&i,&o);
}

hidemouseptr()
{
i.x.ax=2;
int86(0x33,&i,&o);
}


//restrict mouse pointer
 restrictmouseptr(int x1,int y1,int x2,int y2)
 {
 i.x.ax=7;
 i.x.cx=x1;
 i.x.dx=x2;
 int86(0x33,&i,&o);

 i.x.ax=8;
 i.x.cx=y1;
 i.x.dx=y2;
 int86(0x33,&i,&o);
 }

 //get mouse coordinates and button status
 getmousepos(int *button,int *x,int *y)
 {
 i.x.ax=3;
 int86(0x33,&i,&o);
 *button=o.x.bx;
 *x=o.x.cx;
 *y=o.x.dx;
 }