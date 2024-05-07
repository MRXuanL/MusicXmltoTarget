#include<string>
using namespace std;
class Note{
    public:
        Note(int s=0,int f=0,double t=0,double d=0):str(s),fret(f),time(t),duration(d){};
        void set(int s=0,int f=0,double t=0,double d=0){
            str=s;
            fret=f;
            time=t;
            duration=d;   
        }
        int str;
        int fret;
        double time;
        double duration;
};