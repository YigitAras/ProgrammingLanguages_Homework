(define (twoOperatorCalculator lst)
	(if (null? lst)
		0
		(if (eqv? '+ (car lst))
			(twoOperatorCalculator (cdr lst))
			(if (eqv? '- (car lst))
				(twoOperatorCalculator (cons (-(cadr lst)) (cddr lst)))
				(+ (car lst)
				(twoOperatorCalculator (cdr lst)))))))
(define (fouroperatorcalculator lst)
	(if (null? (cdr lst))
	lst
		(if (eqv? '/ (cadr lst))
		(fouroperatorcalculator (cons (/ (car lst) (caddr lst)) (cdddr lst)))
			(if (eqv? '* (cadr lst))
			(fouroperatorcalculator (cons (* (car lst) (caddr lst)) (cdddr lst)))
			(cons (car lst) (fouroperatorcalculator (cdr lst)))))))
(define (Nested x)
	(if (pair? x)
	(twooperatorcalculator(fouroperatorcalculator (calculatorNested x)))
	x))
(define (calculatorNested lst)(map Nested lst))
(define (checkoperators lst)
	(if (null? lst)
	#f
	(if (and (number? (car lst)) (null? (cdr lst)))
	#t
	(if (and (pair? (car lst)) (null? (cdr lst)))
	(checkoperators (car lst))
	(if (and (number? (car lst)) (or (eqv? '- (cadr lst)) (eqv? '+ (cadr lst)) (eqv? '/ (cadr lst)) (eqv? '* (cadr lst))))
	(checkoperators (cddr lst))
	(if (and (pair? (car lst))   (or (eqv? '- (cadr lst)) (eqv? '+ (cadr lst)) (eqv? '/ (cadr lst)) (eqv? '* (cadr lst))))
	(and (checkoperators (car lst)) (checkoperators (cddr lst)))
	#f))))))

(define (calculator lst)
	(if (checkoperators lst)
	(twooperatorcalculator (fouroperatorcalculator (calculatornested lst)))
	#f)) 
