/* ****************************************************************** **
**    OpenSees - Open System for Earthquake Engineering Simulation    **
**          Pacific Earthquake Engineering Research Center            **
**                                                                    **
**                                                                    **
** (C) Copyright 1999, The Regents of the University of California    **
** All Rights Reserved.                                               **
**                                                                    **
** Commercial use of this program without express permission of the   **
** University of California, Berkeley, is strictly prohibited.  See   **
** file 'COPYRIGHT'  in main directory for information on usage and   **
** redistribution,  and for a DISCLAIMER OF ALL WARRANTIES.           **
**                                                                    **
** Developed by:                                                      **
**   Frank McKenna (fmckenna@ce.berkeley.edu)                         **
**   Gregory L. Fenves (fenves@ce.berkeley.edu)                       **
**   Filip C. Filippou (filippou@ce.berkeley.edu)                     **
**                                                                    **
** ****************************************************************** */

/*                                                                        
** $Revision: 1.1 $
** $Date: 2008-12-01 23:33:16 $
** $Source: /usr/local/cvs/OpenSees/SRC/api/OPS_ProceduralAPI.h,v $
                                                                        
** Written: fmk 
*/


#ifndef _eleAPI

#define _eleAPI

#define ISW_INIT 0
#define ISW_COMMIT 1
#define ISW_REVERT 2
#define ISW_FORM_TANG_AND_RESID 3
#define ISW_FORM_MASS 4
#define ISW_REVERT_TO_START 5

#define OPS_UNIAXIAL_MATERIAL_TYPE 1
#define OPS_SECTION_TYPE 2

typedef struct {
  double time;
  double dt;
} modelState;

typedef void (*matFunct)(struct matObject *, modelState *,double *strain, double *tang, double *stress, int *isw, int *error); 

struct matObject {
  int tag;
  int nParam;
  int nState;
  double *theParam;
  double *cState;
  double *tState;
  matFunct matFunctPtr;
  void *matObjectPtr;
};

typedef struct matObject matObj;

typedef void (*eleFunct)(struct eleObject *, modelState *, double *u,double *tang, double *resid, int *isw, int *error);

struct eleObject {
  int tag;
  int nNode;
  int nDOF;
  int nParam;
  int nState;
  int nMat;
  int *node;
  double *param;
  double *cState;
  double *tState;
  matObject **mats;
  eleFunct eleFunctPtr;
};

typedef struct eleObject eleObj;

#define OPS_ERROR ops_error_
#define OPS_GetIntInput ops_getintinput_
#define OPS_GetDoubleInput ops_getdoubleinput_
#define OPS_AllocateMaterial ops_allocatematerial_
#define OPS_AllocateElement ops_allocateelement_
#define OPS_GetMaterialType ops_getmaterialtype_
#define OPS_GetMaterial ops_getmaterial_
#define OPS_GetMaterialPtr ops_getmaterialptr_
#define OPS_GetNodeCrd ops_getnodecrd_
#define OPS_GetNodeDisp ops_getnodedisp_
#define OPS_InvokeMaterial ops_invokematerial_
#define OPS_InvokeMaterialDirectly ops_invokematerialdirectly_

extern "C" int        OPS_Error(char *, int length);
extern "C" int        OPS_GetIntInput(int *numData, int*data);
extern "C" int        OPS_GetDoubleInput(int *numData, double *data);
extern "C" matObj    *OPS_GetMaterial(int *matTag, int *matType);
extern "C" void       OPS_GetMaterialPtr(int *, matObj *);
extern "C" eleObj    *OPS_GetElement(int *);
extern "C" matObj    *OPS_GetMaterialType(char *type, int sizeType);
extern "C" eleObj    *OPS_GetElementType(char *, int);
extern "C" int        OPS_AllocateElement(eleObject *, int *matTags, int *maType);
extern "C" int        OPS_AllocateMaterial(matObject *);

extern "C" int    OPS_InvokeMaterial(eleObject *, int *,modelState *, double *, double *, double *, int *);
extern "C" int    OPS_InvokeMaterialDirectly(matObject **, modelState *, double *, double *, double *, int *);
extern "C" int    OPS_InvokeMaterialDirectly2(matObject *, modelState *, double *, double *, double *, int *);

extern "C" int    OPS_GetNodeCrd(int *nodeTag, int *sizeData, double *data);
extern "C" int    OPS_GetNodeDisp(int *nodeTag, int *sizeData, double *data);
extern "C" int    OPS_GetNodeVel(int *nodeTag, int *sizeData, double *data);
extern "C" int    OPS_GetNodeAcc(int *nodeTag, int *sizeData, double *data);

class UniaxialMaterial;
class NDMaterial;
class SectionForceDeformation;
extern UniaxialMaterial *OPS_GetUniaxialMaterial(int matTag);
extern NDMaterial *OPS_GetNDMaterial(int matTag);
extern SectionForceDeformation *OPS_GetSectionForeceDeformation(int matTag);

#endif