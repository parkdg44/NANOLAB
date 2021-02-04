// Auto-generated. Do not edit!

// (in-package test_mapping.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Cmd_val {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.cmd_L = null;
      this.cmd_R = null;
      this.isControl = null;
    }
    else {
      if (initObj.hasOwnProperty('cmd_L')) {
        this.cmd_L = initObj.cmd_L
      }
      else {
        this.cmd_L = 0;
      }
      if (initObj.hasOwnProperty('cmd_R')) {
        this.cmd_R = initObj.cmd_R
      }
      else {
        this.cmd_R = 0;
      }
      if (initObj.hasOwnProperty('isControl')) {
        this.isControl = initObj.isControl
      }
      else {
        this.isControl = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Cmd_val
    // Serialize message field [cmd_L]
    bufferOffset = _serializer.uint16(obj.cmd_L, buffer, bufferOffset);
    // Serialize message field [cmd_R]
    bufferOffset = _serializer.uint16(obj.cmd_R, buffer, bufferOffset);
    // Serialize message field [isControl]
    bufferOffset = _serializer.bool(obj.isControl, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Cmd_val
    let len;
    let data = new Cmd_val(null);
    // Deserialize message field [cmd_L]
    data.cmd_L = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [cmd_R]
    data.cmd_R = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [isControl]
    data.isControl = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'test_mapping/Cmd_val';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'aecdc9e2e94faa677b829fac248e1007';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16 cmd_L
    uint16 cmd_R
    bool isControl
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Cmd_val(null);
    if (msg.cmd_L !== undefined) {
      resolved.cmd_L = msg.cmd_L;
    }
    else {
      resolved.cmd_L = 0
    }

    if (msg.cmd_R !== undefined) {
      resolved.cmd_R = msg.cmd_R;
    }
    else {
      resolved.cmd_R = 0
    }

    if (msg.isControl !== undefined) {
      resolved.isControl = msg.isControl;
    }
    else {
      resolved.isControl = false
    }

    return resolved;
    }
};

module.exports = Cmd_val;
