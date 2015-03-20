#include<cstdlib>
#include<iostream>
#include "classes.h"
using namespace std;

void List::insert(Data x){
	
    if(nodes==0){
        Node* tmp;
        tmp=new Node(x);

        first=tmp;
        last=tmp;
        nodes++;}
    else{
       Node* tmp;
       tmp=new Node(x);

       last->next=tmp;
       last=tmp; //meta dixni apo monot  nul to tmp->next
       nodes++;}        }

void List::out(){
   if(nodes>1){
     Node* temp;
     temp=first;

     first=first->next;
     nodes--;//is out
     delete temp;
              }
 else if(nodes==1){
    Node* temp;
    temp=first;

    first=first->next;
    last=first;
    nodes--;//is out
    delete temp;}
 else cout<<"ERROR  EMPTY!\n"; }
 
 void List::apoxorish(Data x){   //eikonikh apoxorish
         Node* tmp;
         Node* after;

         tmp=first;
         after=tmp->next;

         if(nodes==0){cout<<"ERRORRRRRRR\n"; return ;}

         if(tmp->data=x){//ama ine to proto sixio p rpepi na bgi
             nodes--;
             first=tmp->next;
         //    delete tmp;
              return;             }
         while(after!=NULL){
                if(after->data=  x){
                  tmp->next=after->next;
                  nodes--;
                        if(after->next==NULL)//an prepei na bgi to telefteo
                          last=tmp;
                      //  delete after;
                   break;}
           after=after->next;
           tmp=tmp->next;}    }
           
 void List::apoxorish_kai_diagrafh(Data x){   //kanonikh apoxorish
         Node* tmp;
         Node* after;

         tmp=first;
         after=tmp->next;

         if(nodes==0){cout<<"ERRORRRRRRR\n"; return ;}

         if(tmp->data=x){//ama ine to proto sixio p rpepi na bgi
             nodes--;
             first=tmp->next;
             delete tmp;
              return;             }
         while(after!=NULL){
                if(after->data=  x){
                  tmp->next=after->next;
                  nodes--;
                        if(after->next==NULL)//an prepei na bgi to telefteo
                          last=tmp;
                        delete after;
                   break;}
           after=after->next;
           tmp=tmp->next;}    }
           
void List::move_animals(Ecosystem& eco){
	Node *tmp;
	int x,y;
	tmp=first;
	if(first==NULL) return;
	
	while(tmp!=NULL){
	if(tmp->data->return_hasMoved()==false){	

		tmp->data->Move(eco);

		x=tmp->data->return_point().x;
		y=tmp->data->return_point().y;
	
		tmp->data->set_hasMoved(true);
		(eco.get_terrain()[x][y]).insert_animal_list(tmp->data);
		apoxorish(tmp->data);
	                                      }
		tmp=tmp->next;
									  
	                 }
		                                }
void List::eat_the_animals(Tile& terrain){
	Node *tmp;
	bool j=true;
	int end=0;
	int x,y,k=-1,size,counter=0;
	tmp=first;
	if (first==NULL)
	       return;    //an ine kenh

	while(tmp!=NULL){  //gia ka8e zwo stin lista
        if (tmp->data->return_token() == 'C' && tmp->data->return_inHibernation() == false
            && tmp->data->return_isAlive() == true){
		     end=3;
	
		    if (tmp->data->return_hungerCount()>=8) end=6; //wste na fai ke sarkofaga
		   while(tmp->data->return_isHungry() == true && k<end){
			  if(counter==0){		
				    k++;	/*thn proth fora to k tha gini 1 ke meta kathe fora p teliwnei kathe oura ++*/	
				    size=terrain.return_size(k);
				    j=true;
				            }
			  if(j==true) counter=size; //wste na min alazei sinexia to counter
			  j=false;
			   if(size!=0 && tmp->data != (terrain.return_an_animal(k,size-counter)) 
			              && terrain.return_an_animal(k,size-counter)!=NULL ) //an den ine to idio ke den exi zow
			     tmp->data->Eat(  *(terrain.return_an_animal(k,size-counter))   );
                     /*apw panw epistefo ena animal sto idio tile alla se kathe oura me thn swsth sira*/

			   counter--;  //miwse ton counter analoga me ton ari8mo ton zow se kathe oura p dokimazw
			   if(size==0) counter=0;
										     				   } 										     				   
										                                                     } 
		else if(tmp->data->return_token() == 'H' && tmp->data->return_inHibernation() == false 
		        && tmp->data->return_isAlive() == true){
            
            if(tmp->data->return_isHungry() == true){		
	            	if( terrain.get_pplant()!=NULL) 
				        tmp->data->Eat( *(terrain.get_pplant())  ) ;  //prospathise na fas fito							    				   
											     }
											 }
						tmp->data->set_hasMoved(false);					 
				      tmp=tmp->next;} 
									}
											     			
