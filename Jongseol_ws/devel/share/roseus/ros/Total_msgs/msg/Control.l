;; Auto-generated. Do not edit!


(when (boundp 'Total_msgs::Control)
  (if (not (find-package "TOTAL_MSGS"))
    (make-package "TOTAL_MSGS"))
  (shadow 'Control (find-package "TOTAL_MSGS")))
(unless (find-package "TOTAL_MSGS::CONTROL")
  (make-package "TOTAL_MSGS::CONTROL"))

(in-package "ROS")
;;//! \htmlinclude Control.msg.html


(defclass Total_msgs::Control
  :super ros::object
  :slots (_s16_throttle _s16_steering ))

(defmethod Total_msgs::Control
  (:init
   (&key
    ((:s16_throttle __s16_throttle) 0)
    ((:s16_steering __s16_steering) 0)
    )
   (send-super :init)
   (setq _s16_throttle (round __s16_throttle))
   (setq _s16_steering (round __s16_steering))
   self)
  (:s16_throttle
   (&optional __s16_throttle)
   (if __s16_throttle (setq _s16_throttle __s16_throttle)) _s16_throttle)
  (:s16_steering
   (&optional __s16_steering)
   (if __s16_steering (setq _s16_steering __s16_steering)) _s16_steering)
  (:serialization-length
   ()
   (+
    ;; int16 _s16_throttle
    2
    ;; int16 _s16_steering
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _s16_throttle
       (write-word _s16_throttle s)
     ;; int16 _s16_steering
       (write-word _s16_steering s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _s16_throttle
     (setq _s16_throttle (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _s16_steering
     (setq _s16_steering (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get Total_msgs::Control :md5sum-) "c8b835278dfb2031fe8ad479c5a2c137")
(setf (get Total_msgs::Control :datatype-) "Total_msgs/Control")
(setf (get Total_msgs::Control :definition-)
      "int16 s16_throttle
int16 s16_steering

")



(provide :Total_msgs/Control "c8b835278dfb2031fe8ad479c5a2c137")


