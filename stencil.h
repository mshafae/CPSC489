#ifndef __CS489_STENCIL_H
#define __CS489_STENCIL_H

#include "errors.h"

#define STENCIL_SKELETON_MODEL 0 
#define STENCIL_SKELETON_BONES 1

ErrorCode InitStencilStates(void);
void FreeStencilStates(void);
ID3D11DepthStencilState* GetStencilState(UINT index);
ErrorCode SetStencilState(UINT index, UINT value);
ErrorCode ResetStencilState(void);

#endif
