#include "stdafx.h"
#include "errors.h"
#include "ascii.h"
#include "math.h"
#include "vector3.h"
#include "matrix4.h"
#include "model.h"
#include "collision.h"
#include "portal.h"
#include "map.h"

// singleton map variable
static Map map;
Map* GetMap(void) { return &map; }

Map::Map()
{
 // models
 n_static = 0;
 n_moving = 0;
 n_static_instances = 0;
 n_moving_instances = 0;

 // door controllers
 n_door_controllers = 0;
}

Map::~Map()
{
 FreeMap();
}

ErrorCode Map::LoadMap(LPCWSTR filename)
{
 // free previous
 FreeMap();

 // parse file
 std::deque<std::string> linelist;
 ErrorCode code = ASCIIParseFile(filename, linelist);
 if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

 // temporary data
 uint32 n = 0;
 std::unique_ptr<std::shared_ptr<MeshUTF>[]> meshdata;
 std::unique_ptr<std::shared_ptr<MeshUTFInstance>[]> instdata;

 //
 // PHASE 1:
 // READ STATIC MODELS
 //

 // read number of static models
 n = 0;
 code = ASCIIReadUint32(linelist, &n);
 if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

 // read static models
 if(n)
   {
    // allocate meshdata
    meshdata.reset(new std::shared_ptr<MeshUTF>[n]);

    // load models
    for(uint32 i = 0; i < n; i++)
       {
        // load filename
        STDSTRINGW filename;
        code = ASCIIReadUTF8String(linelist, filename);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // load model
        std::shared_ptr<MeshUTF> model(new MeshUTF);
        code = model->LoadModel(filename.c_str());
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // add model
        meshdata[i] = model;
       }

    // set models
    n_static = n;
    static_models = std::move(meshdata);
   }

 //
 // PHASE 2:
 // READ MOVING MODELS
 //

 // read number of moving models
 n = 0;
 code = ASCIIReadUint32(linelist, &n);
 if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

 // read moving models
 if(n)
   {
    // allocate meshdata
    meshdata.reset(new std::shared_ptr<MeshUTF>[n]);

    // load models
    for(uint32 i = 0; i < n; i++)
       {
        // load filename
        STDSTRINGW filename;
        code = ASCIIReadUTF8String(linelist, filename);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // load model
        std::shared_ptr<MeshUTF> model(new MeshUTF);
        code = model->LoadModel(filename.c_str());
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // add model
        meshdata[i] = model;
       }

    // set models
    n_moving = n;
    moving_models = std::move(meshdata);
   }

 //
 // PHASE 3:
 // READ STATIC INSTANCES
 //

 // read number of static instances
 n = 0;
 code = ASCIIReadUint32(linelist, &n);
 if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

 // read static instances
 if(n)
   {
    // allocate meshdata
    instdata.reset(new std::shared_ptr<MeshUTFInstance>[n]);

    // load instances
    for(uint32 i = 0; i < n; i++)
       {
        // load model reference
        uint32 reference = 0;
        code = ASCIIReadUint32(linelist, &reference);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // validate reference
        if(!(reference < n_static))
           return DebugErrorCode(EC_LOAD_LEVEL, __LINE__, __FILE__);

        // read position
        real32 P[3];
        code = ASCIIReadVector3(linelist, &P[0], false);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // read quaternion
        real32 Q[4];
        code = ASCIIReadVector4(linelist, &Q[0], false);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // add instance
        MeshUTF* ptr = static_models[reference].get();
        instdata[i] = std::make_shared<MeshUTFInstance>(*ptr, P, Q);
        code = instdata[i]->InitInstance();
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);
       }

    // set instance data
    n_static_instances = n;
    static_instances = std::move(instdata);
   }

 //
 // PHASE 4:
 // READ MOVING INSTANCES
 //

 // read number of moving instances
 n = 0;
 code = ASCIIReadUint32(linelist, &n);
 if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

 // read moving instances
 if(n)
   {
    // allocate meshdata
    instdata.reset(new std::shared_ptr<MeshUTFInstance>[n]);

    // load instances
    for(uint32 i = 0; i < n; i++)
       {
        // load model reference
        uint32 reference = 0;
        code = ASCIIReadUint32(linelist, &reference);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // validate reference
        if(!(reference < n_moving))
           return DebugErrorCode(EC_LOAD_LEVEL, __LINE__, __FILE__);

        // read position
        real32 P[3];
        code = ASCIIReadVector3(linelist, &P[0], false);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // read quaternion
        real32 Q[4];
        code = ASCIIReadVector4(linelist, &Q[0], false);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // normalize Q and protect agains invalid values
        if(qnormalize(Q) < 1.0e-7f) {
           Q[0] = 1.0f;
           Q[1] = Q[2] = Q[3] = 0.0f;
          } 

        // add instance
        MeshUTF* ptr = moving_models[reference].get();
        instdata[i] = std::make_shared<MeshUTFInstance>(*ptr, P, Q);
        code = instdata[i]->InitInstance();
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);
       }

    // set instance data
    n_moving_instances = n;
    moving_instances = std::move(instdata);
   }

 //
 // PHASE 5:
 // READ DOOR CONTROLLERS
 //

 // read number of moving instances
 n = 0;
 code = ASCIIReadUint32(linelist, &n);
 if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

 // read door controllers
 if(n)
   {
    // allocate data
    std::unique_ptr<DoorController[]> dcdata;
    dcdata.reset(new DoorController[n]);

    // read data
    for(uint32 i = 0; i < n; i++)
       {
        // read position
        real32 P[3];
        code = ASCIIReadVector3(linelist, &P[0], false);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // read quaternion
        real32 Q[4];
        code = ASCIIReadVector4(linelist, &Q[0], false);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // normalize Q and protect agains invalid values
        if(qnormalize(Q) < 1.0e-7f) {
           Q[0] = 1.0f;
           Q[1] = Q[2] = Q[3] = 0.0f;
          }

        // convert quaternion to matrix
        real32 M[9];
        matrix3D_quaternion(M, Q);

        // read half-widths
        real32 H[3];
        code = ASCIIReadVector3(linelist, &H[0], false);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // read reference
        uint32 reference = 0;
        code = ASCIIReadUint32(linelist, &reference);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // validate reference
        if(!(reference < n_moving))
           return DebugErrorCode(EC_LOAD_LEVEL, __LINE__, __FILE__);

        // read animations
        sint32 anim1 = -1;
        sint32 anim2 = -1;
        sint32 anim3 = -1;
        code = ASCIIReadSint32(linelist, &anim1);
        code = ASCIIReadSint32(linelist, &anim2);
        code = ASCIIReadSint32(linelist, &anim3);
        if(Fail(code)) return DebugErrorCode(code, __LINE__, __FILE__);

        // TODO:
        // WE NEED TO VALIDATE ANIMATION INDICES HERE!!!

        // set item
        DoorController& item = dcdata[i];
        item.box.center[0] = P[0];
        item.box.center[1] = P[1];
        item.box.center[2] = P[2];
        item.box.widths[0] = H[0];
        item.box.widths[1] = H[1];
        item.box.widths[2] = H[2];
        item.box.x[0] = M[0]; item.box.x[1] = M[1]; item.box.x[2] = M[2];
        item.box.y[0] = M[3]; item.box.y[1] = M[4]; item.box.y[2] = M[5];
        item.box.z[0] = M[6]; item.box.z[1] = M[7]; item.box.z[2] = M[8];
        item.anim_start = (anim1 == -1 ? 0xFFFFFFFFul : static_cast<uint32>(anim1));
        item.anim_enter = (anim2 == -1 ? 0xFFFFFFFFul : static_cast<uint32>(anim2));
        item.anim_leave = (anim3 == -1 ? 0xFFFFFFFFul : static_cast<uint32>(anim3));
       }

    // set data
    n_door_controllers = n;
    door_controllers = std::move(dcdata);
   }

