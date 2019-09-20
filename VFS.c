//Customized Dynamic File System

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define MAXSIZE 1024
#define MAXINODE 10
#define MAX 10
#define REGULAR 1


struct IIT
{
				int inodeNo;
				int filetype;
				int fileSize;
				char filename[30];
				char *fileAccessTime;
				char *fileModTime;
				char *inodeModTime;
				char *fileData;
};
struct SuperBlock
{
				int freeInodes;
				int nextfreeInode;
				int noOfInode;
};
struct DILB
{
				struct IIT inodes[MAXINODE];
};
struct fileTable
{
				int refCount;
				int permissions;
				int offset;
};
struct UAREA
{
				int UFDT[MAX];
};

struct DILB db;
struct SuperBlock sb;
void initializeDILB();
void initializeSuperBlock();
void createFile();
void ls();
void display();

int main()
{
				int ch;
				initializeDILB();
				initializeSuperBlock();
				while(1)
				{
								printf("\n1.List Files\n2.create File\n3.display file data\n4.exit");
								printf("\nEnter the choice:");
								scanf("%d",&ch);
								switch(ch)
								{
												case 1: ls();
																break;
												case 2:
																createFile();
																break;
												case 3:
																display();
																break;
												case 4:
																exit(0);

												default: printf("\nWrong Choice");
								}
				}
				return 0;
}
void initializeDILB()
{
				int i=0;
				while(i<MAXINODE)
				{
								db.inodes[i].inodeNo = i+1;
								db.inodes[i].filetype=0;
								db.inodes[i].fileSize=MAXSIZE;
								db.inodes[i].fileAccessTime=NULL;
								db.inodes[i].fileModTime = NULL;
								db.inodes[i].inodeModTime= NULL;
								db.inodes[i].fileData= NULL;
								i++;
				}
				
}
void initializeSuperBlock()
{
				sb.freeInodes=MAXINODE;
				sb.nextfreeInode = 0;
				sb.noOfInode= MAXINODE;
}
void ls()
{
				int i=0;
				printf("\nInode\tFileName\tFileType\tFileAccessTime");
				while(i<MAXINODE)
				{
								printf("\n%4d\t%4s\t%4d\t%4s",db.inodes[i].inodeNo,db.inodes[i].filename,db.inodes[i].filetype,db.inodes[i].fileAccessTime);
								i++;
				}
}
void createFile()
{
				char str[30],ch;
				int i=0,j=0;
				printf("\nEnter a file name:");
				scanf("%s",str);
/*
				while(i<MAXINODE)
				{
								if(db.inodes[i].filetype==1)
								{
												j=0;
												while(str[j]!='\0')
												{
																//printf("%c",str[j]);
																if(db.inodes[i].filename[j]!=str[j])
																{
																				break;
																}
																j++;
												}
												if(str[j]=='\0')
												{
																printf("\nFile is already exist.");
																printf("\nDo you want to overwriteit.y/n");
																scanf("%c",&ch);
																if(ch=='y')
																{
																				printf("Enter a data to add into file: ");
																				scanf("%s",db.inodes[i].fileData);
																				
																}
																else if(ch=='n')
																{
																				return;
																}
												}
								}
								i++;
				}
*/
				while(db.inodes[i].filetype!=0)
				{
								i++;
				}	
				db.inodes[i].filetype=REGULAR;
				while(str[j]!='\0')
				{
								db.inodes[i].filename[j]=str[j];
								j++;
				}
				db.inodes[i].fileData= (char *)malloc(sizeof(char)*MAXSIZE);
				printf("Enter a data to add into file: ");
				scanf("%s",db.inodes[i].fileData);
				//fgets(db.inodes[i].fileData,1024,stdin);
				//flush(stdin);
}
void display()
{
				char str[30];
				int i=0,j=0;
				printf("Enter file name:");
				scanf("%s",str);
				while(i<MAXINODE)
				{
							/*	if(db.inodes[i].fileData!=NULL)	
								{
												printf("\nFile Data is : %s",db.inodes[i].fileData);
								}
								*/
								if(db.inodes[i].filetype==1)
								{
												j=0;
												while(str[j]!='\0')
												{
																//printf("%c",str[j]);
																if(db.inodes[i].filename[j]!=str[j])
																{
																				break;
																}
																j++;
												}
												if(str[j]=='\0')
												{
																printf("\n\nFile Data is :\n\t %s\n",db.inodes[i].fileData);
												}
								}
								i++;
				}
}
