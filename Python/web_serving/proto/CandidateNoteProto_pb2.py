# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)



DESCRIPTOR = descriptor.FileDescriptor(
  name='CandidateNoteProto.proto',
  package='',
  serialized_pb='\n\x18\x43\x61ndidateNoteProto.proto\"\xb9\x01\n\x12\x43\x61ndidateNoteProto\x12\x0b\n\x03zid\x18\x01 \x02(\x05\x12\x0f\n\x07network\x18\x02 \x02(\x0c\x12\x12\n\nprofile_id\x18\x03 \x02(\x0c\x12\x14\n\x0c\x63reated_time\x18\x04 \x01(\x03\x12\x15\n\rmodified_time\x18\x05 \x01(\x03\x12\x0c\n\x04name\x18\x06 \x01(\x0c\x12\x0f\n\x07\x63ompany\x18\x07 \x01(\x0c\x12\x14\n\x0cjob_position\x18\x08 \x01(\x0c\x12\x0f\n\x07\x63omment\x18\t \x01(\x0c')




_CANDIDATENOTEPROTO = descriptor.Descriptor(
  name='CandidateNoteProto',
  full_name='CandidateNoteProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='zid', full_name='CandidateNoteProto.zid', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='network', full_name='CandidateNoteProto.network', index=1,
      number=2, type=12, cpp_type=9, label=2,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='profile_id', full_name='CandidateNoteProto.profile_id', index=2,
      number=3, type=12, cpp_type=9, label=2,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='created_time', full_name='CandidateNoteProto.created_time', index=3,
      number=4, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='modified_time', full_name='CandidateNoteProto.modified_time', index=4,
      number=5, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='name', full_name='CandidateNoteProto.name', index=5,
      number=6, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='company', full_name='CandidateNoteProto.company', index=6,
      number=7, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='job_position', full_name='CandidateNoteProto.job_position', index=7,
      number=8, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='comment', full_name='CandidateNoteProto.comment', index=8,
      number=9, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=29,
  serialized_end=214,
)

DESCRIPTOR.message_types_by_name['CandidateNoteProto'] = _CANDIDATENOTEPROTO

class CandidateNoteProto(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _CANDIDATENOTEPROTO
  
  # @@protoc_insertion_point(class_scope:CandidateNoteProto)

# @@protoc_insertion_point(module_scope)
