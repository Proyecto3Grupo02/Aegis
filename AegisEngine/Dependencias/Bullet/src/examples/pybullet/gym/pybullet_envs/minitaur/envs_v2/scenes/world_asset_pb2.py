# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: world_asset.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='world_asset.proto',
  package='robotics.messages',
  syntax='proto3',
  serialized_options=b'\370\001\001',
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n\x11world_asset.proto\x12\x11robotics.messages\":\n\x0cQQuaternionf\x12\t\n\x01x\x18\x01 \x01(\x02\x12\t\n\x01y\x18\x02 \x01(\x02\x12\t\n\x01z\x18\x03 \x01(\x02\x12\t\n\x01w\x18\x04 \x01(\x02\",\n\tVVector3f\x12\t\n\x01x\x18\x01 \x01(\x02\x12\t\n\x01y\x18\x02 \x01(\x02\x12\t\n\x01z\x18\x03 \x01(\x02\"k\n\x06Labels\x12\x33\n\x05label\x18\x01 \x03(\x0b\x32$.robotics.messages.Labels.LabelEntry\x1a,\n\nLabelEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"\xa4\x01\n\x0cGeneralBox3f\x12,\n\x06\x63\x65nter\x18\x01 \x01(\x0b\x32\x1c.robotics.messages.VVector3f\x12\x30\n\ndimensions\x18\x02 \x01(\x0b\x32\x1c.robotics.messages.VVector3f\x12\x34\n\x0borientation\x18\x03 \x01(\x0b\x32\x1f.robotics.messages.QQuaternionf\"m\n\x06Object\x12\n\n\x02id\x18\x01 \x01(\t\x12\r\n\x05label\x18\x02 \x01(\t\x12\x35\n\x0c\x62ounding_box\x18\x03 \x01(\x0b\x32\x1f.robotics.messages.GeneralBox3f\x12\x11\n\tmesh_path\x18\x04 \x01(\t\"9\n\tPolygon3f\x12,\n\x06vertex\x18\x01 \x03(\x0b\x32\x1c.robotics.messages.VVector3f\"\xb2\x01\n\x06Region\x12\n\n\x02id\x18\x01 \x01(\t\x12\r\n\x05label\x18\x02 \x01(\t\x12\x37\n\x0c\x62ounding_box\x18\x03 \x01(\x0b\x32\x1f.robotics.messages.GeneralBox3fH\x00\x12/\n\x07polygon\x18\x05 \x01(\x0b\x32\x1c.robotics.messages.Polygon3fH\x00\x12\x11\n\tmesh_path\x18\x06 \x01(\tB\x10\n\x0espatial_extent\"\xfb\x01\n\nWorldAsset\x12\x30\n\robject_labels\x18\x01 \x01(\x0b\x32\x19.robotics.messages.Labels\x12*\n\x07objects\x18\x02 \x03(\x0b\x32\x19.robotics.messages.Object\x12\x30\n\rregion_labels\x18\x03 \x01(\x0b\x32\x19.robotics.messages.Labels\x12*\n\x07regions\x18\x04 \x03(\x0b\x32\x19.robotics.messages.Region\x12\x11\n\tmesh_path\x18\x05 \x01(\t\x12\x1e\n\x16segmentation_mesh_path\x18\x06 \x01(\tB\x03\xf8\x01\x01\x62\x06proto3'
)




_QQUATERNIONF = _descriptor.Descriptor(
  name='QQuaternionf',
  full_name='robotics.messages.QQuaternionf',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='robotics.messages.QQuaternionf.x', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='y', full_name='robotics.messages.QQuaternionf.y', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='z', full_name='robotics.messages.QQuaternionf.z', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='w', full_name='robotics.messages.QQuaternionf.w', index=3,
      number=4, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=40,
  serialized_end=98,
)


_VVECTOR3F = _descriptor.Descriptor(
  name='VVector3f',
  full_name='robotics.messages.VVector3f',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='robotics.messages.VVector3f.x', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='y', full_name='robotics.messages.VVector3f.y', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='z', full_name='robotics.messages.VVector3f.z', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=100,
  serialized_end=144,
)


_LABELS_LABELENTRY = _descriptor.Descriptor(
  name='LabelEntry',
  full_name='robotics.messages.Labels.LabelEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='robotics.messages.Labels.LabelEntry.key', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='value', full_name='robotics.messages.Labels.LabelEntry.value', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=b'8\001',
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=209,
  serialized_end=253,
)

_LABELS = _descriptor.Descriptor(
  name='Labels',
  full_name='robotics.messages.Labels',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='label', full_name='robotics.messages.Labels.label', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[_LABELS_LABELENTRY, ],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=146,
  serialized_end=253,
)


_GENERALBOX3F = _descriptor.Descriptor(
  name='GeneralBox3f',
  full_name='robotics.messages.GeneralBox3f',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='center', full_name='robotics.messages.GeneralBox3f.center', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='dimensions', full_name='robotics.messages.GeneralBox3f.dimensions', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='orientation', full_name='robotics.messages.GeneralBox3f.orientation', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=256,
  serialized_end=420,
)


_OBJECT = _descriptor.Descriptor(
  name='Object',
  full_name='robotics.messages.Object',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='robotics.messages.Object.id', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='label', full_name='robotics.messages.Object.label', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='bounding_box', full_name='robotics.messages.Object.bounding_box', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='mesh_path', full_name='robotics.messages.Object.mesh_path', index=3,
      number=4, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=422,
  serialized_end=531,
)


_POLYGON3F = _descriptor.Descriptor(
  name='Polygon3f',
  full_name='robotics.messages.Polygon3f',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='vertex', full_name='robotics.messages.Polygon3f.vertex', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=533,
  serialized_end=590,
)


_REGION = _descriptor.Descriptor(
  name='Region',
  full_name='robotics.messages.Region',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='robotics.messages.Region.id', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='label', full_name='robotics.messages.Region.label', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='bounding_box', full_name='robotics.messages.Region.bounding_box', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='polygon', full_name='robotics.messages.Region.polygon', index=3,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='mesh_path', full_name='robotics.messages.Region.mesh_path', index=4,
      number=6, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
    _descriptor.OneofDescriptor(
      name='spatial_extent', full_name='robotics.messages.Region.spatial_extent',
      index=0, containing_type=None,
      create_key=_descriptor._internal_create_key,
    fields=[]),
  ],
  serialized_start=593,
  serialized_end=771,
)


_WORLDASSET = _descriptor.Descriptor(
  name='WorldAsset',
  full_name='robotics.messages.WorldAsset',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='object_labels', full_name='robotics.messages.WorldAsset.object_labels', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='objects', full_name='robotics.messages.WorldAsset.objects', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='region_labels', full_name='robotics.messages.WorldAsset.region_labels', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='regions', full_name='robotics.messages.WorldAsset.regions', index=3,
      number=4, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='mesh_path', full_name='robotics.messages.WorldAsset.mesh_path', index=4,
      number=5, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='segmentation_mesh_path', full_name='robotics.messages.WorldAsset.segmentation_mesh_path', index=5,
      number=6, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=774,
  serialized_end=1025,
)

_LABELS_LABELENTRY.containing_type = _LABELS
_LABELS.fields_by_name['label'].message_type = _LABELS_LABELENTRY
_GENERALBOX3F.fields_by_name['center'].message_type = _VVECTOR3F
_GENERALBOX3F.fields_by_name['dimensions'].message_type = _VVECTOR3F
_GENERALBOX3F.fields_by_name['orientation'].message_type = _QQUATERNIONF
_OBJECT.fields_by_name['bounding_box'].message_type = _GENERALBOX3F
_POLYGON3F.fields_by_name['vertex'].message_type = _VVECTOR3F
_REGION.fields_by_name['bounding_box'].message_type = _GENERALBOX3F
_REGION.fields_by_name['polygon'].message_type = _POLYGON3F
_REGION.oneofs_by_name['spatial_extent'].fields.append(
  _REGION.fields_by_name['bounding_box'])
_REGION.fields_by_name['bounding_box'].containing_oneof = _REGION.oneofs_by_name['spatial_extent']
_REGION.oneofs_by_name['spatial_extent'].fields.append(
  _REGION.fields_by_name['polygon'])
_REGION.fields_by_name['polygon'].containing_oneof = _REGION.oneofs_by_name['spatial_extent']
_WORLDASSET.fields_by_name['object_labels'].message_type = _LABELS
_WORLDASSET.fields_by_name['objects'].message_type = _OBJECT
_WORLDASSET.fields_by_name['region_labels'].message_type = _LABELS
_WORLDASSET.fields_by_name['regions'].message_type = _REGION
DESCRIPTOR.message_types_by_name['QQuaternionf'] = _QQUATERNIONF
DESCRIPTOR.message_types_by_name['VVector3f'] = _VVECTOR3F
DESCRIPTOR.message_types_by_name['Labels'] = _LABELS
DESCRIPTOR.message_types_by_name['GeneralBox3f'] = _GENERALBOX3F
DESCRIPTOR.message_types_by_name['Object'] = _OBJECT
DESCRIPTOR.message_types_by_name['Polygon3f'] = _POLYGON3F
DESCRIPTOR.message_types_by_name['Region'] = _REGION
DESCRIPTOR.message_types_by_name['WorldAsset'] = _WORLDASSET
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

QQuaternionf = _reflection.GeneratedProtocolMessageType('QQuaternionf', (_message.Message,), {
  'DESCRIPTOR' : _QQUATERNIONF,
  '__module__' : 'world_asset_pb2'
  # @@protoc_insertion_point(class_scope:robotics.messages.QQuaternionf)
  })
_sym_db.RegisterMessage(QQuaternionf)

VVector3f = _reflection.GeneratedProtocolMessageType('VVector3f', (_message.Message,), {
  'DESCRIPTOR' : _VVECTOR3F,
  '__module__' : 'world_asset_pb2'
  # @@protoc_insertion_point(class_scope:robotics.messages.VVector3f)
  })
_sym_db.RegisterMessage(VVector3f)

Labels = _reflection.GeneratedProtocolMessageType('Labels', (_message.Message,), {

  'LabelEntry' : _reflection.GeneratedProtocolMessageType('LabelEntry', (_message.Message,), {
    'DESCRIPTOR' : _LABELS_LABELENTRY,
    '__module__' : 'world_asset_pb2'
    # @@protoc_insertion_point(class_scope:robotics.messages.Labels.LabelEntry)
    })
  ,
  'DESCRIPTOR' : _LABELS,
  '__module__' : 'world_asset_pb2'
  # @@protoc_insertion_point(class_scope:robotics.messages.Labels)
  })
_sym_db.RegisterMessage(Labels)
_sym_db.RegisterMessage(Labels.LabelEntry)

GeneralBox3f = _reflection.GeneratedProtocolMessageType('GeneralBox3f', (_message.Message,), {
  'DESCRIPTOR' : _GENERALBOX3F,
  '__module__' : 'world_asset_pb2'
  # @@protoc_insertion_point(class_scope:robotics.messages.GeneralBox3f)
  })
_sym_db.RegisterMessage(GeneralBox3f)

Object = _reflection.GeneratedProtocolMessageType('Object', (_message.Message,), {
  'DESCRIPTOR' : _OBJECT,
  '__module__' : 'world_asset_pb2'
  # @@protoc_insertion_point(class_scope:robotics.messages.Object)
  })
_sym_db.RegisterMessage(Object)

Polygon3f = _reflection.GeneratedProtocolMessageType('Polygon3f', (_message.Message,), {
  'DESCRIPTOR' : _POLYGON3F,
  '__module__' : 'world_asset_pb2'
  # @@protoc_insertion_point(class_scope:robotics.messages.Polygon3f)
  })
_sym_db.RegisterMessage(Polygon3f)

Region = _reflection.GeneratedProtocolMessageType('Region', (_message.Message,), {
  'DESCRIPTOR' : _REGION,
  '__module__' : 'world_asset_pb2'
  # @@protoc_insertion_point(class_scope:robotics.messages.Region)
  })
_sym_db.RegisterMessage(Region)

WorldAsset = _reflection.GeneratedProtocolMessageType('WorldAsset', (_message.Message,), {
  'DESCRIPTOR' : _WORLDASSET,
  '__module__' : 'world_asset_pb2'
  # @@protoc_insertion_point(class_scope:robotics.messages.WorldAsset)
  })
_sym_db.RegisterMessage(WorldAsset)


DESCRIPTOR._options = None
_LABELS_LABELENTRY._options = None
# @@protoc_insertion_point(module_scope)
