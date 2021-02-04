# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from test_mapping/Cmd_val.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Cmd_val(genpy.Message):
  _md5sum = "aecdc9e2e94faa677b829fac248e1007"
  _type = "test_mapping/Cmd_val"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """uint16 cmd_L
uint16 cmd_R
bool isControl
"""
  __slots__ = ['cmd_L','cmd_R','isControl']
  _slot_types = ['uint16','uint16','bool']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       cmd_L,cmd_R,isControl

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Cmd_val, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.cmd_L is None:
        self.cmd_L = 0
      if self.cmd_R is None:
        self.cmd_R = 0
      if self.isControl is None:
        self.isControl = False
    else:
      self.cmd_L = 0
      self.cmd_R = 0
      self.isControl = False

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_2HB().pack(_x.cmd_L, _x.cmd_R, _x.isControl))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 5
      (_x.cmd_L, _x.cmd_R, _x.isControl,) = _get_struct_2HB().unpack(str[start:end])
      self.isControl = bool(self.isControl)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_2HB().pack(_x.cmd_L, _x.cmd_R, _x.isControl))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 5
      (_x.cmd_L, _x.cmd_R, _x.isControl,) = _get_struct_2HB().unpack(str[start:end])
      self.isControl = bool(self.isControl)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2HB = None
def _get_struct_2HB():
    global _struct_2HB
    if _struct_2HB is None:
        _struct_2HB = struct.Struct("<2HB")
    return _struct_2HB
