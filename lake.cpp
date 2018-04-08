#include "lake.hpp"
#include "executor.hpp"

float *lake::createNoneProgram()
{
	float *prog=new float[PROGRAM_LEN];
	for(int i=0;i<PROGRAM_LEN;i++)
		prog[i]=0;
	return prog;
}

float *lake::createRandomProgram()
{
	float *prog=new float[PROGRAM_LEN];
	prog[0]=rand()%2;
	for(int i=1;i<PROGRAM_LEN;i++)
		prog[i]=rand()%PROGRAM_LEN;
	prog[12]=rand()%100-50;
	prog[13]=2.0;
	return prog;
}

void lake::mutateProgram(float *p)
{
	if(rand()%3==0)
	{	
		p[0]=rand()%2;
	}
	p[rand()%(PROGRAM_LEN-21)+21]=rand()%PROGRAM_LEN;
}

void lake::copyProgram(float *input,float *copy)
{
	for(int i=0;i<PROGRAM_LEN;i++)
		copy[i]=input[i];
}

void lake::addFoodToMax()
{
	while(food.size()<food_count)
	{
		food.push_back(vec2());
		food[food.size()-1]=vec2(rand()%int(size.x),rand()%int(size.y));
	}
}

int lake::getNearestFood(int n)
{
	if(food.size()==0) return -1;
	int min=0;
	float d=distance(fishes[n].getPosition(),food[min]);

	for(int i=1;i<food.size();i++)
		if(distance(fishes[n].getPosition(),food[i])<d)
		{
			min=i;
			d=distance(fishes[n].getPosition(),food[i]);
		}
	return min;
}	

int lake::getNearestPreyFish(int n)
{
	int min=-1;

	for(int i=0;i<fishes.size();i++)
		if((n!=i) && (fishes[i].getProgram()[0]==0))
		{
			min=i;
			break;
		}
	if(min==-1) return -1;

	float d=distance(fishes[n].getPosition(),fishes[min].getPosition());

	for(int i=0;i<fishes.size();i++)
		if((n!=i) && (fishes[i].getProgram()[0]==0))
			if(distance(fishes[i].getPosition(),fishes[n].getPosition())<d)
			{
				min=i;
				d=distance(fishes[i].getPosition(),fishes[n].getPosition());
			}
	return min;
}	

int lake::getNearestPredatorFish(int n)
{
	int min=-1;

	for(int i=0;i<fishes.size();i++)
		if((n!=i) && (fishes[i].getProgram()[0]==1))
		{
			min=i;
			break;
		}
	if(min==-1) return -1;

	float d=distance(fishes[n].getPosition(),fishes[min].getPosition());

	for(int i=0;i<fishes.size();i++)
		if((n!=i) && (fishes[i].getProgram()[0]==1))
			if(distance(fishes[i].getPosition(),fishes[n].getPosition())<d)
			{
				min=i;
				d=distance(fishes[i].getPosition(),fishes[n].getPosition());
			}
	return min;
}

void lake::createFish(float *prog)
{
	fishes.push_back(fish());
	fishes[fishes.size()-1].setProgram(prog);
	fishes[fishes.size()-1].setPosition(vec2(rand()%int(size.x),rand()%int(size.y)));
	fishes[fishes.size()-1].setRotation((rand()%int(2*pi*1000)-pi*1000)/1000.0);
	fishes[fishes.size()-1].setLakeSize(size);
	fishes[fishes.size()-1].setTimerDelay(rand()%3+2);

	fishes[fishes.size()-1].restartTimer();
}

void lake::createChildFish(float *prog, vec2 pos)
{
	float *new_program=new float[PROGRAM_LEN];
	copyProgram(prog, new_program);

	if(rand()%5==0) mutateProgram(new_program);

	fishes.push_back(fish());
	fishes[fishes.size()-1].setProgram(new_program);
	fishes[fishes.size()-1].setPosition(pos);
	fishes[fishes.size()-1].setRotation((rand()%int(2*pi*1000)-pi*1000)/1000.0);
	fishes[fishes.size()-1].setLakeSize(size);
	fishes[fishes.size()-1].setTimerDelay(rand()%3+2);
}

