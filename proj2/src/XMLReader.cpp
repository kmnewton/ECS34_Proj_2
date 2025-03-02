#include "XMLReader.h"
#include "XMLEntity.h"
#include <expat.h>
#include <vector>
#include <memory>
#include <stack>

struct CXMLReader::SImplementation {
    std::shared_ptr<CDataSource> source;
    XML_Parser parser;
    std::stack<SXMLEntity> stack;
    bool dataend;

    SImplementation(std::shared_ptr<CDataSource> src) : source(src), dataend(false) {
        parser = XML_ParserCreate(nullptr);
        XML_SetUserData(parser, this);
        XML_SetElementHandler(parser, StartElementHandler, EndElementHandler);
        XML_SetCharacterDataHandler(parser, CharacterDataHandler);
    }

    ~SImplementation() {
        XML_ParserFree(parser);
    }

    static void StartElementHandler(void *data, const char *name, const char ** attributes) {
        auto * impl = static_cast<SImplementation *>(data);
        SXMLEntity ent;
        ent.DType = SXMLEntity::EType::StartElement; 
        ent.DNameData = name;

        for (int i = 0; attributes[i]; i += 2){
            ent.DAttributes.emplace_back(attributes[i], attributes[i + 1]);
        }

        impl->stack.push(ent);
    }

    static void EndElementHandler(void * data, const char * name) {
        auto *impl = static_cast<SImplementation *>(data);
        SXMLEntity ent; 
        ent.DType = SXMLEntity::EType::EndElement;
        ent.DNameData = name;
        impl->stack.push(ent);
    }

    static void CharacterDataHandler(void * udata, const char * s, int length) {
        auto * impl = static_cast<SImplementation *>(udata);
        std::string data(s, length);
        if (s && length > 0) {
            SXMLEntity ent;
            ent.DType = SXMLEntity::EType::CharData;
            ent.DNameData = data;
            impl->stack.push(ent);
        }
    }

    bool ReadEntity(SXMLEntity &entity, bool skipdata = false) {
        std::vector<char> buffer(4096);
        while (!dataend) {
            size_t bytes = source->Read(buffer, sizeof(buffer));
            if (bytes == 0) {
                dataend = true; 
                return false;
            }

            if (!stack.empty()) {
                entity = stack.top();
                stack.pop();
                return true;
            }

            if (XML_Parse(parser, buffer.data(), bytes, 0) == XML_STATUS_ERROR) {
                return false;
            }
        }
        if (!stack.empty()) {
            entity = stack.top();
            stack.pop();
            return true;
        }
        return false;
    }

};

CXMLReader::CXMLReader(std::shared_ptr<CDataSource> src) : DImplementation(std::make_unique<SImplementation>(std::move(src))) {

}

CXMLReader::~CXMLReader() = default;

bool CXMLReader::End() const {
    return DImplementation->dataend && DImplementation->stack.empty();
}

bool CXMLReader::ReadEntity(SXMLEntity& entity, bool skipCharData) {
    return DImplementation->ReadEntity(entity, skipCharData);
}
