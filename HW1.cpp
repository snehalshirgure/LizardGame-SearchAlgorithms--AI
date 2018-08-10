#include<iostream>
#include<queue>
#include<stack>
#include<fstream>
#include<string>
#include<cmath>
#include<ctime>
#include<random>
#include<climits>


using namespace std;

int n,p;
double T ;
double t =1;
default_random_engine generator_real;
uniform_real_distribution<double> distribution_real(0.0,1.0);

 
struct Node{
    int lizardCount;
    int** arr;
};  

Node generateNode(){
int **a = new int*[n];
	//pointer initialization
for(int i=0;i<n;i++)
		a[i]=new int[n];
		
	Node node1;
	node1.lizardCount=0;
	node1.arr = a;
return node1;		
}  


int invert(int **arr){
for(int i=0;i<n;i++)
 for(int j=0;j<n;j++)
   if(arr[i][j]==-1)
    arr[i][j]=0;
}

void invalidate(int **arr,int x,int y,int toInvert){

for(int j=y+1;j<n;j++){
 if(arr[x][j]==2)
  break;
 if(toInvert)
 arr[x][j]=0;
 else
 arr[x][j]=-1;
}
	
for(int j=y-1;j>=0;j--){
 if(arr[x][j]==2)
  break;
   if(toInvert)
   arr[x][j]=0;
   else
   arr[x][j]=-1;
}

for(int i=x+1;i<n;i++){
 if(arr[i][y]==2)
  break;
  if(toInvert)
  arr[i][y]=0;
  else
 arr[i][y]=-1;	
}
for(int i=x-1;i>=0;i--){
 if(arr[i][y]==2)
  break;
   if(toInvert)
  arr[i][y]=0;
  else
 arr[i][y]=-1;	
}

for(int i=x+1,j=y+1; i<n&&j<n ; i++,j++)
 {
 if(arr[i][j]==2)
  break;
   if(toInvert)
  arr[i][j]=0;
  else
 arr[i][j]=-1;	
}

for(int i=x-1,j=y-1; i>=0&&j>=0 ; i--,j--)
 {
 if(arr[i][j]==2)
  break;
   if(toInvert)
  arr[i][j]=0;
  else
 arr[i][j]=-1;	
}


for(int i=x+1,j=y-1; i<n&&j>=0 ; i++,j--)
 {
 if(arr[i][j]==2)
  break;
   if(toInvert)
  arr[i][j]=0;
  else
 arr[i][j]=-1;	
}


for(int i=x-1,j=y+1; i>=0&&j<n ; i--,j++)
 {
 if(arr[i][j]==2)
  break;
   if(toInvert)
  arr[i][j]=0;
  else
 arr[i][j]=-1;	
}

}
   

Node generateChildren(Node n1,int x,int y){
Node n2 = generateNode();
for(int i=0;i<n;i++)
 for(int j=0;j<n;j++)
       n2.arr[i][j]=n1.arr[i][j];
      
       n2.arr[x][y]=1;
       invalidate(n2.arr,x,y,0);
       n2.lizardCount = n1.lizardCount+1;
        //printArray(n2.arr,n);
    
return n2;		
}  

void printArray(int **arr){
for(int i=0;i<n;i++){
     for(int j=0;j<n;j++){ 
      cout<<arr[i][j]<<" ";
  }    
  cout<<endl;
  } 
}    


int bfs(int **array){

    queue<Node> myarr;
    Node root= generateNode();
    
    for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
		 root.arr[i][j]=array[i][j];

    myarr.push(root);
 
   while (1)
  {
  //no more nodes to check 
    if(myarr.empty()){
      
       return 0;
   }    
   
    Node n1 =  myarr.front();
    myarr.pop();
   
  //check goal state for popped node and not checking on root
   if(n1.lizardCount == p){
   
       invert(n1.arr);
    
   for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
       array[i][j]=n1.arr[i][j]; 
      return 1;
    
     }    

     
  //if goal not found, form children nodes and push back into queue for checking
           
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
    if(n1.arr[i][j]==0){
    Node n2 = generateChildren(n1,i,j);
    myarr.push(n2);
       }   
  
   }//end of while(1)     
    
}
   

int dfs(int **array){

    stack<Node> myarr;
    Node root= generateNode();
    
    for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
		 root.arr[i][j]=array[i][j];

    myarr.push(root);
 
   while (1)
  {
  //no more nodes to check 
    if(myarr.empty()){
        return 0;
   }    
   
    Node n1 =  myarr.top();
    myarr.pop();
   
  //check goal state for popped node and not checking on root
   if(n1.lizardCount == p){
     invert(n1.arr);
  
   for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
       array[i][j]=n1.arr[i][j];
   
      return 1;
    
     }    

     
  //if goal not found, form children nodes and push back into queue for checking
           
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
    if(n1.arr[i][j]==0){
    Node n2 = generateChildren(n1,i,j);
    myarr.push(n2);
       }   
  
   }//end of while(1)     
    
}
   

