#include "utils.h"

namespace utils
{

std::vector<std::string> split(const std::string& content, const std::string& delimeter)
{
    std::vector<std::string> splitContents;
    std::string::size_type start = 0;
    std::string::size_type end = content.find(delimeter);
    while (end != std::string::npos)
    {
        std::string token = content.substr(start, end - start);
        splitContents.push_back(token);
        start = end + delimeter.length();
        end = content.find(delimeter, start);
    }
    std::string token = content.substr(start, end - start);
    splitContents.push_back(token);
    return splitContents;
}

}
