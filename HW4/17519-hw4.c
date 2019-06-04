#include "17519-hw4.h"

// binds ELEMlist nodes together with their respective elems and ptrs
ELEMlist *mkElemListNode(TreeNode *elem,ELEMlist *next){
  ELEMlist *ret = (ELEMlist *) malloc(sizeof(ELEMlist));
  ret->elem = elem;
  ret->next_elemlist = next;
  return ret;
}

// ===========================================================================

TreeNode *mkElemNode(ELEMlist *Listptr, TreeNode *courseBegin,NodeType ntype,int num){
  TreeNode *ret = (TreeNode*) malloc(sizeof(TreeNode));
  ret->n_type = ntype;
  ret->ElemPTR = (ELEMENT*) malloc(sizeof(ELEMENT));
  if(ntype == COURSE_NODE){
      // if course_node
      ret->ElemPTR->course_node.Class_List_Ptr = Listptr;
      ret->ElemPTR->course_node.Begin_Course_Node = courseBegin;
      return ret;
  }else if(ntype == CONSTRAINT_NODE){
      // if constraint_node
      ret->ElemPTR->constraint_node.line_num = num;
      ret->ElemPTR->constraint_node.Item_List_Ptr = Listptr;
      return ret;
  }
  printf("Unexpected error at mkElemNode...\n");
  return ret;
}

// ===========================================================================

TreeNode *mkBeginCourse(ELEMlist *Listptr,Values values){
  TreeNode *ret = (TreeNode*) malloc(sizeof(TreeNode));
  ret->n_type = BEGINCOURSE_NODE;
  ret->ElemPTR = (ELEMENT*) malloc(sizeof(ELEMENT));
  ret->ElemPTR->begincourse_node.Course_Attr_List = Listptr;
  ret->ElemPTR->begincourse_node.line_num = values.line_num;
  return ret;
}

// ===========================================================================

ELEMlist *mkCourseAttrListNode(TreeNode *cattr,ELEMlist *cnext){
  ELEMlist *ret = (ELEMlist *) malloc(sizeof(ELEMlist));
  ret->elem = cattr;
  ret->next_elemlist = cnext;
  return ret;
}

// ===========================================================================

TreeNode *mkCourseAttrNode(CourseAttrType ctype,Values values){
  TreeNode *ret = (TreeNode *) malloc(sizeof(TreeNode));
  ret->n_type = COURSEATTR_NODE;
  ret->ElemPTR = (ELEMENT*) malloc(sizeof(ELEMENT));
  ret->ElemPTR->courseattr_node.line_num = values.line_num;
  ret->ElemPTR->courseattr_node.courseattr_type = ctype;
  // strcpy(dest, src);
  strcpy(ret->ElemPTR->courseattr_node.attr_name,values.name_str);
  //strcpy(ret->ElemPTR->courseattr_node.attr_name,values.name_str);
  return ret;
}
// ===========================================================================

ELEMlist *mkClassListNode(TreeNode *cptr,ELEMlist *cnext){
  ELEMlist *ret = (ELEMlist *) malloc(sizeof(ELEMlist));
  ret->elem = cptr;
  ret->next_elemlist = cnext;
  return ret;
}

// ===========================================================================

TreeNode *mkClassNode(ELEMlist *cattrlistptr,ELEMlist *mlistptr,Values values){
  TreeNode *ret = (TreeNode*) malloc(sizeof(TreeNode));
  ret->n_type = CLASS_NODE;
  ret->ElemPTR = (ELEMENT*) malloc(sizeof(ELEMENT));
  ret->ElemPTR->class_node.Class_Attr_List = cattrlistptr;
  ret->ElemPTR->class_node.Meeting_List = mlistptr;
  ret->ElemPTR->class_node.line_num = values.line_num;
  return ret;
}

// ===========================================================================

