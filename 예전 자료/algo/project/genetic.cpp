#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <ctime>
#include "defines.h"
using std::cout;
using std::vector;

int generation=0;

class Chromosome{
public:
    Chromosome(int *genes, int fitness){
        for(int i=0; i<BOARD_SIZE; i++)
            this->Genes[i] = genes[i];
        this->Fitness = fitness;
    }
    int Genes[BOARD_SIZE];
    int Fitness;
};

//returns a random integer between x and y
inline int RandInt(int x,int y){
	return rand()%(y-x+1)+x;
}

//returns a random float between zero and 1
inline float RandFloat(){
	return (rand())/(RAND_MAX+1.0);
}

// swap
void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

vector<Chromosome> generate_parent();
int get_fitness(int *guess);
vector<Chromosome> selection(const vector<Chromosome> &chromo_list);
void mutation(vector<Chromosome> &chromo_list);
void crossover(vector<Chromosome> &chromo_list);

vector<Chromosome> generate_parent(){
    vector<Chromosome> chromosome_list; 
    for(int i=0; i<POPULATION_SIZE; i++){
        int genes[BOARD_SIZE];
        // 12171833 이정우
        vector<int> box;
        for(int i=0; i<BOARD_SIZE; i++) box.push_back(i);
        for(int i=0; i<BOARD_SIZE; i++){
            int k = RandInt(0, box.size()-1);
            genes[i] = box[k];
            box.erase(box.begin()+k);
        }
        int fitness = get_fitness(genes);
        chromosome_list.push_back(Chromosome(genes, fitness));
    }
    return chromosome_list;
}

int get_fitness(int *guess){
    int fitness = 0;
    for(int i=0; i<BOARD_SIZE; i++){
        bool flag = true;
        for(int j=0; j<i; j++){
            if (guess[j]==guess[i] || i-j==abs(guess[i]-guess[j])){
                flag = false;
                break;
            }
        }
        if(flag) fitness++;
        else break;
    }
    return fitness;
}

Chromosome update_fitness(vector<Chromosome> &chromo_list){
    Chromosome most_fit = chromo_list[0];
    for(int i=0; i<chromo_list.size(); i++){
        chromo_list[i].Fitness = get_fitness(chromo_list[i].Genes);
        if(most_fit.Fitness < chromo_list[i].Fitness){
            most_fit = Chromosome(chromo_list[i].Genes, chromo_list[i].Fitness);
        }
    }
    return most_fit;
}

void scaling(vector<Chromosome> &chromo_list) {
    //get Total fitness
    float fitness_sum = 0;
    for(auto chromo : chromo_list){
        fitness_sum += chromo.Fitness;
    }   
	float mean = fitness_sum/chromo_list.size();
	
    // get variation
    float var = 0;
	for (int i=0; i<chromo_list.size(); i++)
		var += (chromo_list[i].Fitness - mean)*(chromo_list[i].Fitness - mean);
    var /= chromo_list.size();

	// get standard deviation
	float stddev = sqrt(var);
	
	for(int i=0; i<chromo_list.size(); i++) {
		float temp = 1 + (chromo_list[i].Fitness-mean)/2 * stddev;
		chromo_list[i].Fitness = temp;
	}
}

// Roulette wheel Selection
vector<Chromosome> selection(vector<Chromosome> &chromo_list){
    vector<Chromosome> child_list;

    scaling(chromo_list);
    
    //get Total fitness
    float fitness_sum = 0;
    for(auto chromo : chromo_list){
        fitness_sum += chromo.Fitness;
    }   
    
    //get percent of Total
    vector<float> fitness_percent_list;
    for(auto chromo : chromo_list){
        fitness_percent_list.push_back(float(chromo.Fitness)/fitness_sum);
    }
    // 12171833 이정우
    //get accumulation  0~1
    fitness_sum = 0;
    vector<float> fitness_accum_list;
    for(auto fitness_percent : fitness_percent_list){
        fitness_sum += fitness_percent;
        fitness_accum_list.push_back(fitness_sum);
    }

    // Selection
    for(int i=0; i<chromo_list.size(); i++){
        float rand = RandFloat();
        int before = 0;
        for(int j=0; j<fitness_accum_list.size(); j++){
            if(before < rand && rand <= fitness_accum_list[j]){
                child_list.push_back(chromo_list[j]);
                break;
            }
            before = fitness_accum_list[j];
        }
    }
    return child_list;
}

