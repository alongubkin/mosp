// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: messages.proto

#ifndef PROTOBUF_messages_2eproto__INCLUDED
#define PROTOBUF_messages_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace mosp {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_messages_2eproto();
void protobuf_AssignDesc_messages_2eproto();
void protobuf_ShutdownFile_messages_2eproto();

class BaseMessage;
class Vector3;
class JoinRequestMessage;
class JoinNotificationMessage;
class MoveRequestMessage;
class MoveNotificationMessage;

enum Type {
  JoinRequest = 1,
  JoinNotification = 2,
  MoveRequest = 3,
  MoveNotification = 4
};
bool Type_IsValid(int value);
const Type Type_MIN = JoinRequest;
const Type Type_MAX = MoveNotification;
const int Type_ARRAYSIZE = Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* Type_descriptor();
inline const ::std::string& Type_Name(Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    Type_descriptor(), value);
}
inline bool Type_Parse(
    const ::std::string& name, Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Type>(
    Type_descriptor(), name, value);
}
// ===================================================================

class BaseMessage : public ::google::protobuf::Message {
 public:
  BaseMessage();
  virtual ~BaseMessage();

  BaseMessage(const BaseMessage& from);

  inline BaseMessage& operator=(const BaseMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const BaseMessage& default_instance();

  void Swap(BaseMessage* other);

  // implements Message ----------------------------------------------

  BaseMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BaseMessage& from);
  void MergeFrom(const BaseMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .mosp.Type type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::mosp::Type type() const;
  inline void set_type(::mosp::Type value);

  // @@protoc_insertion_point(class_scope:mosp.BaseMessage)
 private:
  inline void set_has_type();
  inline void clear_has_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  int type_;
  friend void  protobuf_AddDesc_messages_2eproto();
  friend void protobuf_AssignDesc_messages_2eproto();
  friend void protobuf_ShutdownFile_messages_2eproto();

  void InitAsDefaultInstance();
  static BaseMessage* default_instance_;
};
// -------------------------------------------------------------------

class Vector3 : public ::google::protobuf::Message {
 public:
  Vector3();
  virtual ~Vector3();

  Vector3(const Vector3& from);

  inline Vector3& operator=(const Vector3& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Vector3& default_instance();

  void Swap(Vector3* other);

  // implements Message ----------------------------------------------

  Vector3* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Vector3& from);
  void MergeFrom(const Vector3& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required double x = 1;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 1;
  inline double x() const;
  inline void set_x(double value);

  // required double y = 2;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 2;
  inline double y() const;
  inline void set_y(double value);

  // required double z = 3;
  inline bool has_z() const;
  inline void clear_z();
  static const int kZFieldNumber = 3;
  inline double z() const;
  inline void set_z(double value);

  // @@protoc_insertion_point(class_scope:mosp.Vector3)
 private:
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_z();
  inline void clear_has_z();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  double x_;
  double y_;
  double z_;
  friend void  protobuf_AddDesc_messages_2eproto();
  friend void protobuf_AssignDesc_messages_2eproto();
  friend void protobuf_ShutdownFile_messages_2eproto();

  void InitAsDefaultInstance();
  static Vector3* default_instance_;
};
// -------------------------------------------------------------------

class JoinRequestMessage : public ::google::protobuf::Message {
 public:
  JoinRequestMessage();
  virtual ~JoinRequestMessage();

  JoinRequestMessage(const JoinRequestMessage& from);

  inline JoinRequestMessage& operator=(const JoinRequestMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const JoinRequestMessage& default_instance();

  void Swap(JoinRequestMessage* other);

  // implements Message ----------------------------------------------

  JoinRequestMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const JoinRequestMessage& from);
  void MergeFrom(const JoinRequestMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .mosp.Type type = 1 [default = JoinRequest];
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::mosp::Type type() const;
  inline void set_type(::mosp::Type value);

  // required string name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // @@protoc_insertion_point(class_scope:mosp.JoinRequestMessage)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* name_;
  int type_;
  friend void  protobuf_AddDesc_messages_2eproto();
  friend void protobuf_AssignDesc_messages_2eproto();
  friend void protobuf_ShutdownFile_messages_2eproto();

  void InitAsDefaultInstance();
  static JoinRequestMessage* default_instance_;
};
// -------------------------------------------------------------------

class JoinNotificationMessage : public ::google::protobuf::Message {
 public:
  JoinNotificationMessage();
  virtual ~JoinNotificationMessage();

