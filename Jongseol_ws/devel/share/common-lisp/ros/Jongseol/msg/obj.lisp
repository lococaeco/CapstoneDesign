; Auto-generated. Do not edit!


(cl:in-package Jongseol-msg)


;//! \htmlinclude obj.msg.html

(cl:defclass <obj> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (z
    :reader z
    :initarg :z
    :type cl:float
    :initform 0.0)
   (dx
    :reader dx
    :initarg :dx
    :type cl:float
    :initform 0.0)
   (dy
    :reader dy
    :initarg :dy
    :type cl:float
    :initform 0.0)
   (dz
    :reader dz
    :initarg :dz
    :type cl:float
    :initform 0.0))
)

(cl:defclass obj (<obj>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <obj>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'obj)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name Jongseol-msg:<obj> is deprecated: use Jongseol-msg:obj instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Jongseol-msg:x-val is deprecated.  Use Jongseol-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Jongseol-msg:y-val is deprecated.  Use Jongseol-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Jongseol-msg:z-val is deprecated.  Use Jongseol-msg:z instead.")
  (z m))

(cl:ensure-generic-function 'dx-val :lambda-list '(m))
(cl:defmethod dx-val ((m <obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Jongseol-msg:dx-val is deprecated.  Use Jongseol-msg:dx instead.")
  (dx m))

(cl:ensure-generic-function 'dy-val :lambda-list '(m))
(cl:defmethod dy-val ((m <obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Jongseol-msg:dy-val is deprecated.  Use Jongseol-msg:dy instead.")
  (dy m))

(cl:ensure-generic-function 'dz-val :lambda-list '(m))
(cl:defmethod dz-val ((m <obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Jongseol-msg:dz-val is deprecated.  Use Jongseol-msg:dz instead.")
  (dz m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <obj>) ostream)
  "Serializes a message object of type '<obj>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dz))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <obj>) istream)
  "Deserializes a message object of type '<obj>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dy) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dz) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<obj>)))
  "Returns string type for a message object of type '<obj>"
  "Jongseol/obj")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'obj)))
  "Returns string type for a message object of type 'obj"
  "Jongseol/obj")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<obj>)))
  "Returns md5sum for a message object of type '<obj>"
  "7ebdf4fc16c563585927be0d949cdc5a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'obj)))
  "Returns md5sum for a message object of type 'obj"
  "7ebdf4fc16c563585927be0d949cdc5a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<obj>)))
  "Returns full string definition for message of type '<obj>"
  (cl:format cl:nil "float32 x~%float32 y~%float32 z~%~%float32 dx~%float32 dy~%float32 dz~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'obj)))
  "Returns full string definition for message of type 'obj"
  (cl:format cl:nil "float32 x~%float32 y~%float32 z~%~%float32 dx~%float32 dy~%float32 dz~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <obj>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <obj>))
  "Converts a ROS message object to a list"
  (cl:list 'obj
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
    (cl:cons ':dx (dx msg))
    (cl:cons ':dy (dy msg))
    (cl:cons ':dz (dz msg))
))
