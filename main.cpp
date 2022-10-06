#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "hashMap.h"

int main(int argc, char * argv[])
{

	std::string filename;
	std::cout << "Enter filename: ";
	std::cin >> filename;
	int numElections;
	int numCanidates;
	std::string voteName;
	std::string canidateParty;
	std::string lineCatcher;
	std::string winnerParty;
	int numVotes;
	int caseCounter = 1;

	int randomCounter = 0;
	try
	{
		std::ifstream myFile(filename); 

		//myfile is not opening 
		if(!myFile)
		{
			throw std::string(filename); //try to open the file
		}
		myFile >> numElections;
	
		for(int k = numElections; k > 0; k--)
		{
			std::vector <std::string> canidates;
			std::vector <std::string> inputs;

			hashMap <std::string, int> ourMap;
		
			myFile >> numCanidates;
			getline(myFile, canidateParty);

			for(int l = numCanidates; l > 0; l--)
			{
				getline(myFile, voteName);
				canidates.push_back(voteName);
				getline(myFile, canidateParty);
				canidates.push_back(canidateParty);
			}

			myFile >> numVotes;
			getline(myFile, lineCatcher);

			for(int j = numVotes; j > 0; j--)
			{
				getline(myFile, voteName);
				ourMap[voteName] += 1;
				if(voteName == canidates[6])
				{
					randomCounter++;
				}
			}
			
			hashMap<std::string, int>::iterator it1;
			it1 = ourMap.begin();
			int valueAnwser = 0;
			std::string winner;
			while(it1 != ourMap.end())
			{

				if(valueAnwser < it1.second())
				{
					valueAnwser = it1.second();
					winner = it1.first();
				}
				else if(valueAnwser == it1.second())
				{
					winner = "tie";
					winnerParty = "Tie";
				}
				it1++;

			}

			for(int i = 0; i < canidates.size(); i++)
			{
				if(canidates[i] == winner)
				{
					winnerParty = canidates[i+1];
				}
			}	
			
			std::cout << "Case " << caseCounter << " results: " << winnerParty << std::endl;
			caseCounter++;

		}
	}
	catch(std::string str)
	{
		std::cout << filename << " not found" << std::endl; //catchs for bad files.
		return 0;

	}
	return 0;
	
}
