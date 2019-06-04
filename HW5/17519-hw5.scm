(define twoOperatorCalculator (lambda (lst)
    (cond
        ; return a number
        ((= (length lst) 1) (car lst))
        ; if it's + collapse it (5 + 5 + 5) => (10 + 5)
        ((eq? '+ (cadr lst)) (twoOperatorCalculator (cons (+ (car lst) (caddr lst)) (cdddr lst))))
        ; if it's - collapse it (5 - 5 + 5) => (0 + 5)
        ((eq? '- (cadr lst)) (twoOperatorCalculator (cons (- (car lst) (caddr lst)) (cdddr lst))))
        ; it wont fall here anyways but sure return 0
        (else 0))))
;==========================================================================================================
(define fourOperatorCalculator (lambda (lst)
        (cond
            ; need to return a list
            ((= (length lst) 1) lst)
            ; if it is division
            ((eq? '/ (cadr lst)) (fourOperatorCalculator (cons (/ (car lst) (caddr lst)) (cdddr lst))))
            ; if it is multiplication
            ((eq? '* (cadr lst)) (fourOperatorCalculator (cons (* (car lst) (caddr lst)) (cdddr lst))))
            ; else
            (else (cons (car lst) (fourOperatorCalculator (cdr lst)))))))
;==========================================================================================================            
(define Recur_Apply (lambda (elem)
        (if (pair? elem)            
            (twoOperatorCalculator                      ; lastly, apply twooperator
                (fourOperatorCalculator                 ; second, apply fouroperator
                    (calculatorNested elem)))           ; if it is a pair recursively apply nestedcalculator
                                             elem)))    ; if it is not a pair return it as it is
;==========================================================================================================
(define calculatorNested (lambda (lst) (map Recur_Apply lst)))
;==========================================================================================================
(define checkOperators (lambda (lst)
       (cond
            ; if it is empty list wrong
            ((null? lst) #f)
            ; if it is a number only
            ((and (number? (car lst)) (null? (cdr lst))) #t) 
            ; if first elem is number
            ((and (number? (car lst))
                ; rest is not null, second is division operator
                (not (null? (cdr lst))) (eq? '/ (cadr lst)) 
                ; rest of second element is not null , and it is a number 0
                (not (null? (cddr lst))) (eq? 0 (caddr lst))) #f)
            ; if it is just a pair followed by nothing call check on the pair again...
            ((and (pair? (car lst)) (null? (cdr lst))) (checkoperators (car lst)))
            ; number followed by an operator
            ((and (number? (car lst)) (or (eqv? '- (cadr lst)) (eqv? '+ (cadr lst))
                                           (eqv? '* (cadr lst)) (eqv? '/ (cadr lst)))) 
                                                        ; do a check on the trailing part of the list
                                                        ; since it's known not to be empty from above clause
                                                        (checkOperators (cddr lst)))
            ((and (pair? (car lst)) (or (eqv? '- (cadr lst)) (eqv? '+ (cadr lst))
                                        (eqv? '* (cadr lst)) (eqv? '/ (cadr lst))))
                                        ; then do a check on the first and the trailing part
                                        (and (checkOperators (car lst)) (checkOperators (cddr lst))))
            ; else return false anyways
            (else #f))))
                                        
;==========================================================================================================
(define divbyzero (lambda (lst)
    (if (null? lst) #t 
        (if (eqv? '/ (car lst)) 
            (if (and (divbyzero (cdr lst)) 
                     (not (eqv? 0 (twooperatorCalculator
                                    (fourOperatorCalculator
                                        (calculatorNested(cdr lst))))))) 
                                        #t 
                                        #f)
                                        (divbyzero (cdr lst))))))
;==========================================================================================================
(define calculator (lambda (lst)
	(cond
        ((and (checkOperators lst) (divbyzero lst))                   ; check if input is valid and there is no zero divisions not even nested
            (twooperatorCalculator                                    ; apply twooperator at last
                (fouroperatorCalculator                               ; apply fouropeartor after nested calc
                    (calculatorNested lst))))                         ; apply nested first
                    
        (else #f))))                                                  ; means the test not passed return false
;==========================================================================================================


        
        
        
        
        
        
        
        
        
        

