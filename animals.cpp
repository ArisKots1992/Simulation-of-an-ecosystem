#include "classes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
/*//////////////////////////////////////////////////////////////////////////////*/			   
/*--------------------Animals_functions-----------------------------------------*/
/*//////////////////////////////////////////////////////////////////////////////*/
Animal::Animal(int the_size,int the_speed,string the_name,int the_eatCount,
               bool the_hibernates,int maxsize,int maxspeed){
	eatenFood=0;			   
   size=the_size;
   speed=the_speed;
   name=the_name;
   eatCount=the_eatCount;
   hibernates=the_hibernates;
   max_size=maxsize;
   max_speed=maxspeed;	
   isAlive=true;
   isHungry=true;
   hungerCount=0;
   inHeat=false;
   hasMoved = false;
	   					 					  				}
void Animal::Raise_to_max(){
	 size=max_size;
	 speed=max_speed;
	 inHeat=true;
						   }
void Animal::Raise(int increase_size,int increase_speed,int increase_eatCount=0){
	 if(size<max_size)
     	 size+=increase_size;
     if(speed<max_speed)	 
    	 speed+=increase_speed;
	     eatCount+=increase_eatCount;
	   if(size == max_size && speed == max_speed) inHeat = true;   //wste na kseroume oti einai eniliko 
/*=========mutators===============*/		 							 	 										 }
void Animal::set_point(int x,int y){
	 my_point.x=x;
	 my_point.y=y;
	 		   			   		   }	
void Animal::set_eatenFood(int x){
	 eatenFood=x;
	 			 			     }
void Animal::set_hungerCount(int x){
	 hungerCount=x;
	 if(x == -16) hungerCount++;
	                               } 
void Animal::set_isHungry(bool x){
	 isHungry=x;
	                             }
void Animal::set_hibernates(bool x){
	 hibernates=x;
	                               }
void Animal::set_inHibernation(bool x){
	 inHibernation=x;
	 				 				  }
void Animal::set_isAlive(bool x){
	 isAlive=x;
	 		   				    }
void Animal::set_inHeat(bool x){
	 inHeat=x;
	 		  				   }
void Animal::set_lives_in(char x){
	 lives_in=x;
	                             }
//void Animal::set_growthPeriod(int x){
//	 growthPeriod=x;
//	                               } 
//void Animal::set_breedingRepPeriod(int x){
//	 breedingRepPeriod=x;
//	                               } 
void Animal::set_hasMoved(bool x){
	 hasMoved=x;
	                               } 	                           
/*=========accessors===============*/	    
string Animal::return_name(){
	   return name;
	                        }                                                              
int Animal::return_eatenFood(){
	 return eatenFood;
	 				  			}
int Animal::return_speed(){
	 return speed;
	 				  			}
int Animal::return_size(){
	 return size;
	 				  			}
int Animal::return_eatCount(){
	 return eatCount;
	 				  			}
int Animal::return_hungerCount(){
	 return hungerCount;
	 							 }								   									   								   	 				  			
bool Animal::return_isHungry(){
	 return isHungry;
	 				 		   }
bool Animal::return_hibernates(){	
	 return hibernates;
	 		                    }
bool Animal::return_inHibernation(){
	 return inHibernation;
		                           }	
bool Animal::return_isAlive(){
	 return isAlive;
	 						  };
bool Animal::return_inHeat(){
	 return inHeat;
	 			   			};							  				 		   
point Animal::return_point(){
	 return my_point;
	                        }
char Animal::return_lives_in(){
	 return lives_in;
	                  }
//int Animal::return_growthPeriod(){
//	return growthPeriod;
 //                                }
//int Animal::return_breedingRepPeriod(){
//	return breedingRepPeriod;
//	 	   					 		  }
bool Animal::return_hasMoved(){
	return hasMoved;
	 	   					 		  }

/*=================================*/
/*//////////////////////////////////////////////////////////////////////////////*/			   
/*--------------------Herbivores_functions--------------------------------------*/
/*//////////////////////////////////////////////////////////////////////////////*/	
Herbivores::Herbivores(int size,int speed,int the_needed_food,bool hibernates,
                       string name,bool the_canClimb,int eatCount,int max_size=0,
					   int max_speed=0,int maxneededFood=0)
    : Animal(size,speed,name,eatCount,hibernates,max_size,max_speed){
        
       neededFood=the_needed_food;
	   canClimb=the_canClimb;
	   max_neededFood=maxneededFood;	
	   //days_passed_eat=0;
	   days_passed_from_creation=0;   
	   token='H';
		   		  	                  }
