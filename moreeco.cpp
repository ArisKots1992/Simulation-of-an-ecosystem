#include <iostream>
#include "classes.h"


using namespace std;






//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// RunEcosystem and relative functions ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Ecosystem::RunEcosystem(int days_of_simulation)

{
        int days_passed, hours;

        for(days_passed=1; days_passed<= days_of_simulation; days_passed++){

                if(!(days_passed%90)){
		   next_season();
                       ApplySeason();

			PrintSystem();
			PrintPlantStatistics();
			PrintAnimalStatistics();
		}

                DailyReset();  //

                for(hours=1; hours<=24; hours++){
                        AnimalMovement();
                       
                       AnimalEating();
                }

          
              CheckDeadEntities();
			CheckHunger();

             if(dayOfYear%herbivores_breedingRepPeriod == 0)
                     AnimalBreeding('H');
		     if(dayOfYear%carnivores_breedingRepPeriod == 0)
			         AnimalBreeding('C');
			
				if(plant_breedingRepPeriod)
					if(dayOfYear%plant_breedingRepPeriod == 0)
						   PlantBreeding();

                dayOfYear++;    /*the day just passed*/
        }
}




void Ecosystem::DailyReset()

{
	int i, j;

	for(i=0; i<terrainSize; i++)
		for(j=0; j<terrainSize; j++)
			terrain[i][j].reinitialize_hunger();	
        if(plant_growthPeriod){
		if( dayOfYear%plant_growthPeriod==0 ){

			for(i=0; i<terrainSize; i++)
				for(j=0; j<terrainSize; j++)
					if( terrain[i][j].get_pplant() != NULL )
						terrain[i][j].get_pplant()->grow();
		}
	}

	if( dayOfYear%animal_growthPeriod == 0 ){

		for(i=0; i<terrainSize; i++)
			for(j=0; j<terrainSize; j++)
				terrain[i][j].animal_grow();

	}
}



void Ecosystem::PlantBreeding()

{
        char **temp;
        int i, j;
        Plants *ptr;


        temp = new char*[terrainSize];
        for(i=0; i<terrainSize; i++){
                *(temp + i) = new char[terrainSize];
                for(j=0; j<terrainSize; j++)
                        *(*(temp + i)+j) = '-';
        }

        for(i=0; i<terrainSize; i++){

                for(j=0; j<terrainSize; j++){

                        ptr = (terrain[i][j]).get_pplant();
                        if( ptr != NULL ){      /*obviously only if there is a plant we check if it can breed*/

                                if( ptr->NormalBreeding() )     /*if the plant is capable of breeding, meaning it's not sick*/
                                        *(*(temp + i)+j) = FindFreeTile(ptr->get_token(), i, j, temp);  /*pass the result into a matrix in order to have*/
                                                                                                                /*immediate change*/
                        }
                }
        }



        for(i=0; i<terrainSize; i++){
                for(j=0; j<terrainSize; j++){
                        if((terrain[i][j]).get_pplant() != NULL)
                                switch (temp[i][j]){
                                        case 'l':       (terrain[i][j-1]).set_pplant((terrain[i][j]).get_pplant()->get_token());
                                                        break;
                                        case 'r':       (terrain[i][j+1]).set_pplant((terrain[i][j]).get_pplant()->get_token());
                                                        break;
                                        case 'd':       (terrain[i+1][j]).set_pplant((terrain[i][j]).get_pplant()->get_token());
                                                        break;
                                        case 'u':       (terrain[i-1][j]).set_pplant((terrain[i][j]).get_pplant()->get_token());
                                                        break;
                                }
                }

                delete[] *(temp + i);
        }

        delete[] temp;
}



bool Ecosystem::no_other_plant_left(int i, int j, char **temp)

{
        if( (j==1) || (temp[i][j-2] != 'r') )
                if( (i==0) || (temp[i-1][j-1] != 'd') )
                        if( (i == terrainSize - 1) || (temp[i+1][j-1] != 'u'))
                                return true;
        return false;
}


bool Ecosystem::no_other_plant_right(int i, int j, char **temp)

{
        if( (j == terrainSize - 2) || (temp[i][j+2] != 'l') )
                if( (i==0) || (temp[i-1][j+1] != 'd') )
                        if( (i == terrainSize - 1) || (temp[i+1][j+1] != 'u'))
                                return true;
        return false;
}


bool Ecosystem::no_other_plant_down(int i, int j, char **temp)

