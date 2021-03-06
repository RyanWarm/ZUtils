# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)



DESCRIPTOR = descriptor.FileDescriptor(
  name='WeiboProfile.proto',
  package='weiboprofile',
  serialized_pb='\n\x12WeiboProfile.proto\x12\x0cweiboprofile\"\xf4\x07\n\x0cWeiboProfile\x12\x0b\n\x03uid\x18\x01 \x02(\x03\x12>\n\rpersonal_info\x18\x02 \x01(\x0b\x32\'.weiboprofile.WeiboProfile.PersonalInfo\x12\x34\n\x08his_data\x18\x03 \x01(\x0b\x32\".weiboprofile.WeiboProfile.HisData\x12G\n\x12lite_personal_info\x18\x04 \x01(\x0b\x32+.weiboprofile.WeiboProfile.LitePersonalInfo\x12\r\n\x05medal\x18\x05 \x03(\x0c\x12\x0b\n\x03tag\x18\x06 \x03(\x0c\x12\x0c\n\x04\x66tag\x18\x07 \x03(\x0c\x12\x10\n\x08headline\x18\x08 \x01(\x0c\x12\x15\n\rguess_company\x18\t \x01(\x0c\x1a\xb8\x01\n\x0cPersonalInfo\x12\x0b\n\x03img\x18\x02 \x01(\x0c\x12\x0c\n\x04name\x18\x03 \x01(\x0c\x12\r\n\x05\x64\x61ren\x18\x04 \x01(\x08\x12\x0e\n\x06\x62lue_v\x18\x05 \x01(\x08\x12\x10\n\x08yellow_v\x18\x06 \x01(\x08\x12\r\n\x05level\x18\x07 \x01(\x05\x12\x0b\n\x03url\x18\x08 \x01(\x0c\x12\x0e\n\x06gender\x18\t \x01(\x08\x12\x10\n\x08location\x18\n \x01(\x0c\x12\r\n\x05words\x18\x0b \x01(\x0c\x12\x0f\n\x07gender2\x18\x0c \x01(\x05\x1a\xfa\x02\n\x07HisData\x12\x38\n\x02\x62i\x18\x01 \x01(\x0b\x32,.weiboprofile.WeiboProfile.HisData.BasicInfo\x12\x39\n\x03\x65\x64u\x18\x02 \x03(\x0b\x32,.weiboprofile.WeiboProfile.HisData.Education\x12\x37\n\x03\x63om\x18\x03 \x03(\x0b\x32*.weiboprofile.WeiboProfile.HisData.Company\x1a,\n\tBasicInfo\x12\x10\n\x08\x62irthday\x18\x01 \x01(\x0c\x12\r\n\x05\x65mail\x18\x02 \x01(\x0c\x1a\x36\n\tEducation\x12\x0c\n\x04name\x18\x01 \x02(\x0c\x12\x0c\n\x04year\x18\x02 \x01(\x05\x12\r\n\x05major\x18\x03 \x01(\x0c\x1a[\n\x07\x43ompany\x12\x0c\n\x04name\x18\x01 \x02(\x0c\x12\x0e\n\x06year_s\x18\x02 \x01(\x05\x12\x0e\n\x06year_e\x18\x03 \x01(\x05\x12\x10\n\x08position\x18\x04 \x01(\x0c\x12\x10\n\x08location\x18\x05 \x01(\x0c\x1a\x8c\x01\n\x10LitePersonalInfo\x12\x13\n\x0b\x64\x61ren_title\x18\x01 \x01(\x0c\x12\x10\n\x08interest\x18\x02 \x01(\x0c\x12\r\n\x05jifen\x18\x03 \x01(\x05\x12\x14\n\x0cverify_title\x18\x04 \x01(\x0c\x12\x0e\n\x06\x66ollow\x18\x05 \x01(\x05\x12\x0c\n\x04\x66\x61ns\x18\x06 \x01(\x05\x12\x0e\n\x06tweets\x18\x07 \x01(\x05')




