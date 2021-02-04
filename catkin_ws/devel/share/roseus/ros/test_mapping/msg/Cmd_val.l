;; Auto-generated. Do not edit!


(when (boundp 'test_mapping::Cmd_val)
  (if (not (find-package "TEST_MAPPING"))
    (make-package "TEST_MAPPING"))
  (shadow 'Cmd_val (find-package "TEST_MAPPING")))
(unless (find-package "TEST_MAPPING::CMD_VAL")
  (make-package "TEST_MAPPING::CMD_VAL"))

(in-package "ROS")
;;//! \htmlinclude Cmd_val.msg.html


(defclass test_mapping::Cmd_val
  :super ros::object
  :slots (_cmd_L _cmd_R _isControl ))

(defmethod test_mapping::Cmd_val
  (:init
   (&key
    ((:cmd_L __cmd_L) 0)
    ((:cmd_R __cmd_R) 0)
    ((:isControl __isControl) nil)
    )
   (send-super :init)
   (setq _cmd_L (round __cmd_L))
   (setq _cmd_R (round __cmd_R))
   (setq _isControl __isControl)
   self)
  (:cmd_L
   (&optional __cmd_L)
   (if __cmd_L (setq _cmd_L __cmd_L)) _cmd_L)
  (:cmd_R
   (&optional __cmd_R)
   (if __cmd_R (setq _cmd_R __cmd_R)) _cmd_R)
  (:isControl
   (&optional __isControl)
   (if __isControl (setq _isControl __isControl)) _isControl)
  (:serialization-length
   ()
   (+
    ;; uint16 _cmd_L
    2
    ;; uint16 _cmd_R
    2
    ;; bool _isControl
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _cmd_L
       (write-word _cmd_L s)
     ;; uint16 _cmd_R
       (write-word _cmd_R s)
     ;; bool _isControl
       (if _isControl (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _cmd_L
     (setq _cmd_L (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _cmd_R
     (setq _cmd_R (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; bool _isControl
     (setq _isControl (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get test_mapping::Cmd_val :md5sum-) "aecdc9e2e94faa677b829fac248e1007")
(setf (get test_mapping::Cmd_val :datatype-) "test_mapping/Cmd_val")
(setf (get test_mapping::Cmd_val :definition-)
      "uint16 cmd_L
uint16 cmd_R
bool isControl

")



(provide :test_mapping/Cmd_val "aecdc9e2e94faa677b829fac248e1007")


