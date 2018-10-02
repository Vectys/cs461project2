#include "rooms.h"

void Room::set_student_a(int x)
{
	student_a = x;
}

void Room::set_student_b(int x)
{
	student_b = x;
}

void Room::set_student_c(int x)
{
	student_c = x;
}

void Room::set_student_d(int x)
{
	student_d = x;
}

void Room::set_RMS(float x)
{
	RMS = x;
}


int Room::get_student_a()
{
	return student_a;
}

int Room::get_student_b()
{
	return student_b;
}

int Room::get_student_c()
{
	return student_c;
}

int Room::get_student_d()
{
	return student_d;
}

float Room::get_RMS()
{
	return RMS;
}
