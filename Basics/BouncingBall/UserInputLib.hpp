#pragma once
#include <iostream>
#include <string_view>
#include <limits>

namespace userInput{
    
    template <typename T> T getInput(std::string_view outMessage = "Please enter a double: ", std::string_view errorMessage = "Oops, that input is invalid.  Please try again.\n"){

        while(true){

            std::cout << outMessage;
            T x{};
            std::cin >>x;
            
            //checking if extraction failed
            if(!std::cin){

                //checking if some special OS key has been entered
                if(std::cin.eof()){
                    std::exit(0); //stopping the program if true because input stream has been disconnected
                }
            
                //clearing input stream and removing newlines, tabs, etc
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                std::cout << errorMessage;
                continue; 
            }
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;

        }
    }
}