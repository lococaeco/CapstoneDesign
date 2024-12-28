;; Auto-generated. Do not edit!


(when (boundp 'Total_msgs::Encoder)
  (if (not (find-package "TOTAL_MSGS"))
    (make-package "TOTAL_MSGS"))
  (shadow 'Encoder (find-package "TOTAL_MSGS")))
(unless (find-package "TOTAL_MSGS::ENCODER")
  (make-package "TOTAL_MSGS::ENCODER"))

(in-package "ROS")
;;//! \htmlinclude Encoder.msg.html


(defclass Total_msgs::Encoder
  :super ros::object
  :slots (_s16_RightWheelRPM _s16_LeftWheelRPM ))

(defmethod Total_msgs::Encoder
  (:init
   (&key
    ((:s16_RightWheelRPM __s16_RightWheelRPM) 0)
    ((:s16_LeftWheelRPM __s16_LeftWheelRPM) 0)
    )
   (send-super :init)
   (setq _s16_RightWheelRPM (round __s16_RightWheelRPM))
   (setq _s16_LeftWheelRPM (round __s16_LeftWheelRPM))
   self)
  (:s16_RightWheelRPM
   (&optional __s16_RightWheelRPM)
   (if __s16_RightWheelRPM (setq _s16_RightWheelRPM __s16_RightWheelRPM)) _s16_RightWheelRPM)
  (:s16_LeftWheelRPM
   (&optional __s16_LeftWheelRPM)
   (if __s16_LeftWheelRPM (setq _s16_LeftWheelRPM __s16_LeftWheelRPM)) _s16_LeftWheelRPM)
  (:serialization-length
   ()
   (+
    ;; int16 _s16_RightWheelRPM
    2
    ;; int16 _s16_LeftWheelRPM
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _s16_RightWheelRPM
       (write-word _s16_RightWheelRPM s)
     ;; int16 _s16_LeftWheelRPM
       (write-word _s16_LeftWheelRPM s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _s16_RightWheelRPM
     (setq _s16_RightWheelRPM (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _s16_LeftWheelRPM
     (setq _s16_LeftWheelRPM (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get Total_msgs::Encoder :md5sum-) "d59fd6af93a0eea245e13bc69f96d575")
(setf (get Total_msgs::Encoder :datatype-) "Total_msgs/Encoder")
(setf (get Total_msgs::Encoder :definition-)
      "int16 s16_RightWheelRPM
int16 s16_LeftWheelRPM

")



(provide :Total_msgs/Encoder "d59fd6af93a0eea245e13bc69f96d575")


