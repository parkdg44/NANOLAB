;; Auto-generated. Do not edit!


(when (boundp 'test_mapping::PSD)
  (if (not (find-package "TEST_MAPPING"))
    (make-package "TEST_MAPPING"))
  (shadow 'PSD (find-package "TEST_MAPPING")))
(unless (find-package "TEST_MAPPING::PSD")
  (make-package "TEST_MAPPING::PSD"))

(in-package "ROS")
;;//! \htmlinclude PSD.msg.html


(defclass test_mapping::PSD
  :super ros::object
  :slots (_PSD_L _PSD_R ))

(defmethod test_mapping::PSD
  (:init
   (&key
    ((:PSD_L __PSD_L) 0.0)
    ((:PSD_R __PSD_R) 0.0)
    )
   (send-super :init)
   (setq _PSD_L (float __PSD_L))
   (setq _PSD_R (float __PSD_R))
   self)
  (:PSD_L
   (&optional __PSD_L)
   (if __PSD_L (setq _PSD_L __PSD_L)) _PSD_L)
  (:PSD_R
   (&optional __PSD_R)
   (if __PSD_R (setq _PSD_R __PSD_R)) _PSD_R)
  (:serialization-length
   ()
   (+
    ;; float32 _PSD_L
    4
    ;; float32 _PSD_R
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _PSD_L
       (sys::poke _PSD_L (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _PSD_R
       (sys::poke _PSD_R (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _PSD_L
     (setq _PSD_L (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _PSD_R
     (setq _PSD_R (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get test_mapping::PSD :md5sum-) "598a8964bc738cc86264f0586f420919")
(setf (get test_mapping::PSD :datatype-) "test_mapping/PSD")
(setf (get test_mapping::PSD :definition-)
      "float32 PSD_L
float32 PSD_R
")



(provide :test_mapping/PSD "598a8964bc738cc86264f0586f420919")


