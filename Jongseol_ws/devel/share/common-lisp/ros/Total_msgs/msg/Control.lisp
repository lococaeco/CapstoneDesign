; Auto-generated. Do not edit!


(cl:in-package Total_msgs-msg)


;//! \htmlinclude Control.msg.html

(cl:defclass <Control> (roslisp-msg-protocol:ros-message)
  ((s16_throttle
    :reader s16_throttle
    :initarg :s16_throttle
    :type cl:fixnum
    :initform 0)
   (s16_steering
    :reader s16_steering
    :initarg :s16_steering
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Control (<Control>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Control>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Control)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name Total_msgs-msg:<Control> is deprecated: use Total_msgs-msg:Control instead.")))

(cl:ensure-generic-function 's16_throttle-val :lambda-list '(m))
(cl:defmethod s16_throttle-val ((m <Control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Total_msgs-msg:s16_throttle-val is deprecated.  Use Total_msgs-msg:s16_throttle instead.")
  (s16_throttle m))

(cl:ensure-generic-function 's16_steering-val :lambda-list '(m))
(cl:defmethod s16_steering-val ((m <Control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Total_msgs-msg:s16_steering-val is deprecated.  Use Total_msgs-msg:s16_steering instead.")
  (s16_steering m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Control>) ostream)
  "Serializes a message object of type '<Control>"
  (cl:let* ((signed (cl:slot-value msg 's16_throttle)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 's16_steering)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Control>) istream)
  "Deserializes a message object of type '<Control>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 's16_throttle) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 's16_steering) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Control>)))
  "Returns string type for a message object of type '<Control>"
  "Total_msgs/Control")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Control)))
  "Returns string type for a message object of type 'Control"
  "Total_msgs/Control")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Control>)))
  "Returns md5sum for a message object of type '<Control>"
  "c8b835278dfb2031fe8ad479c5a2c137")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Control)))
  "Returns md5sum for a message object of type 'Control"
  "c8b835278dfb2031fe8ad479c5a2c137")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Control>)))
  "Returns full string definition for message of type '<Control>"
  (cl:format cl:nil "int16 s16_throttle~%int16 s16_steering~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Control)))
  "Returns full string definition for message of type 'Control"
  (cl:format cl:nil "int16 s16_throttle~%int16 s16_steering~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Control>))
  (cl:+ 0
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Control>))
  "Converts a ROS message object to a list"
  (cl:list 'Control
    (cl:cons ':s16_throttle (s16_throttle msg))
    (cl:cons ':s16_steering (s16_steering msg))
))
