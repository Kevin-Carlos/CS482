/**
 *  @file: training.cc
 *  
 *  @author: Kevin Carlos
 * 
 *  @TODO: findWord function needs to better handle which characters to parse 
 * 			for and which ones to ignore to build words and know when a word
 * 			has been found
 * 
 * */

////////////////////////////////////////////////////////////////////////////////
// Include Directives
////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////////////////////////////////////
void parseFile( std::string , std::string , std::string );

void findWord ( std::string , std::string ,
	std::unordered_map<std::string , int> & ,
	std::unordered_map<std::string , int> & ,
	int & , int & );

void outputProbabilityFile( 
	std::string , 
	std::unordered_map<std::string , int> ,
	int , int );

void insertIntoMap( 
	std::string , 
	std::unordered_map<std::string , int> & );


////////////////////////////////////////////////////////////////////////////////
/**
 *  @function: main
 * 	@arguments: int argc, char* argv
 *  @details: argv is used to parse the directives given during compilation
 * 				this is done statically for now.
 * 
 * 	training -i <spam.csv file> -os <output spam probability file> 
 *       -oh <output ham probability file>
 * 
//////////////////////////////////////////////////////////////////////////////*/
int main ( int argc, char* argv[] )
{
   	//Variables
   	std::string		inputFile;
   	std::string		spamOutput;
	std::string		hamOutput;

	//Statically set the above strings to their argv
	inputFile = argv[2];
	spamOutput = argv[4];
	hamOutput = argv[6];

	//Parse the file
	parseFile( inputFile , spamOutput , hamOutput );

   	return 0;
}

/**
 * 	The format of the file:
 * 
 * 	ham,"SMS Message",,,
 * 	or
 * 	spam,"SMS Message",,,
 * 
 * */

////////////////////////////////////////////////////////////////////////////////
/**
 *  @function: parseFile
 *  @arguments: inputFile, spamOutput, hamOutput
 *  @details: parseFile takes in three string arguments, the inputFile to parse,
 * 				spamOutput and hamOutput are the files to output the necessary
 * 				info to.
 * 
//////////////////////////////////////////////////////////////////////////////*/
void parseFile( 
	std::string inputFile , 
	std::string spamOutput , 
	std::string hamOutput )
{
	//Variables
	std::ifstream 							fin;
	std::string								temp;
	std::string 							messageType;
	std::string								message;

	int										hamWordCount = 0,
											spamWordCount = 0,
											hamEmailCount = 0,
											spamEmailCount = 0;

	std::unordered_map<std::string , int> 	hamWords;
	std::unordered_map<std::string , int> 	spamWords;
	

	fin.open ( inputFile );
	if ( fin.is_open() )
	{
		//Read the first line to begin getting to the messages
		std::getline( fin , temp , '\n' );

		while ( !fin.eof() )
		{
			std::getline( fin , messageType , ',');

			//Janky but need the # of emails
			if ( messageType == "ham" )
				hamEmailCount++;
			else if ( messageType == "spam" )
				spamEmailCount++;

			//Grab the rest of the line
			std::getline( fin , temp , '\n' );
			message = temp.substr( 0 , temp.find(",,,") ); 
			
			//Set the message to all lowercase
			std::transform( 
				message.begin() , 
				message.end() , 
				message.begin() , 
				::tolower );

			findWord( 
				messageType , 
				message , 
				hamWords , 
				spamWords ,
				hamWordCount ,
				spamWordCount );
		}

		//Now iterate over the maps and send the info out to output files
		outputProbabilityFile( hamOutput , hamWords , 
			hamWordCount , hamEmailCount );
		outputProbabilityFile( spamOutput , spamWords , 
			spamWordCount , spamEmailCount );
	}
	else
		std::cout << "Error opening the input file...\n";
}

