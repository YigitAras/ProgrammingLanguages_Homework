
%{
	#include <stdio.h>
	#include "17519-hw4.h"

	void yyerror(const char *s){//called by yyparse on error
		printf("%s\n", s);
	}

	ELEMlist *rootPtr;
	// for error check...
	int ERROR_CHECK = 0;

%}

%union{
	Values values;
	TreeNode *treePtr;
	ELEMlist *elemlistptr;
}

%token tOPEN tCLOSE tEND tCODE tNAME tTYPE  tSECTION  tINSTRUCTOR tCRN  tCAPACITY tSELF tSTART tEND_A
%token <values> tMON
%token <values> tTUE
%token <values> tWED
%token <values> tTHU
%token <values> tFRI
%token <values> tDAY
%token <values> tCOURSE
%token <values> tSTRING
%token <values> tNUM
%token <values> tCLASS
%token <values> tTIME
%token <values> tCONSTRAINT
%token <values> tMEETING
%token <values> tITEM
%type <values> beginClass
%type <values> beginMeeting
%type <treePtr> element
%type <elemlistptr> elementList
%type <treePtr> beginCourse
%type <elemlistptr> classList
%type <elemlistptr> courseAttrList
%type <treePtr> courseAttr
%type <treePtr> class
%type <elemlistptr> classAttrList
%type <treePtr> classAttr
%type <elemlistptr> meetingList
%type <treePtr> meeting
%type <treePtr> itemAttr
%type <elemlistptr> itemList
%type <treePtr> item
%type <treePtr> meetingAttr
%type <values> day
%type <elemlistptr> meetingAttrList
%type <values> beginConstraint
%type <values> beginItem

%%
prog :  elementList {rootPtr = $1;}
                  | {rootPtr = NULL;}
	 	  ;


elementList : element   	  { $$ = mkElemListNode($1,NULL);}
	    | element elementList { $$ = mkElemListNode($1,$2);}
	    ;


element : beginCourse classList endCourse{
						NodeType ntype = COURSE_NODE;
						$$ = mkElemNode($2,$1,ntype,0);
					 }
	| beginConstraint itemList endConstraint{
							NodeType ntype = CONSTRAINT_NODE;
							$$ = mkElemNode($2,NULL,ntype,$1.line_num);
						}
	;


beginCourse : tOPEN tCOURSE  courseAttrList tCLOSE {$$ = mkBeginCourse($3,$2);};

endCourse : tEND tCOURSE tCLOSE;

courseAttrList :  courseAttr 		     {$$ = mkCourseAttrListNode($1,NULL);}
	       |  courseAttr  courseAttrList {$$ = mkCourseAttrListNode($1,$2);}
	       ;

courseAttr : tCODE tSTRING {
				CourseAttrType ctype = ATTR_CODE;
				$$ = mkCourseAttrNode(ctype,$2);
			   }
    	   | tNAME tSTRING {
				CourseAttrType ctype = ATTR_NAME;
				$$ = mkCourseAttrNode(ctype,$2);
			   }
	   | tTYPE tSTRING {
				CourseAttrType ctype = ATTR_TYPE;
				$$ = mkCourseAttrNode(ctype,$2);
			   }
	   ;

classList : class 	    { $$ = mkClassListNode($1,NULL);}
	  | class classList { $$ = mkClassListNode($1,$2);  }
	  ;

class :  beginClass classAttrList endClass meetingList closeClass  { $$ = mkClassNode($2,$4,$1);};


beginClass  : tOPEN tCLASS {$$.line_num = $2.line_num;};
endClass :  tCLOSE;
closeClass : tEND tCLASS tCLOSE;


classAttrList :  classAttr	  	  {$$ = mkClassAttrListNode($1,NULL);}
	       | classAttr classAttrList  {$$ = mkClassAttrListNode($1,$2);};

classAttr : tSECTION tSTRING {
				ClassAttrType ctype = SECTION;
			        $$ = mkClassAttrNode($2,ctype);
			     }
	  | tINSTRUCTOR tSTRING {
				  ClassAttrType ctype = INSTRUCTOR;
				  $$ = mkClassAttrNode($2,ctype);
				}
	  | tCRN tNUM 	   {
			     ClassAttrType ctype = CLASS_CRN;
		  	     $$ = mkClassAttrNode($2,ctype);
		           }
	  | tCAPACITY tNUM {
			     ClassAttrType ctype = CAPACITY;
			     $$ = mkClassAttrNode($2,ctype);
			   }
	  ;
meetingList : meeting 		    {$$= mkMeetingListNode($1,NULL);}
 	    | meeting  meetingList  {$$= mkMeetingListNode($1,$2); }
	    ;

meeting : beginMeeting meetingAttrList endMeeting {$$ = mkMeetingNode($2,$1);};

beginMeeting :  tOPEN tMEETING {$$.line_num = $2.line_num;};
endMeeting :tSELF;

meetingAttrList : meetingAttr		       {$$ = mkMeetingAttrListNode($1,NULL);}
	        | meetingAttr meetingAttrList  {$$ = mkMeetingAttrListNode($1,$2);}
		;

meetingAttr : tDAY day      {$$ = mkMeetingAttrNode($2,DAY);}
	    | tSTART tTIME  {$$ = mkMeetingAttrNode($2,START);}
	    | tEND_A tTIME  {$$ = mkMeetingAttrNode($2,END);}
	    ;

day : tMON {strcpy($$.name_str,$1.name_str);}
    | tTUE {strcpy($$.name_str,$1.name_str);}
    | tWED {strcpy($$.name_str,$1.name_str);}
    | tTHU {strcpy($$.name_str,$1.name_str);}
    | tFRI {strcpy($$.name_str,$1.name_str);}
		;

beginConstraint : tOPEN tCONSTRAINT tCLOSE
									{$$.line_num = $2.line_num;}
								;
endConstraint : tEND tCONSTRAINT  tCLOSE;


itemList : item   	  {$$ = mkItemListNode($1,NULL);}
	 | item itemList  {$$ = mkItemListNode($1,$2);}
	 ;

item :  beginItem itemAttr endItem  { $$ = mkItemNode($2);};

beginItem : tOPEN tITEM { $$.line_num = $2.line_num;};
endItem : tSELF;


itemAttr: tCODE tSTRING	{
			   ItemAttrType itype = ITEM_CODE;
			   $$ = mkItemAttrNode($2,itype);
			}
	| tCRN tNUM     {
			   ItemAttrType itype = ITEM_CRN;
			   $$ = mkItemAttrNode($2,itype);
			}
	;

%%



int main(){
	// check course Attrs
	// courseAttrChecker(rootPtr);
	if(yyparse()){
		return 1;
	}else{
		ERROR_CHECK += courseAttrChecker(rootPtr);
		ERROR_CHECK += class_meet_Checker(rootPtr);
		ERROR_CHECK += constraint_check(rootPtr);

		if(ERROR_CHECK == 0){
			// can pretty print here....
			pretty_print(rootPtr);
		}
		//printf("OK\n");
		return 0;
	}
}
