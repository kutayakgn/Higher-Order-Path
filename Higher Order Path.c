// ?EREF KUTAY AKGÜN/150118065 !! IMPORTANT NOTE !!
//IN THIS PROJECT WE NEED TO COPY ADDRESS OF SMALL DATASET FOLDER AND
// COPY TO ADDRESS NAME PART IN LINE: 242,254,272,282,298,308
#include<stdio.h>
#include<dirent.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
//master linked list STRUCTER
struct wordlist{
char data[90];
char dataddress[200];
struct wordlist * next;
}; typedef struct wordlist wl;
// SORTED LYST STRUCTER
struct sortlist{
char data[90];
char dataddress[200];
int count;
struct sortlist * next;
}; typedef struct sortlist sl;
// ADD METHOD FOR ADDYNG WORDS FROM FYLE TO LYNKED LYST
void add(wl *r,char w[],char ad[]){
if (r == NULL){
 strcpy(r->data,w);
 strcpy(r->dataddress,ad);
 r->next=NULL;}
else {
 while(r->next!=NULL){
 r=r->next;
 }
 wl * tempNode = (wl*)malloc(100*sizeof(wl));
 strcpy(tempNode->data,w);
 strcpy(tempNode->dataddress,ad);
 tempNode->next = NULL;
 r->next=tempNode; }}
