(define get-operator (lambda (op-symbol) 
  (cond 
    ((equal? op-symbol '+) +)
    ((equal? op-symbol '-) -)
    ((equal? op-symbol '*) *)
    ((equal? op-symbol '/) /)
    (else (error "cs305-interpreter operator not implemented -->" op-symbol)))))
    

(define formal-list? (lambda (e)
    ;; <formal-list> ==> IDENT <formal-list> | IDENT 
    ;;  first check if its a symbol in a list
    (and (list? e) (symbol? (car e)) 
            ;; check if the trailing list is null or another formal list
            (or (null? (cdr e)) (formal-list? (cdr e))))))

;; var list check
(define var-list? (lambda (e)
    (and (list? e) (list? (car e)) (= (length (car e)) 2) (symbol? (caar e))
            (or (null? (cdr e)) (var-list? (cdr e))))))
            
(define if-stmt? (lambda (e)
    ;; <if_stmt> ==> ( <if> <expr> <expr> <expr> )
    (and ;;  if statement has to have an "if" followed by 3 expressions 
        (list? e) (equal? (car e) 'if) (= (length e) 4))))

(define define-stmt? (lambda (e)
    ;; An expression is a define statement
    ;; if it is a list, and the first element
    ;; is define, the second element is a symbol,
    ;; and the third element is an expression.
    (and (list? e) (equal? (car e) 'define) (symbol? (cadr e)) (= (length e) 3))))
        
(define lambda-stmt? (lambda (e)
    ;; Sanity check to see if it is a list
    (and (list? e) 
        ;; <lambda> ==> lambda (<formal-list>) <expr>
        ;; do this check below
        (equal? (car e) 'lambda) (formal-list? (cadr e))
                    ;; Just in case check to make sure its not define
                    (not (define-stmt? (caddr e))))))

(define letstar-stmt? (lambda (e)
    ;; Santiy check to see if it is a list
    (and (list? e) 
            ;; <letstar> ==> let* (<var-binding-list>) <expr>
            ;; i.e. let* followed by 2 items
            (equal? (car e) 'let*) (= (length e) 3))))

(define let-stmt? (lambda (e)
    ;; Sanity check to see if it is a list 
    (and (list? e) 
            ;; <let> ==> (let (<var-binding-list>) <expr>
            ;; i.e. let followed by 2 items
            (equal? (car e) 'let) (var-list? (cadr e)) (= (length e) 3))))
            
(define built-in-op? (lambda (e)
    (cond
     ((or (eq? e '+) (eq? e '-) (eq? e '*) (eq? e '/)) #t)
     (else #f))))

(define get-value (lambda (var env)
    (cond
      ;; If the environment is empty, then we could not find 
      ;; a binding in this environment.
      ((null? env) (error "cs305-interpreter unbound variable -->" var))

      ;; Check if the first pair is a binding for the
      ;; variable that we are looking for, and if it is
      ;; return the current value of the variable.
      ((equal? (caar env) var) (cdar env))

      ;; Otherwise, search in the remaning of the environment.
      (else (get-value var (cdr env))))))

(define extend-env (lambda (var val old-env)
      ;; Add the new variable binding to the 
      ;; beginning of the old environment.
      (cons (cons var val) old-env)))

(define repl (lambda (env)
  (let* (
         ; first print out some prompt
         (dummy1 (display "cs305> "))

         ; READ an expression
         (expr (read))

         ; Form the new environment
         (new-env (if (define-stmt? expr)
                      (extend-env (cadr expr) (cs305-interpret (caddr expr) env) env)
                      env))

         ; EVALUATE the expression read
         (val (if (define-stmt? expr)
                  (cadr expr)
                  (cs305-interpret expr env)))

         ; PRINT the value evaluated together
         ; with a prompt as MIT interpreter does
         (dummy2 (display "cs305: "))
         (dummy3 (display val))

         ; get ready for the next prompt
         (dummy4 (newline))
         (dummy4 (newline)))
     (repl new-env))))

(define cs305-interpret (lambda (e env)
  (cond 
    ;; If the input expression is a number, then
    ;; the value of the expression is that number.
    ((number? e) e)

    ;; If the input expression is a symbol, then
    ;; get the current value binding of this variable.
    ((symbol? e) (get-value e env))
    
    ;; If it is an if statement
    ((if-stmt? e) 
        ;; since we have no boolean check if the condition is 0
        (if (not (eq? (cs305-interpret (cadr e) env) 0))
                    ;; if true 3rd element i.e then <expr> is evaluated
                    ( cs305-interpret (caddr e) env)
                    ;; if false 4th element i.e else <expr> is evaluated
                    ( cs305-interpret (cadddr e) env)))

    ;; Otherwise, we must see a list.
    ((not (list? e)) 
          (error "cs305-interpreter cannot evaluate -->" e))
    
    ;; EXIT CLAUSE
    ((eq? (car e) 'exit) (exit))
    ;; CLEAR CLAUSE
    ((eq? (car e) 'clear) (clear))
    
    
    ;; Go go let statement below
    ((let-stmt? e)
        (let*
             ;; create the parameters by getting them through the interpreter
             ((params (map cs305-interpret (map cadr (cadr e)) (make-list (length (map cadr (cadr e))) env)))
             ;; concat the identifier,param double and append them to the old env
             (newenv (append ( map cons (map car (cadr e)) params) env)))
             ;; call the interpreter with the newly create env and the <expr>
             (cs305-interpret (caddr e) newenv)))
    
    ;; Go go let star statement below
    ((letstar-stmt? e)
        (cond
             ;; if it is only one length just build a let and yeet it to let
             ;; LEEEEET IT GOOOOOOOOOOO ALL PUNS INTENDED
             ;; this is also the escape clause
             ((eq? (length (cadr e)) 1) (cs305-interpret (list 'let (cadr e) (caddr e)) env))
             (else 
                    (let*
                        ;; recursively get 1 element from the formal-list
                        ;; put it through the interpreter and add it to the old-env
                        ;; call the interpreter with the newenv and the remaining elements of formal-list
                        (   (par (cs305-interpret (car (cdaadr e)) env))
                            (newenv (cons (cons (caaadr e) par) env)))
                            (cs305-interpret (list 'let* (cdadr e) (caddr e)) newenv)))))
             
    
    
    
    ;;Sanity check
    ((lambda-stmt? e) e)  ;; yalın lambda
    
    ;; God forsaken lambda
    ((lambda-stmt? (car e))
                ;; Check if the parameter sizes match properly
                (if (= (length (cadar e)) (length (cdr e)))
                    (let* 
                        ;; get all the inputs of the lambda through the interpreter to make sure
                        ;; they are all proper values
                        ((params (map cs305-interpret (cdr e) (make-list (length (cdr e)) env))) 
                        ;; append the constructed identifier,param to the old env
                        ;; thus creating a new-env
                        (newenv (append (map cons (cadar e) params) env))) 
                        ;; call the interpreter with newly created environment and operation
                        (cs305-interpret (caddar e) newenv))
                        ;; If there is a parameter mismatch give out an error
                        (error "cs305-interpreter: number of parameters don't match->" e)))

    ;; if it is a built on operation
    ;; just hit it hard with the old razzle dazzle
    ((built-in-op? (car e)) 
            (let ((operands (map cs305-interpret (cdr e) (make-list (length (cdr e)) env)))
                (operator (get-operator (car e))))
                ;; And finally apply the operator to the 
                ;; values of the operands
                        (if (and (or (eq? operator -) (eq? operator /)) (< (length operands) 2)) 
                                (error "- and / operators requires 2 or more operands--> " (length operands))
                                (apply operator operands))))
    
    ;; if it is anything else just value it here
    ;; mostly the defined version of the lambda drops here
    (else    ; (error "Fell here with -->" e)
               (if (lambda-stmt? (get-value (car e) env))
               (cs305-interpret (append! (list (get-value (car e) env)) (cdr e)) env)
               ;; anything else is not implemented and wrong
               (error "cs305-interpreter: wrong type of input-->" e))
    
    ))))
       
         
         

(define cs305 (lambda () (repl '())))
