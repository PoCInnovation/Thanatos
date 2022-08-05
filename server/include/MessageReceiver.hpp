#ifndef __MESSAGERECEIVER_HPP__
    #define __MESSAGERECEIVER_HPP__
    #include <sstream>
    #include <map>
    #include <vector>

class MessageReceiver {
    std::map<std::string, std::string> parameters;

public:
    std::vector<std::pair<std::string, std::string>> files;

    MessageReceiver(std::stringstream &message);

    std::string getParameter(std::string &key)
    {
        return parameters.at(key);
    }

    void setParameter(std::string &key, std::string &value)
    {
        parameters.insert(key, value);
    }
};

#endif
