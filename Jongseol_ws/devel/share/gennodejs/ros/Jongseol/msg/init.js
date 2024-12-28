// Auto-generated. Do not edit!

// (in-package Jongseol.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class init {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.init = null;
    }
    else {
      if (initObj.hasOwnProperty('init')) {
        this.init = initObj.init
      }
      else {
        this.init = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type init
    // Serialize message field [init]
    bufferOffset = _serializer.int32(obj.init, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type init
    let len;
    let data = new init(null);
    // Deserialize message field [init]
    data.init = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'Jongseol/init';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7f6ced171af8c7d52168d92bd6d3936e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 init
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new init(null);
    if (msg.init !== undefined) {
      resolved.init = msg.init;
    }
    else {
      resolved.init = 0
    }

    return resolved;
    }
};

module.exports = init;
