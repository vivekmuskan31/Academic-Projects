#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define maxSize 128            //***********Update maxSize here**************
#define default_index -1

//Node class for suffix tree
struct Node{
    int end;                    //Length of string
    int start;                  //Starting index of string in input
    struct Node* childList[128];//Maximum ascii characters
    int leafLabel;
};
typedef struct Node Node;

//Global input variable
static char input[maxSize];

//hashCode
int hashCode(char c){
    int i = c;
    return i;
}

//makeNewNode
Node* makeNewNode(int strt,int finish){
    Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->end = finish;
    temp->start = strt;
    temp->leafLabel = -1;
    for(int i=0;i<128;i++){temp->childList[i]=NULL;} 
    return temp;
}
//addSuffix
void addSuffix(Node* temp, int start_index, int end_index,int leaf_index){
    int h = hashCode(input[start_index]);
    //addLeaf as there is no leaf with current char.            //CASE1
    if(temp->childList[h]==NULL){                           
        Node* new = makeNewNode(start_index,end_index);
        new->leafLabel = leaf_index;
        temp->childList[h] = new;
        return;
    }
    //keepMatching                                         
    Node* ParentOf_temp = temp;
    temp = temp->childList[h];
    int j;
    int k = start_index;
    for(j=temp->start; j<=temp->end; j++){
        if(input[j] == input[k]){k++;}
        else{
            //splitBranch                                       //CASE2
            if(temp->leafLabel==-1){
                Node* above = makeNewNode(temp->start,j-1);     //Rotation has to be done
                above->leafLabel = temp->leafLabel; 

                Node* new = makeNewNode(k,end_index);                    
                new->leafLabel = leaf_index;

                h = hashCode(input[k]);
                above->childList[h] = new;

                temp->start = j;
                
                h = hashCode(input[j]);
                above->childList[h] = temp;

                h = hashCode(input[above->start]);
                ParentOf_temp->childList[h] = above;
                return;

            }
            //splitLeaf                                         //CASE3
            else{
                Node* new = makeNewNode(k,end_index);           //addNewLeaf         
                new->leafLabel = leaf_index;
                h = hashCode(input[k]);
                temp->childList[h] = new;

                Node* old = makeNewNode(j,temp->end);           //addRestString
                old->leafLabel = temp->leafLabel; 
                h = hashCode(input[j]);
                temp->childList[h] = old;

                temp->leafLabel = -1;                           //became internal Node
                temp->end = j-1;
                return;
            }       
        }
    }
    //Jump to next Node                                         //CASE4
    addSuffix(temp,k,end_index,leaf_index);                      
    return;
}

//buildSuffixTree
Node* buildSuffixTree(){
    printf("\nBuilding Suffix Tree...");
    Node *root = makeNewNode(default_index,default_index);
    for(int i=0;i<strlen(input);i++){
        addSuffix(root,i,strlen(input)-1,i);
    }
    printf("\nSuffix Tree built Successfully");
    return root;
}

//print Level
void printLevel(struct Node* temp, int l){                  //Root = Level 0
    for(int i=0;i<128;i++){
        if(temp->childList[i]!=NULL){
            Node* temp2 = temp->childList[i];
            if(l==1){printf("(%d, %d, [%d]) ",temp2->start,temp2->end,temp2->leafLabel);}
            else{printLevel(temp2,l-1);}    
        }
    }
    
}


int height(Node* temp){
    int ht = 0;
    if(temp->leafLabel > -1){return 0;}
    for(int i=0;i<128;i++){
        if(temp->childList[i]!=NULL){
            int k = height(temp->childList[i]);
            if(ht<k){ht = k;}
        }
    }
    return (ht+1);
}

//printSuffixTree
void printSuffixTree(Node* temp){
    printf("\n_____________________________________________________________");
    printf("\nPrinting Suffix Tree of %s ",input);
    printf("\nFORMAT --> (start, end, [leafLabel])");
    for(int i=1;i<=height(temp);i++){
        printf("\nLevel %d ",i);
        printLevel(temp,i);
    }
    printf("\nleafLabel = -1 denotes internal Node");
    printf("\n_____________________________________________________________");
}


//___________________________________________________________________________
//___________________APPLICATION OF SUFFIX TREE______________________________
//___________________________________________________________________________

//getAllLeafLevel
int getAllLeafLevel(Node* temp){
    int count=0;
    if(temp->leafLabel>-1){printf(" %d,",temp->leafLabel);return 1;}
    for(int i=0;i<128;i++){
        if(temp->childList[i]!=NULL){
            Node* temp2 = temp->childList[i];
            count+=getAllLeafLevel(temp2);
        }
    }
    printf("\n");
    return count;
}

