#include <iostream>
#include <string>
#include <cstring>
#include "myVector.h"

const int maxCase{6};
const int maxCharInput{50};

void PushData(MyVector &vec){
    data_t newData;
    std::string tmpString;
    std::cout << "Input number: ";
    std::cin >> newData.number;
    std::cout << "Input string: ";
    std::cin.ignore();
    std::getline(std::cin, tmpString);
    newData.aString = const_cast<char*>(tmpString.c_str());

    std::string frontOrBackKey; 
    std::cout << "Push front or back (f/B): ";
    std::getline(std::cin, frontOrBackKey);
    char frontOrBackFisrtChar = frontOrBackKey.c_str()[0];
    if(frontOrBackFisrtChar == 'f' || frontOrBackFisrtChar == 'F')
        vec.push_front(newData);
    else if(frontOrBackFisrtChar == 'b' || frontOrBackFisrtChar == 'B' || frontOrBackFisrtChar == '\0')
        vec.push_back(newData);
    else
        std::cout << "Pushing cancelled." << std::endl;
}

void PopData(MyVector &vec){
    std::string frontOrBackKey; 
    std::cout << "Pop front or back (f/B): ";
    std::cin.ignore();
    std::getline(std::cin, frontOrBackKey);
    char frontOrBackFisrtChar = frontOrBackKey.c_str()[0];
    if(frontOrBackFisrtChar == 'f' || frontOrBackFisrtChar == 'F'){
        vec.pop_front();
    }
    else if(frontOrBackFisrtChar == 'b' || frontOrBackFisrtChar == 'B' || frontOrBackFisrtChar == '\0'){
        vec.pop_back();
    }
    else
        std::cout << "Popping cancelled." << std::endl;
}

void InsertData(MyVector &vec){
    data_t newData;
    std::string tmpString;
    std::cout << "Input number: ";
    std::cin >> newData.number;
    std::cout << "Input string: ";
    std::cin.ignore();
    std::getline(std::cin, tmpString);
    newData.aString = const_cast<char*>(tmpString.c_str());

    int insertPos{-1};
    std::cout << "Input inserted position: ";
    std::cin >> insertPos;
    if(insertPos < 0 || insertPos > vec.size())
        std::cout << "Invalid position!" << std::endl;
    else
        vec.insert(insertPos, newData);
}

void EraseData(MyVector &vec){
    int erasePos{-1};
    std::cout << "Input erased position: ";
    std::cin >> erasePos;
    if(erasePos < 0 || erasePos > vec.size())
        std::cout << "Invalid position!" << std::endl;
    else
        vec.erase(erasePos);
}

void PrintData(MyVector &vec){
    if(vec.empty() == true){
        std::cout << "This vector is empty!" << std::endl;
    }
    else{
        std::cout << "vector's size: " << vec.size() << " | ";
        for(int i=0; i<vec.size(); ++i){
            std::cout << "(" << vec[i].number << "," << vec[i].aString << ") ";
        }
        std::cout << std::endl;
    }
}

void menu(){
    MyVector dataVec;
    int key{-1};
    while(key != 0){
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "What do you want to do?" << std::endl;
        std::cout << "1. Push data" << std::endl;
        std::cout << "2. Pop data" << std::endl;
        std::cout << "3. Insert data" << std::endl;
        std::cout << "4. Erase data" << std::endl;
        std::cout << "5. Clear all" << std::endl;
        std::cout << "6. Print vector" << std::endl;
        std::cout << "0. Quit" << std::endl;
        std::cin >> key;
        while(key < 0 || key > maxCase){
            std::cout << "Invalid input! Please choose again." << std::endl;
            std::cin >> key;
        }
        switch (key)
        {
        case 1:
            PushData(dataVec);
            break;
        case 2:
            PopData(dataVec);
            break;
        case 3:
            InsertData(dataVec);
            break;
        case 4:
            EraseData(dataVec);
            break;
        case 5:
            dataVec.clear();
            break;
        case 6:
            PrintData(dataVec);
            break;
        case 0:
            break;
        default:
            break;
        }
    }
}

int main() {
    menu();
    return 0;
}