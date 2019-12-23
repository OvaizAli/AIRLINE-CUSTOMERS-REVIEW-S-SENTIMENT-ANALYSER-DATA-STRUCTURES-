#include<iostream>
#include <string.h>
#include <cstdlib>              // Header Files 
#include<conio.h>               // for getch() function 
#include<fstream>
#include <queue>
#include<bits/stdc++.h>
#include<windows.h>             // Necessary when treating consoles  
using namespace std;

void gotoxy (int x, int y)
    {
         COORD coordinates;     // coordinates is declared as COORD
         coordinates.X = x;     // defining x-axis
         coordinates.Y = y;     //defining  y-axis
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);       
    }
    
class node{
	public:
		
		string data;
		node *left;
		node *right;
		int height;
		
		node(string d):left(0),right(0)
		{
			height=1;
			data=d;
		}
				
};

class sentinal
{
	public:
		
		node *positiveroot,*negativeroot;
		
		string userinput;
		
		string words[1000];
		
		int wordcount=0;
		
		int positive=0;
		
		int negative=0;
		
		int notflag=0;
		
		int dontflag=0;
		
		int wontflag=0;
		
		int len;
		
		int flag=0;
		
		double polarity;
		
		queue<string> postv;
		
		queue<string> negtv;
			

		sentinal():positiveroot(0),negativeroot(0)
		{
			
		}

		
		int max(int a,int b)
		{
			
			return (a>b) ? a : b;
			
		}

		
		int height(node *temp)
		{
			
			if(temp==NULL)
				return 0;
			
			return temp->height;	
		
		}
		
		
		node *rightrotate(node *y)
		{
			
			node *x=y->left;
			
			node *t2=x->right;
			
			x->right=y;
			
			y->left=t2;
			
			y->height=max(height(y->left),height(y->right)) + 1;
			
			x->height=max(height(x->left),height(x->right)) + 1;
			
			return x;
		
		}
		

		node *leftrotate(node *x)
		{
			
			node *y=x->right;
			
			node *t2=y->left;
			
			y->left=x;
			
			x->right=t2;
			
			x->height=max(height(x->left),height(x->right)) + 1;
			
			y->height=max(height(y->left),height(y->right)) + 1;
			
			return y;
			
		}
		

		int getbalance(node *temp)
		{
			
			if(temp==NULL)
				return 0;
			
			return height(temp->left)-height(temp->right);	
		
		}
		
		
		node *insert(node *n,string d)
		{
			
			if(n==NULL)
				return new node(d);
				
			if(d<n->data)
				n->left=insert(n->left,d);	
			else if(d>=n->data)
				n->right=insert(n->right,d);
			
				
			n->height=1+max(height(n->left),height(n->right));
			
			int balance	= getbalance(n);
			
			if(balance>1 && d<n->left->data)
				return rightrotate(n);
			
			if(balance<-1 && d>=n->right->data)
				return leftrotate(n);
				
			if(balance>1 && d>=n->left->data)
			{
				
				n->left=leftrotate(n->left);
				
				return rightrotate(n);
			
			}			
			
			if(balance<-1 && d<n->right->data)
			{
				
				n->right=rightrotate(n->right);
				
				return leftrotate(n);
			
			}
			
			return n;
		
		}
		
		
		node *negtree()
		{
			
			fstream neg("Negative.txt");
			
			string str;
			
			while(!neg.eof())
			{
				
				getline(neg,str);
				
				negativeroot=insert(negativeroot,str);
			
			}
			
			neg.close();
		
		}
		

		node *postree()
		{
			
			fstream pos("Positive.txt");
			
			string str;
			
			if(!pos.is_open())
			{
				
				cout<<"File Not Opened"<<endl;
				
				exit(0);
			}
			
			while(!pos.eof())
			{
				
				getline(pos,str);
				
				positiveroot=insert(positiveroot,str);
			
			}
			
			pos.close();
		
		}
		