ELEMlist *mkClassAttrListNode(TreeNode* cptr,ELEMlist *cnext){
  ELEMlist *ret = (ELEMlist *) malloc(sizeof(ELEMlist));
  ret->elem = cptr;
  ret->next_elemlist = cnext;
  return ret;
}

// ===========================================================================

TreeNode* mkClassAttrNode(Values values,ClassAttrType ctype){
  TreeNode *ret = (TreeNode*) malloc(sizeof(TreeNode));
  ret->n_type = CLASSATTR_NODE;
  ret->ElemPTR = (ELEMENT*) malloc(sizeof(ELEMENT));
  ret->ElemPTR->classattr_node.line_num = values.line_num;
  ret->ElemPTR->classattr_node.classattr_type = ctype;
  if(ctype == CLASS_CRN || ctype == CAPACITY){
    ret->ElemPTR->classattr_node.attr_num = values.value_num;
    return ret;
  }else if(ctype == SECTION || ctype == INSTRUCTOR){
    strcpy(ret->ElemPTR->classattr_node.attr_name,values.name_str);
    return ret;
  }
  printf("Unexpected error @ Class Attr Node creation...\n");
  return NULL;
}

// ===========================================================================

ELEMlist *mkMeetingListNode(TreeNode *mptr,ELEMlist *mnext){
  ELEMlist *ret = (ELEMlist *) malloc(sizeof(ELEMlist));
  ret->elem = mptr;
  ret->next_elemlist = mnext;
  return ret;
}

// ===========================================================================

TreeNode *mkMeetingNode(ELEMlist *attrList,Values values){
  TreeNode *ret = (TreeNode* ) malloc(sizeof(TreeNode));
  ret->n_type = MEETING_NODE;
  ret->ElemPTR = (ELEMENT*) malloc(sizeof(ELEMENT));
  ret->ElemPTR->meeting_node.MeetingAttr_List_Ptr = attrList;
  ret->ElemPTR->meeting_node.line_num = values.line_num;
  return ret;
}

// ===========================================================================

ELEMlist *mkMeetingAttrListNode(TreeNode *mptr,ELEMlist *mnext){
  ELEMlist *ret = (ELEMlist *) malloc(sizeof(ELEMlist));
  ret->elem = mptr;
  ret->next_elemlist = mnext;
  return ret;
}

// ===========================================================================

TreeNode* mkMeetingAttrNode(Values values,MeetingAttrType mtype){
  TreeNode *ret = (TreeNode*) malloc(sizeof(TreeNode));
  ret->n_type = MEETINGATTR_NODE;
  ret->ElemPTR = (ELEMENT*) malloc(sizeof(ELEMENT));
  ret->ElemPTR->meetingattr_node.line_num = values.line_num;
  ret->ElemPTR->meetingattr_node.meetingattr_type = mtype;

  if(mtype == DAY){
     strcpy(ret->ElemPTR->meetingattr_node.attr_name,values.name_str);
     return ret;
  }else if(mtype ==  START | mtype == END){
     strcpy(ret->ElemPTR->meetingattr_node.attr_name,values.name_str);
     return ret;
  }
  printf("Unexpected Error Happened at mkMeetingAttrNode ...\n");
}

// ===========================================================================

ELEMlist *mkItemListNode(TreeNode *iptr,ELEMlist *inext){
  ELEMlist *ret = (ELEMlist *) malloc(sizeof(ELEMlist));
  ret->elem = iptr;
  ret->next_elemlist = inext;
  return ret;
}

// ===========================================================================

TreeNode *mkItemNode(TreeNode *iaptr){
  TreeNode *ret = (TreeNode*) malloc(sizeof(TreeNode));
  ret->n_type = ITEM_NODE;
  ret->ElemPTR = (ELEMENT*) malloc(sizeof(ELEMENT));
  ret->ElemPTR->item_node.Item_Attr_Ptr = iaptr;
  return ret;
}

// ===========================================================================

