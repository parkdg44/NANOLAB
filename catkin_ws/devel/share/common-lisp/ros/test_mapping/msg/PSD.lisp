; Auto-generated. Do not edit!


(cl:in-package test_mapping-msg)


;//! \htmlinclude PSD.msg.html

(cl:defclass <PSD> (roslisp-msg-protocol:ros-message)
  ((PSD_L
    :reader PSD_L
    :initarg :PSD_L
    :type cl:float
    :initform 0.0)
   (PSD_R
    :reader PSD_R
    :initarg :PSD_R
    :type cl:float
    :initform 0.0))
)

(cl:defclass PSD (<PSD>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PSD>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PSD)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test_mapping-msg:<PSD> is deprecated: use test_mapping-msg:PSD instead.")))

(cl:ensure-generic-function 'PSD_L-val :lambda-list '(m))
(cl:defmethod PSD_L-val ((m <PSD>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_mapping-msg:PSD_L-val is deprecated.  Use test_mapping-msg:PSD_L instead.")
  (PSD_L m))

(cl:ensure-generic-function 'PSD_R-val :lambda-list '(m))
(cl:defmethod PSD_R-val ((m <PSD>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_mapping-msg:PSD_R-val is deprecated.  Use test_mapping-msg:PSD_R instead.")
  (PSD_R m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PSD>) ostream)
  "Serializes a message object of type '<PSD>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'PSD_L))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'PSD_R))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PSD>) istream)
  "Deserializes a message object of type '<PSD>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'PSD_L) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'PSD_R) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PSD>)))
  "Returns string type for a message object of type '<PSD>"
  "test_mapping/PSD")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PSD)))
  "Returns string type for a message object of type 'PSD"
  "test_mapping/PSD")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PSD>)))
  "Returns md5sum for a message object of type '<PSD>"
  "598a8964bc738cc86264f0586f420919")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PSD)))
  "Returns md5sum for a message object of type 'PSD"
  "598a8964bc738cc86264f0586f420919")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PSD>)))
  "Returns full string definition for message of type '<PSD>"
  (cl:format cl:nil "float32 PSD_L~%float32 PSD_R~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PSD)))
  "Returns full string definition for message of type 'PSD"
  (cl:format cl:nil "float32 PSD_L~%float32 PSD_R~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PSD>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PSD>))
  "Converts a ROS message object to a list"
  (cl:list 'PSD
    (cl:cons ':PSD_L (PSD_L msg))
    (cl:cons ':PSD_R (PSD_R msg))
))