		void preorder(node *root)
		{
			
			if(root!=NULL)
			
			{
				
				cout<<root->data<<" ";
				
				preorder(root->left);
				
				preorder(root->right);	
			
			}
			
		}
		
		
		void user_input()
		{
			
			cout<<"Enter customer's review for analysis:"<<endl;
			
			fflush(stdin);
			
			getline(cin,userinput);
		
		}
		
		
		void file_input()
		{
			
			fstream inp("Input.txt");
			
			getline(inp,userinput);
		
		}
		
		
		void wordbreak()
		{
			
			len=userinput.length();
			
			if(userinput[len-1]!='.')
			{
				
				userinput[len]='.';
				
				len++;	
			
			}
			
			int x=0;
			
			for(int i=0;i<len;i++)
			{
				
				if(userinput[i]==' ')
				{
					
					x++;
					
					wordcount++;
					
					continue;
				
				}
				
				if(userinput[i]=='.'||userinput[i]==',')
				{
						
					x++;
					
					wordcount++;
					
					continue;
				}
				
				words[x]+=userinput[i];
			
			}
		
		}
		
		
		void search(node *root,string temp,int n)
		{
			
			if(root==NULL)
				return;
			
			search(root->left,temp,n);
			
			if(root->data==temp)
			{
				
				if(n==1)
				{
					
					if(notflag==1)
					{
						
						negative++;
						
						string t="not ";
						
						t+=temp;
						
						negtv.push(t);
						
						notflag=0;
						
						flag++;
						
						return;
					
					}
					
					if(wontflag==1)
					{
						
						negative++;
						
						string t="won't ";
						
						t+=temp;
						
						negtv.push(t);
						
						wontflag=0;
						
						flag++;
						
						return;
					
					}
					
					if(dontflag==1)
					{
						
						negative++;
						
						string t="don't ";
						
						t+=temp;
						
						negtv.push(t);
						
						dontflag=0;
						
						flag++;
						
						return;
					
					}
					
					else
					{
						
						positive++;
						
						postv.push(temp);
						
						flag++;
						
						return;
					
					}
				
				}
				
				if(n==2)
				{
					
					if(notflag==1)
					{
						
						positive++;
						
						string t="not ";
						
						t+=temp;
						
						postv.push(t);
						
						notflag=0;
						
						flag++;
						
						return;
					
					}
					
					if(wontflag==1)
					{
						
						positive++;
						
						string t="won't ";
						
						t+=temp;
						
						postv.push(t);
						
						wontflag=0;
						
						flag++;
						
						return;
					
					}
					
					if(dontflag==1)
					{
						
						positive++;
						
						string t="don't ";
						
						t+=temp;
						
						postv.push(t);
						
						dontflag=0;
						
						flag++;
						
						return;
					
					}
					
					else
					{
						
						negative++;
						
						negtv.push(temp);
						
						flag++;
						
						return;
					
					}
				
				}
			
			}
			
			search(root->right,temp,n);
		
		}
		
		
		void word_search()
		{
			
			for(int i=0;i<wordcount;i++)
			{
				
				if(words[i]=="not"||words[i]=="Not")
				{
					
					notflag++;
					
					continue;
				
				}
				
				flag=0;
				
				search(positiveroot,words[i],1);
				
				if(!flag)	
					search(negativeroot,words[i],2);
				else
					continue;	
			
			}
		
		}
		
		
		void result()
		{
			
			system("cls");
			
			if(!postv.empty())
			{
				
				cout<<endl<<"positive words:"<<endl;
				
				while(!postv.empty())
				{
					
					cout<<postv.front()<<endl;;
					
					postv.pop();
				
				}
			
			}
			
			if(!negtv.empty())
			{
				
				cout<<endl<<"negative words:"<<endl;
				
				while(!negtv.empty())
				{
					
					cout<<negtv.front()<<endl;;
					
					negtv.pop();
				
				}
			
			}
			
			double total=positive+negative;
			
			cout<<"positive sentiments: "<<positive<<endl;
			
			cout<<"Negative sentiments: "<<negative<<endl;
			
			cout<<"total sentimental references: "<<total<<endl;
			
			cout<<endl;
			
			polarity=positive/total;
			
			cout<<endl<<"POLARITY OF THE SENTENCE IS: "<<polarity<<endl;
		
		}
		
		void upperToLowerCase()
		{
			transform(userinput.begin(),userinput.end(),userinput.begin(),::tolower);
			cout<<userinput;
		}
		
};


int main()
{
	
	sentinal sen;
	
	sen.negtree();
	
	sen.postree();
	
	int choice;
	
	cout<<"******************************************************************************************************";
	gotoxy(20,1);
	cout<<"WELCOME TO AIRLINE CUSTOMERS' REVIEW'S SENTIMENT ANALYSER"<<endl;
	cout<<"******************************************************************************************************"<<endl;
	gotoxy(40,4);
	cout<<"***CHOICES***";
	gotoxy(20,6);
	cout<<"1) To place customer's review for sentiment analysis";
	gotoxy(20,7);
	cout<<"2) To place file of customer's review for sentiment analysis"<<endl;
	
	cin>>choice;
	
	switch(choice)
	{
		
		case 1:
			
			sen.user_input();
			
			break;
		
		case 2:
			
			sen.file_input();
			
			break;
		
		default:
			
			cout<<"Wrong Choice"<<endl;
			
			exit(0);		
	
	}
	
	sen.upperToLowerCase();
	
	sen.wordbreak();
	
	sen.word_search();
	
	sen.result();      
    
	return 0; 

}