void Herbivores::Raise_to_max(){
	neededFood=max_neededFood;
	Animal::Raise_to_max();
                               }
void Herbivores::Raise(int increase_neededFood){
	 if(neededFood<max_neededFood)
       neededFood+=increase_neededFood;
	                                     } 
void Herbivores::Eat(Plants& x){
	 int temp,eat_c=0;
	 if(neededFood>eatenFood ){
         if( (neededFood-eatenFood) >= eatCount){
	       eat_c=x.LoseLife(eatCount);//epistrefi an bori na fai toso aliws poso
	       eatenFood+=eat_c;   
		 					  }
		 else if( (neededFood-eatenFood) < eatCount){
		   eat_c=x.LoseLife(neededFood-eatenFood);
		   eatenFood+=eat_c;
		   										    }
			                  }
    if( neededFood == eatenFood ) {set_isHungry(false);set_hungerCount(0);}
							  }
void Herbivores::Move(Ecosystem& eco){//cout<<"MOVE HERBIVORES"<<endl;
	int near_move,x,y,counter;
	int size;
	bool enter[8];
	bool walked=false;	
	 size=eco.get_terrainSize()-1;	
	  for(int i=0;i<8;i++)enter[i]=true; //arxika na benei
	  x=return_point().x;
	  y=return_point().y;
	  counter=0;
	  
      while(walked == false){    //perni apo 1 ews 8 pi8anes thesis
		   near_move=(8*(double)rand()/RAND_MAX )+1;
		   counter++;   //ama den bori na pai pou8ena na minei eki p ine
			if(near_move == 1 && enter[0]==true){            /*ante panw aristera*/
		           if(x-1>=0 && y-1>=0 ){
 					    if((eco.get_terrain()[x-1][y-1]).get_token()!=cant_move){
								set_point(x-1,y-1);
								walked=true;
																				}
						else enter[0]=false;														
						                }
				   else
				       enter[0]=false;    //wste na mhn ksanampei
						                         }    						                                       
		    else if(near_move == 2 && enter[1]==true){      /*ante panw*/
	               if(x-1>=0){	        					   
 					    if((eco.get_terrain()[x-1][y]).get_token()!=cant_move){
								set_point(x-1,y);
								walked=true;
																			  }
						else enter[1]=false;													  
				             }
				   else
				       enter[1]=false;          
								                      }             								                      
			else if(near_move == 3 && enter[2] == true){        /*ante panw deksia*/		  	       
		  	       if(x-1>=0 && y+1<=size){   
 					    if((eco.get_terrain()[x-1][y+1]).get_token()!=cant_move){					   
								set_point(x-1,y+1);
								walked=true;
																				}
						else enter[2]=false;
								          }
					else
					    enter[2]=false;
					        			            }             
		    else if(near_move == 4 && enter[3] == true){        /*ante deksia*/
		  	       if(y+1<=size){        
 					    if((eco.get_terrain()[x][y+1]).get_token()!=cant_move){						   
								set_point(x,y+1);
								walked=true;
																				}
					    else enter[3]=false;
					            }
				   else
					    enter[3]=false;            
								                    }
								                    
	        else if(near_move == 5 && enter[4] == true){        /*ante katw deksia*/
		  	        if(x+1<=size && y+1<=size){        
 					    if((eco.get_terrain()[x+1][y+1]).get_token()!=cant_move){			  	           
								set_point(x+1,y+1);
								walked=true;
																				}
						else enter[4]=false;														
					                          }
					else
					    enter[4]=false;            
								                    } 
								                                        
	        else if(near_move == 6 && enter[5] == true){        /*ante katw */
		  	        if(x+1<=size){        
 					    if((eco.get_terrain()[x+1][y]).get_token()!=cant_move){							
								set_point(x+1,y);
								walked=true;
																				}
						else enter[5]=false;
				                 }
					else
					    enter[5]=false;            
								                    }  
	        else if(near_move == 7 && enter[6] == true){        /*ante katw aristera*/
		  	        if(x+1<=size && y-1>=0){
 					    if((eco.get_terrain()[x+1][y-1]).get_token()!=cant_move){							        
								set_point(x+1,y-1);
								walked=true;
																				}
						else enter[6]=false;														
					                          }
					else
					    enter[6]=false;            
								                    }  
	        else if(near_move == 8 && enter[7] == true){        /*ante aristera*/
		  	        if(y-1>=0){        
 					    if((eco.get_terrain()[x][y-1]).get_token()!=cant_move){							
								set_point(x,y-1);
								walked=true;
																				}
						else enter[7]=false;														
			                  }
					else
					    enter[7]=false;            
								                    }  
				if(counter==200)  break;
					  	    }      	
						              }
			 											    					  
