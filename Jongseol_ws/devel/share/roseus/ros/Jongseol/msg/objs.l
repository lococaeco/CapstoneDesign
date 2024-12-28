;; Auto-generated. Do not edit!


(when (boundp 'Jongseol::objs)
  (if (not (find-package "JONGSEOL"))
    (make-package "JONGSEOL"))
  (shadow 'objs (find-package "JONGSEOL")))
(unless (find-package "JONGSEOL::OBJS")
  (make-package "JONGSEOL::OBJS"))

(in-package "ROS")
;;//! \htmlinclude objs.msg.html


(defclass Jongseol::objs
  :super ros::object
  :slots (_num _obj ))

(defmethod Jongseol::objs
  (:init
   (&key
    ((:num __num) 0)
    ((:obj __obj) ())
    )
   (send-super :init)
   (setq _num (round __num))
   (setq _obj __obj)
   self)
  (:num
   (&optional __num)
   (if __num (setq _num __num)) _num)
  (:obj
   (&rest __obj)
   (if (keywordp (car __obj))
       (send* _obj __obj)
     (progn
       (if __obj (setq _obj (car __obj)))
       _obj)))
  (:serialization-length
   ()
   (+
    ;; int32 _num
    4
    ;; Jongseol/obj[] _obj
    (apply #'+ (send-all _obj :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _num
       (write-long _num s)
     ;; Jongseol/obj[] _obj
     (write-long (length _obj) s)
     (dolist (elem _obj)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _num
     (setq _num (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; Jongseol/obj[] _obj
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _obj (let (r) (dotimes (i n) (push (instance Jongseol::obj :init) r)) r))
     (dolist (elem- _obj)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get Jongseol::objs :md5sum-) "789bc1e6255eb45d2bff2d818b83b6cb")
(setf (get Jongseol::objs :datatype-) "Jongseol/objs")
(setf (get Jongseol::objs :definition-)
      "int32 num

obj[] obj
================================================================================
MSG: Jongseol/obj
float32 x
float32 y
float32 z

float32 dx
float32 dy
float32 dz
")



(provide :Jongseol/objs "789bc1e6255eb45d2bff2d818b83b6cb")