TreeNode *mkItemAttrNode(Values values,ItemAttrType itype){
  TreeNode *ret = (TreeNode*) malloc(sizeof(TreeNode));
  ret->n_type = ITEMATTR_NODE;
  ret->ElemPTR = (ELEMENT*) malloc(sizeof(ELEMENT));
  ret->ElemPTR->itemattr_node.itemattr_type = itype;

  if(itype == ITEM_CODE){
    strcpy(ret->ElemPTR->itemattr_node.attr_name,values.name_str);
    ret->ElemPTR->itemattr_node.line_num = values.line_num;
    return ret;
  }else if (itype ==ITEM_CRN ){
    ret->ElemPTR->itemattr_node.num = values.value_num;
    ret->ElemPTR->itemattr_node.line_num = values.line_num;
    return ret;
  }
  printf("An oopsie happened at mkItemAttrNode...\n");
}

// ===========================================================================

int courseAttrChecker(ELEMlist *root){
  // take the root
  int ERROR_CHECK = 0;
  while(root != NULL){
    // traverse the top level looking for classes...
    if(root->elem->n_type == COURSE_NODE){
      int att_count[3] = {0,0,0};
      int line_count = 0;
      // get the CourseAttrList from BeginCourse
      TreeNode *temp1 = root->elem->ElemPTR->course_node.Begin_Course_Node;
      line_count = temp1->ElemPTR->begincourse_node.line_num;
      ELEMlist *temp = temp1->ElemPTR->begincourse_node.Course_Attr_List;
      while(temp != NULL){
        if(temp->elem->ElemPTR->courseattr_node.courseattr_type == ATTR_CODE){
          att_count[0]++;
        }
        else if(temp->elem->ElemPTR->courseattr_node.courseattr_type == ATTR_NAME){
          att_count[1]++;
        }
        else if(temp->elem->ElemPTR->courseattr_node.courseattr_type == ATTR_TYPE){
          att_count[2]++;
        }
        temp = temp->next_elemlist;
      }
      // code -> name -> type
      if(att_count[0] != 1){
        printf("ERROR: course element at line %d has %d occurences of code\n",
                                              line_count,att_count[0]);
        ERROR_CHECK = 1;
      }
      if(att_count[1] != 1){
        printf("ERROR: course element at line %d has %d occurences of name\n",
                                              line_count,att_count[1]);
        ERROR_CHECK = 1;
      }

      if(att_count[2] != 1){
        printf("ERROR: course element at line %d has %d occurences of type\n",
                                              line_count,att_count[2]);
        ERROR_CHECK = 1;
      }
    }
    root = root->next_elemlist;
  }
  if(ERROR_CHECK != 0) return 1;
  else                 return 0;
}
// ===========================================================================

