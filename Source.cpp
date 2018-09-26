#include <iostream>
#include <fstream>

using namespace std;

void main()
{

	//read in the data (200 students)

	//assign all students to a room arbitrarily (50 rooms)

	/*compute average room happiness with Root-Mean-Square
	RMS: find happiness of AB, AC, AD, BC, BD, CD; square each score; take the square root of the average of that */

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

}