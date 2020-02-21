#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<list>
#include<windows.h>
using namespace std;
int width=0,hight=0;
void gotothere(int x,int y,char z)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(handle,coord);
    cout<<z<<endl;
};
char getchar (int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    TCHAR a[1];
    CONSOLE_SCREEN_BUFFER_INFO csbiinfo;
    GetConsoleScreenBufferInfo(handle, &csbiinfo);
    COORD coord;
    coord.X=x;
    coord.Y=y;
    DWORD dwchars;
    ReadConsoleOutputCharacter(handle,a,1,coord,&dwchars);
    return a[0];
}
class food
{
    public:
    food ();
    friend class snack;
    void created();
    private:
    static int foodx,foody;
};
int food::foodx=0;
int food::foody=0;
food::food()
{
    gotothere(width/4,hight/4,'@');
}
void food::created()
{
    int mark=0;
    while(mark==0)
    {
        srand(time(NULL));
        foodx=rand() % (width-1)+1;
        foody=rand() % (hight-1)+1;
        char a=getchar(foodx,foody);
        if(a=='$')
        {
            mark=0;
        }
        else
        mark=1;
    }
    gotothere(foodx,foody,'@');
};
class map
{
    public:
    map();
};
map::map()
{
    for(int i=0;i<width+1;i++)
    {
        for (int j=0; j < hight+1; j++)
        {
            if(i==0||i==width||j==0||j==hight)
            {
                gotothere(i,j,'$');
            }
        }
        
    }
};
class snack
{
    public:
        snack();
        list<int> frontsnack();
        int whatiffrontsnack(list<int> front);
        void movesnack();
        void printfsnack(list<list<int>> everysnack);
    private:
        static list <list<int>> everysnack;
        static char direction;
};
list<list<int>> snack::everysnack;
char snack::direction='s';
snack::snack()
{   
    for(int i=0;i<5;i++)
    {
        list<int> temp;
        temp.push_back(width/2+i);
        temp.push_back(hight/2);
        everysnack.push_back(temp);
    }   
    printfsnack(everysnack);
}
void snack::printfsnack(list<list<int>> everysnack)
{
    list<list<int>>::iterator iterb =everysnack.begin();           //set the outside list iteraor
    list<int> temphead=*iterb;                                         //set the inbside iterator
    list<int>::iterator iters1=temphead.begin();
    list<int>:: iterator iters2=temphead.begin();                        
    gotothere(*iters1,*(++iters2),'@');
    iterb++;
    for(int i=0;i<everysnack.size()-1;i++) 
    {
        list<int> tempbody=*iterb;
        list<int>::iterator iters1=tempbody.begin();
        list<int>::iterator iters2=tempbody.begin(); 
        gotothere(*iters1,*(++iters2),'$');
        iterb++;
    }
};
list<int> snack::frontsnack()
{
    list<list<int>>::iterator iterb =everysnack.begin();           //set the outside list iteraor
    list<int> temphead=*iterb;                                         //set the inbside iterator
    list<int>::iterator iters1=temphead.begin();
    list<int>::iterator iters2=temphead.begin();
    list<int> temp;
    if(_kbhit())
    {
        fflush(stdin);
        char getchar=getch();
        switch (getchar)
        {
        case 'w':
            if(direction=='s')
            {direction='s';}
            else
            direction='w';
            break;
        case 'a':
            if(direction=='d')
            {direction='d';}
            else
            direction='a';
            break;
        case 's':
            if(direction=='w')
            {direction='w';}
            else
            direction='s';
            break;
        case 'd':
            if(direction=='a')
            {direction='a';}
            else
            direction='d';
            break;
        }
    }
    switch (direction)
    {
        
        case 'w':
        temp.push_back(*iters1);
        temp.push_back(*(++iters2)-1);
        break;
        case 'a':
        temp.push_back(*iters1-1);
        temp.push_back(*(++iters2));
        break;
        case 's':
        temp.push_back(*iters1);
        temp.push_back(*(++iters2)+1);
        break;
        case 'd':
        temp.push_back(*iters1+1);
        temp.push_back(*(++iters2));
        break;
    }
    return temp;
};  
int snack::whatiffrontsnack(list<int> front)
{
    list<int>::iterator a=front.begin();
    list<int>::iterator b=front.begin();
    char i=getchar(*a,*(++b));
    if(i=='$')
    {
        return 1;
    }
    if(i=='@')
    {
        return 2;
    }
    return 0; 
}
void snack::movesnack()
{
    int decide=0;
    food foods;
    while(decide!=1)
    {
        Sleep(300);
        list<int> front=frontsnack();
        decide=whatiffrontsnack(front);
        if(decide==2)
        {
            everysnack.push_front(front);
            printfsnack(everysnack);
            foods.created();
        }
        if(decide==0)
        {
            everysnack.push_front(front);
            list<int> temp=everysnack.back();
            list<int>::iterator iters1=temp.begin();
            list<int>::iterator iters2=temp.begin();
            gotothere(*iters1,*(++iters2),' ');
            everysnack.pop_back();
            printfsnack(everysnack);
        }
    }
    cout<<"lose"<<endl;
}
int main()
{   
    width=50;
    hight=25;
    map map;
    snack snack;
    snack.movesnack();
    system("pause");
    return 0;
}