void lake::DivineIntervention(float *prog)
{
	float *new_program=new float[PROGRAM_LEN];
	copyProgram(prog,new_program);
	for(int i=0;i<divine_intervention_count;i++)
	{
		new_program[0]=rand()%2;
		createFish(new_program);
	}
}

lake::lake() 
{
	program=new float[PROGRAM_LEN];
	copyProgram(createNoneProgram(),program);
	evolve=false;
}

void lake::ragnarok() { fishes.clear(); }

void lake::setLakeSize(vec2 s) { size=s; }

vec2 lake::getLakeSize() { return size; }

std::vector<vec2> lake::getFood() { return food; }

std::vector<fish> lake::getFish() { return fishes; }

void lake::setEvolve(bool b) { evolve=b; }

void lake::setFoodCount(int c) { food_count=c; }

void lake::setFirstGenerationFishesCount(int c) { first_generation_fishes_count=c; }

void lake::setFirstGenerationProgramType(int t) { type=t; } 

void lake::setMaxFishesCount(int i) { max_fishes_count=i; }

void lake::setFirstGenerationProgram(float *p) { copyProgram(p,program); }

void lake::setDivineInterventionCount(int c) { divine_intervention_count=c; }

void lake::createFirstGeneration()
{
	addFoodToMax();

	for(int i=0;i<first_generation_fishes_count;i++)
	{
		if(type==PROGRAM_EMPTY) createFish(createNoneProgram());
		else
		if(type==PROGRAM_RANDOM) createFish(createRandomProgram());
		else
		if(type==PROGRAM_INSTALLED) createFish(program);
	}
}

void lake::update(float time)
{
	while(fishes.size()>max_fishes_count)
		fishes.erase(fishes.begin());

	for(int i=0;i<fishes.size();i++)
	{
		int nearest_food=getNearestFood(i);
		int nearest_prey=getNearestPreyFish(i);
		int nearest_predator=getNearestPredatorFish(i);

		vec2 n_food=(nearest_food!=-1)?food[nearest_food]:fishes[i].getPosition();
		vec2 n_prey=(nearest_prey!=-1)?fishes[nearest_prey].getPosition():fishes[i].getPosition();
		vec2 n_predator=(nearest_predator!=-1)?fishes[nearest_predator].getPosition():fishes[i].getPosition();

		fishes[i].writeToRegisters(n_food, n_prey, n_predator);
	}

	for(int i=0;i<fishes.size();i++)
		execute(fishes[i].getProgram(), PROGRAM_LEN);

	for(int i=0;i<fishes.size();i++)
		fishes[i].update(time);

	for(int i=0;i<fishes.size();i++)
		if(fishes[i].getProgram()[0]==0)
			for(int j=0;j<food.size();j++)
				if(fishes[i].getHead().isPointInside(food[j]))
				{
					fishes[i].health+=5.0;
					food.erase(food.begin()+j);
				}

	for(int i=0;i<fishes.size();i++)
		if(fishes[i].getProgram()[0]==1)
			for(int j=0;j<fishes.size();j++)
				if((i!=j) && (fishes[j].isLife()))
					if(fishes[i].getHead().intersects(fishes[j].getBody()))
					{
						fishes[i].health+=5.0;
						fishes[j].health-=100.0;
					}

	for(int i=fishes.size()-1;i>=0;i--)
		if(!fishes[i].isLife()) 
		{
			if(fishes.size()==1)
			{
				float *new_program=new float[PROGRAM_LEN];
				copyProgram(fishes[i].getProgram(), new_program);
				fishes.erase(fishes.begin()+i);
				DivineIntervention(new_program);
			}
			else
			fishes.erase(fishes.begin()+i);
		}

	for(int i=0;i<fishes.size();i++)
		fishes[i].health-=0.02*time;

	if(evolve)
	{
		for(int i=0;i<fishes.size();i++)
		if(fishes[i].isTimer() && (fishes.size()<max_fishes_count))
		{
			createChildFish(fishes[i].getProgram(), fishes[i].getPosition());
			fishes[i].restartTimer();
		}
	}
	addFoodToMax();
}

lake::~lake() {}