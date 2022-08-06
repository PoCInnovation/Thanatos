#ifndef __MESSAGERECEIVER_HPP__
    #define __MESSAGERECEIVER_HPP__
    #include <sstream>
    #include <map>
    #include <vector>
    #include <optional>

class MessageReceiver {
    std::map<std::string, std::string> parameters;

public:
    std::vector<std::pair<std::string, std::string>> files;

    MessageReceiver(std::stringstream &message);

    std::optional<std::string> getParameter(const std::string &key)
    {
        auto parameter = parameters.find(key);
        return parameter != parameters.end() ? std::optional(parameter->second) : std::nullopt;
    }

    void setParameter(const std::string &key, std::string &value)
    {
        parameters[key] = value;
    }
};

#endif