//1. Substring Check
bool PatternMatch(char s[],Node* temp){

    int h = hashCode(s[0]);
    if(temp->childList[h]==NULL){
        printf("\nSubstring %s NOT FOUND in input %s",s,input);
        return false;
    }
    temp = temp->childList[h];
    int l = strlen(s);
    int begin_index[maxSize];
    int k = temp->start;
    for(int j=0; j<l; j++){
        if(s[j] == input[k]){k++;}
        else{
            printf("\nSubstring %s NOT FOUND in input %s",s,input);
            return false;
        }
        if(k>temp->end){
            if(j==l-1){break;}
            if(temp->leafLabel!=-1){
                printf("\nSubstring %s NOT FOUND in input %s",s,input);
                return false;
            }
            else{
                h = hashCode(s[j+1]);
                temp = temp->childList[h];
                k = temp->start;
            }
        }
    }
    printf("\nSubstring '%s' starts from following indices in input String :",s);
    int count = getAllLeafLevel(temp);
    printf("There are total %d match in your input starting from above indices",count);
    return true;
}

typedef struct outNode{
    int min;
    int max;
    bool isTrue;
    int begin;
    int finish;
}out;

out makeNewOut(int Min,int Max,bool T,int b,int f){
    out temp;
    temp.min = Min;
    temp.max = Max;
    temp.isTrue = T;
    temp.begin = b;
    temp.finish = f;
    return temp;
}
//2.Longest Common Substring

//Compare
out Compare(out a, out b,int cmp){
    int min,max,bgn,fnsh;
    bool flag;
    if(a.min < b.min){min = a.min;}
    else{min = b.min;}
    if(a.max > b.max){max = a.max;}
    else{max = b.max;}

    if(min<cmp && max>cmp){flag = true;}
    else{flag=false;}

    int check_a = -(a.begin - a.finish);
    int check_b = -(b.begin - b.finish);
    if(a.isTrue && b.isTrue){
        if(check_a>check_b){bgn = a.begin;fnsh = a.finish;}
        else{bgn = b.begin;fnsh = b.finish;}
    }
    else if(a.isTrue){bgn = a.begin;fnsh = a.finish;}
    else if(b.isTrue){bgn = b.begin;fnsh = b.finish;}
    else{bgn = -1;fnsh = -1;}

    return makeNewOut(min,max,flag,bgn,fnsh);
}
//LCS
out LCS(Node* temp, int idx,int d){
    //baseCase
    if(temp->leafLabel>-1){return makeNewOut(temp->leafLabel,temp->leafLabel,false,temp->start,temp->end);}

    out ans = makeNewOut(maxSize+1,-1,false,-1,-1);
    for(int i=0;i<128;i++){
        if(temp->childList[i]!=NULL){
            Node* temp2 = temp->childList[i];
            out curr_out = LCS(temp2,idx,d+1);
            ans = Compare(ans,curr_out,idx);
        }
    }
    if(ans.begin==-1 && ans.isTrue && d!=0){
        ans.begin = temp->start;
        ans.finish = temp->end;
    }
    else if(ans.isTrue && d!=0){
        ans.begin = temp->start;
    }
    else if(d==0 && ans.begin > -1){
        printf("\n One of the Longest Commmon Substring of given inputs has indices (start,end) = (%d, %d) in input X#Y$ is : ",ans.begin,ans.finish);
        for(int t=ans.begin;t<=ans.finish;t++){printf("%c",input[t]);}
        printf("\n");
    }
    else{
        //printf("\nNo common substring found between given inputs");
    }
    return ans;
}


//Main
void main(){
    //Intialization
    int choice = 1;
    printf("\n*************************SUFFIX TREE BUILDER*****************************\n");
    while(choice > 0){
        printf("\n##########################################################################");
        printf("\n1. Build a Suffix Tree and Print it");
        printf("\n2. Build a Suffix Tree and search a pattern");
        printf("\n3. Find Longest Common Substring of two String");
        printf("\n0. To Exit");
        printf("\nType 0 or 1 or 2 or 3 : ");
        scanf("%d",&choice);
        if(choice ==1){
            printf("Maximum size of string is 128.\nIf you want to change this update value of 'maxSize' in Line number 6");
            printf("\nEnter string input below (Don't put space in between)...\n");
            printf("___CAUTION__ : Add a '$' in the end\n Enter String : ");
            scanf("%s",&input);
            Node* root = buildSuffixTree();
            printSuffixTree(root);
        }
        else if(choice == 2){
            char s[maxSize];
            printf("\nMaximum size of string is 128.\nIf you want to change this, update value of 'maxSize' in Line number 6");
            printf("\nEnter string input below (Don't put space in between)...\n");
            printf("___CAUTION__ : Add a '$' in the end\n Enter String : ");
            scanf("%s",&input);
            Node* root = buildSuffixTree();
            printf("\nEnter the pattern to be searched :");
            scanf("%s",&s);
            PatternMatch(s,root);
        }
        else if(choice == 3){
            int l1;
            printf("\nMaximum size of string is 128.\nIf you want to change this, update value of 'maxSize' in Line number 6");
            printf("\nDon't put space in between");
            printf("\nEnter Two String X and Y as 'X#Y$' Example : Ant#Ball$ ");
            printf("\n___CAUTION__ : Do enter String as X#Y$ : ");
            scanf("%s",&input);
            printf("\nEnter the exact length of 1st String ('#' excluded) : ");
            scanf("%d",&l1);
            Node* root = buildSuffixTree();
            LCS(root,l1,0);
        }
    }
     
}