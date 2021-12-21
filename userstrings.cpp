#include "userstrings.h"

UserStrings::UserStrings()
{
    //FixMe: As this is only written for demonstration purposes, we do not load any language-specific strings from a file
    mapIDtoString["uiWrongImageHeader"]="Image not supported";
    mapIDtoString["uiWrongImageText"]="The file with the path\n%1\nis not supported:\n%2";

}

/**
 * @brief UserStrings::getUserString
 * @param identifier the identifier for the wanted string
 * @return The string in the corresponding language or an "NotFound"
 */
std::string UserStrings::getUserString(std::string identifier) const
{
    if(mapIDtoString.find(identifier) != mapIDtoString.end()){
        return mapIDtoString.find(identifier)->second;
        //return i->second;

    }
    return "NotFound";

}