{
        if( (i == terrainSize - 2) || (temp[i+2][j] != 'u') )
                if( (j==0) || (temp[i+1][j-1] != 'r') )
                        if( (j == terrainSize - 1) || (temp[i+1][j+1] != 'l'))
                                return true;
        return false;
}


bool Ecosystem::no_other_plant_up(int i, int j, char **temp)

{
        if( (i==1) || (temp[i-2][j] != 'd') )
                if( (j==0) || (temp[i-1][j-1] != 'r') )
                        if( (j == terrainSize - 1) || (temp[i-1][j+1] != 'l'))
                                return true;
        return false;
}




char Ecosystem::FindFreeTile(char token, int i, int j, char **temp)

{
        switch (token){

                case 'G':       if(j>0){        /*inside the borders of the matrix*/
                                        if((terrain[i][j-1]).get_token() == '"')        /*if there is the appropriate terrain type*/
                                                if((terrain[i][j-1]).get_pplant() == NULL)      /*if there is no other plant there*/
                                                        if( no_other_plant_left(i, j, temp) )   /*if there is no other plant already been breeded in this tile*/
                                                                return 'l';
                                }
                                if( j < (terrainSize - 1)){
                                        if((terrain[i][j+1]).get_token() == '"')
                                                if((terrain[i][j+1]).get_pplant() == NULL)
                                                        if( no_other_plant_right(i, j, temp) )
                                                                return 'r';
                                }
                                if( i < (terrainSize - 1)){
                                        if((terrain[i+1][j]).get_token() == '"')
                                                if((terrain[i+1][j]).get_pplant() == NULL)
                                                        if( no_other_plant_down(i, j, temp) )
                                                                return 'd';
                                }
                                if(i>0){
                                        if((terrain[i-1][j]).get_token() == '"')
                                                if((terrain[i-1][j]).get_pplant() == NULL)
                                                        if( no_other_plant_up(i, j, temp) )
                                                                return 'u';
                                }

                                break;


                case 'A':       if(j>0){
                                        if((terrain[i][j-1]).get_token() == '#')
                                                if((terrain[i][j-1]).get_pplant() == NULL)
                                                        if( no_other_plant_left(i, j, temp) )
                                                                return 'l';
                                }
                                if( j < (terrainSize - 1)){
                                        if((terrain[i][j+1]).get_token() == '#')
                                                if((terrain[i][j+1]).get_pplant() == NULL)
                                                        if( no_other_plant_right(i, j, temp) )
                                                                return 'r';
                                }
                                if( i < (terrainSize - 1)){
                                        if((terrain[i+1][j]).get_token() == '#')
                                                if((terrain[i+1][j]).get_pplant() == NULL)
                                                        if( no_other_plant_down(i, j, temp) )
                                                                return 'd';
                                }
                                if(i>0){
                                        if((terrain[i-1][j]).get_token() == '#')
                                                if((terrain[i-1][j]).get_pplant() == NULL)
                                                        if( no_other_plant_up(i, j, temp) )
                                                                return 'u';
                                }

                                break;


                case 'M':       if(j>0){
                                        if((terrain[i][j-1]).get_token() != '#')
                                                if((terrain[i][j-1]).get_pplant() == NULL)
                                                        if( no_other_plant_left(i, j, temp) )
                                                                return 'l';
                                }
                                if( j < (terrainSize - 1)){
                                        if((terrain[i][j+1]).get_token() != '#')
                                                if((terrain[i][j+1]).get_pplant() == NULL)
                                                        if( no_other_plant_right(i, j, temp) )
                                                                return 'r';
                                }
                                if( i < (terrainSize - 1)){
                                        if((terrain[i+1][j]).get_token() != '#')
                                                if((terrain[i+1][j]).get_pplant() == NULL)
                                                        if( no_other_plant_down(i, j, temp) )
                                                                return 'd';
                                }
                                if(i>0){
                                        if((terrain[i-1][j]).get_token() != '#')
                                                if((terrain[i-1][j]).get_pplant() == NULL)
                                                        if( no_other_plant_up(i, j, temp) )
                                                                return 'u';
                                }

                                break;


                case 'O':       if(j>0){
                                        if((terrain[i][j-1]).get_token() == '"' )
                                                if((terrain[i][j-1]).get_pplant() == NULL)
                                                        if( no_other_plant_left(i, j, temp) )
                                                                return 'l';
                                }
                                if( j < (terrainSize - 1)){
                                        if((terrain[i][j+1]).get_token() == '"')
                                                if((terrain[i][j+1]).get_pplant() == NULL)
                                                        if( no_other_plant_right(i, j, temp) )
                                                                return 'r';
                                }
                                if( i < (terrainSize - 1)){
                                        if((terrain[i+1][j]).get_token() == '"')
                                                if((terrain[i+1][j]).get_pplant() == NULL)
                                                        if( no_other_plant_down(i, j, temp) )
                                                                return 'd';
                                }
                                if(i>0){
                                        if((terrain[i-1][j]).get_token() == '"')
                                                if((terrain[i-1][j]).get_pplant() == NULL)
                                                        if( no_other_plant_up(i, j, temp) )
                                                                return 'u';
                                }

                                break;


                case 'P':       if(j>0){
                                        if((terrain[i][j-1]).get_token() == '^' || (terrain[i][j-1]).get_token() == '"')
                                                if((terrain[i][j-1]).get_pplant() == NULL)
                                                        if( no_other_plant_left(i, j, temp) )
                                                                return 'l';
                                }
                                if( j < (terrainSize - 1)){
                                        if((terrain[i][j+1]).get_token() == '^' || (terrain[i][j+1]).get_token() == '"')
                                                if((terrain[i][j+1]).get_pplant() == NULL)
                                                        if( no_other_plant_right(i, j, temp) )
                                                                return 'r';
                                }
                                if( i < (terrainSize - 1)){
                                        if((terrain[i+1][j]).get_token() == '^' || (terrain[i+1][j]).get_token() == '"')
                                                if((terrain[i+1][j]).get_pplant() == NULL)
                                                        if( no_other_plant_down(i, j, temp) )
                                                                return 'd';
                                }
                                if(i>0){
                                        if((terrain[i-1][j]).get_token() == '^' || (terrain[i-1][j]).get_token() == '"')
                                                if((terrain[i-1][j]).get_pplant() == NULL)
                                                        if( no_other_plant_up(i, j, temp) )
                                                                return 'u';
                                }

                                break;

        }

        return 'n';

}
void Ecosystem::AnimalBreeding(char ch)

