#include <iostream>
#include <ctime>
#include <vector>
#include <list>

using namespace std;
/* UPDATES
	���� �˰���
	0.1 - ���۽��� (2020-03-26)
UPDATES */



// individual �� ��
#define population 50
// �� chromosome�� �������� ��
#define genes 8
// ���� �θ��� �� (���� ��� ����)
#define top 15

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
	int chromosome[genes]; // ������
	int fitness; // �������� ����
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
// ���� : 
// �ʱ�ȭ (Initalize) OK
// ���� (Selection) OK
// ���� (Crossover) OK, ������ �� �߰��ؾ���
// ���� (Mutation)
// ��ġ (Replace) OK
// �ݺ� (Loop) OK
// ���� (Quit) OK
void Initalize()
{
	for (int start = 0; start < population; start++)
	{
		individual ind;
		for (int i = 0; i < genes; i++)
		{
			ind.chromosome[i] = Random(0, 1); // �ٲ����
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
		GetFitness(&ind);
		individuals.push_back(ind);
		individuals.sort(Comp);
	}
}

void Mutation()
{
	int m = Random(0, 100);
	if (m == 0)
	{
		int a = Random(0, population - 1);
		int b = Random(0, genes - 1);
		int c = Random(0, 1); // �ٲ����
		int num = 0;
		for (auto it : individuals)
		{
			if (num == a)
			{
				it.chromosome[b] = c;
				return;
			}
			num++;
		}
	}

}

void Reset()
{
	top_individuals.clear();
}

void Print()
{
	list<individual>::iterator iter = individuals.begin();
	for (iter; iter != individuals.end(); iter++)
	{
		for (int i = 0; i < genes; i++)
		{
			cout << iter->chromosome[i];
		}
		printf(" [ %d ] \t", iter->fitness);
		cout << endl;
	}
}

int main(void)
{
	srand(time(0));
	Initalize();
	Print();
	int age = 1;
	cout << age << " ����" << endl;
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
			Mutation();
			Print();
			age++;
			cout << age << " ����" << endl;
		}
	}
	
	return 0;
}

