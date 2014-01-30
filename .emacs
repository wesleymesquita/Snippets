(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(show-paren-mode t))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )

(load-theme 'misterioso)

(load-file "~/.emacs.d/cedet-1.1/common/cedet.el")

 ;; Enable EDE (Project Management) features
(global-ede-mode t)

;;to enable code folding
(global-semantic-tag-folding-mode)

;; Enabling Semantic (code parsing, smart completion) features
;; (select only one)
;;(semantic-load-enable-minimum-features)
;;(semantic-load-enable-code-helpers)
(semantic-load-enable-gaudy-code-helpers)
;;(semantic-load-enable-all-exuberent-ctags-support)

(global-semantic-idle-scheduler-mode 1) ;The idle scheduler with automatically reparse buffers in idle time.
(global-semantic-idle-completions-mode 1) ;Display a tooltip with a list of possible completions near the cursor.
(global-semantic-idle-summary-mode 1) ;Display a tag summary of the lexical token under the cursor.

;;to work with my include files and cedet
(semantic-add-system-include "/usr/include" 'c++-mode)
;;(semantic-add-system-include "~/include" 'c-mode)


;;To use additional features for names completion, and displaying of information for tags & classes,
;; you also need to load the semantic-ia package. This could be performed with following command:
(require 'semantic-ia)

;;to work with systme include files and gcc
(require 'semantic-gcc)


;;integrate semantic with Imenu
(defun my-semantic-hook ()
  (imenu-add-to-menubar "TAGS"))
(add-hook 'semantic-init-hooks 'my-semantic-hook)

;;load Semanticdb
(require 'semanticdb)
;;(global-semanticdb-minor-mode 1)

;;working with tags
;; gnu global support
(require 'semanticdb-global)
(semanticdb-enable-gnu-global-databases 'c-mode)
(semanticdb-enable-gnu-global-databases 'c++-mode)

;; ctags
;;(require 'semanticdb-ectag)
;;(semantic-load-enable-primary-exuberent-ctags-support)

(defun my-semantic-hook ()
  (imenu-add-to-menubar "TAGS"))
(add-hook 'semantic-init-hooks 'my-semantic-hook)

;; select which submodes we want to activate
(mapc (lambda (MODE) (add-to-list 'semantic-default-submodes MODE))
      '(global-semantic-mru-bookmark-mode
        global-semanticdb-minor-mode
        global-semantic-idle-scheduler-mode
        global-semantic-stickyfunc-mode
        global-cedet-m3-minor-mode
        global-semantic-highlight-func-mode
        global-semanticdb-minor-mode))

;; Activate semantic
;;(semantic-mode 1)

;; load contrib library
(require 'eassist)

;; customisation of modes
(mapc
 (lambda (MODE)
   (add-hook MODE
             (lambda ()
               (when (boundp 'semantic-ia-complete-symbol) (add-to-list 'completion-at-point-functions 'semantic-ia-complete-symbol))
               (local-set-key [(control return)] 'semantic-ia-complete-symbol-menu)
               (local-set-key "\C-c?" 'semantic-ia-complete-symbol)
               (local-set-key "\C-c>" 'semantic-complete-analyze-inline)
               (local-set-key "\C-c=" 'semantic-decoration-include-visit)
               (local-set-key "\C-cj" 'semantic-ia-fast-jump)
               (local-set-key "\C-cq" 'semantic-ia-show-doc)
               (local-set-key "\C-cs" 'semantic-ia-show-summary)
               (local-set-key "\C-cp" 'semantic-analyze-proto-impl-toggle)
               ))) '(c-mode-common-hook lisp-mode-hook emacs-lisp-mode-hook))

(add-hook 'c-mode-common-hook (lambda ()
                                (local-set-key "\C-ct" 'eassist-switch-h-cpp)
                                (local-set-key "\C-xt" 'eassist-switch-h-cpp)
                                (local-set-key "\C-ce" 'eassist-list-methods)
                                (local-set-key "\C-c\C-r" 'semantic-symref)))

(semanticdb-enable-gnu-global-databases 'c-mode t)
(semanticdb-enable-gnu-global-databases 'c++-mode t)

(when (cedet-ectag-version-check t)
  (semantic-load-enable-primary-ectags-support))

;; SRecode
(global-srecode-minor-mode 1)

;; EDE
(global-ede-mode 1)
(ede-enable-generic-projects)

(defun qt-cedet-setup ()
  "Set up c-mode and related modes. Includes support for Qt code (signal, slots and alikes)."

  ;; add knowledge of qt to emacs
  (setq qt4-base-dir (concat (getenv "QTDIR") "/include"))
  (semantic-add-system-include (concat qt4-base-dir "/Qt") 'c++-mode)
  (semantic-add-system-include (concat qt4-base-dir "/QtGui") 'c++-mode)
  (semantic-add-system-include (concat qt4-base-dir "/QtCore") 'c++-mode)
  (semantic-add-system-include (concat qt4-base-dir "/QtTest") 'c++-mode)
  (semantic-add-system-include (concat qt4-base-dir "/QtNetwork") 'c++-mode)
  (semantic-add-system-include (concat qt4-base-dir "/QtSvg") 'c++-mode)
  (add-to-list 'auto-mode-alist (cons qt4-base-dir 'c++-mode))
  (add-to-list 'semantic-lex-c-preprocessor-symbol-file (concat qt4-base-dir "/Qt/qconfig.h"))
  (add-to-list 'semantic-lex-c-preprocessor-symbol-file (concat qt4-base-dir "/Qt/qconfig-large.h"))
  (add-to-list 'semantic-lex-c-preprocessor-symbol-file (concat qt4-base-dir "/Qt/qglobal.h"))

  ;; qt keywords and stuff ...
  ;; set up indenting correctly for new qt kewords
  (setq c-protection-key (concat "\\<\\(public\\|public slot\\|protected"
                                 "\\|protected slot\\|private\\|private slot"
                                 "\\)\\>")
        c-C++-access-key (concat "\\<\\(signals\\|public\\|protected\\|private"
                                 "\\|public slots\\|protected slots\\|private slots"
                                 "\\)\\>[ \t]*:"))

  ;; modify the colour of slots to match public, private, etc ...
  (font-lock-add-keywords 'c++-mode '(("\\<\\(slots\\|signals\\)\\>" . font-lock-type-face)))
  ;; make new font for rest of qt keywords
  (make-face 'qt-keywords-face)
  (set-face-foreground 'qt-keywords-face "BlueViolet")
  ;; qt keywords
  (font-lock-add-keywords 'c++-mode '(("\\<Q_[A-Z]*\\>" . 'qt-keywords-face)))
  (font-lock-add-keywords 'c++-mode '(("\\<SIGNAL\\|SLOT\\>" . 'qt-keywords-face)))
  (font-lock-add-keywords 'c++-mode '(("\\<Q[A-Z][A-Za-z]*\\>" . 'qt-keywords-face)))
  (font-lock-add-keywords 'c++-mode '(("\\<Q[A-Z_]+\\>" . 'qt-keywords-face)))
  (font-lock-add-keywords 'c++-mode
                          '(("\\<q\\(Debug\\|Wait\\|Printable\\|Max\\|Min\\|Bound\\)\\>" . 'font-lock-builtin-face)))

  (setq c-macro-names-with-semicolon '("Q_OBJECT" "Q_PROPERTY" "Q_DECLARE" "Q_ENUMS"))
  (c-make-macro-with-semi-re)
  )
(when (getenv "QTDIR") (add-hook 'c-mode-common-hook 'qt-cedet-setup))