{
	int i, j;

	for(i=0; i<terrainSize; i++)
		for(j=0; j<terrainSize; j++){

			if( ch == 'H')
				terrain[i][j].herbivores_breed();
			else if( ch == 'C')
				terrain[i][j].carnivores_breed();
		}
}
void Ecosystem::AnimalMovement(){
	int i,j,k;
	for(i=0;i<terrainSize;i++){
		for(j=0;j<terrainSize;j++){
			
			for(k=0;k<7;k++) terrain[i][j].call_move_animals(*this,k);
							      }
                              }


								} 
void Ecosystem::AnimalEating(){
	int i,j;
	for(i=0;i<terrainSize;i++){
		for(j=0;j<terrainSize;j++){

			
			terrain[i][j].eat_animals();
							      }
                              }


								} 	
void Ecosystem::CheckDeadEntities()

{
	int i, j;

	for(i=0; i<terrainSize; i++)
		for(j=0; j<terrainSize; j++){

			if( terrain[i][j].get_pplant() != NULL)
				if( terrain[i][j].get_pplant()->get_life() == 0)	/* remove plant if it is dead */
					terrain[i][j].remove_plant();

			terrain[i][j].remove_dead_animals();

	}
}



void Ecosystem::CheckHunger()

{
	int i, j;

	for(i=0; i<terrainSize; i++)
		for(j=0; j<terrainSize; j++)
			terrain[i][j].check_hunger();

}
////////////////////////////////////////////////////////////////////
////////////////////  print functions //////////////////////////////
////////////////////////////////////////////////////////////////////



void Ecosystem::PrintSystem()

