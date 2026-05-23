#include <graphics.h>
#include <conio.h>
#include <iostream.h>
#include <math.h>
#include <dos.h>

// ---------------- DDA LINE ----------------
void ddaLine(int x1,int y1,int x2,int y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float steps;
    if(fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);

    float xinc = dx / steps;
    float yinc = dy / steps;
    float x = x1, y = y1;

    for(int i=0;i<=steps;i++)
    {
        putpixel((int)(x+0.5),(int)(y+0.5),WHITE);
        x += xinc;
        y += yinc;
        delay(5);
    }
}

// ---------------- BRESENHAM LINE ----------------
void bresenhamLine(int x1,int y1,int x2,int y2)
{
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while(1)
    {
        putpixel(x1,y1,WHITE);
        if(x1==x2 && y1==y2) break;

        int e2 = 2*err;
        if(e2 > -dy) { err -= dy; x1 += sx; }
        if(e2 < dx)  { err += dx; y1 += sy; }
        delay(5);
    }
}

// ---------------- MIDPOINT CIRCLE ----------------
void midpointCircle(int xc,int yc,int r)
{
    int x=0, y=r;
    int p=1-r;

    while(x<=y)
    {
        putpixel(xc+x,yc+y,WHITE);
        putpixel(xc-x,yc+y,WHITE);
        putpixel(xc+x,yc-y,WHITE);
        putpixel(xc-x,yc-y,WHITE);
        putpixel(xc+y,yc+x,WHITE);
        putpixel(xc-y,yc+x,WHITE);
        putpixel(xc+y,yc-x,WHITE);
        putpixel(xc-y,yc-x,WHITE);

        if(p<0)
            p += 2*x + 3;
        else
        {
            p += 2*(x-y) + 5;
            y--;
        }
        x++;
        delay(5);
    }
}

// ---------------- BRESENHAM CIRCLE ----------------
void bresenhamCircle(int xc,int yc,int r)
{
    int x=0, y=r;
    int d = 3 - 2*r;

    while(x<=y)
    {
        putpixel(xc+x,yc+y,WHITE);
        putpixel(xc-x,yc+y,WHITE);
        putpixel(xc+x,yc-y,WHITE);
        putpixel(xc-x,yc-y,WHITE);
        putpixel(xc+y,yc+x,WHITE);
        putpixel(xc-y,yc+x,WHITE);
        putpixel(xc+y,yc-x,WHITE);
        putpixel(xc-y,yc-x,WHITE);

        if(d < 0)
            d = d + 4*x + 6;
        else
        {
            d = d + 4*(x-y) + 10;
            y--;
        }
        x++;
        delay(5);
    }
}

// ---------------- ELLIPSE ----------------
    
void drawEllipseAlgo(int xc, int yc, int rx, int ry)
{
    int x = 0;
    int y = ry;

    // Decision parameter for region 1
    long long rx2 = (long long)rx * rx;
    long long ry2 = (long long)ry * ry;
    long long two_rx2 = 2 * rx2;
    long long two_ry2 = 2 * ry2;

    long long px = 0;
    long long py = two_rx2 * y;

    // Region 1
    long long p1 = ry2 - (rx2 * ry) + (rx2 / 4);
    while (px < py)
    {
        // Plot all 4 symmetric points
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);

        x++;
        px += two_ry2;

        if (p1 < 0)
            p1 += ry2 + px;
        else
        {
            y--;
            py -= two_rx2;
            p1 += ry2 + px - py;
        }
        delay(5);
    }

    // Region 2
    long long p2 = (long long)(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);
    while (y >= 0)
    {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);

        y--;
        py -= two_rx2;

        if (p2 > 0)
            p2 += rx2 - py;
        else
        {
            x++;
            px += two_ry2;
            p2 += rx2 - py + px;
        }
        delay(5);
    }
}


// ---------------- RECTANGLE ----------------
void drawRectangleAlgo(int x1,int y1,int x2,int y2)
{
    rectangle(x1,y1,x2,y2);
}

// ---------------- TRIANGLE ----------------
void drawTriangleAlgo(int x1,int y1,int x2,int y2,int x3,int y3)
{
    line(x1,y1,x2,y2);
    line(x2,y2,x3,y3);
    line(x3,y3,x1,y1);
}

// ---------------- MAIN ----------------
int main()
{
    int gd=DETECT, gm;
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

    int choice;
    do
    {
        cleardevice();
        cout<<"\n----MENU ----";
        cout<<"\n1. Line";
        cout<<"\n2. Circle";
        cout<<"\n3. Ellipse";
        cout<<"\n4. Rectangle";
        cout<<"\n5. Triangle";
        cout<<"\n6. Exit";
        cout<<"\nEnter choice: ";
        cin>>choice;

        if(choice==1)
        {
            int op,x1,y1,x2,y2;
            cout<<"\n1.DDA  2.Bresenham : ";
            cin>>op;
            cout<<"Enter x1 y1 x2 y2: ";
            cin>>x1>>y1>>x2>>y2;
            if(op==1) ddaLine(x1,y1,x2,y2);
            else bresenhamLine(x1,y1,x2,y2);
            getch();
        }
        else if(choice==2)
        {
            int op,xc,yc,r;
            cout<<"\n1.Bresenham Circle  2.Midpoint Circle : ";
            cin>>op;
            cout<<"Enter center (xc yc) and radius: ";
            cin>>xc>>yc>>r;

            if(op==1) bresenhamCircle(xc,yc,r);
            else midpointCircle(xc,yc,r);

            getch();
        }
        else if(choice==3)
        {
            int xc, yc, rx, ry;
            cout<<"Enter center (xc yc) and rx ry: ";
            cin>>xc>>yc>>rx>>ry;
            drawEllipseAlgo(xc, yc, rx, ry);
            getch();
        }

        else if(choice==4)
        {
            int x1,y1,x2,y2;
            cout<<"Enter rectangle corners (x1,y1,x2,y2): ";
            cin>>x1>>y1>>x2>>y2;
            drawRectangleAlgo(x1,y1,x2,y2);
            getch();
        }
        else if(choice==5)
        {
            int x1,y1,x2,y2,x3,y3;
            cout<<"Enter triangle points(x1,y1,x2,y2,x3,y3): ";
            cin>>x1>>y1>>x2>>y2>>x3>>y3;
            drawTriangleAlgo(x1,y1,x2,y2,x3,y3);
            getch();
        }

    }while(choice!=6);

    closegraph();
    return 0;
}
