#include "DSVWriter.h"
#include "DataSink.h"

struct CDSVWriter::SImplementation {
    std::shared_ptr<CDataSink> sink;
    char delimiter;
    bool quoteall;

    SImplementation(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall): sink(sink), delimiter(delimiter), quoteall(quoteall) {
    }

    bool Writerow(const std::vector<std::string> &row){
        
    }

};