/*=========accessors===============*/	
int Herbivores::return_neededFood(){
	 return neededFood;
	 				                }
bool Herbivores::return_canClimb(){
	 return canClimb;
	 				              }
char Herbivores::return_token(){
    return token;
                               }
char Herbivores::return_cant_move(){
	return cant_move;
									}
void Herbivores::set_cant_move(char x){
	cant_move=x;
								      }									            
/*=================================*/	 				              
/*//////////////////////////////////////////////////////////////////////////////*/			   
/*--------------------Herbivores_animals_functions------------------------------*/
/*//////////////////////////////////////////////////////////////////////////////*/

Deer::Deer(): Herbivores(2,4,4,false,"[Deer]",false,2,5,8,8){
			                         /*size,speed,neededFood,hibernates,name,canClimb,eatCount*/
	    set_lives_in('"');   //gia na min megalwsw kialo ta panw perasmata					
	    set_cant_move('@'); //epidi kinite pantou!! bazw asxeto  			  
						  	                   }	  
void Deer::Raise(){
		Animal::Raise(1,2);	/*increse size,speed,eatCount_den_xriazete*/
		Herbivores::Raise(2);	/*increse needed_food*/
		     }     
void Deer::Eat(Plants& x){
	    if( x.get_size() <= return_size()+4 )
			 Herbivores::Eat(x);		     
			            }
void Deer::Move(Ecosystem& eco){
	Herbivores::Move(eco);
	             }
/***************************************************************************/			            
Rabbit::Rabbit(): Herbivores(1,2,2,false,"[Rabbit]",false,1,2,6,4){
				                     /*size,speed,neededFood,hibernates,name,canClimb,eatCount*/
        set_lives_in('"');   //gia na min megalwsw kialo ta panw perasmata                                            
	    set_cant_move('^'); //epidi den kinite se bouno!  					
												     }
void Rabbit::Raise(){
		Animal::Raise(1,2);	/*increase size,speed,eatCount_den_xriazete*/
		Herbivores::Raise(1);	/*increase needed_food*/	
		       }
void Rabbit::Eat(Plants& x){
    char token;       /*gia eksikonomish xronou(min kalo poles sinartisis*/
    token = x.get_token();
	 if(token != 'A'){
        if(token == 'M' || token == 'O' || token == 'P'){
            if(x.get_size() <= return_size())
                Herbivores::Eat(x);
			                                            }
		else
		        Herbivores::Eat(x);
				    }													     
                         }	
void Rabbit::Move(Ecosystem& eco){ //8a boruse na bi sthn move ths mana ths gia na glitoso 1 move
Herbivores::Move(eco);
				          }
/***************************************************************************/			   										     
Groundhog::Groundhog():Herbivores(2,3,3,true,"[Groundhog]",true,1,3,5,5){
                                     /*size,speed,neededFood,hibernates,name,canClimb,eatCount*/
        set_lives_in('"');   //gia na min megalwsw kialo ta panw perasmata                                            
	    set_cant_move('#'); //epidi den kinite se nero!  														   
												   }
void Groundhog::Raise(){
		Animal::Raise(1,1);	/*increase size,speed,eatCount_denxriazete*/
		Herbivores::Raise(1);	/*increase needed_food*/	
		               }
