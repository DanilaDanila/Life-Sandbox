#ifndef LAKE_HPP
#define LAKE_HPP

#include "fish.hpp"
#include <vector>

#define PROGRAM_EMPTY 0
#define PROGRAM_RANDOM 1
#define PROGRAM_INSTALLED 2

class lake
{
private:
	std::vector<vec2> food;
	std::vector<fish> fishes;

	vec2 size;
	int food_count;
	int first_generation_fishes_count;
	int max_fishes_count;
	int type;
	float *program;

	bool evolve;

	int divine_intervention_count;

	float *createNoneProgram();
	float *createRandomProgram();
	void mutateProgram(float*);
	void copyProgram(float *input,float *copy);

	void addFoodToMax();
	int getNearestFood(int n);
	int getNearestPreyFish(int n);
	int getNearestPredatorFish(int n);

	void createFish(float *program);
	void createChildFish(float *program, vec2 pos);
	void DivineIntervention(float *program);

public:
	lake();

	void ragnarok();

	void setLakeSize(vec2);

	vec2 getLakeSize();

	std::vector<vec2> getFood();

	std::vector<fish> getFish();

	void setEvolve(bool);

	void setFoodCount(int);

	void setFirstGenerationFishesCount(int);

	void setFirstGenerationProgramType(int);

	void setMaxFishesCount(int);

	void setFirstGenerationProgram(float*);

	void setDivineInterventionCount(int);

	void createFirstGeneration();

	void update(float time);

	~lake();
};

#endif