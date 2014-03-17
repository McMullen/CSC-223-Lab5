//-------------------------------------------------------------------------------------------------
//Author:	   Jason McMullen and Anthony Martini
//Due Date:    3/18/14
//Program:	   Lab5
//Description: This program will read in a list of courses, store them in an array and then compare
//			   them and ouput some statistical details. The program will first open the required
//			   input .txt file to read in the information for the desired courses. If the file
//			   does not exist or can not be open for any reason then the program will immediately
//			   shutdown. It then will record the course information and store the details in a 2D
//			   array. The program will then comput and ouput the overall course with the least 
//			   amount of students in it. After that the proram will compute and output the maximum
//			   amount of students for each year. It will then sum all the students that attending
//			   each course for all the years it was offered and ouput the sum for each class. 
//			   Finally, the program will print a graphical representation of the number of 
//			   students that attended each course for every year it was offered (note: it will 
//			   print a graph for each course entered). All output will be recorded in a separate
//			   .txt file and will be located in the same directory as this source file.
//-------------------------------------------------------------------------------------------------
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

//Constant to control the maximum number of courses in the array.
const int MAX_ENTRY = 10;

//Constants that will consist of the preapproved course name list. Each course will be later
//converted to an integer. The number following "course" will be its assigned integer value.
const string course1 = "CSC101";
const string course2 = "MTH223";
const string course3 = "ENG105";

//-------------------------------------------------------------------------------------------------
//Function getData: The function will read from an external file and read, line by line, the
//					information for each course. The information must follow this format:
//					YEAR  COURSE  # of STUDENTS   (course will be converted to an int by another
//					function)
//					If there is more room in the array the user will be prompted if they wish to
//					enter more data. If so, then the function will repeat itself. If not, then the
//					function will end.
//
//Precondition:		This function requires the actual array to be sent over so we can modify the
//					contents placed inside. It will also require the object in control of reading
//					from the input file.
//Postcondition:	This function will return the number of courses that have been entered into
//					the array. The function will also close the input file upon completion.
//-------------------------------------------------------------------------------------------------
int getData(int list[][3], ifstream& in_stream);

//-------------------------------------------------------------------------------------------------
//Function graph: graph will print out the results of each class in a graphical format. The format
//				  will be a bar graph with the y axis as the year and the x axis as the number of
//				  students. The symbol "*" will be used to create the bars on the graph. Each set
//				  of 3 "*" will be a unit of 5 students.
//
//Precondition:   graph requires the ability to read the values store in the array and the length
//				  of the array sent to it to work properly.
//Postcondition:  This function will not return anything.
//-------------------------------------------------------------------------------------------------
void graph(const int list[][3], int numOfCourses, int numOfClass, string className,
	ofstream& out_stream);

//-------------------------------------------------------------------------------------------------
//Function rangeOfYears: This function will compute and output the range of years that each class
//						 was offered.
//
//Precondition:			 The function requires access to read the values in the array and the
//						 length of the array as well as the amount of courses in the array sent to
//						 it.
//Postcondition:		 This function will not return anything.
//-------------------------------------------------------------------------------------------------
void rangeOfYears(const int list[][3], int numCourses, ofstream& out_stream);

//-------------------------------------------------------------------------------------------------
//Function totalPerCourse: The function will comput and output the total number of students per
//						   course.
//
//Precondition:			   totalPerCourse requires the array (so it may read the values stored
//						   within) and the length of the array.
//Postcondition:		   This function will not return anything.
//-------------------------------------------------------------------------------------------------
void totalPerCourse(const int list[][3], ofstream& out_stream);

//-------------------------------------------------------------------------------------------------
//Function minNumberOfStudents: This function will compute and output the class, out of all that
//								were entered, that had the lowest amount of students in. It will
//								do this by going through each entry in the array and compare all
//								the classes to find the one with the least amount of students
//								enrolled in it.
//
//Precondition:					This function requires array to be passed so it may read the
//								values stored within. It also will need the length of the array.
//Postcondition:			    This function will not ouput anything.
//-------------------------------------------------------------------------------------------------
void minNumberOfStudents(const int list[][3], int numCourses, ofstream& out_stream);

//-------------------------------------------------------------------------------------------------
//Function maxPerYear: This function will compute and output the class that had the max amount of
//					   students per year. The function will use a for loop to go through every
//					   course looking at only the third position in the second column. The years
//					   will then be examined to determine which course had the most amount of
//					   students enrolled in. The function will the ouput the year, course name,
//					   and the amount of students for that course.
//
//Precondition:		   This function will need the array passed to it so it may read the values
//					   stored within. It will also need the length of the array passed as well.
//Postcondition:       This function will not return anything.
//-------------------------------------------------------------------------------------------------
void maxPerYear(const int list[][3], int numCourses, ofstream& out_stream);

