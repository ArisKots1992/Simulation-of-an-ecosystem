
//Ecosystem Definition
class Tile{
	private:
		char token;
		point p;
		Plants *pplant;
		List* panimals[7];//[0]Deer,[1]Rabbit,[2]Groundhog,[3]Salmon,[4]Fox,[5]Wolf,[6]Bear.

	public:
		Tile() :token('-'), pplant(NULL)/*, panimals(NULL)*/ {for(int i=0;i<7;i++)panimals[i]=new List();}
		~Tile();

		char get_token()	{return token;}
		point get_p();
		Plants* get_pplant()	{return pplant;}
		List** get_panimals();
		
		void set_token(char ch)	{token = ch;}
		void set_p(int x, int y) {p.x = x; p.y = y;}
		void set_pplant(char);
    	void set_in_hibernation(bool);
		void reinitialize_hunger();
		void check_hunger();
		void remove_plant();
		void remove_dead_animals();

		void animal_grow();
		void herbivores_breed();
		void carnivores_breed();
		
		void insert_animal_list(Animal* x);

		void apoxorisi_animal_list(Animal* x);
		void call_move_animals(Ecosystem& eco,int k){panimals[k]->move_animals(eco);}
		void eat_animals();
		Animal* return_an_animal(int k,int place){
			
			return panimals[k]->return_animal(place);

												 }

		int return_size(int k){return panimals[k]->size();}
};


class Ecosystem{
	private:
		int terrainSize;
		int dayOfYear;

		int plant_growthPeriod;
	    int animal_growthPeriod;
		int plant_breedingRepPeriod;
		int herbivores_breedingRepPeriod;
		int carnivores_breedingRepPeriod;
	

		std::string season;
		Tile **terrain;
		
		void next_season();

		bool available_position(int);
		bool available_position(int, int, int);
		bool available_position(char);
		bool available_position(int, int, char);

		void place_plant(char);

		bool no_other_plant_left(int, int, char**);
		bool no_other_plant_right(int, int, char**);
		bool no_other_plant_down(int, int, char**);
		bool no_other_plant_up(int, int, char**);

	public:
		Ecosystem(int, std::string, int, int*, int*);	/*arguements are terrainsize, season, number_of_hills, number of each kind of plant,
									number of each kind of animal*/
		virtual ~Ecosystem();
         
        int get_terrainSize()	{return terrainSize;} 
		Tile** get_terrain()	{return terrain;}

		void ApplySeason();

		void MapGenerator(int);		/*arguement is number of hills*/
		void GenerateRiver();
		void GenerateLake();
		int GenerateHills(int);		/*arguement is number of hills*/
		void GenerateMeadow();

		void PlacePlants(int*);		/*arguement is number of each kind of plant*/
		void PlaceAnimals(int*);	/*arguement is number of each kind of animal*/

		void RunEcosystem(int);	/*arguement is days of simulation*/
		void DailyReset();
		void AnimalMovement();
		void AnimalEating();
		void CheckDeadEntities();
		void CheckHunger();
		void AnimalBreeding(char);
		void PlantBreeding();
		char FindFreeTile(char, int, int, char**);

		void PrintSystem();
		void PrintPlantStatistics();
		void PrintAnimalStatistics();

};
