#include <iostream>
#include <algorithm>
#include<stdlib.h>
#include<stack>

using namespace std;

struct Point{
        int x,y;
    };

class Graham_Scan
{
    
    Point List[100];
    static int n;
    static Point p0;
    Point Find_min_point()
    {
        Point aux;
        int min = 100000000;
        int min_point;
        for(int i = 0;i < n; i++)
        {
            if(List[i].y < min)
            {
                min = List[i].y;
                min_point = i;
            }

        }

        aux = List[0];
        List[0] = List[min_point];
        List[min_point] = aux; 
    }


public:
    Graham_Scan()
    {
        n = 0;
    }

    Graham_Scan(Point point[],int x)
    {
        for(int i = 0; i < x; i++)
        {
            List[n].x = point[i].x;
            List[n].y = point[i].y;
            n++;
        }
    }

    static  int distance(Point p1, Point p2) 
    { 
        return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y); 
    } 
    


    static  int lessthan(Point p, Point q, Point r) 
    { 
        int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
  
        if (val == 0) 
            return 0;  
        else if (val > 0)
            return 1;
        else return 2;
    }  

    static int Compare_points(const void *vp1, const void *vp2)
    {
        Point *p1 = (Point *)vp1; 
        Point *p2 = (Point *)vp2; 
        int o = lessthan(p0, *p1, *p2); 
        if (o == 0) 
            if (distance(p0, *p2) >= distance(p0, *p1))
                return 0;
            else 
                return  1; 
  
        if (o == 2)
            return 0;
        else
            return 1; 
    }

    void Print_points()
    {
        for(int i = 0; i < n; i++)
            cout<<List[i].x<<" "<<List[i].y<<endl;
    }

    void Find_hull()
    {
        Find_min_point();
        p0 = List[0];
        qsort(&List[1], n-1, sizeof(Point), Compare_points);
        Hull();
        
    }

    void Hull()
    {
        int m;
        Point Final[100];
        for(int i = 0;i <= 2; i++)
            Final[i] = List[i];
        
        m = 2;
        for(int i = 3;i < n ;i++)
        {

            while(lessthan(Final[m-1], Final[m], List[i]) != 2)
                m--;
            m++;
            Final[m] = List[i]; 
        }
        for(int i = 0; i <= m ;i++)
            cout<<Final[i].x<<" "<<Final[i].y<<endl;
    }
    void Add_point(Point p)
    {
        List[n].x = p.x;
        List[n].y = p.y;
        n++;
    }
    void delete_point(Point p)
    {

        int i; 
        for (i=0; i<n; i++) 
            if (List[i].x == p.x && List[i].y == p.y)  
                break; 
  
        if (i < n) 
        { 
            n = n - 1; 
            for (int j=i; j<n; j++) 
                List[j] = List[j+1]; 
        } 
    }
};

int Graham_Scan::n = 0;
Point Graham_Scan::p0 = {0,0};

int main()
{
    Point points[10] = {{2,10},{3,15},{10,5},{2,6},{5,1},{12,4},{8,9}};
    Graham_Scan A(points,7);
    A.Find_hull();
}