(define twoOperatorCalculator (lambda (lst)
	(if (= (length lst) 1)  (car lst) ; need to return a number
        (if (eq? '+ (cadr lst)) 
            (twoOperatorCalculator (cons (+ (car lst) (caddr lst)) (cdddr lst))) ; if (5 + 5 - 4 => (10 - 4)
            (if (eq? '- (cadr lst))
            (twoOperatorCalculator (cons (- (car lst) (caddr lst)) (cdddr lst)))  0))))) ; if (5 - 5 - 4) => (0 - 4)
            ; collapse the a + b or a - b type of triplets into 1 element recursively

(define fourOperatorCalculator (lambda (lst)
	(if (= (length lst) 1) lst ; need to return a list
		(if (eq? '/ (cadr lst))
            (fourOperatorCalculator (cons (/ (car lst) (caddr lst)) (cdddr lst)))
			(if (eq? '* (cadr lst))
            (fourOperatorCalculator (cons (* (car lst) (caddr lst)) (cdddr lst)))
            ; different from twooperatorCalculator is that we should return a list
            ; so go ahead and build the list without / or * below 
            (cons (car lst) (fourOperatorCalculator (cdr lst))))))))
            
(define Recur_Apply (lambda (elem)
        (if (pair? elem)            
            (twoOperatorCalculator                      ; lastly, two operator
                (fourOperatorCalculator                 ; second, four operator
                    (calculatorNested elem)))           ; if it is a pair recursively apply nestedcalculator
                                             elem)))    ; if it is not a pair return it as it is

(define calculatorNested (lambda (lst) (map Recur_Apply lst)))

(define checkOperators (lambda (lst)
        ;if the list is null
        (if (null? lst) #f  
            ; if the list is just a number followed by empty a.k.a just a number
            (if (and (number? (car lst)) (null? (cdr lst)))  #t
                    ;if it is a number followed by an operator then a list
                    (if (and (number? (car lst)) (or (eqv? '- (cadr lst))
                                                     (eqv? '+ (cadr lst))
                                                     (eqv? '/ (cadr lst)) ;check the operators of the rest of the list
                                                     (eqv? '* (cadr lst)))) (checkOperators (cddr lst))
                        ;if it is a pair followed by an operator then a list
                        (if (and (pair? (car lst)) (or (eqv? '- (cadr lst))
                                                     (eqv? '+ (cadr lst))
                                                     (eqv? '/ (cadr lst)) ;check the operators of the rest of the list
                                                     (eqv? '* (cadr lst))))
                            ; check the first item and the remaining list after operator recursively
                            (and (checkOperators (car lst)) (checkOperators (cddr lst)))
                            ; return false if it does not fall into any other category
                            #f))))))
                        
(define calculator (lambda (lst)
        ; check the validity first
        (if (checkOperators lst)
            ; if it is in true form return the result
            (twoOperatorCalculator(fourOperatorCalculator(calculatorNested lst))) 
            ; else return false
            #f)))
                                                                                    
                                                                                    