void Groundhog::Eat(Plants& x){		
	 char token;      /*gia eksikonomish xronou(min kalo poles sinartisis*/
	 token = x.get_token();
	 if(token != 'A'){
	    if(token == 'M' || token == 'O' || token == 'P'){
               if(x.get_token() <= return_size())
                   Herbivores::Eat(x);
				   					 			   	    }
		else
		           Herbivores::Eat(x);
				    }		   					 			   	    
	                         }
void Groundhog::Move(Ecosystem& eco){
Herbivores::Move(eco);
				          }

/***************************************************************************/			   								
Salmon::Salmon():Herbivores(1,5,1,false,"[Salmon]",false,1){
                                     /*size,speed,neededFood,hibernates,canClimb,name,eatCount*/
         set_lives_in('#');   //gia na min megalwsw kialo ta panw perasmata
                                                     }
void Salmon::Eat(Plants& x){
	 if(x.get_token() == 'A')
	    Herbivores::Eat(x);  
                          }	
void Salmon::Move(Ecosystem& eco){ 
	/*poly pio periplokh move apla gia me diaforo skeptiko montelopoihshs xoris na bgenw exw apta akra
	  8a mporusa kalista na thn kanw opos tis apo panw*/
	  int size,counter;
	  int x,y,near_move;//tha kanw return x,y tis diastasis tou pinaka
	  char place='#';  //edw NERO alla 8a balw == anti gia !=!!
	  size=eco.get_terrainSize()-1;

	     bool walked=false;
         counter=0;
         x=return_point().x;
         y=return_point().y;

	      if(x>0 && x<size){
              if(y>0 && y<size){
	  		        while(walked == false){    //perni apo 1 ews 8 pi8anes thesis
	  		          counter++;
					  near_move=(8*(double)rand()/RAND_MAX )+1;//cout<<"near_move-"<<near_move<<endl;//cin>>size;
					      if(near_move == 1 &&          /*ante panw aristera*/
		                  (eco.get_terrain()[x-1][y-1]).get_token()==place){	
					     	 set_point(x-1,y-1);
						     walked=true;
						                    }
					      else if(near_move == 2 &&          /*ante panw*/
		                  (eco.get_terrain()[x-1][y]).get_token()==place){
		  	                 set_point(x-1,y);
					         walked=true;
								               }             
					      else if(near_move == 3 &&          /*ante panw deksia*/
		                  (eco.get_terrain()[x-1][y+1]).get_token()==place){
		  	                 set_point(x-1,y+1);
					         walked=true;
								               }             
					      else if(near_move == 4 &&          /*ante deksia*/
		                  (eco.get_terrain()[x][y+1]).get_token()==place){
		  	                 set_point(x,y+1);
					         walked=true;
								               }
					      else if(near_move == 5 &&          /*ante katw deksia*/
		                  (eco.get_terrain()[x+1][y+1]).get_token()==place){
		  	                 set_point(x+1,y+1);
					         walked=true;
								               }                          
					      else if(near_move == 6 &&          /*ante katw*/
		                  (eco.get_terrain()[x+1][y]).get_token()==place){
		  	                 set_point(x+1,y);
					         walked=true;
								               }
					      else if(near_move == 7 &&          /*ante katw aristera*/
		                  (eco.get_terrain()[x+1][y-1]).get_token()==place){
		  	                 set_point(x+1,y-1);
					         walked=true;
								               }
					      else if(near_move == 8 &&          /*ante aristera*/
		                  (eco.get_terrain()[x][y-1]).get_token()==place){
		  	                 set_point(x,y-1);
					         walked=true;
								               }
					if(counter==250) break;			               	
										   }}
    	        else if(y==0){
                       while(walked == false){    //perni apo 1 ews 5 pi8anes thesis
                        counter++;
					    near_move=(5*(double)rand()/RAND_MAX )+1; 	
					      if(near_move == 1 &&          /*ante panw */
		                  (eco.get_terrain()[x-1][y]).get_token()==place){	
					     	 set_point(x-1,y);
						     walked=true;
						                    }
					      else if(near_move == 2 &&          /*ante panw deksia*/
		                  (eco.get_terrain()[x-1][y+1]).get_token()==place){
		  	                 set_point(x-1,y+1);
					         walked=true;
								               }             
					      else if(near_move == 3 &&          /*ante  deksia*/
		                  (eco.get_terrain()[x][y+1]).get_token()==place){
		  	                 set_point(x,y+1);
					         walked=true;
								               }             
					      else if(near_move == 4 &&          /*ante katw deksia*/
		                  (eco.get_terrain()[x+1][y+1]).get_token()==place){
		  	                 set_point(x+1,y+1);
					         walked=true;
								               }
					      else if(near_move == 5 &&          /*ante katw */
		                  (eco.get_terrain()[x+1][y]).get_token()==place){
		  	                 set_point(x+1,y);
					         walked=true;
								               } 
					    if(counter==250) break;			      
	                                        }}     
 	            else if(y == size){
                       while(walked == false){    //perni apo 1 ews 5 pi8anes thesis
                        counter++;
					    near_move=(5*(double)rand()/RAND_MAX )+1; 	
					      if(near_move == 1 &&          /*ante panw */
		                  (eco.get_terrain()[x-1][y]).get_token()==place){	
					     	 set_point(x-1,y);
						     walked=true;
						                    }
					      else if(near_move == 2 &&          /*ante panw aristera*/
		                  (eco.get_terrain()[x-1][y-1]).get_token()==place){
		  	                 set_point(x-1,y-1);
					         walked=true;
								               }             
					      else if(near_move == 3 &&          /*ante  aristera*/
		                  (eco.get_terrain()[x][y-1]).get_token()==place){
		  	                 set_point(x,y-1);
					         walked=true;
								               }             
					      else if(near_move == 4 &&          /*ante katw aristera*/
		                  (eco.get_terrain()[x+1][y-1]).get_token()==place){
		  	                 set_point(x+1,y-1);
					         walked=true;
								               }
					      else if(near_move == 5 &&          /*ante katw */
		                  (eco.get_terrain()[x+1][y]).get_token()==place){
		  	                 set_point(x+1,y);
					         walked=true;
								               }  
	                   if(counter==250) break;			                
	                                        }}     
			          }   
		else if(x==0){
              if(y>0 && y<size){
                       while(walked == false){    //perni apo 1 ews 5 pi8anes thesis
						 counter++;
					    near_move=(5*(double)rand()/RAND_MAX )+1; 	
					         if(near_move == 1 &&          /*ante  aristera*/
		                  (eco.get_terrain()[x][y-1]).get_token()==place){
		  	                 set_point(x,y-1);
					         walked=true;
								               }      
					      else if(near_move == 2 &&          /*ante katw aristera*/
		                  (eco.get_terrain()[x+1][y-1]).get_token()==place){
		  	                 set_point(x+1,y-1);
					         walked=true;
								               }           
					      else if(near_move == 3 &&          /*ante katw */
		                  (eco.get_terrain()[x+1][y]).get_token()==place){
		  	                 set_point(x+1,y);
					         walked=true;
								               }              
					      else if(near_move == 4 &&          /*ante katw deksia*/
		                  (eco.get_terrain()[x+1][y+1]).get_token()==place){
		  	                 set_point(x+1,y+1);
					         walked=true;
								               }
					      else if(near_move == 5 &&          /*ante  deksia*/
		                  (eco.get_terrain()[x][y+1]).get_token()==place){
		  	                 set_point(x,y+1);
					         walked=true;
								               }  
	                   if(counter==250) break;			                 
	                                        }}   
			    else if(y==0){
                       while(walked == false){    //perni apo 1 ews 3 pi8anes thesis
					    counter++;
					    near_move=(3*(double)rand()/RAND_MAX )+1; 						                        
                           if(near_move == 1 &&          /*ante  deksia*/
		                     (eco.get_terrain()[x][y+1]).get_token()==place){
		  	                   set_point(x,y+1);
					           walked=true;
						  		               }  
					      else if(near_move == 2 &&          /*ante katw deksia*/
		                  (eco.get_terrain()[x+1][y+1]).get_token()==place){
		  	                 set_point(x+1,y+1);
					         walked=true;
								               }
					      else if(near_move == 3 &&          /*ante katw */
		                  (eco.get_terrain()[x+1][y]).get_token()==place){
		  	                 set_point(x+1,y);
					         walked=true;
								               }  										   						  		               
   					if(counter==250) break;			     			
   											   }}
			    else if(y==size){
                       while(walked == false){    //perni apo 1 ews 3 pi8anes thesis
					    counter++;
					    near_move=(3*(double)rand()/RAND_MAX )+1; 						   			              																									   											      			   			   
					         if(near_move == 1 &&          /*ante  aristera*/
		                  (eco.get_terrain()[x][y-1]).get_token()==place){
		  	                 set_point(x,y-1);
					         walked=true;
								               }   
					      else if(near_move == 2 &&          /*ante katw aristera*/
		                  (eco.get_terrain()[x+1][y-1]).get_token()==place){
		  	                 set_point(x+1,y-1);
					         walked=true;
								               }
					      else if(near_move == 3 &&          /*ante katw */
		                  (eco.get_terrain()[x+1][y]).get_token()==place){
		  	                 set_point(x+1,y);
					         walked=true;
								               }  											   						  		               
   					if(counter==250) break;			     				
   											   }}   											   
	            }
		else if(x==size){
              if(y>0 && y<size){
                       while(walked == false){    //perni apo 1 ews 5 pi8anes thesis
					    counter++;
					    near_move=(5*(double)rand()/RAND_MAX )+1; 	
					         if(near_move == 1 &&          /*ante  aristera*/
		                  (eco.get_terrain()[x][y-1]).get_token()==place){
		  	                 set_point(x,y-1);
					         walked=true;
								               }     
					      else if(near_move == 2 &&          /*ante panw aristera*/
		                  (eco.get_terrain()[x-1][y-1]).get_token()==place){
		  	                 set_point(x-1,y-1);
					         walked=true;
								               }            
					      else if(near_move == 3 &&          /*ante panw */
		                  (eco.get_terrain()[x-1][y]).get_token()==place){	
					     	 set_point(x-1,y);
						     walked=true;
						                    }             
					      else if(near_move == 4 &&          /*ante panw deksia*/
		                  (eco.get_terrain()[x-1][y+1]).get_token()==place){
		  	                 set_point(x-1,y+1);
					         walked=true;
								               }   
					      else if(near_move == 5 &&          /*ante  deksia*/
		                  (eco.get_terrain()[x][y+1]).get_token()==place){
		  	                 set_point(x,y+1);
					         walked=true;
								               }  
	                   if(counter==250) break;			                
	                                        }}   
			    else if(y==0){
                       while(walked == false){    //perni apo 1 ews 3 pi8anes thesis
					     counter++;
					    near_move=(3*(double)rand()/RAND_MAX )+1; 						   			              																									   											      			   			   
                           if(near_move == 1 &&          /*ante  deksia*/
		                     (eco.get_terrain()[x][y+1]).get_token()==place){
		  	                   set_point(x,y+1);
					           walked=true;
						  		               }  
					      else if(near_move == 2 &&          /*ante panw deksia*/
		                  (eco.get_terrain()[x-1][y+1]).get_token()==place){
		  	                 set_point(x-1,y+1);
					         walked=true;
								               } 
					      else if(near_move == 3 &&          /*ante panw */
		                  (eco.get_terrain()[x-1][y]).get_token()==place){	
					     	 set_point(x-1,y);
						     walked=true;
						                    }											   						  		               
   					if(counter==250) break;			     				
   											   }}
			    else if(y==size){
                       while(walked == false){    //perni apo 1 ews 3 pi8anes thesis
					    counter++;
					    near_move=(3*(double)rand()/RAND_MAX )+1; 						   			              																									   											      			   			   
					         if(near_move == 1 &&          /*ante  aristera*/
		                  (eco.get_terrain()[x][y-1]).get_token()==place){
		  	                 set_point(x,y-1);
					         walked=true;
								               }   
					      else if(near_move == 2 &&          /*ante panw aristera*/
		                  (eco.get_terrain()[x-1][y-1]).get_token()==place){
		  	                 set_point(x-1,y-1);
					         walked=true;
								               }
					      else if(near_move == 3 &&          /*ante panw */
		                  (eco.get_terrain()[x-1][y]).get_token()==place){
		  	                 set_point(x-1,y);
					         walked=true;
								               }  											   						  		               
   						if(counter==250) break;			     			
   											   }} 
							  } 
				          
				          }							
