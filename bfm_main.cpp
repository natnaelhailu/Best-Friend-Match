/////////////////////////////////////////////////////////////////////////
// Description: This program take an initial name from the user
//              and matches the characters with a given set of names
//			    to determine the names with the most characters in 
//              common with the initial name. It uses a custom hashmap 
//              class to implement the character matching.
//
// Input: name of a valid filename containing required information
// Output: names with the most char match to initial name in each case
/////////////////////////////////////////////////////////////////////////

#include <iostream>       // std::cin, std::cout
#include <algorithm>      // std::max_element
#include <cctype>         // std::isupper
#include <fstream>        // std::ifstream
#include <sstream>        // std::istringstream
#include <vector>         // std::vector
#include <iterator>       // std::distance
#include "bfm_map.hpp"    // hashMap

/*
* Main entry-point for this program.
* @returns Exit-code for the process - 0 for success, else an error code.
*/
int main()
{
    std::string filename;   //< input file
    std::string str1;       //< 1st line of case input
    std::string str2;	    //< 2nd line of case input
    std::ifstream file;     //< input file stream object
    std::string loner;      //< name of person looking for friends
    std::string testCases;  //< total # of names per case (string)
    int test_cases;         //< total # of names per case (int)
    int num_of_names;       //< total # of cases per input file
    int max_names;          //< max # of suitable names to print

    // Accept a valid filename from user & open file
    while (true)
    {
        std::cout << "Enter file name: ";
        std::cin >> filename;
        file.open(filename);
        if(file.is_open())
        {
            break;
        }
    }
    std::cout << std::endl;

    // grab the initial name & total test cases from opened file
    std::getline(file, loner);
    std::getline(file, testCases);
    test_cases = std::stoi(testCases);

    // iterate over each case
    for(auto i = 1; i <= test_cases; i++)
    {
        std::getline(file, str1);

        // grab info on next line; associate it to an istringstream object
        std::getline(file, str1);
        std::istringstream iss1(str1);
        iss1 >> num_of_names >> max_names;

        //< stores chars in each name of current case
        std::vector<hashMap<char, int>> name_char(num_of_names);
        //< stores each name on current case
        std::vector<std::string> names(num_of_names);
        //< stores # of common chars for each name of the case
        std::vector<int> count(num_of_names, 0);
        //< reference index for vectors 'names' and 'count'
        int j = 0;

        // grab info on next line; associate it to a new istringstream object
        std::getline(file, str2);
        std::istringstream iss2(str2);

        // iterate over each hashMap in vector 'name_char'
        for(auto n : name_char)
        {
            std::string name;  //< a name in the current case
            iss2 >> name;
            names[j] = name;

            // iterate over each char in 'name'
            for(auto &ch : name)
            {
                int char_count;  //< total matching chars in 'name'
                char ch_pair;    //< upper/lower case form of 'ch'

                // initialize 'ch_pair'
                ch_pair = (std::isupper(ch)) ? ch + ' ' : ch - ' ';

                // count upper & lower case occurences of 'ch' in 'loner'
                char_count = std::count(loner.begin(), loner.end(), ch) +
                             std::count(loner.begin(), loner.end(), ch_pair);

                // store a (ch, char_count) entry in our hashMap
                (n)[ch] = (char_count > 1) ? 1 : char_count;
            }

            // iterate over each char in 'name' again
            for(auto &ch : name)
            {
                // retrieve & add char counts of each 'ch'; store sum in count
                count[j] += (n)[ch];
            }
            ++j;
        }

        // start printing output
        std::cout << "Case " << i << ':';

        // check if 'max_names' names are printed
        while(max_names != 0)
        {
            int k;  //< index of largest char count in 'count'

            // initialize k
            k = std::distance(count.begin(),
                              std::max_element(count.begin(), count.end()));

            // print the name at index k of 'names'
            std::cout << ' ' << names[k];

            // remove printed name from 'names'
            names.erase(names.begin() + k);

            // remove char count of printed name from 'count
            count.erase(count.begin() + k);

            --max_names;
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
    file.close();

    return 0;
}

/* EOF */
