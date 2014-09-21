// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto/join_request.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "join_request.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace mosp {

namespace {

const ::google::protobuf::Descriptor* JoinRequestMessage_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  JoinRequestMessage_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_proto_2fjoin_5frequest_2eproto() {
  protobuf_AddDesc_proto_2fjoin_5frequest_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "proto/join_request.proto");
  GOOGLE_CHECK(file != NULL);
  JoinRequestMessage_descriptor_ = file->message_type(0);
  static const int JoinRequestMessage_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(JoinRequestMessage, name_),
  };
  JoinRequestMessage_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      JoinRequestMessage_descriptor_,
      JoinRequestMessage::default_instance_,
      JoinRequestMessage_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(JoinRequestMessage, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(JoinRequestMessage, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(JoinRequestMessage));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_proto_2fjoin_5frequest_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    JoinRequestMessage_descriptor_, &JoinRequestMessage::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_proto_2fjoin_5frequest_2eproto() {
  delete JoinRequestMessage::default_instance_;
  delete JoinRequestMessage_reflection_;
}

void protobuf_AddDesc_proto_2fjoin_5frequest_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\030proto/join_request.proto\022\004mosp\"\"\n\022Join"
    "RequestMessage\022\014\n\004name\030\001 \002(\t", 68);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "proto/join_request.proto", &protobuf_RegisterTypes);
  JoinRequestMessage::default_instance_ = new JoinRequestMessage();
  JoinRequestMessage::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_proto_2fjoin_5frequest_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_proto_2fjoin_5frequest_2eproto {
  StaticDescriptorInitializer_proto_2fjoin_5frequest_2eproto() {
    protobuf_AddDesc_proto_2fjoin_5frequest_2eproto();
  }
} static_descriptor_initializer_proto_2fjoin_5frequest_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int JoinRequestMessage::kNameFieldNumber;
#endif  // !_MSC_VER

JoinRequestMessage::JoinRequestMessage()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:mosp.JoinRequestMessage)
}

void JoinRequestMessage::InitAsDefaultInstance() {
}

JoinRequestMessage::JoinRequestMessage(const JoinRequestMessage& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:mosp.JoinRequestMessage)
}

void JoinRequestMessage::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

JoinRequestMessage::~JoinRequestMessage() {
  // @@protoc_insertion_point(destructor:mosp.JoinRequestMessage)
  SharedDtor();
}

void JoinRequestMessage::SharedDtor() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (this != default_instance_) {
  }
}

void JoinRequestMessage::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* JoinRequestMessage::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return JoinRequestMessage_descriptor_;
}

const JoinRequestMessage& JoinRequestMessage::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_proto_2fjoin_5frequest_2eproto();
  return *default_instance_;
}

JoinRequestMessage* JoinRequestMessage::default_instance_ = NULL;

JoinRequestMessage* JoinRequestMessage::New() const {
  return new JoinRequestMessage;
}

void JoinRequestMessage::Clear() {
  if (has_name()) {
    if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
      name_->clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool JoinRequestMessage::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:mosp.JoinRequestMessage)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string name = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:mosp.JoinRequestMessage)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:mosp.JoinRequestMessage)
  return false;
#undef DO_
}

void JoinRequestMessage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:mosp.JoinRequestMessage)
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->name(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:mosp.JoinRequestMessage)
}

::google::protobuf::uint8* JoinRequestMessage::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:mosp.JoinRequestMessage)
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mosp.JoinRequestMessage)
  return target;
}

int JoinRequestMessage::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void JoinRequestMessage::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const JoinRequestMessage* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const JoinRequestMessage*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void JoinRequestMessage::MergeFrom(const JoinRequestMessage& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_name(from.name());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void JoinRequestMessage::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void JoinRequestMessage::CopyFrom(const JoinRequestMessage& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool JoinRequestMessage::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void JoinRequestMessage::Swap(JoinRequestMessage* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata JoinRequestMessage::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = JoinRequestMessage_descriptor_;
  metadata.reflection = JoinRequestMessage_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace mosp

// @@protoc_insertion_point(global_scope)