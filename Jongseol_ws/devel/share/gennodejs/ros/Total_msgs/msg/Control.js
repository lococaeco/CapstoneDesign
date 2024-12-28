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

class Control {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.s16_throttle = null;
      this.s16_steering = null;
    }
    else {
      if (initObj.hasOwnProperty('s16_throttle')) {
        this.s16_throttle = initObj.s16_throttle
      }
      else {
        this.s16_throttle = 0;
      }
      if (initObj.hasOwnProperty('s16_steering')) {
        this.s16_steering = initObj.s16_steering
      }
      else {
        this.s16_steering = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Control
    // Serialize message field [s16_throttle]
    bufferOffset = _serializer.int16(obj.s16_throttle, buffer, bufferOffset);
    // Serialize message field [s16_steering]
    bufferOffset = _serializer.int16(obj.s16_steering, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Control
    let len;
    let data = new Control(null);
    // Deserialize message field [s16_throttle]
    data.s16_throttle = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [s16_steering]
    data.s16_steering = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'Total_msgs/Control';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c8b835278dfb2031fe8ad479c5a2c137';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 s16_throttle
    int16 s16_steering
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Control(null);
    if (msg.s16_throttle !== undefined) {
      resolved.s16_throttle = msg.s16_throttle;
    }
    else {
      resolved.s16_throttle = 0
    }

    if (msg.s16_steering !== undefined) {
      resolved.s16_steering = msg.s16_steering;
    }
    else {
      resolved.s16_steering = 0
    }

    return resolved;
    }
};

module.exports = Control;
