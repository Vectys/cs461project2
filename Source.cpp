#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "rooms.h"
#include <vector>

using namespace std;

float calc_RMS(int AB, int AC, int AD, int BC, int BD, int CD);
void main()
{
	srand(time(NULL));
	//bunch of loose variables
	vector<int> scores_1d;
	int scores_1d_x = 0;
	int scores_arr[200][200];
	//using e instead of a built in function because it's easier to read for me
	float e = 2.71828182845904523536f;
	Room rooms[50];
	int student_num = 0;
	int student_x = 0;
	int student_y = 0;
	float temp = 1500.0f;
	int iterations = 1;
	ifstream scores_file;
	int x;

	//open file
	//read in the data (200 students)
	scores_file.open("scores.txt");
	if (!scores_file)
	{
		cerr << "File did not open";
		exit(1);
	}
	//get scores
	while (scores_file >> x)
	{
		scores_1d.push_back(x);
	}
	//sort scores into a 2d array for easy table lookup
	for (int i = 0; i < scores_1d.size(); i++)
	{
		scores_arr[student_x][student_y] = scores_1d[i];
		student_x += 1;
		if (student_x >= 200)
		{
			student_y += 1;
			student_x = 0;
		}
	}
	//arbitrarily fill 50 rooms, get RMS
	for (int i = 0; i < 50; i++)
	{
		rooms[i].set_student_a(student_num);
		student_num++;
		rooms[i].set_student_b(student_num);
		student_num++;
		rooms[i].set_student_c(student_num);
		student_num++;
		rooms[i].set_student_d(student_num);
		student_num++;

		//assign these to variables just to make it easier to read; could put them in with the scores_arr value but way too long of a line
		int AB, AC, AD, BC, BD, CD = 0;
		AB = scores_arr[rooms[i].get_student_a()][rooms[i].get_student_b()];
		AC = scores_arr[rooms[i].get_student_a()][rooms[i].get_student_c()];
		AD = scores_arr[rooms[i].get_student_a()][rooms[i].get_student_d()];
		BC = scores_arr[rooms[i].get_student_b()][rooms[i].get_student_c()];
		BD = scores_arr[rooms[i].get_student_b()][rooms[i].get_student_d()];
		CD = scores_arr[rooms[i].get_student_c()][rooms[i].get_student_d()];
		float x = 0.0f;
		x = calc_RMS(AB, AC, AD, BC, BD, CD);
		rooms[i].set_RMS(x);
	}
	/*while (temp > 1)
	{
		temp = temp * .95;
		cout << temp << endl;
	} */
	int exchanges_attempted = 0;
	int exchanges_made = 0;
	bool still_truckin = true;
	while (still_truckin == true)
	{
		Room new_room;
		Room old_room;
		float iter_best = 0.0f;
		float iter_worst = 100.0f;
		float iter_avg = 0.0;
		float p = 0.0f;
		float old_RMS = 0.0f;
		float new_RMS = 0.0f;
		float difference = 0.0f;
		float prob = rand() / (float)RAND_MAX;
		int random_student = rand() % 4 + 1;
		int random_room_one = rand() % 49 + 1;
		int random_room_two = rand() % 49 + 1;
		old_room = rooms[random_room_one];
		old_RMS = old_room.get_RMS();
		if (random_student == 1)
		{
			new_room.set_student_a(rooms[random_room_one].get_student_a());
			rooms[random_room_one].set_student_a(rooms[random_room_two].get_student_a());
			rooms[random_room_two].set_student_a(new_room.get_student_a());
		}
		if (random_student == 2)
		{
			new_room.set_student_b(rooms[random_room_one].get_student_b());
			rooms[random_room_one].set_student_b(rooms[random_room_two].get_student_b());
			rooms[random_room_two].set_student_b(new_room.get_student_b());
		}
		if (random_student == 3)
		{
			new_room.set_student_c(rooms[random_room_one].get_student_c());
			rooms[random_room_one].set_student_c(rooms[random_room_two].get_student_c());
			rooms[random_room_two].set_student_c(new_room.get_student_c());
		}
		if (random_student == 4)
		{
			new_room.set_student_d(rooms[random_room_one].get_student_d());
			rooms[random_room_one].set_student_d(rooms[random_room_two].get_student_d());
			rooms[random_room_two].set_student_d(new_room.get_student_d());
		}
		int AB_n, AC_n, AD_n, BC_n, BD_n, CD_n = 0;
		AB_n = scores_arr[rooms[random_room_one].get_student_a()][rooms[random_room_one].get_student_b()];
		AC_n = scores_arr[rooms[random_room_one].get_student_a()][rooms[random_room_one].get_student_c()];
		AD_n = scores_arr[rooms[random_room_one].get_student_a()][rooms[random_room_one].get_student_d()];
		BC_n = scores_arr[rooms[random_room_one].get_student_b()][rooms[random_room_one].get_student_c()];
		BD_n = scores_arr[rooms[random_room_one].get_student_b()][rooms[random_room_one].get_student_d()];
		CD_n = scores_arr[rooms[random_room_one].get_student_c()][rooms[random_room_one].get_student_d()];
		new_RMS = calc_RMS(AB_n, AC_n, AD_n, BC_n, BD_n, CD_n);
		rooms[random_room_one].set_RMS(new_RMS);
		if (new_RMS < old_RMS)
		{
			
			difference = old_RMS - new_RMS;
			p = pow(e, -(difference / temp));
			if (prob < p)
			{
				exchanges_made += 1;
			}
			else
			{
				if (random_student == 1)
				{
					rooms[random_room_one].set_student_a(new_room.get_student_a());

				}
				if (random_student == 2)
				{
					rooms[random_room_one].set_student_b(new_room.get_student_b());
				}
				if (random_student == 1)
				{
					rooms[random_room_one].set_student_c(new_room.get_student_c());
				}
				if (random_student == 1)
				{
					rooms[random_room_one].set_student_d(new_room.get_student_d());
				}
				rooms[random_room_one].set_RMS(old_RMS);
			}
		}
		exchanges_attempted += 1;
		if (exchanges_made == 2000 || exchanges_attempted == 20000)
		{
			cout << "Iteration " << iterations << " ended." << "Temperature at: "<< temp << endl;
			for (int j = 0; j < 50; j++)
			{
				if (rooms[j].get_RMS() > iter_best)
				{
					iter_best = rooms[j].get_RMS();
				}
				else if (rooms[j].get_RMS() < iter_worst)
				{
					iter_worst = rooms[j].get_RMS();
				}
				iter_avg += rooms[j].get_RMS();
			}
			iter_avg = iter_avg / 50;
			cout << "Exchanges Made: " << exchanges_made << "          " << "Exchanges Attempted: " << exchanges_attempted << endl;
			cout << "Highest compatibility: " << iter_best << "          " << "Lowest compatibility: " << iter_worst << endl;
			cout << "Average: " << iter_avg << endl;
			temp = temp * .999;
			iterations += 1;
			if (exchanges_made == 0)
			{
				cout <<"System finished. Final values above." << endl;
				still_truckin = false;
			}
			exchanges_attempted = 0;
			exchanges_made = 0;
		}
	}

	/*randomly select 2 rooms, consider swapping those 2; need to find the difference between the two scores D
		formula to consider swap: P=e^(-D/T), where T is an arbitrary 'temperature'
		if the new score is higher, this is a net gain and we should take it
		if the new score is lower, compute the difference D and compute P
		set a random number between 0 and 1; if the value is lower than P, make the swap*/


	/*lower T by a value (T *.95) every 2,000 accepted exchanges OR 20,000 attempted exchanges; this is considered a new iteration
		At each end of iteration, report the best, worst and average score of the assignments
		AND the number of exchanges attempted AND made*/
	
	/*program ends when the system passes through all 20,000 exchanges without accepting any exchanges
		at the end of the program, report the best, worst and average matches*/
	
	
	system("pause");
	scores_file.close();

	

	




	

}


/*compute average room happiness with Root-Mean-Square
RMS: find happiness of AB, AC, AD, BC, BD, CD; square each score; take the square root of the average of that */
float calc_RMS(int AB, int AC, int AD, int BC, int BD, int CD)
{
	float RMS = 0.0f;
	//square the values
	AB = AB * AB;
	AC = AC * AC;
	AD = AD * AD;
	BC = BC * BC;
	BD = BD * BD;
	CD = CD * CD;
	//get the total value of all 6 relationships
	int total = AB + AC + AD + BC + BD + CD;
	//average
	float average = total / 6;
	//RMS yields overall happiness
	RMS = sqrt(average);
	return RMS;
}
