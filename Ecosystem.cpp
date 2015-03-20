#include <iostream>
#include <string>
#include "classes.h"


using namespace std;

Ecosystem::Ecosystem(int terrainSize_, string season_, int num_of_hills, int *num_of_plants, int *num_of_animals) 
	:	terrainSize(terrainSize_), season(season_)

{
	int i, j;

	terrain = new Tile*[terrainSize];	/*create the terrain*/
	for(i=0; i<terrainSize; i++)
		*(terrain + i ) = new Tile[terrainSize];

	for(i=0; i<terrainSize; i++)
		for(j=0; j<terrainSize; j++)
			(terrain[i][j]).set_p(i,j);

	MapGenerator(num_of_hills);

	PlacePlants(num_of_plants);
	PlaceAnimals(num_of_animals);

	ApplySeason();

}

//destructor
Ecosystem::~Ecosystem()

{
	int i;

	for(i=0; i<terrainSize; i++)
		delete[] *(terrain + i);
	delete[] terrain;

}
void Ecosystem::next_season()

{
	if(season == "spring")
		season = "summer";
	else if(season == "summer")
		season = "autumn";
	else if(season == "autumn")
		season = "winter";
	else if(season == "winter")
		season = "spring";
}


void Ecosystem::ApplySeason()

{
	int i, j;

	if(season == "spring"){
		plant_growthPeriod = 5;
		animal_growthPeriod = 20;
		plant_breedingRepPeriod = 10;
		herbivores_breedingRepPeriod = 12;
		carnivores_breedingRepPeriod = 11;

		/* animals in hibernation wake up */
		for(i=0; i<terrainSize; i++)
			for(j=0; j<terrainSize; j++)
				(terrain[i][j]).set_in_hibernation(false);
	}
	else if(season == "summer"){
		plant_growthPeriod = 10;
		animal_growthPeriod = 30;
		plant_breedingRepPeriod = 10;
		herbivores_breedingRepPeriod = 8;
		carnivores_breedingRepPeriod = 9;
	}
	else if(season == "autumn"){
		plant_growthPeriod = 0;
		animal_growthPeriod = 15;
		plant_breedingRepPeriod = 20;
		herbivores_breedingRepPeriod = 5;
		carnivores_breedingRepPeriod = 9;
	}
	else if(season == "winter"){
		plant_growthPeriod = 10;
		animal_growthPeriod = 30;
		plant_breedingRepPeriod = 0;
		herbivores_breedingRepPeriod = 18;
		carnivores_breedingRepPeriod = 10;

		/* animals fall in hibernation */
		for(i=0; i<terrainSize; i++)
			for(j=0; j<terrainSize; j++)
				(terrain[i][j]).set_in_hibernation(true);
	}

}


void Ecosystem::MapGenerator(int num_of_hills)

{
	GenerateRiver();
	GenerateLake();
	GenerateHills(num_of_hills);
	GenerateMeadow();
}


void Ecosystem::GenerateRiver()

{
	int i, y, possibility;

	y = rand()%(terrainSize - 11) + 5;	/*a number in [5, terrainSize - 5]*/

	for(i=0; i<terrainSize; i++){
		if(!i)
			(terrain[0][y]).set_token('#');
		else{
			(terrain[i][y]).set_token('#');

			possibility = rand()%10 + 1;	/*an number from 1 to 10*/
			if(possibility <= 3){

				if(y == terrainSize - 2){	/*river can go only left*/

					possibility = rand()%2;
					switch (possibility){
						case 0: y--;
							break;
						case 1: y -= 2;
							(terrain[i][y+1]).set_token('#');
							break;
					}
					(terrain[i][y]).set_token('#');

				}
				else if(y == terrainSize - 3){		/*river can go left but only one tile right*/

					possibility = rand()%3;
					switch (possibility){
						case 0: y--;
							break;
						case 1:	y -= 2;
							(terrain[i][y+1]).set_token('#');
							break;
						case 2:	y++;
							break;
					}
					(terrain[i][y]).set_token('#');

				}
				else if(y == 1){	/*river can go only right*/

					possibility = rand()%2;
					switch (possibility){
						case 0:	y++;
							break;
						case 1:	y += 2;
							(terrain[i][y-1]).set_token('#');
							break;
					}
					(terrain[i][y]).set_token('#');

				}
				else if(y ==2){		/*river can go right but only one tile left*/

					possibility = rand()%3;
					switch (possibility){
						case 0: y--;
							break;
						case 1:	y++;
							break;
						case 2:	y += 2;
							(terrain[i][y-1]).set_token('#');
							break;
					}
					(terrain[i][y]).set_token('#');

				}
				else{		/*river can go everywere*/

					possibility = rand()%4;
					switch (possibility){
						case 0:	y--;
							break;

						case 1: y -= 2;
							(terrain[i][y+1]).set_token('#');
							break;

						case 2:	y++;
							break;

						case 3:	y += 2;
							(terrain[i][y-1]).set_token('#');
							break;

					}
					(terrain[i][y]).set_token('#');
				}
			}
		}

	}


}


