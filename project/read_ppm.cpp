//
// Created by Oran on 27.01.22.
//
#include "scanpp.h"
#include<array>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>


int main(){
   std::string path = "/Users/Oran/Documents/Master/WS21/algo_engineering/repo/test_p3.ppm";
   bool bimgIsBinary;
   std::string nextLine, imgType;
   int nRows, nCols;
   // output stream
   // openmode std::ios::binary for p6 files (-> the type can be read no matter the encoding), std::ios::in for read
   // EXPERIMENTAL: both work with with both file types?
   // read the first 2 lines:
   // 1.  P6 -> binary/P3 -> ASCII (needs around 3x(?) more space)
   // 2. rowsxcolumns -> format for the array
    // the image should be an array and not a vector: access is faster and the image is fixed size
    std::ifstream file(path.c_str(), std::ios::binary);
    file >> nextLine;
    imgType = nextLine;

    // write the number of rows to a string, convert it to an int via stringstream
    file >> nextLine;
    std::stringstream SSnRows(nextLine);
    SSnRows >> nRows;

    // write the number of cols to a string, convert it to an int via stringstream
    file >> nextLine;
    std::stringstream SSnCols(nextLine);
    SSnCols >> nCols;

    // type string to bool: image binary?
    // is the image binary?
    // P6 binary
    // P3 ASCII
    // TODO: handle error case (neither P6 nor P3)
    bimgIsBinary = imgType == "P6" ? true : false;
    std::cout << bimgIsBinary << std::endl;
    std::cout << imgType << std::endl;

    std::cout << nRows << std::endl;
    std::cout << nCols << std::endl;

    return 0;
}