  JoinNotificationMessage(const JoinNotificationMessage& from);

  inline JoinNotificationMessage& operator=(const JoinNotificationMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const JoinNotificationMessage& default_instance();

  void Swap(JoinNotificationMessage* other);

  // implements Message ----------------------------------------------

  JoinNotificationMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const JoinNotificationMessage& from);
  void MergeFrom(const JoinNotificationMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .mosp.Type type = 1 [default = JoinNotification];
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::mosp::Type type() const;
  inline void set_type(::mosp::Type value);

  // required string name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // required int32 client_id = 3;
  inline bool has_client_id() const;
  inline void clear_client_id();
  static const int kClientIdFieldNumber = 3;
  inline ::google::protobuf::int32 client_id() const;
  inline void set_client_id(::google::protobuf::int32 value);

  // required .mosp.Vector3 position = 4;
  inline bool has_position() const;
  inline void clear_position();
  static const int kPositionFieldNumber = 4;
  inline const ::mosp::Vector3& position() const;
  inline ::mosp::Vector3* mutable_position();
  inline ::mosp::Vector3* release_position();
  inline void set_allocated_position(::mosp::Vector3* position);

  // @@protoc_insertion_point(class_scope:mosp.JoinNotificationMessage)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_client_id();
  inline void clear_has_client_id();
  inline void set_has_position();
  inline void clear_has_position();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* name_;
  int type_;
  ::google::protobuf::int32 client_id_;
  ::mosp::Vector3* position_;
  friend void  protobuf_AddDesc_messages_2eproto();
  friend void protobuf_AssignDesc_messages_2eproto();
  friend void protobuf_ShutdownFile_messages_2eproto();

  void InitAsDefaultInstance();
  static JoinNotificationMessage* default_instance_;
};
// -------------------------------------------------------------------

class MoveRequestMessage : public ::google::protobuf::Message {
 public:
  MoveRequestMessage();
  virtual ~MoveRequestMessage();

  MoveRequestMessage(const MoveRequestMessage& from);

  inline MoveRequestMessage& operator=(const MoveRequestMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MoveRequestMessage& default_instance();

  void Swap(MoveRequestMessage* other);

  // implements Message ----------------------------------------------

  MoveRequestMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MoveRequestMessage& from);
  void MergeFrom(const MoveRequestMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .mosp.Type type = 1 [default = MoveRequest];
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::mosp::Type type() const;
  inline void set_type(::mosp::Type value);

  // required .mosp.Vector3 position = 2;
  inline bool has_position() const;
  inline void clear_position();
  static const int kPositionFieldNumber = 2;
  inline const ::mosp::Vector3& position() const;
  inline ::mosp::Vector3* mutable_position();
  inline ::mosp::Vector3* release_position();
  inline void set_allocated_position(::mosp::Vector3* position);

  // @@protoc_insertion_point(class_scope:mosp.MoveRequestMessage)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_position();
  inline void clear_has_position();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::mosp::Vector3* position_;
  int type_;
  friend void  protobuf_AddDesc_messages_2eproto();
  friend void protobuf_AssignDesc_messages_2eproto();
  friend void protobuf_ShutdownFile_messages_2eproto();

  void InitAsDefaultInstance();
  static MoveRequestMessage* default_instance_;
};
// -------------------------------------------------------------------

class MoveNotificationMessage : public ::google::protobuf::Message {
 public:
  MoveNotificationMessage();
  virtual ~MoveNotificationMessage();

  MoveNotificationMessage(const MoveNotificationMessage& from);

