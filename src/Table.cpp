#include <iostream>
#include "tinyxml2.h"
#include "Table.h"
using namespace tinyxml2;
using namespace std;

Table::Table(string &filename){
    XMLDocument doc;
    _name=filename;
    makexmlcorrect(filename);
    if(doc.LoadFile(filename.c_str())==XML_SUCCESS) 
    {
        double time=0.0;
        XMLElement* root=doc.FirstChildElement("score-partwise");
        //获取part元素，也就是整个吉他谱
        XMLElement* work=root->FirstChildElement("work");
        if(work){
            XMLElement* worktitle=work->FirstChildElement("work-title");
            if(worktitle){
                _name=worktitle->GetText();
            }
        }
        XMLElement* part=root->FirstChildElement("part");
        if(part){
            XMLElement* measure=part->FirstChildElement("measure");
            while(measure){
                XMLElement* division=0;
                XMLElement* attributes=measure->FirstChildElement("attributes");
                if(attributes) division=attributes->FirstChildElement("divisions");
                //寻找分割
                if(division){
                    _division=division->IntText();
                }
                XMLElement* direction=measure->FirstChildElement("direction");
                //寻找tempo
                if(direction){
                    XMLElement* directiontype=direction->FirstChildElement("direction-type");
                    if(directiontype){
                        XMLElement* metronome=directiontype->FirstChildElement("metronome");
                        if(metronome){
                            XMLElement* perminute=metronome->FirstChildElement("per-minute");
                            if(perminute){
                                _tempo=perminute->IntText();
                            }
                        }
                    }
                }
                _dt=60.0/_tempo;
                XMLElement* note=measure->FirstChildElement("note");

                while(note){
                    XMLElement* staff=note->FirstChildElement("staff");
                    if(staff){
                        int row=staff->IntText();
                        if(row!=1){
                            Note n=processnote(note);
                            if(n.duration!=-1) _notelist.push_back(n);
                        }
                    }
                    note=note->NextSiblingElement("note");
                }
                measure=measure->NextSiblingElement("measure");
            }
        }
        
        
        
    }
    _notenum=_notelist.size();
}
Note Table::processnote(XMLElement *note){
    int string=-1,fret=-1;
    double duration=-1,add=0;
    XMLElement* chord=note->FirstChildElement("chord");
    XMLElement* notations=note->FirstChildElement("notations");
    if(notations){
        XMLElement* technical=notations->FirstChildElement("technical");
        if(technical){
            XMLElement* root=technical->FirstChildElement("root");
            if(root){
                XMLElement* str=root->FirstChildElement("string");
                if(str) string=str->IntText();
                XMLElement* fre=root->FirstChildElement("fret");
                if(fre) fret=fre->IntText();

            }
            else{
                XMLElement* str=technical->FirstChildElement("string");
                if(str) string=str->IntText();
                XMLElement* fre=technical->FirstChildElement("fret");
                if(fre) fret=fre->IntText();
            }
        }
    }
    int dur=-1;
    XMLElement* dura=note->FirstChildElement("duration");
    //当上一个是chord时，且这一个不是chord时，time+=_add
    if(dura){
        dur=dura->IntText();
        duration=(1.0*dur/_division)*_dt;
        _add=duration;
    }
    Note n;
    if(chord) n.set(string,fret,_lasttime,duration);
    else {
        n.set(string,fret,_time,duration);
        _lasttime=_time;
        _time+=_add;
    }
    
    return n;
}
void Table::output(ostream &os){
    os<<_name<<endl;
    for(int i=0;i<_notenum;i++){
        const Note &n=_notelist[i];
        os<<n.str<<" "<<n.fret<<" "<<n.time<<" "<<n.duration<<endl;
    }
}


void Table::makexmlcorrect(string &filename){
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    string line;
    ofstream tempFile("temp.txt"); // 创建临时文件
    string searchString1="<?GP";
    string searchString2="?>";
    int num=0;
    while (getline(inputFile, line)) {
        size_t pos = line.find(searchString1);
        if (pos != std::string::npos) {
            // 如果找到了匹配的字符串，删除该字符串
            line.erase(pos, searchString1.length());
        }
        pos = line.find(searchString2);
        if (pos != std::string::npos) {
            // 如果找到了匹配的字符串，删除该字符串
            if(num!=0) line.erase(pos, searchString2.length());
            num++;
        }
        // 将处理后的行写入临时文件
        tempFile << line << std::endl;
    }

    // 关闭文件流
    inputFile.close();
    tempFile.close();

    // 删除原文件
    remove(filename.c_str());

    // 重命名临时文件为原文件名
    rename("temp.txt", filename.c_str());
}

