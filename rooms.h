#pragma once
#ifndef ROOMS_H
#define ROOMS_H

class Room
{
	public:
		void set_student_a(int x);
		void set_student_b(int x);
		void set_student_c(int x);
		void set_student_d(int x);
		void set_RMS(float x);
		int get_student_a();
		int get_student_b();
		int get_student_c();
		int get_student_d();
		float get_RMS();
	
	private:
		int student_a = 0;
		int student_b = 0;
		int student_c = 0;
		int student_d = 0;
		float RMS = 0.0;
};

#endif