/*//////////////////////////////////////////////////////////////////////////////*/			   
/*--------------------Carnivores_functions--------------------------------------*/
/*//////////////////////////////////////////////////////////////////////////////*/	
Carnivores::Carnivores(int size,int the_attack,int the_defence,int speed,
                       int the_neededFood,string name,bool hibernates,int max_size,
					   int max_speed,int maxneededFood,int maxdefence,int maxattack)
      :Animal(size,speed,name,0,hibernates,max_size,max_speed){
	  														   
	  	attack=the_attack;
		defence=the_defence;	
					
		max_attack=maxattack;
		max_defence=maxdefence;					
		
		neededFood=the_neededFood;
		max_neededFood=maxneededFood;
		
		token='C';
						                   }
void Carnivores::Raise_to_max(){
	attack=max_attack;
	defence=max_defence;
	neededFood=max_neededFood;
	Animal::Raise_to_max();
                               }						                   
void Carnivores::Raise(int increase_attack,int increase_defence,int increase_neededFood){
	if (attack<max_attack)
	      attack+=increase_attack;
	if(defence<max_defence)
		  defence+=increase_defence;
    if(neededFood<max_neededFood){
          neededFood+=increase_neededFood;
		  if(neededFood>max_neededFood) neededFood=max_neededFood;
				                 } 
                                                                                       }				                 
