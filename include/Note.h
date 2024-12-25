#include<string>
#include<cmath>
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
        bool operator<(const Note &other)const{
            if(abs(this->time-other.time)>0.0001) return this->time<other.time;
            return this->str>other.str;
        }

        bool operator==(const Note &other)const{
            return abs(this->time-other.time)<0.0001
            &&abs(this->duration-other.duration)<0.0001
            &&this->str==other.str&&this->fret==other.fret;
        }

        bool operator!=(const Note &other)const{
            return !(*this==other);
        }
        int str;
        int fret;
        double time;
        double duration;
};