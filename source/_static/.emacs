(autoload 'python-mode "python-mode.el" "Python mode." t)
(setq auto-mode-alist (append '(("/*.\.py$" . python-mode)) auto-mode-alist))
(global-unset-key [?\C- ])

;;disable default mark-set. for ibus.
(global-set-key (kbd "C-SPC") nil)
;; doxymacs settings
(require 'doxymacs) 
(setq-default user-mail-address "yeshiwei.math@gmail.com")


;;ecb-settings
(add-to-list 'load-path "/usr/share/emacs/site-lisp/ecb")
(require 'ecb)
(require 'ecb-autoloads)
(setq ecb-auto-activate nil)
(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(ecb-layout-window-sizes nil)
 '(ecb-options-version "2.40"))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 )

(auto-image-file-mode)
;;auctex settings
(load "auctex.el" nil t t)
;;preview-latex settings
(load "preview-latex.el" nil t t)

;;set xelatex as default compile command
(add-hook 'LaTeX-mode-hook (lambda()
			     (setq TeX-auto-save t)
			     (setq TeX-parse-self t)
			     (setq-default TeX-master nil)

			     (add-to-list 'TeX-command-list '("XeLaTeX" "%`xelatex%(mode)%' %t" TeX-run-TeX nil t))
			     (setq TeX-command-default "XeLaTeX")
			     (setq TeX-save-query  nil )
			     (setq TeX-show-compilation t)
			     (setq LaTeX-command-style
				   (quote (("\\`fontspec\\'" "xelatex ")
					   ("" "%(PDF)%(latex) %S%(PDFout)"))))
			     (custom-set-variables
			      '(preview-fast-dvips-command "pdftops -origpagesizes %s.pdf %m/preview.ps"))
			     (setq TeX-output-view-style
				   (cons '("^pdf$" "." "evince  %o ") TeX-output-view-style))
			     (set-default 'preview-default-document-pt 12)
			     (set-default 'preview-scale-function 1.2)
			     (setq preview-required-option-list
				   (quote ("active" "tightpage" "auctex" "pdftex" (preview-preserve-counters "counters"))))
			     (setq preview-default-option-list
				   (quote ("displaymath" "floats" "graphics" "textmath" "showlabels" "sections" )))
			     (TeX-global-PDF-mode t)
			     ))

(defun my-maximized ()
(interactive)
(x-send-client-message
nil 0 nil "_NET_WM_STATE" 32
'(2 "_NET_WM_STATE_MAXIMIZED_HORZ" 0))
(x-send-client-message
nil 0 nil "_NET_WM_STATE" 32
'(2 "_NET_WM_STATE_MAXIMIZED_VERT" 0))
)
(my-maximized)


;;(setq default-frame-alist (append (list 
;;  '(width  . 81)  ; Width set to 81 characters 
;;  '(height . 40)) ; Height set to 60 lines 
;;  default-frame-alist)) 

;;(setq inhibit-startup-message   t)   ; Don't want any startup message 
(setq make-backup-files         nil) ; Don't want any backup files 
(setq auto-save-list-file-name  nil) ; Don't want any .saves files 
(setq auto-save-default         nil) ; Don't want any auto saving 

(setq search-highlight           t) ; Highlight search object 
(setq query-replace-highlight    t) ; Highlight query object 
(setq mouse-sel-retain-highlight t) ; Keep mouse high-lightening 

(set-face-background 'region "yellow") ; Set region background color 

;;to set the cursor color
(set-cursor-color "red")

;;to set foreground color to white
(set-foreground-color "green")

;;to set background color to black
(set-background-color "black")



(global-set-key [f2] 'compile)
;;set the keybinding so that you can use f4 for goto line
(global-set-key [f4] 'goto-line)
;;set the keybinding so that f3 will start the shell
(global-set-key [f3] 'shell)
;;set the keybinding so that f5 will start query replace
(global-set-key [f5] 'query-replace)
(global-set-key [f6] 'switch-to-buffer)
(global-set-key [f7] 'hippie-expand)

;; Replace path below to be where your matlab.el file is.
(add-to-list 'load-path "~/.emacs.d/matlab-emacs/")
;;(require 'matlab-load)
(load-library "matlab-load")

  ;; Enable CEDET feature support for MATLAB code. (Optional)
(matlab-cedet-setup)


;;doxymacs config
(add-hook 'c-mode-common-hook 'doxymacs-mode)
(add-to-list 'load-path "~/.emacs.d/auto-complete/")

;;auto-complete
(require 'auto-complete-config)
(add-to-list 'ac-dictionary-directories "~/.emacs.d/auto-complete/ac-dict")
(ac-config-default)
(auto-complete-mode)

;; set font size
(set-face-attribute 'default nil :height 100)

;;google-c-style
;;(require 'google-c-style)
;;(add-hook 'c-mode-common-hook 'google-set-c-style)
;;(add-hook 'c-mode-common-hook 'google-make-newline-indent)
