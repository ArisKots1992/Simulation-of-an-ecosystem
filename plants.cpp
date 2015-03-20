#include <iostream>
#include "classes.h"
//Plants class functions
using namespace std;

Plants::Plants(point position_, string name_, char token_, double breedingProb_, double illnessProb_, int life_, int lifefactor_)
	:	position(position_), name(name_), token(token_), breedingProb(breedingProb_), illnessProb(illnessProb_), life(life_), lifefactor(lifefactor_)	{}


char Plants::get_token()	{return token;}
int Plants::get_life()		{return life;}
int Plants::get_lifefactor()	{return lifefactor;}
double Plants::get_breedingProb()	{return breedingProb;}
double Plants::get_illnessProb()	{return illnessProb;}


void Plants::set_life(int x)	{life = x;}

bool Plants::NormalBreeding()

{
	double possibility;

	possibility = ( (double) rand())/( (double) RAND_MAX);
	if(possibility > breedingProb)
		return true;

	return false;
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

Seedless::Seedless(point position, string name, char token, double breedingProb, double illnessProb, int life, int lifefactor)
	:	Plants(position, name, token, breedingProb, illnessProb, life, lifefactor)	{}



int Seedless::LoseLife(int eat_amount)

{
	int life = get_life();

	if(life >= eat_amount){
		life -= eat_amount;
		set_life(life);
		return eat_amount;	/* amount realy eaten*/
	}
	else{
		set_life(0);
		return life;		/* amount realy eaten*/
	}
}


void Seedless::grow()

{
	double possibility;
	int temp = get_life();

	possibility = ( (double) rand())/( (double) RAND_MAX);

	if(possibility <= get_illnessProb()){
		temp += get_lifefactor();
	}
	else{
		temp -= get_lifefactor();
		if(temp < 0)
			temp = 0;
	}

	set_life(temp);
}


///////////////////////////////////////////////////////////////

Grass::Grass(point position)
	:	Seedless(position, "Grass", 'G', 0.15, 0.15, 5, 4)	{}


///////////////////////////////////////////////////////////////

Algae::Algae(point position)
	:	Seedless(position, "Algae", 'A', 0.25, 0.25, 5, 2)	{}


///////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

Seeded::Seeded(point position, string name, char token, double breedingProb, double illnessProb, int life, int lifefactor, int size_, int foliage_, int seeds_)
	:	Plants(position, name, token, breedingProb, illnessProb, life, lifefactor), size(size_), foliage(foliage_), seeds(seeds_)	{}

int Seeded::get_size(){
	return size;
                      }

int Seeded::LoseLife(int eat_amount)

{
	if(seeds >= eat_amount){
		seeds -= eat_amount;
		return eat_amount;	/* amount realy eaten*/
	}
	else{
		int temp = eat_amount, seeds_ = seeds;
		eat_amount -= seeds;
		seeds = 0;

		if(foliage >= eat_amount){
			foliage -= eat_amount;
			set_life(foliage);
			return temp;	/* amount realy eaten*/
		}
		else{
			int life = get_life();
			foliage = 0;
			set_life(0);
			return life + seeds_;		/* amount realy eaten*/
		}
	}

}


void Seeded::grow()

{
	bool flag;
	double possibility;
	int temp = get_lifefactor();

	possibility = ( (double) rand())/( (double) RAND_MAX);

	if(possibility <= get_illnessProb()){
		foliage -= temp;
		if(foliage < 0)
			foliage = 0;

		seeds -= 2*temp;
		if(seeds < 0)
			seeds = 0;

		flag = false;		/*foliage reduced*/
	}
	else{
		foliage += temp;
		seeds += temp;

		flag = true;		/*foliage increased*/
	}

	set_life(foliage);

	if( (((double) foliage)/( (double) temp)) == (foliage/temp)){	/*if foliage is analogous with lifefactor raise or reduce the size*/
		if(flag)
			size++;
		else{
			size--;
			if(!size)	/*size sould be a positive number*/
				size = 1;

		}
	}

}

///////////////////////////////////////////////////////////////


Oak::Oak(point position)
	:	Seeded(position, "Oak", 'O', 0.20, 0.20, 30, 15, 5, 30, 15)	{}



///////////////////////////////////////////////////////////////


Pine::Pine(point position)
	:	Seeded(position, "Pine", 'P', 0.15, 0.15, 40, 20, 5, 40, 20)	{}



///////////////////////////////////////////////////////////////


Maple::Maple(point position)
	:	Seeded(position, "Maple", 'M', 0.05, 0.05, 20, 10, 2, 20, 10)	{}



///////////////////////////////////////////////////////////////
