; Auto-generated. Do not edit!


(cl:in-package Jongseol-msg)


;//! \htmlinclude init.msg.html

(cl:defclass <init> (roslisp-msg-protocol:ros-message)
  ((init
    :reader init
    :initarg :init
    :type cl:integer
    :initform 0))
)

(cl:defclass init (<init>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <init>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'init)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name Jongseol-msg:<init> is deprecated: use Jongseol-msg:init instead.")))

(cl:ensure-generic-function 'init-val :lambda-list '(m))
(cl:defmethod init-val ((m <init>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Jongseol-msg:init-val is deprecated.  Use Jongseol-msg:init instead.")
  (init m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <init>) ostream)
  "Serializes a message object of type '<init>"
  (cl:let* ((signed (cl:slot-value msg 'init)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <init>) istream)
  "Deserializes a message object of type '<init>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'init) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<init>)))
  "Returns string type for a message object of type '<init>"
  "Jongseol/init")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'init)))
  "Returns string type for a message object of type 'init"
  "Jongseol/init")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<init>)))
  "Returns md5sum for a message object of type '<init>"
  "7f6ced171af8c7d52168d92bd6d3936e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'init)))
  "Returns md5sum for a message object of type 'init"
  "7f6ced171af8c7d52168d92bd6d3936e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<init>)))
  "Returns full string definition for message of type '<init>"
  (cl:format cl:nil "int32 init~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'init)))
  "Returns full string definition for message of type 'init"
  (cl:format cl:nil "int32 init~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <init>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <init>))
  "Converts a ROS message object to a list"
  (cl:list 'init
    (cl:cons ':init (init msg))
))