int class_meet_Checker(ELEMlist *root){
  int ERROR_CHECK = 0;

  while(root != NULL){
    // dive into root
    if(root->elem->n_type == COURSE_NODE){
      int class_line = 0;
      int meeting_line = 0;
      int c_attr_count[4] = {0,0,0,0};
      int m_attr_count[3] = {0,0,0};
      ELEMlist *class_ptr = root->elem->ElemPTR->course_node.Class_List_Ptr;

      while(class_ptr != NULL){
        // get the ptrs
        ELEMlist *cattr_ptr = class_ptr->elem->ElemPTR->class_node.Class_Attr_List;
        ELEMlist *meet_ptr = class_ptr->elem->ElemPTR->class_node.Meeting_List;
        class_line = class_ptr->elem->ElemPTR->class_node.line_num;
        while(cattr_ptr != NULL){
          //traverse the class attributes
          if(cattr_ptr->elem->ElemPTR->classattr_node.classattr_type == SECTION){
            c_attr_count[0]++;
          }else if(cattr_ptr->elem->ElemPTR->classattr_node.classattr_type == INSTRUCTOR){
            c_attr_count[1]++;
          }else if(cattr_ptr->elem->ElemPTR->classattr_node.classattr_type == CLASS_CRN){
            c_attr_count[2]++;
          }else if(cattr_ptr->elem->ElemPTR->classattr_node.classattr_type == CAPACITY){
            c_attr_count[3]++;
          }

          cattr_ptr = cattr_ptr->next_elemlist;
        }
        if(c_attr_count[0] != 1){
          printf("ERROR: class element at line %d has %d occurences of section\n",
                                                class_line,c_attr_count[0]);
          ERROR_CHECK = 1;
        }
        if(c_attr_count[1] != 1){
          printf("ERROR: class element at line %d has %d occurences of instructor\n",
                                                class_line,c_attr_count[1]);
          ERROR_CHECK = 1;
        }
        if(c_attr_count[2] != 1){
          printf("ERROR: class element at line %d has %d occurences of crn\n",
                                                class_line,c_attr_count[2]);
          ERROR_CHECK = 1;
        }
        if(c_attr_count[3] != 1){
          printf("ERROR: class element at line %d has %d occurences of capacity\n",
                                                class_line,c_attr_count[3]);
          ERROR_CHECK = 1;
        }
        // MEETING LIST CHECKS BELOW
        while(meet_ptr != NULL){
          meeting_line = meet_ptr->elem->ElemPTR->meeting_node.line_num;
          ELEMlist *mattr_ptr = meet_ptr->elem->ElemPTR->meeting_node.MeetingAttr_List_Ptr;
          while(mattr_ptr!=NULL){
            // traverse the meeting attributes
            if(mattr_ptr->elem->ElemPTR->meetingattr_node.meetingattr_type == DAY){
              m_attr_count[0]++;
            } else if(mattr_ptr->elem->ElemPTR->meetingattr_node.meetingattr_type == START){
              m_attr_count[1]++;
            } else if(mattr_ptr->elem->ElemPTR->meetingattr_node.meetingattr_type == END){
              m_attr_count[2]++;
            }
            mattr_ptr = mattr_ptr->next_elemlist;
          }
          if(m_attr_count[0] != 1){
            printf("ERROR: meeting element at line %d has %d occurences of day\n",
                                                  meeting_line,m_attr_count[0]);
            ERROR_CHECK = 1;
          }
          if(m_attr_count[1] != 1){
            printf("ERROR: meeting element at line %d has %d occurences of start\n",
                                                    meeting_line,m_attr_count[1]);
            ERROR_CHECK = 1;
          }
          if(m_attr_count[2] != 1){
            printf("ERROR: meeting element at line %d has %d occurences of end\n",
                                                    meeting_line,m_attr_count[2]);
            ERROR_CHECK = 1;
          }
          meet_ptr = meet_ptr->next_elemlist;
          m_attr_count[0] = 0;
          m_attr_count[1] = 0;
          m_attr_count[2] = 0;
        }
        class_ptr = class_ptr->next_elemlist;
        c_attr_count[0] = 0;
        c_attr_count[1] = 0;
        c_attr_count[2] = 0;
        c_attr_count[3] = 0;
      }
    }
    root = root->next_elemlist;
  }

  if(ERROR_CHECK != 0) return 1;
  else                 return 0;
}
// ===========================================================================

