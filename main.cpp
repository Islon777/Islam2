#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <windows.h>
using namespace std;


int main(){

//  ���������� ����� �� txt ����� � ������ ����� � ������
    string str;
    vector<string> data;
    ifstream F;
    F.open("C:\\Users\\Islam_01\\Desktop\\Crypton\\Ex\\example.txt", ios::in); // �� ������ ������� ���� ���� � �����!!!
    if(F)
    {
        while(getline(F, str))
            {
            data.push_back(str);
            }
    } else
    {
      cout<<"File no found"<<endl;
    }
    F.close();

    // �������� ����������� ����������
    vector<string> person;              // ���
    vector<int> reqInHour;              // �������� � ���
    vector<int> hours;                  // �����
    vector<int> total;                  // ����� ����� ��������
    vector<string> adInf;               // ��� ����

    // ���������� ���������
    vector<string> buf_str;
    for (int i = 0; i < data.size();i++)
    {
        buf_str.clear();
        stringstream StrSt(data[i]);
        while(getline(StrSt, str,' '))
         {
            buf_str.push_back(str);

         }
        int reqInTime = atoi(buf_str[1].c_str());
        int hour = atoi(buf_str[2].c_str());
        if (i == 0){ // ������ ��� � ��� ������ ������������ �����
            person.push_back(buf_str[0]);
            reqInHour.push_back(reqInTime);
            hours.push_back(hour);
            total.push_back(reqInTime*hour);
            adInf.push_back(buf_str[3]);
        } else { // ����������� ������ ��������������
            for (int k = 0; k < person.size(); k++){
                if (person[k] == buf_str[0]) // ����� ���������������� ����� � ���������� ������ ��� �������� ������
                {
                    reqInHour[k] = reqInHour[k] + reqInTime;
                    hours[k] = hours[k] + hour;
                    total[k] = total[k] + reqInTime*hour;
                    adInf[k] = buf_str[3];
                    break;
                } else {
                    if (k == person.size()-1){ // ���������� ������ �����
                        person.push_back(buf_str[0]);
                        reqInHour.push_back(reqInTime);
                        hours.push_back(hour);
                        total.push_back(reqInTime*hour);
                        adInf.push_back(buf_str[3]);
                        break;
                    }
                }
            }
        }
    }
    // ���������� �� ��������
    for(int i = 0 ; i < person.size(); i++){
       for(int j = i+1; j < person.size(); j++)
             if(strcmp(person[i].c_str(), person[j].c_str()) > 0){
                 string tmp = person[i];
                 person[i] = person[j];
                 person[j] = tmp;
                 tmp = adInf[i];
                 adInf[i] = adInf[j];
                 adInf[j] = tmp;
                 int tmp1 = reqInHour[i];
                 reqInHour[i] = reqInHour[j];
                 reqInHour[j] = tmp1;
                 tmp1 = hours[i];
                 hours[i] = hours[j];
                 hours[j] = tmp1;
                 tmp1 = total[i];
                 total[i] = total[j];
                 total[j] = tmp1;
             }
    }

    // ����� ���������� � ����
    ofstream F2;
    string s1;
    F2.open("C:\\Users\\Islam_01\\Desktop\\Crypton\\Ex\\sorted.txt",ios::out);  // �� ������ ������� ���� ���� � �����!!!
    stringstream Str;
    for (int i = 0; i < person.size();i++ ){
        Str << person[i]<< " "<< reqInHour[i]<<" "<<hours[i]<<" "<<total[i]<<" "<<adInf[i]<< "\n";
        s1 = Str.str();
        F2 << s1;
        Str.str("");

    }
    F2.close();
    if (!F2.is_open()){
        cout << "Finished";
    }
    return 0;
}
