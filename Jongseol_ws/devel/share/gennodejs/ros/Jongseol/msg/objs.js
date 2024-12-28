// Auto-generated. Do not edit!

// (in-package Jongseol.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let obj = require('./obj.js');

//-----------------------------------------------------------

class objs {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.num = null;
      this.obj = null;
    }
    else {
      if (initObj.hasOwnProperty('num')) {
        this.num = initObj.num
      }
      else {
        this.num = 0;
      }
      if (initObj.hasOwnProperty('obj')) {
        this.obj = initObj.obj
      }
      else {
        this.obj = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type objs
    // Serialize message field [num]
    bufferOffset = _serializer.int32(obj.num, buffer, bufferOffset);
    // Serialize message field [obj]
    // Serialize the length for message field [obj]
    bufferOffset = _serializer.uint32(obj.obj.length, buffer, bufferOffset);
    obj.obj.forEach((val) => {
      bufferOffset = obj.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type objs
    let len;
    let data = new objs(null);
    // Deserialize message field [num]
    data.num = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [obj]
    // Deserialize array length for message field [obj]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.obj = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.obj[i] = obj.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 24 * object.obj.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'Jongseol/objs';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '789bc1e6255eb45d2bff2d818b83b6cb';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 num
    
    obj[] obj
    ================================================================================
    MSG: Jongseol/obj
    float32 x
    float32 y
    float32 z
    
    float32 dx
    float32 dy
    float32 dz
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new objs(null);
    if (msg.num !== undefined) {
      resolved.num = msg.num;
    }
    else {
      resolved.num = 0
    }

    if (msg.obj !== undefined) {
      resolved.obj = new Array(msg.obj.length);
      for (let i = 0; i < resolved.obj.length; ++i) {
        resolved.obj[i] = obj.Resolve(msg.obj[i]);
      }
    }
    else {
      resolved.obj = []
    }

    return resolved;
    }
};

module.exports = objs;
