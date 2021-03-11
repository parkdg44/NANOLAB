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

class PSD {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.PSD_L = null;
      this.PSD_R = null;
    }
    else {
      if (initObj.hasOwnProperty('PSD_L')) {
        this.PSD_L = initObj.PSD_L
      }
      else {
        this.PSD_L = 0.0;
      }
      if (initObj.hasOwnProperty('PSD_R')) {
        this.PSD_R = initObj.PSD_R
      }
      else {
        this.PSD_R = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PSD
    // Serialize message field [PSD_L]
    bufferOffset = _serializer.float32(obj.PSD_L, buffer, bufferOffset);
    // Serialize message field [PSD_R]
    bufferOffset = _serializer.float32(obj.PSD_R, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PSD
    let len;
    let data = new PSD(null);
    // Deserialize message field [PSD_L]
    data.PSD_L = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [PSD_R]
    data.PSD_R = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'test_mapping/PSD';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '598a8964bc738cc86264f0586f420919';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 PSD_L
    float32 PSD_R
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PSD(null);
    if (msg.PSD_L !== undefined) {
      resolved.PSD_L = msg.PSD_L;
    }
    else {
      resolved.PSD_L = 0.0
    }

    if (msg.PSD_R !== undefined) {
      resolved.PSD_R = msg.PSD_R;
    }
    else {
      resolved.PSD_R = 0.0
    }

    return resolved;
    }
};

module.exports = PSD;