int constraint_check(ELEMlist *root){
  int ERROR_CHECK = 0;
  int line_num = 0;
  ELEMlist *root2 = root;
  while(root2 != NULL){
  if(root2->elem->n_type == CONSTRAINT_NODE ){
    line_num = root2->elem->ElemPTR->constraint_node.line_num;
    // TODO: took line, if code search course NODEs
    // if crn search for classes...
    ELEMlist *temp = root2->elem->ElemPTR->constraint_node.Item_List_Ptr;

    while(temp != NULL){
      TreeNode *t_ptr = temp->elem->ElemPTR->item_node.Item_Attr_Ptr;
      if(t_ptr->ElemPTR->itemattr_node.itemattr_type == ITEM_CRN){
          int code_cmp = t_ptr->ElemPTR->itemattr_node.num;
          // search the tree for the CRN
          int found = 0;
          ELEMlist *root4 = root;
          while(root4 != NULL){
              if(root4->elem->n_type == COURSE_NODE){
                  ELEMlist *class_ptr = root4->elem->ElemPTR->course_node.Class_List_Ptr;
                  while(class_ptr != NULL){
                    ELEMlist *cattr_ptr = class_ptr->elem->ElemPTR->class_node.Class_Attr_List;
                    while(cattr_ptr != NULL){
                        if(cattr_ptr->elem->ElemPTR->classattr_node.classattr_type == CLASS_CRN){
                            int test = cattr_ptr->elem->ElemPTR->classattr_node.attr_num;
                            if(test == code_cmp){
                              found = 1;
                            }
                        }
                      cattr_ptr = cattr_ptr->next_elemlist;
                    }

                    class_ptr = class_ptr->next_elemlist;
                  }
              }
              root4 = root4->next_elemlist;
          }

          if(found == 0){
            printf("ERROR: constraint at line %d refers to undefined crn=%d\n",line_num,code_cmp);
            ERROR_CHECK = 1;
          }
      }else if(t_ptr->ElemPTR->itemattr_node.itemattr_type == ITEM_CODE){
          char t_arr[50];
          strcpy(t_arr,t_ptr->ElemPTR->itemattr_node.attr_name);
          // search the tree for the CODE
          ELEMlist *root3 = root;
          int found = 0;
          while(root3 != NULL){
              if(root3->elem->n_type ==COURSE_NODE ){
                TreeNode *tt1 = root3->elem->ElemPTR->course_node.Begin_Course_Node;
                ELEMlist *tt2 = tt1->ElemPTR->begincourse_node.Course_Attr_List;
                while(tt2 != NULL){
                  if(tt2->elem->ElemPTR->courseattr_node.courseattr_type == ATTR_CODE){
                    if(strcmp(t_arr,tt2->elem->ElemPTR->courseattr_node.attr_name) == 0){
                      found = 1;
                    }
                  }
                  tt2 = tt2->next_elemlist;
                }
              }
              root3 = root3->next_elemlist;
          }
          if(found == 0){
            printf("ERROR: constraint at line %d refers to undefined code=%s\n",line_num,t_arr);
            ERROR_CHECK = 1;
          }
      }
      temp = temp->next_elemlist;
    }
  }
  root2 = root2->next_elemlist;
}

  if(ERROR_CHECK != 0) return 1;
  else                 return 0;
}

// ===========================================================================