//PRYNT METHOD FOR MASTER LINKED LIST
void printlist(wl * list){
wl * r;
r=list;
while(r!=NULL){
printf("%s ->",r->data);
//printf("%s\n\n",r->dataddress);
r=r->next;
}}
// PRINT METHOD FOR SORTED LYNKED LIST
void printsortlist(sl * list){
sl * r;
r=list;
while(r!=NULL){
printf("%s -> ",r->data);
printf("%d\n",r->count);
r=r->next;
}}
//THIS METHOD FIND FIRST ORDER BETWEEN MASTER LINKED LIST'S WORDS
void findfirstorder(wl *node){
printf("1st-order term co-occurrence : \n");
wl * tempnode;
tempnode = node;
wl * checknode;
while(tempnode->next!=NULL){
checknode=tempnode->next;
while(checknode!=NULL){
if( (strcmp(checknode->data,tempnode->data)!=0) && (strcmp(checknode->dataddress,tempnode->dataddress)==0)){
printf("{%s,%s},",tempnode->data,checknode->data);
}
checknode=checknode->next;
}
tempnode=tempnode->next;
}
}
// THYS METHOD FYND SECOND ORDER OF MASTER LINKED LIST WORDS
void findsecondorder(wl * node){
wl *firstnode;
firstnode=node;
wl * secondnode;
wl * thirdnode;
wl * fourthnode;
while(firstnode->next!=NULL){
secondnode=firstnode->next;
while(secondnode->next!=NULL){
if(strcmp(secondnode->dataddress,firstnode->dataddress)!=0||(strcmp(secondnode->data,firstnode->data)==0))
continue;
else if((strcmp(secondnode->dataddress,firstnode->dataddress)==0)){
thirdnode=secondnode->next;
while(thirdnode!=NULL){
if((strcmp(secondnode->data,thirdnode->data)==0)){
fourthnode=thirdnode->next;
while(fourthnode!=NULL){
if((strcmp(fourthnode->dataddress,thirdnode->dataddress)==0)&&(strcmp(firstnode->dataddress,fourthnode->dataddress)!=0))
printf("{%s , %s} ,",firstnode->data,fourthnode->next->data);
fourthnode=fourthnode->next;
}
}
thirdnode=thirdnode->next;
}
secondnode=secondnode->next;
}
firstnode=firstnode->next;
}
}}
// THIS METHOD COPY THE MASTER LINKED LYST TO ECON, HEALTH, MAGAZIN LINKED LISTS
// TO SORT WORDS AND FIND FREQURNCY
void copylist(wl * r, sl * e , sl * h , sl * m){
wl * master;
master=r;
sl* ee;
ee=e;
sl* hh;
hh=h;
sl*mm;
mm=m;
while (master!=NULL){
//ADDYNG TO ECON LYNKED LIST
if(strstr(master->dataddress,"econ") != NULL) {
 if (ee == NULL){
 strcpy(ee->data,master->data);
 strcpy(ee->dataddress,master->dataddress);
 ee->count+=1;
 ee->next=NULL;}
else {
 while(ee->next!=NULL){
 if(strcmp(ee->data,master->data)==0)
 break;
 ee=ee->next;
 }
 sl * tempNode = (sl*)malloc(100*sizeof(sl));
 strcpy(tempNode->data,master->data);
 strcpy(tempNode->dataddress,master->dataddress);
 if(strcmp(ee->data,master->data)==0){
 ee->count+=1;
}
else{
tempNode->count=1;
tempNode->next=NULL;
ee->next=tempNode;
}
 }
}
//ADDING TO HEALTH LYNKED LIST
else if(strstr(master->dataddress,"health") != NULL) {
 if (hh == NULL){
 strcpy(hh->data,master->data);
 strcpy(hh->dataddress,master->dataddress);
 hh->count=1;
 hh->next=NULL;}

else {
 while(hh->next!=NULL){
 if(strcmp(hh->data,master->data)==0)
 break;
 hh=hh->next;
 }
 sl * tempNode = (sl*)malloc(100*sizeof(sl));
 strcpy(tempNode->data,master->data);
 strcpy(tempNode->dataddress,master->dataddress);
 if(strcmp(hh->data,master->data)==0){

 hh->count+=1;
}
else{
tempNode->count+=1;
tempNode->next=NULL;
hh->next=tempNode;
}
 }
}
//ADDDING TO MAGAZYN LYNKED LYST
else if(strstr(master->dataddress,"magazin") != NULL) {
 if (mm == NULL){
 strcpy(mm->data,master->data);
 strcpy(mm->dataddress,master->dataddress);
 mm->count=1;
 mm->next=NULL;}
else {
 while(mm->next!=NULL){
 if(strcmp(mm->data,master->data)==0)
 break;
 mm=mm->next;
 }
 sl * tempNode = (sl*)malloc(100*sizeof(sl));
 strcpy(tempNode->data,master->data);
 strcpy(tempNode->dataddress,master->dataddress);
 if(strcmp(mm->data,master->data)==0){
 mm->count+=1;
}
else{
tempNode->count=1;
tempNode->next=NULL;
mm->next=tempNode;
}
 }
}
master=master->next;}
m=m->next;
e=e->next;
h=h->next;
printsortlist(m);
printf("\n\n\n");
printsortlist(e);
printf("\n\n\n");
printsortlist(h);
printf("\n\n\n");
}
int main(void) {
setlocale(LC_ALL,"Turkish");
wl * root;
wl * current;
root=NULL;
current=NULL;
root = (wl*)malloc(100*sizeof(wl));
root->next=NULL;
current=root;
//cREATING FILE*
FILE *fp;
char tempword[90];
int c;
// ENTERING TO DYRECTORY FOLDER
DIR *d;
struct dirent *dir;
d = opendir("C:\\Users\\Kutay\\Desktop\\small dataset2\\econ");
if (d)
{
while ((dir = readdir(d)) != NULL)
{
// IT READS . AND .. FIRST SO THIS CODE PASS THEM
if(!strcmp(dir->d_name,"."))
continue;
if(!strcmp(dir->d_name,".."))
continue;
//COMBYNE FOLDER NAME AND TEXT FILE NAME AND MAKE IT EQUAL TO FP
char tempaddress[200]="C:\\Users\\Kutay\\Desktop\\smalldataset2\\econ\\";
char add_address[200];
strcpy(add_address,tempaddress);
strcat(tempaddress,dir->d_name);
//OPENING AND READING FP(TEXT FILE)
fp=fopen(tempaddress,"r");
do{
c=fscanf(fp,"%s",tempword);
if(c!=EOF){
//ADDING WORDS TO MASTER LINKED LIST
add(current,tempword,add_address);
}
}while(c!=EOF);
fclose(fp);
}
closedir(d);
}
//DOING SAME THING FOR HEALTH AND MAGAZIN
d = opendir("C:\\Users\\Kutay\\Desktop\\small dataset2\\health");
if (d)
{
while ((dir = readdir(d)) != NULL)
{
if(!strcmp(dir->d_name,"."))
continue;
if(!strcmp(dir->d_name,".."))
continue;
char tempaddress[200]="C:\\Users\\Kutay\\Desktop\\smalldataset2\\health\\";
char add_address[200];
strcpy(add_address,tempaddress);
strcat(tempaddress,dir->d_name);
fp=fopen(tempaddress,"r");
do{
c=fscanf(fp,"%s",tempword);
if(c!=EOF){
add(current,tempword,add_address);
}
}while(c!=EOF);
fclose(fp);
}
closedir(d);
}
d = opendir("C:\\Users\\Kutay\\Desktop\\small dataset2\\magazin");
if (d)
{
while ((dir = readdir(d)) != NULL)
{
if(!strcmp(dir->d_name,"."))
continue;
if(!strcmp(dir->d_name,".."))
continue;
char tempaddress[200]="C:\\Users\\Kutay\\Desktop\\small dataset2\\magazin\\";
char add_address[200];
strcpy(add_address,tempaddress);
strcat(tempaddress,dir->d_name);
fp=fopen(tempaddress,"r");
do{
c=fscanf(fp,"%s",tempword);
if(c!=EOF){
add(current,tempword,add_address);
}
}while(c!=EOF);
fclose(fp);
}
closedir(d);
}
root=root->next;
printf("Master Lynked List:\n");
printlist(root);
printf("\n\n\n");
findfirstorder(root);
printf("\n\n");
//THIS METHOD HAS SOME MINOR RUNTIME ERROR
//findsecondorder(root);
sl * esl=NULL;
esl = (sl*)malloc(100*sizeof(sl));
esl->next=NULL;
sl * hsl=NULL;
hsl = (sl*)malloc(100*sizeof(sl));
hsl->next=NULL;
sl * msl=NULL;
msl = (sl*)malloc(100*sizeof(sl));
msl->next=NULL;
printf("\n\n LISTS WITH FREQUENCY: \n\n");
copylist(root,esl,hsl,msl);
return(0);
}