void Ecosystem::GenerateLake()

{
	int lakeSize = rand()%(terrainSize/2 - 1) + 2;		/*lakesize in [2, [terrainSize/2]]*/
	int i, j, x, y;

	x = rand()%(terrainSize/2);
	y = rand()%(terrainSize/2);

	for(i=x; i<x+lakeSize; i++)
		for(j=y; j<y+lakeSize; j++)
			(terrain[i][j]).set_token('#');
}


int Ecosystem::GenerateHills(int num_of_hills)

{
	int i, j, x, y, size, hills_not_placed = 0;

	while(num_of_hills--){
		size = rand()%3 + 2;	/*size in [2,4]*/

		

		if(available_position(size)){
			do{
				x = rand()%(terrainSize - size + 1);
				y = rand()%(terrainSize - size + 1);

			}while(!available_position(x, y, size));

			

			for(i=x; i<x+size; i++)
				for(j=y; j<y+size; j++)
					(terrain[i][j]).set_token('^');

		}
		else
			hills_not_placed++;
	}

	return hills_not_placed;
}


void Ecosystem::GenerateMeadow()

{
	int i, j;

	for(i=0; i<terrainSize; i++)
		for(j=0; j<terrainSize; j++)
			if((terrain[i][j]).get_token() == '-')
				(terrain[i][j]).set_token('"');		/*everything left turns into meadow*/
}



bool Ecosystem::available_position(int size)

{
	bool flag;
	int i, j, ii, jj;

	for(i=0; i<=terrainSize-size; i++){
		for(j=0; j<=terrainSize-size; j++){

			flag = true;

			for(ii=i; ii<i+size; ii++){
				for(jj=j; jj<j+size; jj++){
					if((*(*(terrain + ii) + jj)).get_token() != '-'){
						flag = false;
						break;
					}
				}
				if(!flag)
					break;
			}

			if(flag){
				return true;
			}
		}

	}

	return flag;
}


bool Ecosystem::available_position(int x, int y, int size)

{
	bool flag = true;
	int i, j;

	if((x > terrainSize - size) || (y > terrainSize - size))
		return false;

	for(i=x; i<x+size; i++){
		for(j=y; j<y+size; j++){
			if((*(*(terrain + i) + j)).get_token() != '-'){
				flag = false;
				break;
			}
		}
		if(!flag)
			break;
	}

	return flag;
}





void Ecosystem::PlacePlants(int *table)

{
	int i;

	for(i=0; i< *(table + 0); i++)	/*place grass*/
		place_plant('G');
	for(i=0; i< *(table + 1); i++)	/*place algae*/
		place_plant('A');
	for(i=0; i< *(table + 2); i++)	/*place maple*/
		place_plant('M');
	for(i=0; i< *(table + 3); i++)	/*place oak*/
		place_plant('O');
	for(i=0; i< *(table + 4); i++)	/*place pine*/
		place_plant('P');
}


void Ecosystem::place_plant(char ch)

