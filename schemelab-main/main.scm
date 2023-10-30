;; entry           
(define entry
  (lambda (bst)
    (cond
     [(null? bst) #f]
     [(not (= 3 (length bst))) #f]
     [(not (list? (car (cdr bst)))) #f]
     [(not (list? (car (cdr (cdr bst))))) #f]
     (else (car bst)))))

;; left
(define left
  (lambda (bst)
    (cond
     [(null? bst) #f]
     [(not (= 3 (length bst))) #f]
     [(not (list? (car (cdr bst)))) #f]
     [(not (list? (car (cdr (cdr bst))))) #f]
	 (else (car ( cdr bst))))))


;; right
(define right
  (lambda (bst)
    (cond
     [(null? bst) #f]
     [(not (= 3 (length bst))) #f]
     [(not (list? (car (cdr bst)))) #f]
     [(not (list? (car (cdr (cdr bst))))) #f]
	 (else (car ( cdr ( cdr bst)))))))


;; make-bst
(define make-bst
  (lambda (elt left-bst right-bst)
    (cond [(not (integer? elt)) #f]
	  [(and (equal? (entry left-bst) #f) (not (equal? left-bst '()))) #f]
	  [(and (equal? (entry right-bst) #f) (not (equal? right-bst '()))) #f]
	  [else (list elt left-bst right-bst)])))

;;preorder
(define preorder
  (lambda (bst)
    (cond [(equal? (entry bst) #f) '()]
	  [(and (equal? (left bst) #f) (equal? (right bst) #f)) (entry bst)]
	  [(equal? (left bst) #f) (append (list (entry bst)) (preorder (right bst)))]
	  [(equal? (right bst) #f) (append (list (entry bst)) (preorder (left bst)))]
	  [else (append (list (entry bst)) (preorder (left bst)) (preorder (right bst)))])))

;;inorder
(define inorder
  (lambda (bst)
    (cond [(equal? (entry bst) #f) '()]
	  [(equal? (left bst) #f) (append (list (entry bst)) (inorder (right bst)))]
	  [(equal? (right bst) #f) (append (inorder (left bst)) (list (entry bst)))]
	  [else (append (inorder (left bst)) (list (entry bst)) (inorder (right bst)))])))

;;postorder
(define postorder
  (lambda (bst)
    (cond [(equal? (entry bst) #f) '()]
	  [(equal? (left bst) #f) (list '() (inorder (right bst)) (entry bst))]
	  [(equal? (right bst) #f) (list (inorder (left bst)) '() (entry bst))]
	  [else (list (inorder (left bst)) (inorder (right bst)) (entry bst))])))


;;insert
(define insert
  (lambda (v bst)
    (cond [(null? bst) (make-bst v ‘() ‘())]
              [(= v (entry bst)) bst]
	  [(< v (entry bst)) (if (null? (left bst))
				 (make-bst (entry bst) (list v '() '()) (right bst))
				 (insert (v (left bst))))]
	  [(> v (entry bst)) (if (null? (right bst))
				 (make-bst (entry bst) (left bst) (list v '() '()))
				 (insert (v (right bst))))])))