#include<fstream.h>
#include<conio.h>
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
#include<ctype.h>
int a=0;
void blist();
void del(int &n);
void profile(int &n);
void add();
void mainmenu();
void assign();
void sort();
void edit(int t);
void store_in_list();

struct birddata
{
 char birdname[25];
 int cstatus;
}B[50];

union REGS in,out;
int callmouse()
	     {
	      in.x.ax=1;
	      int86(51,&in,&out);
	      return 1;
	     }
void mouseposi(int &xpos,int &ypos,int &click)
	      {
	       in.x.ax=3;
	       int86(51,&in,&out);
	       click=out.x.bx;
	       xpos=out.x.cx;
	       ypos=out.x.dx;
	      }
void assign()
{int i=0;
 ifstream fin;
 fin.open("BNLIST",ios::in);
 if(!fin)cout<<"file not found";
 fin.seekg(0);
 while(!fin.eof())
 {
    fin.read((char *)&B[i],sizeof(birddata));
    i++;
 }
 a=i-1 ;
 fin.close();
 mainmenu();
}
void mainmenu()
{clrscr();
int x,y,cl;
int gs=DETECT,gd;
initgraph(&gs,&gd,"C://TC//BGI");
int mx=getmaxx();
int my=getmaxy();
int cx=mx/2;
int cy=my/2;

setcolor(15);
rectangle(10,10,mx-10,my-10); //Frame

/* MENU */
rectangle(50,95,cx-100,cy-50);//1st       x>50&&x<(cx-100)&&y>95&&y<(cy-50)
floodfill(51,96,15);

rectangle(50,my-225,cx-100,my-122);//down 1st    x>50&&x<(cx-100)&&y>(my-225)&&y<(my-122)
floodfill(51,my-224,15);

rectangle(mx-225,95,mx-50,190); //3rd right     x>(mx-225)&&x<(mx-50)&&y>95&&y<190
floodfill(mx-224,96,15);

rectangle(mx-225,my-225,mx-50,my-122);//4th beneath right x>(mx-225)&&x<(mx-50)&&y>(my-225)&&y<(my-122)
floodfill(mx-224,my-224,15);

rectangle(cx-50,my-90,cx+50,my-50);    // x>(cx-50)&&x<(cx+50)&&y>(my-90)&&y<(my-50)
floodfill(cx,my-60,15);

/* MENU TEXT */
settextstyle(DEFAULT_FONT,0,2);
outtextxy((cx-(cx/5))-10,30,"MAIN MENU");//Heading
setcolor(0);
outtextxy(70,125,"BIRDS");//1st
outtextxy(70,my-175,"STATS"); //Down 1st
outtextxy(mx-155,125,"PIN");//3rd Right
outtextxy(mx-155,my-175,"ABOUT");//3rd down
outtextxy(cx-30,my-80,"EXIT");//EXIT


/* LOGO */

setfillstyle(SOLID_FILL,0);
fillellipse(cx,cy,135,135);//outer cirlce
setcolor(15);
setfillstyle(SOLID_FILL,15);
fillellipse(cx,cy,125,125);//inner circle
setcolor(0);
fillellipse(cx,cy,120,120);

/* LOWER WINGS */
setfillstyle(SOLID_FILL,0);
setcolor(0);
ellipse(cx,cy,225,315,120,120);
line(cx,cy,cx-85,cy+85);
line(cx,cy,cx+85,cy+85);
floodfill(cx,cy+50,0);

/*SIDE WINGS*/
setlinestyle(SOLID_LINE,1,3);
line(cx-50,cy+20,cx-100,cy+65);//OUTLINE LOWER
line(cx-50,cy+20,cx-100,cy-65);
floodfill(cx-100,cy,0);

setlinestyle(SOLID_LINE,1,3);
line(cx+50,cy+20,cx+100,cy+65);
line(cx+50,cy+20,cx+100,cy-65);
floodfill(cx+100,cy,0);
setcolor(15);
line(cx+50,cy,cx+110,cy+45);//LOWER WING
line(cx-50,cy,cx-110,cy+45);// "
line(cx+60,cy-20,cx+120,cy+20);//MIDDLE WING
line(cx-60,cy-20,cx-120,cy+20);// "
line(cx+60,cy-60,cx+120,cy-20);//UPPER WING
line(cx-60,cy-60,cx-120,cy-20);// "

/* UPPER BODY */
setcolor(0);
line(cx-95,cy-75,cx,cy+60);//BODY LOWER
line(cx+95,cy-75,cx,cy+60);// "
line(cx-70,cy-95,cx-15,cy-30);//BODY UPPER
line(cx+70,cy-95,cx+15,cy-30);// "
line(cx-15,cy-30,cx+15,cy-30);// BODY ENDS
floodfill(cx,cy-5,0);
/* NECK */
line(cx-30,cy-35,cx-15,cy-80);
line(cx+30,cy-35,cx+10,cy-68);
arc(cx-5,cy-78,100,180,10);//CURVE HEAD
line(cx-8,cy-88,cx+15,cy-88);
arc(cx+17,cy-68,100,180,7); //NECK
arc(cx+15,cy-82,50,90,6);//BEAK NOSE
line(cx+17,cy-88,cx+26,cy-80);//UPPER BEAK
line(cx+15,cy-76,cx+26,cy-80);
floodfill(cx,cy-70,0);

/* BODY TAIL PARTITION */
setcolor(15);
line(cx-98,cy-78,cx,cy+63);//BODY LOWER
line(cx+98,cy-78,cx,cy+63);// "

callmouse();
		 do
		  {cl=0;
		   mouseposi(x,y,cl);
		   if(x>50&&x<(cx-100)&&y>95&&y<(cy-50))
		     {if(cl==1)
			{cleardevice();
			 closegraph();
			 blist();
			}
		     }
		/*   if(x>50&&x<(cx-100)&&y>(my-225)&&y<(my-122))
		     {if(cl==1)
			{cleardevice();
			 closegraph();
			 stats();
			}
		     }
		   if(x>(mx-225)&&x<(mx-50)&&y>95&&y<190)
		     {if(cl==1)
			{cleardevice();
			 closegraph();
			 pin();
			}
		     }
		   if(x>(mx-225)&&x<(mx-50)&&y>(my-225)&&y<(my-122))
		     {if(cl==1)
			{cleardevice();
			 closegraph();
			 about();
			}
		     }*/
		   if(x>(cx-50)&&x<(cx+50)&&y>(my-90)&&y<(my-50))
		     {
		      if(cl==1)
			{cleardevice();
			 closegraph();
			 exit(0);
			}
		     }
		  }while(!kbhit());
}
void blist()
{clrscr();
 int cl,x,y;
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"C://TC//BGI");
 cout<<endl<<endl<<endl<<endl;
 int flag=0,l;
  char m='A';
  for(int k=0;k<a;k++)
     {
      if(B[k].birdname[0]==m)
	{
	 if(flag==0){cout<<endl<<"  "<<m<<endl<<"  ";}
	 l=strlen(B[k].birdname);
	 cout<<k+1<<"."<<B[k].birdname;
	 if((k+1)%3==0){cout<<endl<<"  ";}
	 else
	 { for(int i=0;i<(26-l);i++){cout<<" ";} }
	 flag=1;
	}
      else {m++;k--;flag=0;}
     }
 rectangle(0,0,639,475);
 rectangle(-1,10,640,40);
 settextstyle(SMALL_FONT,HORIZ_DIR,6);
 outtextxy(30,15,"   + ADD A NEW BIRD          DELETE    VIEW");