{
	int x, y;

	if(available_position(ch)){	/*check if there is an available position for the plant*/
		do{
			x = rand()%terrainSize;
			y = rand()%terrainSize;
		}while(!available_position(x, y, ch));		/*check if this specific position is available*/

		(terrain[x][y]).set_pplant(ch);		/*create a plant in the available position*/
	}
}



bool Ecosystem::available_position(char token)

{
	int i, j;

	for(i=0; i<terrainSize; i++)
		for(j=0; j<terrainSize; j++){
			if((terrain[i][j]).get_pplant() == NULL){	/*if there is not another plant in this tile*/

				switch (token){
					case 'G':	if((terrain[i][j]).get_token() == '"')
								return true;
							break;

					case 'A':	if((terrain[i][j]).get_token() == '#')
								return true;
							break;

					case 'M':	if((terrain[i][j]).get_token() != '#')
								return true;
							break;

					case 'O':	if((terrain[i][j]).get_token() == '"')
								return true;
							break;

					case 'P':	if((terrain[i][j]).get_token() == '^')
								return true;
							break;
				}
			}
		}

	return false;

}


bool Ecosystem::available_position(int i, int j, char token)

{
	if((terrain[i][j]).get_pplant() != NULL)	/*if there is another plant in this tile this position is not available*/
		return false;

	switch (token){
		case 'G':       if((terrain[i][j]).get_token() == '"')
					return true;
				break;

		case 'A':       if((terrain[i][j]).get_token() == '#')
					return true;
				break;

		case 'M':       if((terrain[i][j]).get_token() != '#')
					return true;
				break;

		case 'O':       if((terrain[i][j]).get_token() == '"')
					return true;
				break;

		case 'P':       if((terrain[i][j]).get_token() == '^')
					return true;
				break;
	}

	return false;
}


