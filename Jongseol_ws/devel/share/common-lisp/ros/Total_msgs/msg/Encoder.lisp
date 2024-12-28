; Auto-generated. Do not edit!


(cl:in-package Total_msgs-msg)


;//! \htmlinclude Encoder.msg.html

(cl:defclass <Encoder> (roslisp-msg-protocol:ros-message)
  ((s16_RightWheelRPM
    :reader s16_RightWheelRPM
    :initarg :s16_RightWheelRPM
    :type cl:fixnum
    :initform 0)
   (s16_LeftWheelRPM
    :reader s16_LeftWheelRPM
    :initarg :s16_LeftWheelRPM
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Encoder (<Encoder>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Encoder>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Encoder)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name Total_msgs-msg:<Encoder> is deprecated: use Total_msgs-msg:Encoder instead.")))

(cl:ensure-generic-function 's16_RightWheelRPM-val :lambda-list '(m))
(cl:defmethod s16_RightWheelRPM-val ((m <Encoder>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Total_msgs-msg:s16_RightWheelRPM-val is deprecated.  Use Total_msgs-msg:s16_RightWheelRPM instead.")
  (s16_RightWheelRPM m))

(cl:ensure-generic-function 's16_LeftWheelRPM-val :lambda-list '(m))
(cl:defmethod s16_LeftWheelRPM-val ((m <Encoder>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Total_msgs-msg:s16_LeftWheelRPM-val is deprecated.  Use Total_msgs-msg:s16_LeftWheelRPM instead.")
  (s16_LeftWheelRPM m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Encoder>) ostream)
  "Serializes a message object of type '<Encoder>"
  (cl:let* ((signed (cl:slot-value msg 's16_RightWheelRPM)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 's16_LeftWheelRPM)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Encoder>) istream)
  "Deserializes a message object of type '<Encoder>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 's16_RightWheelRPM) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 's16_LeftWheelRPM) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Encoder>)))
  "Returns string type for a message object of type '<Encoder>"
  "Total_msgs/Encoder")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Encoder)))
  "Returns string type for a message object of type 'Encoder"
  "Total_msgs/Encoder")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Encoder>)))
  "Returns md5sum for a message object of type '<Encoder>"
  "d59fd6af93a0eea245e13bc69f96d575")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Encoder)))
  "Returns md5sum for a message object of type 'Encoder"
  "d59fd6af93a0eea245e13bc69f96d575")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Encoder>)))
  "Returns full string definition for message of type '<Encoder>"
  (cl:format cl:nil "int16 s16_RightWheelRPM~%int16 s16_LeftWheelRPM~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Encoder)))
  "Returns full string definition for message of type 'Encoder"
  (cl:format cl:nil "int16 s16_RightWheelRPM~%int16 s16_LeftWheelRPM~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Encoder>))
  (cl:+ 0
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Encoder>))
  "Converts a ROS message object to a list"
  (cl:list 'Encoder
    (cl:cons ':s16_RightWheelRPM (s16_RightWheelRPM msg))
    (cl:cons ':s16_LeftWheelRPM (s16_LeftWheelRPM msg))
))