  inline MoveNotificationMessage& operator=(const MoveNotificationMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MoveNotificationMessage& default_instance();

  void Swap(MoveNotificationMessage* other);

  // implements Message ----------------------------------------------

  MoveNotificationMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MoveNotificationMessage& from);
  void MergeFrom(const MoveNotificationMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .mosp.Type type = 1 [default = JoinNotification];
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::mosp::Type type() const;
  inline void set_type(::mosp::Type value);

  // required int32 client_id = 2;
  inline bool has_client_id() const;
  inline void clear_client_id();
  static const int kClientIdFieldNumber = 2;
  inline ::google::protobuf::int32 client_id() const;
  inline void set_client_id(::google::protobuf::int32 value);

  // required .mosp.Vector3 position = 3;
  inline bool has_position() const;
  inline void clear_position();
  static const int kPositionFieldNumber = 3;
  inline const ::mosp::Vector3& position() const;
  inline ::mosp::Vector3* mutable_position();
  inline ::mosp::Vector3* release_position();
  inline void set_allocated_position(::mosp::Vector3* position);

  // @@protoc_insertion_point(class_scope:mosp.MoveNotificationMessage)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_client_id();
  inline void clear_has_client_id();
  inline void set_has_position();
  inline void clear_has_position();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  int type_;
  ::google::protobuf::int32 client_id_;
  ::mosp::Vector3* position_;
  friend void  protobuf_AddDesc_messages_2eproto();
  friend void protobuf_AssignDesc_messages_2eproto();
  friend void protobuf_ShutdownFile_messages_2eproto();

  void InitAsDefaultInstance();
  static MoveNotificationMessage* default_instance_;
};
// ===================================================================


// ===================================================================

// BaseMessage

// required .mosp.Type type = 1;
inline bool BaseMessage::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BaseMessage::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BaseMessage::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BaseMessage::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::mosp::Type BaseMessage::type() const {
  // @@protoc_insertion_point(field_get:mosp.BaseMessage.type)
  return static_cast< ::mosp::Type >(type_);
}
inline void BaseMessage::set_type(::mosp::Type value) {
  assert(::mosp::Type_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:mosp.BaseMessage.type)
}

// -------------------------------------------------------------------

// Vector3

// required double x = 1;
inline bool Vector3::has_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Vector3::set_has_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Vector3::clear_has_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Vector3::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline double Vector3::x() const {
  // @@protoc_insertion_point(field_get:mosp.Vector3.x)
  return x_;
}
inline void Vector3::set_x(double value) {
  set_has_x();
  x_ = value;
  // @@protoc_insertion_point(field_set:mosp.Vector3.x)
}

// required double y = 2;
inline bool Vector3::has_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Vector3::set_has_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Vector3::clear_has_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Vector3::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline double Vector3::y() const {
  // @@protoc_insertion_point(field_get:mosp.Vector3.y)
  return y_;
}
inline void Vector3::set_y(double value) {
  set_has_y();
  y_ = value;
  // @@protoc_insertion_point(field_set:mosp.Vector3.y)
}

// required double z = 3;
inline bool Vector3::has_z() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Vector3::set_has_z() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Vector3::clear_has_z() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Vector3::clear_z() {
  z_ = 0;
  clear_has_z();
}
inline double Vector3::z() const {
  // @@protoc_insertion_point(field_get:mosp.Vector3.z)
  return z_;
}
inline void Vector3::set_z(double value) {
  set_has_z();
  z_ = value;
  // @@protoc_insertion_point(field_set:mosp.Vector3.z)
}

// -------------------------------------------------------------------

// JoinRequestMessage

// required .mosp.Type type = 1 [default = JoinRequest];
inline bool JoinRequestMessage::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void JoinRequestMessage::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void JoinRequestMessage::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void JoinRequestMessage::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::mosp::Type JoinRequestMessage::type() const {
  // @@protoc_insertion_point(field_get:mosp.JoinRequestMessage.type)
  return static_cast< ::mosp::Type >(type_);
}
inline void JoinRequestMessage::set_type(::mosp::Type value) {
  assert(::mosp::Type_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:mosp.JoinRequestMessage.type)
}

// required string name = 2;
inline bool JoinRequestMessage::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void JoinRequestMessage::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void JoinRequestMessage::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void JoinRequestMessage::clear_name() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& JoinRequestMessage::name() const {
  // @@protoc_insertion_point(field_get:mosp.JoinRequestMessage.name)
  return *name_;
}
inline void JoinRequestMessage::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set:mosp.JoinRequestMessage.name)
}
inline void JoinRequestMessage::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set_char:mosp.JoinRequestMessage.name)
}
inline void JoinRequestMessage::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:mosp.JoinRequestMessage.name)
}
inline ::std::string* JoinRequestMessage::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:mosp.JoinRequestMessage.name)
  return name_;
}
inline ::std::string* JoinRequestMessage::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void JoinRequestMessage::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:mosp.JoinRequestMessage.name)
}

// -------------------------------------------------------------------

