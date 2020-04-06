/*
  Trevor Schmidt
  CS - 235 Section 4
  Lab 01 - Grades
*/

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;


// Reads from an input file a person's name followed by all their exam scores
// Calculates and writes the average score for all students on each exam to an output file
// Then, writes each student's name to the output file followed by the student's score and grade on each exam.
int main(int argc, char* argv[])
{
	VS_MEM_CHECK               // enable memory leak check

	//Check Inputs / Outputs
	if (argc < 3)
	{
		cerr << "Please provide name of input and output files" << endl;
		return 1;
	}
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input" << endl;
		return 2;
	}
	ofstream out(argv[2]);
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output" << endl;
		return 3;
	}

	//Initiate number of students and exams from first line of input file
	int numStudents, numExams;
	in >> numStudents >> numExams;

	in.ignore(std::numeric_limits<int>::max(), '\n');

	//Create Array of Student's names
	string *dynamStudentArray;
	dynamStudentArray = new string[numStudents];

	//Create Array of Student's exam scores
	double **dynamScoresArray;
	dynamScoresArray = new double*[numStudents];
	for (int i = 0; i < numStudents; ++i)
	{
		dynamScoresArray[i] = new double[numExams];
	}

	// Input data to both arrays from the input file
	string firstName;
	string lastName;
	for (int i = 0; i < numStudents; ++i)
	{
		in >> firstName >> lastName;
		dynamStudentArray[i] = firstName + " " + lastName;
		for (int j = 0; j < numExams; ++j)
		{
			in >> dynamScoresArray[i][j];
		}
	}

	//STUDENT SCORES
	out << "Student Scores: " << endl;
	for (int i = 0; i < numStudents; ++i)
	{
		out << std::setw(20) << dynamStudentArray[i] << " ";
		for (int j = 0; j < numExams; ++j)
		{
			out << std::fixed << std::setprecision(0) << std::setw(6) << dynamScoresArray[i][j];
		}
		out << endl;
	}

	//EXAM AVERAGES
	double *averageExamArray;
	averageExamArray = new double[numExams];
	out << "Exam Averages:" << endl;
	for (int i = 0; i < numExams; ++i)
	{
		out << std::setw(9) << "Exam " << i + 1 << " Average =   ";
		double averageScore = 0;
		for (int j = 0; j < numStudents; ++j)
		{
			averageScore = averageScore + dynamScoresArray[j][i];
		}
		averageScore = averageScore / numStudents;
		averageExamArray[i] = averageScore;
		out << setprecision(1) << averageScore;
		out << endl;
	}

	//Student Exam Grades
	double **dynamGradesPerExam;
	dynamGradesPerExam = new double*[numExams];
	for (int i = 0; i < numExams; ++i)
	{
		dynamGradesPerExam[i] = new double[5];
	}
	for (int i = 0; i < numExams; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			dynamGradesPerExam[i][j] = 0;
		}
	}
	out << "Student Exam Grades: " << endl;
	for (int i = 0; i < numStudents; ++i)
	{
		out << std::setw(20) << dynamStudentArray[i] << "  ";
		for (int j = 0; j < numExams; ++j)
		{
			out << std::fixed << std::setprecision(0) << std::setw(6) << dynamScoresArray[i][j];
			if (dynamScoresArray[i][j] - averageExamArray[j] >= 15)
			{
				out << "(A)";
				dynamGradesPerExam[j][0]++;
			}
			else if (dynamScoresArray[i][j] - averageExamArray[j] >= 4.5)
			{
				out << "(B)";
				dynamGradesPerExam[j][1]++;
			}
			else if (dynamScoresArray[i][j] - averageExamArray[j] >= -4.5)
			{
				out << "(C)";
				dynamGradesPerExam[j][2]++;
			}
			else if (dynamScoresArray[i][j] - averageExamArray[j] >= -15)
			{
				out << "(D)";
				dynamGradesPerExam[j][3]++;
			}
			else 
			{
				out << "(E)";
				dynamGradesPerExam[j][4]++;
			}
		}
		out << endl;
	}

	//Exam Grades:
	out << "Exam Grades: " << endl;
	for (int i = 0; i < numExams; ++i)
	{
		out << std::setw(10) << "Exam  " << i + 1;
		out << std::fixed << std::setprecision(0) << std::setw(5) << dynamGradesPerExam[i][0] << "(A)";
		out << std::fixed << std::setprecision(0) << std::setw(5) << dynamGradesPerExam[i][1] << "(B)";
		out << std::fixed << std::setprecision(0) << std::setw(5) << dynamGradesPerExam[i][2] << "(C)";
		out << std::fixed << std::setprecision(0) << std::setw(5) << dynamGradesPerExam[i][3] << "(D)";
		out << std::fixed << std::setprecision(0) << std::setw(5) << dynamGradesPerExam[i][4] << "(E)";
		out << endl;
	}

	//Prep for Class Final Grade
	double classFinalAverage = 0;
	for (int i = 0; i < numStudents; ++i)
	{
		double finalAverage = 0;
		for (int j = 0; j < numExams; ++j)
		{
			finalAverage = finalAverage + dynamScoresArray[i][j];
		}
		finalAverage = finalAverage / numExams;
		classFinalAverage = classFinalAverage + finalAverage;
	}
	classFinalAverage = classFinalAverage / numStudents;

	//Student Final Grades:
	out << "Student Final Grades:" << endl;
	for (int i = 0; i < numStudents; ++i)
	{
		out << std::setw(20) << dynamStudentArray[i] << " ";
		double finalAverage = 0;
		for (int j = 0; j < numExams; ++j)
		{
			finalAverage = finalAverage + dynamScoresArray[i][j];
		}
		finalAverage = finalAverage / numExams;
		out << setprecision(1) << finalAverage;
		if (finalAverage - classFinalAverage > 15)
		{
			out << "(A)";
		}
		else if (finalAverage - classFinalAverage > 5)
		{
			out << "(B)";
		}
		else if (finalAverage - classFinalAverage > -5)
		{
			out << "(C)";
		}
		else if (finalAverage - classFinalAverage > -15)
		{
			out << "(D)";
		}
		else
		{
			out << "(E)";
		}
		out << endl;
	}

	//Class Average Score
	out << "Class Average Score = " << classFinalAverage;

	// Memory Cleaner
	for (int i = 0; i < numExams; ++i)
	{
		delete[] dynamGradesPerExam[i];
	}
	for (int i = 0; i < numStudents; ++i)
	{
		delete[] dynamScoresArray[i];
	}
	delete[] dynamScoresArray;
	delete[] dynamStudentArray;
	delete[] averageExamArray;
	delete[] dynamGradesPerExam;

	return 0;
}