void Ecosystem::PlaceAnimals(int *table){
	int i,j,k,random_x,random_y;
	Animal *x;
	
		for(i=0;i<table[0];i++){
			x=new Deer();
			x->Raise_to_max();
			do{
			random_x=(terrainSize-1)*(double)rand()/RAND_MAX;
			random_y=(terrainSize-1)*(double)rand()/RAND_MAX;}
			while( terrain[random_x][random_y].get_token()!=x->return_lives_in() );
			x->set_point(random_x,random_y);
			terrain[random_x][random_y].insert_animal_list(x);
		                       }
		for(i=0;i<table[1];i++){
			x=new Rabbit();
			x->Raise_to_max();
			do{
			random_x=(terrainSize-1)*(double)rand()/RAND_MAX;
			random_y=(terrainSize-1)*(double)rand()/RAND_MAX;}
			while( terrain[random_x][random_y].get_token()!=x->return_lives_in() );
		    x->set_point(random_x,random_y);
		    terrain[random_x][random_y].insert_animal_list(x);
		                       }		
		for(i=0;i<table[2];i++){
			x=new Groundhog();
			x->Raise_to_max();
			do{
			random_x=(terrainSize-1)*(double)rand()/RAND_MAX;
			random_y=(terrainSize-1)*(double)rand()/RAND_MAX;}
			while( terrain[random_x][random_y].get_token()!=x->return_lives_in() );
			x->set_point(random_x,random_y);
		    terrain[random_x][random_y].insert_animal_list(x);        
		                       }			
		for(i=0;i<table[3];i++){
			x=new Salmon();
			do{
			random_x=(terrainSize-1)*(double)rand()/RAND_MAX;
			random_y=(terrainSize-1)*(double)rand()/RAND_MAX;}
			while( terrain[random_x][random_y].get_token()!=x->return_lives_in() );
		    x->set_point(random_x,random_y);
		    terrain[random_x][random_y].insert_animal_list(x);
		                       }
		for(i=0;i<table[4];i++){
			x=new Fox();
			x->Raise_to_max();
			do{
			random_x=(terrainSize-1)*(double)rand()/RAND_MAX;
			random_y=(terrainSize-1)*(double)rand()/RAND_MAX;}
			while( terrain[random_x][random_y].get_token()!=x->return_lives_in() );
		    x->set_point(random_x,random_y);
		    terrain[random_x][random_y].insert_animal_list(x);                  
		                       }
		for(i=0;i<table[5];i++){
			x=new Wolf();
			x->Raise_to_max();
			do{
			random_x=(terrainSize-1)*(double)rand()/RAND_MAX;
			random_y=(terrainSize-1)*(double)rand()/RAND_MAX;}
			while( terrain[random_x][random_y].get_token()!=x->return_lives_in() );
		    x->set_point(random_x,random_y);
		    terrain[random_x][random_y].insert_animal_list(x);
		                       }
		for(i=0;i<table[6];i++){
			x=new Bear();
			x->Raise_to_max();
			do{
			random_x=(terrainSize-1)*(double)rand()/RAND_MAX;
			random_y=(terrainSize-1)*(double)rand()/RAND_MAX;}
			while( terrain[random_x][random_y].get_token()!=x->return_lives_in() );
		    x->set_point(random_x,random_y);
		    terrain[random_x][random_y].insert_animal_list(x);
		                       }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Tile::~Tile()

{
	if(pplant!=NULL)
		delete pplant;	/*destroy the plant in the tile if exists*/
}
List** Tile::get_panimals()

{
	return panimals;
}

void Tile::set_pplant(char token)

{
	switch (token){
		case 'G':	pplant = new Grass(p);
				break;

		case 'A':	pplant = new Algae(p);
				break;

		case 'M':	pplant = new Maple(p);
				break;

		case 'O':	pplant = new Oak(p);
				break;

		case 'P':	pplant = new Pine(p);
				break;
	}
}
void Tile::remove_plant()

{
	delete pplant;
	pplant = NULL;
}



void Tile::remove_dead_animals()

{
	int i;

	for(i=0; i<7; i++)
		(panimals[i])->remove_dead_animals();

}

void Tile::set_in_hibernation(bool value)

{
	(panimals[2])->set_in_hibernation(value);
	(panimals[6])->set_in_hibernation(value);
}



void Tile::animal_grow()

{
	int i;

	for(i=0; i<7; i++)
		if( i!=3 ) (panimals[i])->grow();  //wste na min kanei Raise o salmon
}



void Tile::herbivores_breed()

{
	(panimals[0])->breed(p);
	(panimals[1])->breed(p);
	(panimals[2])->breed(p);
	(panimals[3])->breed(p);
}


void Tile::carnivores_breed()

{
	(panimals[4])->breed(p);
	(panimals[5])->breed(p);
	(panimals[6])->breed(p);
}


void Tile::check_hunger()

{
	int i;

	for(i=0; i<7; i++)
		(panimals[i])->check_hunger();

}


void Tile::reinitialize_hunger()

{
        (panimals[0])->reinitialize_herbivores_hunger();
        (panimals[1])->reinitialize_herbivores_hunger();
        (panimals[2])->reinitialize_herbivores_hunger();
        (panimals[3])->reinitialize_herbivores_hunger();

        (panimals[4])->reinitialize_carnivores_hunger();
        (panimals[5])->reinitialize_carnivores_hunger();
        (panimals[6])->reinitialize_carnivores_hunger();

}

void Tile::insert_animal_list(Animal* x){
	if( x->return_name() == "[Deer]"){
		panimals[0]->insert(x);
									 }
	else if( x->return_name() == "[Rabbit]"){
		panimals[1]->insert(x);
									 }									 
	else if( x->return_name() == "[Groundhog]"){
		panimals[2]->insert(x);
									 }
	else if( x->return_name() == "[Salmon]"){
		panimals[3]->insert(x);
									 }
	else if( x->return_name() == "[Fox]"){
		panimals[4]->insert(x);
									 }
	else if( x->return_name() == "[Wolf]"){
		panimals[5]->insert(x);
									 }
	else if( x->return_name() == "[Bear]"){
		panimals[6]->insert(x);
									 }									 								 
									}

void Tile::eat_animals(){
	
	for(int i=0;i<7;i++) panimals[i]->eat_the_animals(*this);}
	
	
										

	
	
