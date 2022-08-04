#include <string>
#include <iostream>
#include <iostream>
#include <fstream>

void CreateFile(std::string FileName, std::string FileContent)
{
    std::ofstream outfile (FileName);

    outfile << FileContent << std::endl;
    outfile.close();
}