line(290,10,290,40);       // x>0&&x<290&&y>10&&y<40
 line(400,10,400,40);       // x>290&&x<400&&y>10&&y<40
line(470,10,470,40);      //  x>400&&x<470&&y>10&&y<40
line(608,10,608,40);      // x>470&&x<608&&y>10&&y<40
 circle(624,25,15);
int n;
setcolor(3);
settextstyle(SMALL_FONT,HORIZ_DIR,6);
outtextxy(490,15,"BIRDS LIST");
gotoxy(2,25);
setcolor(111);
cout<<"\n\n\n\n         Choose The bird name from the options above : ";
rectangle(0,0,639,475);
cin>>n;
callmouse();
		 do
		  {cl=0;
		   mouseposi(x,y,cl);
			  if(x>290&&x<400&&y>10&&y<40)
			  {if(cl==1)
			     {cleardevice();
			      closegraph();
			      del(n);
			     }
			   }
			   if(x>400&&x<470&&y>10&&y<40)
			   {if(cl==1)
			     { cleardevice();
			       closegraph();
			       profile(n);
			     }
			    }
		  if(x>0&&x<290&&y>10&&y<40)
		  {
		   if(cl==1)
		   { cleardevice();
		     closegraph();
		     a++;
		     add();
		   }
		  }
		  if(x>608&&x<639&&y>10&&y<40)
		  {
		   if(cl==1)
		   { cleardevice();
		     closegraph();
		     mainmenu();
		   }
		  }
		  }while(!kbhit());
}
void add()
{
 clrscr();
 char ch[300];
 ofstream fout;
 cout<<"Enter birds name : ";
 gets(B[a-1].birdname);
 fout.open(B[a-1].birdname,ios::out);
 fout<<B[a-1].birdname<<'$';
 cout<<"Type short description about "<<B[a-1].birdname<<" :"<<endl;
 gets(ch);
 fout<<ch<<'$';
 cout<<"What is the scientific name of "<<B[a-1].birdname<<" : ";
 gets(ch);
 fout<<ch<<'$';
 cout<<"Write the common names of "<<B[a-1].birdname<<" : ";
 gets(ch);
 fout<<ch<<'$';
 cout<<"Type the factors to correctly identify "<<B[a-1].birdname<<" :"<<endl;
 gets(ch);
 fout<<ch<<'$';
 cout<<"Write about the habitat of "<<B[a-1].birdname<<" : "<<endl;
 gets(ch);
 fout<<ch<<'$';
 cout<<"What do "<<B[a-1].birdname<<"'s eats to survive : "<<endl;
 gets(ch);
 fout<<ch<<'$';
 cout<<"Write about the nest of "<<B[a-1].birdname<<" : "<<endl;
 gets(ch);
 fout<<ch<<'$';
 cout<<"Write few words about the behaviour of "<<B[a-1].birdname<<" :";
 gets(ch);
 fout<<ch<<'$';
 cout<<"How are "<<B[a-1].birdname<<" safegaurded form being endangered/extinct : "<<endl;
 gets(ch);
 fout<<ch<<'$';
 cout<<"What is the conservation status of "<<B[a-1].birdname<<" (Least concern/concerned/Vulnerable/Isolated/Extinct) :"<<endl;
 gets(ch);
 if(strcmpi(ch,"LEAST CONCERN")==0)B[a-1].cstatus=1;
 else
   {
    if(strcmpi(ch,"CONCERNED")==0)B[a-1].cstatus=2;
    else
      {
       if(strcmpi(ch,"VULNERABLE")==0)B[a-1].cstatus=3;
       else
	 {
	  if(strcmpi(ch,"ISOLATED")==0)B[a-1].cstatus=4;
	  if(strcmpi(ch,"EXTINCT")==0)B[a-1].cstatus=5;
	 }
      }
   }
 fout<<ch<<'$';
 fout.close();
 store_in_list();
 sort();
 clrscr();
 int gd=DETECT,gm;
	 initgraph(&gd,&gm,"C:\\TC\\bgi");
	 setcolor(BLUE);
	 settextstyle(TRIPLEX_FONT,0,2);
	 outtextxy(175,150,"DATA SUCCESSFULLY ADDED");
	 cout<<"\n\n\n\n\n\n\n\n\n\n\n                               Press any key.....";
 getch();
 cleardevice();
 closegraph();
 blist();
}
void store_in_list()
{
 ofstream fout;
 fout.open("BNLIST",ios::app);
 fout.write((char *)&B[a-1],sizeof(birddata));
 fout.close();
}
void sort()
 {
  for(int i=0;i<a;i++)
   {
    B[i].birdname[0]=toupper(B[i].birdname[0]);
   }
   birddata temp;
   int d,pos;
   for(i=0;i<a-1;i++)
   { temp=B[i];
     d=B[i].birdname[0];pos=i;
     for(int j=i+1;j<a;j++)
      {
       if(B[j].birdname[0]<d){d=B[j].birdname[0];pos=j;}
      }
     B[i]=B[pos];
     B[pos]=temp;
   }
 }
