#include <iostream>
#include<stdio.h>
#include <string>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include<map>
#include <dirent.h>
#include <algorithm> 
#include <cctype>
#include <locale>
#include<iterator>
#include<string.h>
#include<sstream>
#include<fstream>
#include<vector>


using namespace std;

map<string, int> FNO_IOC;
map<string, int> FNO_BID;
map<string, int> CD_IOC;
map<string, int> CD_BID;
map<int, string> strategy;
map<int ,string> findiocser;
map<int ,string> findbidser;
map<int ,string> findcdser;
char* path_ioc=(char*) "/home/chandan/pankaj/TEST/IOC.txt";
char* path_bid=(char*) "/home/chandan/pankaj/TEST/BID.txt";
char* path_cdi=(char*) "/home/chandan/pankaj/TEST/CD.txt";
char* path_cdb=(char*) "/home/chandan/pankaj/TEST/CD_BD.txt";
char* path_strategy=(char*) "/home/chandan/pankaj/TEST/strategy.txt";
char* path_iocserver=(char*) "/home/chandan/pankaj/TEST/iocserver.txt";
char* path_bidserver=(char*) "/home/chandan/pankaj/TEST/bidserver.txt";
char* path_cdserver=(char*) "/home/chandan/pankaj/TEST/cdserver.txt";

string backuppath;
string date_format;
string segment;
string subsegment;

class fileprocess
{	
    public :	
	string serIp;
	int flag;
	string sDirectory;
	fileprocess()
	{
		sDirectory="";
		flag=0;
		serIp="";		
		//cout<<backuppath<<"|"<<date_format<<"|"<<segment<<"|"<<subsegment<<"|"<<endl;
	}
	void filereaddir()
	{
		sDirectory=backuppath;
		DIR *dir;
        struct dirent *ent;
		cout<<"Opening dir: "<<sDirectory<<endl<<endl<<endl;;
		if ((dir = opendir(sDirectory.c_str())) != NULL)
        {
			while ((ent = readdir (dir)) != NULL)
            {
				if((strcmp(ent->d_name,".")==0) ||(strcmp(ent->d_name,"..")==0 )) continue;
				int len = strlen(ent->d_name);
				cout<<"Opening dir: "<<ent->d_name<<endl<<endl<<endl<<endl;;
				//cout<<ent->d_name<<endl;
				int n = 0;
                for(int i=0; i<len; i++)
                {
                    if(ent->d_name[i] == '.')
                    {
                        flag=1;
                        break;
                    }
					n=i;
                }
				 if(flag!=1)
                {
					
                    string str(ent->d_name, n+1);
                    int x = atoi(str.c_str());
					serIp=findserverIP(x);	
						if(serIp=="")continue;
					cout<<"Checking for Server 192.168.100."+serIp<<endl<<endl;;
						//cout<<serIp<<"IP"<<endl;
				//	cout<<sDirectory + "/" + str.c_str()+"Backup"+date_format+"_"+str.c_str()<<"||"<<serIp<<endl;
					openningfile(sDirectory + "/" + str.c_str()+"/Backup"+date_format+"_"+str.c_str());			   
                }
				
			}
			 closedir (dir);
		}
		
	}
	
	string findserverIP(int x)
	{
		//cout<<x<<"Hello";
		int s=x;
		string sIP="";
		map<int,string>::iterator it;
		if(segment=="FNO"&&subsegment=="IOC")
		{
				it=findiocser.find(s);
				if( it!= findiocser.end())
				{
				sIP=it->second;
				return sIP;
				}
				else
				{
				return sIP;		
				}
		}
			else if(segment=="FNO"&&subsegment=="BID")
			{
				it=findbidser.find(s);
				if( it!= findbidser.end())
				{	
				sIP=it->second;
				return sIP;
				}			
				else
				{
				return sIP;		
				}
			}
				else if(segment=="CD")
				{
					it=findcdser.find(s);
					if( it!= findcdser.end())
					{
					sIP=it->second;
					return sIP;
					}
					else
						{
					return sIP;		
						}
				}		
					else
						cout<<"Segment Error"<<endl;
	}
 void openningfile(std::string path)
{	
	//cout<<path<<endl;
	string dirpath=path;
	string filepath="";
		//for(int i=0;i<4;i++)
		{
			//string out_string;
			//std::stringstream ss;
			//ss >> i;
			//out_string = ss.str();
			filepath=path+"/FO_IntOrd_0";
			Read_file(filepath);
			if(segment=="CM")
			{
				filepath=path+"/CM_IntOrd_0";
				Read_file(filepath);
			}
		}
			
	/*std::string chnagedir;   
    chnagedir=sDirectory;
    //cin.get();     
	int chdir_return_value = chdir(sDirectory.c_str());
    return chdir_return_value;*/

}

void Read_file(string filepath)///1 arg not define
	{
		map<int,string> algtag;
		//cout<<filepath<<endl;
		algtag.clear();
		string mfile=filepath;
		char* b_path = strdup(mfile.c_str());		
		int AlgoId=1;
		int OldAlgoID=1;
		int flag=0;	
		string 	TagId="";
		char* fileRead = b_path;		
		ifstream file1(fileRead);
		string str1;
		vector<string> v(2);	
if(file1.is_open())
{	
		 while(file1)
		 {			
			 if (!getline(file1, str1 )) break;
			 istringstream ss(str1);
			 v.clear();
			 int check=0,count=0;
			 while(ss)
                    {
                        string s1;
                        if(!getline( ss, s1, '|' ) )
                        {
                            break;
                        }
						
						if(check==1)
						{
							v[0]=s1;
							check=0;
						//	v.push_back(s1);count++;check=0;							
		
						}
						if(check==2)
							{
							v[1]=s1;
							check=0;
							}
						
						if(s1=="FNO"||s1=="CM")
							check=1;
						if(s1=="STP")
							check=2;
					//if(count>2){ v.clear(); v.push_back(s1);check=0;count=1;}
					
			}			
				//if(flag!=1)
{
				TagId=v[0];
				AlgoId=atoi(v[1].c_str());
				int mapAlgoId=atoi((v[1]+TagId.substr(3,2)).c_str());			

				if(algtag.count(mapAlgoId)>0)continue;
					else
						{
									
					//cout<<"1st"<<TagId<<endl<<"2nd"<<AlgoId<<"|"<<endl;		
					operation(AlgoId,TagId);
					//cout<<"CALLED"<<endl;		
					algtag.insert(pair<int,string>(mapAlgoId,TagId));
				}
				
		 }
}
		  file1.close();	
}
else
cout<<"Date File not Available"<<endl;	
	}

