#include <string>


class Plants{
	private:
		std::string name;
		point position;
		char token;
		double breedingProb;
		double illnessProb;
		int life;
		int lifefactor;

	public:
		Plants(point, std::string, char, double, double, int, int);


		char get_token();
		int get_life();
		int get_lifefactor();
		double get_breedingProb();
		double get_illnessProb();
		virtual int get_size(){}
		void set_life(int);

		virtual int LoseLife(int) = 0;
		virtual void grow() = 0;

		bool NormalBreeding();		/*no need to be virtual*/
};



class Seedless : public Plants{

	private:

	public:
		Seedless(point, std::string, char, double, double, int, int);

		int LoseLife(int);
		void grow();

};


class Grass : public Seedless{

	private:

	public:
		Grass(point);
		
};


class Algae : public Seedless{

	private:

	public:
		Algae(point);
};



////////////////////////////////////////////////////////////////////////



class Seeded : public Plants{

	private:
		int size;
		int foliage;
		int seeds;

	public:
		Seeded(point, std::string, char, double, double, int, int, int, int, int);
		
		int get_size();
		int LoseLife(int);
		void grow();
};



class Oak : public Seeded{

	private:

	public:
		Oak(point);
	
};


class Pine : public Seeded{

	private:

	public:
		Pine(point);
		
};


class Maple : public Seeded{

	private:

	public:
		Maple(point);
		
};
