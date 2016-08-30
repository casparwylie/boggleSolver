//
//  main.cpp
//  Eyes
//
//  Created by Caspar Wylie on 28/07/16.
//  Copyright (c) 2016 Caspar Wylie. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <unistd.h>


using namespace std;

vector<string> getNextTo(int x, int y){
    
    vector<string> zero(1);
    zero[0] = "0";
    
    if(x<=3&&y<=3){
        vector<string> data(8);
        
        bool xAdd = true;
        bool yAdd = true;
        bool xMin = true;
        bool yMin = true;
        
        if(x==3){
            xAdd = false;
        }else if(x==0){
            xMin = false;
        }
        
        if(y==3){
            yAdd = false;
        }else if(y==0){
            yMin = false;
        }
        
        data[0] = (xMin&&yMin)? to_string(x-1)+to_string(y-1): "0";
        data[1] = (xAdd&&yAdd)? to_string(x+1)+to_string(y+1): "0";
        data[2] = (xAdd&&yMin)? to_string(x+1)+to_string(y-1): "0";
        data[3] = (xMin&&yAdd)? to_string(x-1)+to_string(y+1): "0";
        data[4] = (yMin)? to_string(x)+to_string(y-1): "0";
        data[5] = (yAdd)? to_string(x)+to_string(y+1): "0";
        data[6] = (xAdd)? to_string(x+1)+to_string(y): "0";
        data[7] = (xMin)? to_string(x-1)+to_string(y): "0";
        
        return data;
    }else{
        return zero;
    }
}

void outputSquare(vector< vector<string> > letters){
    for(int i = 0;i<4;i++){
        for(int x = 0;x<4;x++){
            cout << letters[i][x] << " ";
        }
        cout << endl;
    }
}


bool isFirstUpper(string word) {
    return word.size() && isupper(word[0]);
}

int main(int argc, const char * argv[]) {
    
    
    vector< vector<string> > letters(4,vector<string>(4));
    
    for(int i = 0;i<4;i++){
        string row;
        string outputText ="enter row " + to_string(i+1) + ", with spaces: ";
        cout << outputText;
        getline(cin,row, '\n');
        istringstream iss(row, istringstream::in);
        int count = 0;
        string chars;
        while(iss >> chars){
            letters[i][count] = chars;
            count++;
        }

    }
    
    cout << "-----" << endl;
    
    vector<string> words;
    vector<string> success;
    
    int y = 0;
    int x = 0;
    for(int place = 0;place<16;place++){
        
        if(place>1&&place%4==0){
            x++;
        }
        y++;
        if(y==4){
            y = 0;
        }
        
        string xySTR = to_string(x) + to_string(y);
        words.push_back(xySTR);
        
    }
    
    for(int x = 0;x<words.size();x++){
        string latestLetter = words[x].substr(words[x].length()-2, 2);
        int x_ = stoi(latestLetter.substr(0,1));
        int y = stoi(latestLetter.substr(1,1));
        
        
        vector<string> nextToList = getNextTo(x_,y);
        for(int i = 0;i<nextToList.size();i++){
            if(nextToList[i]!="0"){
                string nextChar = nextToList[i];
                
                words.push_back(words[x] + " " + nextChar);
                string coords = words[x];
                
                istringstream iss(coords, istringstream::in);
                string singCoord;
                string compWord  = "";
                vector<string> singCoordCountUnique;
                vector<int> singCoordCount;
                bool allowWord = true;
                while(iss >> singCoord){
                    
                    for(int check = 0;check<singCoordCountUnique.size();check++){
                        if(singCoordCountUnique[check]==singCoord){
                            allowWord = false;
                        }
                    }
                    int x = stoi(singCoord.substr(0,1));
                    int y = stoi(singCoord.substr(1,1));
                    compWord = compWord + letters[x][y];
                    singCoordCountUnique.push_back(singCoord);
                    
                }
                
                
                string firstLetters;
                string compWordLen = to_string(compWord.length());
                firstLetters = compWord.substr(0,3);
                string fPath = "9words4/"+compWordLen+firstLetters+"words.txt";
       
                ifstream file(fPath);
                string str;
                
      
                while (getline(file, str)) {
                    
                    
                    //cout << "if " << compWord << "==" << str << endl;
                    
                    if(isFirstUpper(str)==0){
                        if(compWord==str&&allowWord==true){
                            bool defNew = true;
                            for(int checkRep = 0;checkRep<success.size();checkRep++){
                                if(success[checkRep]==str){
                                    defNew = false;
                                }
                            }
                            if(defNew==true&&str.length()>=4){
                                success.push_back(str);
                                cout << str << ", ";
                                cout.flush();
                            }
                            
                        }
                    }
                }
                file.close();
                
            }
        }
    }
}
