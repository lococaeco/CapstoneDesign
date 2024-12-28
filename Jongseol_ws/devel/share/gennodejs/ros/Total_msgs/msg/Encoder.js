// Auto-generated. Do not edit!

// (in-package Total_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Encoder {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.s16_RightWheelRPM = null;
      this.s16_LeftWheelRPM = null;
    }
    else {
      if (initObj.hasOwnProperty('s16_RightWheelRPM')) {
        this.s16_RightWheelRPM = initObj.s16_RightWheelRPM
      }
      else {
        this.s16_RightWheelRPM = 0;
      }
      if (initObj.hasOwnProperty('s16_LeftWheelRPM')) {
        this.s16_LeftWheelRPM = initObj.s16_LeftWheelRPM
      }
      else {
        this.s16_LeftWheelRPM = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Encoder
    // Serialize message field [s16_RightWheelRPM]
    bufferOffset = _serializer.int16(obj.s16_RightWheelRPM, buffer, bufferOffset);
    // Serialize message field [s16_LeftWheelRPM]
    bufferOffset = _serializer.int16(obj.s16_LeftWheelRPM, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Encoder
    let len;
    let data = new Encoder(null);
    // Deserialize message field [s16_RightWheelRPM]
    data.s16_RightWheelRPM = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [s16_LeftWheelRPM]
    data.s16_LeftWheelRPM = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'Total_msgs/Encoder';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd59fd6af93a0eea245e13bc69f96d575';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 s16_RightWheelRPM
    int16 s16_LeftWheelRPM
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Encoder(null);
    if (msg.s16_RightWheelRPM !== undefined) {
      resolved.s16_RightWheelRPM = msg.s16_RightWheelRPM;
    }
    else {
      resolved.s16_RightWheelRPM = 0
    }

    if (msg.s16_LeftWheelRPM !== undefined) {
      resolved.s16_LeftWheelRPM = msg.s16_LeftWheelRPM;
    }
    else {
      resolved.s16_LeftWheelRPM = 0
    }

    return resolved;
    }
};

module.exports = Encoder;
