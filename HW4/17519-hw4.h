#ifndef __HW4__
#define __HW4__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { COURSE_NODE, CONSTRAINT_NODE, CLASS_NODE, ITEM_NODE,
               COURSEATTR_NODE, CLASSATTR_NODE, MEETING_NODE,
               MEETINGATTR_NODE, ITEMATTR_NODE, BEGINCOURSE_NODE,
               COURSEATTR_LIST} NodeType;

typedef enum { ATTR_CODE, ATTR_NAME, ATTR_TYPE } CourseAttrType;
typedef enum {SECTION, INSTRUCTOR, CLASS_CRN , CAPACITY} ClassAttrType;
typedef enum {DAY,START,END} MeetingAttrType;
typedef enum {MON,TUE,WED,THU,FRI} Day_Type;
typedef enum {ITEM_CRN,ITEM_CODE} ItemAttrType;

/*
Below are the structured nodes used on the semantic tree
*/
typedef struct Values {
    int value_num;
    int line_num;
    char name_str[50];
} Values;
// To hold the Main list of elements
typedef struct ELEMlist{
  struct ELEMlist *next_elemlist;
  struct TreeNode *elem;
} ELEMlist;

// parts of element: beginCourse classList endCourse
typedef struct BeginCourse{
  // beginCourse: tOPEN tCOURSE coursteAttrList tCLOSE
  int line_num;
  struct ELEMlist *Course_Attr_List;
} BeginCourse;

// one version of element: (Course) or Constraint
typedef struct CourseNode{
  // struct TreeNode *ElemListPtr; // for the element list
  struct ELEMlist *Class_List_Ptr;
  struct TreeNode *Begin_Course_Node;  // beginCourse one
  // tEND tCOURSE tCLOSE
} CourseNode;

typedef struct ConstraintNode{
  // struct TreeNode *ElemListPtr; // for the element list
  struct ELEMlist *Item_List_Ptr;    // for the itemList
  int line_num;
  // beginConstraint: tOPEN tCONSTRAINT tCLOSE
  // endConstraint: tEND tCONSTRAINT tCLOSE
} ConstraintNode;
/*
REPLACED BY ELEMlist NODE

ALL LIST NODEs are replaced by ELEMlist
*/

typedef struct CourseAttrNode{
  CourseAttrType courseattr_type;
  char attr_name[50];
  int line_num;
} CourseAttrNode;

typedef struct ClassNode{
  // beginclass: tOPEN tCLASS
  // endClass: tCLOSE
  // closeClass: tEND tCLASS tCLOSE
  int line_num;
  struct ELEMlist *Class_Attr_List;
  struct ELEMlist *Meeting_List;
} ClassNode;

typedef struct ClassAttrNode{
  ClassAttrType classattr_type;
  char attr_name[50];
  int attr_num;
  int line_num;
} ClassAtrrNode;

typedef struct MeetingNode{
  // beginMeeting: tOPEN tMEETING
  // endMeeting: tSELF
  int line_num;
  struct ELEMlist *MeetingAttr_List_Ptr;
} MeetingNode;

typedef struct MeetingAttrNode{
  MeetingAttrType meetingattr_type;
  char attr_name[50];
  Day_Type day_name;
  int line_num;
} MeetingAttrNode;

typedef struct ItemNode{
  struct TreeNode *Item_Attr_Ptr;
  // beginItem: tOPEN tITEM
  // endItem: tSELF
} ItemNode;

typedef struct ItemAttrNode{
  ItemAttrType itemattr_type;
  int num;
  char attr_name[50];
  int line_num;
} ItemAttrNode;


/*
    ABOVE ARE THE REVISED NODE STRUCTS
*/


typedef union {
  CourseNode course_node;
  ConstraintNode constraint_node;
  CourseAttrNode courseattr_node;
  ClassNode class_node;
  ClassAtrrNode classattr_node;
  MeetingNode meeting_node;
  MeetingAttrNode meetingattr_node;
  ItemNode item_node;
  ItemAttrNode itemattr_node;
  BeginCourse begincourse_node;
} ELEMENT;

// all purpouse nodes for anything else
typedef struct TreeNode{
  NodeType n_type;
  ELEMENT *ElemPTR;
} TreeNode;
// FUNCTION DEFINITIONS BELOW

/*
    Below are the Tree Building Nodes
*/
TreeNode *mkElemNode(ELEMlist *Listptr, TreeNode *courseBegin,NodeType ntype,int num);
ELEMlist *mkElemListNode(TreeNode *elem,ELEMlist *next);
TreeNode *mkBeginCourse(ELEMlist *Listptr,Values values);
ELEMlist *mkCourseAttrListNode(TreeNode *cattr,ELEMlist *cnext);
TreeNode *mkCourseAttrNode(CourseAttrType ctype,Values values);
ELEMlist *mkClassListNode(TreeNode *cptr,ELEMlist *cnext);
TreeNode *mkClassNode(ELEMlist *cattrlistptr,ELEMlist *mlistptr,Values values);
ELEMlist *mkClassAttrListNode(TreeNode* cptr,ELEMlist *cnext);
TreeNode* mkClassAttrNode(Values values,ClassAttrType ctype);
ELEMlist *mkMeetingListNode(TreeNode *mptr,ELEMlist *mnext);
TreeNode *mkMeetingNode(ELEMlist *attrList,Values values);
ELEMlist *mkMeetingAttrListNode(TreeNode *mptr,ELEMlist *mnext);
TreeNode* mkMeetingAttrNode(Values values,MeetingAttrType mtype);
ELEMlist *mkItemListNode(TreeNode *iptr,ELEMlist *inext);
TreeNode *mkItemNode(TreeNode *iaptr);
TreeNode *mkItemAttrNode(Values values,ItemAttrType itype);

/*
    Semantic Rule Checkers below
*/
int courseAttrChecker(ELEMlist *root);
int class_meet_Checker(ELEMlist *root);
int constraint_check(ELEMlist *root);
void pretty_print(ELEMlist *root);

#endif