void Carnivores::Eat(Animal& x){
	 set_isHungry(false);	/*xortase to zow p katafere na to fai*/
	 x.set_isAlive(false);   /*psofa fagomeno zow!*/
	 set_hungerCount(0);  //midenise to poses meres exi na fai afu efage!
	 
	 }									
void Carnivores::Move(Ecosystem& eco){
	int near_move,x,y;
	int size;
	bool enter[8];
	bool walked=false;	
	 size=eco.get_terrainSize()-1;	
	  for(int i=0;i<8;i++)enter[i]=true; //arxika na benei
	  x=return_point().x;
	  y=return_point().y;
	  
      while(walked == false){    //perni apo 1 ews 8 pi8anes thesis
		   near_move=(8*(double)rand()/RAND_MAX )+1;
		   
			if(near_move == 1 && enter[0]==true){            /*ante panw aristera*/
		           if(x-1>=0 && y-1>=0 ){
					   set_point(x-1,y-1);
			           walked=true;
						                }
				   else
				       enter[0]=false;    //wste na mhn ksanampei
						                         }    						                                       
		    else if(near_move == 2 && enter[1]==true){      /*ante panw*/
	               if(x-1>=0){	      
		  	           set_point(x-1,y);
					   walked=true;
				             }
				   else
				       enter[1]=false;          
								                      }             								                      
			else if(near_move == 3 && enter[2] == true){        /*ante panw deksia*/
		  	       if(x-1>=0 && y+1<=size){   
		  	           set_point(x-1,y+1);
					   walked=true;
								          }
					else
					    enter[2]=false;
					        			            }             
		    else if(near_move == 4 && enter[3] == true){        /*ante deksia*/
		  	       if(y+1<=size){        
		  	            set_point(x,y+1);
					    walked=true;
					            }
				   else
					    enter[3]=false;            
								                    }
								                    
	        else if(near_move == 5 && enter[4] == true){        /*ante katw deksia*/
		  	        if(x+1<=size && y+1<=size){      
		  	             set_point(x+1,y+1);
				         walked=true;
					                          }
					else
					    enter[4]=false;            
								                    }                     
	        else if(near_move == 6 && enter[5] == true){        /*ante katw */
		  	        if(x+1<=size){        
		  	             set_point(x+1,y);
				         walked=true;
				                 }
					else
					    enter[5]=false;            
								                    }  
	        else if(near_move == 7 && enter[6] == true){        /*ante katw aristera*/
		  	        if(x+1<=size && y-1>=0){   
		  	             set_point(x+1,y-1);
				         walked=true;
					                          }
					else
					    enter[6]=false;            
								                    }  
	        else if(near_move == 8 && enter[7] == true){        /*ante aristera*/
		  	        if(y-1>=0){        
		  	             set_point(x,y-1);
				         walked=true;
			                  }
					else
					    enter[7]=false;            
								                    }  
				
					  	    }      	
						              }
