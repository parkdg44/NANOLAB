
(cl:in-package :asdf)

(defsystem "test_mapping-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Cmd_val" :depends-on ("_package_Cmd_val"))
    (:file "_package_Cmd_val" :depends-on ("_package"))
    (:file "PSD" :depends-on ("_package_PSD"))
    (:file "_package_PSD" :depends-on ("_package"))
  ))