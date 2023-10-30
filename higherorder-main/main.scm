(use-modules (rnrs))

;;currying
(define curry3
  (lambda (f)
    (lambda(x)
      (lambda(y)
	(lambda(z)
	  (f x y z))))))

;;uncurrying
(define uncurry3
  (lambda (f)
      (lambda (x y z)
	(((f x) y) z))))

;; my-filter
(define my-filter
  (lambda (f lst)
    (if (null? lst) lst
      (if (f (car lst))
        (cons (car lst) (my-filter f (cdr lst)))
        (my-filter f (cdr lst))))))

;; exists
(define exists
   (lambda (f lst)
     (if (null? lst) #f
       (if (null? (my-filter f lst)) #f  #t))))

;; doclist
(define doclist '((cs (Welcome to the Carleton CS department))
                  (art (The department consists of two separate majors))
                  (geology (The geology department retains a spirit of exploration))
                  (president (Alison R Byerly is Carleton College’s 12th president))))
    
;; find-docs
;(define find-docs
;  (lambda (target lst)
;    (fold-right cons '()
;		(map (lambda doc
;		     (cond ((member target (car (cdr (car doc))))
;			    (car (car doc)))
;		           (else #f))) lst))))

;; find-docs
(define find-docs
  (lambda (target lst)
    (filter (lambda (empty) (not(equal? empty #f)))
    (fold-right cons '()
		(map (lambda doc
		     (cond ((member target (car (cdr (car doc))))
			    (car (car doc)))
		           (else #f))) lst)))))

(define plus1 (lambda (x) (+ x 1)))

;; flat-map
(define flat-map
  (lambda (f lst)
    [fold-right cons '() (f car lst)]))
