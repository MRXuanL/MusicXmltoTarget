#include <fstream>
#include <string>
#include <vector>
#include "tinyxml2.h"
#include "Note.h"
using namespace tinyxml2;
using namespace std;
class Table{
    public:
        Table(string &filename);
        Note processnote(XMLElement *note);
        void output(ostream &os=cout);
        void makexmlcorrect(string &filename);
    private:
        string _name;
        int _tempo;
        double _time=0;
        int _division;
        int _notenum=0;
        double _add=0;
        double _lasttime=0;
        double _dt;
        double _measureStartTime;
        int _curVoice=0;
        vector<Note>_notelist;
};