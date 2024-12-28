
(cl:in-package :asdf)

(defsystem "Jongseol-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "init" :depends-on ("_package_init"))
    (:file "_package_init" :depends-on ("_package"))
    (:file "obj" :depends-on ("_package_obj"))
    (:file "_package_obj" :depends-on ("_package"))
    (:file "objs" :depends-on ("_package_objs"))
    (:file "_package_objs" :depends-on ("_package"))
  ))