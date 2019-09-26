#include "atsp.h"

#include <string>
#include <fstream>
#include <regex>

using namespace std;

void loadData(std::string fname, ProblemData & data)
{
    ifstream file(fname);

    if ( file.is_open() )
    {
        string line;
        getline(file,line); // problem name

        smatch m;
        regex e("^\\s*NAME\\s*:\\s*(\\w+)");

        if ( regex_search (line,m,e) )
        {
            const string id(m[1]);

            getline(file,line); // type
            getline(file,line); // comment
            getline(file,line); // matrix size

            e = "^\\s*DIMENSION\\s*:\\s*(\\d+)";
            if ( regex_search (line,m,e) )
            {
                const uint size = static_cast<uint>(stoul(m[1]));

                getline(file,line); // weight type
                getline(file,line); // weight format
                getline(file,line); // weight section

                int value = 0;
                data.reserve(size);

                for( uint i = 0; i < size; ++i )
                {
                    vector<int> row;
                    row.reserve(size);

                    for( uint j = 0; j < size; ++j )
                    {
                        file >> value;
                        row.push_back(value);
                    }
                    data.push_back(row);
                }
            }
        }
    }
}