	void operation (int AlgoId,string tagId)
	{
		string Tag=tagId;
		string stra_value="";
		if(AlgoId==0) cout<<"AlgoId 0 for "<<serIp<<"|"<<Tag;
		int Tag_str=atoi(Tag.substr(3,2).c_str());
//cout<<Tag_str<<endl;
		map<int,string>::iterator it;
		it=strategy.find(Tag_str);
		if( it!= strategy.end())
		{
				stra_value=it->second;				
		}	
		if(segment=="FNO")
		{
			if(subsegment=="IOC")
			{
				//cout<<stra_value<<endl;
				int id=0;
				map<string,int>::iterator it1;
				it1=FNO_IOC.find(stra_value);				
				if( it1!= FNO_IOC.end())
				{
				id=it1->second;				
				}			
				if(id==AlgoId)
					{
					//cout<<"";				
					//cout<<serIp<<"|"<<AlgoId<<"|"<<Tag<<"|"<<stra_value<<"|"<<"Found in FNO_IOC"<<endl;
					//break;
					}
					else
					cout<<serIp<<"|"<<AlgoId<<"|"<<id<<"|"<<Tag<<"|"<<stra_value<<"|"<<" NOT Found in FNO_IOC"<<endl;
			}
			
			else if(subsegment=="BID")
			{
				int id2=0;
				map<string,int>::iterator it2;
				it2=FNO_BID.find(stra_value);
				if( it2!= FNO_BID.end())
				{
				id2=it2->second;
				//return sIP;
				}
				if(id2==AlgoId)
					{
					//cout<<"";
				//cout<<serIp<<"|"<<id2<<"|"<<stra_value<<"|"<<"Found in FNO_BID"<<endl;	
				//	break;
					}		
				else					
					cout<<serIp<<"|"<<AlgoId<<"|"<<id2<<"|"<<stra_value<<"|"<<" NOT Found in FNO_BID"<<endl;
			}
				
		}
		else if(segment=="CD")
		{
			if(subsegment=="IOC")
			{
				//int id=CD_IOC.find(stra_value)->second;
				int id=0;
				map<string,int>::iterator it1;
				it1=CD_IOC.find(stra_value);
				if( it1!= CD_IOC.end())
				{
				id=it1->second;
				//return sIP;
				}
				if(id==AlgoId)
				{
				cout<<"";
				//cout<<serIp<<"|"<<AlgoId<<"|"<<stra_value<<"|"<<"Found in CD_IOC"<<endl;
				//break;
				}
				else
				cout<<serIp<<"|"<<AlgoId<<"|"<<id<<"|"<<stra_value<<"|"<<" NOT Found in CD_IOC"<<endl;				
			}
			else if(subsegment=="BID")
			{
				//int id2=CD_BID.find(stra_value)->second;
				int id2=0;
				map<string,int>::iterator it2;
				it2=CD_BID.find(stra_value);
				if( it2!= CD_BID.end())
				{
				id2=it2->second;
				//return sIP;
				}
				if(id2==AlgoId)
					{
					cout<<"";
					//cout<<serIp<<"|"<<AlgoId<<"|"<<stra_value<<"|"<<"Found in CD_BID"<<endl;	
					//break;
					}
					else
				cout<<serIp<<"|"<<AlgoId<<"|"<<id2<<"|"<<stra_value<<"|"<<" NOT Found in CD"<<endl;	
			}
			
			
		}

		
	}	
void AddDict(char* path, string dict_name)
	{			
		char* fileRead = (char*)path;
		ifstream file1(fileRead);
		string str1;		
		 while(file1)
		 {
			if (!getline(file1, str1 )) break;
			istringstream ss(str1);	
			int i=0;
			int AId=0;
			string st_value="";
			 while(ss)
                    {
                        string s1;
                        if(!getline( ss, s1, ':' ))
                        {
                            break;
                        }
						if(i==0)
						st_value=s1;
						else
						AId=atoi(s1.c_str());						
						i++;
						//cout<<s1<<endl;
					}					
				if(dict_name=="FNO_IOC")
				{
					 FNO_IOC.insert(pair<string, int>(st_value,AId ));
					 //cout<<"Added IOC";
				}
				else if(dict_name=="FNO_BID")
				{
					FNO_BID.insert(pair<string, int>(st_value,AId));
					//cout<<"Added IOC";
				}
				 else if(dict_name=="CD_IOC")
				 {
					 CD_IOC.insert(pair<string, int>(st_value,AId));
					// cout<<"Added CD";
				 }
				else  if(dict_name=="CD_BID")
				 {
					 CD_BID.insert(pair<string, int>(st_value,AId));
					 //cout<<"Added CD";
				 }
				 else
					 cout<<"Invalid Operation"<<endl;	
				
				
		 }
		  file1.close();		
	
	}
	void Addstrategy()
        {  

		char* fileRead = (char*)+"/home/chandan/pankaj/TEST/strategy.txt";
		ifstream file1(fileRead);
		string str1;		
		 while(file1)
		 {			
			 if (!getline(file1, str1 )) break;
			 istringstream ss(str1);	
			int i=0;
			int index=0;
			string st_value="";
			 while(ss)
                    {
                        string s1;
                        if(!getline( ss, s1, ':' ))
                        {
                            break;
                        }
						if(i==0)
						index=atoi(s1.c_str());	
						else
						st_value=s1;						
						i++;
						//cout<<st_value<<endl;
						 
					}
					//cout<<st_value<<endl;
					//cout<<st_value<<index<<endl;
					strategy.insert(pair<int, string>(index,st_value));						
					// cout<<"Adding222"<<endl;
		 }
		 file1.close();
		 
   }
		void Addserver()
        {        
		char* fileRead = (char*)+"/home/chandan/pankaj/TEST/fnoserver.txt";
		if(segment=="FNO"&&subsegment=="IOC")
		fileRead = (char*)+"/home/chandan/pankaj/TEST/iocserver.txt";
		else if(segment=="FNO"&&subsegment=="BID")
		fileRead = (char*)+"/home/chandan/pankaj/TEST/bidserver.txt";
		else if(segment=="CD")
		fileRead = (char*)+"/home/chandan/pankaj/TEST/cdserver.txt";
		//else			
		
		ifstream file1(fileRead);
		string str1;		
		 while(file1)
		 {
			 if (!getline(file1, str1 )) break;
			 istringstream ss(str1);	
			int i=0;
			int Foid=0;
			string sr_Ip="";
			 while(ss)
                    {
                        string s1;
                        if(!getline( ss, s1, ':' ))
                        {
                            break;
                        }
						if(i==0)
						Foid=atoi(s1.c_str());
						else
						sr_Ip=s1;						
						i++;
					}
					if(segment=="FNO"&&subsegment=="IOC")
					findiocser.insert(pair<int, string>(Foid,sr_Ip));
					if(segment=="FNO"&&subsegment=="BID")
					findbidser.insert(pair<int, string>(Foid,sr_Ip));
					if(segment=="CD")
					findcdser.insert(pair<int, string>(Foid,sr_Ip));

		 }
		 file1.close();	
        }
		

};

int main(int arg, char* args[])
{
 backuppath="";
date_format="";
 segment="";
 subsegment="";	
//cout<<arg<<endl;
	for(int i=1; i<arg; i++)
    {		
        string str(args[i]);
		//cout<<str<<endl;
		if(str=="--path")
		{
			backuppath=args[i+1];
			i++;
		}
		else if(str=="--date")
		{
			date_format=args[i+1];
			i++;
		}
		else if(str=="--segment")
		{
			segment=args[i+1];
			i++;
		}
		else if(str=="--subsegment")
		{
			subsegment=args[i+1];
			i++;
		}
		else
		{
		cout<<"Invalid Argument  "<<args[i+1]<<endl;
		return 0;
		}
		//fileprocess flp;
		//fpl.
	}
	fileprocess fp1;
	fp1.Addstrategy();
	fp1.Addserver();
	fp1.AddDict(path_ioc,"FNO_IOC");
	fp1.AddDict(path_bid,"FNO_BID");
	fp1.AddDict(path_cdi,"CD_IOC");
	fp1.AddDict(path_cdb,"CD_BID");
	fp1.filereaddir();	
	return 0;
}
	
