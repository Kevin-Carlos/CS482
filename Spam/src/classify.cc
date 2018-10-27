/**
 *  @file: classify.cc
 *  
 *  @author: Kevin Carlos
 * 
 *  @TODO: 
 * 
 * */

////////////////////////////////////////////////////////////////////////////////
// Include Directives
////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////////////////////////////////////
void readIntoMap( std::string , std::unordered_map< std::string , int > & );
void naiveBayes( std::unordered_map< std::string , int > spamWords , 
    std::unordered_map< std::string , int > hamWords );


////////////////////////////////////////////////////////////////////////////////
// Global Struct
////////////////////////////////////////////////////////////////////////////////
struct MsgInfo
{
    int hamWordCount,
        spamWordCount,
        hamMsgCount,
        spamMsgCount;
};

////////////////////////////////////////////////////////////////////////////////
/**
 *  @function: main
 * 	@arguments: int argc, char* argv
 *  @details: argv is used to parse the directives given during compilation
 * 				this is done statically for now.
 * 
 * 	classify -i <testing dataset .csv file> -is <spam probability file> 
 *      -ih <ham probability file> -o <classification output filename>
 * 
//////////////////////////////////////////////////////////////////////////////*/
int main( int argc, char* argv[] )
{
    //Variables
   	std::string		inputFile,
   			        spamInput,
		            hamInput,
                    classifyFile;

    std::unordered_map< std::string , int > spamWords;
    std::unordered_map< std::string , int > hamWords;

	//Statically set the above strings to their argv
	inputFile = argv[2];
	spamInput = argv[4];
	hamInput = argv[6];
    classifyFile = argv[8];

    //First step, read in spam/ham input files into maps and save total words
    readIntoMap( spamInput , spamWords );
    readIntoMap( hamInput , hamWords );

    //Work some Naive Bayes magic
    naiveBayes( spamWords , hamWords );

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
/**
 *  @function: readIntoMap
 *  @arguments: inputProbabilityFile, &myMap
 *  @returns: an integer of the total wordCount of the file
 *  @details: Reads in from the inputProbabilityFile and parses it to grab
 *              a word and its occurence value and stores it into the 
 *              respective map which was passed by value
 * 
//////////////////////////////////////////////////////////////////////////////*/
void readIntoMap( 
    std::string inputProbabilityFile , 
    std::unordered_map< std::string , int > &myMap )
{
    //Variables
    std::ifstream   fin;
    std::string     word,
                    temp;
    int             value,
                    wordCount;
    bool            fileType;
    MsgInfo       info;

    fileType = inputProbabilityFile.find("spam"); //True for spam
                                                    //False for ham

    fin.open( inputProbabilityFile );
    if ( fin.is_open() )
    {
        if ( fileType )
        {
            std::getline( fin , temp , '\n' );
            info.spamWordCount = std::stoi( temp );
            std::getline( fin , temp , '\n' );
            info.spamMsgCount = std::stoi( temp );
        }
        else if ( !fileType )
        {
            std::getline( fin , temp , '\n' );
            info.hamWordCount = std::stoi( temp );
            std::getline( fin , temp , '\n' );
            info.hamMsgCount = std::stoi( temp );
        }
        else
            std::cout << "Error reading wordCount and emailCount...\n";

        while ( !fin.eof() )
        {
            /**
             * 
             * Format:
             * word #
             * 
             * */
            std::getline( fin , word , ' ' );
            std::getline( fin , temp , '\n' );

            //Convert temp into an integer
            value = std::stoi( temp );

            //Insert into map
            myMap.insert( std::pair< std::string , int > ( word , value ));
        }
    }
    else
        std::cout << "Error opening input probability file...\n";
}

void naiveBayes( std::unordered_map< std::string , int > spamWords , 
    std::unordered_map< std::string , int > hamWords )
{
    int         totalNumMsg,

                probabilitySpam,
                probabilityHam;

    MsgInfo   info;

    totalNumMsg = info.hamMsgCount + info.spamMsgCount;

    //P(Spam) and P(Ham)
    probabilityHam = info.hamMsgCount / totalNumMsg;
    probabilitySpam = info.spamMsgCount / totalNumMsg;

    //P(word i|spam) = #word_i_occurrence_in_all_spams/#all_words_in_spams
    //P(word i|ham) = #word_i_occurrence_in_all_spams/#all_words_in_hams


}