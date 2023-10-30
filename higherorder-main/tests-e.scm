;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

(define curry-plus
    (lambda ()
        (lambda (x)
            (lambda (y)
                (+ x y)))))
                
(define curry-plus-four
    (lambda ()
        (lambda (x)
            (lambda (y)
              (lambda (z)
                  (lambda (w)
                    (+ x y z w)))))))

(test-equal "myfilter3" '() (my-filter positive? '()))

(test-assert "exists3-ne" (not (exists (lambda (x) (< x 3)) '())))

(test-equal "find-docs3" '()               (find-docs 'schiller doclist))