// Insertion Mutation
void mutation(vector<Chromosome> &chromo_list){
    // 12171833 이정우
    for(int i=0; i<chromo_list.size(); i++){
        if(RandFloat() < MUTATION_RATE) {
            int from = RandInt(0, BOARD_SIZE-1);
            int to = from;
            while(to==from) to = RandInt(0, BOARD_SIZE-1);
            int d = (to-from)/abs(to-from);
            while(from != to){
                swap(chromo_list[i].Genes[from], chromo_list[i].Genes[from+d]);
                from+=d;
            }
        }
    }
}

// OBX Crossover 
void crossover(vector<Chromosome> &chromo_list){
    for(int i=1; i<chromo_list.size(); i++){
        if(RandFloat() < CROSSOVER_RATE) {
            // find random position for exchange
            vector<int> positions;
            int Pos = RandInt(0, BOARD_SIZE-1);
            while (Pos < BOARD_SIZE) {              //12171833 이정우
                positions.push_back(Pos);
                Pos += RandInt(1, BOARD_SIZE-Pos);
            }

            // exchange value 
            Chromosome child1(chromo_list[i].Genes, chromo_list[i].Fitness);
            Chromosome child2(chromo_list[i-1].Genes, chromo_list[i-1].Fitness);
            int pos_idx=0;
            for(int j=0; j<BOARD_SIZE; j++){
                for(int k=0; k<positions.size(); k++){
                    if(child1.Genes[j] == chromo_list[i-1].Genes[positions[k]]){
                        child1.Genes[j] = chromo_list[i-1].Genes[positions[pos_idx]];
                        pos_idx++;
                        break;
                    }
                    if(pos_idx==positions.size()) break;
                }
            }
            pos_idx=0;
            for(int j=0; j<BOARD_SIZE; j++){
                for(int k=0; k<positions.size(); k++){
                    if(child2.Genes[j] == chromo_list[i].Genes[positions[k]]){
                        child2.Genes[j] = chromo_list[i].Genes[positions[pos_idx]];
                        pos_idx++;
                        break;
                    }
                    if(pos_idx==positions.size()) break;
                }
            }
            chromo_list[i-1] = child1;
            chromo_list[i] = child2;
        }
    }
}

vector<Chromosome> generate_child(vector<Chromosome> parent_list){
    vector<Chromosome> child_list;

    // Selection
    child_list = selection(parent_list);

    // Crossover
    crossover(child_list);

    // mutate
    mutation(child_list);

    return child_list;
}

Chromosome Epoch(vector<Chromosome> &chromo_list)
{
	int i, j = 0;

	// get most fitted Chromosome
	Chromosome pre_mostfit = update_fitness(chromo_list);
    // check success condition
	if (pre_mostfit.Fitness == SUCCESS_CONDITION) return pre_mostfit;

    vector<Chromosome> child_list = generate_child(chromo_list);
    chromo_list = child_list;

    generation++;
	return pre_mostfit;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

	// generate first
	vector<Chromosome> parent = generate_parent();

	// genrate child until satisfy success condition
    Chromosome most_fit = update_fitness(parent);
	while(true){
		most_fit = Epoch(parent);
		if (most_fit.Fitness == SUCCESS_CONDITION) break;
	}
	cout<<"finishing at "<<generation<<"th generation\n";

    // show chess board
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            if(most_fit.Genes[i]==j) cout<<"■ ";
            else cout<<"□ ";
        }
        cout<<"\n";
    }
    return 0;
}
