#include<cstdlib>
#include<iostream>
//List class definition

class Animal;
typedef Animal* Data;

class List
{

        struct Node
        {
                Data    data;
                Node*   next;

                Node (Data data_, Node* next_ = NULL) : data(data_), next(next_) {}
        };


        Node*           first;
        Node*           last;
        unsigned int    nodes;
public:
    List():nodes(0),first(NULL),last(first){/*cout<<"egine lista"<<endl;*/}
   ~List ()
        {
                Node *temp, *i = first;
                while (i != NULL)
                {
                        temp = i;
                        i = i->next;
                        delete temp;
                }
        }
    int size(){return nodes;}
    void insert(Data);
    void move_animals(Ecosystem&);
    void eat_the_animals(Tile&);
    Animal* return_animal(int k);
    void print();
    void out();
    void apoxorish(Data);
    void apoxorish_kai_diagrafh(Data);
    void grow();
    void breed(point);
    void remove_dead_animals();
    void check_hunger();
    void reinitialize_herbivores_hunger();
    void reinitialize_carnivores_hunger();
    void set_in_hibernation(bool value);

};

