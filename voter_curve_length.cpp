# include <stdio.h>
# include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>


using namespace std;



int main(int argc, char* argv[]){

	int n = atoi(argv[1]);
	
	
	int i,j;
		
	int lattice [n+2][n+2];
	
	string line;
	std::string filename1 = "config_size_";
	std::string filename2 = argv[1];
	std::string filename3 = "_job_";
	std::string filename4 = argv[2];
	std::string filename5 = ".dat";
	std::string filename = filename1+filename2+filename3+filename4+filename5;
	const char * name = filename.c_str();
	ifstream config (name);
		
	if (config.is_open()){
		i=0;
		getline (config,line);
		for (j=0;j<=n+1;j++){
				lattice[i][j] =(int)line[2*j]-48;
			}
		while ( getline (config,line) ){
			i++;
			for (j=0;j<=n+1;j++){
				lattice[i][j] =(int)line[2*j]-48;
			}
		}
		config.close();
	}
	else cout << "Unable to open file"; 

// now compute the length of the boundary
	
	
// now run boundary walk until hits {n,n,0}
	int curve[2*(n+1)][2*(n+1)]; 	//array to hold the curve with values 1
	
	
	
	for(i=0;i<2*(n+1);i++){
		for(j=0;j<2*(n+1);j++){
			curve[i][j]=0;
		}
	}
	curve[0][0]=1; // initial segment of the curve
	curve[1][1]=2;

	
	int pw[3] = {0,0,0};     // previous position of the boundary walker
	int cw[3] = {0,0,1}; 	 // current position of the boundary walker
	int curveLength = 2;

	while(cw[0]!=n || cw[1]!=n ){
		switch(cw[2]){
			case 0:
				if(lattice[cw[0]][cw[1]]!=lattice[cw[0]+1][cw[1]]){
					if(lattice[cw[0]][cw[1]]!=lattice[cw[0]][cw[1]+1]){
						if(cw[1]-1 == pw[1]){
							pw[0]=cw[0]; pw[1]=cw[1]; pw[2]=cw[2];
							cw[0]=cw[0]-1;cw[2]=1;
							curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
						} 
						else{
							pw[0]=cw[0]; pw[1]=cw[1];
							cw[1]= cw[1]-1;cw[2]= 1;
							curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
						}
					}
					else{
						if(cw[1]-1 == pw[1]){
							pw[0]=cw[0]; pw[1]=cw[1]; pw[2]=cw[2];
							cw[2]=1;
							curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
						} 
						else{
							pw[0]=cw[0]; pw[1]=cw[1];
							cw[1]= cw[1]-1;cw[2]= 1;
							curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
						}
					}
	
				}
				else{
					if(cw[0]-1 == pw[0]){
						pw[0]=cw[0]; pw[1]=cw[1]; pw[2]=cw[2];
						cw[2]=1;
						curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
					}
					else{
						pw[0]=cw[0]; pw[1]=cw[1]; pw[2]=cw[2];
						cw[0]= cw[0]-1; cw[2]=1;
						curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
					}
				}
			break;
			
			case 1:
				if(lattice[cw[0]+1][cw[1]+1] != lattice[cw[0]][cw[1]+1]){
					if(lattice[cw[0]+1][cw[1]+1] != lattice[cw[0]+1][cw[1]]){
						if( cw[1]+1==pw[1]){
							pw[0]=cw[0]; pw[1]=cw[1]; pw[2]=cw[2];
							cw[0] = cw[0]+1; cw[2]=0;
							curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
						}
						else{
							pw[0]=cw[0]; pw[1]=cw[1]; pw[2]=cw[2];
							cw[1]=cw[1]+1; cw[2]=0;
							curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
						}
					}
					else{
						if( cw[1]+1==pw[1]){
							pw[0]=cw[0]; pw[1]=cw[1]; pw[2]=cw[2];
							cw[2]=0;
							curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
						}
						else{
							pw[0]=cw[0]; pw[1]=cw[1]; pw[2]=cw[2];
							cw[1]=cw[1]+1; cw[2]=0;
							curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
						}
					}
				}
				else{
					if(cw[0]+1==pw[0]){
						pw[0]=cw[0]; pw[1]=cw[1]; pw[2]=cw[2];
						cw[2]=0;
						curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
					}
					else{
						pw[0]=cw[0]; pw[1]=cw[1]; pw[2]=cw[2];
						cw[0]=cw[0]+1; cw[2]=0;
						curve[2*cw[0]+cw[2]][2*cw[1]+cw[2]] = curveLength+1;
					}
				}
			break;
		}
		
		curveLength++;
	}
	curve[2*n+1][2*n+1]=curveLength+1;
	
	
	
	
	ofstream interfacecurve;
	std::string title1 = "curve_size_";
	std::string title2 = title1+filename2+filename3+filename4+filename5;
	const char * titlecurve = title2.c_str();
	interfacecurve.open (titlecurve);
	for(i=0;i<2*(n+1);i++){
		for(j=0;j<2*(n+1);j++){
			interfacecurve << curve[i][j];
			interfacecurve << " ";
		}
		interfacecurve << endl;
	}
	interfacecurve.close();


	ofstream result;
	std::string title3 = "length_size_";
	std::string title4 = title3+filename2+filename3+filename4+filename5;
	const char * titlelength = title4.c_str();
	result.open (titlelength);
			result << curveLength << endl;
	result.close();
	
	
return 0;
}