_WEIBOPROFILE_PERSONALINFO = descriptor.Descriptor(
  name='PersonalInfo',
  full_name='weiboprofile.WeiboProfile.PersonalInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='img', full_name='weiboprofile.WeiboProfile.PersonalInfo.img', index=0,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='name', full_name='weiboprofile.WeiboProfile.PersonalInfo.name', index=1,
      number=3, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='daren', full_name='weiboprofile.WeiboProfile.PersonalInfo.daren', index=2,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='blue_v', full_name='weiboprofile.WeiboProfile.PersonalInfo.blue_v', index=3,
      number=5, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='yellow_v', full_name='weiboprofile.WeiboProfile.PersonalInfo.yellow_v', index=4,
      number=6, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='level', full_name='weiboprofile.WeiboProfile.PersonalInfo.level', index=5,
      number=7, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='url', full_name='weiboprofile.WeiboProfile.PersonalInfo.url', index=6,
      number=8, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='gender', full_name='weiboprofile.WeiboProfile.PersonalInfo.gender', index=7,
      number=9, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='location', full_name='weiboprofile.WeiboProfile.PersonalInfo.location', index=8,
      number=10, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='words', full_name='weiboprofile.WeiboProfile.PersonalInfo.words', index=9,
      number=11, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='gender2', full_name='weiboprofile.WeiboProfile.PersonalInfo.gender2', index=10,
      number=12, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
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
  serialized_start=341,
  serialized_end=525,
)

_WEIBOPROFILE_HISDATA_BASICINFO = descriptor.Descriptor(
  name='BasicInfo',
  full_name='weiboprofile.WeiboProfile.HisData.BasicInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='birthday', full_name='weiboprofile.WeiboProfile.HisData.BasicInfo.birthday', index=0,
      number=1, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='email', full_name='weiboprofile.WeiboProfile.HisData.BasicInfo.email', index=1,
      number=2, type=12, cpp_type=9, label=1,
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
  serialized_start=713,
  serialized_end=757,
)

_WEIBOPROFILE_HISDATA_EDUCATION = descriptor.Descriptor(
  name='Education',
  full_name='weiboprofile.WeiboProfile.HisData.Education',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='name', full_name='weiboprofile.WeiboProfile.HisData.Education.name', index=0,
      number=1, type=12, cpp_type=9, label=2,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='year', full_name='weiboprofile.WeiboProfile.HisData.Education.year', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='major', full_name='weiboprofile.WeiboProfile.HisData.Education.major', index=2,
      number=3, type=12, cpp_type=9, label=1,
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
  serialized_start=759,
  serialized_end=813,
)

_WEIBOPROFILE_HISDATA_COMPANY = descriptor.Descriptor(
  name='Company',
  full_name='weiboprofile.WeiboProfile.HisData.Company',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='name', full_name='weiboprofile.WeiboProfile.HisData.Company.name', index=0,
      number=1, type=12, cpp_type=9, label=2,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='year_s', full_name='weiboprofile.WeiboProfile.HisData.Company.year_s', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='year_e', full_name='weiboprofile.WeiboProfile.HisData.Company.year_e', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='position', full_name='weiboprofile.WeiboProfile.HisData.Company.position', index=3,
      number=4, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='location', full_name='weiboprofile.WeiboProfile.HisData.Company.location', index=4,
      number=5, type=12, cpp_type=9, label=1,
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
  serialized_start=815,
  serialized_end=906,
)

_WEIBOPROFILE_HISDATA = descriptor.Descriptor(
  name='HisData',
  full_name='weiboprofile.WeiboProfile.HisData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='bi', full_name='weiboprofile.WeiboProfile.HisData.bi', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='edu', full_name='weiboprofile.WeiboProfile.HisData.edu', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='com', full_name='weiboprofile.WeiboProfile.HisData.com', index=2,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_WEIBOPROFILE_HISDATA_BASICINFO, _WEIBOPROFILE_HISDATA_EDUCATION, _WEIBOPROFILE_HISDATA_COMPANY, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=528,
  serialized_end=906,
)

_WEIBOPROFILE_LITEPERSONALINFO = descriptor.Descriptor(
  name='LitePersonalInfo',
  full_name='weiboprofile.WeiboProfile.LitePersonalInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='daren_title', full_name='weiboprofile.WeiboProfile.LitePersonalInfo.daren_title', index=0,
      number=1, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='interest', full_name='weiboprofile.WeiboProfile.LitePersonalInfo.interest', index=1,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='jifen', full_name='weiboprofile.WeiboProfile.LitePersonalInfo.jifen', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='verify_title', full_name='weiboprofile.WeiboProfile.LitePersonalInfo.verify_title', index=3,
      number=4, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='follow', full_name='weiboprofile.WeiboProfile.LitePersonalInfo.follow', index=4,
      number=5, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='fans', full_name='weiboprofile.WeiboProfile.LitePersonalInfo.fans', index=5,
      number=6, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='tweets', full_name='weiboprofile.WeiboProfile.LitePersonalInfo.tweets', index=6,
      number=7, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
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
  serialized_start=909,
  serialized_end=1049,
)