void del(int &n)
{ birddata temp;
 remove(B[n-1].birdname);
 ifstream fin;
 fin.open("BNLIST",ios::in);
 ofstream fout;
 fout.open("TEMP",ios::out);
 while(!fin.eof())
 {
   fin.read((char *)&temp,sizeof(birddata));
   if(strcmpi(temp.birdname,B[n-1].birdname)==0)
     {
     }
   else
     {
      fout.write((char *)&temp,sizeof(birddata));
     }
 }
 fin.close();
 fout.close();
 remove("BNLIST");
 rename("TEMP","BNLIST");
 for(int i=(n-1);i<a;i++)
 {
   strcpy(B[n-1].birdname,B[n].birdname);
   B[n-1].cstatus=B[n].cstatus;
 }
 a--;
 clrscr();
 int gd=DETECT,gm;
	 initgraph(&gd,&gm,"C:\\TC\\bgi");
	 setcolor(BLUE);
	 settextstyle(TRIPLEX_FONT,0,2);
	 outtextxy(175,150,"DATA SUCCESSFULLY DELETED");
	 cout<<"\n\n\n\n\n\n\n\n\n\n\n                               Press any key.....";
 getch();
 cleardevice();
 closegraph();
 blist();
}
void profile(int &n)
	    {clrscr();
	     char lt[300],st[50];
	     int l,i,x,y,cl;
	     int gdriver=DETECT,gmode;
	     initgraph(&gdriver,&gmode,"C:\\TC\\bgi");
	     ifstream fin;
	     fin.open(B[n-1].birdname,ios::in);
	     if(!fin)cout<<"file not found";
	     fin.getline(st,50,'$');
	     setcolor(9);                //bird name color
	     settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
	     outtextxy(16,3,st);
	     fin.getline(lt,300,'$');
	     gotoxy(10,4);
	     cout<<lt;
	     fin.getline(st,50,'$');
	     gotoxy(2,8);
	     cout<<"Scientific Name :"<<st;
	     fin.getline(lt,300,'$');
	     gotoxy(2,9);
	     cout<<"Common Names    :";
	     l=strlen(lt);
	     for(i=0;i<l;i++)
	     {
	      cout<<lt[i];if(i==36)cout<<endl<<"                  ";
	     }
	     setcolor(8);
	     settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	     outtextxy(500,100,"PICTURE");
	     settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	     outtextxy(3,169,"IDENTIFICATION");
	     gotoxy(1,13);
	     fin.getline(lt,300,'$');
	     l=strlen(lt);
	     int m=1;
	     for(i=0;i<l;i++)
	     {
	      cout<<lt[i];if(i==(m*54)+(m-1)){cout<<endl;m++;}
	     }
	     settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	     outtextxy(3,279,"LIFE");
	     gotoxy(2,20);
	     fin.getline(lt,300,'$');
	     cout<<"HABITAT    : "<<lt;
	     fin.getline(lt,300,'$');
	     cout<<endl<<" FOOD       : "<<lt;
	     fin.getline(lt,300,'$');
	     cout<<endl<<" NESTING    : ";
	     l=strlen(lt);
	     for(i=0;i<l;i++)
	     {
	      cout<<lt[i];if(i==65)cout<<"             ";
	     }
	     fin.getline(lt,300,'$');
	     gotoxy(2,24);
	     cout<<"BEHAVIOUR  : ";
	     l=strlen(lt);
	     for(i=0;i<l;i++)
	     {
	      cout<<lt[i];if(i==65)cout<<"             ";
	     }
	     cout<<endl<<endl<<endl;
	     settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	     outtextxy(3,404,"CONSERVATION");
	     fin.getline(lt,300,'$');
	     cout<<" "<<lt;
	     setcolor(8);
	     settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	     outtextxy(440,230,"CONSERVATION STATUS");
	     fin.getline(st,50,'$');
	     l=strlen(st);
	     for(i=0;i<l;i++)
	     {
	     if(islower(st[i]))
	       {
		st[i]=st[i]-32;
	       }
	    }
	     if(strcmpi(st,"LEAST CONCERN")==0){setcolor(2);}
	     if(strcmpi(st,"VULNARABLE")==0){setcolor(6);}
	     if(strcmpi(st,"EXTINCT")==0){setcolor(4);}
	     if(strcmpi(st,"CONCERNED")==0){setcolor(YELLOW);}
	     if(strcmpi(st,"ISOLATED")==0){setcolor(3);}
	     settextstyle(SMALL_FONT,HORIZ_DIR,6);
	     outtextxy(470,265,st);
	     fin.close();
	     setcolor(8);
	     rectangle(-1,0,640,30); //bird name rectangle
	     rectangle(440,100,639,250); //appearence box
	     line(0,100,440,100);
	     line(0,170,440,170);
	     line(0,190,440,190);
	     line(0,280,440,280);
	     line(0,300,440,300);
	     line(0,405,639,405);
	     line(0,425,639,425);
	     rectangle(440,230,639,300);
	     setcolor(3);
	     circle(624,15,15);   //logo x>609&&x<639&&y>0&&y<30
	     circle(590,15,15);   // x>575&&x<605&&y>0&&y<30
	     circle(556,15,15);   // x>541&&x<571&&y>0&&y<30
	     callmouse();
		 do
		  {cl=0;
		   mouseposi(x,y,cl);
		   if(x>541&&x<571&&y>0&&y<30)
		     {if(cl==1)
			{cleardevice();
			 closegraph();
			 blist();
			}
		     }
		  if(x>575&&x<605&&y>0&&y<30)
		  {
		   if(cl==1)
		   { cleardevice();
		     closegraph();
		     edit(n);
		   }
		  }
		  if(x>609&&x<639&&y>0&&y<30)
		  {
		   if(cl==1)
		   { cleardevice();
		     closegraph();
		     mainmenu();
		   }
		  }
		  }while(!kbhit());
	     }
