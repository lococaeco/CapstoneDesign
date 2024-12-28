; Auto-generated. Do not edit!


(cl:in-package Jongseol-msg)


;//! \htmlinclude objs.msg.html

(cl:defclass <objs> (roslisp-msg-protocol:ros-message)
  ((num
    :reader num
    :initarg :num
    :type cl:integer
    :initform 0)
   (obj
    :reader obj
    :initarg :obj
    :type (cl:vector Jongseol-msg:obj)
   :initform (cl:make-array 0 :element-type 'Jongseol-msg:obj :initial-element (cl:make-instance 'Jongseol-msg:obj))))
)

(cl:defclass objs (<objs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <objs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'objs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name Jongseol-msg:<objs> is deprecated: use Jongseol-msg:objs instead.")))

(cl:ensure-generic-function 'num-val :lambda-list '(m))
(cl:defmethod num-val ((m <objs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Jongseol-msg:num-val is deprecated.  Use Jongseol-msg:num instead.")
  (num m))

(cl:ensure-generic-function 'obj-val :lambda-list '(m))
(cl:defmethod obj-val ((m <objs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Jongseol-msg:obj-val is deprecated.  Use Jongseol-msg:obj instead.")
  (obj m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <objs>) ostream)
  "Serializes a message object of type '<objs>"
  (cl:let* ((signed (cl:slot-value msg 'num)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'obj))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'obj))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <objs>) istream)
  "Deserializes a message object of type '<objs>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'num) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'obj) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'obj)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'Jongseol-msg:obj))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<objs>)))
  "Returns string type for a message object of type '<objs>"
  "Jongseol/objs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'objs)))
  "Returns string type for a message object of type 'objs"
  "Jongseol/objs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<objs>)))
  "Returns md5sum for a message object of type '<objs>"
  "789bc1e6255eb45d2bff2d818b83b6cb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'objs)))
  "Returns md5sum for a message object of type 'objs"
  "789bc1e6255eb45d2bff2d818b83b6cb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<objs>)))
  "Returns full string definition for message of type '<objs>"
  (cl:format cl:nil "int32 num~%~%obj[] obj~%================================================================================~%MSG: Jongseol/obj~%float32 x~%float32 y~%float32 z~%~%float32 dx~%float32 dy~%float32 dz~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'objs)))
  "Returns full string definition for message of type 'objs"
  (cl:format cl:nil "int32 num~%~%obj[] obj~%================================================================================~%MSG: Jongseol/obj~%float32 x~%float32 y~%float32 z~%~%float32 dx~%float32 dy~%float32 dz~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <objs>))
  (cl:+ 0
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'obj) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <objs>))
  "Converts a ROS message object to a list"
  (cl:list 'objs
    (cl:cons ':num (num msg))
    (cl:cons ':obj (obj msg))
))