//-------------------------------------------------------------------------------------------------
//Function totalPerCourse: This function will output the total number of students in each course
//						   for all years.
//
//Precondition:			   This function will need the array passed to it so it may read the values
//						   contained within as well as the length of the array.
//Postcondition:		   This function will not return anything.
//-------------------------------------------------------------------------------------------------
void totalPerCourse(int list[][3], ofstream& out_stream);

//-------------------------------------------------------------------------------------------------
//Function convertCourse: This function will compare an entered string and return an int value
//						  assigned with it. The values have been predetermined wiht each course
//						  title. There will be no error checking in this function.
//
//Precondition:			  This function needs the entered string passed for it to compare that
//						  string with a predetermined int value for each one.
//Postcondition:		  This function will return the int value of the course name entered in
//						  order for it to be added to an int array. The values are: CSC101 = 1,
//						  MTH223 = 2, ENG1-5 = 3. The function will return a -1 if the course
//						  entered does not match what is on the predetermined list of courses.
//-------------------------------------------------------------------------------------------------
int convertCourse(string course);

//-------------------------------------------------------------------------------------------------
//Function courseName: This function will convert an integer back into the course title.
//
//Precondition:		   The function requires the indetifing integer sent to it so it can compare it
//					   to the predifined list of courses and return the proper course title.
//Postcondition:	   This function will return the string containing the course title.
//-------------------------------------------------------------------------------------------------
string courseName(int num);

//-------------------------------------------------------------------------------------------------
//Function printAsterisks: Function that will print n many times "*" to screen.
//
//Precondition: The function requires the amount of "*" needed to be printed sent to it.
//Postcondition: This function will not return anything.
//-------------------------------------------------------------------------------------------------
void printAsterisks(int n, ofstream& out_stream);

//-------------------------------------------------------------------------------------------------
//Function totalPerCourse: This function will find the sum of all the students registered for each
//class throughout the years it was offered and then display the results.
//
//Precondition: This function requires the array, the array length and the integer value for the
//course name to be passed to it.
//Postcondition: This function will not return anything.
//-------------------------------------------------------------------------------------------------
void totalPerCourse(const int list[][3], int numCourses, int numOfClass, ofstream& out_stream);

//-------------------------------------------------------------------------------------------------
//Function main: The main function. It will be responsible for running the program and making the
//				 necessary calls to following functions.
//-------------------------------------------------------------------------------------------------
int main()
{

	//object for reading in from file
	ifstream in_stream;

	//connection to input file
	in_stream.open("infile.txt");

	//check to see if the input file is there, if it isnt then close this program instantly
	if (in_stream.fail())
		exit(1);

	//object for writing to file
	ofstream out_stream;

	//conection to output file
	out_stream.open("outfile.txt");

	//create a new array. Will have to change code to adjust size of array
	int list[MAX_ENTRY][3];

	//variable to hold the number of courses in the array
	int numCourses;

	//read data from input file and enter into array, then return number of courses
	numCourses = getData(list, in_stream);

	//print the graphs for each course
	graph(list, numCourses, convertCourse(course1), courseName(1), out_stream);
	graph(list, numCourses, convertCourse(course2), courseName(2), out_stream);
	graph(list, numCourses, convertCourse(course3), courseName(3), out_stream);

	//range of years courses were offered
	rangeOfYears(list, numCourses, out_stream);

	//total number of students per course
	totalPerCourse(list, numCourses, convertCourse(course1), out_stream);
	totalPerCourse(list, numCourses, convertCourse(course2), out_stream);
	totalPerCourse(list, numCourses, convertCourse(course3), out_stream);

	//course with the least amount of students registered
	minNumberOfStudents(list, numCourses, out_stream);

	//class with highest amount of students per year
	maxPerYear(list, numCourses, out_stream);

	out_stream.close();

	return 0;

}//end main function