void pretty_print(ELEMlist *root){
  ELEMlist *root2 = root;
  ELEMlist *root3 = root;

  // loop for COURSE nodes first
  while(root2 != NULL){
    if(root2->elem->n_type == COURSE_NODE){
    TreeNode *bc_ptr = root2->elem->ElemPTR->course_node.Begin_Course_Node;
    ELEMlist *cl_at_ptr = bc_ptr->ElemPTR->begincourse_node.Course_Attr_List;
    printf("<course");
    while(cl_at_ptr != NULL){
      printf(" ");
      if(cl_at_ptr->elem->ElemPTR->courseattr_node.courseattr_type == ATTR_CODE){
        printf("code=%s",cl_at_ptr->elem->ElemPTR->courseattr_node.attr_name);
      }
      else if(cl_at_ptr->elem->ElemPTR->courseattr_node.courseattr_type == ATTR_NAME){
        printf("name=%s", cl_at_ptr->elem->ElemPTR->courseattr_node.attr_name);
      }
      else if(cl_at_ptr->elem->ElemPTR->courseattr_node.courseattr_type == ATTR_TYPE){
        printf("type=%s",cl_at_ptr->elem->ElemPTR->courseattr_node.attr_name);
      }
      cl_at_ptr = cl_at_ptr->next_elemlist;
    }
    // close course brackets
    printf(">\n");

    // traverse classes and print with 1 indent
    ELEMlist *class_ptr = root2->elem->ElemPTR->course_node.Class_List_Ptr;
    while(class_ptr != NULL){
      // get the ptrs

      ELEMlist *cattr_ptr = class_ptr->elem->ElemPTR->class_node.Class_Attr_List;
      ELEMlist *meet_ptr = class_ptr->elem->ElemPTR->class_node.Meeting_List;

      printf("\t<class");

      while(cattr_ptr != NULL){
        printf(" ");
        if(cattr_ptr->elem->ElemPTR->classattr_node.classattr_type == SECTION){
          printf("section=%s",cattr_ptr->elem->ElemPTR->classattr_node.attr_name);
        }else if(cattr_ptr->elem->ElemPTR->classattr_node.classattr_type == INSTRUCTOR){
          printf("instructor=%s",cattr_ptr->elem->ElemPTR->classattr_node.attr_name);
        }else if(cattr_ptr->elem->ElemPTR->classattr_node.classattr_type == CLASS_CRN){
          printf("crn=%d",cattr_ptr->elem->ElemPTR->classattr_node.attr_num);
        }else if(cattr_ptr->elem->ElemPTR->classattr_node.classattr_type == CAPACITY){
          printf("capacity=%d",cattr_ptr->elem->ElemPTR->classattr_node.attr_num);
        }

        cattr_ptr = cattr_ptr->next_elemlist;
      }
      printf(">\n");
      // get the meeting elements
      while(meet_ptr != NULL){
        printf("\t\t<meeting");
        ELEMlist *mattr_ptr = meet_ptr->elem->ElemPTR->meeting_node.MeetingAttr_List_Ptr;
        while(mattr_ptr!=NULL){
          // traverse the meeting attributes
          printf(" ");
          if(mattr_ptr->elem->ElemPTR->meetingattr_node.meetingattr_type == DAY){
            printf("day=%s",mattr_ptr->elem->ElemPTR->meetingattr_node.attr_name);
          } else if(mattr_ptr->elem->ElemPTR->meetingattr_node.meetingattr_type == START){
            printf("start=%s",mattr_ptr->elem->ElemPTR->meetingattr_node.attr_name);
          } else if(mattr_ptr->elem->ElemPTR->meetingattr_node.meetingattr_type == END){
            printf("end=%s",mattr_ptr->elem->ElemPTR->meetingattr_node.attr_name);
          }

          mattr_ptr = mattr_ptr->next_elemlist;
          }
        printf("/>\n");
        meet_ptr = meet_ptr->next_elemlist;
        }

      printf("\t</class>\n");
      class_ptr = class_ptr->next_elemlist;
      }
    printf("</course>\n");
    }
  root2 = root2->next_elemlist;
  }
  // check for CONSTRAINT ELEMENTS NOW....
  while(root3 != NULL){
    if(root3->elem->n_type == CONSTRAINT_NODE){
      printf("<constraint>\n");
      ELEMlist *i_temp = root3->elem->ElemPTR->constraint_node.Item_List_Ptr;
      while(i_temp != NULL){
        TreeNode *t_ptr = i_temp->elem->ElemPTR->item_node.Item_Attr_Ptr;
        if(t_ptr->ElemPTR->itemattr_node.itemattr_type == ITEM_CRN){
          printf("\t<item crn=%d/>\n",t_ptr->ElemPTR->itemattr_node.num);
        }
        if(t_ptr->ElemPTR->itemattr_node.itemattr_type == ITEM_CODE){
          printf("\t<item code=%s/>\n",t_ptr->ElemPTR->itemattr_node.attr_name);
        }
        i_temp = i_temp->next_elemlist;
      }
      printf("</constraint>\n");
    }
    root3 = root3->next_elemlist;
  }
}
