// PigLatin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

int continueCheck();											//declared functions for later use.
int wordPLTrans(char wordArray[47], char pigLatinArray[50]);
int sentencePLTrans(char sentenceArray[500], char wordArray[47]);

int main()
{
	char wordArray[47];			//A series of delcared arrays for intial user array and transformed pig Latin array.	
	char sentenceArray[500];
	char pigLatinArray[50];
	char optionChar = ' ';		//initialized as empty, used for storing users choice.
	bool continueFlag = 1;		//initialized as true, and used to test weather user wants to continue. 

	strcpy(wordArray, " ");

	do {						//Do while to wrap the full application and will test if user would like to continue translating.
		do {					//Do while used for validation testing with the option char
			cout << "\nDo you want to translate a word or sentence?"<< endl;
			cout << "Type S for sentence and W for word." << endl;
			cin >> optionChar;			
			cin.clear();		//clearing the cin buffer.
			cin.ignore();

			switch (optionChar)	//switch statement for validation testing of optionChar.
				{
				case's':
				case'S':
					optionChar = 's';
					break;
				case'w':
				case'W':
					optionChar = 'w';
					break;
				default:
					cout << "Invalid choice, Try again." << endl;
				}
			}while (optionChar != 's' && optionChar != 'w');	//Will not break out of the loop unless optionCHar equal s or w
			
			if (optionChar == 'w')			//If user choose "w" the program will proceed to translating a word to pig latin.
			{
				cout << "Please type any word: ";
				gets_s(wordArray);			//Will store a users input into array.
				wordPLTrans(wordArray,pigLatinArray);	
				continueFlag = continueCheck();		
			}
			else if(optionChar == 's')		//If user choose "s" the program will proceed to translating a full sentence to pig latin.
			{
				cout << "Please type any sentence: ";
				gets_s(sentenceArray);		//Will store a users input into array.
				sentencePLTrans(sentenceArray, wordArray);
				continueFlag = continueCheck();
			}
			else
			{ 
				cout << "Invalid choice! 'S' or 'W' wasn't choosen, try again!" << endl;
				continueFlag = 1;
			}

	} while (continueFlag != 0);	//Will not exit the loop unless the continueFlag is set to false. 

    return 0;
}

int continueCheck()		//Function to test and assign a users response to continue to translate.
{
	char userInput;		//declared local variables. 
	bool continueFlag;
	
	do {				//Do while loop for testing an validating a users option to continue to translate.
		cout << "\nWould you like to continue? Use 'Y' for Yes or 'N' for No." << endl;
		cin >> userInput;
		cin.clear();	//clearing the cin buffer.
		cin.ignore();

		switch (userInput)	//Switch statement for testing and assigning userInput.
		{
		case'y':
		case'Y':
			userInput = 'y';
			break;
		case'n':
		case'N':
			userInput = 'n';
			break;
		default:
			cout << "Invalid choice, Try again." << endl;
		}
	} while (userInput != 'y' && userInput != 'n');	//Will not exit the loop unless the userInput is set to "y" or "n"
	 
	if (userInput == 'y')	//conditional statement for assigning userInput to continueFLag.
		continueFlag = 1;
	else
		continueFlag = 0;

	return continueFlag;	//Will return either true or false back to main
}
int wordPLTrans(char wordArray[47], char pigLatinArray[50])		//Used to translate a word stored in an array to pigLatin.
{
	int successCheck = 0;		//A series of intialized and declared variables and array for testing.
	bool isVowel = 0;
	int i = 0;
	char NumArray[10] = {'0','1','2','3','4','5','6','7','8','9'};
	bool isArticle = 0;
	char firstLetter = ' ';
	char vowels[10] = { 'a','A','e','E','u','U','i','I','o','O' };
	char articleConjArray[10][10] = {"a","an","the","and","but","for","nor","so","yet","or"};

	strcpy(pigLatinArray," ");	//Intialized as an empty array.

	for (int itr = 0; itr < strlen(vowels); itr++)		//This for loop will iterate through each vowel and number in the vowels and number array an test against the 0th element or first letter of the users word. 
	{
		if (vowels[itr] == wordArray[0])	
		{
			isVowel = 1;	
			break;
		}
		else if (NumArray[itr] == wordArray[0])
		{
			successCheck = -1;
			break;
		}
	}

	if (successCheck != -1)		//Used parent conditional statement to check the value of the successCheck. Will fail if word starts with a number.
	{
		for (int itr = 0; itr < 10; itr++)	//For loop that will compare each element of the artical or Conjunction array against user input.
		{
			if ((strcmp(wordArray, articleConjArray[itr])) == 0) //strcmp evaluates to false if arrays is the same. 
			{
				strcpy(pigLatinArray, wordArray);
				isArticle = 1;
				break;
			}		
		}

		if ((isVowel == 1) && (isArticle != 1))		//if word starts with a vowel and is not a artical or conjuntion an "ay" will be added to the end of the word.
		{
			strcpy(pigLatinArray, wordArray);
			strcat(pigLatinArray, "ay");
		}

		else if ((isVowel == 0) && (isArticle != 1))	//if word doesn't start with a vowel and is not a artical or conjunction first letter will be moved to the end of the word and "ay" will be added to the end
		{
			strcpy(pigLatinArray, wordArray + 1);
			strncat(pigLatinArray, wordArray, 1);
			strcat(pigLatinArray, "ay");
		}
		else	//if does not start with a vowel, consonant, or number. the word is deemed invalid
		{
			if (isArticle != 1)
			{
				cout << "Invalid response! (" << wordArray << ") can't be translated" << endl;
			}
		}

		cout <<"Pig Latin translation: "<< pigLatinArray << endl;
		return i;	//return i back to main, which will be 0,1, or either -1.
	}
	else
	{
		cout << "\nSorry "<< wordArray <<" can't be translated"<< endl;
		i = successCheck;
		return i;	//return i back to main, which will be 0,1, or either -1.
	}
}
int sentencePLTrans(char sentenceArray[500], char wordArray[47]) //Tried a couple of things but no luck, the idea was to take a sentence into an array, split the array at " " and store the word as pigLatinArray[i]. Then send pigLatinArray[i] to wordPLTranslate for translation. 
{
	char pigLatinArray[50][50] = { " ", " " };
	char emptyArray[50];
	int counter = 0;
	int lastCounter = 0;
	int i = 0;

	stringstream ssin(sentenceArray);							//failing somewhere in here. My 2 dimensional array is filling up but I want it to stop at \0
	while (ssin.good() && i < 47 && (sentenceArray[i]!= NULL)) {
		ssin >> pigLatinArray[i];
		++i;
	}
	for (i = 0; i < 47; i++) {
		wordPLTrans(pigLatinArray[i], emptyArray);
	}
	/*for (int itr = 0; itr < strlen(sentenceArray); itr++)		//didn't work
	{
		if (sentenceArray[itr] != ' ')
		{
			counter++;
		}
		else {
			strncpy(pigLatinArray[i], sentenceArray, counter += '\0');
			wordArray = pigLatinArray[i];
			wordPLTrans(wordArray, emptyArray);
			i++;
		}
	}*/
	
	cout << pigLatinArray << endl;
	return i;
}