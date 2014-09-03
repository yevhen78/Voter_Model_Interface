# include <stdio.h>
# include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>



using namespace std;


struct  stackNode {
		int data;
		struct stackNode *next;
	};
		
	typedef stackNode *stackNodePtr;
		
	void push(stackNode **top, int info);
	void move(stackNode **to_first, stackNode **from_last, stackNode **from_first, stackNode **to_last);
	int pop(stackNode **top);
	int isEmpty (stackNode *top);		
	
	unsigned int get_seed() {
	unsigned int seed;
	FILE *urandom = fopen ("/dev/urandom", "r");
	if (urandom == NULL) {
		fprintf (stderr, "Cannot open /dev/urandom!\n");
		exit (1);
	}
	fread (&seed, sizeof(seed), 1, urandom);
	return seed;
	}	



int main(int argc, char* argv[])
{
	// first run random walks untill reach boundary
	int n = atoi(argv[1]);
	
	
	
			
	stackNode *location_first[n][n];	// array of pointers to first nodes of stacks of voters in each location of the lattice
	stackNode *location_last[n][n];		// array of pointers to last nodes of stacks of voters in each location of the lattice
	stackNode *b_last = NULL;
	stackNode *w_last = NULL;
		 
	
	int counter[n][n]; 	//counters of each location position
	int bc=0;        		//counter of black array
	int wc=0;	     		//counter of black array
	int i,j;
	int configuration[n][n]; //resulting configuration colored in 0 for white and 1 for black 
	int coalescing_sets[n][n];
	int coalescing_counter=0;
	
	int x;					// position of random flip
	int y;
	int x_temp;				// position of a voter writen in coalescing_sets array
	int y_temp;
	int step;				// holds random step
	int temp;				//temporary storage variable
	int flag=0;
	

	unsigned int seed = get_seed();
	srand (seed);

	
	bc=0;        		
	wc=0;
	coalescing_counter=0;
	flag=0;	
	
//initialize location to having each voter in its corresponding location
	for(i=0; i< n; i++){
		for(j=0; j<n; j++){
			location_first[i][j]= NULL;
			location_last[i][j]= location_first[i][j];
			push(&(location_last[i][j]),j*n+i);
			location_first[i][j]=location_last[i][j];
			counter[i][j] = 1;
			coalescing_sets[i][j] = 0;
		}
	}
	
		
//run voter model

	
	while ( bc+wc < n*n ){
		
//chose random location for a step
		x = rand() % n;
		y = rand() % n;
		
// chose random direction 
		step = ( rand() % 6 );
		
// move all walkers from (x,y) to (x,y)+step
		switch( step ){
			case 0:
				if (x-1 == -1) {
					// move to w
					while(!(isEmpty(location_last[x][y]))){
						temp = pop(&location_last[x][y]);
						push(&w_last, temp);
						wc += counter[x][y];
						counter[x][y] = 0;
						if(flag==0){
							flag=1;
							coalescing_counter ++;
						}
						x_temp = temp%n;
						y_temp = temp/n;
						coalescing_sets[x_temp][y_temp] = coalescing_counter;
						
					}
					flag = 0;
				}
				else{
					// move to (x-1,y)
					if(!(isEmpty(location_last[x][y]))){
						move(&location_first[x-1][y],&location_last[x-1][y],&location_first[x][y],&location_last[x][y]);	// move value
						counter[x-1][y] += counter[x][y];
						counter[x][y] = 0;
					}
				}
				break;
				
			case 1:
				if (x-1 == -1 || y+1 == n) {
					// move to w
					while(!(isEmpty(location_last[x][y]))){
						temp = pop(&location_last[x][y]);
						push(&w_last, temp);
						wc += counter[x][y];
						counter[x][y] = 0;
						if(flag==0){
							flag=1;
							coalescing_counter ++;
						}
						x_temp= temp%n;
						y_temp = temp/n;
						coalescing_sets[x_temp][y_temp] = coalescing_counter;
						
					}
					flag = 0;
				}
				else{
					// move to (x-1, y+1)
					if(!(isEmpty(location_last[x][y]))){
						move(&location_first[x-1][y+1],&location_last[x-1][y+1],&location_first[x][y],&location_last[x][y]);	// move value
						counter[x-1][y+1] += counter[x][y];
						counter[x][y] = 0;
					}
				}
				break;
				
			case 2:
				if (y+1 == n) {
					// move to w
					while(!(isEmpty(location_last[x][y]))){
						temp = pop(&location_last[x][y]);
						push(&w_last, temp);
						wc += counter[x][y];
						counter[x][y] = 0;
						if(flag==0){
							flag=1;
							coalescing_counter ++;
						}
						x_temp = temp%n;
						y_temp = temp/n;
						coalescing_sets[x_temp][y_temp] = coalescing_counter;
						
					}
					flag = 0;
				}
				else{
					// move to (x, y+1)
					if(!(isEmpty(location_last[x][y]))){
						move(&location_first[x][y+1],&location_last[x][y+1],&location_first[x][y],&location_last[x][y]);	// move value
						counter[x][y+1] += counter[x][y];
						counter[x][y] = 0;
					}
				}
				break;
				
			case 3:
				if (x+1 == n ) {
					// move to b
					while(!(isEmpty(location_last[x][y]))){
						temp = pop(&location_last[x][y]);
						push(&b_last, temp);
						bc += counter[x][y];
						counter[x][y] = 0;
						if(flag==0){
							flag=1;
							coalescing_counter ++;
						}
						x_temp = temp%n;
						y_temp = temp/n;
						coalescing_sets[x_temp][y_temp] = coalescing_counter;
						
					}
					flag = 0;
				}
				else{
					// move to (x+1, y)
					if(!(isEmpty(location_last[x][y]))){
						move(&location_first[x+1][y],&location_last[x+1][y],&location_first[x][y],&location_last[x][y]);	// move value
						counter[x+1][y] += counter[x][y];
						counter[x][y] = 0;
					}
				}
				break;	
				
			case 4:
				if (x+1 == n || y-1 == -1) {
					// move to b
					while(!(isEmpty(location_last[x][y]))){
						temp = pop(&location_last[x][y]);
						push(&b_last, temp);
						bc += counter[x][y];
						counter[x][y] = 0;
						if(flag==0){
							flag=1;
							coalescing_counter ++;
						}
						x_temp = temp%n;
						y_temp = temp/n;
						coalescing_sets[x_temp][y_temp] = coalescing_counter;
						
					}
					flag = 0;
				}
				else{
					// move to (x+1, y-1)
					if(!(isEmpty(location_last[x][y]))){
						move(&location_first[x+1][y-1],&location_last[x+1][y-1],&location_first[x][y],&location_last[x][y]);	// move value
						counter[x+1][y-1] += counter[x][y];
						counter[x][y] = 0;
					}
				}
				break;
				
			case 5:
				if (y-1 == -1) {
					// move to b
					while(!(isEmpty(location_last[x][y]))){
						temp = pop(&location_last[x][y]);
						push(&b_last, temp);
						bc += counter[x][y];
						counter[x][y] = 0;
						if(flag==0){
							flag=1;
							coalescing_counter ++;
						}
						x_temp = temp%n;
						y_temp = temp/n;
						coalescing_sets[x_temp][y_temp] = coalescing_counter;
						
					}
					flag = 0;
				}
				else{
					// move to (x, y-1)
					if(!(isEmpty(location_last[x][y]))){
						move(&location_first[x][y-1],&location_last[x][y-1],&location_first[x][y],&location_last[x][y]);	// move value
						counter[x][y-1] += counter[x][y];
						counter[x][y] = 0;
					}
				}
				break;
		}
	}
	
	
// now recover configuration from b, and w queues
	
	while(!(isEmpty(b_last))){
		
		temp = pop(&b_last);
		x = temp%n;
		y = temp/n;
	
		configuration[x][y] = 1;
		bc--;
	}
	
	while(!(isEmpty(w_last))){
		
		temp = pop(&w_last);
		x = temp%n;
		y = temp/n;
	
		configuration[x][y] = 0;
		wc--;
	}

	int lattice[n+2][n+2];	 // configuration with the boundary
		
	for( i=0;i<=n+1;i++){
		lattice[i][0] = 1;
		lattice[i][n+1] = 0;
	}
	
	for( j=1;j<=n;j++){
		lattice[0][j] = 0;
		lattice[n+1][j] = 1;
	}
	
	for( i=1;i<=n;i++){
		for( j=1;j<=n;j++){
			lattice[i][j] = configuration[i-1][j-1];
		}
	}



// output the config and coalescing 		
	
	
	ofstream config;
	std::string title1 = "config_size_";
	std::string title2 = argv[1];
	std::string title3 = "_job_";
	std::string title4 = argv[2];
	std::string title5 = ".dat";
	std::string titleconf = title1+title2+title3+title4+title5;
	const char * titleconfig = titleconf.c_str();
	config.open (titleconfig);
	for(i=0; i<=n+1; i++){
		for(j=0; j<=n+1; j++){
			config << lattice[i][j];
			config << " ";
		}
		config << endl;
	}
	config.close();
	
	
	ofstream coalesc;
	std::string title6 = "coalesc_size_";
	std::string titlecoal = title6+title2+title3+title4+title5;
	const char * titlecoalesc = titlecoal.c_str();
	coalesc.open (titlecoalesc);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			coalesc << coalescing_sets[i][j];
			coalesc << " ";
		}
		coalesc << endl;
	}
	coalesc.close();

return 0;
}









void push( stackNode *(*top), int info){
	stackNode *newPtr;
	newPtr = (stackNode *)malloc(sizeof(stackNode));
	
	if(newPtr != NULL){
		newPtr->data = info;
		newPtr->next = *top;
		*top = newPtr;
	}
	else{
		cout << "Out of memory!";
	}
}

void move(stackNode **to_first, stackNode **to_last, stackNode **from_first, stackNode **from_last){
	if(*to_last != NULL){
		(*from_first)->next = *to_last;
		*to_last = *from_last;
		*from_first = NULL;
		*from_last = NULL;
	}
	else{
		(*from_first)->next = *to_last;
		*to_last = *from_last;
		*to_first = *from_first;
		*from_first = NULL;
		*from_last = NULL;
	}
}


int pop( stackNodePtr *top ){
	stackNodePtr tempNode;
	int popValue;
	
	tempNode = *top;
	popValue = (*top)->data;
	*top = (*top)->next;
	free(tempNode);
	
	return popValue;
}

int isEmpty( stackNodePtr top)
{
	return top == NULL;
}
