#ifndef __RECEIVEDREQ_HPP
    #define __RECEIVEDREQ_HPP
    #include <map>
    #include <vector>

    class ReceivedReq
    {
        std::map parameters;
    public:
        std::vector<std::pair<std::string, std::string>> files;
        ReceivedReq(std::stringstream &raw_message);
    private:
        void add_header(std::string &key, std::string &value);
    };

#endif