//-------------------------------------------------------------------------------------------------
//Function getData: The function will read from an external file and read, line by line, the
//					information for each course. The information must follow this format:
//					YEAR  COURSE  # of STUDENTS   (course will be converted to an int by another
//					function)
//					If there is more room in the array the user will be prompted if they wish to
//					enter more data. If so, then the function will repeat itself. If not, then the
//					function will end.
//
//Precondition:		This function requires the actual array to be sent over so we can modify the
//					contents placed inside. It will also require the object in control of reading
//					from the input file.
//Postcondition:	This function will return the number of courses that have been entered into
//					the array. The function will also close the input file upon completion.
//-------------------------------------------------------------------------------------------------
int getData(int list[][3], ifstream& in_stream)
{

	//temp variables that will hold data being read from the .txt file
	int year, numStudents, courseID, numCourses, i = 0;
	string courseName;

	//continue running if there are 3 values on next line to be read in
	while (in_stream >> year >> courseName >> numStudents)
	{

		for (int j = 0; j < 3; j++)
		{

			switch (j)
			{

				//first row of array will hold years
			case 0:
				list[i][0] = year;
				break;

				//second row of array will hold course name, will have to be changed to int
			case 1:
				courseID = convertCourse(courseName);
				list[i][1] = courseID;
				break;

				//third row of array will hold the number of students
			case 2:
				list[i][2] = numStudents;
				break;

			}//end switch block

		}//end for loop

		i++;
		numCourses = i;

	}//end while loop

	//close the input file
	in_stream.close();

	return numCourses;

}//end getData function

//-------------------------------------------------------------------------------------------------
//Function convertCourse: This function will compare an entered string and return an int value
//						  assigned with it. The values have been predetermined wiht each course
//						  title. There will be no error checking in this function.
//
//Precondition:			  This function needs the entered string passed for it to compare that
//						  string with a predetermined int value for each one.
//Postcondition:		  This function will return the int value of the course name entered in
//						  order for it to be added to an int array. The values are: CSC101 = 1,
//						  MTH223 = 2, ENG1-5 = 3. The function will return a -1 if the course
//						  entered does not match what is on the predetermined list of courses.
//-------------------------------------------------------------------------------------------------
int convertCourse(string course)
{

	int answer = -1;

	//CSC101
	if (course == course1)
	{

		answer = 1;

	}//end if statement
	//MTH223
	else if (course == course2)
	{

		answer = 2;

	}//end first else
	//ENG105
	else if (course == course3)
	{

		answer = 3;

	}//end last else

	return answer;

}//end convertCourse function

//-------------------------------------------------------------------------------------------------
//Function courseName: This function will convert an integer back into the course title.
//
//Precondition:		   The function requires the indetifing integer sent to it so it can compare it
//					   to the predifined list of courses and return the proper course title.
//Postcondition:	   This function will return the string containing the course title.
//-------------------------------------------------------------------------------------------------
string courseName(int num)
{

	string answer = " ";

	if (num == 1)
	{

		answer = course1;

	}//end if statement
	else if (num == 2)
	{

		answer = course2;

	}//end else if statment
	else if (num == 3)
	{

		answer = course3;

	}//end else if statement

	return answer;

}//end courseName function

//-------------------------------------------------------------------------------------------------
//Function maxPerYear: This function will compute and output the class that had the max amount of
//					   students per year. The function will use a for loop to go through every
//					   course looking at only the third position in the second column. The years
//					   will then be examined to determine which course had the most amount of
//					   students enrolled in. The function will the ouput the year, course name,
//					   and the amount of students for that course.
//
//Precondition:		   This function will need the array passed to it so it may read the values
//					   stored within. It will also need the length of the array passed as well.
//Postcondition:       This function will not return anything.
//-------------------------------------------------------------------------------------------------
void maxPerYear(const int list[][3], int numCourses, ofstream& out_stream)
{

	int max2012 = list[0][2];
	int index2012 = 0;
	int max2013 = list[0][2];
	int index2013 = 0;
	int max2014 = list[0][2];
	int index2014 = 0;
	for (int i = 0; i <numCourses; i++)
	{
		if ((list[i][2] > max2012) && (list[i][0] == 2012))
		{
			max2012 = list[i][2];
			index2012 = i;
		}
		if ((list[i][2] > max2013) && (list[i][0] == 2013))
		{
			max2013 = list[i][2];
			index2013 = i;
		}
		if ((list[i][2] > max2014) && (list[i][0] == 2014))
		{
			max2014 = list[i][2];
			index2014 = i;
		}
	}
	out_stream << "\nThe courses that had the MAXIMUM number of students per year\n"
		<< "\n\tIn 2012 the max number of students in "
		<< courseName(list[index2012][1]) << " with " << max2012 << "\tstudents."
		<< endl;

	out_stream << "\n\tIn 2013 the max number of students in "
		<< courseName(list[index2013][1])
		<< " with " << max2013 << "\tstudents."
		<< endl;

	out_stream << "\n\tIn 2014 the max number of students in "
		<< courseName(list[index2014][1])
		<< " with " << max2014 << "\tstudents."
		<< endl;

}//end maxPerYear function

