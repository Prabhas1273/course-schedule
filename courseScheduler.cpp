/*
----------- Documentation -------------
File Name: courseScheduler.cpp
Description: Course scheduling using Kahn's algorithm
Author: Prabhas Reddy M.
Date: Sunday 30 June 2024 11:15:02 AM 
*/

/*
---------- Input File Format ----------
Number of courses = n
Number of prerequisite pairs = p

Line[1]: n
Line[2]: p
followed by 'p' prerequisite pairs [a, b] => b is a prerequisite course of a
*/


// Include the necesary headers
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

// findSchedule() function returns the topological sort of courses
vector<int> findSchedule(int numCourses, vector<vector<int>> graph) {
	vector<int> prereqCount(numCourses, 0);
	for(int u = 0; u < numCourses; u++) {
		for(const int &v : graph[u]) {
			prereqCount[v] += 1;
		}
	}
	queue<int> q;
	
	// Push all the courses into queue for which there are no prerequisites
	for(int i = 0; i < numCourses; i++) {
		if(prereqCount[i] == 0) {
			q.push(i);
		}
	}
	
	vector<int> schedule;
	while(!q.empty()) {
		int course = q.front();
		q.pop();
		schedule.push_back(course);
		
		for(int adjCourse : graph[course]) {
			// Decrement the prerequisite dependency of adjacent course
			prereqCount[adjCourse] -= 1;
			// Push the course into queue if there are no more dependencies
			if(prereqCount[adjCourse] == 0) {
				q.push(adjCourse);
			}
		}
	}
	return schedule;
}

// Driver code
int main() {
	// Read the input data file
	const char *inFilePath = "courseInput.txt";
	
	// Open the file for reading
	ifstream inFile(inFilePath);
	if(!inFile) {
		cerr << "ERROR: Could not open file " << inFilePath << " for reading" << endl;
		return 1;
	}
	
	int numCourses, numPrereqPairs;
	inFile >> numCourses;
	inFile >> numPrereqPairs;
	
	vector<vector<int>> graph(numCourses);
	
	int course, prereqCourse;
	
	for(int i = 0; i < numPrereqPairs; i++) {
		inFile >> course >> prereqCourse;
		graph[prereqCourse].push_back(course);
	}
	inFile.close();
	
	// Verify the course and prerequisite course relationship
	for(int i = 0; i < numCourses; i++) {
		cout << i << " -> ";
		for(const int &it : graph[i]) {
			cout << it << " ";
		}
		cout << endl;
	}
	
	vector<int> schedule = findSchedule(numCourses, graph);
	
	// Invalid ordering of courses
	if(schedule.size() != numCourses) {
		cout << "Course scheduling not possible." << endl;
	}
	
	// Output the course schedule to an output file
	const char *outFilePath = "courseOutput.txt";
	ofstream outFile(outFilePath);
	if(!outFile) {
		cerr << "Could not open the file" << outFilePath << "for reading" << endl;
		return 1;
	}
	
	for(int i = 0; i < schedule.size(); i++) {
		outFile << schedule[i] << " ";
	}
	cout << "Course schedule written to file " << outFilePath << endl;
	
	return 0;
}