/*=========accessors===============*/
int Carnivores::return_attack(){
	return attack;
	                           }
int Carnivores::return_defence(){
	return defence;
		                        }
int Carnivores::return_neededFood(){
	return neededFood;
                                   }
char Carnivores::return_token(){
    return token;
                               }
/*=================================*/							   			  
/*//////////////////////////////////////////////////////////////////////////////*/			   
/*--------------------Carnivores_animals_functions------------------------------*/
/*//////////////////////////////////////////////////////////////////////////////*/                                                   
Fox::Fox(): Carnivores(1,1,1,1,2,"[Fox]",false,4,6,6,5,5){
								    /*size,atack,defence,speed,?nf,name,hibernates*/                                                  
             set_lives_in('"');   //gia na min megalwsw kialo ta panw perasmata
									          }
void Fox::Raise(){
		Animal::Raise(1,1);	/*increase size,speed,neededFood*/
		Carnivores::Raise(1,1,1);	/*increase attack,defence*/		
		         }
void Fox::Eat(Animal& x){
	 if( x.return_token() == 'H'){          /*an einai fitofago*/
	       if(x.return_size() <= return_size() &&
	          x.return_speed() < return_speed() && x.return_name() != "[Salmon]"){
			     Carnivores::Eat(x);
			 				                                                   }
			                     }
     else if(x.return_token() == 'C'){      /*an einai sarkofago*/
           if(x.return_size() < return_size())
		   		 Carnivores::Eat(x);		
		   else	if(x.return_size() == return_size() &&
                   return_attack() > ((Carnivores&)x).return_defence() )
		         Carnivores::Eat(x);		       
								     }
					    }
