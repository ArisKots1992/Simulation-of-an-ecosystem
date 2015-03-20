#include<string>
#include<iostream>

using namespace std;

class Animal{
	private:  		  		  			  
	  string name;					/*animal name*/
	  int size;						/*animal size*/
	  int max_size;		
	  int hungerCount;				/*how many days has to eat*/
	 protected:
	  int eatenFood;				/*the food has been consubed by an animal*/
	  int eatCount;					/*units of food consumed per meal/hour*/
     private:
	  bool isAlive;					/*if the animal is alive or dead*/
	  bool isHungry;				/*if the animal is hungry or not*/ 
	  bool inHeat;					/*if it is his spawing season*/
	  int speed;					/*the animal speed*/
	  int max_speed;
	  bool hibernates;				/*if hibernate*/
	  bool inHibernation;			/*if it is in hibernation*/
      point my_point;		    	/*animal coordinates*/
      char lives_in;                /*living place*/
      bool hasMoved;				/*boolian variable for help movement*/
	  
   public:
	  Animal(int,int,string,int,bool,int,int);
	  ~Animal(){};
   	   virtual void Move(Ecosystem& usd){};					/*move in the terrain*/
	   virtual void Eat(Plants&){};			/*eat a Plant*/
	   virtual void Eat(Animal&){};			/*eat another animal*/
	   virtual void Raise()=0;		//apla gia na pigenis thn Raise tou zwou(glitono cast)
	   virtual void set_cant_move(char x) {}
	   void Raise(int,int,int);	    		  	/*evolve*/
	   void set_point(int,int); /*mutators*/
	   void set_eatenFood(int);
	   void set_hungerCount(int);
	   void set_isHungry(bool);
	   void set_hibernates(bool);
	   void set_inHibernation(bool);
	   void set_isAlive(bool);
	   void set_inHeat(bool);
	   void set_lives_in(char);
	   void set_growthPeriod(int);
	   void set_breedingRepPeriod(int);
	   void set_hasMoved(bool);
	   string return_name();	/*accessors*/
	   int return_speed();      
	   int return_size();
	   int return_eatenFood();
	   int return_eatCount();
	   int return_hungerCount();
	   virtual char return_token()=0; //gia na kalo tis katw
	   bool return_isHungry();
	   bool return_hibernates();
	   bool return_inHibernation();
	   bool return_isAlive();
	   bool return_inHeat();
       point return_point();
       char return_lives_in();
       int return_growthPeriod();
       int return_breedingRepPeriod();
       bool return_hasMoved();
       virtual void Raise_to_max()=0;
       virtual void increase_days_passed_from_creation(){}
       virtual int return_days_passed_from_creation(){}
	   virtual void print(){
	  	   cout<<"------------------"<<endl;
	  	   cout<<"------------------"<<endl;
	  	   cout<<"name = "<<name<<endl;
	  	   cout<<"size = "<<size<<endl<<"speed = "<<speed<<endl<<"eatCount = "<<eatCount<<endl;
	  	   cout<<"hibernates = ";
			  if (hibernates) 
			  cout<<"true"<<endl; 
			  else
			   cout<<"false"<<endl; }
			   };
/*//////////////////////////////////////////////////////////////////////////////*/			   
/*----------------------Herbivores----------------------------------------------*/
/*//////////////////////////////////////////////////////////////////////////////*/				   
class Herbivores : public Animal{		/*na t balw H?*/
    private:
      char token;
	  bool canClimb;				/*if the animal can climb or not*/
	  int neededFood;				/*necessary amount of food that must be taken*/	
	  int max_neededFood;
	  char cant_move;	    
	  int days_passed_from_creation;
	public:
	  Herbivores(int,int,int,bool,string,bool,int,int,int,int);
	  ~Herbivores(){};
	   virtual void Eat(Plants&);   /*eat a Plant*/
	   virtual void Raise()=0;//apla gi na pigenei stou zow thn Raise(glitono cast)
	   virtual void Move(Ecosystem&);
       void Raise(int);
       int return_neededFood();   /*accessor*/
       bool return_canClimb();     /*accesor*/
       char return_token();
       char return_cant_move();
       void set_cant_move(char);
       void increase_days_passed_from_creation(){days_passed_from_creation++;}
       int return_days_passed_from_creation(){return days_passed_from_creation;}
       virtual void Raise_to_max();
       void print(){
	   		Animal::print();
			   cout<<"neededFood = "<<neededFood<<endl<<"canClimb = ";	
			  if (canClimb) 
			  cout<<"true"<<endl; 
			  else
			   cout<<"false"<<endl;  } 
 		   	                  };  