_WEIBOPROFILE = descriptor.Descriptor(
  name='WeiboProfile',
  full_name='weiboprofile.WeiboProfile',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='uid', full_name='weiboprofile.WeiboProfile.uid', index=0,
      number=1, type=3, cpp_type=2, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='personal_info', full_name='weiboprofile.WeiboProfile.personal_info', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='his_data', full_name='weiboprofile.WeiboProfile.his_data', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='lite_personal_info', full_name='weiboprofile.WeiboProfile.lite_personal_info', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='medal', full_name='weiboprofile.WeiboProfile.medal', index=4,
      number=5, type=12, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='tag', full_name='weiboprofile.WeiboProfile.tag', index=5,
      number=6, type=12, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='ftag', full_name='weiboprofile.WeiboProfile.ftag', index=6,
      number=7, type=12, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='headline', full_name='weiboprofile.WeiboProfile.headline', index=7,
      number=8, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='guess_company', full_name='weiboprofile.WeiboProfile.guess_company', index=8,
      number=9, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_WEIBOPROFILE_PERSONALINFO, _WEIBOPROFILE_HISDATA, _WEIBOPROFILE_LITEPERSONALINFO, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=37,
  serialized_end=1049,
)

_WEIBOPROFILE_PERSONALINFO.containing_type = _WEIBOPROFILE;
_WEIBOPROFILE_HISDATA_BASICINFO.containing_type = _WEIBOPROFILE_HISDATA;
_WEIBOPROFILE_HISDATA_EDUCATION.containing_type = _WEIBOPROFILE_HISDATA;
_WEIBOPROFILE_HISDATA_COMPANY.containing_type = _WEIBOPROFILE_HISDATA;
_WEIBOPROFILE_HISDATA.fields_by_name['bi'].message_type = _WEIBOPROFILE_HISDATA_BASICINFO
_WEIBOPROFILE_HISDATA.fields_by_name['edu'].message_type = _WEIBOPROFILE_HISDATA_EDUCATION
_WEIBOPROFILE_HISDATA.fields_by_name['com'].message_type = _WEIBOPROFILE_HISDATA_COMPANY
_WEIBOPROFILE_HISDATA.containing_type = _WEIBOPROFILE;
_WEIBOPROFILE_LITEPERSONALINFO.containing_type = _WEIBOPROFILE;
_WEIBOPROFILE.fields_by_name['personal_info'].message_type = _WEIBOPROFILE_PERSONALINFO
_WEIBOPROFILE.fields_by_name['his_data'].message_type = _WEIBOPROFILE_HISDATA
_WEIBOPROFILE.fields_by_name['lite_personal_info'].message_type = _WEIBOPROFILE_LITEPERSONALINFO
DESCRIPTOR.message_types_by_name['WeiboProfile'] = _WEIBOPROFILE

class WeiboProfile(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  
  class PersonalInfo(message.Message):
    __metaclass__ = reflection.GeneratedProtocolMessageType
    DESCRIPTOR = _WEIBOPROFILE_PERSONALINFO
    
    # @@protoc_insertion_point(class_scope:weiboprofile.WeiboProfile.PersonalInfo)
  
  class HisData(message.Message):
    __metaclass__ = reflection.GeneratedProtocolMessageType
    
    class BasicInfo(message.Message):
      __metaclass__ = reflection.GeneratedProtocolMessageType
      DESCRIPTOR = _WEIBOPROFILE_HISDATA_BASICINFO
      
      # @@protoc_insertion_point(class_scope:weiboprofile.WeiboProfile.HisData.BasicInfo)
    
    class Education(message.Message):
      __metaclass__ = reflection.GeneratedProtocolMessageType
      DESCRIPTOR = _WEIBOPROFILE_HISDATA_EDUCATION
      
      # @@protoc_insertion_point(class_scope:weiboprofile.WeiboProfile.HisData.Education)
    
    class Company(message.Message):
      __metaclass__ = reflection.GeneratedProtocolMessageType
      DESCRIPTOR = _WEIBOPROFILE_HISDATA_COMPANY
      
      # @@protoc_insertion_point(class_scope:weiboprofile.WeiboProfile.HisData.Company)
    DESCRIPTOR = _WEIBOPROFILE_HISDATA
    
    # @@protoc_insertion_point(class_scope:weiboprofile.WeiboProfile.HisData)
  
  class LitePersonalInfo(message.Message):
    __metaclass__ = reflection.GeneratedProtocolMessageType
    DESCRIPTOR = _WEIBOPROFILE_LITEPERSONALINFO
    
    # @@protoc_insertion_point(class_scope:weiboprofile.WeiboProfile.LitePersonalInfo)
  DESCRIPTOR = _WEIBOPROFILE
  
  # @@protoc_insertion_point(class_scope:weiboprofile.WeiboProfile)

# @@protoc_insertion_point(module_scope)
