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

    std::string getParameter(const std::string &key)
    {
        auto parameter = parameters.find(key);
        return parameter == parameters.end() ? parameter->second : "";
    }

    void setParameter(const std::string &key, std::string &value)
    {
        parameters[key] = value;
    }
};

#endif