//-------------------------------------------------------------------------------------------------
//Function minNumberOfStudents: This function will compute and output the class, out of all that
//								were entered, that had the lowest amount of students in. It will
//								do this by going through each entry in the array and compare all
//								the classes to find the one with the least amount of students
//								enrolled in it.
//
//Precondition:					This function requires array to be passed so it may read the
//								values stored within. It also will need the length of the array.
//Postcondition:			    This function will not ouput anything.
//-------------------------------------------------------------------------------------------------
void minNumberOfStudents(const int list[][3], int numCourses, ofstream& out_stream)
{

	int answer = list[0][2];
	int answerIndex = 0;

	for (int i = 0; i < numCourses; i++)
	{

		int numStudents = list[i][2];

		if (numStudents <= answer)
		{

			answer = numStudents;
			answerIndex = i;

		}//end if statements

	}//end for loop

	out_stream << "\nThe course with the MINIMUM number of students was in "
		<< list[answerIndex][0]
		<< " "
		<< courseName(list[answerIndex][1])
		<< " with "
		<< list[answerIndex][2]
		<< " students"
		<< endl;

}//end minNumberOfStudents function

//-------------------------------------------------------------------------------------------------
//Function rangeOfYears: This function will compute and output the range of years that each class
//						 was offered.
//
//Precondition:			 The function requires access to read the values in the array and the
//						 length of the array as well as the amount of courses in the array sent to
//						 it.
//Postcondition:		 This function will not return anything.
//-------------------------------------------------------------------------------------------------
void rangeOfYears(const int list[][3], int numCourses, ofstream& out_stream)
{

	int low = list[0][0];
	int high = list[0][0];

	for (int i = 0; i < numCourses; i++)
	{

		int year = list[i][0];

		if (low >= year)
		{

			low = list[i][0];

		}//end if statement
		else if (high <= year)
		{
			high = list[i][0];

		}//end if statment

	}//end for loop

	out_stream << "Statistics for the years " << low << " - " << high << "."
		<< endl;

}//end rangeOfYears function

//-------------------------------------------------------------------------------------------------
//Function graph: graph will print out the results of each class in a graphical format. The format
//				  will be a bar graph with the y axis as the year and the x axis as the number of
//				  students. The symbol "*" will be used to create the bars on the graph. Each set
//				  of 3 "*" will be a unit of 5 students.
//
//Precondition:   graph requires the ability to read the values store in the array and the length
//				  of the array sent to it to work properly.
//Postcondition:  This function will not return anything.
//-------------------------------------------------------------------------------------------------
void graph(const int list[][3], int numOfCourses, int numOfClass, string className,
	ofstream& out_stream)
{

	out_stream << className << "\n" << setw(5) << "|" << "\n" << setw(5) << "|";

	for (int i = 0; i <= numOfCourses; i++)
	{
		if ((list[i][1] == numOfClass) && (list[i][0] == 2012))
		{
			out_stream << "\n" << setw(5) << "2012|";
			printAsterisks(list[i][2], out_stream);
			out_stream << "\n" << setw(5) << "|";
		}
		else if ((list[i][1] == numOfClass) && (list[i][0] == 2013))
		{
			out_stream << "\n" << setw(5) << "2013|";
			printAsterisks(list[i][2], out_stream);
			out_stream << "\n" << setw(5) << "|";
		}
		else if (list[i][1] == numOfClass && (list[i][0] == 2014))
		{
			out_stream << "\n" << setw(5) << "2014|";
			printAsterisks(list[i][2], out_stream);
		}
		if (i == numOfCourses)
		{

			out_stream << "\n" << "    " << "|__________________________________________________" << endl;
			out_stream << "\n" << "     " << "____5___10___15___20___25___30___35___40___45___50" << "\n";
		}
	}
	out_stream << "\n"
		<< endl;
}

//-------------------------------------------------------------------------------------------------
//Function printAsterisks: Function that will print n many times "*" to screen.
//
//Precondition: The function requires the amount of "*" needed to be printed sent to it.
//Postcondition: This function will not return anything.
//-------------------------------------------------------------------------------------------------
void printAsterisks(int n, ofstream& out_stream)
{

	for (int count = 0; count < n; count++)
		out_stream << "*";

}

//-------------------------------------------------------------------------------------------------
//Function totalPerCourse: This function will find the sum of all the students registered for each
//class throughout the years it was offered and then display the results.
//
//Precondition: This function requires the array, the array length and the integer value for the
//course name to be passed to it.
//Postcondition: This function will not return anything.
//-------------------------------------------------------------------------------------------------
void totalPerCourse(const int list[][3], int numCourses, int numOfClass, ofstream& out_stream)
{
	out_stream << "\n\t" << courseName(numOfClass) << " had ";

	int total;
	int newTotal = 0;
	for (int i = 0; i <= numCourses; i++)
	{
		if (list[i][1] == numOfClass)
		{
			total = (list[i][2]);
			newTotal += total;
		}
	}
	out_stream << newTotal << " students\n";
}