#include <iostream>
#include <ctime>
#include <cstdio>
#include "classes.h"

using namespace std;

int main(int argc,char *argv[])

{
   int i, j, terrainsize, num, table_plant[5],table_animal[7];
	char t;
	bool input=false;
	string def="-manual";
	string season="winter";
    int days=360;

	if(argc!=1)
	  if (argv[1]==def)
	     input=true;

if(input==true){
cout<<"terrain size: ";
	cin >> terrainsize;
do{
cout<<"\nnumber of hills: ";
	cin >> num;
   }while(num<=0);
do{
cout<<"Give season: ";
    cin >> season;
  }while(season != "spring" && season!="winter" && season!="autumn" && season!="summer");
do{
  cout<<"Give days of simulation: ";
    cin >> days;
}while(days<=0);
cout<<"|====Plants Insert====|"<<endl;
	cout<<"number of grasses: ";  cin >> table_plant[0];
    cout<<"number of algaes: ";   cin >> table_plant[1];
    cout<<"number of maples: ";   cin >> table_plant[2];
    cout<<"number of oaks: ";     cin >> table_plant[3];
    cout<<"number of pines: ";    cin >> table_plant[4];
cout<<"|====Animals Insert====|"<<endl;
	cout<<"Number of Deers: ";    cin >> table_animal[0];
	cout<<"Number of Rabbits: ";  cin >> table_animal[1];
	cout<<"Number of Groundhogs: ";cin >> table_animal[2]; 
	cout<<"Number of Salmons: "; cin >> table_animal[3];
	cout<<"Number of Foxes: ";   cin >> table_animal[4];
	cout<<"Number of Wolves: ";  cin >> table_animal[5];
	cout<<"Number of Bears: ";   cin >> table_animal[6];
	cout<<"press Enter to start";t=getchar();t=getchar();						   
	                   }
	else{
		terrainsize=30;
	    num=10;
        table_plant[0]=100;
        table_plant[1]=190;
        table_plant[2]=100;
        table_plant[3]=100;
        table_plant[4]=100;

        table_animal[0]=10;
        table_animal[1]=350;
        table_animal[2]=100;
        table_animal[3]=10;
        table_animal[4]=30;
        table_animal[5]=45;
        table_animal[6]=30;
}
srand(time(NULL));

	Ecosystem* ptr = new Ecosystem(terrainsize, season, num, table_plant, table_animal);
	cout<<endl;
 cout << "\033[1;37m                   Terrain without Plants\033[0m"<<endl<<endl;
	for(i=0; i<terrainsize; i++){	/* this is how the terrain looks like without plants */
		for(j=0; j<terrainsize; j++){
			if (ptr->get_terrain()[i][j].get_token() == '#')
			  cout << "\033[1;35m "<< ptr->get_terrain()[i][j].get_token()<<"\033[0m" ;
			else if( ptr->get_terrain()[i][j].get_token() == '"')
			  cout << "\033[1;33m "<< ptr->get_terrain()[i][j].get_token()<<"\033[0m" ;
			else
			  cout << "\033[1;37m "<< ptr->get_terrain()[i][j].get_token()<<"\033[0m" ;  
		}
		cout << endl;
	}
	cout << "\n\n\n";
   ptr->PrintSystem();
   	cout << "\n\n\n";
   ptr->PrintAnimalStatistics();
   ptr->PrintPlantStatistics();
   
   
   ptr->RunEcosystem(days);

return 0;
}
