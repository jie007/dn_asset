#include <iostream>
#include<Windows.h>
#include<time.h>
#include<string>

using namespace std;

typedef void(*CB)(const char*);
typedef void(*DllCommand)(CB);
typedef void(*DllInitial)(char*,char*);
typedef int(*DllAdd)(int,int);
typedef int(*DllSub)(int*,int*);
typedef void(*DllReadQteTable)();
typedef void(*DllReadSuitTable)();
DllCommand cb;
DllInitial init;
DllAdd add;
DllSub sub;
DllReadQteTable qte;
DllReadSuitTable suit;


void DebugInfo()
{
	cout<<"********* op *********"<<endl;
	cout<<"** a stands for Add **"<<endl;
	cout<<"** s stands for Sub **"<<endl;
	cout<<"** t stands for Read *"<<endl;
	cout<<"** q stands for Quit *"<<endl;
	cout<<"** input your command:";
}

bool CheckIn()
{
	if(cin.fail()) 
	{
		cin.clear();  //���fail״̬	
		cin.sync();   //���������
		cout<<"input format error"<<endl<<endl;
		return false;
	}
	return true;
}

void EAdd()
{
	int a,b,c;
	cout<<"input a:";
	cin>>a;
	if(!CheckIn()) return;
	cout<<"input b:";
	cin>>b;
	if(!CheckIn()) return;
	c=add(a,b);
	cout<<"add result:"<<c<<endl<<endl;
}

void ESub()
{
	int a,b,c;
	cout<<"input a:";
	cin>>a;
	if(!CheckIn()) return;
	cout<<"input b:";
	cin>>b;
	if(!CheckIn()) return;
	c=sub(&a,&b);
	cout<<"add result:"<<c<<endl<<endl;
}

void ERead()
{
	qte();
	cout<<endl;
	suit();
	cout<<endl<<endl;
}

void OnCallback(const char* command)
{
	cout<<"> "<<command<<endl;
}

void main()
{
	cout<<"**********  main **********"<<endl;
	HINSTANCE hInst = LoadLibrary("XTable.dll");
	if(hInst==NULL)
	{
		cout<<"hInst is null"<<endl;
		return;
	}
	cout<<"load library succ"<<endl;
	cb = (DllCommand)GetProcAddress(hInst,"iInitCallbackCommand");
	init = (DllInitial)GetProcAddress(hInst,"iInitial");
	add = (DllAdd)GetProcAddress(hInst,"iAdd");
	sub = (DllSub)GetProcAddress(hInst,"iSub");
	qte = (DllReadQteTable)GetProcAddress(hInst,"iReadQteStatusList");
	suit = (DllReadSuitTable)GetProcAddress(hInst,"iReadEquipSuitList");
	cb(OnCallback);
	init("","");

	while(true)
	{
		DebugInfo();
		char input;
		cin>>input;
		bool jump =false;
		switch(input)
		{
			case 'a':
				EAdd();
				break;
			case 's':
				ESub();
				break;
			case 't':
				ERead();
				break;
			case 'q':
				jump = true;
				break;
			default:
				cout<<"invalid command"<<endl<<endl;
		}
		if(jump)
			break;
	}
	
	FreeLibrary(hInst);
	system("pause");
}