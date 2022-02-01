//
// Created by Oran on 27.01.22.
// I didn't want to delete this because I worked on it so long :(
//
#include<array>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "ppm.h"
/*
int main(){
   std::string path = "/Users/Oran/Documents/Master/WS21/algo_engineering/repo/test_p6.ppm";
   std::string output = "/Users/Oran/Documents/Master/WS21/algo_engineering/repo/output_p6.ppm";
   ppm img(path);
   img.write(output);

   bool bimgIsBinary;
   std::string nextLine, imgType;
   int nRows, nCols;
    //max intensity is USHRT_MAX (65335)
   unsigned short maxIntensity;
    std::ifstream file(path.c_str(), std::ios::binary);
   // output stream
   // openmode std::ios::binary for p6 files (-> the type can be read no matter the encoding), std::ios::in for read
   // EXPERIMENTAL: both work with with both file types?
   // read the first 2 lines:
   // 1.  P6 -> binary/P3 -> ASCII (needs around 3x(?) more space)
   // 2. rowsxcolumns -> format for the array
    // the image should be an array and not a vector: access is faster and the image is fixed size
    if(file >> nextLine)
    {
        imgType = nextLine;
        // type string to bool: image binary?
        // P6 binary
        // P3 ASCII
        // TODO: handle error case (neither P6 nor P3)
        bimgIsBinary = imgType == "P6" ? true : false;
    }
    // write the number of rows to a string, convert it to an int via stringstream
    if(file >> nextLine) {
        std::stringstream SSnRows(nextLine);
        SSnRows >> nRows;
    }
    // write the number of cols to a string, convert it to an int via stringstream
    if(file >> nextLine){
        std::stringstream SSnCols(nextLine);
        SSnCols >> nCols;
        // because we handle RGB tuples, we need 3 times as many columns
        nCols = nCols * 3;
    }

    if(file >> nextLine){
        std::stringstream SSnMax(nextLine);
        SSnMax >> maxIntensity;
    }


    std::cout << "Image is binary: " << bimgIsBinary << std::endl;
    std::cout << "Image Type " << imgType << std::endl;

    std::cout << nRows << " Rows" << std::endl;
    std::cout << nCols/3 << " Columns (3 times as many values)" << std::endl;

    std::cout << "Max intensity is " << maxIntensity << std::endl;
    unsigned char r[nRows][nCols], g[nRows][nCols], b[nRows][nCols];

    // 1 Byte per value
    // which is the size of a char
    if(maxIntensity < 256)
    {
        int curRow, curCol = 0;
        unsigned char color = 0;
        std::cout << std::getline(file, nextLine)<< std::endl;
        std::cout << std::getline(file, nextLine)<< std::endl;
        std::cout << std::getline(file, nextLine)<< std::endl;
        std::cout << std::getline(file, nextLine)<< std::endl;
        std::cout << std::getline(file, nextLine)<< std::endl;
        std::cout << std::getline(file, nextLine)<< std::endl;
        std::cout << std::getline(file, nextLine)<< std::endl;
        std::cout << std::getline(file, nextLine)<< std::endl;
        std::cout << std::getline(file, nextLine)<< std::endl;
        return 0;
        while(file >> nextLine)
        {
            if(curRow < nRows) {
                // we have 24 bits
                // r is the first 8, g is the second 8, b is the 3rd 8
                std::stringstream SSintensity(nextLine);
                std::cout << SSintensity << std::endl;
                short numRgbVals = sizeof(nextLine);
                unsigned char curIntensity[numRgbVals];
                std::cout << "Iteration " << curRow << std::endl;

                SSintensity >> curIntensity;
                //std::cout << curIntensity << std::endl;
                // the order of r,g,b
                for (int i = 0; i < numRgbVals; i++) {
                    std::cout << "Red val should be " << (int)curIntensity[i] << curRow << std::endl;

                    r[curRow][3 * i] = curIntensity[i];
                    g[curRow][3 * i + 1] = curIntensity[i + 1];
                    b[curRow][3 * i + 2] = curIntensity[i + 2];
                }
                curRow++;
            }
            else{
                curRow++;
                std::cout << curRow << std::endl;
            }
        }
    }
    // 2 Bytes per value
    else
    {
        //ignore for now
    }
    file.close();
    std::ofstream out(output, std::ios::binary);
    if(out.is_open()) {
        out << imgType << std::endl;
        out << nRows << ' ' << nCols << std::endl;
        out << maxIntensity << std::endl;
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                out << r[i][j] << g[i][j] << b[i][j];
                if(j==nCols-1)
                {
                    out << std::endl;
                }

            }
        }
    }
    return 0;
}
*/