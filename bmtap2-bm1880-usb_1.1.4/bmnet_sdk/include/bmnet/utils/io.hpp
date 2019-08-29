/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _UTILS_IO_H_
#define _UTILS_IO_H_

#include <boost/filesystem.hpp>
#include <iomanip>
#include <iostream>  // NOLINT(readability/streams)
#include <string>

#include <google/protobuf/message.h>

namespace bmnet {

using std::string;
using ::google::protobuf::Message;
using ::boost::filesystem::path;

bool ReadProtoFromTextFile(const char* filename, Message* proto);
inline bool ReadProtoFromTextFile(const string& filename, Message* proto) {
  return ReadProtoFromTextFile(filename.c_str(), proto);
}

void WriteProtoToTextFile(const Message& proto, const char* filename);
inline void WriteProtoToTextFile(const Message& proto, const string& filename) {
  WriteProtoToTextFile(proto, filename.c_str());
}

bool ReadProtoFromString(const std::string &str_proto, Message& proto);

void WriteProtoToString(const Message& proto, std::string &str_proto);

bool ReadProtoFromBinaryFile(const char* filename, Message* proto);

void ReadProtoFromCodedStream(const std::string &str_proto, Message& proto);

inline bool ReadProtoFromBinaryFile(const string& filename, Message* proto) {
  return ReadProtoFromBinaryFile(filename.c_str(), proto);
}

void WriteProtoToBinaryFile(const Message& proto, const char* filename);
inline void WriteProtoToBinaryFile(
    const Message& proto, const string& filename) {
  WriteProtoToBinaryFile(proto, filename.c_str());
}

void ReadFloatDataFromBinaryFile(const string& filename, std::vector<float>& data);
void ReadDataFromBinaryFile(const string& filename, std::vector<float>& data);
void ReadDataFromBinaryFile(const string& filename, std::vector<int8_t>& data);

void WriteDataToBinaryFile(std::vector<float>* data, const string& filename);
void WriteDataToBinaryFile(std::vector<int8_t>* data, const string& filename);

void WriteFloatDataToBinaryFile(void *data, uint32_t size, const string& filename);

/*
 * Int8 version
 */

void ReadInt8DataFromBinaryFile(const string& filename, std::vector<int8_t>& data);

void WriteInt8DataToBinaryFile(std::vector<int8_t>* data, const string& filename);

std::string ReadStringFromFile(const std::string& filename);

}  // namespace bmnet

#endif   // _UTILS_IO_H_