int conflict(int **arr,int x,int y){
int attackCount = 0;

for(int j=y+1;j<n;j++){
 if(arr[x][j]==2)
  break;
 if(arr[x][j]==1)
 attackCount++;
 
}
	
for(int j=y-1;j>=0;j--){
 if(arr[x][j]==2)
  break;
  if(arr[x][j]==1)
 attackCount++;
}

for(int i=x+1;i<n;i++){
 if(arr[i][y]==2)
  break;
  if(arr[i][y]==1)
 attackCount++;	
}
for(int i=x-1;i>=0;i--){
 if(arr[i][y]==2)
  break;
 
  if(arr[i][y]==1)
 attackCount++;
}

for(int i=x+1,j=y+1; i<n&&j<n ; i++,j++)
 {
 if(arr[i][j]==2)
  break;
 if(arr[i][j]==1)
  attackCount++;
}

for(int i=x-1,j=y-1; i>=0&&j>=0 ; i--,j--)
 {
 if(arr[i][j]==2)
  break;
 
 if(arr[i][j]==1)
  attackCount++;
}


for(int i=x+1,j=y-1; i<n&&j>=0 ; i++,j--)
 {
 if(arr[i][j]==2)
  break;

 if(arr[i][j]==1)
  attackCount++;
}


for(int i=x-1,j=y+1; i>=0&&j<n ; i--,j++)
 {
 if(arr[i][j]==2)
  break;
 
 if(arr[i][j]==1)
  attackCount++;
}

return attackCount;

}
 

//probablity calculator
int accept(double p){
 double r = distribution_real(generator_real);
 //cout<<"r is "<<r<<endl;
  if(r<p)
     return 1;
  return 0;
  
}


void set(int **arr1,int** arr2){
 
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      arr1[i][j]=arr2[i][j];
}

int sa(int **prev, int lizConflict){
   
 

            
   if(lizConflict==0){
   //	printArray(arr);
    return 1;
    }
    
 
  int **next = new int*[n];
	//pointer initialization
    for(int i=0;i<n;i++)
		next[i]=new int[n];

 default_random_engine generator;
 uniform_int_distribution<int> distribution(0,n-1);

 time_t start = time(NULL);
 
  while (1)
  {
   time_t timer = time(NULL);
// cout<<timer<<endl;
   double seconds = difftime(timer,start); 
    if( seconds > 280 )
     break;
   
 
   set(next,prev);
   
   //printArray(next);

  int i;
  int j;
  
   while(1){

     int x= distribution(generator);
     int y= distribution(generator); 
  
   if(next[x][y]==1){
    i = x;
    j = y;
   //  cout<<"i is: "<<i<<" j is "<<j<<endl;
      break;
      }
          
   }
   
 
   while(1){
 int x= distribution(generator);
     int y= distribution(generator); 
  
   if(next[x][y]==0){
    next[i][j]=0;
    next[x][y]=1;
      break;
      }
          
   }//endwhile
   
   
   int c=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        if(next[i][j]==1)
         c += conflict(next,i,j);  

    
   if(c==0){
    set(prev,next);
    return 1;
    }
    
    //good state always accepted
    if(c <= lizConflict)
    {
     set(prev,next);	
     lizConflict = c;
    }
    
    //accept bad state with decreasing probability
     else{
        
       T= 1/log(t) ;
            t++;
       double p = exp( (double)(( lizConflict - c   )/ T ) );
       // cout<<"prob : "<<p<<"T "<<T<<endl;
         
         if(accept(p)){
       // cout<<"accpt"<<endl;
        set(prev,next);	
        lizConflict = c;
         }
     
     }
   
   
   }//end of while(1)     
 
 // cout<<"TIMEOUT"<<endl;
    return 0;

}    


   

   
int main()
{

int method=0;

	
	string line;
	ifstream infile("input.txt");
	getline(infile,line);
	
	if(!line.compare("BFS"))
	 method=1;
    if(!line.compare("DFS"))
     method=2;
     if(!line.compare("SA"))
     method=3;
    
    getline(infile,line);
    n = stoi(line);
    
    getline(infile,line);
    p = stoi(line);
 
     int **a = new int*[n];
	//pointer initialization
    for(int i=0;i<n;i++)
		a[i]=new int[n];
    
    if (infile.is_open())
  { 
    int i=0;
    while ( getline (infile,line) )
    {
      for(int j=0;j<n;j++){
      char c = line[j];
      a[i][j] = (int)(c)-48;
      
      }         
     i++;
    } 
    infile.close();

  }
  
  
 ofstream outfile("output.txt");

    switch(method){
      
    case 1: {
         if(bfs(a)){
         //printArray(a);
         outfile<<"OK\n";

      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          outfile<<a[i][j];
          }
       if(i!=(n-1))
       outfile<<"\n";
          }     
         }
      else
     outfile<<"FAIL";
      break;
        }//endof case1
      
     case 2: {
     if(dfs(a)){
         outfile<<"OK\n";
      
      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          outfile<<a[i][j];
        }
       if(i!=(n-1))
       outfile<<"\n";
      }
      }
      
      else{
     outfile<<"FAIL";
      }
        break;
        }//endof case2
    
   case 3: {
     
    
    int lizard=0;
    
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0,n-1);
    
    
  
    while(1){
     int i= distribution(generator);
     int j= distribution(generator);
     if(a[i][j]==0){
       a[i][j]=1;  
       lizard++;
     }
     if(lizard==p)
      break;
     }
  
    int c=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
        if(a[i][j]==1)
         c += conflict(a,i,j);
     }    
    // cout<<"Conflict: "<<c<<endl;
     // printArray(a);
     if(sa(a,c)){
    outfile<<"OK\n";

      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          outfile<<a[i][j];
        }
       if(i!=(n-1))
       outfile<<"\n";
      }
      }
      
    else{   
     outfile<<"FAIL"; 
       }
       
     break;
        } //endofcase3
           
    default: {
         if(dfs(a)){
    outfile<<"OK\n";

      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          outfile<<a[i][j];
        }
       if(i!=(n-1))
       outfile<<"\n";
      }
      }
       else
     outfile<<"FAIL";  
       break;
        }
      
       }//endofswitch   
    
    outfile.close();   

      return 0;
}    
