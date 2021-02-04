; Auto-generated. Do not edit!


(cl:in-package test_mapping-msg)


;//! \htmlinclude Cmd_val.msg.html

(cl:defclass <Cmd_val> (roslisp-msg-protocol:ros-message)
  ((cmd_L
    :reader cmd_L
    :initarg :cmd_L
    :type cl:fixnum
    :initform 0)
   (cmd_R
    :reader cmd_R
    :initarg :cmd_R
    :type cl:fixnum
    :initform 0)
   (isControl
    :reader isControl
    :initarg :isControl
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Cmd_val (<Cmd_val>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Cmd_val>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Cmd_val)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test_mapping-msg:<Cmd_val> is deprecated: use test_mapping-msg:Cmd_val instead.")))

(cl:ensure-generic-function 'cmd_L-val :lambda-list '(m))
(cl:defmethod cmd_L-val ((m <Cmd_val>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_mapping-msg:cmd_L-val is deprecated.  Use test_mapping-msg:cmd_L instead.")
  (cmd_L m))

(cl:ensure-generic-function 'cmd_R-val :lambda-list '(m))
(cl:defmethod cmd_R-val ((m <Cmd_val>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_mapping-msg:cmd_R-val is deprecated.  Use test_mapping-msg:cmd_R instead.")
  (cmd_R m))

(cl:ensure-generic-function 'isControl-val :lambda-list '(m))
(cl:defmethod isControl-val ((m <Cmd_val>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_mapping-msg:isControl-val is deprecated.  Use test_mapping-msg:isControl instead.")
  (isControl m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Cmd_val>) ostream)
  "Serializes a message object of type '<Cmd_val>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cmd_L)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'cmd_L)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cmd_R)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'cmd_R)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'isControl) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Cmd_val>) istream)
  "Deserializes a message object of type '<Cmd_val>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cmd_L)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'cmd_L)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cmd_R)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'cmd_R)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'isControl) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Cmd_val>)))
  "Returns string type for a message object of type '<Cmd_val>"
  "test_mapping/Cmd_val")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Cmd_val)))
  "Returns string type for a message object of type 'Cmd_val"
  "test_mapping/Cmd_val")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Cmd_val>)))
  "Returns md5sum for a message object of type '<Cmd_val>"
  "aecdc9e2e94faa677b829fac248e1007")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Cmd_val)))
  "Returns md5sum for a message object of type 'Cmd_val"
  "aecdc9e2e94faa677b829fac248e1007")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Cmd_val>)))
  "Returns full string definition for message of type '<Cmd_val>"
  (cl:format cl:nil "uint16 cmd_L~%uint16 cmd_R~%bool isControl~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Cmd_val)))
  "Returns full string definition for message of type 'Cmd_val"
  (cl:format cl:nil "uint16 cmd_L~%uint16 cmd_R~%bool isControl~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Cmd_val>))
  (cl:+ 0
     2
     2
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Cmd_val>))
  "Converts a ROS message object to a list"
  (cl:list 'Cmd_val
    (cl:cons ':cmd_L (cmd_L msg))
    (cl:cons ':cmd_R (cmd_R msg))
    (cl:cons ':isControl (isControl msg))
))