// JoinNotificationMessage

// required .mosp.Type type = 1 [default = JoinNotification];
inline bool JoinNotificationMessage::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void JoinNotificationMessage::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void JoinNotificationMessage::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void JoinNotificationMessage::clear_type() {
  type_ = 2;
  clear_has_type();
}
inline ::mosp::Type JoinNotificationMessage::type() const {
  // @@protoc_insertion_point(field_get:mosp.JoinNotificationMessage.type)
  return static_cast< ::mosp::Type >(type_);
}
inline void JoinNotificationMessage::set_type(::mosp::Type value) {
  assert(::mosp::Type_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:mosp.JoinNotificationMessage.type)
}

// required string name = 2;
inline bool JoinNotificationMessage::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void JoinNotificationMessage::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void JoinNotificationMessage::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void JoinNotificationMessage::clear_name() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& JoinNotificationMessage::name() const {
  // @@protoc_insertion_point(field_get:mosp.JoinNotificationMessage.name)
  return *name_;
}
inline void JoinNotificationMessage::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set:mosp.JoinNotificationMessage.name)
}
inline void JoinNotificationMessage::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set_char:mosp.JoinNotificationMessage.name)
}
inline void JoinNotificationMessage::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:mosp.JoinNotificationMessage.name)
}
inline ::std::string* JoinNotificationMessage::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:mosp.JoinNotificationMessage.name)
  return name_;
}
inline ::std::string* JoinNotificationMessage::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void JoinNotificationMessage::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:mosp.JoinNotificationMessage.name)
}

// required int32 client_id = 3;
inline bool JoinNotificationMessage::has_client_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void JoinNotificationMessage::set_has_client_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void JoinNotificationMessage::clear_has_client_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void JoinNotificationMessage::clear_client_id() {
  client_id_ = 0;
  clear_has_client_id();
}
inline ::google::protobuf::int32 JoinNotificationMessage::client_id() const {
  // @@protoc_insertion_point(field_get:mosp.JoinNotificationMessage.client_id)
  return client_id_;
}
inline void JoinNotificationMessage::set_client_id(::google::protobuf::int32 value) {
  set_has_client_id();
  client_id_ = value;
  // @@protoc_insertion_point(field_set:mosp.JoinNotificationMessage.client_id)
}

// required .mosp.Vector3 position = 4;
inline bool JoinNotificationMessage::has_position() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void JoinNotificationMessage::set_has_position() {
  _has_bits_[0] |= 0x00000008u;
}
inline void JoinNotificationMessage::clear_has_position() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void JoinNotificationMessage::clear_position() {
  if (position_ != NULL) position_->::mosp::Vector3::Clear();
  clear_has_position();
}
inline const ::mosp::Vector3& JoinNotificationMessage::position() const {
  // @@protoc_insertion_point(field_get:mosp.JoinNotificationMessage.position)
  return position_ != NULL ? *position_ : *default_instance_->position_;
}
inline ::mosp::Vector3* JoinNotificationMessage::mutable_position() {
  set_has_position();
  if (position_ == NULL) position_ = new ::mosp::Vector3;
  // @@protoc_insertion_point(field_mutable:mosp.JoinNotificationMessage.position)
  return position_;
}
inline ::mosp::Vector3* JoinNotificationMessage::release_position() {
  clear_has_position();
  ::mosp::Vector3* temp = position_;
  position_ = NULL;
  return temp;
}
inline void JoinNotificationMessage::set_allocated_position(::mosp::Vector3* position) {
  delete position_;
  position_ = position;
  if (position) {
    set_has_position();
  } else {
    clear_has_position();
  }
  // @@protoc_insertion_point(field_set_allocated:mosp.JoinNotificationMessage.position)
}

// -------------------------------------------------------------------

// MoveRequestMessage

// required .mosp.Type type = 1 [default = MoveRequest];
inline bool MoveRequestMessage::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MoveRequestMessage::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MoveRequestMessage::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MoveRequestMessage::clear_type() {
  type_ = 3;
  clear_has_type();
}
inline ::mosp::Type MoveRequestMessage::type() const {
  // @@protoc_insertion_point(field_get:mosp.MoveRequestMessage.type)
  return static_cast< ::mosp::Type >(type_);
}
inline void MoveRequestMessage::set_type(::mosp::Type value) {
  assert(::mosp::Type_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:mosp.MoveRequestMessage.type)
}