/*//////////////////////////////////////////////////////////////////////////////*/ 		   	                  
/*---------------------Herbivores_Animals---------------------------------------*/
/*//////////////////////////////////////////////////////////////////////////////*/ 	
class Deer : public Herbivores{
	public:
	    Deer();
	   ~Deer(){};  
	    virtual void Move(Ecosystem&);
	    virtual void Raise();
	    virtual void Eat(Plants&);
                            };	 
class Rabbit : public Herbivores{
    public:
	    Rabbit();
	   ~Rabbit(){};
	    virtual void Move(Ecosystem&);
	    virtual void Raise();
	    virtual void Eat(Plants&);	   
                            };
class Groundhog : public Herbivores{
    public:
        Groundhog();
       ~Groundhog(){};
	    virtual void Move(Ecosystem&);       
        virtual void Raise();
	    virtual void Eat(Plants&);
	                        };                            
class Salmon : public Herbivores{
    public:
	    Salmon();
       ~Salmon(){};   		
        virtual void Move(Ecosystem&);
	    virtual void Raise(){};   
 	    virtual void Eat(Plants&);
                            };                          
/*//////////////////////////////////////////////////////////////////////////////*/ 	 
/*----------------------Carnivores----------------------------------------------*/ 
/*//////////////////////////////////////////////////////////////////////////////*/ 	
class Carnivores : public Animal{
    private:
      char token;
      int neededFood;   //DEN TO LEI H EKFONISH ALLA PROFANOS ENOITE!
      int max_neededFood;
	  int attack;
	  int defence;
	  int max_attack;
	  int max_defence;
	  	  
    public:		  				  
	   Carnivores(int,int,int,int,int,string,bool,int,int,int,int,int);
      ~Carnivores(){};
	   virtual void Eat(Animal&);	  /*eat another animal*/
	   virtual void Raise()=0;//apla gi na pigenei stou zow thn Raise(glitono cast)	   
	   virtual void Raise(int,int,int);
	   virtual void Move(Ecosystem&);
	   int return_attack();      /*accessor*/
	   int return_defence();    /*accessor*/
	   int return_neededFood();  /*accessor*/
	   char return_token();
       virtual void Raise_to_max();	   
       void print(){
	   		Animal::print();
			   cout<<"attack = "<<attack<<endl<<"defence = "<<defence<<endl;
			   cout<<"neededFood = "<<neededFood<<endl; } 	 
	                            };
/*//////////////////////////////////////////////////////////////////////////////*/ 		   	                  
/*---------------------Carnivores_Animals---------------------------------------*/
/*//////////////////////////////////////////////////////////////////////////////*/ 	  
class Fox : public Carnivores{
	public:
	   Fox();
	  ~Fox(){};	    
	   virtual void Move(Ecosystem&);
	   virtual void Raise();	 
	   virtual void Eat(Animal&);    
		                     };	  
class Bear : public Carnivores{
	public:
	    Bear();
	   ~Bear(){};	   
	    virtual void Move(Ecosystem&);
	    virtual void Raise();	   
	    virtual void Eat(Animal&);
	   		                  };
class Wolf : public Carnivores{
	public:
	   Wolf();
	  ~Wolf(){};	  
	   virtual void Move(Ecosystem&);
	   virtual void Raise();	  
	   virtual void Eat(Animal&);
	   		                  };								 	  
	   			   
	   			   