void Fox::Move(Ecosystem& eco){
		         Carnivores::Move(eco);

	             }
/***************************************************************************/    
Wolf::Wolf(): Carnivores(1,2,2,2,2,"[Wolf]",false,7,8,8,6,8){
								    /*size,atack,defence,speed,?nf,name,hibernates*/   
    double random;
    random=101*(double)rand()/RAND_MAX;
    if (random<=50)    //50% na zi se pediada
         set_lives_in('"');   //gia na min megalwsw kialo ta panw perasmata
    else
         set_lives_in('^');   //gia na min megalwsw kialo ta panw perasmata
									     }                                               
void Wolf::Raise(){
		Animal::Raise(1,2);	/*increase size,speed*/
		Carnivores::Raise(2,2,2);	/*increase attack,defence,neededFood*/	
		       }	    
void Wolf::Eat(Animal& x){
	 if( x.return_token() == 'H'){          /*an einai fitofago*/
	       if(x.return_size() <= return_size() &&
	          x.return_speed() < return_speed() && x.return_name() != "[Salmon]"){
			     Carnivores::Eat(x);
			 				                                                   }
			                     }
     else if(x.return_token() == 'C'){      /*an einai sarkofago*/
           if(x.return_size() < return_size())
		   		 Carnivores::Eat(x);		
		   else	if(x.return_size() == return_size() &&
                   return_attack() > ((Carnivores&)x).return_defence() )
		         Carnivores::Eat(x);		       
								     }
					    } 
void Wolf::Move(Ecosystem& eco){
		         Carnivores::Move(eco);

	             }	   
/***************************************************************************/									          										  	
Bear::Bear(): Carnivores(3,6,6,4,5,"[Bear]",true,10,4,10,10,10){ 	
								    /*size,atack,defence,speed,?nf,name,hibernates*/         
   set_lives_in('^');   //gia na min megalwsw kialo ta panw perasmata
								       	}                                         
 void Bear::Raise(){
		Animal::Raise(2,0);	/*increase size,speed*/
		Carnivores::Raise(2,2,2);	/*increase attack,defence,neededFood*/	
		       }	  
void Bear::Eat(Animal& x){ 
	 if( x.return_token() == 'H'){
	 	 if(return_speed() > x.return_speed())
	 	    Carnivores::Eat(x);
			                     }
	 else if(x.return_token() == 'C' && x.return_name() != "[Bear]"){
	 	  if(return_attack() > ((Carnivores&)x).return_defence() )
		     Carnivores::Eat(x);
			      				     }	    
				          }
void Bear::Move(Ecosystem& eco){

	         Carnivores::Move(eco);
	             }
/***************************************************************************/									          
	
	
	
	
	
	
	
	
	
	
	                                                 
