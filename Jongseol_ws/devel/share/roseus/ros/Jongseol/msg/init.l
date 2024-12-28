;; Auto-generated. Do not edit!


(when (boundp 'Jongseol::init)
  (if (not (find-package "JONGSEOL"))
    (make-package "JONGSEOL"))
  (shadow 'init (find-package "JONGSEOL")))
(unless (find-package "JONGSEOL::INIT")
  (make-package "JONGSEOL::INIT"))

(in-package "ROS")
;;//! \htmlinclude init.msg.html


(defclass Jongseol::init
  :super ros::object
  :slots (_init ))

(defmethod Jongseol::init
  (:init
   (&key
    ((:init __init) 0)
    )
   (send-super :init)
   (setq _init (round __init))
   self)
  (:init
   (&optional __init)
   (if __init (setq _init __init)) _init)
  (:serialization-length
   ()
   (+
    ;; int32 _init
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _init
       (write-long _init s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _init
     (setq _init (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get Jongseol::init :md5sum-) "7f6ced171af8c7d52168d92bd6d3936e")
(setf (get Jongseol::init :datatype-) "Jongseol/init")
(setf (get Jongseol::init :definition-)
      "int32 init

")



(provide :Jongseol/init "7f6ced171af8c7d52168d92bd6d3936e")