void edit(int t)
{clrscr();
 int i=1;
 cout<<i<<".Bird name"<<endl;i++;
 cout<<i<<".Short description about bird "<<endl;i++;
 cout<<i<<".Scientific name"<<endl;i++;
 cout<<i<<".Common names "<<endl;i++;
 cout<<i<<".Identification"<<endl;i++;
 cout<<i<<".Habitat "<<endl;i++;
 cout<<i<<".Food "<<endl;i++;
 cout<<i<<".Nesting "<<endl;i++;
 cout<<i<<".Behaviour "<<endl;i++;
 cout<<i<<".Conservation info"<<endl;i++;
 cout<<i<<".conservation status"<<endl;i++;
 cout<<"Choose from the above options what you want to edit : ";
 cin>>i;
 ifstream fin;
 fin.open(B[t-1].birdname,ios::in);
 ofstream fout;
 fout.open("TEMP",ios::out);
 char ch[300];int k=1;
 while(!fin.eof())
 {
   fin.getline(ch,300,'$');
   if(i==k)
     {
      cout<<"Previous data : "<<endl;
      cout<<ch<<endl<<endl<<"Enter the new data : "<<endl;
      gets(ch);
      fout<<ch<<'$';
      if(i==1)
	{
	 strcpy(B[t-1].birdname,ch);
	}
      if(i==11)
	 {
	  if(strcmpi(ch,"LEAST CONCERN")==0)B[t-1].cstatus=1;
	  else
	    {
	     if(strcmpi(ch,"CONCERNED")==0)B[t-1].cstatus=2;
	     else
	       {
		if(strcmpi(ch,"VULNERABLE")==0)B[t-1].cstatus=3;
		else
		  {
		   if(strcmpi(ch,"ISOLATED")==0)B[t-1].cstatus=4;
		   if(strcmpi(ch,"EXTINCT")==0)B[t-1].cstatus=5;
		  }
		}
	     }
	  }
     }
   else
     {
      fout<<ch<<'$';
     }
   k++;
 }
 fin.close();
 fout.close();
 remove(B[t-1].birdname);
 rename("TEMP",B[t-1].birdname);
 clrscr();
 int gd=DETECT,gm;
	 initgraph(&gd,&gm,"C:\\TC\\bgi");
	 setcolor(BLUE);
	 settextstyle(TRIPLEX_FONT,0,2);
	 outtextxy(175,150,"DATA SUCCESSFULLY EDITED");
	 cout<<"\n\n\n\n\n\n\n\n\n\n\n                               Press any key.....";
 getch();
 cleardevice();
 closegraph();
 profile(t);
 }
void main()
{clrscr();
 assign();
}