Animal* List::return_animal(int place){
	Node *tmp;
	tmp=first;
	if (tmp==NULL) return NULL;
	for(int i=0;i<place;i++){  //tha proxorise mion mia thesi gt arxika ine sto first
		tmp=tmp->next;
							 }
		return tmp->data;
		
	                                  }					 
	
void List::set_in_hibernation(bool value)

{
	Node *temp;

	temp = first;
	while(temp != NULL){
		temp->data->set_inHibernation(value);
		temp = temp->next;
	}
}


void List::breed(point p)

{   
	Node *temp;
	Animal *animal;

	temp = first;

	while(temp != NULL){

		if(temp->data->return_inHeat() && temp->data->return_isAlive() && temp->data->return_inHibernation() == false){	/* if the animal can breed */

			if(temp->data->return_name() == "[Deer]")
				animal = new Deer;
			else if(temp->data->return_name() == "[Rabbit]")
				animal = new Rabbit;
			else if(temp->data->return_name() == "[Groundhog]")
				animal = new Groundhog;
		    else if(temp->data->return_name() == "[Salmon]")
		        animal = new Salmon;
			else if(temp->data->return_name() == "[Fox]")
				animal = new Fox;
			else if(temp->data->return_name() == "[Wolf]")
				animal = new Wolf;
			else if(temp->data->return_name() == "[Bear]")
				animal = new Bear;
            animal->set_point(p.x,p.y);
			this->insert(animal);
		}

		temp = temp->next;
	}
}


void List::remove_dead_animals()

{
	Node *temp;

	temp = first;

	while(temp != NULL){

		if(! (temp->data->return_isAlive() ) )
			apoxorish_kai_diagrafh(temp->data);

		temp = temp->next;
	}
}



void List::check_hunger()

{
	Node *temp;

	temp = first;

	while(temp != NULL){
		if(temp->data->return_isHungry())
			temp->data->set_hungerCount( temp->data->return_hungerCount() + 1 );

		if(temp->data->return_hungerCount() == 10)
			temp->data->set_isAlive(false);

		temp = temp->next;
	}
}



void List::reinitialize_herbivores_hunger()

{
	Node *temp;

	temp = first;

	while(temp != NULL){

		if(temp->data->return_hungerCount() >= 7 )
		     temp->data->set_isHungry(true);
		     
		 temp->data->increase_days_passed_from_creation();		 
		 if(temp->data->return_name() == "[Salmon]")
		        if(temp->data->return_days_passed_from_creation() == 25)
		              temp->data->set_inHeat(true);
		 temp = temp->next;    
	}
	
}


void List::reinitialize_carnivores_hunger()

{
	Node *temp;

	temp = first;

	while(temp != NULL){
		temp->data->set_isHungry(true);
		temp = temp->next;
	}
}





void List::grow()

{
	Node *temp;

	temp = first;

	while( temp != NULL){
		temp->data->Raise();
		temp = temp->next;
	}
}	
			   
		
		
		
				
		
		
		
	
	
