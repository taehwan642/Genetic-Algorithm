#include <iostream>
#include <ctime>
#include <vector>
#include <list>

using namespace std;
/* UPDATES
	Genetic Algorithm
	0.1 - START (2020-03-26)
	0.2 - Mutate Bug Fix
UPDATES */

/* NEED TO DO
	Adding Two More Crossovers
NEED TO DO */

// individual 의 수
#define population 50
// 각 chromosome의 유전자의 수
#define genes 8
// 상위 부모의 수 (순위 기반 선택)
#define top 15
// 각 유전자의 최대 값 0~9
#define geneval 9


list<class individual> individuals;
vector<class individual> top_individuals;

int Random(int start, int end)
{
	int range = (end - start) + 1;
	int random_int = start + (rand() % range);
	return random_int;
}


class individual
{
public:
	int chromosome[genes]; // 유전자
	int fitness; // 유전자의 점수
};

bool Comp(individual a, individual b)
{
	return a.fitness > b.fitness;
}

int GetFitness(individual* in)
{
	int a = (in->chromosome[0] + in->chromosome[1]) - (in->chromosome[2] + in->chromosome[3]) +
		(in->chromosome[4] + in->chromosome[5]) - (in->chromosome[6] + in->chromosome[7]);
	in->fitness = a;
	return a;
}

individual Single_Point_Crossover(individual* a, individual* b)
{
	int r = Random(0, genes - 1);
	individual child;
	for (int i = 0; i < genes; i++)
	{
		child.chromosome[i] = a->chromosome[i];
	}
	for (int j = r; j < genes; j++)
	{
		child.chromosome[j] = b->chromosome[j];
	}
	GetFitness(&child);
	return child;
}
// 절차 : 
// 초기화 (Initialize) OK
// 선택 (Selection) OK
// 교차 (Crossover) OK, 하지만 더 추가해야함
// 변이 (Mutation) OK
// 대치 (Replace) OK
// 반복 (Loop) OK
// 종료 (Quit) OK
void Initalize()
{
	for (int start = 0; start < population; start++)
	{
		individual ind;
		for (int i = 0; i < genes; i++)
		{
			ind.chromosome[i] = Random(0, geneval); // 바꿔야함
		}
		GetFitness(&ind);
		individuals.push_back(ind);
		individuals.sort(Comp);
	}
}

void Selection()
{
	int i = 0;
	for (auto it : individuals)
	{
		if (i == top)
			break;
		top_individuals.push_back(it);
		i++;
	}
}

void Crossover()
{
	individuals.clear();
	for (int start = 0; start < population; start++)
	{
		individual ind;
		int x = Random(0, top - 1);
		int y = Random(0, top - 1);
		ind = Single_Point_Crossover(&top_individuals[x], &top_individuals[y]);
		int m = Random(0, 100);
		if (m == 0)
		{
			int a = Random(0, population - 1);
			int b = Random(0, genes - 1);
			int c = Random(0, geneval); // 바꿔야함
			ind.chromosome[b] = c;
		}
		GetFitness(&ind);
		individuals.push_back(ind);
		individuals.sort(Comp);
	}
}

void Reset()
{
	top_individuals.clear();
}

void Print()
{
	int num = 0;
	list<individual>::iterator iter = individuals.begin();
	for (iter; iter != individuals.end(); iter++)
	{
		for (int i = 0; i < genes; i++)
		{
			cout << iter->chromosome[i];
		}
		printf(" [ %d ]  %d \t", iter->fitness, num);
		num++;
		cout << endl;
	}
}

int main(void)
{
	srand(time(0));
	Initalize();
	Print();
	int age = 0;
	cout << age << " 세대" << endl;
	while (true)
	{
		int num = 0;
		scanf_s("%d", &num);
		for (int i = 0; i < num; i++)
		{
			system("cls");
			Reset();
			Selection();
			Crossover();
			Print();
			age++;
			cout << age << " 세대" << endl;
		}
	}
	
	return 0;
}

