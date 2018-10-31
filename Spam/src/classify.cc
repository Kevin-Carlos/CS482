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
#include <regex>
#include <algorithm>
#include <math.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////////////////////////////////////
void readIntoMap( string , unordered_map< string , int > & );

void calculatetotalMsg();

void naiveBayes( unordered_map< string , int > spamWords , 
    unordered_map< string , int > hamWords ,
    string inputFile , string );

void outputMessages( string ,
    string outputFile );

////////////////////////////////////////////////////////////////////////////////
// Global Struct
////////////////////////////////////////////////////////////////////////////////
struct MsgInfo
{
    int hamWordCount,
        spamWordCount,
        hamMsgCount,
        spamMsgCount,
        totalNumMsg;
} info;

struct Probability
{
    int probabilityHam,
        probabilitySpam;
} probs;

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
   	string		inputFile,
   			        spamInput,
		            hamInput,
                    classifyFile;

    unordered_map< string , int > spamWords;
    unordered_map< string , int > hamWords;

    /* for ( int i = 0; i < argc; i++ )
    {
        cout << "" << argc << ": " << argv[i] << "\n";
    } */

	//Statically set the above strings to their argv
	inputFile = argv[2];
	spamInput = argv[4];
	hamInput = argv[6];
    classifyFile = argv[8];

    //First step, read in spam/ham input files into maps and save total words
    readIntoMap( spamInput , spamWords );
    readIntoMap( hamInput , hamWords );

    calculatetotalMsg();

    //Start some trainin'
    naiveBayes( spamWords , hamWords , 
        inputFile , classifyFile );

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
    string inputProbabilityFile , 
    unordered_map< string , int > &myMap )
{
    //Variables
    ifstream        fin;
    string          word,
                    temp;
    int             value,
                    wordCount;
    bool            fileType;

    fileType = inputProbabilityFile.find("spam"); //True for spam
                                                    //False for ham

    fin.open( inputProbabilityFile );
    if ( fin.is_open() )
    {
        if ( fileType )
        {
            getline( fin , temp , '\n' );
            info.spamWordCount = stoi( temp );
            getline( fin , temp , '\n' );
            info.spamMsgCount = stoi( temp );
        }
        else if ( !fileType )
        {
            getline( fin , temp , '\n' );
            info.hamWordCount = stoi( temp );
            getline( fin , temp , '\n' );
            info.hamMsgCount = stoi( temp );
        }
        else
            cout << "Error reading wordCount and emailCount...\n";

        while ( !fin.eof() )
        {
            /**
             * 
             * Format:
             * word #
             * 
             * */
            getline( fin , word , ' ' );
            getline( fin , temp , '\n' );

            //Convert temp into an integer
            value = stoi( temp );

            //Insert into map
            myMap.insert( pair< string , int > ( word , value ));
        }
    }
    else
        cout << "Error opening input probability file...\n";
}

void calculatetotalMsg()
{
    info.totalNumMsg = info.hamMsgCount + info.spamMsgCount;

    //P(Spam) and P(Ham)
    probs.probabilityHam = info.hamMsgCount / info.totalNumMsg;
    probs.probabilitySpam = info.spamMsgCount / info.totalNumMsg;
}

void naiveBayes( unordered_map< string , int > spamWords , 
    unordered_map< string , int > hamWords ,
    string inputFile , string outFile )
{
    //Variables
    ifstream       fin;

    regex regExpr( "([^.,<>/\()-_@#$%^&*=+?!:;'\" ]+)" );
    smatch match;

    string              temp,
                        message,
                        messageType,
                        word;

    const string        HAM = "ham",
                        SPAM = "spam";

    long double         wordProbHam,
                        wordProbSpam;
    long double         msgHamProb,
                        msgSpamProb;
    int                 spamValue = 0,
                        hamValue = 0;

    unordered_map<string , int>::iterator it;

    int lines = 0;

    fin.open( inputFile );
    if ( fin.is_open() )
    {
        while ( !fin.eof() ) 
        {
            lines++;
            getline( fin , messageType , ',' );

            getline( fin , temp , '\n' );
            message = temp.substr( 0 , temp.find(",,,") ); 

            //cout << "Type: " << messageType << " ";
            //cout << "Message: " << message << endl;
            //cout << "Line #: " << lines << endl;

            //Classify some stoof
            //Set the message to all lowercase
            transform( 
                message.begin() , 
                message.end() , 
                message.begin() , 
                ::tolower );  

            regex_iterator<string::iterator> rit 
                    ( message.begin(), message.end(), regExpr );
            regex_iterator<string::iterator> rend;

            while ( rit != rend )
            {
                /**
                 * This starts off with a 50/50 chance of probability
                */
                msgHamProb = 0.5;
                msgSpamProb = 0.5;

                word = rit->str(); //Obtain the word

                //First does the word exist in one of the maps at all?
                if ( spamWords.count( word ) != 0 )
	            {
                    it = spamWords.find( word );

                    /**
                     * Use this as a threshold to not use words that only occur
                     * once.
                    */
                    if ( it->second == 1 ) 
                        wordProbSpam = 1;
                    else
                        wordProbSpam = it->second / ( info.spamWordCount - 1 );
	            }
                else
                    wordProbSpam = 1;
    
	            if ( hamWords.count( word ) != 0 )
	            {
                    it = hamWords.find( word ); 

                    if ( it->second == 1 )
                        wordProbHam = 1;
                    else
                        wordProbHam = it->second / ( info.hamWordCount - 1);
	            }
                else
                    wordProbHam = 1;

                msgSpamProb *= wordProbSpam;
                msgHamProb *= wordProbHam;

                ++rit;
            } 

            if ( log(msgHamProb) > log(msgSpamProb) )
            {
                outputMessages( HAM , outFile );
            }
            else if ( log(msgSpamProb) > log(msgHamProb) )
            {
                outputMessages( SPAM , outFile );
            }
            else if ( log(msgSpamProb) == log(msgHamProb) )
                outputMessages( HAM , outFile );
            else
                outputMessages( messageType , outFile );

            if ( lines == 1672 ) //Jank, needs fixing because EOF is bad
                exit(1);
        }
    }
    fin.close();
}

void outputMessages( string type , string classifyFile )
{
    //Variables
    ofstream   fout;

    fout.open( classifyFile , ios::app );
    if ( fout.is_open() )
    {
        fout << type << endl;
    }

    fout.close();
}