// required .mosp.Vector3 position = 2;
inline bool MoveRequestMessage::has_position() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MoveRequestMessage::set_has_position() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MoveRequestMessage::clear_has_position() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MoveRequestMessage::clear_position() {
  if (position_ != NULL) position_->::mosp::Vector3::Clear();
  clear_has_position();
}
inline const ::mosp::Vector3& MoveRequestMessage::position() const {
  // @@protoc_insertion_point(field_get:mosp.MoveRequestMessage.position)
  return position_ != NULL ? *position_ : *default_instance_->position_;
}
inline ::mosp::Vector3* MoveRequestMessage::mutable_position() {
  set_has_position();
  if (position_ == NULL) position_ = new ::mosp::Vector3;
  // @@protoc_insertion_point(field_mutable:mosp.MoveRequestMessage.position)
  return position_;
}
inline ::mosp::Vector3* MoveRequestMessage::release_position() {
  clear_has_position();
  ::mosp::Vector3* temp = position_;
  position_ = NULL;
  return temp;
}
inline void MoveRequestMessage::set_allocated_position(::mosp::Vector3* position) {
  delete position_;
  position_ = position;
  if (position) {
    set_has_position();
  } else {
    clear_has_position();
  }
  // @@protoc_insertion_point(field_set_allocated:mosp.MoveRequestMessage.position)
}

// -------------------------------------------------------------------

// MoveNotificationMessage

// required .mosp.Type type = 1 [default = JoinNotification];
inline bool MoveNotificationMessage::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MoveNotificationMessage::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MoveNotificationMessage::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MoveNotificationMessage::clear_type() {
  type_ = 2;
  clear_has_type();
}
inline ::mosp::Type MoveNotificationMessage::type() const {
  // @@protoc_insertion_point(field_get:mosp.MoveNotificationMessage.type)
  return static_cast< ::mosp::Type >(type_);
}
inline void MoveNotificationMessage::set_type(::mosp::Type value) {
  assert(::mosp::Type_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:mosp.MoveNotificationMessage.type)
}

// required int32 client_id = 2;
inline bool MoveNotificationMessage::has_client_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MoveNotificationMessage::set_has_client_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MoveNotificationMessage::clear_has_client_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MoveNotificationMessage::clear_client_id() {
  client_id_ = 0;
  clear_has_client_id();
}
inline ::google::protobuf::int32 MoveNotificationMessage::client_id() const {
  // @@protoc_insertion_point(field_get:mosp.MoveNotificationMessage.client_id)
  return client_id_;
}
inline void MoveNotificationMessage::set_client_id(::google::protobuf::int32 value) {
  set_has_client_id();
  client_id_ = value;
  // @@protoc_insertion_point(field_set:mosp.MoveNotificationMessage.client_id)
}

// required .mosp.Vector3 position = 3;
inline bool MoveNotificationMessage::has_position() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MoveNotificationMessage::set_has_position() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MoveNotificationMessage::clear_has_position() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MoveNotificationMessage::clear_position() {
  if (position_ != NULL) position_->::mosp::Vector3::Clear();
  clear_has_position();
}
inline const ::mosp::Vector3& MoveNotificationMessage::position() const {
  // @@protoc_insertion_point(field_get:mosp.MoveNotificationMessage.position)
  return position_ != NULL ? *position_ : *default_instance_->position_;
}
inline ::mosp::Vector3* MoveNotificationMessage::mutable_position() {
  set_has_position();
  if (position_ == NULL) position_ = new ::mosp::Vector3;
  // @@protoc_insertion_point(field_mutable:mosp.MoveNotificationMessage.position)
  return position_;
}
inline ::mosp::Vector3* MoveNotificationMessage::release_position() {
  clear_has_position();
  ::mosp::Vector3* temp = position_;
  position_ = NULL;
  return temp;
}
inline void MoveNotificationMessage::set_allocated_position(::mosp::Vector3* position) {
  delete position_;
  position_ = position;
  if (position) {
    set_has_position();
  } else {
    clear_has_position();
  }
  // @@protoc_insertion_point(field_set_allocated:mosp.MoveNotificationMessage.position)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace mosp

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::mosp::Type> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::mosp::Type>() {
  return ::mosp::Type_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_messages_2eproto__INCLUDED