////////////////////////////////////////////////////////////////////////////////
/**
 *  @function: findWord
 *  @arguments: messageType, message, hamWords, spamWords
 *  @details: This function uses messageType to determine which map(hamWords or
 * 				spamWords) to insert the word and its occurence value into. It 
 * 				takes in message to build words out of the entire SMS message.
 * 
//////////////////////////////////////////////////////////////////////////////*/
void findWord ( 
	std::string messageType , 
	std::string message , 
	std::unordered_map<std::string , int> &hamWords , 
	std::unordered_map<std::string , int> &spamWords ,
	int &hamWordCount , int &spamWordCount )
{
	//Variables
	const int 	ASCII_ZERO = 48,
				ASCII_NINE = 57,
				
				ASCII_A = 97,
				ASCII_Z = 122,

				ASCII_SPACE = 32,
				ASCII_EX = 33,
				ASCII_COMMA = 44,
				ASCII_DOT = 46,
				ASCII_FSLASH = 47,
				ASCII_QUEST = 63,
				ASCII_BSLASH = 92;

	std::string	word;
	const int 	check = 1;
			
	for ( int index = 0; index < message.size(); index++ )
	{
 		//Add character by character until a space is seen
		//ONLY AlphaNumerics
		if ( ( message[index] >= ASCII_ZERO && message[index] <= ASCII_NINE ) ||
			( message[index] >= ASCII_A && message[index] <= ASCII_Z ))
		{
			word.push_back(message[index]);

			//Need a better way to handle these checks
			//Possibly learn/use regex here
			if ( ( message[index + check] == ASCII_DOT ) ||
				( message[index + check] == ASCII_COMMA) ||
				( message[index + check] == ASCII_SPACE ) ||
				( message[index + check] == ASCII_BSLASH ) ||
				( message[index + check] == ASCII_FSLASH ) ||
				( message[index + check] == ASCII_EX ) ||
				( message[index + check] == ASCII_QUEST ))
			{	
				//Insert word into map
				if ( messageType == "ham" )
				{
					hamWordCount++;
					insertIntoMap( word , hamWords );
				}
				else if ( messageType == "spam" )
				{
					spamWordCount++;
					insertIntoMap( word , spamWords );							
				}
				else
				{
					std::cout << "Default...error///\n";
					std::cout << "Message at error: " << message << "\n";
				}
			
				//std::cout << "Word: " << word << "\n";
				word.erase(word.begin(), word.end());
			}
		} 
	}
}

////////////////////////////////////////////////////////////////////////////////
/**
 *  @function: insertIntoMap
 *  @arguments: word, &insertMap
 *  @details: This function takes in word to check if it already has been
 * 				inserted into the given map (insertMap) which is passed by
 * 				value so the map stays consistent across functions.
 * 				The occurence value of the word is updated accordingly.
 * 
//////////////////////////////////////////////////////////////////////////////*/ 
void insertIntoMap( 
	std::string word , 
	std::unordered_map<std::string , int> &insertMap )
{
	int value = 0;
	std::unordered_map<std::string , int>::iterator it;

	//If the word already exists
	if ( insertMap.count( word ) != 0 )
	{
		it = insertMap.find( word );
		value = it->second;
		value++;

		it->second = value;
	}
	else //Otherwise set the value to 1 as its the first occurrence and insert
	{
		value = 1;
		insertMap.insert( std::pair<std::string , int > ( word , value ));
	}
}

////////////////////////////////////////////////////////////////////////////////
/**
 *  @function: outputProbabiliityFile
 *  @arguments: outputFile, outputMap
 *  @details: Takes in the name of the file to output to and the map its
 * 				outputting. This is passed by default reference as its the end
 * 				of the program and no data manipulation occurs here.
 * 
//////////////////////////////////////////////////////////////////////////////*/
void outputProbabilityFile( 
	std::string outputFile , 
	std::unordered_map<std::string , int> outputMap ,
	int wordCount , int emailCount )
{
	//Variables
	std::ofstream	fout;

	std::unordered_map<std::string , int>::iterator it;

	//Output information to file
	fout.open( outputFile , std::ios::out );
	if ( fout.is_open() )
	{
		fout << wordCount << std::endl;
		fout << emailCount << std::endl;

		//Now iterate over the map and output key value pairs
		for ( it = outputMap.begin(); it != outputMap.end(); it++ )
			fout << it->first << " " << it->second << std::endl;
	}

	fout.close();
}