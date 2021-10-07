#pragma once
//3
#define CHECK_RETURN_0(pCheck) {if(pCheck == NULL) return 0;} // lines 72,76,173 - Company.c
//1
#define CHECK_RETURN_NULL(pCheck) if(pCheck == NULL) return NULL; // line 326 - Company.c
//3
#define CHECK_MSG_RETURN_0(pCheck,msg) if(pCheck == NULL){ printf(msg); return 0;}// lines 136,162 - Company.c , line 126 - AirportManager.c

//files:
//1
#define CHECK_0_MSG_CLOSE_FILE(fp,value,msg) if(value == 0){printf("%s",msg); fclose(fp); return 0;}  //line 39 - fileHelper.c
//1
#define CHECK_NULL__MSG_CLOSE_FILE(fp,value,msg) if(value == NULL){printf(msg); fclose(fp); return 0;} //line 190 - Company.c
//3
#define MSG_CLOSE_RETURN_0(fp, msg) {printf("%s", msg); fclose(fp); return 0;}//lines 29,79,91 - fileHelper.c