/*
 // read number of portal cells
 uint32 n_cells = 0;
 code = ASCIIReadUint32(linelist, &n_cells);
 if(Fail(code)) return DebugErrorCode(EC_LOAD_LEVEL, __LINE__, __FILE__);

 // read cell graph (named connections)
 for(uint32 i = 0; i < n_cells; i++)
    {
     // load line that holds adjacency list
     char line[1024];
     code = ASCIIReadString(linelist, line);
     if(Fail(code)) return DebugErrorCode(EC_LOAD_LEVEL, __LINE__, __FILE__);

     // separate line into paramters (you must have at least one parameter)
     std::deque<std::string> parameters;
     boost::split(parameters, linelist.front(), boost::is_any_of(" "));
     if(!parameters.size()) return DebugErrorCode(EC_LOAD_LEVEL, __LINE__, __FILE__);

     // TODO:
     // This is where we want to lookup the names of the portals to match them to the names of the
     // static models so we can index them. Once we have the model, we can figure out bounding boxes
     // for the portals.
    }

 // read cell graph (portal connections)
 for(uint32 i = 0; i < n_cells; i++)
    {
     // load cell references
     std::vector<uint32> v;
     code = ASCIIReadArray(linelist, v);
     if(Fail(code)) return DebugErrorCode(EC_LOAD_LEVEL, __LINE__, __FILE__);

     // bidirectional portal
     // room_001 room_002 room_004
     // room_004 room_001 room_003
     // 0 1 # room_001 -> room_004 using cell[1]
     // 1 3 # room_004 -> room_001 using cell[1] (give a warning if they don't match)

     // unidirectional portal
     // room_001 room_002 room_004
     // room_004 room_003
     // 0 1 # room_001 -> room_004 using cell[1]
     // 3   # room_004 -> room_003 using cell[3]

     // cell with no connections
     // room_001
     // room_002
     // -1 means no cell
     // -1 means no cell
    }
*/
 return EC_SUCCESS;
}

void Map::FreeMap(void)
{
 if(n_door_controllers) door_controllers.reset();
 n_door_controllers = 0;

 // free instances
 if(n_static_instances) static_instances.reset();
 if(n_moving_instances) moving_instances.reset();
 n_static_instances = 0;
 n_moving_instances = 0;

 // free models
 if(n_static) static_models.reset();
 if(n_moving) moving_models.reset();
 n_static = 0;
 n_moving = 0;
}

void Map::RenderMap(real32 dt)
{
 // INEFFICIENT!!!
 for(uint32 i = 0; i < n_door_controllers; i)
    {
    }

 // INEFFICIENT!!!
 // RENDER ALL STATIC MODEL INSTANCES
 for(uint32 i = 0; i < n_static_instances; i++)
     static_instances[i]->RenderModel();

 // INEFFICIENT!!!
 // RENDER ALL MOVING MODEL INSTANCES
 for(uint32 i = 0; i < n_moving_instances; i++) {
     moving_instances[i]->Update(dt);
     moving_instances[i]->RenderModel();
    }
}