{
	int i, j, k;
	int num_plants, num_animals, num_herbivores, num_carnivores;
	List **list;

	cout << "\033[1;37m Day of simulation\t"<< dayOfYear+1 <<"\033[0m"<<endl<<endl;

	num_plants = 0;
	num_animals = 0;
	num_herbivores = 0;
	num_carnivores = 0;

        for(i=0; i<terrainSize; i++){
                for(j=0; j<terrainSize; j++){
                        if(terrain[i][j].get_pplant() == NULL){  //enxromh ektiposh
                        	if(terrain[i][j].get_token() == '#'){
                               cout << "\033[1;35m "<< terrain[i][j].get_token()<<"\033[0m" ;
															   }
							else if(terrain[i][j].get_token() == '"'){	
			                  cout << "\033[1;33m "<< terrain[i][j].get_token()<<"\033[0m" ;															   
														             }
							else if(terrain[i][j].get_token()=='^'){
						      cout << "\033[1;37m "<< terrain[i][j].get_token()<<"\033[0m" ;
						                                          }
															  }  											             
                        else{			/* evaluate plants */
				num_plants++;
				             if(terrain[i][j].get_token() == '#'){
                                cout << "\033[1;35m "<<  terrain[i][j].get_pplant()->get_token()<<"\033[0m" ;
																		       }
							else if(terrain[i][j].get_token() == '"')	{
							cout << "\033[1;33m "<< terrain[i][j].get_pplant()->get_token()<<"\033[0m" ; 	
																	}
							else if(terrain[i][j].get_token() == '^'){
								 cout << "\033[1;37m "<<terrain[i][j].get_pplant()->get_token()<<"\033[0m" ;	
																}								       
			}

			list = (terrain[i][j]).get_panimals();
			for(k=0; k<7; k++){
				num_animals += (*(list + k))->size();	/* evaluate animals */
				if(k<4)
					num_herbivores += (*(list + k))->size();	/* evaluate herbivores */
				else
					num_carnivores += (*(list + k))->size();	/* evaluate carnivores */
			}
                }
                cout << endl;
        }
	cout << "\n\n";

	cout << "Ecosystem Statistics:\n\n";

	cout << "\tNumber of plants:\t\t" << num_plants << endl;
	cout << "\tTotal number of animals:\t" << num_animals << endl;
	cout << "\tNumber of herbivore animals:\t" << num_herbivores << endl;
	cout << "\tNumber of carnivore animals:\t" << num_carnivores << endl<<endl;
}


void Ecosystem::PrintPlantStatistics()

{
	char ch;
	int i, j;
	int num_grass, num_algae, num_maple, num_oak, num_pine;

	num_grass = num_algae = num_maple = num_oak = num_pine = 0;

	for(i=0; i<terrainSize; i++)
		for(j=0; j<terrainSize; j++){

			if(terrain[i][j].get_pplant() != NULL){
				ch = terrain[i][j].get_pplant()->get_token();

				switch (ch){
					case 'G':	num_grass++;
							break;
					case 'A':	num_algae++;
							break;
					case 'M':	num_maple++;
							break;
					case 'O':	num_oak++;
							break;
					case 'P':	num_pine++;
							break;
				}
			}
		}

	cout << "Plant Statistics:\n\n";

	cout << "\tTotal number of grasses:\t" << num_grass << endl;
	cout << "\tTotal number of algaes:\t\t" << num_algae << endl;
	cout << "\tTotal number of maples:\t\t" << num_maple << endl;
	cout << "\tTotal number of oaks:\t\t" << num_oak << endl;
	cout << "\tTotal number of pines:\t\t" << num_pine << endl;

	cout << "\n\n\n";
}


void Ecosystem::PrintAnimalStatistics()

{
	int i, j;
	int num_deer, num_rabbit, num_groundhog, num_salmon, num_fox, num_wolf, num_bear;
	List **list;

	num_deer = num_rabbit = num_groundhog = num_salmon = num_fox = num_wolf = num_bear = 0;

	for(i=0; i<terrainSize; i++)
		for(j=0; j<terrainSize; j++){

			list = (terrain[i][j]).get_panimals();

			num_deer += (list[0])->size();
			num_rabbit += (list[1])->size();
			num_groundhog += (list[2])->size();
			num_salmon += (list[3])->size();
			num_fox += (list[4])->size();
			num_wolf += (list[5])->size();
			num_bear += (list[6])->size();
		}

	cout << "Animal Statistics:\n\n";

        cout << "\tTotal number of deer:\t\t" << num_deer << endl;
        cout << "\tTotal number of rabbits:\t" << num_rabbit << endl;
        cout << "\tTotal number of groundhogs:\t" << num_groundhog << endl;
        cout << "\tTotal number of salmons:\t" << num_salmon << endl;
        cout << "\tTotal number of foxes:\t\t" << num_fox << endl;
	cout << "\tTotal number of wolfs:\t\t" << num_wolf << endl;
	cout << "\tTotal number of bears:\t\t" << num_bear << endl;

	cout << "\n\n\n";
}
	
	
