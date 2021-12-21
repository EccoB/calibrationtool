#ifndef USERSTRINGS_H
#define USERSTRINGS_H
#include <string>
#include <map>
/**
 * This class intentionally does not use any QT-features to be more independet

*/


/**
 * @brief The UserStrings class holds all necessary language dependent strings that are displayed to the user
 */
class UserStrings
{
public:
    UserStrings();
    std::string getUserString(std::string identifier) const;
private:
    std::map<std::string, std::string> mapIDtoString;


};

#endif // USERSTRINGS_H
